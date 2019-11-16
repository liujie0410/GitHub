select vFirstName,vLastName,vEmailId
from Shopper 
/*查找条件为洲名为California或者Florida*/
where cState='California' or cState='Florida'