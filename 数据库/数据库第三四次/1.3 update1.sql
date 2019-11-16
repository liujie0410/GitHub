/*在OrderDetail上定义一个触发器，当向OrderDetail表中新增一条记录时，自动修改Toys表中玩具的库存数量（siToyQoh）*/

create trigger update3 on OrderDetail
after insert /*当向OrderDetail表中新增一条记录时*/
as
declare @ctoyid char(6)
declare @siqty int
select @ctoyid=inserted.cToyId,@siqty=inserted.siQty
from inserted
update Toys
--将对应的ctoyid的sitoyqoh减去新增的数量
set siToyQoh=siToyQoh-@siqty
where cToyId=@ctoyid
go
