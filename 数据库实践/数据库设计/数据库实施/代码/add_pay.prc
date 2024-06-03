create or replace procedure add_pay(n1 pay.pfno%type,n2 pay.pname%type) 
is

num number;
info pay%rowtype;
begin

    select count(pay.pno)+1 into num from pay;
    info.pno := concat('P', lpad(num, 3, '0'));
    info.pdate := sysdate;
    info.pname := n2;
    info.pfno := n1;
    info.ppay := 0;
    
    insert into pay
    values(info.pno,info.pfno,info.ppay,info.pname,info.pdate);
    commit;

end add_pay;
/
