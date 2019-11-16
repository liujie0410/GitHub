
#include <iostream>
#include<windows.h>
#include<string>
using namespace std;
int abc[9999999]={0};//统计当前图书编号的个数
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
    }//cnt库存
    double get(){
        return money;
    }
};
class book
{
protected:
    string name;//书名
    int code;//编号
    string writer;
    string press;
    string date;
    double price;
    int cnt;//库存
    string cdanhao;//采购单
    string xdanhao;//销售单
    string cdate;//采购日期
    string xdate;//销售日期
    double cprice;//采购单价
    double cmoney;//采购总价
    double xmoney;//销售总价
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
            cout<<"书名："<<name<<endl;
            cout<<"图书编号："<<code<<endl;
            cout<<"作者："<<writer<<endl;
            cout<<"出版社："<<press<<endl;
            cout<<"出版日期："<<date<<endl;
            cout<<"单价："<<price<<endl;
        }

    }
    void cai(int a)
    {
        if(a==code)
            {cout<<"请输入采购单号："<<endl;
        cin>>cdanhao;
        cout<<"请输入采购日期："<<endl;
        cin>>cdate;}
    }
      void xiao(int a)
    {
        if(a==code)
            {cout<<"请输入销售单号："<<endl;
        cin>>xdanhao;
        cout<<"请输入销售日期："<<endl;
        cin>>xdate;}
    }
    double caigou(int a,int b)//a编号，b采购量
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
    cout<<"请输入书名:"<<endl;
    cin>>name;
    cout<<"请输入图书编号:"<<endl;
    cin>>code;
    cout<<"请输入作者:"<<endl;
    cin>>writer;
    cout<<"请输入出版社:"<<endl;
    cin>>press;
    cout<<"请输入出版日期:"<<endl;
    cin>>date;
    cout<<"请输入定价:"<<endl;
    cin>>price;
    book a(name,code,writer,press,date,price);
     abc[code]=1;
    return a;

}
void mulu1()
{
    cout<<"*****************************************"<<endl;
    cout<<"           欢迎来到图书管理系统！        "<<endl;
    cout<<"            1.添加图书信息               "<<endl;
    cout<<"            2.提取图书信息               "<<endl;
    cout<<"            3.计算采购金额               "<<endl;
    cout<<"            4.计算销售金额               "<<endl;
    cout<<"            5.利润计算                   "<<endl;
    cout<<"            0.安全退出系统               "<<endl;
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
                cout<<"添加完成返回主菜单（y）/继续添加（n）"<<endl;
                cin>>choice;
                if(choice==("y")){system("cls");goto A;}
                if(choice==("n")){goto B;}
                break;
 C:           case 2:
                cout<<"请输入要提取的图书编号:"<<endl;
                int code;
                cin>>code;
                if(abc[code]==0)
                    {cout <<"输入错误,返回主菜单！"<<endl;
                     goto A;
                    }
                for(int s=0; s<t; s++)
                {
                    a[s].chaxun(code);
                }
                cout<<"提取完成返回主菜单（y）/继续提取（n）"<<endl;//
                  cin>>choice;

                if(choice==("y")){system("cls");goto A;}
                if(choice==("n")){goto C;}
                break;
  D:      case 3:
            int code1;
            cout<<"请输入要采购的图书编号:"<<endl;
            cin>>code1;
            if(abc[code1]==0){cout <<"输入错误 没有该图书！ "<<endl;break;}
            for(int s=0; s<t; s++)
            {
                a[s].chaxun(code1);
                a[s].cai(code1);
            }
            cout<<"请输入采购数量："<<endl;
            int cnt;cin>>cnt;
            cout<<"请输入采购单价："<<endl;
            double e;cin>>e;
            for(int s=0; s<t; s++)
            {
                double d;
                d=a[s].caigou(code1,cnt);
                if(d!=0)
                {
                    b.add(e,cnt);
                    cout<<"采购金额为："<<e*cnt<<endl;
                }
            }
             cout<<"计算完成返回主菜单（y）/继续计算（n）"<<endl;//
                  cin>>choice;
                if(choice==("y")){system("cls");goto A;}
                if(choice==("n")){goto D;}break;
   E:     case 4:
            int code2;
            cout<<"请输入要销售的图书编号："<<endl;
            cin>>code2;
            if(abc[code2]==0)
   {cout <<"输入错误没有该图书,返回菜单。"<<endl;goto A;}
            for(int s=0; s<t; s++)
            {
                a[s].chaxun(code2);
                a[s].xiao(code2);
            }
            cout<<"请输入销售数量："<<endl;
            int cnt2;
            cin>>cnt2;

            bool bl;
            for(int s=0; s<t; s++)
            {
                double d;
                d=a[s].xiaoshou(code2,cnt2);
                if(d==-1)
                {
                    cout<<"库存不足！"<<endl;
                    bl=true;
                  break;
                }
                if(d!=0&&d!=-1){
                    cout<<"总销售额为："<<d*cnt2<<endl;
                    c.add(d,cnt2);
                    bl=true;
                    break;
                }
            }
            if(bl=false){
                cout<<"输入错误!!没有这本书"<<endl;
            }//有书为true没书为false
             cout<<"计算完成返回主菜单（y）/继续计算（n）"<<endl;//
                  cin>>choice;
                if(choice==("y")){system("cls");goto A;}
                if(choice==("n")){goto E;}break;
        case 5:{
            cout<<"销售成本为："<<endl;
            cout<<b.get()<<endl;
            cout<<"销售收入为："<<endl;
            cout<<c.get()<<endl;
            cout<<"销售利润为："<<endl;
            cout<<c.get()-b.get()<<endl;}
             cout<<"计算完成返回主菜单（y）"<<endl;//
                  cin>>choice;
                if(choice==("y")){system("cls");goto A;}
                break;
        case 0:
            return(0);
        }
    }
}


