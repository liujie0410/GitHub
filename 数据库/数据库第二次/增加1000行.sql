/*定义orders相关数据*/
declare @orderno char
declare @cartid char(6)
declare @shopperid char(6)
declare @shippingid char(6)
declare @shipcharges money
declare @giftcharges money
declare @orderprocess char
declare @totalcost money
declare @sitoyweight int
declare @totalweight int
declare @wrapperrate money/*包装单价*/
declare @countryid int
declare @counryrate int
--产生随机下单时间
declare @Date_start datetime 

set @Date_start=(select top 1 dOrderDate from Orders  order by dOrderDate desc) 
--产生随机的ExpDel时间*/
declare @Date_start2 datetime 



/*定义orderdetail相关数据*/
declare @toyid char
declare @siqty int
declare @giftwrap char
declare @wrapperid int
declare @message char
declare @toyrate money
declare @toycost money

/*循环变量*/
declare @i int
set @i=1
declare @j int
set @j=0
/*暂时解除外键约束*/
alter table Toys nocheck constraint all 
alter table Orders nocheck  constraint all
alter table OrderDetail nocheck  constraint all
alter table PickOfMonth nocheck  constraint all
alter table Shipment nocheck  constraint all
alter table ShippingMode nocheck  constraint all
alter table Shopper nocheck  constraint all
alter table Recipient nocheck  constraint all
alter table Wrapper nocheck  constraint all

declare @no int
declare @lastno int

--设置当前订单编号为上一次最后一条订单编号
set @lastno = (select top 1 cOrderNo from Orders order by cOrderNo desc);
set @no = @lastno + 1;

/*循环插入1000次*/
while @i<=10
begin

/*产生orders第一部分数据*/
--分不同取值段产生订单号，使得不同取值范围内的订单号前的0的个数不同，以此统一格式
 /* if(@i<90) set @orderno='0000'+convert(char(2),@i+10)
  else if((@i>90)and(@i<990)) set @orderno='000'+convert(char(3),@i+10)
  else if(@i>990) set @orderno='00'+convert(char(4),@i+10)*/
  set @orderno = right('000000'+convert(varchar(6),@no),6);
  set @cartid=(select top 1 cCartId from ShoppingCart order by newid())
  set @shopperid=(select top 1 cShopperId from Shopper order by newid())
  set @shippingid=(select top 1 cModeId from ShippingMode order by newid())
  set @orderprocess='Y'
--产生随机的下单时间和ExpDel时间
 -- set @Date_start=dateadd(minute,abs(checksum(newid()))%(datediff(minute,@Date_start,@Date_end)+1),@Date_start)
 -- set @Date_start2=dateadd(minute,abs(checksum(newid()))%(datediff(minute,@Date_start2,@Date_end2)+1),@Date_start2)
 set @Date_start = dateadd(dd,round(rand()*2,0),@Date_start);
set @Date_start = dateadd(ss,round(rand()*5000+1,0),@Date_start);


/*第一次插入orders信息*/
  insert into Orders(cOrderNo,dOrderDate,cCartId,cShopperId)
  values(@orderno,@Date_start,@cartid,@shopperid)

set @j=0
/*产生orderdetail各数据*/
  set @toyid= (select top 1 cToyId from Toys	where cToyId not in (select top (@j) cToyId from Toys))
  set @siqty=round(rand()*4+1,0)
  set @giftwrap=(select top 1 cGiftWrap from OrderDetail order by newid())
--随机获取wrapperid
  if(@giftwrap = 'Y')
  begin
    set @wrapperid = (select top 1 cWrapperId from Wrapper order by newid())
  end
--随机获取message
  set @message = (select  top 1 vMessage from OrderDetail order by NEWID());
--计算玩具总价
  set @toyrate = (select mToyRate from Toys where cToyId = @toyid)
  set @toycost = @siqty * @toyrate

/*插入orderdetail*/
  insert into OrderDetail(cOrderNo,cToyId,siQty,cGiftWrap,cWrapperId,vMessage,mToyCost)
  values(@orderno,@toyid,@siqty,@giftwrap,@wrapperid,@message,@toycost)
 set @j=@j+1

/*产生orders第二部分数据*/
set @Date_start2= @Date_start 
set @Date_start2 = dateadd(dd,round(rand()*2,0),@Date_start2);
set @Date_start2 = dateadd(ss,round(rand()*5000+1,0),@Date_start2)
--计算订单总重量
  set @sitoyweight=(select siToyWeight from Toys where cToyId = @toyid)
  set @totalweight+=@sitoyweight * @siqty
--计算包装费 
  if(@giftwrap='Y')
  begin
    set @wrapperrate=(select mWrapperRate from Wrapper where cWrapperId=@wrapperid)
    set @giftcharges+=@siqty*@wrapperrate
  end
--计算总玩具价格
  set @totalcost+=@toycost
--计算运费
  set @countryid=(select cCountryId from Shopper where cShopperId=@shopperid)
  set @counryrate=(select mRatePerPound from ShippingRate where cModeId=@shippingid and cCountryID=@countryid)
  set @shipcharges=@counryrate*@totalweight
--计算订单总价
  set @totalcost=@shipcharges+@giftcharges

/*第二次插入orders的数据*/
update Orders
set cShippingModeId = @shippingid,
mShippingCharges = @shipcharges,
mGiftWrapCharges = @giftcharges,
cOrderProcessed = @orderprocess,
mTotalCost = @totalcost,
dExpDelDate = @Date_start2
where cOrderNo = @orderno

/*循环计数*/
  set @i=@i+1
  set @no=@no+1
end

/*恢复外键*/
alter table Toys check constraint all 
alter table Orders check  constraint all
alter table OrderDetail check  constraint all
alter table PickOfMonth check  constraint all
alter table Shipment check  constraint all
alter table ShippingMode check  constraint all
alter table Shopper check  constraint all
alter table Recipient check  constraint all
alter table Wrapper check  constraint all
