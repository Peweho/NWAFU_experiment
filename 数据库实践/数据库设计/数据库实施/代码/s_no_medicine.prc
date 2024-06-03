create or replace procedure s_no_medicine(n medicine_view.mno%type) is
info medicine_view%rowtype;
cursor c is
       select *
       from medicine_view
       where medicine_view.mno=n;
begin
  open c;
  loop
    fetch c into info;
    exit when c%notfound;
    dbms_output.put_line(info.mno||','||
                         info.mname||','||
                         info.mprice||','||
                         info.mnum||','||
                         info.MPRODUCE||','||
                         info.MQUALITY);
  end loop;
  close c;
  
end s_no_medicine;
/
