--1
create table patient
(
      pno varchar2(30) constraint pk_pno primary key,
      pname varchar2(20),
      psex varchar2(5) constraint ck_psex check (psex ='ÄĞ' or psex = 'Å®'),
      page number(3) constraint ck_page check (page >=0 and page <= 200),
      padress varchar2(100)
)
--2
create table division
(
       dino varchar2(30) constraint pk_dino primary key,
       diname varchar2(20),
       diadress varchar2(50)
)
--3
create table doctor
(
       dno varchar2(30) constraint pk_dno primary key,
       dname varchar2(20),
       dsex varchar2(5) constraint ck_dsex check (dsex ='ÄĞ' or dsex = 'Å®'),
       dage number constraint ck_dage check (dage >=0 and dage <= 200),
       dino varchar2(30) constraint fk_dino references division(dino)
)
--4
create table illness_history
(
       ihno varchar2(30) constraint pk_illhis_ihno primary key,
       pno varchar2(30) constraint fk_illhis_pno references patient(pno),
       describe varchar2(500),
       idata date,
       dino varchar2(30) constraint fk_illhis_dino references division(dino)
)
--5---------------------------
create table medicine
(
       mno varchar2(30) constraint pk_mno primary key,
       mname varchar2(30),
       mproduce date not null,
       mquality number not null constraint ck_mquality check (mquality >= 0),
       mnum number
)
--6
create table registe
(
       rno varchar2(30) constraint pk_reno primary key,
       rpno varchar2(30) constraint fk_repno references patient(pno),
       rdno varchar2(30) constraint fk_redno references doctor(dno)
)
--7
create table func
(
       fno varchar2(30) constraint pk_fno primary key,
       reno varchar2(30) constraint fk_reno references registe(rno)
       fdate date
)
--8
create table med_func
(
       mfno varchar2(30) constraint fk_mfno references medicine(mno),
       mfunc varchar2(30) constraint fk_mfunc  references func(fno),
       mnum number not null constraint ck_mfnum check (mnum > 0),
       constraint pk_mfno_mfunc primary key (mfno,mfunc)
)
--9
create table med_price
(
       mpno varchar2(30) constraint pk_mpno primary key,
       mprice number constraint ck_mprice check(mprice >=0),
       constraint fk_mpno foreign key (mpno) references medicine(mno)
)
--10
create table pay
(
       pno varchar2(30) constraint pk_payno primary key,
       pfno varchar2(30) constraint fk_pfno references func(fno),
       ppay number constraint ck_ppay check(ppay >= 0),
       pname varchar2(30) not null,
       pdate date
)
--11
create table medicine_warning
(
       mwno varchar2(30) constraint pk_mwno primary key,
       mwup number constraint ck_mwup check (mwup >= 0),
       mwdown number constraint ck_mwdown check (mwdown >= 0),
       constraint fk_mwno foreign key (mwno) references medicine(mno)
)

--12
create table loss
(
       lno varchar2(30) constraint pk_lno primary key,
       lmno varchar2(30) constraint fk_lmno references medicine(mno),
       lnum number constraint ck_lnum check(lnum >= 0),
       lreason varchar2(500),
       ldate date
)
--13
create table Outbound
(
       ono varchar2(30) constraint pk_ono primary key,
       omno varchar2(30) constraint fk_omno references medicine(mno),
       onum number constraint ck_onum check(onum >= 0),
       odate date
)
--14
create table need
(
       nno varchar2(30) constraint pk_nno primary key,
       nmno varchar2(30) constraint fk_nmno references medicine(mno),
       nnum number constraint ck_nnum check(nnum >= 0),
       ndate date
)
--15
create table support
(
       sno varchar2(30) constraint pk_sno primary key,
       smon varchar2(30) constraint fk_smno references medicine(mno),
       sprice number,
       snum number,
       sdate date
)
--16
create table ruku
(
       rno varchar2(30) constraint pk_rno primary key,
       rmno varchar2(30) constraint fk_rmno references medicine(mno),
       rnum number,
       rdate date
)
