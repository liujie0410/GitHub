/*基于表Orders和Shopper，以下列格式生成报表：
      购货人ID   XXX    购货人姓名   XXX    
      购货人地址  XXXXXX 
      定单号XXX  定单时间XXX  定单金额XXX
      定单号XXX  定单时间XXX  定单金额XXX*/

--定义变量
declare @id char(6)
declare @name char(12)
declare @area char(30)
declare @no char(6)
declare @date1 date
declare @cost money

--创建游标1，获取购货人信息
declare cursor1 cursor for
select cShopperId ,concat(vFirstName,vLastName) ,vAddress 
from Shopper
--打开游标1
open cursor1
--移动游标1提取数据
fetch cursor1 into @id,@name,@area
--当游标获取下一条数据成功时
while(@@fetch_status=0)
begin
--输出购货人信息
print '购货人ID   '+ @id+'   '+'购货人姓名   '+@name
print '购货人地址   '+@area
  
  --创建游标2，获取订单信息
  declare cursor2 cursor for
  select cOrderNo,dOrderDate,mTotalCost
  from Orders
  where @id=cShopperId
  --打开游标2
  open cursor2
  --移动游标2提取数据
  fetch cursor2 into @no,@date1,@cost
  --当游标获取下一条数据成功时
  while(@@fetch_status=0)
  begin
  --输出订单信息
  print '定单号   '+ @no+'   '+'订单时间   '+convert(varchar(100), @date1, 120)+ '定单金额   '+convert(varchar(6),@cost)
  --游标2继续获取下一条数据
  fetch cursor2 into @no,@date1,@cost
  end
  close cursor2
  --删除游标2使用
  deallocate cursor2

--游标1继续获取下一条数据
fetch cursor1 into @id,@name,@area
end
close cursor1
--删除游标1使用
deallocate cursor1 