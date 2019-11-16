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

//����
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
 
//course�ṹ������ 
struct course
{
	public: 
    int course_num;//�γ̱��
	string course_name;//�γ�����
	double credits;//ѧ�� 
	double ordinary;//ƽʱ�ɼ� 
	double test;//���Գɼ�
	double sum;//�ۺϳɼ� 
	string again;//������� 
};  

//student������
class student
{  
 public:
 	course cour[2];//�ṹ������ 
    long int num;  //ѧ�� 
    string name;  //���� 
    double class1;  //�༶ 
    string sex; //�Ա�
    double age;//����
	double home;//�������
	double phone;//�绰���� 
	double all;//�ܳɼ� 
	double aver;//ƽ���ɼ�
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

//�˵�
void menu()
{
	system("cls");
	int choice;
      cout<<"\n\t           ��ӭʹ��ѧ���ɼ�����ϵͳ\n\n";
	  cout<<"\t��*************************************************��\n\n";
	  cout<<"\t��\t\t(1)ѧ����Ϣ¼��\t\t\t    ��\n\n";
	  cout<<"\t��\t\t(2)ѧ����Ϣ��ѯ\t\t\t    ��\n\n";
	  cout<<"\t��\t\t(3)ѧ����Ϣ�޸�\t\t\t    ��\n\n";
	  cout<<"\t��\t\t(4)ѧ����Ϣ����\t\t\t    ��\n\n";
	  cout<<"\t��\t\t(5)ѧ���ɼ�����\t\t\t    ��\n\n";
	  cout<<"\t��\t\t(6)ѧ����Ϣɾ��\t\t\t    ��\n\n";
      cout<<"\t��\t\t(7)�˳�����\t\t\t    ��\n\n";
	  cout<<"\t��*************************************************��\n\n";
	  cout<<"��������ѡ��Ĺ�����ţ�";
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
 
//������ 
int main()
{
	menu();
	return 0;
}
 
//���溯��
int save()
{
	ofstream outfile("student.txt",ios::binary);
	if(!outfile)
	{
		cerr<<"�Ҳ����ļ���"<<endl;
		abort();
	}
    for(int i=0;i<=100;i++)
     outfile.write((char*)&stud[i],sizeof(stud[i]));
	outfile.close();
	return 0;
} 

//¼�뺯�� 
void input()
{  
	 int i,j;
     int b;
   	 cout<<"��Ҫ�����ѧ����Ŀ��";
   	 cin>>N; 
   	 if(N>=100)
   	 cout<<"���󣡳����޶�ѧ����Ŀ��\n";
   	for(j=0;j<N;j++)
   	{
	  cout <<"\n\t��ѧ�����:NO."<<j+1<<endl;
      cout << "\t1.ѧ��ѧ��:";  
      cin >> stud[j].num;  
      cout << "\t2.ѧ������:";  
      cin >> stud[j].name;  
      cout << "\t3.ѧ���༶:";  
      cin >> stud[j].class1; 
	  cout << "\t4.ѧ���Ա�:";  
      cin >> stud[j].sex;  
      cout << "\t5.ѧ������:";  
      cin >> stud[j].age;  
      cout << "\t6.�������:";  
      cin >> stud[j].home;   
      cout << "\t7.�绰����:";  
      cin >> stud[j].phone;
	  cout << "\t8.ѡ�޿γ���Ϣ:\n";
	  for(i=0;i<2;i++)
	  {
	  	cout<<"\n\t  *ѡ�޿����:"<<i+1<<endl;
	  	cout<<"\t    (1)�γ̱��:";
		cin>>stud[j].cour[i].course_num;
		cout<<"\t    (2)�γ�����:";
		cin>>stud[j].cour[i].course_name;
		cout<<"\t    (3)ѧ��:";
		cin>>stud[j].cour[i].credits;
		cout<<"\t    (4)ƽʱ�ɼ�:";
		cin>>stud[j].cour[i].ordinary;
		cout<<"\t    (5)���Գɼ�:";
		cin>>stud[j].cour[i].test;
		stud[j].cour[i].sum=0.5*(stud[j].cour[i].ordinary+stud[j].cour[i].test);		
		cout<<"\t    (6)�ۺϳɼ�:"<<stud[j].cour[i].sum;
		cout<<"\n\t    (7)��Ҫ����(��/��)��";
		cin>>stud[j].cour[i].again;
		stud[j].all+=stud[j].cour[i].sum;
		stud[j].aver=0.5*stud[j].all;		 
	  }
	  cout<<"\t9.ƽ���ɼ���"<<stud[j].aver;
	  save();	  
    }
    cout<<"\n�밴1�������˵�";
	cin>>b;
	if(b==1)
	menu(); 
} 
   
//��ѯ����
void search()
{
	int b;
  	int j;
	long int num;
	  cout<<"��������Ҫ���ҵ�ѧ��ѧ�ţ�";
	  cin>>num;
	  for(j=0;j<N;j++)
	  {
	    if(num==stud[j].num) {print(j);} 
      }	 
          cout<<"\n�밴1�������˵�";
	cin>>b;
	if(b==1)
	menu(); 
}

//��Ϣ��ʾ 
void print(int j)
{
	int i; 
      cout<<"\n����Ϊ��Ӧѧ������Ϣ";
      cout<<"\n****������Ϣ****";
      cout<<"\nѧ�ţ�"<<stud[j].num;
      cout<<"\n������"<<stud[j].name;
      cout<<"\n�Ա�"<<stud[j].sex;
      cout<<"\n�༶��"<<stud[j].class1;
	  cout<<"\n���䣺"<<stud[j].age;
	  cout<<"\n���᣺"<<stud[j].home;
      cout<<"\n�绰��"<<stud[j].phone;
      cout<<"\nƽ���ɼ���"<<stud[j].aver;
      cout<<"\n****ѡ����Ϣ****";
      for(i=0;i<2;i++)
      {
      	cout<<"\n���γ���ţ�"<<i+1;
      	cout<<"\n��1���γ̱�ţ�"<<stud[j].cour[i].course_num;
      	cout<<"\n��2���γ����ƣ�"<<stud[j].cour[i].course_name;
      	cout<<"\n��3���γ�ѧ�֣�"<<stud[j].cour[i].credits;
      	cout<<"\n��4��ƽʱ�ɼ���"<<stud[j].cour[i].ordinary;
      	cout<<"\n��5�����Գɼ���"<<stud[j].cour[i].test;
      	cout<<"\n��6���ۺϳɼ���"<<stud[j].cour[i].sum;
      	cout<<"\n��7���Ƿ����ޣ�"<<stud[j].cour[i].again;
	  }
	  cout<<"\n****************";
}
 
//�޸ĺ���
void change()
{
	int j;
	int k;
	int s;
	int m;
	int n; 
	string name;
	cout<<"��������Ҫ�޸���Ϣ��ѧ��������";
	cin>>name;
	for(j=0;j<100;j++)
	{
		if(stud[j].name==name)
       {
       	  print(j); 
       	  cout<<"\n\n��ѡ������Ҫ�޸ĵ���Ϣ��Ӧ����ţ�"; 
		  cout<<"\n*************************\n";
	      cout<<"*\t(1)ѧ��ѧ��\t*\n";
	      cout<<"*\t(2)ѧ������\t*\n";
	      cout<<"*\t(3)ѧ���Ա�\t*\n";
	      cout<<"*\t(4)ѧ���༶\t*\n";
	      cout<<"*\t(5)ѧ������\t*\n";
	      cout<<"*\t(6)�������\t*\n";
	      cout<<"*\t(7)�绰����\t*\n";
	      cout<<"*\t(8)ѡ����Ϣ\t*\n";
	      cout<<"*************************\n";
	      cin>>k;
	      switch(k)
	      {
			 case 1:cout<<"���������µ�ѧ��ѧ��:\n";
		            cin>>stud[j].num;
		            break;
		     case 2:cout<<"���������µ�ѧ������:\n";
		            cin>>stud[j].name;
		            break;
		     case 3:cout<<"���������µ�ѧ���Ա�:\n";
		            cin>>stud[j].sex;
		            break;
		     case 4:cout<<"���������µ�ѧ���༶:\n";
		            cin>>stud[j].class1;
		            break;
		     case 5:cout<<"���������µ�ѧ������:\n";
		            cin>>stud[j].age;
		            break;
		     case 6:cout<<"���������µ��������:\n";
		            cin>>stud[j].home;
		            break;  
		     case 7:cout<<"���������µĵ绰����:\n";
		            cin>>stud[j].phone;
		            break;  
		     case 8:cout<<"��������Ҫ�޸ĵ�ѡ�޿γ����:\n";
		            cin>>m;
		            cout<<"��ѡ������Ҫ�޸ĵ���Ϣ��Ӧ����ţ�\n"; 
		            cout<<"\n*************************\n";
	                cout<<"*\t(1)�γ̱��\t*\n";
	                cout<<"*\t(2)�γ�����\t*\n";
	                cout<<"*\t(3)�γ�ѧ��\t*\n";
	                cout<<"*\t(4)ƽʱ�ɼ�\t*\n";
	                cout<<"*\t(5)���Գɼ�\t*\n";
	                cout<<"*\t(6)�Ƿ�����\t*\n";
	                cout<<"*************************\n";
	                cin>>n;
	                switch(n)
	                {
	                	case 1:cout<<"���������µĿγ̱��:\n";
		                       cin>>stud[j].cour[m-1].course_num;
		                       break;
		                case 2:cout<<"���������µĿγ�����:\n";
		                       cin>>stud[j].cour[m-1].course_name;
		                       break;
		                case 3:cout<<"���������µĿγ�ѧ��:\n";
		                       cin>>stud[j].cour[m-1].credits;
		                       break;
		                case 4:cout<<"���������µ�ƽʱ�ɼ�:\n";
		                       cin>>stud[j].cour[m-1].ordinary;
		                       break;
		                case 5:cout<<"���������µĿ��Գɼ�:\n";
		                       cin>>stud[j].cour[m-1].test;
		                       break;
		                case 6:cout<<"���������µ��������:\n";
		                       cin>>stud[j].cour[m-1].again;
		                       break;
					}	                
		   }
	   }
   }
   save();
   cout<<"�밴1�ɽ���˵���ѯ�޸���Ϣ��";
   cin>>s;
   if(s==1) 
   menu();	
}

//���뺯�� 
int add()
{
	 int i,j;
     int b; 
     int p;
   	 cout<<"��Ҫ�����ѧ����Ŀ��";
   	 cin>>p; 
   	for(j=0;j<N+p-2;j++)
   	{
	  cout <<"\n ��ѧ�����:NO."<<N+j+1<<endl;
      cout << "\t1.ѧ��ѧ��:";  
      cin >> stud[N+j].num;  
      cout << "\t2.ѧ������:";  
      cin >> stud[N+j].name;  
      cout << "\t3.ѧ���༶:";  
      cin >> stud[N+j].class1; 
	  cout << "\t4.ѧ���Ա�:";  
      cin >> stud[N+j].sex;  
      cout << "\t5.ѧ������:";  
      cin >> stud[N+j].age;  
      cout << "\t6.�������:";  
      cin >> stud[N+j].home;   
      cout << "\t7.�绰����:";  
      cin >> stud[N+j].phone;
	  cout << "\t8.ѡ�޿γ���Ϣ:\n";
	  for(i=0;i<2;i++)
	  {
	  	cout<<"\t  *ѡ�޿����:"<<i+1<<endl;
	  	cout<<"\t    (1)�γ̱��:";
		cin>>stud[N+j].cour[i].course_num;
		cout<<"\t    (2)�γ�����:";
		cin>>stud[N+j].cour[i].course_name;
		cout<<"\t    (3)ѧ��:";
		cin>>stud[N+j].cour[i].credits;
		cout<<"\t    (4)ƽʱ�ɼ�:";
		cin>>stud[N+j].cour[i].ordinary;
		cout<<"\t    (5)���Գɼ�:";
		cin>>stud[N+j].cour[i].test;
		stud[N+j].cour[i].sum=0.5*(stud[N+j].cour[i].ordinary+stud[N+j].cour[i].test);		
		cout<<"\t    (6)�ۺϳɼ�:"<<stud[N+j].cour[i].sum;
		cout<<"\n\t    (7)��Ҫ����(��/��)��";
		cin>>stud[N+j].cour[i].again;
	    stud[N+j].all+=stud[N+j].cour[i].sum;
		stud[N+j].aver=0.5*stud[N+j].all;		 
	  }
	  cout<<"\t9.ƽ���ɼ���"<<stud[N+j].aver;
	  save();	  
    }
    N+=p;
    cout<<"\n�밴1�������˵�";
	cin>>b;
	if(b==1)
	menu(); 	
}

//������
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
	cout<<"\n��ƽ���ɼ���������"<<endl;   
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
      	 cout<<"\n����"<<k+1<<"��ѧ��";
      	 cout<<"\nƽ���ɼ���"<<stud[k].aver;
         cout<<"\nѧ��ѧ�ţ�"<<stud[k].num;
         cout<<"\nѧ��������"<<stud[k].name<<endl;
	   }
	   cout<<"***********";
  cout<<"\n�밴1���ز˵�";
  cin>>h;
  if(h==1)
  menu();
} 

//ɾ������
void clean()
{
	int m;
   string n3;
   bool f5=0;
   string c;
   	cout<<"��������Ҫɾ����ѧ������:";
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
	   cout<<"��Ҫ��ɾ����ѧ�������ڣ�";
   save(); 
   cout<<"�밴1�ɷ��ز˵���ѯ��Ϣ��";
   cin>>m;
   if(m==1) 
   menu();	
}
