CREATE TABLE Employee (
    ENO NUMBER(4) PRIMARY KEY,
    ENAME VARCHAR2(50) NOT NULL,
    ZIP CHAR(5),
    HDATE DATE,
    FOREIGN KEY (ZIP) REFERENCES ZIPCODES (ZIP)
);

CREATE TABLE Customers (
    CNO NUMBER(4) PRIMARY KEY,
    CNAME VARCHAR2(50) NOT NULL,
    STREET VARCHAR2(50),
    ZIP CHAR(5),
    PHONE VARCHAR2(12),
    FOREIGN KEY (ZIP) REFERENCES ZIPCODES (ZIP)
);

CREATE TABLE ZIPCODES (
    ZIP CHAR(5) PRIMARY KEY,
    CITY VARCHAR2(50) NOT NULL
);
