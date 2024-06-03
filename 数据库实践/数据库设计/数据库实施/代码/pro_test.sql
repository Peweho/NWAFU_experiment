--查看挂号单
declare
  r register_view.rno%type;
begin
  r := &输入挂号单号;
  s_register(r);
end;

--查看医生信息
declare
  r doctor.dname%type;
begin
  r := &医生姓名;
  s_doctor(r);
end;

--挂号
declare
  r1 registe.rpno%type;
  r3 doctor.dno%type;
begin
  r1 := &病人号;
  r3 :=&医生号;
  add_register(r1,r3);
end;

--查看病史记录
declare
  r illhis_view.PNO%type;
begin
  r := &病人号;
  s_illness(r);
end;

--添加病情描述
declare
  r illhis_view.PNO%type;
  de illhis_view.describe%type;
begin
  r := &病人号;
  de := &病情描述;
  add_illness(r,de);
end;

--按名查看药品信息
declare
  r medicine_view.mname%type;
begin
  r := &药品名称;
  s_name_medicine(r);
end;

--按号查看药品信息
declare
  r medicine_view.mno%type;
begin
  r := &药品号;
  s_no_medicine(r);
end;

--生成处方 参数1：挂号单号；
-----------参数2：药品种类数；
-----------参数3：',药品号,数量...'
--例：add_func('R022',2,',M001,20,M002,34');
declare
  r := &挂号单号;
  n := &药品种类数;
  d := &药品号,数量;
begin
  add_func(r,n,d);
end;

--增加缴费单
declare
  f pay.pfno%type;
  p pay.pname%type;
begin
  f := &处方单号;
  p := &收银员姓名;
  add_pay(f,p);
end;

--缴费
declare
  m pay.ppay%type;
  n pay.pno%type;
begin
  n := &缴费单号;
  m := &支付金额;
  alter_pay(n,m);
end;
commit;
select p.total
from pay_view p
where p.pno='P001';

--增加入库信息
declare
  mno medicine.mno%type;
  mnum number;
begin
  mno := &药品号;
  mnum := &数量;
  add_ruku(mno,mnum);
end;
