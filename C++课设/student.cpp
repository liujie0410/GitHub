#include<iostream>  
#include<iomanip>  
#include<cstring> 
#include<vector>
#include<set>
#include<stdlib.h> 
#include<fstream>
#include<conio.h> 
#include<windows.h>
using namespace std;

//声明
int N;
void menu(); 
void input();
int save();
void search();
void change();
void clean();
int add();
void paixv();
void print(int j);
 
//course结构体声明 
struct course
{
	public: 
    int course_num;//课程编号
	string course_name;//课程名称
	double credits;//学分 
	double ordinary;//平时成绩 
	double test;//考试成绩
	double sum;//综合成绩 
	string again;//重修情况 
};  

//student类声明
class student
{  
 public:
 	course cour[2];//结构体数组 
    long int num;  //学号 
    string name;  //姓名 
    double class1;  //班级 
    string sex; //性别
    double age;//年龄
	double home;//宿舍号码
	double phone;//电话号码 
	double all;//总成绩 
	double aver;//平均成绩
	friend void menu();
	friend void input();
	friend int save();
	friend void search();
	friend void change();
	friend void clean();
	friend int add();
	friend void paixv();
	friend void print(int j);
};

student stud[100];

//菜单
void menu()
{
	system("cls");
	int choice;
      cout<<"\n\t           欢迎使用学生成绩管理系统\n\n";
	  cout<<"\t◤*************************************************◥\n\n";
	  cout<<"\t▎\t\t(1)学生信息录入\t\t\t    ▎\n\n";
	  cout<<"\t▎\t\t(2)学生信息查询\t\t\t    ▎\n\n";
	  cout<<"\t▎\t\t(3)学生信息修改\t\t\t    ▎\n\n";
	  cout<<"\t▎\t\t(4)学生信息插入\t\t\t    ▎\n\n";
	  cout<<"\t▎\t\t(5)学生成绩排序\t\t\t    ▎\n\n";
	  cout<<"\t▎\t\t(6)学生信息删除\t\t\t    ▎\n\n";
      cout<<"\t▎\t\t(7)退出程序\t\t\t    ▎\n\n";
	  cout<<"\t◣*************************************************◢\n\n";
	  cout<<"请输入您选择的功能序号：";
	  cin>>choice;
	  switch(choice)
	  {
	     case 1:input();break;
	     case 2:search();break;
		 case 3:change();break;
		 case 4:add();break;
		 case 5:paixv();break;
		 case 6:clean();break;
	     case 7:break;
      }	
 } 
 
//主函数 
int main()
{
	menu();
	return 0;
}
 
//保存函数
int save()
{
	ofstream outfile("student.txt",ios::binary);
	if(!outfile)
	{
		cerr<<"找不到文件。"<<endl;
		abort();
	}
    for(int i=0;i<=100;i++)
     outfile.write((char*)&stud[i],sizeof(stud[i]));
	outfile.close();
	return 0;
} 

//录入函数 
void input()
{  
	 int i,j;
     int b;
   	 cout<<"需要输入的学生数目：";
   	 cin>>N; 
   	 if(N>=100)
   	 cout<<"错误！超出限定学生数目！\n";
   	for(j=0;j<N;j++)
   	{
	  cout <<"\n\t▲学生序号:NO."<<j+1<<endl;
      cout << "\t1.学生学号:";  
      cin >> stud[j].num;  
      cout << "\t2.学生姓名:";  
      cin >> stud[j].name;  
      cout << "\t3.学生班级:";  
      cin >> stud[j].class1; 
	  cout << "\t4.学生性别:";  
      cin >> stud[j].sex;  
      cout << "\t5.学生年龄:";  
      cin >> stud[j].age;  
      cout << "\t6.宿舍号码:";  
      cin >> stud[j].home;   
      cout << "\t7.电话号码:";  
      cin >> stud[j].phone;
	  cout << "\t8.选修课程信息:\n";
	  for(i=0;i<2;i++)
	  {
	  	cout<<"\n\t  *选修课序号:"<<i+1<<endl;
	  	cout<<"\t    (1)课程编号:";
		cin>>stud[j].cour[i].course_num;
		cout<<"\t    (2)课程名称:";
		cin>>stud[j].cour[i].course_name;
		cout<<"\t    (3)学分:";
		cin>>stud[j].cour[i].credits;
		cout<<"\t    (4)平时成绩:";
		cin>>stud[j].cour[i].ordinary;
		cout<<"\t    (5)考试成绩:";
		cin>>stud[j].cour[i].test;
		stud[j].cour[i].sum=0.5*(stud[j].cour[i].ordinary+stud[j].cour[i].test);		
		cout<<"\t    (6)综合成绩:"<<stud[j].cour[i].sum;
		cout<<"\n\t    (7)需要重修(是/否)：";
		cin>>stud[j].cour[i].again;
		stud[j].all+=stud[j].cour[i].sum;
		stud[j].aver=0.5*stud[j].all;		 
	  }
	  cout<<"\t9.平均成绩："<<stud[j].aver;
	  save();	  
    }
    cout<<"\n请按1返回主菜单";
	cin>>b;
	if(b==1)
	menu(); 
} 
   
