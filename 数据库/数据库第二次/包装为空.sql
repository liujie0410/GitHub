select vToyName
from Toys
where cToyId
in (select cToyId from OrderDetail where  cWrapperId is NULL)/*�Ӳ�ѯ������װΪ��ʱ*/