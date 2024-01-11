CREATE TABLE dept (
  DEPTNO NUMBER(3) PRIMARY KEY,
  DNAME VARCHAR2(16),
  LOC VARCHAR2(16)
);

CREATE TABLE dept_shadow (
  DEPTNO NUMBER(3) PRIMARY KEY,
  DNAME VARCHAR2(16),
  LOC VARCHAR2(16),
  "USER" VARCHAR2(32),
  MODTIME CHAR(17)
);

CREATE OR REPLACE TRIGGER dept_insert_trigger
AFTER INSERT ON dept
FOR EACH ROW
BEGIN
  INSERT INTO dept_shadow (DEPTNO, DNAME, LOC, "USER", MODTIME)
  VALUES (:NEW.DEPTNO, :NEW.DNAME, :NEW.LOC, USER, TO_CHAR(SYSDATE, 'MM/DD/YY HH:MI:SS'));
END;
/
