/*创建视图order_month_summary，视图中的字段包括月份、该月的订单总量和该月的订单总金额*/
create view order_month_summary(month, allqty,alldollars)
as select month,sum(qty) as allqty,sum(dollars*qty) as alldollars
from Orders
group by month