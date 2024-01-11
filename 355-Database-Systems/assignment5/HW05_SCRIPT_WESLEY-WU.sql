/*  
Wesley Wu  
CSC 355 Section 501t  
Homework 5  
02/26/2023 
*/  

SET SERVEROUTPUT ON;
-- #1
declare
    tax_max number;
    tax_rate number;
    tax_withheld number;
    total_withheld number := 0;
begin
    select MaxAmount into tax_max from taxvalues;
    select TaxRate into tax_rate from taxvalues;
    dbms_output.put_line('max: ' || tax_max);
    dbms_output.put_line('rate: ' || tax_rate);
    for worker in (select wid, wsalary from c_worker) loop
    tax_withheld := worker.wsalary*tax_rate;
    if tax_withheld >= tax_max then
        tax_withheld := tax_max;
        total_withheld := total_withheld+tax_withheld;
        dbms_output.put_line(worker.wid || ': ' || worker.wsalary || ' ' || tax_withheld || ' ' || (worker.wsalary-tax_withheld) || ' +');
    else
        total_withheld := total_withheld+tax_withheld;
        dbms_output.put_line(worker.wid || ': ' || worker.wsalary || ' ' || tax_withheld || ' ' || (worker.wsalary-tax_withheld));
    end if; 
    end loop;
    dbms_output.put_line('Total tax withheld: ' || total_withheld);
end;

-- #2
create or replace trigger NewTaxByWuWesley
after update of wsalary on c_worker
for each row
when(new.wsalary*0.13 < 10000)
declare
    tax_max number;
    tax_rate number;
    new_tax number;
    old_tax number;
begin   
    select MaxAmount into tax_max from taxvalues;
    select TaxRate into tax_rate from taxvalues;
    new_tax := :new.wsalary*tax_rate;
    old_tax := :old.wsalary*tax_rate;
    insert into t_audit values (:old.wid, :old.wsalary, :new.wsalary, old_tax, new_tax, sysdate);
    dbms_output.put_line(:old.wid || ' ' || :old.wsalary || ' ' || old_tax || ' ' || :new.wsalary || ' ' || new_tax || ' ' || (new_tax-old_tax));
end;
/

UPDATE C_WORKER SET WSalary = 1.1 * WSalary;
select * from t_audit;