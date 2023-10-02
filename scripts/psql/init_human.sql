\c humankind

drop schema if exists human cascade;
create schema human;

drop table if exists human.names;
create table human.names
(
    id                serial not null primary key,
    human_id          serial not null,
    deleted           bool not null default false,

    first_name        text not null,
    last_name         text not null,
    patronymic        text,
    valid_from        timestamptz not null,

    modification_date timestamptz not null default now(),
    source            text not null
);

drop table if exists human.birth_place;
create table human.birth_place
(
    id                serial not null primary key,
    human_id          serial not null,
    deleted           bool not null default false,

    place_id          serial not null,

    modification_date timestamptz not null default now(),
    source            text not null
);

drop table if exists human.address;
create table human.address
(
    id                serial not null primary key,
    human_id          serial not null,
    deleted           bool not null default false,

    place_id          serial not null,
    valid_from        timestamptz not null,

    modification_date timestamptz not null default now(),
    source            text not null
);

drop table if exists human.dates;
create table human.dates
(
    id                serial not null primary key,
    human_id          serial not null,
    deleted           bool not null default false,

    birth             timestamptz not null,
    death             timestamptz,
    valid_from        timestamptz not null,

    modification_date timestamptz not null default now(),
    source            text not null
);

drop table if exists human.social;
create table human.social
(
    id                serial not null primary key,
    human_id          serial not null,
    deleted           bool not null default false,

    religion          text,
    wealth            text,
    literacy          text,
    busyness          text,
    valid_from        timestamptz not null,

    modification_date timestamptz not null default now(),
    source            text not null
);

drop table if exists human.general;
create table human.general
(
    id                serial not null primary key,
    human_id          serial not null,
    deleted           bool not null default false,

    blood_type        text not null,
    gender            text not null,
    race              text not null,
    valid_from        timestamptz not null,

    modification_date timestamptz not null default now(),
    source            text not null
);

drop table if exists human.language;
create table human.language
(
    id                serial not null primary key,
    human_id          serial not null,
    deleted           bool not null default false,

    language_id       serial not null,
    level             text not null,
    valid_from        timestamptz not null,

    modification_date timestamptz not null default now(),
    source            text not null
);

alter table humankind.human.names add
    constraint "fkey_human_names_human_id"
    foreign key (human_id)
    references humankind.entities.human(id);
alter table humankind.human.names add
    constraint "unique_human_names_modification_record"
    unique (human_id, modification_date);
alter table humankind.human.names add
    constraint "not_empty_human_names"
    check (first_name != '' and last_name != ''
           and (patronymic is null or patronymic != ''));

alter table humankind.human.birth_place add
    constraint "fkey_human_birth_place_human_id"
    foreign key (human_id)
    references humankind.entities.human(id);
alter table humankind.human.birth_place add
    constraint "fkey_human_birth_place_place_id"
    foreign key (place_id)
    references humankind.entities.place(id);
alter table humankind.human.birth_place add
    constraint "unique_human_birth_place_modification_record"
    unique (human_id, modification_date);

alter table humankind.human.address add
    constraint "fkey_human_address_human_id"
    foreign key (human_id)
    references humankind.entities.human(id);
alter table humankind.human.address add
    constraint "fkey_human_address_place_id"
    foreign key (place_id)
    references humankind.entities.place(id);
alter table humankind.human.address add
    constraint "unique_human_address_modification_record"
    unique (human_id, modification_date);

alter table humankind.human.dates add
    constraint "fkey_human_dates_human_id"
    foreign key (human_id)
    references humankind.entities.human(id);
alter table humankind.human.dates add
    constraint "unique_human_dates_modification_record"
    unique (human_id, modification_date);
alter table humankind.human.dates add
    constraint "birth_death_sequene_human_dates"
    check (death is null or birth < death);

alter table humankind.human.social add
    constraint "fkey_human_social_human_id"
    foreign key (human_id)
    references humankind.entities.human(id);
alter table humankind.human.social add
    constraint "unique_human_social_modification_record"
    unique (human_id, modification_date);
alter table humankind.human.social add
    constraint "not_empty_human_social"
    check ((religion is null or religion != '')
           and (wealth is null or wealth != '')
           and (literacy is null or literacy != '')
           and (literacy is null or literacy != ''));

alter table humankind.human.general add
    constraint "fkey_human_general_human_id"
    foreign key (human_id)
    references humankind.entities.human(id);
alter table humankind.human.general add
    constraint "unique_human_general_modification_record"
    unique (human_id, modification_date);
alter table humankind.human.general add
    constraint "not_empty_human_general"
    check (blood_type != '' and gender != '' and race != '');

alter table humankind.human.language add
    constraint "fkey_human_language_human_id"
    foreign key (human_id)
    references humankind.entities.human(id);
alter table humankind.human.language add
    constraint "fkey_human_language_language_id"
    foreign key (language_id)
    references humankind.entities.language(id);
alter table humankind.human.language add
    constraint "unique_human_language_modification_record"
    unique (human_id, language_id, modification_date);
alter table humankind.human.language add
    constraint "not_empty_human_language"
    check (level != '');

