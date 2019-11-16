#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h> 
#include<windows.h>


/*��������*/ 
void menu();
void menu_2();
int save();
int input(); 
void search();
int insert();
void clean();
void alter();
void print(int j);
int N; 
FILE *fp;


/*����ṹ��*/ 
struct teacher
{
    	int id;
	    char name[10];
	    char sex[10];
	    char profession[10];
	    int num;
	    int class_num;
	    struct course
	    {
	      int theory;
	      int experiment;
	      float total;
	    }cour[10];
}teacher[100];


/*������*/ 
int main()
{
     menu();
	return 0;
}
 
 
 /*���˵�*/ 	
void menu()
{
	int choice;
      printf("\n\t           ��ӭʹ�ý�ʦ����������ϵͳ\n\n");
	  printf("\t��*************************************************��\n\n");
	  printf("\t��\t\t(1)��ʦ��Ϣ¼��\t\t\t    ��\n\n");
	  printf("\t��\t\t(2)��ʦ��Ϣ����\t\t\t    ��\n\n");
	  printf("\t��\t\t(3)��ʦ�ۺ���Ϣ��ѯ\t\t    ��\n\n");
      printf("\t��\t\t(4)�˳�����\t\t\t    ��\n\n");
	  printf("\t��*************************************************��\n\n");
	  printf("��������ѡ��Ĺ�����ţ�");
	  scanf("%d",&choice);
	  switch(choice)
	  {
	     case 1:input();break;
	     case 2:menu_2();break;
		 case 3:search();break;
	     case 4:break;
      }
}


/*�����˵�*/ 
void menu_2()
{
	system("cls");
	int n;
	printf("\n\n\t           ��ʦ��Ϣ����\n");
	printf("\t��*****************************��\n");
	printf("\t��\t(1)��������\t        ��\n");
	printf("\t��\t(2)�޸�����\t        ��\n"); 
    printf("\t��\t(3)ɾ������\t        ��\n");
    printf("\t��\t(4)�����ѯϵͳ\t        ��\n");
    printf("\t��\t(5)�˳�����\t        ��\n");
    printf("\t��*****************************��\n");
    printf("��������ѡ��Ĺ�����ţ�");
    scanf("%d",&n);
    switch(n)
	  {
	     case 1:insert();break;
	     case 2:alter();break;
		 case 3:clean();break;
		 case 4:search();break;
		 case 5:break;
	 }
}
 
/*�����ļ�*/
int save()
{
   int j;
  fp=fopen("teacher.txt","w+");
  if (fp==NULL)
      printf("�޷����ļ�.");
  if(N!=0)
  {
    for(j=0;j<100;j++)
      fwrite(&teacher[j],sizeof(struct teacher),1,fp);
  }
 fclose(fp);
}
 
/*¼����Ϣ*/ 
int input()
{
    int i,j;
    int b;
    float all_total=0;
   	  printf("���������ʦ��Ŀ��");
   	  scanf("%d",&N);
   	  if(N>=100)
   	  printf("���󣡳����޶���Ŀ��\n");
    for(j=0;j<N;j++)
   	{
		printf("\n��ʦ���:NO.%d\n",j+1);
		printf("���������ʦ���ţ�");
		scanf("%d",&teacher[j].id);
		printf("���������ʦ����:");
		scanf("%s",&teacher[j].name);
		printf("���������ʦ�Ա�");
		scanf("%s",&teacher[j].sex);
		printf("���������ʦְ�ƣ�");
		scanf("%s",&teacher[j].profession);
		printf("���������ʦ�γ���Ŀ��");
		scanf("%d",&teacher[j].num);
		printf("�������������༶��Ŀ(>=2):");
		scanf("%d",&teacher[j].class_num);
		save();
		if(teacher[j].class_num<2)
		printf("���������༶��ĿӦ����2!");
		for(i=0;i<teacher[j].num;i++)
		{
			printf("�γ���Ϣ����ţ�NO.%d\n",i+1);
			printf("�����������ۿ�ʱ:");
			scanf("%d",&teacher[j].cour[i].theory);
			printf("��������ʵ���ʱ:");
			scanf("%d",&teacher[j].cour[i].experiment);
		    if(teacher[j].class_num==2)
		    teacher[j].cour[i].total=1.5*(teacher[j].cour[i].theory+teacher[j].cour[i].experiment);
		    if(teacher[j].class_num==3)
			teacher[j].cour[i].total=2*(teacher[j].cour[i].theory+teacher[j].cour[i].experiment);
	        if(teacher[j].class_num==4)
			teacher[j].cour[i].total=2.5*(teacher[j].cour[i].theory+teacher[j].cour[i].experiment);
	    	all_total=all_total+teacher[j].cour[i].total;
		}   
	    printf("��ʦ������Ϊ��%f\n",all_total);
   }
   printf("�밴1����¼����Ϣ������棺");
   scanf("%d",&b);
   if(b=1) 
   menu_2();
}


