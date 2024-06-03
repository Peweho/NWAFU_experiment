create or replace procedure add_ruku(n ruku.rmno%type,num ruku.rnum%type) 
is
id number;
info ruku%rowtype;
begin
  select count(r.rno)+1 into id from ruku r;
  info.rno := concat('R',lpad(id,3,'0'));
   
  insert into ruku
  values(info.rno,n,num,sysdate); 
  commit;
end add_ruku;
/
