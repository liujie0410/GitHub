alter table Toys nocheck constraint all /*½â³ýÍâ¼ü*/
alter table ShoppingCart nocheck  constraint all
alter table OrderDetail nocheck  constraint all
alter table PickOfMonth nocheck  constraint all
delete
from Toys
where cBrandId=(select cBrandId from ToyBrand where cBrandName='Largo')
alter table Toys check  constraint all  /*»Ö¸´Íâ¼ü*/
alter table ShoppingCart check  constraint all
alter table OrderDetail check  constraint all
alter table PickOfMonth check  constraint all
