#include <windows.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <cstring>
#include <cstdio>
#include <iostream>
#define  N 22
using namespace std;

//声明
int gameover;                             //游戏进行判断条件 
int x1, y1;                               //食物坐标 
int x,y;                                  //蛇坐标 
long start;     

//定位光标
void gotoxy(int x, int y)
{
    HANDLE hConsoleOutput;
    COORD dwCursorPosition;
    dwCursorPosition.X = x;
    dwCursorPosition.Y = y;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hConsoleOutput, dwCursorPosition);
}                          

//贪吃蛇的坐标类
class snake_point 
{
  public:
    int x,y;                             //行，列
    snake_point(){};                     //贪吃蛇坐标类的构造函数 
    void initialize(int &);              //坐标初始化
};

snake_point point[(N-2)*(N-2)+1];        //定义贪吃蛇坐标类数组，有20*20个坐标

//蛇坐标初始化函数 
void snake_point::initialize(int &j)
{
    x = 10;
    y = j;
}

//定义地图类
class map
{ 
  private:  
    char m[N][N];                        //地图数组  
    int grade, length, head, tail;        //等级、长度、蛇头、蛇尾 
    int gamespeed;                       //前进一步的时间间隔
    char direction;                      //前进方向 
    int score;                           //得分 
    bool gameauto;                       // 
  public:
    map(int h=4,int t=1,int l=4,char d=77,int s=0):length(l),direction(d),head(h),tail(t),score(s){}//构造函数 
    void initialize();                   //初始化函数 
    void show(); 
    int updata_game(); 
    void setpoint();
    void getgrade();
    void display();
}; 

//地图初始化 
void map::initialize()
{
    int i,j; 
    for(i=1;i<=3;i++) 
        m[10][i] = 'O';                                       //初始化蛇身 
    m[10][4] = '#';                                           //初始化蛇尾 
    for(i=1;i<=N-2;i++)
    {
       for(j=1;j<=N-2;j++) 
            m[i][j]=' ';                                     // 初始化贪吃蛇棋盘中间空白部分
	}
    for(i=0;i<=N-1;i++)
        m[0][i] = m[N-1][i] = m[i][0] = m[i][N-1]= '*';      //初始化边界 
 } 

//等级速度选择 
void map::getgrade()
{
    cin>>grade;
    while( grade>10 || grade<1 )
    {
        cout << "输入数字无效，请选择1-10的游戏等级！" << endl;
        cin >> grade;
    }
    switch(grade)
    {
        case 1: gamespeed = 900;gameauto = 0;break;
        case 2: gamespeed = 800;gameauto = 0;break;
        case 3: gamespeed = 700;gameauto = 0;break;
        case 4: gamespeed = 600;gameauto = 0;break;
        case 5: gamespeed = 500;gameauto = 0;break;
        case 6: gamespeed = 400;gameauto = 0;break;
        case 7: gamespeed = 300;gameauto = 0;break;
        case 8: gamespeed = 200;gameauto = 0;break;
        case 9: gamespeed = 100;gameauto = 0;break; 
        case 10: grade = 1;gamespeed = 1000;gameauto = 1;break;
    }
}

//游戏界面显示 
void map::show()
{
    //system("cls"); // 清屏
    gotoxy(0,0);
    int i,j;
    cout << endl;
    for(i=0;i<N;i++)
    {
        cout << '\t';
        for(j=0;j<N;j++)
            cout<<m[i][j]<<' '; // 显示地图 
        if(i==2) cout << "\t等级：" << grade;//在不同行显示不同内容 
        if(i==6) cout << "\t速度：" << gamespeed;
        if(i==10) cout << "\t得分：" << score << "分" ;
        if(i==14) cout << "\t暂停游戏：按一下空格键" ;
        if(i==18) cout << "\t继续游戏：按两下空格键" ;
        cout<<endl;
    }
}

//等级得分界面 
void map::display()
{
    cout << "\n\t\t\t\t等级：" << grade;
    cout << "\n\n\n\t\t\t\t速度：" << gamespeed;
    cout << "\n\n\n\t\t\t\t得分：" << score << "分" ;
}

//随机生成食物坐标 
void map::setpoint()
{
    srand(time(0)); //调用种子函数 
    do
    {
        x1 = rand() % (N-2) + 1;
        y1 = rand() % (N-2) + 1;
    }while(m[x1][y1]!=' ');
    m[x1][y1]='O';
}

char d;
 
