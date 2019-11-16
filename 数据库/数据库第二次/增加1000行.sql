/*����orders�������*/
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
declare @wrapperrate money/*��װ����*/
declare @countryid int
declare @counryrate int
--��������µ�ʱ��
declare @Date_start datetime 

set @Date_start=(select top 1 dOrderDate from Orders  order by dOrderDate desc) 
--���������ExpDelʱ��*/
declare @Date_start2 datetime 



/*����orderdetail�������*/
declare @toyid char
declare @siqty int
declare @giftwrap char
declare @wrapperid int
declare @message char
declare @toyrate money
declare @toycost money

/*ѭ������*/
declare @i int
set @i=1
declare @j int
set @j=0
/*��ʱ������Լ��*/
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

--���õ�ǰ�������Ϊ��һ�����һ���������
set @lastno = (select top 1 cOrderNo from Orders order by cOrderNo desc);
set @no = @lastno + 1;

/*ѭ������1000��*/
while @i<=10
begin

/*����orders��һ��������*/
--�ֲ�ͬȡֵ�β��������ţ�ʹ�ò�ͬȡֵ��Χ�ڵĶ�����ǰ��0�ĸ�����ͬ���Դ�ͳһ��ʽ
 /* if(@i<90) set @orderno='0000'+convert(char(2),@i+10)
  else if((@i>90)and(@i<990)) set @orderno='000'+convert(char(3),@i+10)
  else if(@i>990) set @orderno='00'+convert(char(4),@i+10)*/
  set @orderno = right('000000'+convert(varchar(6),@no),6);
  set @cartid=(select top 1 cCartId from ShoppingCart order by newid())
  set @shopperid=(select top 1 cShopperId from Shopper order by newid())
  set @shippingid=(select top 1 cModeId from ShippingMode order by newid())
  set @orderprocess='Y'
--����������µ�ʱ���ExpDelʱ��
 -- set @Date_start=dateadd(minute,abs(checksum(newid()))%(datediff(minute,@Date_start,@Date_end)+1),@Date_start)
 -- set @Date_start2=dateadd(minute,abs(checksum(newid()))%(datediff(minute,@Date_start2,@Date_end2)+1),@Date_start2)
 set @Date_start = dateadd(dd,round(rand()*2,0),@Date_start);
set @Date_start = dateadd(ss,round(rand()*5000+1,0),@Date_start);


/*��һ�β���orders��Ϣ*/
  insert into Orders(cOrderNo,dOrderDate,cCartId,cShopperId)
  values(@orderno,@Date_start,@cartid,@shopperid)

set @j=0
/*����orderdetail������*/
  set @toyid= (select top 1 cToyId from Toys	where cToyId not in (select top (@j) cToyId from Toys))
  set @siqty=round(rand()*4+1,0)
  set @giftwrap=(select top 1 cGiftWrap from OrderDetail order by newid())
--�����ȡwrapperid
  if(@giftwrap = 'Y')
  begin
    set @wrapperid = (select top 1 cWrapperId from Wrapper order by newid())
  end
--�����ȡmessage
  set @message = (select  top 1 vMessage from OrderDetail order by NEWID());
--��������ܼ�
  set @toyrate = (select mToyRate from Toys where cToyId = @toyid)
  set @toycost = @siqty * @toyrate

/*����orderdetail*/
  insert into OrderDetail(cOrderNo,cToyId,siQty,cGiftWrap,cWrapperId,vMessage,mToyCost)
  values(@orderno,@toyid,@siqty,@giftwrap,@wrapperid,@message,@toycost)
 set @j=@j+1

/*����orders�ڶ���������*/
set @Date_start2= @Date_start 
set @Date_start2 = dateadd(dd,round(rand()*2,0),@Date_start2);
set @Date_start2 = dateadd(ss,round(rand()*5000+1,0),@Date_start2)
--���㶩��������
  set @sitoyweight=(select siToyWeight from Toys where cToyId = @toyid)
  set @totalweight+=@sitoyweight * @siqty
--�����װ�� 
  if(@giftwrap='Y')
  begin
    set @wrapperrate=(select mWrapperRate from Wrapper where cWrapperId=@wrapperid)
    set @giftcharges+=@siqty*@wrapperrate
  end
--��������߼۸�
  set @totalcost+=@toycost
--�����˷�
  set @countryid=(select cCountryId from Shopper where cShopperId=@shopperid)
  set @counryrate=(select mRatePerPound from ShippingRate where cModeId=@shippingid and cCountryID=@countryid)
  set @shipcharges=@counryrate*@totalweight
--���㶩���ܼ�
  set @totalcost=@shipcharges+@giftcharges

/*�ڶ��β���orders������*/
update Orders
set cShippingModeId = @shippingid,
mShippingCharges = @shipcharges,
mGiftWrapCharges = @giftcharges,
cOrderProcessed = @orderprocess,
mTotalCost = @totalcost,
dExpDelDate = @Date_start2
where cOrderNo = @orderno

/*ѭ������*/
  set @i=@i+1
  set @no=@no+1
end

/*�ָ����*/
alter table Toys check constraint all 
alter table Orders check  constraint all
alter table OrderDetail check  constraint all
alter table PickOfMonth check  constraint all
alter table Shipment check  constraint all
alter table ShippingMode check  constraint all
alter table Shopper check  constraint all
alter table Recipient check  constraint all
alter table Wrapper check  constraint all
