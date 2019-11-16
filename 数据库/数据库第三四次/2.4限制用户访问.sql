/*在GlobalToyz数据库里创建一个用户，用户名为user_xxxx（你的学号）。通过视图限制该用户只能访问Orders表中2017年以前的数据*/
--创建视图

/*create view seeview
as
select *
from Orders
--取dOrderDate的年份为2017
where convert(char(4),dOrderDate,121)='2017'*/

--创建登陆
create login user_0919170119 with password='123456'
--创建用户
create user user_0919170119
--分配视图访问权限
grant select on seeview to user_0919170119
