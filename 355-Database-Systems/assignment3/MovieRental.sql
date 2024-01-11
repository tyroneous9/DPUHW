DROP TABLE RENTAL;
DROP TABLE MOVIE;
DROP TABLE CUSTOMER;
DROP TABLE DIRECTOR;

CREATE TABLE DIRECTOR(
	dId CHAR(9) PRIMARY KEY CHECK (REGEXP_LIKE  (dId,'[0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9]')),
	fname VARCHAR(50) NOT NULL,
	lname VARCHAR(50) NOT NULL,
	dob DATE,
	email VARCHAR(50) check (email like '_%@_%._%'), 
	producerId INTEGER,
	UNIQUE(email) 
);
CREATE TABLE CUSTOMER(
	cId CHAR(9) PRIMARY KEY CHECK (REGEXP_LIKE  (cId,'[0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9]')),
	fname VARCHAR(50) NOT NULL,
	lname VARCHAR(50) NOT NULL,
	dob DATE,
	email VARCHAR(50) check (email like '_%@_%._%'),
	UNIQUE(email)
);

CREATE TABLE MOVIE(
	mId CHAR(16) PRIMARY KEY CHECK (REGEXP_LIKE  (mId,'[A-Z][A-Z][A-Z]-[0-9][0-9][0-9][0-9]-[A-Z][A-Z]-[0-9][0-9][0-9][0-9]')),
	title VARCHAR(255) NOT NULL,
	genreid CHAR(2) NOT NULL,
	duration CHAR(5) CHECK (REGEXP_LIKE  (duration,'[0-1][0-9]:[0-6][0-9]')),
	year number(4) CHECK (year >= 1950 ),
	directorId CHAR(9),
	CONSTRAINT FK_MOVIE_DIRECTOR FOREIGN KEY  (directorId) REFERENCES DIRECTOR(dId)
);

CREATE TABLE RENTAL(
  id NUMBER GENERATED ALWAYS as IDENTITY(START with 1 INCREMENT by 1), 
	mId  CHAR(16),
	cId CHAR(9),
	rented DATE,
	duedate DATE,
	PRIMARY KEY(id),
	CONSTRAINT FK_RENTAL_MOVIE FOREIGN KEY  (mId) REFERENCES MOVIE(mId),
	CONSTRAINT FK_RENTAL_CUSTOMER FOREIGN KEY  (cId) REFERENCES CUSTOMER(cId)
);


--DIRECTORS
INSERT INTO DIRECTOR (dId,fname,lname,dob,email,producerId)
VALUES ('000000001','Kimberley','Marshall','27-JAN-22','mollis@protonmail.net',3);
INSERT INTO DIRECTOR (dId,fname,lname,dob,email,producerId)
VALUES ('000000002','Myles','Bailey','28-FEB-37','nunc.risus@aol.edu',4);
INSERT INTO DIRECTOR (dId,fname,lname,dob,email,producerId)
VALUES ('000000003','Susan','Scott','18-OCT-21','urna.et.arcu@aol.org',2);
INSERT INTO DIRECTOR (dId,fname,lname,dob,email,producerId)
VALUES ('000000004','Cain','Burnett','14-JAN-81','eu.euismod.ac@google.net',3);
INSERT INTO DIRECTOR (dId,fname,lname,dob,email,producerId)
VALUES ('000000005','Mari','Austin','24-JAN-57','dui.nec.tempus@protonmail.couk',3);
INSERT INTO DIRECTOR (dId,fname,lname,dob,email,producerId)
VALUES ('000000006','Thomas','Sanders','09-AUG-36','sapien.aenean@protonmail.edu',1);
INSERT INTO DIRECTOR (dId,fname,lname,dob,email,producerId)
VALUES ('000000007','Reagan','Underwood','22-FEB-39','vitae.diam.proin@hotmail.ca',4);
INSERT INTO DIRECTOR (dId,fname,lname,dob,email,producerId)
VALUES ('000000008','Mary','Holder','12-JUL-39','leo.in@hotmail.couk',1);
INSERT INTO DIRECTOR (dId,fname,lname,dob,email,producerId)
VALUES ('000000009','Hamish','Heath','13-DEC-39','sed@icloud.org',3);
INSERT INTO DIRECTOR (dId,fname,lname,dob,email,producerId)
VALUES ('000000010','Sylvester','Mcintosh','21-DEC-88','metus.in.lorem@protonmail.edu',4);


UPDATE DIRECTOR SET email = substr(fname,1,1) || '.' || lname || '_' || substr(did,8,2) || '@movie.com';


