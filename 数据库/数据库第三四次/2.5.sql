/*
当购物者确认定单时，应该包含下面的步骤：
（1）产生新的定单号（要求创建一个存储过程，用于产生新定单号）。
（2）定单号，当前日期，购物车ID，和购物者ID应该加到Orders表中。
（3）定单号，玩具ID和数量应加到OrderDetail表中。
（4）在OrderDetail表中更新玩具成本。（提示：Toy cost = Quantity * Toy Rate）。
（5）从ShoppingCart表中将本次已购买的玩具删除。
将上述步骤定义为一个事务。编写一个过程以购物车ID和购物者ID为参数，实现这个事务。
（提示：首先需要修改表ShoppingCart的结构，在表中新增一个字段‘Status’。该字段取值为1，表示该玩具为本次下订单时要购买的玩具，并产生一些模拟数据。）*/

/*
--创建产生新订单号的存储过程
create procedure updateorderno
@orderno char(6) output
as
--找到订单表中最大的订单号
select @orderno=max(cOrderNo) from Orders
--用case对不同阶段的orderno更新，保持格式一致
select @orderno=
case
  when @orderno>=0 and @orderno<9 then '00000'+ convert(char,@orderno+1)
  when @orderno>=9 and @orderno<99 then '0000' + convert(char,@orderno+1)
  when @orderno>=99 and @orderno<999 then '000' + convert(char,@orderno+1)
  when @orderno>=999 and @orderno<9999 then '00' + convert(char,@orderno+1)
  when @orderno>=9999 and @orderno<99999 then '0' + convert(char,@orderno+1)
  when @orderno>=99999  then convert(char,@orderno+1)
end
return
*/

--创建存储过程
create procedure prcorder (@cartid char(6) output,@shopperid char(6) output)
as
--创建事务
begin transaction
--定义变量
declare @orderno char(6),@orderno1 char(6),@toyid char(6),@qty char(6)
--执行存储过程updateorderno
exec updateorderno @orderno output
--查询非空的orderno
select @orderno1 =isnull(convert(nvarchar,@orderno),'null')
--创建表tab1，将搜索到的订单的订单号、购物车id、购买者id，下单时间插入表中
create table tab1 (orderno char(6),cartid char(6),shopperid char(6),orderdate datetime)
insert into tab1 (orderno,cartid,shopperid,orderdate) values(@orderno1,@cartid,@shopperid,getdate())
--受上一条影响的行数若为0，则回到最初状态
if @@rowcount=0
begin 
rollback transaction
return
end

--向orders表中插入信息
insert into Orders(cOrderNo,cCartId,cShopperId,dOrderDate)
select * 
from tab1
select @toyid=cToyId,@qty=siQty
from ShoppingCart
where cCartId=@cartid
if @@rowcount=0
begin 
rollback transaction
return
end

--向ordersdetail表中插入信息
insert into OrderDetail(cOrderNo,cToyId,siQty)
values(@orderno1,@toyid,@qty)
--更新表oderdetil
update OrderDetail
set mToyCost=siQty*mToyRate
from OrderDetail,Toys
if @@rowcount=0
begin 
rollback transaction
return
end

--从ShoppingCart表中将本次已购买的玩具删除
delete 
from ShoppingCart
where cCartId=@cartid
if @@rowcount=0
begin 
rollback transaction
return
end

--提交事务，保存到数据库中
commit transaction
go