//查询函数
void search()
{
	int b;
  	int j;
	long int num;
	  cout<<"请输入需要查找的学生学号：";
	  cin>>num;
	  for(j=0;j<N;j++)
	  {
	    if(num==stud[j].num) {print(j);} 
      }	 
          cout<<"\n请按1返回主菜单";
	cin>>b;
	if(b==1)
	menu(); 
}

//信息显示 
void print(int j)
{
	int i; 
      cout<<"\n以下为对应学生的信息";
      cout<<"\n****个人信息****";
      cout<<"\n学号："<<stud[j].num;
      cout<<"\n姓名："<<stud[j].name;
      cout<<"\n性别："<<stud[j].sex;
      cout<<"\n班级："<<stud[j].class1;
	  cout<<"\n年龄："<<stud[j].age;
	  cout<<"\n宿舍："<<stud[j].home;
      cout<<"\n电话："<<stud[j].phone;
      cout<<"\n平均成绩："<<stud[j].aver;
      cout<<"\n****选修信息****";
      for(i=0;i<2;i++)
      {
      	cout<<"\n▲课程序号："<<i+1;
      	cout<<"\n（1）课程编号："<<stud[j].cour[i].course_num;
      	cout<<"\n（2）课程名称："<<stud[j].cour[i].course_name;
      	cout<<"\n（3）课程学分："<<stud[j].cour[i].credits;
      	cout<<"\n（4）平时成绩："<<stud[j].cour[i].ordinary;
      	cout<<"\n（5）考试成绩："<<stud[j].cour[i].test;
      	cout<<"\n（6）综合成绩："<<stud[j].cour[i].sum;
      	cout<<"\n（7）是否重修："<<stud[j].cour[i].again;
	  }
	  cout<<"\n****************";
}
 
