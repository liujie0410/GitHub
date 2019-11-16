select cOrderNo,cToyId,mToyCost
from OrderDetail
order by cOrderNo
compute sum(mToyCost) by cOrderNo