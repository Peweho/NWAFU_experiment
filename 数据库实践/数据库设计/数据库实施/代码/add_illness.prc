create or replace procedure add_illness(n illness_history.pno%type,
                                        d illness_history.describe%type)
is
begin
   update illness_history i
   set i.describe=d
   where i.pno=n and i.describe is null;
  commit;
end add_illness;
/
