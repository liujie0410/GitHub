/*用SUBSTRING方法可以求得字段的首字母*/
select (substring(vFirstName,1,1)+'.'+substring(vLastName,1,1)) as Initials,vFirstName,vLastName
from Shopper
