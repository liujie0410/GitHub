/*��OrderDetail�϶���һ��������������OrderDetail��������һ����¼ʱ���Զ��޸�Toys������ߵĿ��������siToyQoh��*/

create trigger update3 on OrderDetail
after insert /*����OrderDetail��������һ����¼ʱ*/
as
declare @ctoyid char(6)
declare @siqty int
select @ctoyid=inserted.cToyId,@siqty=inserted.siQty
from inserted
update Toys
--����Ӧ��ctoyid��sitoyqoh��ȥ����������
set siToyQoh=siToyQoh-@siqty
where cToyId=@ctoyid
go
