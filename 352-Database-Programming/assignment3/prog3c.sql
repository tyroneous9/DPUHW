DECLARE
  old_zip ZIPCODES.ZIP%TYPE := '67226';
  new_zip ZIPCODES.ZIP%TYPE := '12345';
  city_name VARCHAR2(50);
  found_old BOOLEAN := FALSE;

BEGIN
  SELECT CITY INTO city_name FROM ZIPCODES WHERE ZIP = old_zip;
  found_old := TRUE;
  EXCEPTION
    WHEN NO_DATA_FOUND THEN
      DBMS_OUTPUT.PUT_LINE('Old zip' || old_zip || ' does not exist');
      RETURN;
  UPDATE ZIPCODES SET ZIP = new_zip WHERE ZIP = old_zip;
  UPDATE CUSTOMERS SET ZIP = new_zip WHERE ZIP = old_zip;
  UPDATE EMPLOYEE SET ZIP = new_zip WHERE ZIP = old_zip;
END;
/
