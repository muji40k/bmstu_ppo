\c humankind

reset role;

create or replace function authentication.authorize(_role text, _email text, _password text) 
returns bool
language plpgsql
as
$$
declare
    _is bool = false;
    _prole text;

begin
    select current_user into _prole;
    reset role;

    if exists(select *
              from (select id
                    from authentication.users
                    where email = _email and password = _password) as fuser
              join (select user_id
                    from authentication.user_roles
                    where role = _role) as frole
                on fuser.id = frole.user_id) then
        execute format ('set role %I', _role);
        select true into _is;
    else
        execute format ('set role %I', _prole);
    end if;

    return _is;
end;
$$;

create or replace procedure authentication.add_role(_role text, _email text, _password text) 
language plpgsql
as
$$
declare
    _prole text;
    _id integer;

begin
    select current_user into _prole;
    reset role;

    select id
    from authentication.users
    where email = _email and password = _password
    into _id;

    if _id is not null then
        insert into authentication.user_roles (user_id, role) values (_id, _role);
    end if;

    execute format ('set role %I', _prole);
end;
$$;

-- ROLES
-- Administrator
drop owned by admin;
drop role if exists admin;
create role admin with superuser;

grant select, insert, update, delete
on all tables
   in schema entities, human, place, country,
             resource, language, authentication
to admin;

-- Guest
drop owned by guest;
drop role if exists guest;
create role guest;

grant usage
on schema entities, human, place, country, resource, language, authentication
to guest;

grant select
on all tables
   in schema entities, human, place, country,
             resource, language
to guest;

grant select, insert on table authentication.users to guest;
grant insert on table authentication.user_human to guest;
grant insert on table authentication.user_roles to guest;
grant usage on all sequences in schema authentication to guest;

-- PlainUser
drop owned by plainuser;
drop role if exists plainuser;
create role plainuser;

grant usage
on schema entities, human, place, country, resource, language, authentication
to plainuser;

grant select
on all tables
   in schema entities, human, place, country,
             resource, language
to plainuser;

grant select, insert, update
on all tables in schema authentication
to plainuser;

grant usage on all sequences in schema authentication to plainuser;

