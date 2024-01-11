DROP TABLE StudentsCopy;
DROP TABLE StudentsCopyLName_B;
DROP TABLE StudentsCopyNoData_V1;
DROP TABLE StudentsCopyNoData_V2;
DROP TABLE StudentsEmailList;
DROP TABLE StudentsDiffColNames;
DROP TABLE StudentsPK;




/*
A table can be created from an existing table in the database 
using a sub query option.

The table is created with specified column names, and rows retrieved 
by the select statement are inserted into the table.

If the table column specification is not given, 
table is created  with the same column as given in sub query

The column data type definitions including the explicitly 
imposed NOT NULL constraints are copied into the new table. 
No other constraints, including PKs, are copied unless indicated.

*/
CREATE TABLE StudentsCopy
AS
SELECT * FROM Students;


/*
Data can be copied all or based on conditions.
The one above copied all because there were no conditions.
*/
CREATE TABLE StudentsCopyLName_B
AS
SELECT * FROM Students 
WHERE LNAME LIKE 'B%';

/*
Copying only the structure
No DATA, use rownum < 1  condition or any condition that returns false.
*/

CREATE TABLE StudentsCopyNoData_V1
AS
SELECT * FROM Students WHERE 1 = 0; --<-- condition is not true

CREATE TABLE StudentsCopyNoData_V2
AS
SELECT * FROM Students WHERE 1=2; --<-- condition is not true


/*
Select the individual columns instead of select *
*/

CREATE TABLE StudentsEmailList
AS
SELECT s_id, fname, lname, email FROM Students;

/*
Use the same datatype as the source table but new column name 
in new the table
*/
CREATE TABLE StudentsDiffColNames (id, first, last, e_address)
AS
SELECT s_id, fname, lname, email FROM Students;
-- another way to do it
CREATE TABLE StudentsDiffColNamesv2 
AS
SELECT s_id id, fname first, lname last, email eaddress FROM Students;
/*
Defining the primary and unique key.
The CREATE TABLE AS only copy columns, data types and Explicit NOT NULLS
*/
CREATE TABLE StudentsPK(id PRIMARY KEY, first, last, e_address UNIQUE)
AS
SELECT s_id, fname, lname, email FROM Students;
desc STUDENTSPK
/*
The CREATE TABLE AS only copy columns, 
data types and Explicit NOT NULLS.
*/

CREATE TABLE DepartmentFullAddress
(did PRIMARY KEY, dname, daddress, dzip, dcity, dstate, dcountry, dregion)
AS (
    SELECT d.department_id , d.department_name , l.street_address , 
        l.postal_code , l.city , l.state_province , c.country_name ,
        r.region_name 
    FROM
        departments d, locations l, countries c, regions r
    WHERE   d.location_id = l.location_id 
      AND   l.country_id = c.country_id
      AND   c.region_id = r.region_id
      AND   1=0
      ); --< not true condition to copy only structure




/*** INSERT USING SUBQUERIES ****/

select * from StudentsCopyNoData_V2;

-- all columns from source subquery
INSERT INTO StudentsCopyNoData_V1
SELECT * FROM Students;

-- some columns from source subquery (a join)
INSERT INTO DepartmentFullAddress
SELECT  
d.department_id ,
d.department_name ,
l.street_address ,
l.postal_code ,
l.city ,
l.state_province ,
c.country_name ,
r.region_name 
FROM
departments d, locations l, countries c, regions r
WHERE d.location_id = l.location_id 
AND   l.country_id = c.country_id
AND   c.region_id = r.region_id
AND l.state_province = 'Washington';

/*** UPDATES WITH SUBQUERY ***/

UPDATE StudentsCopy sc
SET    email = (SELECT fname || '.' || lname || '@uni.edu'
                FROM Students s
                WHERE s.s_id= sc.s_id)
WHERE program_id =(SELECT program_id
                    FROM StudentsCopy
                    WHERE s_id = '0000001');


/*** DELETE WITH SUBQUERY ***/
DELETE FROM StudentsCopy
  WHERE program_id IN
                  ( SELECT p_id
                    FROM programs
                    WHERE p_name LIKE '%Software%');
                    

                    
                    