-- CUSTOMERS
INSERT INTO CUSTOMER (cId,fname,lname,dob,email)
VALUES ('000000001','Norman','Justice','26-APR-53','libero.et.tristique@outlook.ca');
INSERT INTO CUSTOMER (cId,fname,lname,dob,email)
VALUES ('000000002','Kasimir','Kane','11-APR-98','mi@protonmail.org');
INSERT INTO CUSTOMER (cId,fname,lname,dob,email)
VALUES ('000000003','Jocelyn','Johnson','10-AUG-86','semper.nam@google.ca');
INSERT INTO CUSTOMER (cId,fname,lname,dob,email)
VALUES ('000000004','Wanda','Crane','28-NOV-92','nascetur@yahoo.org');
INSERT INTO CUSTOMER (cId,fname,lname,dob,email)
VALUES ('000000005','Velma','Fleming','13-APR-63','neque.et.nunc@icloud.org');
INSERT INTO CUSTOMER (cId,fname,lname,dob,email)
VALUES ('000000006','Logan','Buckley','08-DEC-88','maecenas@hotmail.com');
INSERT INTO CUSTOMER (cId,fname,lname,dob,email)
VALUES ('000000007','Jared','Mullins','04-AUG-59','nunc.sollicitudin.commodo@aol.ca');
INSERT INTO CUSTOMER (cId,fname,lname,dob,email)
VALUES ('000000008','Remedios','Bentley','20-APR-97','aliquam.adipiscing.lacus@aol.edu');
INSERT INTO CUSTOMER (cId,fname,lname,dob,email)
VALUES ('000000009','Kiara','Carrillo','27-DEC-83','nullam.lobortis@aol.org');
INSERT INTO CUSTOMER (cId,fname,lname,dob,email)
VALUES ('000000010','Rinah','Barnett','28-APR-04','tempus.mauris.erat@protonmail.ca');
INSERT INTO CUSTOMER (cId,fname,lname,dob,email)
VALUES ('000000011','Amity','Hickman','09-JUL-76','penatibus.et.magnis@google.ca');
INSERT INTO CUSTOMER (cId,fname,lname,dob,email)
VALUES ('000000012','Lewis','Foley','23-AUG-84','proin.ultrices@yahoo.ca');
INSERT INTO CUSTOMER (cId,fname,lname,dob,email)
VALUES ('000000013','Daphne','Duffy','02-AUG-58','interdum.enim@yahoo.com');
INSERT INTO CUSTOMER (cId,fname,lname,dob,email)
VALUES ('000000014','Omar','Hendrix','20-JAN-02','a@protonmail.couk');
INSERT INTO CUSTOMER (cId,fname,lname,dob,email)
VALUES ('000000015','Odysseus','Lindsey','14-APR-57','ipsum.sodales@outlook.edu');

UPDATE CUSTOMER SET email = substr(fname,1,1) || '.' || lname || '_' || substr(cid,8,2) || '@movie.com';


--MOVIES
INSERT INTO MOVIE (mId,title,genreid,duration,year,directorId)
VALUES ('ESP-2013-AC-0001','vel, faucibus id, libero.','AC','09:38',2013,'000000001');
INSERT INTO MOVIE (mId,title,genreid,duration,year,directorId)
VALUES ('KOR-1990-AC-0001','mi. Duis risus odio, auctor','AC','01:50',1990,'000000001');
INSERT INTO MOVIE (mId,title,genreid,duration,year,directorId)
VALUES ('CHN-2016-DR-0002','mollis. Duis sit','DR','16:20',2016,'000000001');
INSERT INTO MOVIE (mId,title,genreid,duration,year,directorId)
VALUES ('BRA-1998-DR-0002','at arcu. Vestibulum','DR','03:12',1998,'000000002');
INSERT INTO MOVIE (mId,title,genreid,duration,year,directorId)
VALUES ('ESP-1979-RC-0003','gravida nunc','RC','01:06',1979,'000000002');
INSERT INTO MOVIE (mId,title,genreid,duration,year,directorId)
VALUES ('KOR-1980-RC-0003','ut aliquam','RC','09:56',1980,'000000002');
INSERT INTO MOVIE (mId,title,genreid,duration,year,directorId)
VALUES ('KOR-1966-CM-0001','Nunc ut erat.','CM','02:01',1966,'000000003');
INSERT INTO MOVIE (mId,title,genreid,duration,year,directorId)
VALUES ('IND-1957-CM-0001','odio sagittis','CM','11:11',1957,'000000003');
INSERT INTO MOVIE (mId,title,genreid,duration,year,directorId)
VALUES ('KOR-1994-MU-0002','est ac','MU','13:29',1994,'000000003');
INSERT INTO MOVIE (mId,title,genreid,duration,year,directorId)
VALUES ('IND-1965-MU-0002','velit justo','MU','15:13',1965,'000000004');
INSERT INTO MOVIE (mId,title,genreid,duration,year,directorId)
VALUES ('IND-2006-HR-0003','dictum eu, eleifend','HR','16:33',2006,'000000004');
INSERT INTO MOVIE (mId,title,genreid,duration,year,directorId)
VALUES ('KOR-1987-HR-0003','scelerisque','HR','18:59',1987,'000000004');
INSERT INTO MOVIE (mId,title,genreid,duration,year,directorId)
VALUES ('USA-1968-DC-0001','at, egestas','DC','02:35',1968,'000000005');
INSERT INTO MOVIE (mId,title,genreid,duration,year,directorId)
VALUES ('CHN-1977-DC-0001','massa. Suspendisse','DC','01:10',1977,'000000005');
INSERT INTO MOVIE (mId,title,genreid,duration,year,directorId)
VALUES ('CAN-1996-SM-0002','libero. Morbi accumsan laoreet ipsum.','SM','14:22',1996,'000000005');
INSERT INTO MOVIE (mId,title,genreid,duration,year,directorId)
VALUES ('KOR-1971-SM-0002','Fusce mi lorem,','SM','01:21',1971,'000000006');
INSERT INTO MOVIE (mId,title,genreid,duration,year,directorId)
VALUES ('CAN-2018-AC-0003','bibendum. Donec','AC','18:02',2018,'000000006');
INSERT INTO MOVIE (mId,title,genreid,duration,year,directorId)
VALUES ('IND-2015-AC-0003','mi enim, condimentum eget,','AC','19:13',2015,'000000006');
INSERT INTO MOVIE (mId,title,genreid,duration,year,directorId)
VALUES ('USA-1994-DR-0001','vestibulum. Mauris magna. Duis dignissim','DR','01:47',1994,'000000007');
INSERT INTO MOVIE (mId,title,genreid,duration,year,directorId)
VALUES ('USA-1984-DR-0001','luctus vulputate, nisi sem semper','DR','14:00',1984,'000000007');
INSERT INTO MOVIE (mId,title,genreid,duration,year,directorId)
VALUES ('IND-1985-RC-0002','eget massa. Suspendisse eleifend.','RC','12:54',1985,'000000007');
INSERT INTO MOVIE (mId,title,genreid,duration,year,directorId)
VALUES ('CAN-2017-RC-0002','augue eu','RC','14:41',2017,'000000008');
INSERT INTO MOVIE (mId,title,genreid,duration,year,directorId)
VALUES ('IND-2018-CM-0003','sed turpis','CM','17:03',2018,'000000008');
INSERT INTO MOVIE (mId,title,genreid,duration,year,directorId)
VALUES ('ESP-1991-CM-0003','In condimentum.','CM','08:30',1991,'000000008');
INSERT INTO MOVIE (mId,title,genreid,duration,year,directorId)
VALUES ('USA-1971-MU-0001','Quisque imperdiet, erat','MU','17:19',1971,'000000009');
INSERT INTO MOVIE (mId,title,genreid,duration,year,directorId)
VALUES ('CHN-1988-MU-0001','Integer in','MU','01:25',1988,'000000009');
INSERT INTO MOVIE (mId,title,genreid,duration,year,directorId)
VALUES ('BRA-1981-HR-0002','risus, at fringilla','HR','02:42',1981,'000000009');
INSERT INTO MOVIE (mId,title,genreid,duration,year,directorId)
VALUES ('USA-1983-HR-0002','feugiat. Sed','HR','04:42',1983,'000000010');
INSERT INTO MOVIE (mId,title,genreid,duration,year,directorId)
VALUES ('CAN-2017-DC-0003','blandit enim consequat purus. Maecenas','DC','16:38',2017,'000000010');
INSERT INTO MOVIE (mId,title,genreid,duration,year,directorId)
VALUES ('CAN-1985-DC-0003','adipiscing elit. Aliquam','DC','18:53',1985,'000000010');
INSERT INTO MOVIE (mId,title,genreid,duration,year,directorId)
VALUES ('ESP-2005-SM-0001','facilisis facilisis,','SM','15:37',2005,'000000001');
INSERT INTO MOVIE (mId,title,genreid,duration,year,directorId)
VALUES ('USA-2016-SM-0001','aliquam arcu. Aliquam ultrices','SM','03:28',2016,'000000001');
INSERT INTO MOVIE (mId,title,genreid,duration,year,directorId)
VALUES ('BRA-1975-AC-0002','metus sit amet ante. Vivamus','AC','02:21',1975,'000000001');
INSERT INTO MOVIE (mId,title,genreid,duration,year,directorId)
VALUES ('IND-2013-AC-0002','Duis mi enim, condimentum eget,','AC','02:08',2013,'000000002');
INSERT INTO MOVIE (mId,title,genreid,duration,year,directorId)
VALUES ('CAN-1979-DR-0003','ornare. Fusce','DR','14:43',1979,'000000002');
INSERT INTO MOVIE (mId,title,genreid,duration,year,directorId)
VALUES ('CAN-1982-DR-0003','quis arcu vel quam','DR','05:13',1982,'000000002');
INSERT INTO MOVIE (mId,title,genreid,duration,year,directorId)
VALUES ('ESP-1963-RC-0001','dui nec','RC','05:59',1963,'000000003');
INSERT INTO MOVIE (mId,title,genreid,duration,year,directorId)
VALUES ('CHN-1994-RC-0001','lobortis quis, pede. Suspendisse dui.','RC','16:06',1994,'000000003');
INSERT INTO MOVIE (mId,title,genreid,duration,year,directorId)
VALUES ('KOR-1955-CM-0002','dignissim lacus. Aliquam rutrum','CM','08:34',1955,'000000003');
INSERT INTO MOVIE (mId,title,genreid,duration,year,directorId)
VALUES ('IND-1963-CM-0002','varius. Nam porttitor scelerisque','CM','09:38',1963,'000000004');