//修改函数
void change()
{
	int j;
	int k;
	int s;
	int m;
	int n; 
	string name;
	cout<<"请输入需要修改信息的学生姓名：";
	cin>>name;
	for(j=0;j<100;j++)
	{
		if(stud[j].name==name)
       {
       	  print(j); 
       	  cout<<"\n\n请选择您需要修改的信息对应的序号："; 
		  cout<<"\n*************************\n";
	      cout<<"*\t(1)学生学号\t*\n";
	      cout<<"*\t(2)学生姓名\t*\n";
	      cout<<"*\t(3)学生性别\t*\n";
	      cout<<"*\t(4)学生班级\t*\n";
	      cout<<"*\t(5)学生年龄\t*\n";
	      cout<<"*\t(6)宿舍号码\t*\n";
	      cout<<"*\t(7)电话号码\t*\n";
	      cout<<"*\t(8)选修信息\t*\n";
	      cout<<"*************************\n";
	      cin>>k;
	      switch(k)
	      {
			 case 1:cout<<"▲请输入新的学生学号:\n";
		            cin>>stud[j].num;
		            break;
		     case 2:cout<<"▲请输入新的学生姓名:\n";
		            cin>>stud[j].name;
		            break;
		     case 3:cout<<"▲请输入新的学生性别:\n";
		            cin>>stud[j].sex;
		            break;
		     case 4:cout<<"▲请输入新的学生班级:\n";
		            cin>>stud[j].class1;
		            break;
		     case 5:cout<<"▲请输入新的学生年龄:\n";
		            cin>>stud[j].age;
		            break;
		     case 6:cout<<"▲请输入新的宿舍号码:\n";
		            cin>>stud[j].home;
		            break;  
		     case 7:cout<<"▲请输入新的电话号码:\n";
		            cin>>stud[j].phone;
		            break;  
		     case 8:cout<<"▲输入需要修改的选修课程序号:\n";
		            cin>>m;
		            cout<<"请选择您需要修改的信息对应的序号：\n"; 
		            cout<<"\n*************************\n";
	                cout<<"*\t(1)课程编号\t*\n";
	                cout<<"*\t(2)课程名称\t*\n";
	                cout<<"*\t(3)课程学分\t*\n";
	                cout<<"*\t(4)平时成绩\t*\n";
	                cout<<"*\t(5)考试成绩\t*\n";
	                cout<<"*\t(6)是否重修\t*\n";
	                cout<<"*************************\n";
	                cin>>n;
	                switch(n)
	                {
	                	case 1:cout<<"▲请输入新的课程编号:\n";
		                       cin>>stud[j].cour[m-1].course_num;
		                       break;
		                case 2:cout<<"▲请输入新的课程名称:\n";
		                       cin>>stud[j].cour[m-1].course_name;
		                       break;
		                case 3:cout<<"▲请输入新的课程学分:\n";
		                       cin>>stud[j].cour[m-1].credits;
		                       break;
		                case 4:cout<<"▲请输入新的平时成绩:\n";
		                       cin>>stud[j].cour[m-1].ordinary;
		                       break;
		                case 5:cout<<"▲请输入新的考试成绩:\n";
		                       cin>>stud[j].cour[m-1].test;
		                       break;
		                case 6:cout<<"▲请输入新的重修情况:\n";
		                       cin>>stud[j].cour[m-1].again;
		                       break;
					}	                
		   }
	   }
   }
   save();
   cout<<"请按1可进入菜单查询修改信息：";
   cin>>s;
   if(s==1) 
   menu();	
}

//插入函数 
int add()
{
	 int i,j;
     int b; 
     int p;
   	 cout<<"需要插入的学生数目：";
   	 cin>>p; 
   	for(j=0;j<N+p-2;j++)
   	{
	  cout <<"\n ▲学生序号:NO."<<N+j+1<<endl;
      cout << "\t1.学生学号:";  
      cin >> stud[N+j].num;  
      cout << "\t2.学生姓名:";  
      cin >> stud[N+j].name;  
      cout << "\t3.学生班级:";  
      cin >> stud[N+j].class1; 
	  cout << "\t4.学生性别:";  
      cin >> stud[N+j].sex;  
      cout << "\t5.学生年龄:";  
      cin >> stud[N+j].age;  
      cout << "\t6.宿舍号码:";  
      cin >> stud[N+j].home;   
      cout << "\t7.电话号码:";  
      cin >> stud[N+j].phone;
	  cout << "\t8.选修课程信息:\n";
	  for(i=0;i<2;i++)
	  {
	  	cout<<"\t  *选修课序号:"<<i+1<<endl;
	  	cout<<"\t    (1)课程编号:";
		cin>>stud[N+j].cour[i].course_num;
		cout<<"\t    (2)课程名称:";
		cin>>stud[N+j].cour[i].course_name;
		cout<<"\t    (3)学分:";
		cin>>stud[N+j].cour[i].credits;
		cout<<"\t    (4)平时成绩:";
		cin>>stud[N+j].cour[i].ordinary;
		cout<<"\t    (5)考试成绩:";
		cin>>stud[N+j].cour[i].test;
		stud[N+j].cour[i].sum=0.5*(stud[N+j].cour[i].ordinary+stud[N+j].cour[i].test);		
		cout<<"\t    (6)综合成绩:"<<stud[N+j].cour[i].sum;
		cout<<"\n\t    (7)需要重修(是/否)：";
		cin>>stud[N+j].cour[i].again;
	    stud[N+j].all+=stud[N+j].cour[i].sum;
		stud[N+j].aver=0.5*stud[N+j].all;		 
	  }
	  cout<<"\t9.平均成绩："<<stud[N+j].aver;
	  save();	  
    }
    N+=p;
    cout<<"\n请按1返回主菜单";
	cin>>b;
	if(b==1)
	menu(); 	
}

