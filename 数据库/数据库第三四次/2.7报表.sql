/*���ڱ�Orders��Shopper�������и�ʽ���ɱ���
      ������ID   XXX    ����������   XXX    
      �����˵�ַ  XXXXXX 
      ������XXX  ����ʱ��XXX  �������XXX
      ������XXX  ����ʱ��XXX  �������XXX*/

--�������
declare @id char(6)
declare @name char(12)
declare @area char(30)
declare @no char(6)
declare @date1 date
declare @cost money

--�����α�1����ȡ��������Ϣ
declare cursor1 cursor for
select cShopperId ,concat(vFirstName,vLastName) ,vAddress 
from Shopper
--���α�1
open cursor1
--�ƶ��α�1��ȡ����
fetch cursor1 into @id,@name,@area
--���α��ȡ��һ�����ݳɹ�ʱ
while(@@fetch_status=0)
begin
--�����������Ϣ
print '������ID   '+ @id+'   '+'����������   '+@name
print '�����˵�ַ   '+@area
  
  --�����α�2����ȡ������Ϣ
  declare cursor2 cursor for
  select cOrderNo,dOrderDate,mTotalCost
  from Orders
  where @id=cShopperId
  --���α�2
  open cursor2
  --�ƶ��α�2��ȡ����
  fetch cursor2 into @no,@date1,@cost
  --���α��ȡ��һ�����ݳɹ�ʱ
  while(@@fetch_status=0)
  begin
  --���������Ϣ
  print '������   '+ @no+'   '+'����ʱ��   '+convert(varchar(100), @date1, 120)+ '�������   '+convert(varchar(6),@cost)
  --�α�2������ȡ��һ������
  fetch cursor2 into @no,@date1,@cost
  end
  close cursor2
  --ɾ���α�2ʹ��
  deallocate cursor2

--�α�1������ȡ��һ������
fetch cursor1 into @id,@name,@area
end
close cursor1
--ɾ���α�1ʹ��
deallocate cursor1 