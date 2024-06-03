create or replace trigger add_illness
  before insert
  on registe 
  for each row
declare
  info illness_history%rowtype;
  num number;
begin
  select count(r.dino)+1 into num
  from illness_history r;
  info.ihno := concat('IH', lpad(num, 3, '0'));
  
  info.pno := :new.rpno;
  info.idata := sysdate;
  
  select d.dino into info.dino
  from doctor d
  where d.dno=:new.rdno;
  
  insert 
  into illness_history(IHNO,pno,idata,dino)
  values(info.ihno,info.pno,info.idata,info.dino);
end add_illness;
/
