/*Orders����GlobalToyz���ݿ����һ�ź��ĵı������ű��������κθ��¶���������ɾ���ģ�����Ҫ��¼�����������ݿ���ƣ�Audit���Ļ���˼�롣
Ҫ�����һ�ű�洢��Orders��ĸ��²��������������ߡ�����ʱ�䡢�������͡�����ǰ�����ݡ����º�����ݡ���ƴ�����ʵ�ֶ�Orders�����ơ�*/

--����changelog��¼���µĶ���
create table changelog(
logid int not null identity(1,1),
operate varchar(10),               --�������ͣ�insert,delete,update
cOrderNo int not null,                      --Orders������
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
login_name varchar(100),           -- ��¼��  
prog_name varchar(100),            -- ������    
UDate datetime                     -- ��������ʱ��  
)

go
--�������Լ��
alter table changelog add primary key (cOrderNo)
go

--����������
create trigger changetrig
on Orders after update,insert,delete
as 
begin
   --��¼�ӿͻ��˷��͵����һ�����
   declare @di table(et varchar(200),pt varchar(200),ei varchar(max))
   insert into @di exec('dbcc inputbuffer(@@spid)')
   --�жϲ�������
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



 

