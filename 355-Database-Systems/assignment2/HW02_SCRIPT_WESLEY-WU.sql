/*
Wesley Wu
CSC 355 Section 501T
Assignment 2
01/23/2023
*/

DROP TABLE RENTAL;
DROP TABLE MOVIE;
DROP TABLE DIRECTOR;
DROP TABLE CUSTOMER;


CREATE TABLE DIRECTOR(
    dId VARCHAR(9) PRIMARY KEY,
    d_fname VARCHAR(50),
    d_lname VARCHAR(50),
    d_dob DATE,
    d_email VARCHAR(50) check(d_email like '_%@%_'),
    producerId VARCHAR(3)
);

CREATE TABLE MOVIE(
    mId VARCHAR(16) check(mId like '___-____-__-____') PRIMARY KEY,
    title VARCHAR(50),
    genreid VARCHAR(2),
    duration VARCHAR(5) check(duration like '__:__'),
    year NUMBER(4) check(year >= 1950),
    dId VARCHAR(9) REFERENCES DIRECTOR(dId)
);

CREATE TABLE CUSTOMER(
    cId VARCHAR(9) PRIMARY KEY,
    c_fname VARCHAR(50),
    c_lname VARCHAR(50),
    c_dob DATE,
    c_email VARCHAR(50) check(c_email like '_%@%_')
);

CREATE TABLE RENTAL(
    mId VARCHAR(16),
    cId VARCHAR(9),
    rented DATE,
    duedate DATE,
    num_rentals NUMBER DEFAULT 0,
    FOREIGN KEY(mId) REFERENCES MOVIE(mId), 
    FOREIGN KEY(cId) REFERENCES CUSTOMER(cId)
);
--POPULATE TABLES
INSERT INTO DIRECTOR VALUES ('000000001', 'John', 'Doe', DATE '2023-01-20', 'johnd@gmail.com', '001');
INSERT INTO DIRECTOR VALUES ('000000002', 'Jane', 'Doe', DATE '2023-01-20', 'janed@gmail.com', '001');
INSERT INTO DIRECTOR VALUES ('000000003', 'Herman', 'Hermit', DATE '1995-01-20', 'hermanh@myspace.com', '002');

INSERT INTO CUSTOMER VALUES ('000000001', 'Harry', 'Pots', DATE '2000-12-12', 'harryp@gmail.com');
INSERT INTO CUSTOMER VALUES ('000000002', 'George', 'Washed', DATE '2001-12-23', 'georgew@gmail.com');
INSERT INTO CUSTOMER VALUES ('000000003', 'Mundane', 'Mann', DATE '2002-11-11', 'mundanem@gmail.com');

INSERT INTO MOVIE VALUES ('USA-2003-HR-0001', 'The Great Pencil', 'HR', '02:32', 2003, '000000001');
INSERT INTO MOVIE VALUES ('BRA-2001-CM-0001', 'No Interesting Title', 'CM', '04:06', 2001, '000000002');
INSERT INTO MOVIE VALUES ('CAN-1950-AD-0001', 'Beetle Adventures', 'AC', '33:12', 1950, '000000001');
INSERT INTO MOVIE VALUES ('USA-1999-AC-0001', 'Picnic of Doom', 'AC', '10:10', 1999, '000000003');

INSERT INTO RENTAL VALUES ('USA-2003-HR-0001', '000000001', DATE '2023-01-01', DATE '2023-12-30', 1);
INSERT INTO RENTAL VALUES ('BRA-2001-CM-0001', '000000002', DATE '2022-06-01', DATE '2023-09-30', 1);
INSERT INTO RENTAL VALUES ('CAN-1950-AD-0001', '000000003', DATE '2022-02-20', DATE '2022-03-25', 2);
INSERT INTO RENTAL VALUES ('CAN-1950-AD-0001', '000000001', DATE '2022-05-15', DATE '2022-05-20', 2);
INSERT INTO RENTAL VALUES ('USA-1999-AC-0001', '000000002', DATE '2022-01-10', DATE '2022-01-15', 1);

SELECT * FROM DIRECTOR;
SELECT * FROM CUSTOMER;
SELECT * FROM MOVIE;
SELECT * FROM RENTAL;
COMMIT;