\c humankind

drop schema if exists resource cascade;
create schema resource;

drop table if exists resource.general;
create table resource.general
(
    id                serial not null primary key,
    resource_id       serial not null,
    deleted           bool not null default false,

    name              text not null,
    type              text not null,
    value             float8 not null,
    rarity            text not null,
    valid_from        timestamptz not null,

    modification_date timestamptz not null default now(),
    source            text not null
);

alter table humankind.resource.general add
    constraint "fkey_resource_general_resource_id"
    foreign key (resource_id)
    references humankind.entities.resource(id);
alter table humankind.resource.general add
    constraint "unique_resource_general_modification_record"
    unique (resource_id, modification_date);
alter table humankind.resource.general add
    constraint "not_empty_place_general"
    check (name != '' and type != '' and rarity != '');
alter table humankind.resource.general add
    constraint "not_negative_place_resource_value"
    check (value > 0);

