/*  
Wesley Wu  
CSC 355 Section 501t  
Homework 3  
01/31/2023 
*/  

--#1
select title, genreid, duration
from movie;

--#2 how to insert multiple?
select title, duration, fname, lname, g_description
from movie, director, genre;

create table genre(
    genreid char(2) not null primary key,
    g_description varchar(50)
);
insert into genre values ('RC', 'Romantic Comedy');
insert into genre values ('MU', 'Musical');
insert into genre values ('HR', 'Horror');
insert into genre values ('DR', 'Drama');
insert into genre values ('AC', 'Action');
insert into genre values ('DC', 'Documentary');
insert into genre values ('SM', 'Sport Movie');
insert into genre values ('CM', 'Comedy');
insert into genre values ('SF', 'SciFi');
insert into genre values ('AN', 'Animated');
alter table movie add constraint FK_MOVIE_GENRE foreign key(genreid) references genre(genreid);

--#3
select g_description, title
from genre, movie 
where title like '%enim%'
order by g_description, title;

--#4
select title, genreid, year, duration
from movie
where directorId = '000000001' and duration < '10:00'
order by year desc;

--#5
select g_description, count(movie.genreid) as num_movies
from genre
left join movie on genre.genreid = movie.genreid 
group by g_description
order by num_movies;

--#6
select cId, count(cId) as num_rentals, max(year) as most_recent_movie
from rental
left join movie on rental.mId = movie.mId
group by cId
having count(cId) > 15
order by cId;

--#7
select distinct fname, lname
from movie
left join director on movie.directorId = director.dId
where year between 1975 and 1980;

--#8 
select title, rented
from rental
inner join customer on rental.cId = customer.cId
inner join movie on rental.mId = movie.mId
where email = 'K.Kane_02@movie.com'
order by title;

--#9
select genreid, count(id) as num_rentals, max(year) as oldest_movie, max(duration) as longest_duration
from rental
inner join movie on rental.mId = movie.mId
where rented >= date '2022-11-02'
group by genreid;


