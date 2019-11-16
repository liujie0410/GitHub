/*创建一个称为prcHandlingCharges的过程，它接收定单号并显示经营费用。PrchandlingCharges过程应使用prcCharges过程来得到装运费和礼品包装费。
（提示：经营费用=装运费+礼品包装费）*/

create procedure prcHandlingCharges
(@non char(6),@cost money output)
as
declare @ship money
declare @gift money
--执行存储过程prcCharges
exec prcCharges  @non,@ship output,@gift output
set @cost=@ship+@gift
go