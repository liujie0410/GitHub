select *
from Shopper
left join Orders
on Shopper.cShopperId=Orders.cShopperId
where Orders.cOrderNo is null