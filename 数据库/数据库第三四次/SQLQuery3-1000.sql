/*--2．1.1创建数据库关系图
use GlobalToyz
exec sp_changedbowner sa
go 
EXEC sp_dbcmptlevel GlobalToyz, 
90 USE GlobalToyz 
EXEC sp_changedbowner 'sa' */

--2.1.3 插入1000条数据
use GlobalToyz
--定义数据
declare @i int;
declare @j int;
declare @no int;
declare @mtoyrate money;
declare @mwrapperrate money;
declare @mrateperpound money;
declare @ccountryid char(3);
declare @sitoyweight smallint;
declare @totalweight smallint;
declare @lastno int;
declare @year int;
declare @month smallint;

--orders内容
declare @corderno char(6);
declare @dorderdate datetime;
declare @ccartid char(6);
declare @cshopperid char(6);
declare @cshippingmodeid char(2);
declare @mshippingcharges money;
declare @mgiftwrapcharges money;
declare @corderprocessed char;
declare @mtotalcost	money;
declare @dexpdeldate DateTime;

--orderdetail内容
declare @ctoyid char(6);
declare @siqty smallint;
declare @cgiftwrap char;
declare @cwrapperid	char(3);
declare @vmessage varchar(256);
declare @mtoycost money;

--创建表
--用于选取是否有包装
if exists(select * from sysobjects where name = 'giftwrap')
drop table giftwrap
create table giftwrap
(gift char)
insert into giftwrap(gift)
values('Y')
insert into giftwrap(gift)
values('N')
--由于选取备注内容
if exists(select * from sysobjects where name = 'message')
drop table message
create table message
(mess varchar(256))
insert into message(mess)
values('Surprise')
insert into message(mess)
values('I Love you')
insert into message(mess)
values('Happy Birthday')
insert into message(mess)
values('Best Wishes')
insert into message(mess)
values('With love')
insert into message(mess)
values('For you with love')
insert into message(mess)
values('Congratulations')
insert into message(mess)
values('You are the best')
insert into message(mess)
values(null)


--第一次增加orders数据
--设置当前订单编号为上一次最后一条订单编号
set @lastno = (select top 1 cOrderNo
               from Orders
               order by cOrderNo desc);
set @i = 0;
set @no = @lastno + 1;
--设置当前时间为上一次最后一条记录的时间
set @dorderdate = (select top 1 dOrderDate
                    from Orders
                    order by dOrderDate desc);


--循环添加1000条数据
while(@i < 1000)                
begin

--插入orders
--更新orderno
set @corderno = right('000000'+convert(varchar(6),@no),6);
--更新日期（天和秒）
set @dorderdate = dateadd(dd,round(rand()*2,0),@dorderdate);
set @dorderdate = dateadd(ss,round(rand()*5000+1,0),@dorderdate);
--如果时间 > 当前时间，则设置为当前时间
if(@dorderdate > GETDATE())
begin
set @dorderdate = GETDATE();
end;
--随机获取cartid
set @ccartid = (select  top 1 cCartId          
                from ShoppingCart
		        order by NEWID());
--随机获取cShopperId
set @cshopperid = (select  top 1 cShopperId       
                   from Shopper
		           order by NEWID());
--插入数据
insert into Orders(cOrderNo,dOrderDate,cCartId,cShopperId)
values(@corderno,@dorderdate,@ccartid,@cshopperid)

--插入orderdetail
set @j = 0;
--创建toyid表
if exists(select * from sysobjects where name = 'toyid')
drop table toyid
select  top 10 cToyId
into toyid     
from Toys
order by NEWID()

--循环
set @totalweight = 0;
set @mgiftwrapcharges = 0;
set @mtotalcost = 0;
--随机插入1-3条orderdetail记录
while(@j < round(rand()*2+1,0))
begin
--获取orderno
set @corderno = right('000000'+convert(varchar(6),@no),6);
--随机获取不重复的toyid
set @ctoyid = (select top 1 cToyId
                from toyid
				where cToyId not in (select top (@j) cToyId from toyid))
