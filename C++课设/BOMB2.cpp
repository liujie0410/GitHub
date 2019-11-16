#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <queue>
#include<conio.h>
#include<windows.h>
#define BOMB 16
using namespace std;

int map[10][10];//整个地图的坐标 
int show[10][10]={{0}}; //表示翻牌情况，0表示未翻开且未标记，1表示翻开，2表示标记
char answer[10][10];//当用户失败时输出正确答案 
int mine[10];//mine数组，表示地雷位置，其值等于10*雷的行+雷的列 ，共有10个雷 

//定位光标
void gotoxy(int x,int y)
{
	COORD pos;
	pos.X=2*x;
	pos.Y=y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
}

//改变输出字符颜色
void color(int a)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),a);
}

//没有雷的格子对应的数字
int count(int map[][10],int i,int j)
{
	int d=0;
	int k,l;
	if(i>0&&i<9&&j>0&&j<9)//中间部分任取一个格子 
	{
		for(k=i-1;k<=i+1;k++)//从左到右扫描 
		{
			for(l=j-1;l<=j+1;l++)//从上到下扫描 
			{
				if(map[k][l]==BOMB)
				d++;//无雷格子周围的雷数目 
			}
		}
	}
	else if(i==0&&j>0&&j<9)//左边界任取一个格子 
	{
		for(k=i;k<=i+1;k++)//往右扫描一格 
		{
			for(l=j-1;l<=j+1;l++)//从上到下扫描 
			{
				if(map[k][l]==BOMB)
				d++;
			}
		}
	}
	else if(i==9&&j>0&&j<9)//右边界任取一个格子 
	{
		for(k=i-1;k<=i;k++)
		{
			for(l=j-1;l<=j+1;l++)
			{
				if(map[k][l]==BOMB)
				d++;
			}
		}
	}
	else if(j==0&&i>0&&i<9)//上边界任取一格 
	{
		for(k=i-1;k<=i+1;k++)
		{
			for(l=j;l<=j+1;l++)
			{
				if(map[k][l]==BOMB)
				d++;
			}
		}
	}
	else if(j==9&&i>0&&i<9)//下边界任取一格 
	{
		for(k=i-1;k<=i+1;k++)
		{
			for(l=j-1;l<=j;l++)
			{
				if(map[k][l]==BOMB)
				d++;
			}
		}
	}
	else if(i==0&&j==0)//左上顶点坐标 
	{
		for(k=0;k<=1;k++)
		{
			for(l=0;l<=1;l++)
			{
				if(map[k][l]==BOMB)
				d++;
			}
		}
	}
	else if(i==0&&j==9)//右上顶点坐标 
	{
		for(k=0;k<=1;k++)
		{
			for(l=14;l<=15;l++)
			{
				if(map[k][l]==BOMB)
				d++;
			}
		}
	}
	else if(i==9&&j==0)//左下顶点坐标 
	{
		for(k=8;k<=9;k++)
		{
			for(l=0;l<=1;l++)
			{
				if(map[k][l]==BOMB)
				d++;
			}
		}
	}
	else if(i==9&&j==9)//右下顶点坐标 
	{
		for(k=8;k<=9;k++)
		{
			for(l=8;l<=9;l++)
			{
				if(map[k][l]==BOMB)
				d++;
			}
		}
	}
	return d;
}

//判断随机数之前是否出现过，出现过则返回0，否则返回1
int whether(int mine[],int a,int j)
{
	int i;
	for(i=0;i<j;i++)
	{
		if(mine[i]==a)//地雷位置出现过 
		return 0;
	}
	return 1;
}

//产生地雷和数字 
void Arrange()
{
	int i,j;
	for(i=0;i<10;i++)
	{
		for(j=0;j<10;j++)  map[i][j]=0;//地图初始化 
	}
	srand((unsigned)time(NULL)); //调用种子函数，传入空指针初始化 
	for(i=0;i<10;i++)
	{
		int t=rand()%100;//产生一个100之内的随机数 
		while(whether(mine,t,i)==0)//每取一个随机数调用一次whether函数，等于0表示出现过该随机数 
		t=rand()%100;//重新取一个随机数 
		mine[i]=t;//随机产生雷的位置 
	}
	for(i=0;i<10;i++)
	map[mine[i]/10][mine[i]%10]=BOMB;//用雷的位置进行相关计算，确定雷在地图上的行列坐标 
	for(i=0;i<10;i++)//左右扫描 
	{
		for(j=0;j<10;j++)//上下扫描 
		{
			if(map[i][j]!=BOMB)//不是雷的格子调用count函数，得到对应的数字 
			map[i][j]=count(map,i,j);
		}
	}
}

//答案矩阵
void an(int map[][10])
{
	int i,j;
	for(i=0;i<10;i++)//左右扫描 
	{
		for(j=0;j<10;j++)//上下扫描 
		{
			if(map[i][j]==BOMB) answer[i][j]='L';
			else answer[i][j]=(char)(map[i][j]+48);
		}
	}
}

