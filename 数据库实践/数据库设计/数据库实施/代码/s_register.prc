create or replace procedure s_register(n in register_view.rno%type) 
is
r r.egister_view%rowtype;
cursor c is
         select *
         from register_view rv
         where rv.rno=n;
begin    
  open c;
  loop
       fetch c into r;
       exit when c%notfound;
       dbms_output.put_line(r.PNAME||','||
                            r.PSEX||','||
                            r.PAGE||','||
                            r.PADRESS||','||
                            r.dname||','||
                            r.diname);
   end loop;
   close c;
end s_register;
/
