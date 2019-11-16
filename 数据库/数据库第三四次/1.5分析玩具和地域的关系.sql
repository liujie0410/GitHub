/*编写代码，分析玩具和地域的关系，例如哪个城市的购买者对哪一种、哪一类或哪一个品牌的玩具更有兴趣。
这道题是个开放的题目，同学们可以按照自己的理解从不同的角度进行分析。*/


select cCity,t1.cToyId,sum(t1.siQty) as siQty
from
--先将OrderDetail和 Orders按照cOrderNo相同内连接，取出cToyId,siQty,cShopperId ，整体作为t1
(select cToyId,siQty,cShopperId 
from OrderDetail inner join Orders
on OrderDetail.cOrderNo=Orders.cOrderNo) as t1
--再将t1和Shopper按照cShopperId内连接
inner join Shopper
on t1.cShopperId=Shopper.cShopperId
--对某城市按照某种玩具分组求得订购总数
group by cCity,cToyId
--对某城市的玩具订购按照数量降序排列
order by cCity,siQty desc
