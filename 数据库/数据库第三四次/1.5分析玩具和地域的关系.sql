/*��д���룬������ߺ͵���Ĺ�ϵ�������ĸ����еĹ����߶���һ�֡���һ�����һ��Ʒ�Ƶ���߸�����Ȥ��
������Ǹ����ŵ���Ŀ��ͬѧ�ǿ��԰����Լ������Ӳ�ͬ�ĽǶȽ��з�����*/


select cCity,t1.cToyId,sum(t1.siQty) as siQty
from
--�Ƚ�OrderDetail�� Orders����cOrderNo��ͬ�����ӣ�ȡ��cToyId,siQty,cShopperId ��������Ϊt1
(select cToyId,siQty,cShopperId 
from OrderDetail inner join Orders
on OrderDetail.cOrderNo=Orders.cOrderNo) as t1
--�ٽ�t1��Shopper����cShopperId������
inner join Shopper
on t1.cShopperId=Shopper.cShopperId
--��ĳ���а���ĳ����߷�����ö�������
group by cCity,cToyId
--��ĳ���е���߶�������������������
order by cCity,siQty desc
