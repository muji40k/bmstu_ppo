\c humankind

drop schema if exists country cascade;
create schema country;

drop table if exists country.general;
create table country.general
(
    id                serial not null primary key,
    country_id        serial not null,
    deleted           bool not null default false,

    name              text not null,
    type              text not null,
    gdp               float8 not null,
    valid_from        timestamptz not null,

    modification_date timestamptz not null default now(),
    source            text not null
);

alter table humankind.country.general add
    constraint "fkey_country_general_country_id"
    foreign key (country_id)
    references humankind.entities.country(id);
alter table humankind.country.general add
    constraint "unique_country_general_modification_record"
    unique (country_id, modification_date);
alter table humankind.country.general add
    constraint "not_empty_country_general"
    check (name != '' and type != '');
alter table humankind.country.general add
    constraint "not_negative_country_general_gdp"
    check (gdp > 0);

