/*��top5ȡ��ǰ5,sum������������*/
select top 5 cToyId,sum(iTotalSold) as total
from PickOfMonth
/*��������Ϊ�����2016*/
where iYear='2016'
/*����toyid������������*/
group by cToyId
/*������������������*/
order by total desc
