--declare @year int;
--declare @month smallint;
/*
--����pickofmonth
set @month = (select month(dOrderDate)
		      from Orders
		      where cOrderNo = @corderno)
set @year = (select year(dOrderDate)
		      from Orders
		      where cOrderNo = @corderno)
--������ڵ�ǰ���¼�¼�������
if exists(select * 
          from PickOfMonth
		  where cToyId = @ctoyid and siMonth = @month and iYear = @year)
begin
update PickOfMonth
set iTotalSold = iTotalSold + @siqty 
where cToyId = @ctoyid and siMonth = @month and iYear = @year;
end;
--��������ڵ�ǰ���¼�¼��������
else begin
insert PickOfMonth(cToyId,siMonth,iYear,iTotalSold)
values(@ctoyid,@month,@year,@siqty)
end;*/