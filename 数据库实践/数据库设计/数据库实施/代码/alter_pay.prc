create or replace procedure alter_pay(n pay.pno%type,m pay_view.total%type) 
is
zhifu pay_view.total%type;
begin
  select p.total into zhifu from pay_view p where p.pno=n;
  if zhifu <= m then
    update pay set pay.ppay=m where pay.pno=n;
    commit;
  else
    dbms_output.put_line('支付失败，原因：金额不足');
  end if;
end alter_pay;
/
