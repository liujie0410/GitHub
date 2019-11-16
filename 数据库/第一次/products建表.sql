/*创建Products表*/
create table Products
(
  pid varchar(3) constraint Products_Prim primary key,/*设置pid为主键*/
  pname nvarchar(10),
  city nvarchar(10),
  quantity int,
  price float not null
)

/*向表中输入数据*/
insert into Products (pid,pname,city,quantity,price)
values('P01','comb','Dallas','111400','0.50')
insert into Products (pid,pname,city,quantity,price)
values('P02','brush','Newark','203000','0.50')
insert into Products (pid,pname,city,quantity,price)
values('P03','razor','Duluth','150600','1.00')
insert into Products (pid,pname,city,quantity,price)
values('P04','Pen','Duluth','125300','1.00')
insert into Products (pid,pname,city,quantity,price)
values('P05','pencil','Dallas','221400','1.00')
insert into Products (pid,pname,city,quantity,price)
values('P06','folder','Dallas','123100','2.00')
insert into Products (pid,pname,city,quantity,price)
values('P07','case','Newark','100500','1.00')
