/*--2��1.1�������ݿ��ϵͼ
use GlobalToyz
exec sp_changedbowner sa
go 
EXEC sp_dbcmptlevel GlobalToyz, 
90 USE GlobalToyz 
EXEC sp_changedbowner 'sa' */

--2.1.3 ����1000������
use GlobalToyz
--��������
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

--orders����
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

--orderdetail����
declare @ctoyid char(6);
declare @siqty smallint;
declare @cgiftwrap char;
declare @cwrapperid	char(3);
declare @vmessage varchar(256);
declare @mtoycost money;

--������
--����ѡȡ�Ƿ��а�װ
if exists(select * from sysobjects where name = 'giftwrap')
drop table giftwrap
create table giftwrap
(gift char)
insert into giftwrap(gift)
values('Y')
insert into giftwrap(gift)
values('N')
--����ѡȡ��ע����
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


--��һ������orders����
--���õ�ǰ�������Ϊ��һ�����һ���������
set @lastno = (select top 1 cOrderNo
               from Orders
               order by cOrderNo desc);
set @i = 0;
set @no = @lastno + 1;
--���õ�ǰʱ��Ϊ��һ�����һ����¼��ʱ��
set @dorderdate = (select top 1 dOrderDate
                    from Orders
                    order by dOrderDate desc);


--ѭ�����1000������
while(@i < 1000)                
begin

--����orders
--����orderno
set @corderno = right('000000'+convert(varchar(6),@no),6);
--�������ڣ�����룩
set @dorderdate = dateadd(dd,round(rand()*2,0),@dorderdate);
set @dorderdate = dateadd(ss,round(rand()*5000+1,0),@dorderdate);
--���ʱ�� > ��ǰʱ�䣬������Ϊ��ǰʱ��
if(@dorderdate > GETDATE())
begin
set @dorderdate = GETDATE();
end;
--�����ȡcartid
set @ccartid = (select  top 1 cCartId          
                from ShoppingCart
		        order by NEWID());
--�����ȡcShopperId
set @cshopperid = (select  top 1 cShopperId       
                   from Shopper
		           order by NEWID());
--��������
insert into Orders(cOrderNo,dOrderDate,cCartId,cShopperId)
values(@corderno,@dorderdate,@ccartid,@cshopperid)

--����orderdetail
set @j = 0;
--����toyid��
if exists(select * from sysobjects where name = 'toyid')
drop table toyid
select  top 10 cToyId
into toyid     
from Toys
order by NEWID()

--ѭ��
set @totalweight = 0;
set @mgiftwrapcharges = 0;
set @mtotalcost = 0;
--�������1-3��orderdetail��¼
while(@j < round(rand()*2+1,0))
begin
--��ȡorderno
set @corderno = right('000000'+convert(varchar(6),@no),6);
--�����ȡ���ظ���toyid
set @ctoyid = (select top 1 cToyId
                from toyid
				where cToyId not in (select top (@j) cToyId from toyid))
--�����ȡ����;
set @siqty = round(rand()*4+1,0);
--�����ȡ�Ƿ��а�װ
set @cgiftwrap = (select  top 1 gift     
                   from giftwrap
		           order by NEWID());
--�����ȡwrapperid
if(@cgiftwrap = 'Y')
begin
set @cwrapperid = (select  top 1 cWrapperId     
                   from Wrapper
		           order by NEWID());
end;
else begin
set @cwrapperid = null;
end;
--�����ȡmessage
set @vmessage = (select  top 1 mess
                  from message
		          order by NEWID());
--����toycost
set @mtoyrate = (select mToyRate
                  from Toys
				  where cToyId = @ctoyid);
set @mtoycost = @siqty * @mtoyrate;

--����
insert into OrderDetail(cOrderNo,cToyId,siQty,cGiftWrap,cWrapperId,vMessage,mToyCost)
values(@corderno,@ctoyid,@siqty,@cgiftwrap,@cwrapperid,@vmessage,@mtoycost)

--���㶩������
set @sitoyweight = (select siToyWeight
                    from Toys
				    where cToyId = @ctoyid);
set @totalweight += @sitoyweight * @siqty;

--����giftwrappercharges
if(@cgiftwrap = 'Y')
begin
set @mwrapperrate = (select mWrapperRate
                     from Wrapper
				     where cWrapperId = @cwrapperid);
set @mgiftwrapcharges +=  @siqty * @mwrapperrate;
end;


--��������߼۸�
set @mtotalcost += @mtoycost;

--����pickofmonth
set @month = (select month(dOrderDate)
		      from Orders
		      where cOrderNo = @corderno)
set @year = (select year(dOrderDate)
		      from Orders
		      where cOrderNo = @corderno)
--������ڵ�ǰ���¼�¼�������
if exists(select * 
          from PickOfMonth
		  where cToyId = @ctoyid and siMonth = @month and iYear = @year)
begin
update PickOfMonth
set iTotalSold = iTotalSold + @siqty 
where cToyId = @ctoyid and siMonth = @month and iYear = @year;
end;
--��������ڵ�ǰ���¼�¼��������
else begin
insert PickOfMonth(cToyId,siMonth,iYear,iTotalSold)
values(@ctoyid,@month,@year,@siqty)
end;
--j�Լ�
set @j += 1;
end;

--�ٴβ���orders
--���ҹ���˰��
set @cshippingmodeid = (select top 1 cModeId
                        from ShippingMode
				        order by NEWID());
set @ccountryid = (select cCountryId
                   from Shopper
				   where cShopperId = @cshopperid);
set @mrateperpound = (select mRatePerPound
                   from ShippingRate
				   where cModeId = @cshippingmodeid and cCountryID = @ccountryid);

--����shippingcharges
set @mshippingcharges = @mrateperpound * @totalweight;

--��������
set @corderprocessed = 'Y';

--�����ܼ�
set @mtotalcost += @mshippingcharges + @mgiftwrapcharges;

--����dexpdeldate��ʹ��ȶ���ʱ���������һ��ֵ
set @dexpdeldate = @dorderdate;
set @dexpdeldate = dateadd(dd,round(rand()*2,0),@dexpdeldate);
set @dexpdeldate = dateadd(ss,round(rand()*5000+1,0),@dexpdeldate);
--���ʱ�� > ��ǰʱ�䣬������Ϊ��ǰʱ��
if(@dexpdeldate > GETDATE())
begin
set @dexpdeldate = GETDATE();
end;
--�ڶ��β�������
update Orders set cShippingModeId = @cshippingmodeid,
mShippingCharges = @mshippingcharges,
mGiftWrapCharges = @mgiftwrapcharges,
cOrderProcessed = @corderprocessed,
mTotalCost = @mtotalcost,
dExpDelDate = @dexpdeldate
where cOrderNo = @corderno;

--�Լ�
set @i += 1;
set @no += 1;
end;