//翻格子 
void point(int i,int j)
{
	int k,l;
	if(show[i][j]==2) show[i][j]==2;//标记雷 
	else if(map[i][j]==BOMB)//若翻开的格子有雷，则游戏失败并显示正确答案
	{
		cout<<"已踩雷！游戏结束！"<<endl; an(map);
		cout<<"正确答案为："<<endl;
		for(int p=0;p<10;p++)
		{
			for(int q=0;q<10;q++)
			{
				if(answer[p][q]=='L')//判定为雷 
				{
					cout<<"●";
				}
				else
				{
					cout<<answer[p][q]<<" ";
				}
			}
			cout<<endl;
		} 
		color(15);
		system("pause");
		exit(0);
	}
	else if(map[i][j]==0)//若点开为空格子，则循环调用point函数，逐个翻开周围格子，直到遇到雷 
	{
		show[i][j]=1;//翻开 
		if(i>0&&i<9&&j>0&&j<9)//中间部分 
		{
			for(k=i-1;k<=i+1;k++)//左右扫描 
			{
				for(l=j-1;l<=j+1;l++)//上下扫描 
				{
					if(show[k][l]==0) //翻开且未标记 
					{
						if(map[k][l]!=BOMB)//选中的不是雷 
						{
							show[k][l]=1;//翻开  point(k,l);//将k,l带回point函数 
						}
					}
				}
			}
		}
		else if(i==0&&j>0&&j<9)//左边界格子 
		{
			for(k=i;k<=i+1;k++)
			{
				for(l=j-1;l<=j+1;l++)
				{
					if(show[k][l]==0) 
					{
						if(map[k][l]!=BOMB)
						{
							show[k][l]=1; point(k,l);
						}
					}
				}
			}
		}
		else if(i==9&&j>0&&j<9)//右边界格子 
		{
			for(k=i-1;k<=i;k++)
			{
				for(l=j-1;l<=j+1;l++)
				{
					if(show[k][l]==0) 
					{
						if(map[k][l]!=BOMB)
						{
							show[k][l]=1; point(k,l);
						}
					}
				}
			}
		}
		else if(j==0&&i>0&&i<9)//上边界格子 
		{
			for(k=i-1;k<=i+1;k++)
			{
				for(l=j;l<=j+1;l++)
				{
					if(show[k][l]==0) 
					{
						if(map[k][l]!=BOMB)
						{
							show[k][l]=1; point(k,l);
						}
					}
				}
			}
		}
		else if(j==9&&i>0&&i<9)//下边界格子 
		{
			for(k=i-1;k<=i+1;k++)
			{
				for(l=j-1;l<=j;l++)
				{
					if(show[k][l]==0) 
					{
						if(map[k][l]!=BOMB)
						{
							show[k][l]=1; point(k,l);
						}
					}
				}
			}
		}
		else if(i==0&&j==0)//左上顶点 
		{
			for(k=0;k<=1;k++)
			{
				for(l=0;l<=1;l++)
				{
					if(show[k][l]==0) 
					{
						if(map[k][l]!=BOMB)
						{
							show[k][l]=1; point(k,l);
						}
					}
				}
			}
		}
		else if(i==0&&j==9)//左下顶点 
		{
			for(k=0;k<=1;k++)
			{
				for(l=8;l<=9;l++)
				{
					if(show[k][l]==0) 
					{
						if(map[k][l]!=BOMB)
						{
							show[k][l]=1; point(k,l);
						}
					}
				}
			}
		}
		else if(i==9&&j==0)//右上顶点 
		{
			for(k=8;k<=9;k++)
			{
				for(l=0;l<=1;l++)
				{
					if(show[k][l]==0) 
					{
						if(map[k][l]!=BOMB)
						{
							show[k][l]=1; point(k,l);
						}
					}
				}
			}
		}
		else if(i==9&&j==9)//右下顶点 
		{
			for(k=8;k<=9;k++)
			{
				for(l=8;l<=9;l++)
				{
					if(show[k][l]==0) 
					{
						if(map[k][l]!=BOMB)
						{
							show[k][l]=1; point(k,l);
						}
					}
				}
			}
		}
	}
	else
	show[i][j]=1;//没有雷，且非空的格子直接翻开 
}

//判断胜负 
int judge(int mind[],int show[][10]) 
{
	int i,j;
	int bomb=0,flag=0;
	for(i=0;i<10;i++)
	{
		if(show[mind[i]/10][mind[i]%10]==2)
		bomb++;//地雷数目 
	}
	for(i=0;i<9;i++)
	{
		for(j=0;j<9;j++)
		{
			if(show[i][j]==2)
			flag++;//标记数目 
		}
	}
	if(bomb==10&&flag==10)//雷的数目刚好等于标记数目且都等于10个 
	return 1;//返回1
	else
	return 0;
}

