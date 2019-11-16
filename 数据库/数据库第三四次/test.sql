/*����ѭ������*/
declare @i int
declare @j int

/*����order�������*/
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

/*orderdetail�������*/
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

/*pickofmonth�������*/
declare @year int;
declare @month smallint;

/*�����������ݵĳ�ʼorderno��orderdate*/
set @toporderno = (select top 1 cOrderNo from Orders order by cOrderNo desc) + 1
set @orderdate = (select top 1 dOrderDate from Orders  order by dOrderDate desc)

/*ѭ�����1000������*/
set @i = 0
while(@i < 1000)                
begin

/*����orders��һ��������*/
  set @orderno = right('000000'+convert(varchar(6),@toporderno),6)
  set @orderdate = dateadd(dd,round(rand()*2,0),@orderdate)
  set @orderdate = dateadd(ss,round(rand()*5000+1,0),@orderdate)
  set @cartid = (select  top 1 cCartId from ShoppingCart order by NEWID());
  set @shopperid = (select  top 1 cShopperId  from Shopper order by NEWID());
/*��һ�β���order����*/
  insert into Orders(cOrderNo,dOrderDate,cCartId,cShopperId)
  values(@orderno,@orderdate,@cartid,@shopperid)

/*detail���ݳ�ʼ��*/
  set @totalweight = 0;
  set @wrapcharges = 0;
  set @totalcost = 0;
/*����orderdetail����*/
  set @j = 0
  set @toyid = (select top 1 cToyId from Toys where cToyId not in (select top (@j) cToyId from Toys))
  set @j += 1;
  set @siqty = round(rand()*4+1,0);
  /*����pickofmonth*/
  set @month = (select month(dOrderDate) from Orders where cOrderNo = @orderno)
  set @year = (select year(dOrderDate) from Orders where cOrderNo = @orderno)
  --�жϱ����Ƿ�ǡ���д�����´˶����ŵļ�¼�����У������Ķ����������������¶������������������*/
  if exists(select *  from PickOfMonth  where cToyId = @toyid and siMonth = @month and iYear = @year)
  begin
    update PickOfMonth
    set iTotalSold = iTotalSold + @siqty 
    where cToyId = @toyid and siMonth = @month and iYear = @year;
  end;
   --�����ǰʱ���¼�ڱ��в����ڣ���Ϊ��������¼
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
  --��������ܼ�=����*����
  set @toyrate = (select mToyRate  from Toys where cToyId = @toyid);
  set @toycost = @siqty * @toyrate;
/*����detail*/
  insert into OrderDetail(cOrderNo,cToyId,siQty,cGiftWrap,cWrapperId,vMessage,mToyCost)
  values(@orderno,@toyid,@siqty,@giftwrap,@wrapperid,@message,@toycost)

/*����order�Ĳ�������*/
  --���������=��������*����
  set @sitoyweight = (select siToyWeight from Toys where cToyId = @toyid);
  set @totalweight += @sitoyweight * @siqty;
  if(@giftwrap = 'Y')
  begin
   --��װ�ܼ�=���ΰ�װ�۸�*����
    set @wrapperrate = (select mWrapperRate from Wrapper where cWrapperId = @wrapperid);
    set @wrapcharges +=  @siqty * @wrapperrate;
  end;
  --����ܼ�
  set @totalcost += @toycost;
  --�����˷�
  set @shippingmodeid = (select top 1 cModeId from ShippingMode order by NEWID());
  set @countryid = (select cCountryId from Shopper where cShopperId = @shopperid);
  set @pound = (select mRatePerPound from ShippingRate where cModeId = @shippingmodeid and cCountryID = @countryid);
  set @shippingcharges = @pound * @totalweight;
  set @corderprocessed = 'Y';
  --�����ܼ�
  set @totalcost += @shippingcharges + @wrapcharges;
  set @dexpdeldate = @orderdate;
  set @dexpdeldate = dateadd(dd,round(rand()*2,0),@dexpdeldate);
  set @dexpdeldate = dateadd(ss,round(rand()*5000+1,0),@dexpdeldate);

/*�ڶ��β���order����*/
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
