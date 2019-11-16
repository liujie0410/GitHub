/*创建Orders表*/
create table Orders
(
  ordno int constraint Orders_Prim primary key,/*设置ordno为主键*/
  month varchar(3),
  qty int,
  dollars float,
  cid varchar(4) not null foreign key references Customers(cid) ,
  pid varchar(3) not null foreign key references Products(pid),
  aid varchar(3) not null foreign key references Agents(aid)
)
/*向表中输入数据*/
insert into Orders (ordno,month,cid,aid,pid,qty,dollars)
values('1011','Jan','C001','A01','P01','1000','450.00')
insert into Orders (ordno,month,cid,aid,pid,qty,dollars)
values('1012','Jan','C001','A01','P01','1000','450.00')
insert into Orders (ordno,month,cid,aid,pid,qty,dollars)
values('1019','Feb','C001','A02','P02','400','180.00')
insert into Orders (ordno,month,cid,aid,pid,qty,dollars)
values('1017','Feb','C001','A06','P03','600','540.00')
insert into Orders (ordno,month,cid,aid,pid,qty,dollars)
values('1018','Feb','C001','A03','P04','600','540.00')
insert into Orders (ordno,month,cid,aid,pid,qty,dollars)
values('1023','Mar','C001','A04','P05','500','450.00')
insert into Orders (ordno,month,cid,aid,pid,qty,dollars)
values('1022','Mar','C001','A05','P06','400','720.00')
insert into Orders (ordno,month,cid,aid,pid,qty,dollars)
values('1025','Apr','C001','A05','P07','800','720.00')
insert into Orders (ordno,month,cid,aid,pid,qty,dollars)
values('1013','Jan','C002','A03','P03','1000','880.00')
insert into Orders (ordno,month,cid,aid,pid,qty,dollars)
values('1026','May','C002','A05','P03','800','704.00')
insert into Orders (ordno,month,cid,aid,pid,qty,dollars)
values('1015','Jan','C003','A03','P05','1200','1104.00')
insert into Orders (ordno,month,cid,aid,pid,qty,dollars)
values('1014','Jan','C003','A03','P05','1200','1104.00')
insert into Orders (ordno,month,cid,aid,pid,qty,dollars)
values('1021','Feb','C004','A06','P01','1000','460.00')
insert into Orders (ordno,month,cid,aid,pid,qty,dollars)
values('1016','Jan','C004','A01','P01','1000','500.00')
insert into Orders (ordno,month,cid,aid,pid,qty,dollars)
values('1020','Feb','C005','A03','P07','600','600.00')
insert into Orders (ordno,month,cid,aid,pid,qty,dollars)
values('1024','Mar','C006','A06','P01','800','400.00')
