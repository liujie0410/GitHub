create table analysis(
city char(30),
toy char(6)
)


declare @ccity char(30)
declare @toyid char(6)
declare City cursor for
select cCity
from toy_siqty_city
open City
fetch City into @ccity
while(@@fetch_status=0)
begin
 insert into analysis(city)
 values(@ccity)
 declare Toy cursor for
 select top 1 cToyId from toy_siqty_city order by siQty desc
 open Toy
 fetch Toy into @toyid
 while(@@fetch_status=0)
 begin
 insert into analysis(toy)
 values(@toyid)
 end
end