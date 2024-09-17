The doggie found a bone in an ancient maze, which fascinated him a lot. However, when he picked it up, the maze began to shake, and the doggie could feel the ground sinking. He realized that the bone was a trap, and he tried desperately to get out of this maze.  
  
The maze was a rectangle with sizes N by M. There was a door in the maze. At the beginning, the door was closed and it would open at the T-th second for a short period of time (less than 1 second). Therefore the doggie had to arrive at the door on exactly the T-th second. In every second, he could move one block to one of the upper, lower, left and right neighboring blocks. Once he entered a block, the ground of this block would start to sink and disappear in the next second. He could not stay at one block for more than one second, nor could he move into a visited block. Can the poor doggie survive? Please help him.  

Input

The input consists of multiple test cases. The first line of each test case contains three integers N, M, and T (1 < N, M < 7; 0 < T < 50), which denote the sizes of the maze and the time at which the door will open, respectively. The next N lines give the maze layout, with each line containing M characters. A character is one of the following:  
  
'X': a block of wall, which the doggie cannot enter;  
'S': the start point of the doggie;  
'D': the Door; or  
'.': an empty block.  
  
The input is terminated with three 0's. This test case is not to be processed.  

Output

For each test case, print in one line "YES" if the doggie can survive, or "NO" otherwise.  

Sample

|Inputcopy|Outputcopy|
|---|---|
|4 4 5<br>S.X.<br>..X.<br>..XD<br>....<br>3 4 5<br>S.X.<br>..X.<br>...D<br>0 0 0|NO<br>YES|

## 题解
因为我们本题要求我们恰好在 t 秒到达我们的目标点，所以我们一定要采用我们的 dfs 来进行搜索，而不能用我们的 bfs。

但这一题的数据范围较大，需要我们进行我们的**剪枝优化**

我们可以进行如下剪枝
1.当我们此刻到我们终点的曼哈顿距离大于我们的时间时，这个一定不可行，我们直接跳过。（**可行性**剪枝）
2. 当我们的时间 t，减去我们的哈密顿距离结果并不是奇数，就说明我们不能在 t 步恰好到达，（**奇偶剪枝**）

```cpp
#include <iostream>
#include <cstdio>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <deque>
#include <vector>
#include <queue>
#include <string>
#include <cstring>
#include <map>
#include <stack>
#include <set>
#include <sstream>
#define mod 1000000007
#define eps 1e-6
#define ll long long
#define INF 0x3f3f3f3f
#define MEM(x,y) memset(x,y,sizeof(x))
#define Maxn 10
using namespace std;
int T,n,m,steps;
int ex,ey,sx,sy;;
char mp[Maxn][Maxn];//原始地图
int vis[Maxn][Maxn];//记录人是否走过
int dt[][2]= {{1,0},{-1,0},{0,1},{0,-1}};//四个方向
int dfs(int x,int y,int step)//当前坐标 当前步数
{
    if(x==ex&&y==ey&&step==steps)//满足条件，成功
        return 1;
    for(int i=0; i<4; i++)//四个方向
    {
        int tx=x+dt[i][0];
        int ty=y+dt[i][1];
        if(tx>=0&&tx<n&&ty>=0&&ty<m&&!vis[tx][ty]&&mp[tx][ty]!='X')//判断条件
        {
            vis[tx][ty]=1;
            if(dfs(tx,ty,step+1))//继续搜索
                return 1;
            vis[tx][ty]=0;//回溯
        }
    }
    return 0;
}
int main()
{
    while(cin>>n>>m>>steps,n+m+steps)
    {
        MEM(vis,0);//初始化
        for(int i=0; i<n; i++)
            for(int j=0; j<m; j++)
            {
                cin>>mp[i][j];
                if(mp[i][j]=='S')//起点
                {
                    sx=i,sy=j;
                    vis[sx][sy]=1;//标记
                }
                if(mp[i][j]=='D')//终点
                    ex=i,ey=j;
            }
        if((abs(ex-sx)+abs(ey-sy))%2!=steps%2)//剪枝，不然超时
            cout<<"NO"<<endl;
        else
        {
            if(dfs(sx,sy,0))
                cout<<"YES"<<endl;
            else
                cout<<"NO"<<endl;
        }
    }
}#include <iostream>
#include <cstdio>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <deque>
#include <vector>
#include <queue>
#include <string>
#include <cstring>
#include <map>
#include <stack>
#include <set>
#include <sstream>
#define mod 1000000007
#define eps 1e-6
#define ll long long
#define INF 0x3f3f3f3f
#define MEM(x,y) memset(x,y,sizeof(x))
#define Maxn 10
using namespace std;
int T,n,m,steps;
int ex,ey,sx,sy;;
char mp[Maxn][Maxn];//原始地图
int vis[Maxn][Maxn];//记录人是否走过
int dt[][2]= {{1,0},{-1,0},{0,1},{0,-1}};//四个方向
int dfs(int x,int y,int step)//当前坐标 当前步数
{
    if(x==ex&&y==ey&&step==steps)//满足条件，成功
        return 1;
    for(int i=0; i<4; i++)//四个方向
    {
        int tx=x+dt[i][0];
        int ty=y+dt[i][1];
        if(tx>=0&&tx<n&&ty>=0&&ty<m&&!vis[tx][ty]&&mp[tx][ty]!='X')//判断条件
        {
            vis[tx][ty]=1;
            if(dfs(tx,ty,step+1))//继续搜索
                return 1;
            vis[tx][ty]=0;//回溯
        }
    }
    return 0;
}
int main()
{
    while(cin>>n>>m>>steps,n+m+steps)
    {
        MEM(vis,0);//初始化
        for(int i=0; i<n; i++)
            for(int j=0; j<m; j++)
            {
                cin>>mp[i][j];
                if(mp[i][j]=='S')//起点
                {
                    sx=i,sy=j;
                    vis[sx][sy]=1;//标记
                }
                if(mp[i][j]=='D')//终点
                    ex=i,ey=j;
            }
        if((abs(ex-sx)+abs(ey-sy))%2!=steps%2)//剪枝，不然超时
            cout<<"NO"<<endl;
        else
        {
            if(dfs(sx,sy,0))
                cout<<"YES"<<endl;
            else
                cout<<"NO"<<endl;
        }
    }
}
```