CREATE OR REPLACE PROCEDURE parse_name(input_name IN VARCHAR2) IS
  v_first_name VARCHAR2(50);
  v_last_name VARCHAR2(50);
  v_title VARCHAR2(50);
BEGIN
  IF INSTR(input_name, ',') > 0 THEN
    v_last_name := TRIM(SUBSTR(input_name, 1, INSTR(input_name, ',') - 1));
    v_first_name := TRIM(SUBSTR(input_name, INSTR(input_name, ',') + 1, INSTR(input_name, ' ', INSTR(input_name, ',') + 1) - INSTR(input_name, ',') - 1));
    v_title := TRIM(SUBSTR(input_name, INSTR(input_name, ' ', INSTR(input_name, ',') + 1)));
  ELSE
    v_first_name := TRIM(SUBSTR(input_name, 1, INSTR(input_name, ' ') - 1));
    v_last_name := TRIM(SUBSTR(input_name, INSTR(input_name, ' ') + 1, INSTR(input_name, ' ', INSTR(input_name, ' ') + 1) - INSTR(input_name, ' ') - 1));
    v_title := TRIM(SUBSTR(input_name, INSTR(input_name, ' ', INSTR(input_name, ' ') + 1)));
  END IF;

  IF v_first_name IS NULL OR v_last_name IS NULL OR v_title IS NULL THEN
    RAISE_APPLICATION_ERROR(-20001, 'Invalid input name string. Name components missing.');
  END IF;

  DBMS_OUTPUT.PUT_LINE(v_title || ' ' || UPPER(v_first_name) || ' ' || UPPER(v_last_name));
EXCEPTION
  WHEN OTHERS THEN
    DBMS_OUTPUT.PUT_LINE('An error occurred: ' || SQLERRM);
END;
/

DECLARE
  name_input VARCHAR2(100);
BEGIN
  parse_name('&input_name');
END;
/