/*������Ϣ*/
void search()
{
	int j;
	int a;
	float all_total=0;
	char name[10];
	printf("�������ʦ������\n");
	scanf("%s",name);
	for(j=0;j<100;j++)
	{
	   if(strcmp(name,teacher[j].name)==0)
		  print(j); 
    }
}


/*��ʾ��Ϣ*/
void print(int j) 
{
    int a;
    fp=fopen("teacher.txt","r");
    if (fp==NULL)
      printf("�޷����ļ�.");
  if(N!=0)
  {
      fread(teacher,sizeof(struct teacher),1,fp);
      printf("����Ϊ��Ҫ���ҵĽ�ʦ��Ϣ\n");
      printf("************************\n");
      printf("����ʦ���ţ�%d\n",teacher[j].id);
      printf("����ʦ������%s\n",teacher[j].name);
      printf("����ʦ�Ա�%s\n",teacher[j].sex);
	  printf("����ʦְ�ƣ�%s\n",teacher[j].profession);
	  printf("���γ���Ŀ��%d\n",teacher[j].num);
      printf("���༶��Ŀ��%d\n",teacher[j].class_num);
  }
 fclose(fp);
 printf("�밴1�ص�����˵�");
 scanf("%d",&a);
 if(a==1)
 menu_2();
}


/*������Ϣ*/ 
int insert()
{
    int i,j; 
    int n;
    int b;
    float all_total=0;
    printf("��������Ҫ��ӵĽ�ʦ��Ŀ��");
   	scanf("%d",&n);
	for(j=0;j<N+n-1;j++)
	{
		printf("\n��ʦ���:NO.%d\n",N+j+1);
		printf("���������ʦ���ţ�");
		scanf("%d",&teacher[N+j].id);
		printf("���������ʦ����:");
		scanf("%s",&teacher[N+j].name);
		printf("���������ʦ�Ա�");
		scanf("%s",&teacher[N+j].sex);
		printf("���������ʦְ�ƣ�");
		scanf("%s",&teacher[N+j].profession);
		printf("���������ʦ�γ���Ŀ��");
		scanf("%d",&teacher[N+j].num);
		printf("�������������༶��Ŀ(>=2):");
		scanf("%d",&teacher[N+j].class_num);
		save();
		if(teacher[N+j].class_num<2)
		printf("���������༶��ĿӦ����2!");
		for(i=0;i<teacher[N+j].num;i++)
		{
			printf("�γ���Ϣ����ţ�NO.%d\n",i+1);
			printf("�����������ۿ�ʱ��");
			scanf("%d",&teacher[N+j].cour[i].theory);
			printf("��������ʵ���ʱ��");
			scanf("%d",&teacher[N+j].cour[i].experiment);
		    if(teacher[N+j].class_num==2)
		    teacher[N+j].cour[i].total=1.5*(teacher[N+j].cour[i].theory+teacher[N+j].cour[i].experiment);
		    if(teacher[N+j].class_num==3)
			teacher[N+j].cour[i].total=2*(teacher[N+j].cour[i].theory+teacher[N+j].cour[i].experiment);
	        if(teacher[j].class_num==4)
			teacher[N+j].cour[i].total=2.5*(teacher[N+j].cour[i].theory+teacher[N+j].cour[i].experiment);
	    	all_total=all_total+teacher[N+j].cour[i].total;
		}   
	    printf("����ʦ������Ϊ��%f\n",all_total);
   }
    printf("�밴1����¼����Ϣ������棺");
    scanf("%d",&b);
    if(b=1) 
    menu_2();
}


