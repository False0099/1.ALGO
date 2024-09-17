Flip game is played on a rectangular 4x4 field with two-sided pieces placed on each of its 16 squares. One side of each piece is white and the other one is black and each piece is lying either it's black or white side up. Each round you flip 3 to 5 pieces, thus changing the color of their upper side from black to white and vice versa. The pieces to be flipped are chosen every round according to the following rules:  

1. Choose any one of the 16 pieces.  
    
2. Flip the chosen piece and also all adjacent pieces to the left, to the right, to the top, and to the bottom of the chosen piece (if there are any).

  
![](https://vj.csgrandeur.cn/14b4b3ec0b5261bea3a5ad9f1313252c?v=1699169418)Consider the following position as an example:  
  
bwbw  
wwww  
bbwb  
bwwb  
Here "b" denotes pieces lying their black side up and "w" denotes pieces lying their white side up. If we choose to flip the 1st piece from the 3rd row (this choice is shown at the picture), then the field will become:  
  
bwbw  
bwww  
wwwb  
wwwb  
The goal of the game is to flip either all pieces white side up or all pieces black side up. You are to write a program that will search for the minimum number of rounds needed to achieve this goal.  

Input

The input consists of 4 lines with 4 characters "w" or "b" each that denote game field position.

Output

Write to the output file a single integer number - the minimum number of rounds needed to achieve the goal of the game from the given position. If the goal is initially achieved, then write 0. If it's impossible to achieve the goal, then write the word "Impossible" (without quotes).

Sample

|Inputcopy|Outputcopy|
|---|---|
|bwwb<br>bbwb<br>bwwb<br>b www|4|

## 题解
我们这一题其实和我们的灯游戏是相同的，如果我们确定了我们的第一行之后，我们的每一行，都是唯一确定的，此时，我们只需要按照我们的关灯问题计算即可。不过因为我们这一题范围较小，我们也可以考虑直接用我们的 dfs 搜索进行。
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