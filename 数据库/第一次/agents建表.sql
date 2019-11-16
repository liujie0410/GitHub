/*创建Agents表*/
create table Agents
(
  aid varchar(3)  constraint Agents_Prim primary key,/*设置aid为主键*/
  aname nvarchar(10),
  city nvarchar(10),
  percents int
)

/*向表中输入数据*/
insert into Agents (aid,aname,city,percents)
values('A01','smith','New York','6')
insert into Agents (aid,aname,city,percents)
values('A02','Jones','Newark','6')
insert into Agents (aid,aname,city,percents)
values('A03','Brown','Tokyo','7')
insert into Agents (aid,aname,city,percents)
values('A04','Gray','New York','6')
insert into Agents (aid,aname,city,percents)
values('A05','Otasi','Duluth','5')
insert into Agents (aid,aname,city,percents)
values('A06','smith','Dallas','5')
