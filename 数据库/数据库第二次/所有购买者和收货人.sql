select a.vFirstName,a.vLastName,a.vAddress,a.cCity,b.vFirstName,b.vLastName,b.vAddress,b.cCity   
from Shopper a,Recipient b,Orders c
where a.cShopperId=c.cShopperId and c.cOrderNO=b.cOrderNO
