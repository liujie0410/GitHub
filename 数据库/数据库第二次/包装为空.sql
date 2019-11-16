select vToyName
from Toys
where cToyId
in (select cToyId from OrderDetail where  cWrapperId is NULL)/*子查询，当包装为空时*/