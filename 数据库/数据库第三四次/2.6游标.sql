/*编写一个程序显示每天的定单状态。
如果当天的定单值总合大于150，则显示“High sales”,否则显示”Low sales”。
要求列出日期、定单状态和定单总价值。*/

/*
--查找订单日期、状态、订单价值，存入ordertable表
select dOrderDate,sum(mTotalCost) as totalcost
into ordertable 
from Orders
group by dOrderDate
select * from ordertable*/

--定义变量，存储游标获取的内容
declare @date varchar(20)
declare @cost money

--创建游标
declare mycursor cursor for
select dOrderDate,TotalCost 
from ordertable
--打开游标
open mycursor
--移动游标提取数据
fetch mycursor into @date,@cost
print'       日期           订单状态   订单总价值'
--当游标获取下一条数据成功时
while(@@fetch_status=0)
begin
--输出订单状态
 if(@cost>150)
   print @date+'    '+'High Sales'+'    '+cast(@cost as varchar(10))
 else
   print @date+'    '+'Low Sales'+'    '+cast(@cost as varchar(10))
--继续获取下一条数据
fetch mycursor into @date,@cost
end
close mycursor
--删除游标使用
deallocate mycursor

