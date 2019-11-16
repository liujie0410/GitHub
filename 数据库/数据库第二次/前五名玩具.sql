/*用top5取出前5,sum计算总销售量*/
select top 5 cToyId,sum(iTotalSold) as total
from PickOfMonth
/*查找条件为年份是2016*/
where iYear='2016'
/*按照toyid分组销售总量*/
group by cToyId
/*按照销售量降序排列*/
order by total desc
