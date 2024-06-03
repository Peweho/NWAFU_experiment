create view register_view
as
       select f.rno,p.*,d.dname,di.diname
       from registe f, patient p, doctor d, division di
       where f.rpno=p.pno and f.rdno=d.dno and d.dino=di.dino
       order by rno;
  
create view illhis_view
as 
       select f.PNO,f.PNAME,f.PSEX,f.PAGE,f.PADRESS,i.describe,f.dname,f.diname,i.idata
       from register_view f,illness_history i
       where f.PNO=i.pno;
       
create view func_view
as
       select f.fno,r.PNAME,r.PSEX,r.PAGE,r.dname,r.diname,med.mname,m.mnum
       from func f,register_view r,med_func m,medicine med
       where f.reno=r.rno and f.fno=m.mfunc and m.mfno=med.mno
  
create view medicine_view
as
       select m.mno,m.mname,mp.mprice,m.mnum,m.MPRODUCE,m.MQUALITY,mew.mwup,mew.mwdown             
       from medicine m,med_price mp,medicine_warning mew,ruku r
       where m.mno=mp.mpno and m.mno=mew.mwno and r.rmno=m.mno
       
create view moneyinfo_view
as
       select p.pno,sum(price.m) total
       from pay p,(
                    select mf.mfunc,(mf.mnum*mp.mprice) m
                    from med_func mf,med_price mp
                    where mf.mfno=mp.mpno
                  ) price
       where p.pfno=price.mfunc
       group by p.pno

create view payinfo_view
as       
       select p.pno,fv.mname,mp.mprice,fv.mnum,mi.total
              ,p.ppay,(ppay-mi.total) ling,p.pname,p.pdate
       from pay p,
            moneyinfo_view mi,
            med_price mp,
            ( select f.fno,med.mno,med.mname,r.*,m.mnum
              from func f,register_view r,med_func m,medicine med
              where f.reno=r.rno and f.fno=m.mfunc and m.mfno=med.mno
            ) fv 
       where mp.mpno=fv.mno and
             p.pfno=fv.fno and
             mi.pno=p.pno
          
create view no_pay
as
       select fv.fno,fv.PNAME,fv.PSEX
       from func_view fv
       where fv.fno in (select mf.mfunc
                        from med_func mf left outer join pay p on (p.pfno=mf.mfunc)
                        where p.pno is null
                        group by mf.mfunc)
       group by fv.fno,fv.PNAME,fv.PSEX
       
create view pay_view
as
       select pv.pno,pv.total,pv.pname,pv.pdate
       from payinfo_view pv
       group by pv.pno,pv.total,pv.pname,pv.pdate
       
create view warn_up_view
as
       select m.mno,m.mname,m.mnum,m.mwup,m.mwdown
       from medicine_view m
       where m.mnum > m.mwup or  m.mnum < m.mwdown
       
  
       
create view loss_view
as 
       select m.mno,m.mname,l.lnum,l.lreason,l.ldate
       from loss l,medicine m
       where l.lmno=m.mno
       
create view out_view
as
       select o.ono,m.mno,m.mname,o.onum,o.odate
       from outbound o,medicine m
       where o.omno=m.mno
       
create view need_view
as
       select o.nno,m.mno,m.mname,o.nnum,o.ndate
       from need o,medicine m
       where o.nmno=m.mno
       
create view support_view
as
       select s.*,m.mname,m.mproduce,mquality
       from support s,medicine_view m
       where s.smon=m.mno
       
create view ruku_view
as
       select o.rno,m.mno,m.mname,o.rnum,o.rdate
       from ruku o,medicine m
       where o.rmno=m.mno
      
     
       
       
       
       
      
       
