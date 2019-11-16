/*从Orders表中选取month为Jan的存入表Orders*/

  select *  /*投影所有列*/
  into Orders_Jan
  from Orders
  where month='Jan'/*选取month=Jan的所有行*/
  