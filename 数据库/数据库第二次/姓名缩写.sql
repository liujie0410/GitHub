/*��SUBSTRING������������ֶε�����ĸ*/
select (substring(vFirstName,1,1)+'.'+substring(vLastName,1,1)) as Initials,vFirstName,vLastName
from Shopper
