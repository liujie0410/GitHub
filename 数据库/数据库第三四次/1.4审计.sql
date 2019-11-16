/*Orders表是GlobalToyz数据库里的一张核心的表，对这张表上做的任何更新动作（增、删、改）都需要记录下来这是数据库审计（Audit）的基本思想。
要求设计一张表存储对Orders表的更新操作，包括操作者、操作时间、操作类型、更新前的数据、更新后的数据。设计触发器实现对Orders表的审计。*/

--建表changelog记录更新的动作
create table changelog(
logid int not null identity(1,1),
operate varchar(10),               --操作类型，insert,delete,update
cOrderNo int not null,                      --Orders表主键
dOrderDate_o date null,
dOrderDate_n date null,
cCartId_o char(6) null,
cCartId_n char(6) null,
cShopperId_o char(6) null,
cShopperId_n char(6) null,
cShippingModeId_o int null,
cShippingModeId_n int null,
mShippingCharges_o money null,
mShippingCharges_n money null,
mGiftWrapCharges_o money null,
mGiftWrapCharges_n money null,
cOrderProcessed_o char null,
cOrderProcessed_n char null,
mTotalCost_o money null,
mTotalCost_n money null,
dExpDelDate_o date null,
dExpDelDate_n date null,
spid int not null,                 -- spid  
login_name varchar(100),           -- 登录名  
prog_name varchar(100),            -- 程序名    
UDate datetime                     -- 操作日期时间  
)

go
--添加主键约束
alter table changelog add primary key (cOrderNo)
go

--建立触发器
create trigger changetrig
on Orders after update,insert,delete
as 
begin
   --记录从客户端发送的最后一个语句
   declare @di table(et varchar(200),pt varchar(200),ei varchar(max))
   insert into @di exec('dbcc inputbuffer(@@spid)')
   --判断操作类型
   declare @op varchar(10)
   select @op=case when exists(select 1 from inserted) and exists(select 1 from deleted)
                   then 'Update'
                   when exists(select 1 from inserted) and not exists(select 1 from deleted)
                   then 'Insert'
                   when not exists(select 1 from inserted) and exists(select 1 from deleted)
                   then 'Delete' end               
   if @op in('Update','Insert')
   begin
   insert into changelog(
   operate,cOrderNo,dOrderDate_o,dOrderDate_n,cCartId_o,cCartId_n,cShopperId_o,cShopperId_n,
   cShippingModeId_o,cShippingModeId_n,mShippingCharges_o,mShippingCharges_n,mGiftWrapCharges_o,mGiftWrapCharges_n,
   cOrderProcessed_o,cOrderProcessed_n,mTotalCost_o,mTotalCost_n,dExpDelDate_o,dExpDelDate_n,
   spid,login_name,prog_name,UDate)
   select @op, n.cOrderNo, o.dOrderDate,n.dOrderDate,o.cCartId,n.cCartId,o.cShopperId,n.cShopperId,
   o.cShippingModeId,n.cShippingModeId,o.mShippingCharges,n.mShippingCharges,o.mGiftWrapCharges,n.mGiftWrapCharges,
   o.cOrderProcessed,n.cOrderProcessed,o.mTotalCost,n.mTotalCost,o.dExpDelDate,n.dExpDelDate,
     @@spid,
       (select login_name from sys.dm_exec_sessions where session_id=@@spid),
       (select program_name from sys.dm_exec_sessions where session_id=@@spid),
       getdate()
     from inserted n
     left join deleted o on o.cOrderNo=n.cOrderNo
   end
   else
   begin
   insert into changelog(
   operate,cOrderNo,dOrderDate_o,dOrderDate_n,cCartId_o,cCartId_n,cShopperId_o,cShopperId_n,
   cShippingModeId_o,cShippingModeId_n,mShippingCharges_o,mShippingCharges_n,mGiftWrapCharges_o,mGiftWrapCharges_n,
   cOrderProcessed_o,cOrderProcessed_n,mTotalCost_o,mTotalCost_n,dExpDelDate_o,dExpDelDate_n,
   spid,login_name,prog_name,UDate)
   select @op,o.cOrderNo,
            o.dOrderDate,null,o.cCartId,null,o.cShopperId,null,o.cShippingModeId,null,o.mShippingCharges,null,
     o.mGiftWrapCharges,null,o.cOrderProcessed,null,o.mTotalCost,null,o.dExpDelDate,null,
       @@spid,
         (select login_name from sys.dm_exec_sessions where session_id=@@spid),
         (select program_name from sys.dm_exec_sessions where session_id=@@spid),
         getdate()
       from deleted o
   end
end
go



 