//画地图 
void draw(int show[][10])
{
	gotoxy(1,0);//光标移到第一行 
	color(10);//设定第一行颜色 
	cout<<'A'<<" "<<'B'<<" "<<'C'<<" "<<'D'<<" "<<'E'<<" "<<'F'<<" "<<'G'<<" "<<'H'<<" "<<'I'<<" "<<'J'<<" ";
	gotoxy(0,1);//光标移到第一列 
	int i,j;
	for(i=0;i<10;i++)
	{
		gotoxy(0,i+1);
		color(10);//绿字 
		cout<<(char)(i+65)<<" ";//在第一列的每一行输出字母，65表示ASCII码 
		for(j=0;j<10;j++)
		{
			if(show[i][j]==0)
			{
				color(11);//蓝框 
				cout<<"■";//初始化地图 
			}
			else if(show[i][j]==1)//翻开未标记 
			{
				color(14);
				cout<<map[i][j]<<" ";
			}
			else if(show[i][j]==2)//标记 
			{
				color(12);//红标 
				cout<<"★";
			}
		}
	}
}

//主函数 
int main()
{
	char nx,ny;
	Arrange();//埋地雷 
	char ch,c;
	int row=1,col=1;
	int i,j;
	while(judge(mine,show)!=1)
	{   
		gotoxy(0,0);
		draw(show);
		color(15);
		gotoxy(14,0); 
		cout<<"***欢迎来到扫雷游戏！***";
		gotoxy(14,1);
		cout<<"  请输入对应操作选项：";
		gotoxy(14,2);
		cout<<"    F:标记地雷";
		gotoxy(14,3);
		cout<<"    L:翻格测试";
		gotoxy(14,4);
		ch=getche();
		while(ch!='F'&&ch!='L')
		{
			gotoxy(14,5);
			cout<<"输入有误！";
			gotoxy(14,4);
			ch=getche();
		}
		if(ch=='F')
		{
			gotoxy(14,5);
			cout<<"输入无误！"; 
			gotoxy(14,6);
			color(12);
			cout<<"初始指向格子为(A,A)"; 
			gotoxy(14,7);
			color(15);
			cout<<"A、D控制左右(横坐标)，W、S键控制上下(纵坐标)"; 
			gotoxy(14,8);
			cout<<"请通过小键盘持续操作控制格子指向！";
			gotoxy(14,10);
			cout<<"您当前输入的方向为："; 
			c=getche();
			while(c=='W'||c=='A'||c=='S'||c=='D')
			{
				nx=col;ny=row;
				switch(c)//WASD控制选择的格子位置
				{
					case 'W':row=row-1<0?0:row-1;break;//向上 
					case 'A':col=col-1<0?0:col-1;break;//向左 
					case 'S':row=row+1>9?9:row+1;break;//向右 
					case 'D':col=col+1>9?9:col+1;break;//向下 
				}
				gotoxy(col,row);
				color(15);
				cout<<"■";
				gotoxy(nx,ny);
			    color(11);
			    cout<<"■";
			   gotoxy(14,12);
				color(12); 
			    cout<<"您当前指向的格子是："<<"("<<(char)(col+65)<<","<<(char)(row+65)<<")";
				gotoxy(14,13);
			    color(15);
			    cout<<"确认该格子后请按回车键进行翻牌或者标记地雷！";
				gotoxy(14,10);
				cout<<"您当前输入的方向为："; 
				c=getche();
			}
			show[row][col]=2-show[row][col];
			if(judge(mine,show)==1)
			{
				gotoxy(8,13);
				cout<<"恭喜您！您获胜了！"<<endl;
				system("pause");
				exit(0);
			}
		}
		else if(ch=='L')
		{
			gotoxy(14,5);
			cout<<"输入无误！"; 
			gotoxy(14,6);
			color(12);
			cout<<"初始指向格子为(A,A)"; 
			gotoxy(14,7);
			color(15);
			cout<<"A、D控制左右(横坐标)，W、S键控制上下(纵坐标)"; 
			gotoxy(14,8);
			cout<<"请通过小键盘持续操作控制格子指向！";
			gotoxy(14,10);
			cout<<"您当前输入的方向为："; 
			c=getche();
			while(c=='W'||c=='A'||c=='S'||c=='D')
			{
				nx=col;ny=row;
				switch(c)//WASD控制选择的格子位置
				{
					case 'W':row=row-1<0?0:row-1;break;//向上 
					case 'A':col=col-1<0?0:col-1;break;//向左 
					case 'S':row=row+1>9?9:row+1;break;//向下 
					case 'D':col=col+1>9?9:col+1;break;//向右 
				}
				gotoxy(col,row);
				color(15);
				cout<<"■";
				gotoxy(nx,ny);
			    color(11);
			    cout<<"■";
				gotoxy(14,12);
				color(12); 
			    cout<<"您当前指向的格子是："<<"("<<(char)(col+65)<<","<<(char)(row+65)<<")";
			    gotoxy(14,13);
			    color(15);
			    cout<<"确认该格子后请按回车键进行翻牌或者标记地雷！";
				gotoxy(14,10);
				cout<<"您当前输入的方向为："; 
				c=getche();
                
			}
			point(row,col);
		}
	}
	   system("pause");
	   return 0;
   }
