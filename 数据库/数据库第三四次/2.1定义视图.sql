/*����һ����ͼ�����������ı�š�ʱ�䡢����Լ��ջ��˵����������Ҵ���͹������ơ�*/
create view orderdetails
as
select Orders.cOrderNo,dOrderDate,mTotalCost,vFirstName,vLastName,Recipient.cCountryId,cCountry
from Orders,Recipient,Country
where Orders.cOrderNo=Recipient.cOrderNo and Recipient.cCountryId=Country.cCountryId