--RENTALS
INSERT INTO RENTAL (MID,CID,RENTED,DUEDATE) values ('BRA-1975-AC-0002','000000004',to_date('25-NOV-22','DD-MON-RR'),to_date('30-NOV-22','DD-MON-RR'));
INSERT INTO RENTAL (MID,CID,RENTED,DUEDATE) values ('BRA-1981-HR-0002','000000006',to_date('07-MAY-22','DD-MON-RR'),to_date('12-MAY-22','DD-MON-RR'));
INSERT INTO RENTAL (MID,CID,RENTED,DUEDATE) values ('BRA-1998-DR-0002','000000007',to_date('20-MAR-22','DD-MON-RR'),to_date('25-MAR-22','DD-MON-RR'));
INSERT INTO RENTAL (MID,CID,RENTED,DUEDATE) values ('ESP-1963-RC-0001','000000002',to_date('14-FEB-22','DD-MON-RR'),to_date('19-FEB-22','DD-MON-RR'));
INSERT INTO RENTAL (MID,CID,RENTED,DUEDATE) values ('ESP-1979-RC-0003','000000006',to_date('27-JUN-22','DD-MON-RR'),to_date('02-JUL-22','DD-MON-RR'));
INSERT INTO RENTAL (MID,CID,RENTED,DUEDATE) values ('ESP-1991-CM-0003','000000007',to_date('03-MAR-22','DD-MON-RR'),to_date('08-MAR-22','DD-MON-RR'));
INSERT INTO RENTAL (MID,CID,RENTED,DUEDATE) values ('ESP-2005-SM-0001','000000003',to_date('22-DEC-22','DD-MON-RR'),to_date('27-DEC-22','DD-MON-RR'));
INSERT INTO RENTAL (MID,CID,RENTED,DUEDATE) values ('ESP-2013-AC-0001','000000003',to_date('26-AUG-22','DD-MON-RR'),to_date('31-AUG-22','DD-MON-RR'));
INSERT INTO RENTAL (MID,CID,RENTED,DUEDATE) values ('BRA-1975-AC-0002','000000008',to_date('27-APR-22','DD-MON-RR'),to_date('02-MAY-22','DD-MON-RR'));
INSERT INTO RENTAL (MID,CID,RENTED,DUEDATE) values ('BRA-1981-HR-0002','000000006',to_date('02-NOV-22','DD-MON-RR'),to_date('07-NOV-22','DD-MON-RR'));
INSERT INTO RENTAL (MID,CID,RENTED,DUEDATE) values ('BRA-1998-DR-0002','000000008',to_date('23-OCT-22','DD-MON-RR'),to_date('28-OCT-22','DD-MON-RR'));
INSERT INTO RENTAL (MID,CID,RENTED,DUEDATE) values ('ESP-1963-RC-0001','000000008',to_date('06-JUL-22','DD-MON-RR'),to_date('11-JUL-22','DD-MON-RR'));
INSERT INTO RENTAL (MID,CID,RENTED,DUEDATE) values ('ESP-1979-RC-0003','000000002',to_date('15-JUN-22','DD-MON-RR'),to_date('20-JUN-22','DD-MON-RR'));
INSERT INTO RENTAL (MID,CID,RENTED,DUEDATE) values ('ESP-1991-CM-0003','000000009',to_date('12-OCT-22','DD-MON-RR'),to_date('17-OCT-22','DD-MON-RR'));
INSERT INTO RENTAL (MID,CID,RENTED,DUEDATE) values ('ESP-2005-SM-0001','000000004',to_date('31-MAY-22','DD-MON-RR'),to_date('05-JUN-22','DD-MON-RR'));
INSERT INTO RENTAL (MID,CID,RENTED,DUEDATE) values ('ESP-2013-AC-0001','000000001',to_date('25-APR-22','DD-MON-RR'),to_date('30-APR-22','DD-MON-RR'));
INSERT INTO RENTAL (MID,CID,RENTED,DUEDATE) values ('IND-1957-CM-0001','000000008',to_date('24-NOV-22','DD-MON-RR'),to_date('29-NOV-22','DD-MON-RR'));
INSERT INTO RENTAL (MID,CID,RENTED,DUEDATE) values ('IND-1963-CM-0002','000000006',to_date('05-SEP-22','DD-MON-RR'),to_date('10-SEP-22','DD-MON-RR'));
INSERT INTO RENTAL (MID,CID,RENTED,DUEDATE) values ('IND-1965-MU-0002','000000003',to_date('29-NOV-22','DD-MON-RR'),to_date('04-DEC-22','DD-MON-RR'));
INSERT INTO RENTAL (MID,CID,RENTED,DUEDATE) values ('IND-1985-RC-0002','000000005',to_date('04-MAY-22','DD-MON-RR'),to_date('09-MAY-22','DD-MON-RR'));
INSERT INTO RENTAL (MID,CID,RENTED,DUEDATE) values ('IND-2006-HR-0003','000000005',to_date('27-DEC-22','DD-MON-RR'),to_date('01-JAN-23','DD-MON-RR'));
INSERT INTO RENTAL (MID,CID,RENTED,DUEDATE) values ('IND-2013-AC-0002','000000007',to_date('17-MAY-22','DD-MON-RR'),to_date('22-MAY-22','DD-MON-RR'));
INSERT INTO RENTAL (MID,CID,RENTED,DUEDATE) values ('IND-2015-AC-0003','000000003',to_date('16-FEB-22','DD-MON-RR'),to_date('21-FEB-22','DD-MON-RR'));
INSERT INTO RENTAL (MID,CID,RENTED,DUEDATE) values ('IND-2018-CM-0003','000000008',to_date('31-JAN-22','DD-MON-RR'),to_date('05-FEB-22','DD-MON-RR'));
INSERT INTO RENTAL (MID,CID,RENTED,DUEDATE) values ('USA-1968-DC-0001','000000005',to_date('21-AUG-22','DD-MON-RR'),to_date('26-AUG-22','DD-MON-RR'));
INSERT INTO RENTAL (MID,CID,RENTED,DUEDATE) values ('USA-1971-MU-0001','000000006',to_date('21-NOV-22','DD-MON-RR'),to_date('26-NOV-22','DD-MON-RR'));
INSERT INTO RENTAL (MID,CID,RENTED,DUEDATE) values ('USA-1983-HR-0002','000000003',to_date('09-JUN-22','DD-MON-RR'),to_date('14-JUN-22','DD-MON-RR'));
INSERT INTO RENTAL (MID,CID,RENTED,DUEDATE) values ('USA-1984-DR-0001','000000004',to_date('25-JUL-22','DD-MON-RR'),to_date('30-JUL-22','DD-MON-RR'));
INSERT INTO RENTAL (MID,CID,RENTED,DUEDATE) values ('USA-1994-DR-0001','000000007',to_date('27-JUN-22','DD-MON-RR'),to_date('02-JUL-22','DD-MON-RR'));
INSERT INTO RENTAL (MID,CID,RENTED,DUEDATE) values ('USA-2016-SM-0001','000000001',to_date('27-DEC-22','DD-MON-RR'),to_date('01-JAN-23','DD-MON-RR'));
INSERT INTO RENTAL (MID,CID,RENTED,DUEDATE) values ('IND-1957-CM-0001','000000005',to_date('18-NOV-22','DD-MON-RR'),to_date('23-NOV-22','DD-MON-RR'));
INSERT INTO RENTAL (MID,CID,RENTED,DUEDATE) values ('IND-1963-CM-0002','000000007',to_date('12-AUG-22','DD-MON-RR'),to_date('17-AUG-22','DD-MON-RR'));
INSERT INTO RENTAL (MID,CID,RENTED,DUEDATE) values ('IND-1965-MU-0002','000000007',to_date('24-SEP-22','DD-MON-RR'),to_date('29-SEP-22','DD-MON-RR'));
INSERT INTO RENTAL (MID,CID,RENTED,DUEDATE) values ('IND-1985-RC-0002','000000003',to_date('22-AUG-22','DD-MON-RR'),to_date('27-AUG-22','DD-MON-RR'));
INSERT INTO RENTAL (MID,CID,RENTED,DUEDATE) values ('IND-2006-HR-0003','000000003',to_date('23-APR-22','DD-MON-RR'),to_date('28-APR-22','DD-MON-RR'));
INSERT INTO RENTAL (MID,CID,RENTED,DUEDATE) values ('IND-2013-AC-0002','000000002',to_date('19-SEP-22','DD-MON-RR'),to_date('24-SEP-22','DD-MON-RR'));
INSERT INTO RENTAL (MID,CID,RENTED,DUEDATE) values ('IND-2015-AC-0003','000000008',to_date('07-AUG-22','DD-MON-RR'),to_date('12-AUG-22','DD-MON-RR'));
INSERT INTO RENTAL (MID,CID,RENTED,DUEDATE) values ('IND-2018-CM-0003','000000008',to_date('24-DEC-22','DD-MON-RR'),to_date('29-DEC-22','DD-MON-RR'));
INSERT INTO RENTAL (MID,CID,RENTED,DUEDATE) values ('USA-1968-DC-0001','000000003',to_date('11-MAY-22','DD-MON-RR'),to_date('16-MAY-22','DD-MON-RR'));
INSERT INTO RENTAL (MID,CID,RENTED,DUEDATE) values ('USA-1971-MU-0001','000000005',to_date('12-MAY-22','DD-MON-RR'),to_date('17-MAY-22','DD-MON-RR'));
INSERT INTO RENTAL (MID,CID,RENTED,DUEDATE) values ('USA-1983-HR-0002','000000001',to_date('27-JUN-22','DD-MON-RR'),to_date('02-JUL-22','DD-MON-RR'));
INSERT INTO RENTAL (MID,CID,RENTED,DUEDATE) values ('USA-1984-DR-0001','000000005',to_date('07-JUN-22','DD-MON-RR'),to_date('12-JUN-22','DD-MON-RR'));
INSERT INTO RENTAL (MID,CID,RENTED,DUEDATE) values ('USA-1994-DR-0001','000000003',to_date('19-SEP-22','DD-MON-RR'),to_date('24-SEP-22','DD-MON-RR'));
INSERT INTO RENTAL (MID,CID,RENTED,DUEDATE) values ('USA-2016-SM-0001','000000003',to_date('01-JUN-22','DD-MON-RR'),to_date('06-JUN-22','DD-MON-RR'));
INSERT INTO RENTAL (MID,CID,RENTED,DUEDATE) values ('CHN-1977-DC-0001','000000007',to_date('08-JUN-22','DD-MON-RR'),to_date('13-JUN-22','DD-MON-RR'));
INSERT INTO RENTAL (MID,CID,RENTED,DUEDATE) values ('CHN-1988-MU-0001','000000005',to_date('10-MAY-22','DD-MON-RR'),to_date('15-MAY-22','DD-MON-RR'));
INSERT INTO RENTAL (MID,CID,RENTED,DUEDATE) values ('CHN-1994-RC-0001','000000004',to_date('24-OCT-22','DD-MON-RR'),to_date('29-OCT-22','DD-MON-RR'));
INSERT INTO RENTAL (MID,CID,RENTED,DUEDATE) values ('CHN-2016-DR-0002','000000002',to_date('31-OCT-22','DD-MON-RR'),to_date('05-NOV-22','DD-MON-RR'));
INSERT INTO RENTAL (MID,CID,RENTED,DUEDATE) values ('KOR-1955-CM-0002','000000004',to_date('29-DEC-22','DD-MON-RR'),to_date('03-JAN-23','DD-MON-RR'));
INSERT INTO RENTAL (MID,CID,RENTED,DUEDATE) values ('KOR-1966-CM-0001','000000002',to_date('05-AUG-22','DD-MON-RR'),to_date('10-AUG-22','DD-MON-RR'));
INSERT INTO RENTAL (MID,CID,RENTED,DUEDATE) values ('KOR-1971-SM-0002','000000007',to_date('04-FEB-22','DD-MON-RR'),to_date('09-FEB-22','DD-MON-RR'));
INSERT INTO RENTAL (MID,CID,RENTED,DUEDATE) values ('KOR-1980-RC-0003','000000004',to_date('07-SEP-22','DD-MON-RR'),to_date('12-SEP-22','DD-MON-RR'));
INSERT INTO RENTAL (MID,CID,RENTED,DUEDATE) values ('KOR-1987-HR-0003','000000008',to_date('22-JUL-22','DD-MON-RR'),to_date('27-JUL-22','DD-MON-RR'));
INSERT INTO RENTAL (MID,CID,RENTED,DUEDATE) values ('KOR-1990-AC-0001','000000003',to_date('28-JUL-22','DD-MON-RR'),to_date('02-AUG-22','DD-MON-RR'));
INSERT INTO RENTAL (MID,CID,RENTED,DUEDATE) values ('KOR-1994-MU-0002','000000004',to_date('12-MAR-22','DD-MON-RR'),to_date('17-MAR-22','DD-MON-RR'));
INSERT INTO RENTAL (MID,CID,RENTED,DUEDATE) values ('CAN-1979-DR-0003','000000003',to_date('01-APR-22','DD-MON-RR'),to_date('06-APR-22','DD-MON-RR'));
INSERT INTO RENTAL (MID,CID,RENTED,DUEDATE) values ('CAN-1982-DR-0003','000000002',to_date('07-AUG-22','DD-MON-RR'),to_date('12-AUG-22','DD-MON-RR'));
INSERT INTO RENTAL (MID,CID,RENTED,DUEDATE) values ('CAN-1985-DC-0003','000000007',to_date('11-APR-22','DD-MON-RR'),to_date('16-APR-22','DD-MON-RR'));
INSERT INTO RENTAL (MID,CID,RENTED,DUEDATE) values ('CAN-1996-SM-0002','000000005',to_date('10-FEB-22','DD-MON-RR'),to_date('15-FEB-22','DD-MON-RR'));
INSERT INTO RENTAL (MID,CID,RENTED,DUEDATE) values ('CAN-2017-DC-0003','000000002',to_date('28-JUL-22','DD-MON-RR'),to_date('02-AUG-22','DD-MON-RR'));
INSERT INTO RENTAL (MID,CID,RENTED,DUEDATE) values ('CAN-2017-RC-0002','000000009',to_date('26-APR-22','DD-MON-RR'),to_date('01-MAY-22','DD-MON-RR'));
INSERT INTO RENTAL (MID,CID,RENTED,DUEDATE) values ('CAN-2018-AC-0003','000000002',to_date('26-JUN-22','DD-MON-RR'),to_date('01-JUL-22','DD-MON-RR'));
INSERT INTO RENTAL (MID,CID,RENTED,DUEDATE) values ('CHN-1977-DC-0001','000000001',to_date('29-SEP-22','DD-MON-RR'),to_date('04-OCT-22','DD-MON-RR'));
INSERT INTO RENTAL (MID,CID,RENTED,DUEDATE) values ('CHN-1988-MU-0001','000000006',to_date('29-OCT-22','DD-MON-RR'),to_date('03-NOV-22','DD-MON-RR'));
INSERT INTO RENTAL (MID,CID,RENTED,DUEDATE) values ('CHN-1994-RC-0001','000000005',to_date('10-JAN-23','DD-MON-RR'),to_date('15-JAN-23','DD-MON-RR'));
INSERT INTO RENTAL (MID,CID,RENTED,DUEDATE) values ('CHN-2016-DR-0002','000000005',to_date('04-MAR-22','DD-MON-RR'),to_date('09-MAR-22','DD-MON-RR'));
INSERT INTO RENTAL (MID,CID,RENTED,DUEDATE) values ('CAN-1979-DR-0003','000000006',to_date('12-MAR-22','DD-MON-RR'),to_date('17-MAR-22','DD-MON-RR'));
INSERT INTO RENTAL (MID,CID,RENTED,DUEDATE) values ('CAN-1982-DR-0003','000000002',to_date('17-FEB-22','DD-MON-RR'),to_date('22-FEB-22','DD-MON-RR'));
INSERT INTO RENTAL (MID,CID,RENTED,DUEDATE) values ('CAN-1985-DC-0003','000000002',to_date('07-MAY-22','DD-MON-RR'),to_date('12-MAY-22','DD-MON-RR'));
INSERT INTO RENTAL (MID,CID,RENTED,DUEDATE) values ('CAN-1996-SM-0002','000000002',to_date('11-JUN-22','DD-MON-RR'),to_date('16-JUN-22','DD-MON-RR'));
INSERT INTO RENTAL (MID,CID,RENTED,DUEDATE) values ('CAN-2017-DC-0003','000000003',to_date('08-AUG-22','DD-MON-RR'),to_date('13-AUG-22','DD-MON-RR'));
INSERT INTO RENTAL (MID,CID,RENTED,DUEDATE) values ('CAN-2017-RC-0002','000000005',to_date('28-FEB-22','DD-MON-RR'),to_date('05-MAR-22','DD-MON-RR'));
INSERT INTO RENTAL (MID,CID,RENTED,DUEDATE) values ('CAN-2018-AC-0003','000000002',to_date('22-NOV-22','DD-MON-RR'),to_date('27-NOV-22','DD-MON-RR'));
INSERT INTO RENTAL (MID,CID,RENTED,DUEDATE) values ('USA-1968-DC-0001','000000005',to_date('13-MAR-22','DD-MON-RR'),to_date('18-MAR-22','DD-MON-RR'));
INSERT INTO RENTAL (MID,CID,RENTED,DUEDATE) values ('USA-1971-MU-0001','000000003',to_date('13-OCT-22','DD-MON-RR'),to_date('18-OCT-22','DD-MON-RR'));
INSERT INTO RENTAL (MID,CID,RENTED,DUEDATE) values ('USA-1983-HR-0002','000000007',to_date('08-SEP-22','DD-MON-RR'),to_date('13-SEP-22','DD-MON-RR'));
INSERT INTO RENTAL (MID,CID,RENTED,DUEDATE) values ('USA-1984-DR-0001','000000008',to_date('23-OCT-22','DD-MON-RR'),to_date('28-OCT-22','DD-MON-RR'));
INSERT INTO RENTAL (MID,CID,RENTED,DUEDATE) values ('USA-1994-DR-0001','000000001',to_date('11-MAY-22','DD-MON-RR'),to_date('16-MAY-22','DD-MON-RR'));
INSERT INTO RENTAL (MID,CID,RENTED,DUEDATE) values ('USA-2016-SM-0001','000000003',to_date('24-FEB-22','DD-MON-RR'),to_date('01-MAR-22','DD-MON-RR'));
INSERT INTO RENTAL (MID,CID,RENTED,DUEDATE) values ('BRA-1975-AC-0002','000000006',to_date('18-AUG-22','DD-MON-RR'),to_date('23-AUG-22','DD-MON-RR'));
INSERT INTO RENTAL (MID,CID,RENTED,DUEDATE) values ('BRA-1981-HR-0002','000000005',to_date('02-APR-22','DD-MON-RR'),to_date('07-APR-22','DD-MON-RR'));
INSERT INTO RENTAL (MID,CID,RENTED,DUEDATE) values ('BRA-1998-DR-0002','000000004',to_date('16-JAN-23','DD-MON-RR'),to_date('21-JAN-23','DD-MON-RR'));
INSERT INTO RENTAL (MID,CID,RENTED,DUEDATE) values ('ESP-1963-RC-0001','000000007',to_date('08-OCT-22','DD-MON-RR'),to_date('13-OCT-22','DD-MON-RR'));
INSERT INTO RENTAL (MID,CID,RENTED,DUEDATE) values ('ESP-1979-RC-0003','000000007',to_date('26-OCT-22','DD-MON-RR'),to_date('31-OCT-22','DD-MON-RR'));
INSERT INTO RENTAL (MID,CID,RENTED,DUEDATE) values ('ESP-1991-CM-0003','000000003',to_date('25-MAR-22','DD-MON-RR'),to_date('30-MAR-22','DD-MON-RR'));
INSERT INTO RENTAL (MID,CID,RENTED,DUEDATE) values ('ESP-2005-SM-0001','000000004',to_date('24-APR-22','DD-MON-RR'),to_date('29-APR-22','DD-MON-RR'));
INSERT INTO RENTAL (MID,CID,RENTED,DUEDATE) values ('ESP-2013-AC-0001','000000004',to_date('30-JUN-22','DD-MON-RR'),to_date('05-JUL-22','DD-MON-RR'));
INSERT INTO RENTAL (MID,CID,RENTED,DUEDATE) values ('BRA-1975-AC-0002','000000004',to_date('31-DEC-22','DD-MON-RR'),to_date('05-JAN-23','DD-MON-RR'));
INSERT INTO RENTAL (MID,CID,RENTED,DUEDATE) values ('BRA-1981-HR-0002','000000008',to_date('05-JUN-22','DD-MON-RR'),to_date('10-JUN-22','DD-MON-RR'));
INSERT INTO RENTAL (MID,CID,RENTED,DUEDATE) values ('BRA-1998-DR-0002','000000005',to_date('05-NOV-22','DD-MON-RR'),to_date('10-NOV-22','DD-MON-RR'));
INSERT INTO RENTAL (MID,CID,RENTED,DUEDATE) values ('ESP-1963-RC-0001','000000006',to_date('02-OCT-22','DD-MON-RR'),to_date('07-OCT-22','DD-MON-RR'));
INSERT INTO RENTAL (MID,CID,RENTED,DUEDATE) values ('ESP-1979-RC-0003','000000006',to_date('13-SEP-22','DD-MON-RR'),to_date('18-SEP-22','DD-MON-RR'));
INSERT INTO RENTAL (MID,CID,RENTED,DUEDATE) values ('ESP-1991-CM-0003','000000003',to_date('16-JUN-22','DD-MON-RR'),to_date('21-JUN-22','DD-MON-RR'));
INSERT INTO RENTAL (MID,CID,RENTED,DUEDATE) values ('ESP-2005-SM-0001','000000006',to_date('02-FEB-22','DD-MON-RR'),to_date('07-FEB-22','DD-MON-RR'));
INSERT INTO RENTAL (MID,CID,RENTED,DUEDATE) values ('ESP-2013-AC-0001','000000007',to_date('11-MAY-22','DD-MON-RR'),to_date('16-MAY-22','DD-MON-RR'));
INSERT INTO RENTAL (MID,CID,RENTED,DUEDATE) values ('IND-1957-CM-0001','000000004',to_date('06-JUN-22','DD-MON-RR'),to_date('11-JUN-22','DD-MON-RR'));
INSERT INTO RENTAL (MID,CID,RENTED,DUEDATE) values ('IND-1963-CM-0002','000000005',to_date('20-JUL-22','DD-MON-RR'),to_date('25-JUL-22','DD-MON-RR'));
INSERT INTO RENTAL (MID,CID,RENTED,DUEDATE) values ('IND-1965-MU-0002','000000006',to_date('05-FEB-22','DD-MON-RR'),to_date('10-FEB-22','DD-MON-RR'));
INSERT INTO RENTAL (MID,CID,RENTED,DUEDATE) values ('IND-1985-RC-0002','000000007',to_date('04-NOV-22','DD-MON-RR'),to_date('09-NOV-22','DD-MON-RR'));
INSERT INTO RENTAL (MID,CID,RENTED,DUEDATE) values ('IND-2006-HR-0003','000000002',to_date('11-OCT-22','DD-MON-RR'),to_date('16-OCT-22','DD-MON-RR'));
INSERT INTO RENTAL (MID,CID,RENTED,DUEDATE) values ('IND-2013-AC-0002','000000001',to_date('25-FEB-22','DD-MON-RR'),to_date('02-MAR-22','DD-MON-RR'));
INSERT INTO RENTAL (MID,CID,RENTED,DUEDATE) values ('IND-2015-AC-0003','000000006',to_date('10-JUN-22','DD-MON-RR'),to_date('15-JUN-22','DD-MON-RR'));
INSERT INTO RENTAL (MID,CID,RENTED,DUEDATE) values ('IND-2018-CM-0003','000000008',to_date('08-DEC-22','DD-MON-RR'),to_date('13-DEC-22','DD-MON-RR'));
INSERT INTO RENTAL (MID,CID,RENTED,DUEDATE) values ('USA-1968-DC-0001','000000005',to_date('27-APR-22','DD-MON-RR'),to_date('02-MAY-22','DD-MON-RR'));
INSERT INTO RENTAL (MID,CID,RENTED,DUEDATE) values ('USA-1971-MU-0001','000000008',to_date('23-JUL-22','DD-MON-RR'),to_date('28-JUL-22','DD-MON-RR'));
INSERT INTO RENTAL (MID,CID,RENTED,DUEDATE) values ('USA-1983-HR-0002','000000008',to_date('02-MAR-22','DD-MON-RR'),to_date('07-MAR-22','DD-MON-RR'));
INSERT INTO RENTAL (MID,CID,RENTED,DUEDATE) values ('USA-1984-DR-0001','000000003',to_date('29-OCT-22','DD-MON-RR'),to_date('03-NOV-22','DD-MON-RR'));
INSERT INTO RENTAL (MID,CID,RENTED,DUEDATE) values ('USA-1994-DR-0001','000000007',to_date('23-MAR-22','DD-MON-RR'),to_date('28-MAR-22','DD-MON-RR'));
INSERT INTO RENTAL (MID,CID,RENTED,DUEDATE) values ('USA-2016-SM-0001','000000004',to_date('27-JAN-22','DD-MON-RR'),to_date('01-FEB-22','DD-MON-RR'));
INSERT INTO RENTAL (MID,CID,RENTED,DUEDATE) values ('USA-1968-DC-0001','000000009',to_date('11-JUL-22','DD-MON-RR'),to_date('16-JUL-22','DD-MON-RR'));
INSERT INTO RENTAL (MID,CID,RENTED,DUEDATE) values ('USA-1971-MU-0001','000000001',to_date('09-DEC-22','DD-MON-RR'),to_date('14-DEC-22','DD-MON-RR'));
INSERT INTO RENTAL (MID,CID,RENTED,DUEDATE) values ('USA-1983-HR-0002','000000008',to_date('05-MAY-22','DD-MON-RR'),to_date('10-MAY-22','DD-MON-RR'));
INSERT INTO RENTAL (MID,CID,RENTED,DUEDATE) values ('USA-1984-DR-0001','000000004',to_date('03-JAN-23','DD-MON-RR'),to_date('08-JAN-23','DD-MON-RR'));
INSERT INTO RENTAL (MID,CID,RENTED,DUEDATE) values ('USA-1994-DR-0001','000000007',to_date('20-NOV-22','DD-MON-RR'),to_date('25-NOV-22','DD-MON-RR'));
INSERT INTO RENTAL (MID,CID,RENTED,DUEDATE) values ('USA-2016-SM-0001','000000007',to_date('07-JUL-22','DD-MON-RR'),to_date('12-JUL-22','DD-MON-RR'));
INSERT INTO RENTAL (MID,CID,RENTED,DUEDATE) values ('CHN-1977-DC-0001','000000004',to_date('17-FEB-22','DD-MON-RR'),to_date('22-FEB-22','DD-MON-RR'));
INSERT INTO RENTAL (MID,CID,RENTED,DUEDATE) values ('CHN-1988-MU-0001','000000005',to_date('25-DEC-22','DD-MON-RR'),to_date('30-DEC-22','DD-MON-RR'));
INSERT INTO RENTAL (MID,CID,RENTED,DUEDATE) values ('CHN-1994-RC-0001','000000008',to_date('10-AUG-22','DD-MON-RR'),to_date('15-AUG-22','DD-MON-RR'));
INSERT INTO RENTAL (MID,CID,RENTED,DUEDATE) values ('CHN-2016-DR-0002','000000005',to_date('01-JAN-23','DD-MON-RR'),to_date('06-JAN-23','DD-MON-RR'));
INSERT INTO RENTAL (MID,CID,RENTED,DUEDATE) values ('KOR-1955-CM-0002','000000002',to_date('15-NOV-22','DD-MON-RR'),to_date('20-NOV-22','DD-MON-RR'));
INSERT INTO RENTAL (MID,CID,RENTED,DUEDATE) values ('KOR-1966-CM-0001','000000002',to_date('14-JUL-22','DD-MON-RR'),to_date('19-JUL-22','DD-MON-RR'));
INSERT INTO RENTAL (MID,CID,RENTED,DUEDATE) values ('KOR-1971-SM-0002','000000008',to_date('16-JAN-23','DD-MON-RR'),to_date('21-JAN-23','DD-MON-RR'));
INSERT INTO RENTAL (MID,CID,RENTED,DUEDATE) values ('KOR-1980-RC-0003','000000009',to_date('22-NOV-22','DD-MON-RR'),to_date('27-NOV-22','DD-MON-RR'));
INSERT INTO RENTAL (MID,CID,RENTED,DUEDATE) values ('KOR-1987-HR-0003','000000005',to_date('07-FEB-22','DD-MON-RR'),to_date('12-FEB-22','DD-MON-RR'));
INSERT INTO RENTAL (MID,CID,RENTED,DUEDATE) values ('KOR-1990-AC-0001','000000005',to_date('04-JUN-22','DD-MON-RR'),to_date('09-JUN-22','DD-MON-RR'));
INSERT INTO RENTAL (MID,CID,RENTED,DUEDATE) values ('KOR-1994-MU-0002','000000005',to_date('19-APR-22','DD-MON-RR'),to_date('24-APR-22','DD-MON-RR'));
INSERT INTO RENTAL (MID,CID,RENTED,DUEDATE) values ('CAN-1979-DR-0003','000000004',to_date('11-JAN-23','DD-MON-RR'),to_date('16-JAN-23','DD-MON-RR'));
INSERT INTO RENTAL (MID,CID,RENTED,DUEDATE) values ('CAN-1982-DR-0003','000000001',to_date('12-SEP-22','DD-MON-RR'),to_date('17-SEP-22','DD-MON-RR'));
INSERT INTO RENTAL (MID,CID,RENTED,DUEDATE) values ('CAN-1985-DC-0003','000000009',to_date('16-SEP-22','DD-MON-RR'),to_date('21-SEP-22','DD-MON-RR'));
INSERT INTO RENTAL (MID,CID,RENTED,DUEDATE) values ('CAN-1996-SM-0002','000000007',to_date('02-JUN-22','DD-MON-RR'),to_date('07-JUN-22','DD-MON-RR'));
INSERT INTO RENTAL (MID,CID,RENTED,DUEDATE) values ('CAN-2017-DC-0003','000000006',to_date('09-APR-22','DD-MON-RR'),to_date('14-APR-22','DD-MON-RR'));
INSERT INTO RENTAL (MID,CID,RENTED,DUEDATE) values ('CAN-2017-RC-0002','000000006',to_date('12-AUG-22','DD-MON-RR'),to_date('17-AUG-22','DD-MON-RR'));
INSERT INTO RENTAL (MID,CID,RENTED,DUEDATE) values ('CAN-2018-AC-0003','000000006',to_date('17-APR-22','DD-MON-RR'),to_date('22-APR-22','DD-MON-RR'));


COMMIT;




