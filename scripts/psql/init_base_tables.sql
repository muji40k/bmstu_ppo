\c humankind

drop schema if exists entities cascade;
create schema entities;

drop table if exists entities.human;
create table entities.human
(
    id            serial primary key,
    creation_date timestamptz not null default now(),
    source        text not null
);

drop table if exists entities.place;
create table entities.place
(
    id            serial primary key,
    creation_date timestamptz not null default now(),
    source        text not null
);

drop table if exists entities.resource;
create table entities.resource
(
    id            serial primary key,
    creation_date timestamptz not null default now(),
    source        text not null
);

drop table if exists entities.country;
create table entities.country
(
    id            serial primary key,
    creation_date timestamptz not null default now(),
    source        text not null
);

drop table if exists entities.language;
create table entities.language
(
    id            serial primary key,
    creation_date timestamptz not null default now(),
    source        text not null
);

