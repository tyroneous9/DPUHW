SET SERVEROUTPUT ON;

ACCEPT n_input NUMBER PROMPT 'Enter an integer number N: ';

DECLARE
  v_n NUMBER := &n_input;
BEGIN
  IF v_n IS NULL THEN
    v_n := 0;
  END IF;

  FOR i IN 1..v_n LOOP
    IF MOD(i, 2) = 0 THEN
      DBMS_OUTPUT.PUT_LINE(i || ' is even');
    ELSE
      DBMS_OUTPUT.PUT_LINE(i || ' is odd');
    END IF;
  END LOOP;
END;
/
