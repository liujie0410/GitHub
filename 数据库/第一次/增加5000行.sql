/*向Orders增加5000条均分分布在各月的订单*/
declare @i int/*定义局部变量*/
set @i=1
declare @a int/*定义局部变量a，使添加的记录中的ordno逐一增加，保证每一条都是唯一的*/
set @a=1028
while @i<=5000/*运用while语句，循环添加5000条*/
begin
   if @i<=417 begin insert into Orders (ordno,month,cid,aid,pid,qty,dollars) /*if语句将5000条均分为12份，分别添加不同的数据*/
	                 values(@a,'Jan','C001','A01','P01','1000','450.00')
					 set @a=@a+1
			  end
   if (@i>417 and @i<=834) begin insert into Orders (ordno,month,cid,aid,pid,qty,dollars) 
	                 values(@a,'Feb','C002','A06','P03','600','540.00')
					 set @a=@a+1
			    end
   if (@i>834 and @i<=1252) begin insert into Orders (ordno,month,cid,aid,pid,qty,dollars) 
	                 values(@a,'Mar','C003','A05','P06','400','720.00')
					 set @a=@a+1
			    end
   if (@i>1252 and @i<=1668) begin insert into Orders (ordno,month,cid,aid,pid,qty,dollars) 
	                 values(@a,'Apr','C004','A05','P07','800','720.00')
					 set @a=@a+1
			    end
   if (@i>1668 and @i<=2058) begin insert into Orders (ordno,month,cid,aid,pid,qty,dollars) 
	                 values(@a,'May','C005','A03','P03','1000','880.00')
					 set @a=@a+1
			    end
   if (@i>2058 and @i<=2502) begin insert into Orders (ordno,month,cid,aid,pid,qty,dollars) 
	                 values(@a,'Jun','C006','A05','P08','700','600.00')
					 set @a=@a+1
			    end
   if (@i>2502 and @i<=2919) begin insert into Orders (ordno,month,cid,aid,pid,qty,dollars) 
	                 values(@a,'Jul','C001','A02','P02','900','40.00')
					 set @a=@a+1
			    end
   if (@i>2919 and @i<=3336) begin insert into Orders (ordno,month,cid,aid,pid,qty,dollars) 
	                 values(@a,'Aug','C002','A01','P04','120','110.00')
					 set @a=@a+1
			    end
   if (@i>3336 and @i<=3753) begin insert into Orders (ordno,month,cid,aid,pid,qty,dollars) 
	                 values(@a,'Sept','C003','A03','P05','300','300.00')
					 set @a=@a+1
			    end
   if (@i>3753 and @i<=4170) begin insert into Orders (ordno,month,cid,aid,pid,qty,dollars) 
	                 values(@a,'Oct','C004','A01','P07','600','280.00')
					 set @a=@a+1
			    end
   if (@i>4170 and @i<4587) begin insert into Orders (ordno,month,cid,aid,pid,qty,dollars) 
	                 values(@a,'Nov','C005','A04','P02','1200','500.00')
					 set @a=@a+1
			    end
   else begin insert into Orders (ordno,month,cid,aid,pid,qty,dollars) 
	                 values(@a,'Dec','C006','A02','P01','200','720.00')
					 set @a=@a+1
			    end
set @i=@i+1
end