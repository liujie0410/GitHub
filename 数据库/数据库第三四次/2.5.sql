/*
��������ȷ�϶���ʱ��Ӧ�ð�������Ĳ��裺
��1�������µĶ����ţ�Ҫ�󴴽�һ���洢���̣����ڲ����¶����ţ���
��2�������ţ���ǰ���ڣ����ﳵID���͹�����IDӦ�üӵ�Orders���С�
��3�������ţ����ID������Ӧ�ӵ�OrderDetail���С�
��4����OrderDetail���и�����߳ɱ�������ʾ��Toy cost = Quantity * Toy Rate����
��5����ShoppingCart���н������ѹ�������ɾ����
���������趨��Ϊһ�����񡣱�дһ�������Թ��ﳵID�͹�����IDΪ������ʵ���������
����ʾ��������Ҫ�޸ı�ShoppingCart�Ľṹ���ڱ�������һ���ֶΡ�Status�������ֶ�ȡֵΪ1����ʾ�����Ϊ�����¶���ʱҪ�������ߣ�������һЩģ�����ݡ���*/

/*
--���������¶����ŵĴ洢����
create procedure updateorderno
@orderno char(6) output
as
--�ҵ������������Ķ�����
select @orderno=max(cOrderNo) from Orders
--��case�Բ�ͬ�׶ε�orderno���£����ָ�ʽһ��
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

--�����洢����
create procedure prcorder (@cartid char(6) output,@shopperid char(6) output)
as
--��������
begin transaction
--�������
declare @orderno char(6),@orderno1 char(6),@toyid char(6),@qty char(6)
--ִ�д洢����updateorderno
exec updateorderno @orderno output
--��ѯ�ǿյ�orderno
select @orderno1 =isnull(convert(nvarchar,@orderno),'null')
--������tab1�����������Ķ����Ķ����š����ﳵid��������id���µ�ʱ��������
create table tab1 (orderno char(6),cartid char(6),shopperid char(6),orderdate datetime)
insert into tab1 (orderno,cartid,shopperid,orderdate) values(@orderno1,@cartid,@shopperid,getdate())
--����һ��Ӱ���������Ϊ0����ص����״̬
if @@rowcount=0
begin 
rollback transaction
return
end

--��orders���в�����Ϣ
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

--��ordersdetail���в�����Ϣ
insert into OrderDetail(cOrderNo,cToyId,siQty)
values(@orderno1,@toyid,@qty)
--���±�oderdetil
update OrderDetail
set mToyCost=siQty*mToyRate
from OrderDetail,Toys
if @@rowcount=0
begin 
rollback transaction
return
end

--��ShoppingCart���н������ѹ�������ɾ��
delete 
from ShoppingCart
where cCartId=@cartid
if @@rowcount=0
begin 
rollback transaction
return
end

--�ύ���񣬱��浽���ݿ���
commit transaction
go
