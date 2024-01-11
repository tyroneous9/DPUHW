
--DROP TABLE STUDENT;
--DROP TABLE COURSE;
--DROP TABLE ENROLLMENT;
--DROP TABLE FACULTY;

CREATE TABLE STUDENT(
    student_id VARCHAR(25) PRIMARY KEY,
    std_name VARCHAR(25),
    home_phone CHAR(12),
    total_credits NUMBER,
    gpa DEC(3,2),
    advisor_id VARCHAR(25),
    FOREIGN KEY(advisor_id) REFERENCES FACULTY(faculty_id)
);

CREATE TABLE COURSE(
    course# CHAR(12) PRIMARY KEY,
    credit_hours NUMBER,
    time NUMBER,
    location VARCHAR(25),
    faculty_id VARCHAR(25),
    FOREIGN KEY(faculty_id) REFERENCES FACULTY(faculty_id)
);

CREATE TABLE ENROLLMENT (
    student_id VARCHAR(25),
    course# CHAR(12),
    grade DEC(3,2),
    FOREIGN KEY(student_id) REFERENCES STUDENT(student_id),
    FOREIGN KEY(course#) REFERENCES COURSE(course#)
);

CREATE TABLE FACULTY (
    faculty_id VARCHAR(25) PRIMARY KEY,
    fac_name VARCHAR(25),
    office VARCHAR(25),
    salary DEC(20,2)
);


