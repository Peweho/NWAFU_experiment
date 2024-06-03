create or replace procedure add_func(n1 registe.rno%type,
                                     n2 number,
                                     params varchar2 default null)
is
num number;
info func%rowtype;
current_param varchar2(30);
current_param2 varchar2(30);
i number;
begin
  select count(f.fno)+1 into num
  from func f;
  
  info.fno := concat('F', lpad(num, 3, '0'));
  info.reno := n1;
  info.fdate := sysdate;
  
  insert 
  into func(fno,fdate,reno)
  values(info.fno,info.fdate,info.reno);
  
  i := 1;
  WHILE i <=n2*2  LOOP
    current_param := REGEXP_SUBSTR(params, '[^,]+', 1, i);
    current_param2 := REGEXP_SUBSTR(params, '[^,]+', 1, i+1);
    
    -- 处理当前参数
    insert into med_func
    values(current_param,info.fno,to_number(current_param2));
    i := i + 2;
  END LOOP;
  commit;
end add_func;
/
