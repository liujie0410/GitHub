/*��GlobalToyz���ݿ��ﴴ��һ���û����û���Ϊuser_xxxx�����ѧ�ţ���ͨ����ͼ���Ƹ��û�ֻ�ܷ���Orders����2017����ǰ������*/
--������ͼ

/*create view seeview
as
select *
from Orders
--ȡdOrderDate�����Ϊ2017
where convert(char(4),dOrderDate,121)='2017'*/

--������½
create login user_0919170119 with password='123456'
--�����û�
create user user_0919170119
--������ͼ����Ȩ��
grant select on seeview to user_0919170119
