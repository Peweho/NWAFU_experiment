create or replace procedure s_doctor(n doctor.dname%type) 
is
info doctor%rowtype;
dion division.diname%type;
cursor c is
       select d.dno,d.dname,d.dage,d.dsex,di.diname
       from doctor d,division di
       where d.dname=n and d.dino=di.dino;
begin
  open c;
  loop
    fetch c into info.dno,info.dname,info.dage,info.dsex,dion;
    exit when c%notfound;
    dbms_output.put_line(info.dno||','||
                         info.dname||','||
                         info.dsex||','||
                         info.dage||','||
                         dion);
  end loop;
  close c;
end s_doctor;
/
