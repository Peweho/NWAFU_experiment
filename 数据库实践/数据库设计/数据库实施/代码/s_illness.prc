create or replace procedure s_illness(n illhis_view.PNO%type) 
is
info illhis_view%rowtype;
cursor c is 
       select *
       from illhis_view
       where illhis_view.PNO=n;
begin
     open c;
     loop
       fetch c into info;
       exit when c%notfound;
       dbms_output.put_line(info.PNO||','||
                            info.PNAME||','||
                            info.PSEX||','||
                            info.describe||','||
                            info.diname||','||
                            info.idata);
     end loop;
     close c;
end s_illness;
/
