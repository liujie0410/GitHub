/*����һ����ΪprcHandlingCharges�Ĺ��̣������ն����Ų���ʾ��Ӫ���á�PrchandlingCharges����Ӧʹ��prcCharges�������õ�װ�˷Ѻ���Ʒ��װ�ѡ�
����ʾ����Ӫ����=װ�˷�+��Ʒ��װ�ѣ�*/

create procedure prcHandlingCharges
(@non char(6),@cost money output)
as
declare @ship money
declare @gift money
--ִ�д洢����prcCharges
exec prcCharges  @non,@ship output,@gift output
set @cost=@ship+@gift
go