/*��dollars>500�Ŀͻ���discnt+2 */
update Customers /*��Customers���޸�����*/
set discnt=discnt+2
where 
(
  Customers.cid in (select Customers.cid
  from Orders,Customers  /*ѡ��orders��customers����cid��ͬ����dollars����500������*/
  where dollars>500 and Orders.cid=Customers.cid)
)