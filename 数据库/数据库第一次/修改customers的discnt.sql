/*��dollars>500�Ķ����Ŀͻ�������discnt+2*/
update Customers /*��Cusomers�����޸�*/
set  discnt= discnt+2
from Customers inner join Orders  /*Customers��Orders��������*/
on Customers.cid=Orders.cid/*��������Ϊcid��ͬ*/
where  dollars>500 
