\c postgres

drop database if exists humankind;
create database humankind;

-- \i scripts/psql/init_base_tables.sql
-- \i scripts/psql/init_human.sql
-- \i scripts/psql/init_place.sql
-- \i scripts/psql/init_country.sql
-- \i scripts/psql/init_resource.sql
-- \i scripts/psql/init_language.sql
--  
-- \i scripts/psql/init_user.sql
--  
-- \i scripts/psql/init_roles.sql

\i /home/pg/labfs/course_proj/src/scripts/psql/init_base_tables.sql
\i /home/pg/labfs/course_proj/src/scripts/psql/init_human.sql
\i /home/pg/labfs/course_proj/src/scripts/psql/init_place.sql
\i /home/pg/labfs/course_proj/src/scripts/psql/init_country.sql
\i /home/pg/labfs/course_proj/src/scripts/psql/init_resource.sql
\i /home/pg/labfs/course_proj/src/scripts/psql/init_language.sql

\i /home/pg/labfs/course_proj/src/scripts/psql/init_user.sql

\i /home/pg/labfs/course_proj/src/scripts/psql/init_roles.sql

