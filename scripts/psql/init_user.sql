\c humankind

drop schema if exists authentication cascade;
create schema authentication;

drop table if exists authentication.users;
create table authentication.users
(
    id       serial not null primary key,
    email    text not null,
    password text not null,
    name     text not null
);

drop table if exists authentication.user_roles;
create table authentication.user_roles
(
    id      serial not null primary key,
    user_id serial not null,
    role    text not null
);

drop table if exists authentication.user_human;
create table authentication.user_human
(
    id       serial not null primary key,
    user_id  serial not null,
    human_id integer default null
);

drop table if exists authentication.merge_requests;
create table authentication.merge_requests
(
    id       serial not null primary key,
    user_id  serial not null,
    human_id serial not null,
    state    text not null
);

alter table humankind.authentication.users add
    constraint "unique_user_email"
    unique (email);
alter table humankind.authentication.users add
    constraint "not_empty_user_general"
    check (password != '' and name != '');
alter table humankind.authentication.users add
    constraint "correct_user_email"
    check (email ~ '.*@.*\..*');

alter table humankind.authentication.user_roles add
    constraint "fkey_user_role_user_id"
    foreign key (user_id)
    references humankind.authentication.users(id) on delete cascade;
alter table humankind.authentication.user_roles add
    constraint "unique_user_role"
    unique (user_id, role);
alter table humankind.authentication.user_roles add
    constraint "not_empty_role_user_role"
    check (role != '');

alter table humankind.authentication.user_human add
    constraint "fkey_user_human_user_id"
    foreign key (user_id)
    references humankind.authentication.users(id) on delete cascade;
alter table humankind.authentication.user_human add
    constraint "fkey_user_human_human_id"
    foreign key (human_id)
    references humankind.entities.human(id);
alter table humankind.authentication.user_human add
    constraint "unique_user_human"
    unique (user_id);

alter table humankind.authentication.merge_requests add
    constraint "fkey_merge_request_user_id"
    foreign key (user_id)
    references humankind.authentication.users(id);
alter table humankind.authentication.merge_requests add
    constraint "fkey_merge_request_human_id"
    foreign key (human_id)
    references humankind.entities.human(id);
alter table humankind.authentication.merge_requests add
    constraint "unique_merge_request"
    unique (user_id, human_id, state);
alter table humankind.authentication.merge_requests add
    constraint "not_empty_state_merge_request"
    check (state != '');