//排序函数
void paixv()
{
	int r,k;
	int h;
    long int num_2;
    double t;
	string sname;
	string ssex;
	double class_2;
	double a;
	double home_2;
	double phone_2;
	int course_num_2;
	string course_name_2;
	double credits_2;
	double ordinary_2;
	double test_2;
	double sum_2;
	string again_2;
	cout<<"\n按平均成绩排序结果："<<endl;   
        for(int i=0;i<N;i++)
	    {
            for(int j=0;j<N-i;j++)
	       {
                if(stud[j].aver<stud[j+1].aver)
	          { 
                 t=stud[j].aver;   stud[j].aver=stud[j+1].aver;     stud[j+1].aver=t;
                 num_2=stud[j].num;   stud[j].num=stud[j+1].num;    stud[j+1].num=num_2;
                 sname=stud[j].name;stud[j].name=stud[j+1].name; stud[j+1].name=sname;
                 ssex=stud[j].sex;stud[j].sex=stud[j+1].sex; stud[j+1].sex=ssex;
                 class_2=stud[j].class1;stud[j].class1=stud[j+1].class1; stud[j+1].class1=class_2;
                 a=stud[j].age;  stud[j].age=stud[j+1].age;  stud[j+1].age=a;
                 home_2=stud[j].home;  stud[j].home=stud[j+1].home;  stud[j+1].home=home_2;
                 phone_2=stud[j].phone;  stud[j].phone=stud[j+1].phone;   stud[j+1].phone=phone_2;
                 for(int l=0;l<2;l++)
                 {
                  course_num_2=stud[j].cour[l].course_num;  
                  stud[j].cour[l].course_num=stud[j+1].cour[l].course_num;  
                  stud[j+1].cour[l].course_num=course_num_2;
				  course_name_2=stud[j].cour[l].course_name;
				  stud[j].cour[l].course_name=stud[j+1].cour[l].course_name; 
                  stud[j+1].cour[l].course_name=course_name_2; 
                  credits_2=stud[j].cour[l].credits;  
                  stud[j].cour[l].credits=stud[j+1].cour[l].credits;  
                  stud[j+1].cour[l].credits=credits_2;
                  ordinary_2=stud[j].cour[l].ordinary;  
                  stud[j].cour[l].ordinary=stud[j+1].cour[l].ordinary;  
                  stud[j+1].cour[l].ordinary=ordinary_2;
                  test_2=stud[j].cour[l].test;  
                  stud[j].cour[l].test=stud[j+1].cour[l].test;  
                  stud[j+1].cour[l].test=test_2;
                  sum_2=stud[j].cour[l].sum;  
                  stud[j].cour[l].sum=stud[j+1].cour[l].sum;  
                  stud[j+1].cour[l].sum=sum_2;
                  again_2=stud[j].cour[l].again;
				  stud[j].cour[l].again=stud[j+1].cour[l].again; 
                  stud[j+1].cour[l].again=again_2; 
               }
               }              
            } 
        }  
         for(k=0;k<N;k++)
        {
         cout<<"***********";
      	 cout<<"\n▲第"<<k+1<<"名学生";
      	 cout<<"\n平均成绩："<<stud[k].aver;
         cout<<"\n学生学号："<<stud[k].num;
         cout<<"\n学生姓名："<<stud[k].name<<endl;
	   }
	   cout<<"***********";
  cout<<"\n请按1返回菜单";
  cin>>h;
  if(h==1)
  menu();
} 

//删除函数
void clean()
{
	int m;
   string n3;
   bool f5=0;
   string c;
   	cout<<"请输入您要删除的学生姓名:";
   	cin>>n3;
   	for(int i=0;i<N;i++)
   	{
   		if(n3==stud[i].name)
   		{
   			f5=1;
   			N--;
   			do{
   				stud[i]=stud[i+1];
   				for(int j=0;j<2;j++)
   				stud[i].cour[j]=stud[i+1].cour[j];
   				i++;
			   }while(i<=N);
		   }
	   }
	   if(f5==0)
	   cout<<"您要求删除的学生不存在！";
   save(); 
   cout<<"请按1可返回菜单查询信息：";
   cin>>m;
   if(m==1) 
   menu();	
}
