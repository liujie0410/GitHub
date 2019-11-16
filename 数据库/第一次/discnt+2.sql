/*对dollars>500的客户，discnt+2 */
update Customers /*对Customers表修改数据*/
set discnt=discnt+2
where 
(
  Customers.cid in (select Customers.cid
  from Orders,Customers  /*选出orders和customers表中cid相同，且dollars大于500的数据*/
  where dollars>500 and Orders.cid=Customers.cid)
)