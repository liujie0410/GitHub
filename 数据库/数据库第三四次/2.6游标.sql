/*��дһ��������ʾÿ��Ķ���״̬��
�������Ķ���ֵ�ܺϴ���150������ʾ��High sales��,������ʾ��Low sales����
Ҫ���г����ڡ�����״̬�Ͷ����ܼ�ֵ��*/

/*
--���Ҷ������ڡ�״̬��������ֵ������ordertable��
select dOrderDate,sum(mTotalCost) as totalcost
into ordertable 
from Orders
group by dOrderDate
select * from ordertable*/

--����������洢�α��ȡ������
declare @date varchar(20)
declare @cost money

--�����α�
declare mycursor cursor for
select dOrderDate,TotalCost 
from ordertable
--���α�
open mycursor
--�ƶ��α���ȡ����
fetch mycursor into @date,@cost
print'       ����           ����״̬   �����ܼ�ֵ'
--���α��ȡ��һ�����ݳɹ�ʱ
while(@@fetch_status=0)
begin
--�������״̬
 if(@cost>150)
   print @date+'    '+'High Sales'+'    '+cast(@cost as varchar(10))
 else
   print @date+'    '+'Low Sales'+'    '+cast(@cost as varchar(10))
--������ȡ��һ������
fetch mycursor into @date,@cost
end
close mycursor
--ɾ���α�ʹ��
deallocate mycursor

