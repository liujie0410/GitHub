
#include <iostream>
#include<windows.h>
#include<string>
using namespace std;
int abc[9999999]={0};//ͳ�Ƶ�ǰͼ���ŵĸ���
class cb{
private:
    double money;
public:
    cb(){
        money=0;
    }
    void add(double d,int cnt){
        money+=d*cnt;
    }
    double get(){
        return money;
    }
};
class sr{
private:
    double money;
public:
    sr(){
        money=0;
    }
    void add(double d,int cnt){
        money+=d*cnt;
    }//cnt���
    double get(){
        return money;
    }
};
class book
{
protected:
    string name;//����
    int code;//���
    string writer;
    string press;
    string date;
    double price;
    int cnt;//���
    string cdanhao;//�ɹ���
    string xdanhao;//���۵�
    string cdate;//�ɹ�����
    string xdate;//��������
    double cprice;//�ɹ�����
    double cmoney;//�ɹ��ܼ�
    double xmoney;//�����ܼ�
public:
    book(string a,int b,string c,string d,string e,double f)
    {
        name=a;
        code=b;
        writer=c;
        press=d;
        date=e;
        price=f;
        cnt=0;
    }
    book()
    {
    }
    void chaxun(int a)
    {
        if(a==code)
        {
            cout<<"������"<<name<<endl;
            cout<<"ͼ���ţ�"<<code<<endl;
            cout<<"���ߣ�"<<writer<<endl;
            cout<<"�����磺"<<press<<endl;
            cout<<"�������ڣ�"<<date<<endl;
            cout<<"���ۣ�"<<price<<endl;
        }

    }
    void cai(int a)
    {
        if(a==code)
            {cout<<"������ɹ����ţ�"<<endl;
        cin>>cdanhao;
        cout<<"������ɹ����ڣ�"<<endl;
        cin>>cdate;}
    }
      void xiao(int a)
    {
        if(a==code)
            {cout<<"���������۵��ţ�"<<endl;
        cin>>xdanhao;
        cout<<"�������������ڣ�"<<endl;
        cin>>xdate;}
    }
    double caigou(int a,int b)//a��ţ�b�ɹ���
    {
        if(a==code)
        {
            cnt+=b;
            return price;
        }
      else  return 0;
    }
    double xiaoshou(int a,int b){
        if(a==code){
            if(b<=cnt){
                cnt-=b;
                return price;
            }
            else{
                return -1;
            }
        }
      else  return 0;
    }
};

book tianjiatushu()
{
    string name;
    int code;
    string writer;
    string press;
    string date;
    double price;
    cout<<"����������:"<<endl;
    cin>>name;
    cout<<"������ͼ����:"<<endl;
    cin>>code;
    cout<<"����������:"<<endl;
    cin>>writer;
    cout<<"�����������:"<<endl;
    cin>>press;
    cout<<"�������������:"<<endl;
    cin>>date;
    cout<<"�����붨��:"<<endl;
    cin>>price;
    book a(name,code,writer,press,date,price);
     abc[code]=1;
    return a;

}
void mulu1()
{
    cout<<"*****************************************"<<endl;
    cout<<"           ��ӭ����ͼ�����ϵͳ��        "<<endl;
    cout<<"            1.���ͼ����Ϣ               "<<endl;
    cout<<"            2.��ȡͼ����Ϣ               "<<endl;
    cout<<"            3.����ɹ����               "<<endl;
    cout<<"            4.�������۽��               "<<endl;
    cout<<"            5.�������                   "<<endl;
    cout<<"            0.��ȫ�˳�ϵͳ               "<<endl;
    cout<<"*****************************************"<<endl;
}

int main()
{

    int t=0;
    book a[100];
    cb b;
    sr c;
    string choice;
    while(true)
    {
        int i;
A:
        mulu1();
        cin>>i;
        switch(i)
        {
B:          case 1:
                a[t]=tianjiatushu();
                t++;
                cout<<"�����ɷ������˵���y��/������ӣ�n��"<<endl;
                cin>>choice;
                if(choice==("y")){system("cls");goto A;}
                if(choice==("n")){goto B;}
                break;
 C:           case 2:
                cout<<"������Ҫ��ȡ��ͼ����:"<<endl;
                int code;
                cin>>code;
                if(abc[code]==0)
                    {cout <<"�������,�������˵���"<<endl;
                     goto A;
                    }
                for(int s=0; s<t; s++)
                {
                    a[s].chaxun(code);
                }
                cout<<"��ȡ��ɷ������˵���y��/������ȡ��n��"<<endl;//
                  cin>>choice;

                if(choice==("y")){system("cls");goto A;}
                if(choice==("n")){goto C;}
                break;
  D:      case 3:
            int code1;
            cout<<"������Ҫ�ɹ���ͼ����:"<<endl;
            cin>>code1;
            if(abc[code1]==0){cout <<"������� û�и�ͼ�飡 "<<endl;break;}
            for(int s=0; s<t; s++)
            {
                a[s].chaxun(code1);
                a[s].cai(code1);
            }
            cout<<"������ɹ�������"<<endl;
            int cnt;cin>>cnt;
            cout<<"������ɹ����ۣ�"<<endl;
            double e;cin>>e;
            for(int s=0; s<t; s++)
            {
                double d;
                d=a[s].caigou(code1,cnt);
                if(d!=0)
                {
                    b.add(e,cnt);
                    cout<<"�ɹ����Ϊ��"<<e*cnt<<endl;
                }
            }
             cout<<"������ɷ������˵���y��/�������㣨n��"<<endl;//
                  cin>>choice;
                if(choice==("y")){system("cls");goto A;}
                if(choice==("n")){goto D;}break;
   E:     case 4:
            int code2;
            cout<<"������Ҫ���۵�ͼ���ţ�"<<endl;
            cin>>code2;
            if(abc[code2]==0)
   {cout <<"�������û�и�ͼ��,���ز˵���"<<endl;goto A;}
            for(int s=0; s<t; s++)
            {
                a[s].chaxun(code2);
                a[s].xiao(code2);
            }
            cout<<"����������������"<<endl;
            int cnt2;
            cin>>cnt2;

            bool bl;
            for(int s=0; s<t; s++)
            {
                double d;
                d=a[s].xiaoshou(code2,cnt2);
                if(d==-1)
                {
                    cout<<"��治�㣡"<<endl;
                    bl=true;
                  break;
                }
                if(d!=0&&d!=-1){
                    cout<<"�����۶�Ϊ��"<<d*cnt2<<endl;
                    c.add(d,cnt2);
                    bl=true;
                    break;
                }
            }
            if(bl=false){
                cout<<"�������!!û���Ȿ��"<<endl;
            }//����Ϊtrueû��Ϊfalse
             cout<<"������ɷ������˵���y��/�������㣨n��"<<endl;//
                  cin>>choice;
                if(choice==("y")){system("cls");goto A;}
                if(choice==("n")){goto E;}break;
        case 5:{
            cout<<"���۳ɱ�Ϊ��"<<endl;
            cout<<b.get()<<endl;
            cout<<"��������Ϊ��"<<endl;
            cout<<c.get()<<endl;
            cout<<"��������Ϊ��"<<endl;
            cout<<c.get()-b.get()<<endl;}
             cout<<"������ɷ������˵���y��"<<endl;//
                  cin>>choice;
                if(choice==("y")){system("cls");goto A;}
                break;
        case 0:
            return(0);
        }
    }
}


