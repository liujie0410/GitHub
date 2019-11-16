#include <windows.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <cstring>
#include <cstdio>
#include <iostream>
#define  N 22
using namespace std;

//����
int gameover;                             //��Ϸ�����ж����� 
int x1, y1;                               //ʳ������ 
int x,y;                                  //������ 
long start;     

//��λ���
void gotoxy(int x, int y)
{
    HANDLE hConsoleOutput;
    COORD dwCursorPosition;
    dwCursorPosition.X = x;
    dwCursorPosition.Y = y;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hConsoleOutput, dwCursorPosition);
}                          

//̰���ߵ�������
class snake_point 
{
  public:
    int x,y;                             //�У���
    snake_point(){};                     //̰����������Ĺ��캯�� 
    void initialize(int &);              //�����ʼ��
};

snake_point point[(N-2)*(N-2)+1];        //����̰�������������飬��20*20������

//�������ʼ������ 
void snake_point::initialize(int &j)
{
    x = 10;
    y = j;
}

//�����ͼ��
class map
{ 
  private:  
    char m[N][N];                        //��ͼ����  
    int grade, length, head, tail;        //�ȼ������ȡ���ͷ����β 
    int gamespeed;                       //ǰ��һ����ʱ����
    char direction;                      //ǰ������ 
    int score;                           //�÷� 
    bool gameauto;                       // 
  public:
    map(int h=4,int t=1,int l=4,char d=77,int s=0):length(l),direction(d),head(h),tail(t),score(s){}//���캯�� 
    void initialize();                   //��ʼ������ 
    void show(); 
    int updata_game(); 
    void setpoint();
    void getgrade();
    void display();
}; 

//��ͼ��ʼ�� 
void map::initialize()
{
    int i,j; 
    for(i=1;i<=3;i++) 
        m[10][i] = 'O';                                       //��ʼ������ 
    m[10][4] = '#';                                           //��ʼ����β 
    for(i=1;i<=N-2;i++)
    {
       for(j=1;j<=N-2;j++) 
            m[i][j]=' ';                                     // ��ʼ��̰���������м�հײ���
	}
    for(i=0;i<=N-1;i++)
        m[0][i] = m[N-1][i] = m[i][0] = m[i][N-1]= '*';      //��ʼ���߽� 
 } 

