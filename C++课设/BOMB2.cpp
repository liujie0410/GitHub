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

int map[10][10];//������ͼ������ 
int show[10][10]={{0}}; //��ʾ���������0��ʾδ������δ��ǣ�1��ʾ������2��ʾ���
char answer[10][10];//���û�ʧ��ʱ�����ȷ�� 
int mine[10];//mine���飬��ʾ����λ�ã���ֵ����10*�׵���+�׵��� ������10���� 

//��λ���
void gotoxy(int x,int y)
{
	COORD pos;
	pos.X=2*x;
	pos.Y=y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
}

//�ı�����ַ���ɫ
void color(int a)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),a);
}

//û���׵ĸ��Ӷ�Ӧ������
int count(int map[][10],int i,int j)
{
	int d=0;
	int k,l;
	if(i>0&&i<9&&j>0&&j<9)//�м䲿����ȡһ������ 
	{
		for(k=i-1;k<=i+1;k++)//������ɨ�� 
		{
			for(l=j-1;l<=j+1;l++)//���ϵ���ɨ�� 
			{
				if(map[k][l]==BOMB)
				d++;//���׸�����Χ������Ŀ 
			}
		}
	}
	else if(i==0&&j>0&&j<9)//��߽���ȡһ������ 
	{
		for(k=i;k<=i+1;k++)//����ɨ��һ�� 
		{
			for(l=j-1;l<=j+1;l++)//���ϵ���ɨ�� 
			{
				if(map[k][l]==BOMB)
				d++;
			}
		}
	}
	else if(i==9&&j>0&&j<9)//�ұ߽���ȡһ������ 
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
	else if(j==0&&i>0&&i<9)//�ϱ߽���ȡһ�� 
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
	else if(j==9&&i>0&&i<9)//�±߽���ȡһ�� 
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
	else if(i==0&&j==0)//���϶������� 
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
	else if(i==0&&j==9)//���϶������� 
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
	else if(i==9&&j==0)//���¶������� 
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
	else if(i==9&&j==9)//���¶������� 
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

//�ж������֮ǰ�Ƿ���ֹ������ֹ��򷵻�0�����򷵻�1
int whether(int mine[],int a,int j)
{
	int i;
	for(i=0;i<j;i++)
	{
		if(mine[i]==a)//����λ�ó��ֹ� 
		return 0;
	}
	return 1;
}

//�������׺����� 
void Arrange()
{
	int i,j;
	for(i=0;i<10;i++)
	{
		for(j=0;j<10;j++)  map[i][j]=0;//��ͼ��ʼ�� 
	}
	srand((unsigned)time(NULL)); //�������Ӻ����������ָ���ʼ�� 
	for(i=0;i<10;i++)
	{
		int t=rand()%100;//����һ��100֮�ڵ������ 
		while(whether(mine,t,i)==0)//ÿȡһ�����������һ��whether����������0��ʾ���ֹ�������� 
		t=rand()%100;//����ȡһ������� 
		mine[i]=t;//��������׵�λ�� 
	}
	for(i=0;i<10;i++)
	map[mine[i]/10][mine[i]%10]=BOMB;//���׵�λ�ý�����ؼ��㣬ȷ�����ڵ�ͼ�ϵ��������� 
	for(i=0;i<10;i++)//����ɨ�� 
	{
		for(j=0;j<10;j++)//����ɨ�� 
		{
			if(map[i][j]!=BOMB)//�����׵ĸ��ӵ���count�������õ���Ӧ������ 
			map[i][j]=count(map,i,j);
		}
	}
}

//�𰸾���
void an(int map[][10])
{
	int i,j;
	for(i=0;i<10;i++)//����ɨ�� 
	{
		for(j=0;j<10;j++)//����ɨ�� 
		{
			if(map[i][j]==BOMB) answer[i][j]='L';
			else answer[i][j]=(char)(map[i][j]+48);
		}
	}
}

//������ 
void point(int i,int j)
{
	int k,l;
	if(show[i][j]==2) show[i][j]==2;//����� 
	else if(map[i][j]==BOMB)//�������ĸ������ף�����Ϸʧ�ܲ���ʾ��ȷ��
	{
		cout<<"�Ѳ��ף���Ϸ������"<<endl; an(map);
		cout<<"��ȷ��Ϊ��"<<endl;
		for(int p=0;p<10;p++)
		{
			for(int q=0;q<10;q++)
			{
				if(answer[p][q]=='L')//�ж�Ϊ�� 
				{
					cout<<"��";
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
	else if(map[i][j]==0)//���㿪Ϊ�ո��ӣ���ѭ������point���������������Χ���ӣ�ֱ�������� 
	{
		show[i][j]=1;//���� 
		if(i>0&&i<9&&j>0&&j<9)//�м䲿�� 
		{
			for(k=i-1;k<=i+1;k++)//����ɨ�� 
			{
				for(l=j-1;l<=j+1;l++)//����ɨ�� 
				{
					if(show[k][l]==0) //������δ��� 
					{
						if(map[k][l]!=BOMB)//ѡ�еĲ����� 
						{
							show[k][l]=1;//����  point(k,l);//��k,l����point���� 
						}
					}
				}
			}
		}
		else if(i==0&&j>0&&j<9)//��߽���� 
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
		else if(i==9&&j>0&&j<9)//�ұ߽���� 
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
		else if(j==0&&i>0&&i<9)//�ϱ߽���� 
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
		else if(j==9&&i>0&&i<9)//�±߽���� 
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
		else if(i==0&&j==0)//���϶��� 
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
		else if(i==0&&j==9)//���¶��� 
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
		else if(i==9&&j==0)//���϶��� 
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
		else if(i==9&&j==9)//���¶��� 
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
	show[i][j]=1;//û���ף��ҷǿյĸ���ֱ�ӷ��� 
}

//�ж�ʤ�� 
int judge(int mind[],int show[][10]) 
{
	int i,j;
	int bomb=0,flag=0;
	for(i=0;i<10;i++)
	{
		if(show[mind[i]/10][mind[i]%10]==2)
		bomb++;//������Ŀ 
	}
	for(i=0;i<9;i++)
	{
		for(j=0;j<9;j++)
		{
			if(show[i][j]==2)
			flag++;//�����Ŀ 
		}
	}
	if(bomb==10&&flag==10)//�׵���Ŀ�պõ��ڱ����Ŀ�Ҷ�����10�� 
	return 1;//����1
	else
	return 0;
}

//����ͼ 
void draw(int show[][10])
{
	gotoxy(1,0);//����Ƶ���һ�� 
	color(10);//�趨��һ����ɫ 
	cout<<'A'<<" "<<'B'<<" "<<'C'<<" "<<'D'<<" "<<'E'<<" "<<'F'<<" "<<'G'<<" "<<'H'<<" "<<'I'<<" "<<'J'<<" ";
	gotoxy(0,1);//����Ƶ���һ�� 
	int i,j;
	for(i=0;i<10;i++)
	{
		gotoxy(0,i+1);
		color(10);//���� 
		cout<<(char)(i+65)<<" ";//�ڵ�һ�е�ÿһ�������ĸ��65��ʾASCII�� 
		for(j=0;j<10;j++)
		{
			if(show[i][j]==0)
			{
				color(11);//���� 
				cout<<"��";//��ʼ����ͼ 
			}
			else if(show[i][j]==1)//����δ��� 
			{
				color(14);
				cout<<map[i][j]<<" ";
			}
			else if(show[i][j]==2)//��� 
			{
				color(12);//��� 
				cout<<"��";
			}
		}
	}
}

//������ 
int main()
{
	char nx,ny;
	Arrange();//����� 
	char ch,c;
	int row=1,col=1;
	int i,j;
	while(judge(mine,show)!=1)
	{   
		gotoxy(0,0);
		draw(show);
		color(15);
		gotoxy(14,0); 
		cout<<"***��ӭ����ɨ����Ϸ��***";
		gotoxy(14,1);
		cout<<"  �������Ӧ����ѡ�";
		gotoxy(14,2);
		cout<<"    F:��ǵ���";
		gotoxy(14,3);
		cout<<"    L:�������";
		gotoxy(14,4);
		ch=getche();
		while(ch!='F'&&ch!='L')
		{
			gotoxy(14,5);
			cout<<"��������";
			gotoxy(14,4);
			ch=getche();
		}
		if(ch=='F')
		{
			gotoxy(14,5);
			cout<<"��������"; 
			gotoxy(14,6);
			color(12);
			cout<<"��ʼָ�����Ϊ(A,A)"; 
			gotoxy(14,7);
			color(15);
			cout<<"A��D��������(������)��W��S����������(������)"; 
			gotoxy(14,8);
			cout<<"��ͨ��С���̳����������Ƹ���ָ��";
			gotoxy(14,10);
			cout<<"����ǰ����ķ���Ϊ��"; 
			c=getche();
			while(c=='W'||c=='A'||c=='S'||c=='D')
			{
				nx=col;ny=row;
				switch(c)//WASD����ѡ��ĸ���λ��
				{
					case 'W':row=row-1<0?0:row-1;break;//���� 
					case 'A':col=col-1<0?0:col-1;break;//���� 
					case 'S':row=row+1>9?9:row+1;break;//���� 
					case 'D':col=col+1>9?9:col+1;break;//���� 
				}
				gotoxy(col,row);
				color(15);
				cout<<"��";
				gotoxy(nx,ny);
			    color(11);
			    cout<<"��";
			   gotoxy(14,12);
				color(12); 
			    cout<<"����ǰָ��ĸ����ǣ�"<<"("<<(char)(col+65)<<","<<(char)(row+65)<<")";
				gotoxy(14,13);
			    color(15);
			    cout<<"ȷ�ϸø��Ӻ��밴�س������з��ƻ��߱�ǵ��ף�";
				gotoxy(14,10);
				cout<<"����ǰ����ķ���Ϊ��"; 
				c=getche();
			}
			show[row][col]=2-show[row][col];
			if(judge(mine,show)==1)
			{
				gotoxy(8,13);
				cout<<"��ϲ��������ʤ�ˣ�"<<endl;
				system("pause");
				exit(0);
			}
		}
		else if(ch=='L')
		{
			gotoxy(14,5);
			cout<<"��������"; 
			gotoxy(14,6);
			color(12);
			cout<<"��ʼָ�����Ϊ(A,A)"; 
			gotoxy(14,7);
			color(15);
			cout<<"A��D��������(������)��W��S����������(������)"; 
			gotoxy(14,8);
			cout<<"��ͨ��С���̳����������Ƹ���ָ��";
			gotoxy(14,10);
			cout<<"����ǰ����ķ���Ϊ��"; 
			c=getche();
			while(c=='W'||c=='A'||c=='S'||c=='D')
			{
				nx=col;ny=row;
				switch(c)//WASD����ѡ��ĸ���λ��
				{
					case 'W':row=row-1<0?0:row-1;break;//���� 
					case 'A':col=col-1<0?0:col-1;break;//���� 
					case 'S':row=row+1>9?9:row+1;break;//���� 
					case 'D':col=col+1>9?9:col+1;break;//���� 
				}
				gotoxy(col,row);
				color(15);
				cout<<"��";
				gotoxy(nx,ny);
			    color(11);
			    cout<<"��";
				gotoxy(14,12);
				color(12); 
			    cout<<"����ǰָ��ĸ����ǣ�"<<"("<<(char)(col+65)<<","<<(char)(row+65)<<")";
			    gotoxy(14,13);
			    color(15);
			    cout<<"ȷ�ϸø��Ӻ��밴�س������з��ƻ��߱�ǵ��ף�";
				gotoxy(14,10);
				cout<<"����ǰ����ķ���Ϊ��"; 
				c=getche();
                
			}
			point(row,col);
		}
	}
	   system("pause");
	   return 0;
   }
