SET SERVEROUTPUT ON;

ACCEPT old_salary NUMBER PROMPT 'Enter the current salary: ';
ACCEPT raise_percentage NUMBER PROMPT 'Enter the raise percentage: ';

DECLARE
  v_old_salary NUMBER := &old_salary;
  v_raise_percentage NUMBER := &raise_percentage;
  v_new_salary NUMBER;
BEGIN
  IF v_old_salary IS NULL THEN
    v_old_salary := 0;
  END IF;

  IF v_raise_percentage IS NULL THEN
    v_raise_percentage := 0;
  END IF;

  v_new_salary := v_old_salary * (1 + v_raise_percentage / 100);

  DBMS_OUTPUT.PUT_LINE('New Salary: ' || v_new_salary);
END;
/
