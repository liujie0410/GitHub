#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h> 
#include<windows.h>


/*函数声明*/ 
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


/*定义结构体*/ 
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


/*主函数*/ 
int main()
{
     menu();
	return 0;
}
 
 
 /*主菜单*/ 	
void menu()
{
	int choice;
      printf("\n\t           欢迎使用教师工作量管理系统\n\n");
	  printf("\t◤*************************************************◥\n\n");
	  printf("\t▎\t\t(1)教师信息录入\t\t\t    ▎\n\n");
	  printf("\t▎\t\t(2)教师信息管理\t\t\t    ▎\n\n");
	  printf("\t▎\t\t(3)教师综合信息查询\t\t    ▎\n\n");
      printf("\t▎\t\t(4)退出程序\t\t\t    ▎\n\n");
	  printf("\t◣*************************************************◢\n\n");
	  printf("请输入您选择的功能序号：");
	  scanf("%d",&choice);
	  switch(choice)
	  {
	     case 1:input();break;
	     case 2:menu_2();break;
		 case 3:search();break;
	     case 4:break;
      }
}


/*二级菜单*/ 
void menu_2()
{
	system("cls");
	int n;
	printf("\n\n\t           教师信息管理\n");
	printf("\t◤*****************************◥\n");
	printf("\t▎\t(1)插入数据\t        ▎\n");
	printf("\t▎\t(2)修改数据\t        ▎\n"); 
    printf("\t▎\t(3)删除数据\t        ▎\n");
    printf("\t▎\t(4)进入查询系统\t        ▎\n");
    printf("\t▎\t(5)退出程序\t        ▎\n");
    printf("\t◣*****************************◢\n");
    printf("请输入您选择的功能序号：");
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
 
/*保存文件*/
int save()
{
   int j;
  fp=fopen("teacher.txt","w+");
  if (fp==NULL)
      printf("无法打开文件.");
  if(N!=0)
  {
    for(j=0;j<100;j++)
      fwrite(&teacher[j],sizeof(struct teacher),1,fp);
  }
 fclose(fp);
}
 
/*录入信息*/ 
int input()
{
    int i,j;
    int b;
    float all_total=0;
   	  printf("▲请输入教师数目：");
   	  scanf("%d",&N);
   	  if(N>=100)
   	  printf("错误！超出限定数目！\n");
    for(j=0;j<N;j++)
   	{
		printf("\n教师序号:NO.%d\n",j+1);
		printf("▲请输入教师工号：");
		scanf("%d",&teacher[j].id);
		printf("▲请输入教师姓名:");
		scanf("%s",&teacher[j].name);
		printf("▲请输入教师性别：");
		scanf("%s",&teacher[j].sex);
		printf("▲请输入教师职称：");
		scanf("%s",&teacher[j].profession);
		printf("▲请输入教师课程数目：");
		scanf("%d",&teacher[j].num);
		printf("▲请输入所带班级数目(>=2):");
		scanf("%d",&teacher[j].class_num);
		save();
		if(teacher[j].class_num<2)
		printf("错误！所带班级数目应超过2!");
		for(i=0;i<teacher[j].num;i++)
		{
			printf("课程信息的序号：NO.%d\n",i+1);
			printf("▲请输入理论课时:");
			scanf("%d",&teacher[j].cour[i].theory);
			printf("▲请输入实验课时:");
			scanf("%d",&teacher[j].cour[i].experiment);
		    if(teacher[j].class_num==2)
		    teacher[j].cour[i].total=1.5*(teacher[j].cour[i].theory+teacher[j].cour[i].experiment);
		    if(teacher[j].class_num==3)
			teacher[j].cour[i].total=2*(teacher[j].cour[i].theory+teacher[j].cour[i].experiment);
	        if(teacher[j].class_num==4)
			teacher[j].cour[i].total=2.5*(teacher[j].cour[i].theory+teacher[j].cour[i].experiment);
	    	all_total=all_total+teacher[j].cour[i].total;
		}   
	    printf("教师工作量为：%f\n",all_total);
   }
   printf("请按1进入录入信息管理界面：");
   scanf("%d",&b);
   if(b=1) 
   menu_2();
}


/*查找信息*/
void search()
{
	int j;
	int a;
	float all_total=0;
	char name[10];
	printf("请输入教师姓名：\n");
	scanf("%s",name);
	for(j=0;j<100;j++)
	{
	   if(strcmp(name,teacher[j].name)==0)
		  print(j); 
    }
}


/*显示信息*/
void print(int j) 
{
    int a;
    fp=fopen("teacher.txt","r");
    if (fp==NULL)
      printf("无法打开文件.");
  if(N!=0)
  {
      fread(teacher,sizeof(struct teacher),1,fp);
      printf("以下为您要查找的教师信息\n");
      printf("************************\n");
      printf("▲教师工号：%d\n",teacher[j].id);
      printf("▲教师姓名：%s\n",teacher[j].name);
      printf("▲教师性别：%s\n",teacher[j].sex);
	  printf("▲教师职称：%s\n",teacher[j].profession);
	  printf("▲课程数目：%d\n",teacher[j].num);
      printf("▲班级数目：%d\n",teacher[j].class_num);
  }
 fclose(fp);
 printf("请按1回到管理菜单");
 scanf("%d",&a);
 if(a==1)
 menu_2();
}


/*插入信息*/ 
int insert()
{
    int i,j; 
    int n;
    int b;
    float all_total=0;
    printf("请输入需要添加的教师数目：");
   	scanf("%d",&n);
	for(j=0;j<N+n-1;j++)
	{
		printf("\n教师序号:NO.%d\n",N+j+1);
		printf("▲请输入教师工号：");
		scanf("%d",&teacher[N+j].id);
		printf("▲请输入教师姓名:");
		scanf("%s",&teacher[N+j].name);
		printf("▲请输入教师性别：");
		scanf("%s",&teacher[N+j].sex);
		printf("▲请输入教师职称：");
		scanf("%s",&teacher[N+j].profession);
		printf("▲请输入教师课程数目：");
		scanf("%d",&teacher[N+j].num);
		printf("▲请输入所带班级数目(>=2):");
		scanf("%d",&teacher[N+j].class_num);
		save();
		if(teacher[N+j].class_num<2)
		printf("错误！所带班级数目应超过2!");
		for(i=0;i<teacher[N+j].num;i++)
		{
			printf("课程信息的序号：NO.%d\n",i+1);
			printf("▲请输入理论课时；");
			scanf("%d",&teacher[N+j].cour[i].theory);
			printf("▲请输入实验课时：");
			scanf("%d",&teacher[N+j].cour[i].experiment);
		    if(teacher[N+j].class_num==2)
		    teacher[N+j].cour[i].total=1.5*(teacher[N+j].cour[i].theory+teacher[N+j].cour[i].experiment);
		    if(teacher[N+j].class_num==3)
			teacher[N+j].cour[i].total=2*(teacher[N+j].cour[i].theory+teacher[N+j].cour[i].experiment);
	        if(teacher[j].class_num==4)
			teacher[N+j].cour[i].total=2.5*(teacher[N+j].cour[i].theory+teacher[N+j].cour[i].experiment);
	    	all_total=all_total+teacher[N+j].cour[i].total;
		}   
	    printf("▲教师工作量为：%f\n",all_total);
   }
    printf("请按1进入录入信息管理界面：");
    scanf("%d",&b);
    if(b=1) 
    menu_2();
}


/*删除信息*/
void clean()
{
  int i,j; 
  int m;
  char name[20];
  printf("请输入需要删除信息的教师姓名：");
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
   printf("请按1进入录入信息管理界面：");
   scanf("%d",&m);
   if(m=1) 
   menu_2();
} 


/*修改信息*/
void alter()
{
	int i,j;
	int k;
	int s; 
	char name[20];
	printf("请输入需要修改信息的教师姓名：");
	scanf("%s",name);
	for(j=0;j<100;j++)
	{
		if(strcmp(teacher[j].name,name)==0)
       {
		  printf("\n*************************\n");
	      printf("*(1)教师工号\t\t*\n");
	      printf("*(2)教师性别\t\t*\n");
	      printf("*(3)教师职称\t\t*\n");
	      printf("*(4)课程数目\t\t*\n");
	      printf("*(5)班级数目\t\t*\n");
	      printf("*(6)理论课时\t\t*\n");
	      printf("*(7)实验课时\t\t*\n");
	      printf("*************************\n");
	      printf("请输入需要修改信息的序号：\n");
	      scanf("%d",&k);
	      switch(k)
	      {
			 case 1:printf("▲请输入教师工号:\n");
		            scanf("%d",&teacher[j].id);
		            break;
		     case 2:printf("▲请输入教师性别:\n");
		            scanf("%s",&teacher[j].sex);
		            break;
		     case 3:printf("▲请输入教师职称:\n");
		            scanf("%s",&teacher[j].profession);
		            break;
		     case 4:printf("▲请输入课程数目:\n");
		            scanf("%s",&teacher[j].num);
		            break;
		     case 5:printf("▲请输入班级数目:\n");
		            scanf("%s",&teacher[j].class_num);
		            break;
		     case 6:printf("▲请输入理论课时:\n");
		            for(j=0;i<teacher[j].num;i++);
		            scanf("%s",&teacher[j].cour[i].theory);
		            break;  
		     case 7:printf("▲请输入实验课时:\n");
		            for(i=0;i<teacher[j].num;i++);
		            scanf("%s",&teacher[j].cour[i].experiment);
		            break; 
		   }
	   }
   }
   save();
   printf("请按1进入录入信息管理界面：");
   scanf("%d",&s);
   if(s=1) 
   menu_2();
}
 
   


    
