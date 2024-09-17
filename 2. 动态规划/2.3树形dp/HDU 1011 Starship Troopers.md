**有 n 个洞穴编号为1～n，洞穴间有通道，形成了一个 n-1条边的树, 洞穴的入口即根节点是1。每个洞穴有 x 只 bugs，并有价值 y 的金子，全部消灭完一个洞穴的虫子，就可以获得这个洞穴的 y 个金子. 现在要派 m 个战士去找金子，从入口进入。每次只有消灭完当前洞穴的所有虫子，才可以选择进入下一个洞穴。一个战士可以消灭20只虫子，如果要杀死 x 只虫子，那么要 x/20向上取整即(x+19)/20个战士。如果要获得某个洞穴的金子，必须留下足够杀死所有虫子的战士数量，即(x+19)/20个战士，然后这些留下战士就不能再去其它洞穴其他战士可以继续走去其它洞穴，可以选择分组去不同的洞穴。战士只能往洞穴深处走，不能走回头路问最多能获得多少金子？**

Input

The input contains several test cases. The first line of each test case contains two integers N (0 < N <= 100) and M (0 <= M <= 100), which are the number of rooms in the cavern and the number of starship troopers you have, respectively. The following N lines give the description of the rooms. Each line contains two non-negative integers -- the amount of bugs inside and the possibility of containing a brain, respectively. The next N - 1 lines give the description of tunnels. Each tunnel is described by two integers, which are the indices of the two rooms it connects. Rooms are numbered from 1 and room 1 is the entrance to the cavern.  
  
  
  
The last test case is followed by two -1's.  
  

Output

For each test case, print on a single line the maximum sum of all the possibilities of containing brains for the taken rooms.  
  

Sample Input

5 10
50 10
40 10
40 20
65 30
70 30
1 2
1 3
2 4
2 5
1 1
20 7
-1 -1

Sample Output

50
7

## 题解
我们这一题类似于我们的分组背包，我们以 $dp[i][j]$ 表示，我们给 i 和他的子树安排 j 个人员所能获得的最大值，那么我们的转移就可以有 $dp[i][j]=max(dp[i][j],dp[son][k]+dp[i][j-k])$

```cpp
#include "cstdio"
#include "vector"
#include "cstring"
using namespace std;
#define maxn 500
int bug[maxn],w[maxn],head[maxn],n,m,u,v,tol;
struct Edge
{
    int to,next;
}e[maxn*2];
bool vis[maxn];
int dp[maxn][maxn];
void addedge(int u,int v)
{
    e[tol].to=v;
    e[tol].next=head[u];
    head[u]=tol++;
}
void dfs(int root,int pre)
{
    int i=root,cost=(bug[root]+19)/20;
    for(int i=cost;i<=m;i++) dp[root][i]=w[root];
    for(int a=head[root];a!=-1;a=e[a].next)
    {
        int t=e[a].to;
        if(t==pre) continue;
        dfs(t,root);
        for(int j=m;j>=cost;j--)
            for(int k=1;k<=j-cost;k++)
                dp[i][j]=max(dp[i][j],dp[i][j-k]+dp[t][k]);
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    while(~scanf("%d%d",&n,&m)&&n>0)
    {
        memset(head,-1,sizeof(head));
        memset(dp,0,sizeof(dp));
        tol=0;
        for(int i=1;i<=n;i++)
            scanf("%d%d",&bug[i],&w[i]);
        for(int i=1;i<n;i++)
        {
            scanf("%d%d",&u,&v);
            addedge(u,v);
            addedge(v,u);
        }
        if(m==0) {printf("0\n");continue;}
        dfs(1,1);
        printf("%d\n",dp[1][m]);
    }
    return 0;
}
```