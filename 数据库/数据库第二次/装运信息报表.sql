/*��datediff����������ʱ����������*/
select cOrderNo,dShipmentDate,dActualDeliveryDate,Days_in_Transit=datediff(day,dShipmentDate,dActualDeliveryDate)  
from Shipment