--declare @year int;
--declare @month smallint;
/*
--更新pickofmonth
set @month = (select month(dOrderDate)
		      from Orders
		      where cOrderNo = @corderno)
set @year = (select year(dOrderDate)
		      from Orders
		      where cOrderNo = @corderno)
--如果存在当前年月记录，则更新
if exists(select * 
          from PickOfMonth
		  where cToyId = @ctoyid and siMonth = @month and iYear = @year)
begin
update PickOfMonth
set iTotalSold = iTotalSold + @siqty 
where cToyId = @ctoyid and siMonth = @month and iYear = @year;
end;
--如果不存在当前年月记录，则增加
else begin
insert PickOfMonth(cToyId,siMonth,iYear,iTotalSold)
values(@ctoyid,@month,@year,@siqty)
end;*/