//游戏运行 
int map::updata_game()
{
	gameover = 1;//游戏进行条件为gameover等于1 
    d = direction;//前进方向 
    start = clock();//调用计时函数，计算程序开始运行到此步的时间 
    while((gameover=(clock()-start<=gamespeed))&&!kbhit());//如果有键按下或时间超过自动前进时间间隔则终止循环
	    if(gameover)
        {
            getch();//程序等待用户按键 
            d= getch();
        }
        if(d==' ')
		{
			while(getch()!=' '){};
		}
        else {direction = d;}
          switch(direction)
          {
            case 72: x= point[head].x-1; y= point[head].y;break; // 向左 
            case 80: x= point[head].x+1; y= point[head].y;break; // 向右 
            case 75: x= point[head].x; y= point[head].y-1;break; // 向上 
            case 77: x= point[head].x; y= point[head].y+1;break; // 向下 
          }
        if(!(direction==72||direction==80||direction==75 ||direction==77))   // 按键非方向键
            gameover = 0;//游戏结束 
        else if(x==0 || x==N-1 ||y==0 || y==N-1)   // 碰到墙壁
        {
          if(x==0)   x=20;
		  if(x==N-1) x=1;
		  if(y==0)   y=20;
		  if(y==N-1) y=1;
	    }
        if(m[x][y]!=' '&&!(x==x1&&y==y1))    // 蛇头碰到蛇身
            gameover = 0;
        else if(x==x1 && y==y1)// 吃到食物，长度加1
        { 
            length ++;
            if(length>=8 && gameauto)
            {
                length -= 8;
                grade ++;
                if(gamespeed>=200)
                    gamespeed -= 100; //自动升级等级，改变前进间隔时间 
                else
                    gamespeed = 100;
            }
            m[x][y]= '#';  //更新蛇头
            m[point[head].x][point[head].y] = 'O'; //吃到食物后将原先蛇头变为蛇身
            head = (head+1) % ( (N-2)*(N-2) );   //取蛇头坐标
            point[head].x = x;
            point[head].y = y;
            show();
            gameover = 1;
            score += grade*10;  //加分
            setpoint();   //生成食物 
        }
        else//未吃到食物 
        { 
            m[point[tail].x][point[tail].y]=' ';    //将蛇尾置空
            tail= (tail+1) % ( (N-2) * (N-2) );     //更新蛇尾坐标
            m[point[head].x][point[head].y]='O';    //将蛇头更为蛇身
            head= (head+1) % ( (N-2) * (N-2) );     //更新蛇头坐标 
            point[head].x = x;
            point[head].y = y;
            m[point[head].x][point[head].y]='#'; //更新蛇头
            gameover = 1;
        }
    return gameover;
}


//欢迎界面
void welcome()
{
    cout<<"\n\n\n\n\n\t\t\t 欢迎进入贪吃蛇游戏!"<<endl;
    cout<<"\n\n\n\t\t\t    版本：刘婕1.0"<<endl;
    cout<<"\n\n\n\t\t\t   按任意键开始游戏"<<endl;
    getch();
}
 
//主函数 
int main()
{
	system("color F0");
    char ctn = 'y';
    int nodead;
    welcome();
    while( ctn=='y' )
    {
        system("cls"); // 清屏
        map snake;
        snake.initialize();
        cout << "\n\t\t   欢迎来到贪吃蛇游戏等级界面" << endl;
        cout << "\n\n\t\t\t1.等级一：速度 900 \n\n\t\t\t2.等级二：速度 800 \n\n\t\t\t3.等级三：速度 700 ";
        cout << "\n\n\t\t\t4.等级四：速度 600 \n\n\t\t\t5.等级五：速度 500 \n\n\t\t\t6.等级六：速度 400 ";
        cout << "\n\n\t\t\t7.等级七：速度 300 \n\n\t\t\t8.等级八：速度 200 \n\n\t\t\t9.等级九：速度 100 \n\n\t\t\t10.自动升级模式"<<endl;
        cout << "\n请输入数字选择游戏等级：" << endl;
        snake.getgrade();//获取等级
        for(int i=1;i<=4;i++)
        {
            point[i].initialize(i);//初始化坐标
        }
        snake.setpoint();  // 生成第一个食物 
        do
        {
            snake.show();
            nodead = snake.updata_game();
        }while(nodead);
        system("cls"); //清屏
        cout << "\n\n\n\t\t\t\tGameover！\n\n"<<endl;
        snake.display();//显示等级得分情况
        cout << "\n\n\n\t\t    是否选择继续游戏？输入 y 继续，n 退出" << endl;
        cin >> ctn;
    }
    return 0;
}
