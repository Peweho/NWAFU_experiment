create or replace procedure add_register(n1 registe.rpno%type,
                                         din doctor.dno%type)
is
num number;
new_id registe.rno%type;
begin
  select count(r.rno)+1 into num
  from registe r;
  
  new_id := concat('R', lpad(num, 3, '0'));
  
  insert into registe
  values(new_id,n1,din);
  commit;
end add_register;
/
