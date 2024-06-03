create or replace trigger add_medicine_num
  before insert
  on ruku 
  for each row
declare
begin
    update medicine
    set medicine.mnum = medicine.mnum + :new.rnum
    where medicine.mno=:new.rmno;
end add_medicine_num;
/
