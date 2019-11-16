/*查询order_month_summary视图中的第一季度各个月份的订单总量和订单总金额*/
select sum(allqty) as qtys,sum(alldollars) as moneys
from order_month_summary
where month='Jan' or month='Feb' or month='Mar'