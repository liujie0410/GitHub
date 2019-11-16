/*将Orders中一月份的数据复制到表Orders_Jan*/

  select * /*投影所有列*/
  into Orders_Jan
  from Orders
  where month='Jan'/*选取满足条件的行*/

