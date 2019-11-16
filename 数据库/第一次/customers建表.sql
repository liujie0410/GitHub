/*创建Customers表*/
create table Customers
(
  cid varchar(4) constraint Customers_Prim primary key,/*设置cid为主键*/
  cname nvarchar(10),
  city nvarchar(10),
  discnt float check ( discnt between 0 and 30)
)

/*向表中输入数据*/
insert into Customers (cid,cname,city,discnt)
values('C001','TipTop','Duluth','10.00')
insert into Customers (cid,cname,city,discnt)
values('C002','Basics','Dallas','12.00')
insert into Customers (cid,cname,city,discnt)
values('C003','Allied','Dallas','8.00')
insert into Customers (cid,cname,city,discnt)
values('C004','ACME','Duluth','8.00')
insert into Customers (cid,cname,city,discnt)
values('C005','Oriental','Kyoto','6.00')
insert into Customers (cid,cname,city,discnt)
values('C006','ACME','Kyoto','0.00')

