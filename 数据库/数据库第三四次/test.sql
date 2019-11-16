/*定义循环变量*/
declare @i int
declare @j int

/*定义order相关数据*/
declare @orderno char(6)
declare @orderdate datetime
declare @cartid char(6)
declare @shopperid char(6)
declare @shippingmodeid char(2)
declare @shippingcharges money
declare @corderprocessed char
declare @dexpdeldate DateTime
declare @toporderno int
declare @wrapperrate money;
declare @sitoyweight smallint;
declare @countryid char(3);

/*orderdetail相关数据*/
declare @toyid char(6);
declare @siqty smallint;
declare @giftwrap char;
declare @wrapperid	char(3);
declare @message varchar(256);
declare @totalweight int;
declare @wrapcharges money
declare @totalcost	money
declare @toyrate money;
declare @toycost money;
declare @pound money;

/*pickofmonth相关数据*/
declare @year int;
declare @month smallint;

/*设置增加数据的初始orderno和orderdate*/
set @toporderno = (select top 1 cOrderNo from Orders order by cOrderNo desc) + 1
set @orderdate = (select top 1 dOrderDate from Orders  order by dOrderDate desc)

/*循环添加1000条数据*/
set @i = 0
while(@i < 1000)                
begin

/*产生orders第一部分数据*/
  set @orderno = right('000000'+convert(varchar(6),@toporderno),6)
  set @orderdate = dateadd(dd,round(rand()*2,0),@orderdate)
  set @orderdate = dateadd(ss,round(rand()*5000+1,0),@orderdate)
  set @cartid = (select  top 1 cCartId from ShoppingCart order by NEWID());
  set @shopperid = (select  top 1 cShopperId  from Shopper order by NEWID());
/*第一次插入order数据*/
  insert into Orders(cOrderNo,dOrderDate,cCartId,cShopperId)
  values(@orderno,@orderdate,@cartid,@shopperid)

/*detail数据初始化*/
  set @totalweight = 0;
  set @wrapcharges = 0;
  set @totalcost = 0;
/*产生orderdetail数据*/
  set @j = 0
  set @toyid = (select top 1 cToyId from Toys where cToyId not in (select top (@j) cToyId from Toys))
  set @j += 1;
  set @siqty = round(rand()*4+1,0);
  /*更新pickofmonth*/
  set @month = (select month(dOrderDate) from Orders where cOrderNo = @orderno)
  set @year = (select year(dOrderDate) from Orders where cOrderNo = @orderno)
  --判断表中是否恰好有此年此月此订单号的记录，若有，则将它的订单订单总量加上新订单中随机产生的数量*/
  if exists(select *  from PickOfMonth  where cToyId = @toyid and siMonth = @month and iYear = @year)
  begin
    update PickOfMonth
    set iTotalSold = iTotalSold + @siqty 
    where cToyId = @toyid and siMonth = @month and iYear = @year;
  end;
   --如果当前时间记录在表中不存在，则为表新增记录
  else begin
    insert PickOfMonth(cToyId,siMonth,iYear,iTotalSold)
    values(@toyid,@month,@year,@siqty)
   end;
  set @giftwrap = (select  top 1 cGiftWrap  from OrderDetail order by NEWID());
  if(@giftwrap = 'Y')
  begin
    set @wrapperid = (select  top 1 cWrapperId  from Wrapper order by NEWID());
  end;
  else begin
    set @wrapperid = null;
  end
  set @message = (select  top 1 vMessage from OrderDetail order by NEWID());
  --计算玩具总价=数量*单价
  set @toyrate = (select mToyRate  from Toys where cToyId = @toyid);
  set @toycost = @siqty * @toyrate;
/*插入detail*/
  insert into OrderDetail(cOrderNo,cToyId,siQty,cGiftWrap,cWrapperId,vMessage,mToyCost)
  values(@orderno,@toyid,@siqty,@giftwrap,@wrapperid,@message,@toycost)

/*计算order的部分数据*/
  --玩具总重量=单个重量*数量
  set @sitoyweight = (select siToyWeight from Toys where cToyId = @toyid);
  set @totalweight += @sitoyweight * @siqty;
  if(@giftwrap = 'Y')
  begin
   --包装总价=单次包装价格*数量
    set @wrapperrate = (select mWrapperRate from Wrapper where cWrapperId = @wrapperid);
    set @wrapcharges +=  @siqty * @wrapperrate;
  end;
  --玩具总价
  set @totalcost += @toycost;
  --计算运费
  set @shippingmodeid = (select top 1 cModeId from ShippingMode order by NEWID());
  set @countryid = (select cCountryId from Shopper where cShopperId = @shopperid);
  set @pound = (select mRatePerPound from ShippingRate where cModeId = @shippingmodeid and cCountryID = @countryid);
  set @shippingcharges = @pound * @totalweight;
  set @corderprocessed = 'Y';
  --计算总价
  set @totalcost += @shippingcharges + @wrapcharges;
  set @dexpdeldate = @orderdate;
  set @dexpdeldate = dateadd(dd,round(rand()*2,0),@dexpdeldate);
  set @dexpdeldate = dateadd(ss,round(rand()*5000+1,0),@dexpdeldate);

/*第二次插入order数据*/
  update Orders set cShippingModeId = @shippingmodeid,
  mShippingCharges = @shippingcharges,
  mGiftWrapCharges = @wrapcharges,
  cOrderProcessed = @corderprocessed,
  mTotalCost = @totalcost,
  dExpDelDate = @dexpdeldate
  where cOrderNo = @orderno;

set @i += 1;
set @toporderno += 1;
end;
