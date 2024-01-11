SET SERVEROUTPUT ON;

DECLARE
    TYPE dept_rec_type IS RECORD (
        DEPTNO NUMBER(3),
        DNAME VARCHAR2(16),
        LOC VARCHAR2(16)
    );
    
    TYPE dept_tab_type IS TABLE OF dept_rec_type;
    
    dept_table dept_tab_type;
BEGIN
    SELECT DEPTNO, DNAME, LOC
    BULK COLLECT INTO dept_table
    FROM DEPT;

    FOR i IN 1..dept_table.COUNT LOOP
        DBMS_OUTPUT.PUT_LINE('Department ' || dept_table(i).DEPTNO || ':');
        DBMS_OUTPUT.PUT_LINE('  Name: ' || dept_table(i).DNAME);
        DBMS_OUTPUT.PUT_LINE('  Location: ' || dept_table(i).LOC);
        DBMS_OUTPUT.PUT_LINE('');
    END LOOP;
END;
/
