\c humankind

drop schema if exists place cascade;
create schema place;

drop table if exists place.general;
create table place.general
(
    id                serial not null primary key,
    place_id          serial not null,
    deleted           bool not null default false,

    name              text not null,
    type              text not null,
    area              float8 not null,
    continent         text not null,
    valid_from        timestamptz not null,

    modification_date timestamptz not null default now(),
    source            text not null
);

drop table if exists place.resource;
create table place.resource
(
    id                serial not null primary key,
    place_id          serial not null,
    deleted           bool not null default false,

    resource_id       serial not null,
    volume            float8 not null,
    valid_from        timestamptz not null,

    modification_date timestamptz not null default now(),
    source            text not null
);

drop table if exists place.country;
create table place.country
(
    id                serial not null primary key,
    place_id          serial not null,
    deleted           bool not null default false,

    country_id        serial not null,
    valid_from        timestamptz not null,

    modification_date timestamptz not null default now(),
    source            text not null
);

alter table humankind.place.general add
    constraint "fkey_place_general_place_id"
    foreign key (place_id)
    references humankind.entities.place(id);
alter table humankind.place.general add
    constraint "unique_place_general_modification_record"
    unique (place_id, modification_date);
alter table humankind.place.general add
    constraint "not_empty_place_general"
    check (name != '' and type != '' and continent != '');
alter table humankind.place.general add
    constraint "not_negative_area_place_general"
    check (area > 0);

alter table humankind.place.resource add
    constraint "fkey_place_resource_place_id"
    foreign key (place_id)
    references humankind.entities.place(id);
alter table humankind.place.resource add
    constraint "fkey_place_resource_resource_id"
    foreign key (resource_id)
    references humankind.entities.resource(id);
alter table humankind.place.resource add
    constraint "unique_place_resource_modification_record"
    unique (place_id, modification_date);
alter table humankind.place.resource add
    constraint "not_negative_place_resource_volume"
    check (volume > 0);

alter table humankind.place.country add
    constraint "fkey_place_country_place_id"
    foreign key (place_id)
    references humankind.entities.place(id);
alter table humankind.place.country add
    constraint "fkey_place_country_country_id"
    foreign key (country_id)
    references humankind.entities.country(id);
alter table humankind.place.country add
    constraint "unique_place_country_modification_record"
    unique (place_id, modification_date);

