/*���ڣ�1���ж������ͼ����ѯ���й��Ҵ���Ϊ��001�����ջ��˵��������������¶����ı������������ܽ��*/

select concat(vFirstName,vLastName) as name,siQty,mToyCost
from orderdetails,OrderDetail
where cCountryId='001' and OrderDetail.cOrderNo=orderdetails.cOrderNo