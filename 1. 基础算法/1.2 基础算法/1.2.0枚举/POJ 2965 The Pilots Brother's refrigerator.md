The game “The Pilots Brothers: following the stripy elephant” has a quest where a player needs to open a refrigerator.

There are 16 handles on the refrigerator door. Every handle can be in one of two states: open or closed. The refrigerator is open only when all handles are open. The handles are represented as a matrix 4х4. You can change the state of a handle in any location $[i, j]$ (1 ≤ i, j ≤ 4). However, this also changes states of all handles in row **i** and all handles in column **j**.

The task is to determine the minimum number of handle switching necessary to open the refrigerator.

Input

The input contains four lines. Each of the four lines contains four characters describing the initial state of appropriate handles. A symbol “+” means that the handle is in closed state, whereas the symbol “−” means “open”. At least one of the handles is initially closed.

Output

The first line of the input contains N – the minimum number of switching. The rest N lines describe switching sequence. Each of the lines contains a row number and a column number of the matrix separated by one or more spaces. If there are several solutions, you may give any one of them.

Sample

|Inputcopy|Outputcopy|
|---|---|
|-+--<br>----<br>----<br>-+--|6<br>1 1<br>1 3<br>1 4<br>4 1<br>4 3<br>4 4|

## 题解
我们这一题不能说和我们的前一题差别很大，只能说完全一致，我们只需要套用上一个模板，然后修改一下上一个的 change 函数即可。
```cpp
#include <iostream>
#include <algorithm>
using namespace std;
char chess[4][4],now[]={'w','b'}; //棋盘，棋子类型
int ans=1<<27;  //ans初始值，设置为很大的数

char revise(char c) //翻转
{
	if(c==now[0]) return now[1];
	else return now[0];
}

bool in(int x,int y) //判断位置是否可行~
{
	if(x>=0 && x<4 && y>=0 && y<4)
	  return 1;
	return 0;
}

bool isOk(char chess[4][4]) //判断棋盘是否清一色~
{
	for(int i=0;i<4;i++)
	   for(int j=0;j<4;j++)
	      if(chess[i][j]!=chess[0][0]) return 0;
	return 1;
}

void op(int x,int y) //操作：将当前位置以及上下左右的棋子翻转
{
   chess[x][y]=revise(chess[x][y]);
   //如果在边界内，棋子才进行翻转
   if(in(x+1,y))  chess[x+1][y]=revise(chess[x+1][y]); 
   if(in(x-1,y))  chess[x-1][y]=revise(chess[x-1][y]);
   if(in(x,y-1))  chess[x][y-1]=revise(chess[x][y-1]);
   if(in(x,y+1))  chess[x][y+1]=revise(chess[x][y+1]);
}

void dfs(int x,int y,int k) //位置(x,y) , 已操作次数 k
{
   if(isOk(chess)) //清一色~
   {
   	  ans=min(ans,k); //要最少次数
   	  return;
   }

    if(!in(x,y)) return; //不在范围内，返回
    
    int newy=(y+1)%4;   //得到下一个位置的坐标（y为0 1 2 3）
    int newx=x+(y+1)/4; //x的值，取决于y+1是否等于4，等于则x+1
    
	dfs(newx,newy,k);//这一步不操作 
	op(x,y);
	dfs(newx,newy,k+1);//这一步操作 
	op(x,y);  //回溯
}

int main()
{
   for(int i=0;i<4;i++)
     for(int j=0;j<4;j++)
	   cin>>chess[i][j];
	
    dfs(0,0,0);
	if(ans==1<<27) cout<<"Impossible";
	else cout<<ans; 
   return 0;
}
```