/*ɾ����Ϣ*/
void clean()
{
  int i,j; 
  int m;
  char name[20];
  printf("��������Ҫɾ����Ϣ�Ľ�ʦ������");
  scanf("%s",name);
  for(j=0;j<100;j++)
  {
	if(strcmp(teacher[j].name,name)==0)
	{
	  strcpy(teacher[j].name,teacher[j+1].name);
	  teacher[j].id=teacher[j+1].id;	
	  strcpy(teacher[j].sex,teacher[j+1].sex);
	  strcpy(teacher[j].profession,teacher[j+1].profession);
	  teacher[j].num=teacher[j+1].num;
	  teacher[j].class_num=teacher[j+1].class_num;
	  save();
	  for(i=0;i<teacher[j].num;i++)
	  {
	  teacher[j].cour[i].theory=teacher[j+1].cour[i+1].theory;
	  teacher[j].cour[i].experiment=teacher[j+1].cour[i+1].experiment;
      }  
    }
  } 
   printf("�밴1����¼����Ϣ������棺");
   scanf("%d",&m);
   if(m=1) 
   menu_2();
} 


/*�޸���Ϣ*/
void alter()
{
	int i,j;
	int k;
	int s; 
	char name[20];
	printf("��������Ҫ�޸���Ϣ�Ľ�ʦ������");
	scanf("%s",name);
	for(j=0;j<100;j++)
	{
		if(strcmp(teacher[j].name,name)==0)
       {
		  printf("\n*************************\n");
	      printf("*(1)��ʦ����\t\t*\n");
	      printf("*(2)��ʦ�Ա�\t\t*\n");
	      printf("*(3)��ʦְ��\t\t*\n");
	      printf("*(4)�γ���Ŀ\t\t*\n");
	      printf("*(5)�༶��Ŀ\t\t*\n");
	      printf("*(6)���ۿ�ʱ\t\t*\n");
	      printf("*(7)ʵ���ʱ\t\t*\n");
	      printf("*************************\n");
	      printf("��������Ҫ�޸���Ϣ����ţ�\n");
	      scanf("%d",&k);
	      switch(k)
	      {
			 case 1:printf("���������ʦ����:\n");
		            scanf("%d",&teacher[j].id);
		            break;
		     case 2:printf("���������ʦ�Ա�:\n");
		            scanf("%s",&teacher[j].sex);
		            break;
		     case 3:printf("���������ʦְ��:\n");
		            scanf("%s",&teacher[j].profession);
		            break;
		     case 4:printf("��������γ���Ŀ:\n");
		            scanf("%s",&teacher[j].num);
		            break;
		     case 5:printf("��������༶��Ŀ:\n");
		            scanf("%s",&teacher[j].class_num);
		            break;
		     case 6:printf("�����������ۿ�ʱ:\n");
		            for(j=0;i<teacher[j].num;i++);
		            scanf("%s",&teacher[j].cour[i].theory);
		            break;  
		     case 7:printf("��������ʵ���ʱ:\n");
		            for(i=0;i<teacher[j].num;i++);
		            scanf("%s",&teacher[j].cour[i].experiment);
		            break; 
		   }
	   }
   }
   save();
   printf("�밴1����¼����Ϣ������棺");
   scanf("%d",&s);
   if(s=1) 
   menu_2();
}
 
   


    
