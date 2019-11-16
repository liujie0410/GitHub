/*创建一个称为prcCharges的存储过程，它返回某个定单号的装运费用和包装费用*/
create proc prcCharges 
( @non char(6),@shipcharges money output,@giftcharges money output
 )
as
select @shipcharges=mShippingCharges,@giftcharges=mGiftWrapCharges
from Orders
where @non=cOrderNo
go

