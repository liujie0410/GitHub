/*�������ݿ�*/
create database CAP/*���������ļ�*/
on
(
  name=CAP_Data,
  filename='\\Mac\Home\Desktop\OneDrive\���ݿ�\CAPData.mdf',
  size=50,/*��ʼ�洢�ռ��С*/
  maxsize=500,/*���洢�ռ�*/
  filegrowth=10/*�洢�ռ��Զ���ֵ��*/
)

log on/*������־�ļ�*/
(
  name=CAP_Log,
  filename='\\Mac\Home\Desktop\���ݿ�\OneDrive\CAPData.ldf',
  size=50,
  maxsize=500,
  filegrowth=10
)