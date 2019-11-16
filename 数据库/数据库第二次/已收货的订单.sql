select cOrderNo,dOrderDate
from Orders where cOrderNo
in (select cOrderNo from Shipment where dActualDeliveryDate is NOT NULL)