/*����һ����ΪprcCharges�Ĵ洢���̣�������ĳ�������ŵ�װ�˷��úͰ�װ����*/
create proc prcCharges 
( @non char(6),@shipcharges money output,@giftcharges money output
 )
as
select @shipcharges=mShippingCharges,@giftcharges=mGiftWrapCharges
from Orders
where @non=cOrderNo
go

