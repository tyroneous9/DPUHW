/*  
Wesley Wu  
CSC 355 Section 501t  
Homework 4  
02/12/2023 
*/  

--tables 
drop table dept;
create table dept as 
select department_id, department_name, departments.location_id, city
from departments
left join locations
on departments.location_id = locations.location_id
where city in ('Seattle', 'Southlake') 

drop table sal_grade;
create table sal_grade (
    grade varchar(2) primary key,
    min number,
    max number
);

insert into sal_grade values('G1', 2000, 3000);
insert into sal_grade values('G2', 3001, 4000);
insert into sal_grade values('G3', 4001, 7000);
insert into sal_grade values('G4', 7001, 10000);
insert into sal_grade values('G5', 10001, 99999);

--#1
select employee_id, first_name, last_name, salary, department_name
from employees
inner join dept 
on employees.department_id = dept.department_id
and job_id in ('FI_ACCOUNT', 'ST_CLERK') 
and hire_date < add_months(sysdate, -60)
and commission_pct is null
order by city;

--#2
select *
from employees
left join sal_grade
on employees.salary between sal_grade.min and sal_grade.max
where salary between (
    select min
    from sal_grade
    where grade = 'G4' 
) and (
    select max
    from sal_grade
    where grade = 'G5' 
);

--#3
select *
from employees
where salary > (
    select salary
    from employees
    where phone_number = '590.423.4568'
);

--#4
select first_name, last_name, department_name
from employees
inner join (
    select department_id, department_name
    from departments
    where department_name in ('Finance', 'IT', 'Purchasing')
) dept
on employees.department_id = dept.department_id;

--#5
select *
from employees
inner join (
    select department_id, department_name
    from departments
    where department_name in ('Shipping', 'Sales')
) dept 
on employees.department_id = dept.department_id
left join sal_grade
on employees.salary between sal_grade.min and sal_grade.max
where salary between (
    select min
    from sal_grade
    where grade = 'G2' 
) and (
    select max
    from sal_grade
    where grade = 'G4' 
)
and salary > (
    select salary
    from employees
    where first_name = 'Kelly' and last_name = 'Chung'
)
and hire_date < (
    select hire_date
    from employees
    where first_name = 'Lindsey' and last_name = 'Smith'
);


--#6
select first_name, last_name, salary, hire_date
from employees
where department_id = (
    select department_id
    from employees
    where first_name = 'Payam' and last_name = 'Kaufling'
)
and salary > (
    select salary
    from employees
    where first_name = 'Hazel' and last_name = 'Philtanker'
)
and first_name not like 'J%' and first_name not like 'P%';



--PART II SET OPERATIONS
--#1
select cid, fname, lname, email
from customer
where extract(month from dob) between 4 and 6
union
select did, fname, lname, email
from director
where extract(month from dob) between 4 and 6;

--#2
select *
from employees
where salary between 8999 and 17001
minus
select employees.*
from employees
left join departments
on employees.department_id = departments.department_id
where department_name not in ('Executive', 'Finance');

--#3
select *
from employees
where salary between 8999 and 17001
union
select employees.*
from employees
left join departments
on employees.department_id = departments.department_id
where department_name in ('Executive', 'Finance');

--#4
select employee_id, first_name, last_name, salary
from employees
left join departments
on employees.department_id = departments.department_id
where department_name in ('Shipping', 'Sales')
intersect
select employee_id, first_name, last_name, salary
from employees
left join sal_grade
on employees.salary between sal_grade.min and sal_grade.max
where salary between (
    select min
    from sal_grade
    where grade = 'G2' 
) and (
    select max
    from sal_grade
    where grade = 'G4' 
)
intersect
select employee_id, first_name, last_name, salary 
from employees
where salary > (
    select salary
    from employees
    where first_name = 'Kelly' and last_name = 'Chung'
)
intersect
select employee_id, first_name, last_name, salary
from employees
where hire_date < (
    select hire_date
    from employees
    where first_name = 'Lindsey' and last_name = 'Smith'
);