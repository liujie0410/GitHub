select vFirstName,vLastName,vEmailId
from Shopper 
/*��������Ϊ����ΪCalifornia����Florida*/
where cState='California' or cState='Florida'