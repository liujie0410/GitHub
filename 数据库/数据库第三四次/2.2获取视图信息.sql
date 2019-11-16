/*基于（1）中定义的视图，查询所有国家代码为‘001’的收货人的姓名和他们所下定单的笔数及定单的总金额*/

select concat(vFirstName,vLastName) as name,siQty,mToyCost
from orderdetails,OrderDetail
where cCountryId='001' and OrderDetail.cOrderNo=orderdetails.cOrderNo