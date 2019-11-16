/*对dollars>500的订单的客户，将其discnt+2*/
update Customers /*在Cusomers表中修改*/
set  discnt= discnt+2
from Customers inner join Orders  /*Customers和Orders表内连接*/
on Customers.cid=Orders.cid/*连接条件为cid相同*/
where  dollars>500 