--随机获取数量;
set @siqty = round(rand()*4+1,0);
--随机获取是否有包装
set @cgiftwrap = (select  top 1 gift     
                   from giftwrap
		           order by NEWID());
--随机获取wrapperid
if(@cgiftwrap = 'Y')
begin
set @cwrapperid = (select  top 1 cWrapperId     
                   from Wrapper
		           order by NEWID());
end;
else begin
set @cwrapperid = null;
end;
--随机获取message
set @vmessage = (select  top 1 mess
                  from message
		          order by NEWID());
--计算toycost
set @mtoyrate = (select mToyRate
                  from Toys
				  where cToyId = @ctoyid);
set @mtoycost = @siqty * @mtoyrate;

--插入
insert into OrderDetail(cOrderNo,cToyId,siQty,cGiftWrap,cWrapperId,vMessage,mToyCost)
values(@corderno,@ctoyid,@siqty,@cgiftwrap,@cwrapperid,@vmessage,@mtoycost)

--计算订单重量
set @sitoyweight = (select siToyWeight
                    from Toys
				    where cToyId = @ctoyid);
set @totalweight += @sitoyweight * @siqty;

--计算giftwrappercharges
if(@cgiftwrap = 'Y')
begin
set @mwrapperrate = (select mWrapperRate
                     from Wrapper
				     where cWrapperId = @cwrapperid);
set @mgiftwrapcharges +=  @siqty * @mwrapperrate;
end;


--计算总玩具价格
set @mtotalcost += @mtoycost;

--更新pickofmonth
set @month = (select month(dOrderDate)
		      from Orders
		      where cOrderNo = @corderno)
set @year = (select year(dOrderDate)
		      from Orders
		      where cOrderNo = @corderno)
--如果存在当前年月记录，则更新
if exists(select * 
          from PickOfMonth
		  where cToyId = @ctoyid and siMonth = @month and iYear = @year)
begin
update PickOfMonth
set iTotalSold = iTotalSold + @siqty 
where cToyId = @ctoyid and siMonth = @month and iYear = @year;
end;
--如果不存在当前年月记录，则增加
else begin
insert PickOfMonth(cToyId,siMonth,iYear,iTotalSold)
values(@ctoyid,@month,@year,@siqty)
end;
--j自加
set @j += 1;
end;

--再次插入orders
--查找国家税率
set @cshippingmodeid = (select top 1 cModeId
                        from ShippingMode
				        order by NEWID());
set @ccountryid = (select cCountryId
                   from Shopper
				   where cShopperId = @cshopperid);
set @mrateperpound = (select mRatePerPound
                   from ShippingRate
				   where cModeId = @cshippingmodeid and cCountryID = @ccountryid);

--计算shippingcharges
set @mshippingcharges = @mrateperpound * @totalweight;

--订单处理
set @corderprocessed = 'Y';

--计算总价
set @mtotalcost += @mshippingcharges + @mgiftwrapcharges;

--插入dexpdeldate，使其比订单时间随机增加一定值
set @dexpdeldate = @dorderdate;
set @dexpdeldate = dateadd(dd,round(rand()*2,0),@dexpdeldate);
set @dexpdeldate = dateadd(ss,round(rand()*5000+1,0),@dexpdeldate);
--如果时间 > 当前时间，则设置为当前时间
if(@dexpdeldate > GETDATE())
begin
set @dexpdeldate = GETDATE();
end;
--第二次插入数据
update Orders set cShippingModeId = @cshippingmodeid,
mShippingCharges = @mshippingcharges,
mGiftWrapCharges = @mgiftwrapcharges,
cOrderProcessed = @corderprocessed,
mTotalCost = @mtotalcost,
dExpDelDate = @dexpdeldate
where cOrderNo = @corderno;

--自加
set @i += 1;
set @no += 1;
end;







