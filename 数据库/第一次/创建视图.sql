/*������ͼorder_month_summary����ͼ�е��ֶΰ����·ݡ����µĶ��������͸��µĶ����ܽ��*/
create view order_month_summary(month, allqty,alldollars)
as select month,sum(qty) as allqty,sum(dollars*qty) as alldollars
from Orders
group by month