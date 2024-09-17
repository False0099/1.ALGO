# [USACO 17 DEC]Barn Painting G

## 题面翻译

题意：给定一颗 $N$ 个节点组成的树，你要给每个点涂上三种颜色之一，其中有 $K$ 个节点已染色，要求任意两相邻节点颜色不同，求合法染色方案数。

## 题目描述

Farmer John has a large farm with $N$ barns ($1 \le N \le 10^5$), some of which are already painted and some not yet painted. Farmer John wants to paint these remaining barns so that all the barns are painted, but he only has three paint colors available. Moreover, his prize cow Bessie becomes confused if two barns that are directly reachable from one another are the same color, so he wants to make sure this situation does not happen.

It is guaranteed that the connections between the $N$ barns do not form any 'cycles'. That is, between any two barns, there is at most one sequence of connections that will lead from one to the other.


How many ways can Farmer John paint the remaining yet-uncolored barns?

## 输入格式

The first line contains two integers $N$ and $K$ ($0 \le K \le N$), respectively the number of barns on the farm and the number of barns that have already been painted.


The next $N-1$ lines each contain two integers $x$ and $y$ ($1 \le x, y \le N, x \neq y$) describing a path directly connecting barns $x$ and $y$.


The next $K$ lines each contain two integers $b$ and $c$ ($1 \le b \le N$, $1 \le c \le 3$) indicating that barn $b$ is painted with color $c$.

## 输出格式

Compute the number of valid ways to paint the remaining barns, modulo $10^9 + 7$, such that no two barns which are directly connected are the same color.

## 样例 #1

### 样例输入 #1

```
4 1
1 2
1 3
1 4
4 3
```

### 样例输出 #1

```
8
```

## 思路
我们这一题能用树形 DP，在于问题可以分成两个不相关的小问题，我们对于每一个点，**先去找他是不是已经涂过颜色了**，如果涂过颜色，我们这一个点其他颜色的**方案数直接置为 0**，这是因为由于不可能有环，**一个点的赋值只有可能有一次**，**所以当这个点的初始值不为0是，说明已经在条件中被染过色了**。除此之外的所有节点，我们都设置为 1, 之后我们通过**乘法转移**，我们的 $dp[i][j]$ 就表示 $i$ 节点染 $j$ 颜色时的总共的方案数。



```cpp
```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#define p 1000000007
#define LL long long
using namespace std;
inline int read()
{
    int sum=0;
    char ch =getchar();
    while(ch<'0'||ch>'9')
        ch=getchar();
    while(ch>='0'&&ch<='9')
    {
        sum=sum*10+ch-'0';
        ch=getchar();
    }
    return sum;
}
int n,m,tot=0;
int Head[100005],col[100005];//Head用于邻接表  col记录颜色
LL dp[100005][4];
bool visit[100005];//由于存图为无向图，所以要记录下已经走过的点防止死循环
struct tree
{
    int next,node;
}h[200010];
inline void add(int u,int v)//邻接表存图
{
    h[++tot].next=Head[u];
    h[tot].node=v;
    Head[u]=tot;
}
void dfs(int pos)//dfs遍历
{
    visit[pos]=1;
    if(col[pos])//如果已经上过色了，其他两种颜色的方案数为0。
        dp[pos][col[pos]]=1;
    else//三种颜色都可以被♂上
    {
        dp[pos][1]=1;
        dp[pos][2]=1;
        dp[pos][3]=1;
    }
    for(register int i=Head[pos];i;i=h[i].next)//找到当前点所有的子节点
    {
        int v=h[i].node;
        if(!visit[v])
        {
            dfs(v);//一直向下遍历直到叶子节点返回
            dp[pos][1]=dp[pos][1]*((dp[v][2]+dp[v][3])%p)%p;
            dp[pos][2]=dp[pos][2]*((dp[v][1]+dp[v][3])%p)%p;
            dp[pos][3]=dp[pos][3]*((dp[v][2]+dp[v][1])%p)%p;//转移  记得取模！
        }
    }
}
int main()
{
    int x,y;
    n=read();
    m=read();
    for(register int i=1;i<n;++i)
    {
        x=read();
        y=read();
        add(x,y);
        add(y,x);//加边
    }
    for(register int i=1;i<=m;++i)
    {
        x=read();
        y=read();
        col[x]=y;//记录颜色
    }
    dfs(1);//随便把一个点当根就好了
    cout<<(dp[1][1]+dp[1][2]+dp[1][3])%p<<endl;
    return 0;
}
```
```