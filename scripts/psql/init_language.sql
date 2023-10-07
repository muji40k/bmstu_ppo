\c humankind

drop schema if exists language cascade;
create schema language;

drop table if exists language.general;
create table language.general
(
    id                serial not null primary key,
    language_id       serial not null,
    deleted           bool not null default false,

    name              text not null,
    family            text not null,
    valid_from        timestamptz not null,

    modification_date timestamptz not null default now(),
    source            text not null
);

alter table humankind.language.general add
    constraint "fkey_language_general_language_id"
    foreign key (language_id)
    references humankind.entities.language(id);
alter table humankind.language.general add
    constraint "unique_language_general_modification_record"
    unique (language_id, modification_date);
alter table humankind.language.general add
    constraint "not_empty_language_general"
    check (name != '' and family != '');

