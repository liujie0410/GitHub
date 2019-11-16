/*定义一个视图，包括定单的编号、时间、金额以及收货人的姓名、国家代码和国家名称。*/
create view orderdetails
as
select Orders.cOrderNo,dOrderDate,mTotalCost,vFirstName,vLastName,Recipient.cCountryId,cCountry
from Orders,Recipient,Country
where Orders.cOrderNo=Recipient.cOrderNo and Recipient.cCountryId=Country.cCountryId