Mr. Hdu is an painter, as we all know, painters need ideas to innovate , one day, he got stuck in rut and the ideas dry up, he took out a drawing board and began to draw casually. Imagine the board is a rectangle, consists of several square grids. He drew diagonally, so there are two kinds of draws, one is like ‘\’ , the other is like ‘/’. In each draw he choose arbitrary number of grids to draw. He always drew the first kind in red color, and drew the other kind in blue color, when a grid is drew by both red and blue, it becomes green. A grid will never be drew by the same color more than one time. Now give you the ultimate state of the board, can you calculate the minimum time of draws to reach this state.

## Input

The first line is an integer T describe the number of test cases.  
Each test case begins with an integer number n describe the number of rows of the drawing board.  
Then n lines of string consist of ‘R’ ‘B’ ‘G’ and ‘.’ of the same length. ‘.’ means the grid has not been drawn.  
1<=n<=50  
The number of column of the rectangle is also less than 50.  
Output  
Output an integer as described in the problem description.  

## Output

Output an integer as described in the problem description.

## Sample

|Inputcopy|Outputcopy|
|---|---|
|2<br>4<br>RR.B<br>.RG.<br>.BRR<br>B..R<br>4<br>RRBB<br>RGGB<br>BGGR<br>BBRR|3<br>6|

## 题解
思路：先找混合的，比如说我们先找绿色，然后再根据再对绿色的对角线进行更新
我们记红色为 1，蓝色为 2，绿色为 3，先遍历绿色，针对每一块绿色进行删除，没找到一块绿色，先把他置为 0，然后主对角线上和他挨着的红色或绿色-1，副对角线上的和他挨着的蓝色或绿色-2，ans+2; 直到所有的绿色都遍历完为止。然后再遍历剩余的红色和蓝色，红色块主对角线上和它挨着的红色-1，绿色对角线上和他挨着的蓝色-1，ans+1, 最后输出 ans 即可

```cpp
#include<cstdio>
#include<cstring>
#include<iostream>

using namespace std;

int n,m;
int g[51][51];
int ans=0;
void dfs_1(int x,int y)  //左上
{
    while(g[x][y]==1||g[x][y]==3)
    {
     //   puts("1");
        g[x][y]--;
        x--;
        y--;
    }
}
void dfs_2(int x,int y)  // 右下
{
    while(g[x][y]==1||g[x][y]==3)
    {
    //    puts("1");
        g[x][y]--;
        x++;
        y++;
    }
}
void dfs_3(int x,int y)  // 左下
{
    while(g[x][y]==2||g[x][y]==3)
    {
     //   puts("1");
        g[x][y]-=2;
        x++;
        y--;
    }
}
void dfs_4(int x,int y)  // 右上
{
    while(g[x][y]==2||g[x][y]==3)
    {
    //    puts("1");
        g[x][y]-=2;
        x--;
        y++;
    }
}
int main()
{
    int t;
    scanf("%d",&t);
    while(t--)
    {
        ans=0;
        memset(g,0,sizeof(g));
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
        {
            char cc[51];
            memset(cc,'\0',sizeof(cc));
            scanf("%s",cc);
            m=strlen(cc);
            for(int j=0;j<m;j++)
            {
                if(cc[j]=='R') g[i][j+1]=1;
                if(cc[j]=='B') g[i][j+1]=2;
                if(cc[j]=='G') g[i][j+1]=3;
            }
        }
        for(int a=1;a<=n;a++)
        {
            for(int b=1;b<=m;b++)
            {
                if(g[a][b]==3)
                {
                    g[a][b]=0;
                    dfs_1(a-1,b-1);
                    dfs_2(a+1,b+1);
                    dfs_3(a+1,b-1);
                    dfs_4(a-1,b+1);
                    ans+=2;
                }
            }
        }
        for(int c=1;c<=n;c++)
        {
            for(int d=1;d<=m;d++)
            {
                if(g[c][d]==1)
                {
                    g[c][d]=0;
                    dfs_1(c-1,d-1);
                    dfs_2(c+1,d+1);
                    ans++;
                }
                else if(g[c][d]==2)
                {
                    g[c][d]=2;
                    dfs_3(c+1,d-1);
                    dfs_4(c-1,d+1);
                    ans++;
                }
            }
        }
        printf("%d\n",ans);
    }
}
```