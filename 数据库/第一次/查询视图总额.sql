/*��ѯorder_month_summary��ͼ�еĵ�һ���ȸ����·ݵĶ��������Ͷ����ܽ��*/
select sum(allqty) as qtys,sum(alldollars) as moneys
from order_month_summary
where month='Jan' or month='Feb' or month='Mar'