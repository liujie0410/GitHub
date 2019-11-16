/*用datediff函数求两段时间相差的天数*/
select cOrderNo,dShipmentDate,dActualDeliveryDate,Days_in_Transit=datediff(day,dShipmentDate,dActualDeliveryDate)  
from Shipment