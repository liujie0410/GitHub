/*创建数据库*/
create database CAP/*创建数据文件*/
on
(
  name=CAP_Data,
  filename='\\Mac\Home\Desktop\OneDrive\数据库\CAPData.mdf',
  size=50,/*初始存储空间大小*/
  maxsize=500,/*最大存储空间*/
  filegrowth=10/*存储空间自动增值量*/
)

log on/*创建日志文件*/
(
  name=CAP_Log,
  filename='\\Mac\Home\Desktop\数据库\OneDrive\CAPData.ldf',
  size=50,
  maxsize=500,
  filegrowth=10
)