//�ȼ��ٶ�ѡ�� 
void map::getgrade()
{
    cin>>grade;
    while( grade>10 || grade<1 )
    {
        cout << "����������Ч����ѡ��1-10����Ϸ�ȼ���" << endl;
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

//��Ϸ������ʾ 
void map::show()
{
    //system("cls"); // ����
    gotoxy(0,0);
    int i,j;
    cout << endl;
    for(i=0;i<N;i++)
    {
        cout << '\t';
        for(j=0;j<N;j++)
            cout<<m[i][j]<<' '; // ��ʾ��ͼ 
        if(i==2) cout << "\t�ȼ���" << grade;//�ڲ�ͬ����ʾ��ͬ���� 
        if(i==6) cout << "\t�ٶȣ�" << gamespeed;
        if(i==10) cout << "\t�÷֣�" << score << "��" ;
        if(i==14) cout << "\t��ͣ��Ϸ����һ�¿ո��" ;
        if(i==18) cout << "\t������Ϸ�������¿ո��" ;
        cout<<endl;
    }
}

//�ȼ��÷ֽ��� 
void map::display()
{
    cout << "\n\t\t\t\t�ȼ���" << grade;
    cout << "\n\n\n\t\t\t\t�ٶȣ�" << gamespeed;
    cout << "\n\n\n\t\t\t\t�÷֣�" << score << "��" ;
}

//�������ʳ������ 
void map::setpoint()
{
    srand(time(0)); //�������Ӻ��� 
    do
    {
        x1 = rand() % (N-2) + 1;
        y1 = rand() % (N-2) + 1;
    }while(m[x1][y1]!=' ');
    m[x1][y1]='O';
}

char d;
 
//��Ϸ���� 
int map::updata_game()
{
	gameover = 1;//��Ϸ��������Ϊgameover����1 
    d = direction;//ǰ������ 
    start = clock();//���ü�ʱ�������������ʼ���е��˲���ʱ�� 
    while((gameover=(clock()-start<=gamespeed))&&!kbhit());//����м����»�ʱ�䳬���Զ�ǰ��ʱ��������ֹѭ��
	    if(gameover)
        {
            getch();//����ȴ��û����� 
            d= getch();
        }
        if(d==' ')
		{
			while(getch()!=' '){};
		}
        else {direction = d;}
          switch(direction)
          {
            case 72: x= point[head].x-1; y= point[head].y;break; // ���� 
            case 80: x= point[head].x+1; y= point[head].y;break; // ���� 
            case 75: x= point[head].x; y= point[head].y-1;break; // ���� 
            case 77: x= point[head].x; y= point[head].y+1;break; // ���� 
          }
        if(!(direction==72||direction==80||direction==75 ||direction==77))   // �����Ƿ����
            gameover = 0;//��Ϸ���� 
        else if(x==0 || x==N-1 ||y==0 || y==N-1)   // ����ǽ��
        {
          if(x==0)   x=20;
		  if(x==N-1) x=1;
		  if(y==0)   y=20;
		  if(y==N-1) y=1;
	    }
        if(m[x][y]!=' '&&!(x==x1&&y==y1))    // ��ͷ��������
            gameover = 0;
        else if(x==x1 && y==y1)// �Ե�ʳ����ȼ�1
        { 
            length ++;
            if(length>=8 && gameauto)
            {
                length -= 8;
                grade ++;
                if(gamespeed>=200)
                    gamespeed -= 100; //�Զ������ȼ����ı�ǰ�����ʱ�� 
                else
                    gamespeed = 100;
            }
            m[x][y]= '#';  //������ͷ
            m[point[head].x][point[head].y] = 'O'; //�Ե�ʳ���ԭ����ͷ��Ϊ����
            head = (head+1) % ( (N-2)*(N-2) );   //ȡ��ͷ����
            point[head].x = x;
            point[head].y = y;
            show();
            gameover = 1;
            score += grade*10;  //�ӷ�
            setpoint();   //����ʳ�� 
        }
        else//δ�Ե�ʳ�� 
        { 
            m[point[tail].x][point[tail].y]=' ';    //����β�ÿ�
            tail= (tail+1) % ( (N-2) * (N-2) );     //������β����
            m[point[head].x][point[head].y]='O';    //����ͷ��Ϊ����
            head= (head+1) % ( (N-2) * (N-2) );     //������ͷ���� 
            point[head].x = x;
            point[head].y = y;
            m[point[head].x][point[head].y]='#'; //������ͷ
            gameover = 1;
        }
    return gameover;
}


//��ӭ����
void welcome()
{
    cout<<"\n\n\n\n\n\t\t\t ��ӭ����̰������Ϸ!"<<endl;
    cout<<"\n\n\n\t\t\t    �汾�����1.0"<<endl;
    cout<<"\n\n\n\t\t\t   ���������ʼ��Ϸ"<<endl;
    getch();
}
 
//������ 
int main()
{
	system("color F0");
    char ctn = 'y';
    int nodead;
    welcome();
    while( ctn=='y' )
    {
        system("cls"); // ����
        map snake;
        snake.initialize();
        cout << "\n\t\t   ��ӭ����̰������Ϸ�ȼ�����" << endl;
        cout << "\n\n\t\t\t1.�ȼ�һ���ٶ� 900 \n\n\t\t\t2.�ȼ������ٶ� 800 \n\n\t\t\t3.�ȼ������ٶ� 700 ";
        cout << "\n\n\t\t\t4.�ȼ��ģ��ٶ� 600 \n\n\t\t\t5.�ȼ��壺�ٶ� 500 \n\n\t\t\t6.�ȼ������ٶ� 400 ";
        cout << "\n\n\t\t\t7.�ȼ��ߣ��ٶ� 300 \n\n\t\t\t8.�ȼ��ˣ��ٶ� 200 \n\n\t\t\t9.�ȼ��ţ��ٶ� 100 \n\n\t\t\t10.�Զ�����ģʽ"<<endl;
        cout << "\n����������ѡ����Ϸ�ȼ���" << endl;
        snake.getgrade();//��ȡ�ȼ�
        for(int i=1;i<=4;i++)
        {
            point[i].initialize(i);//��ʼ������
        }
        snake.setpoint();  // ���ɵ�һ��ʳ�� 
        do
        {
            snake.show();
            nodead = snake.updata_game();
        }while(nodead);
        system("cls"); //����
        cout << "\n\n\n\t\t\t\tGameover��\n\n"<<endl;
        snake.display();//��ʾ�ȼ��÷����
        cout << "\n\n\n\t\t    �Ƿ�ѡ�������Ϸ������ y ������n �˳�" << endl;
        cin >> ctn;
    }
    return 0;
}
