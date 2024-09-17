# [USACO 15 JAN] Grass Cownoisseur G

## 题目描述

In an effort to better manage the grazing patterns of his cows, Farmer John has installed one-way cow paths all over his farm.  The farm consists of N fields, conveniently numbered 1.. N, with each one-way cow path connecting a pair of fields.  For example, if a path connects from field X to field Y, then cows are allowed to travel from X to Y but not from Y to X.

Bessie the cow, as we all know, enjoys eating grass from as many fields as possible.  She always starts in field 1 at the beginning of the day and visits a sequence of fields, returning to field 1 at the end of the day.  She tries to maximize the number of distinct fields along her route, since she gets to eat the grass in each one (if she visits a field multiple times, she only eats the grass there once).

As one might imagine, Bessie is not particularly happy about the one-way restriction on FJ's paths, since this will likely reduce the number of distinct fields she can possibly visit along her daily route.  She wonders how much grass she will be able to eat if she breaks the rules and follows up to one path in the wrong direction. Please compute the maximum number of distinct fields she can visit along a route starting and ending at field 1, where she can follow up to one path along the route in the wrong direction.  Bessie can only travel backwards at most once in her journey.  In particular, she cannot even take the same path backwards twice.

约翰有 $n$ 块草场，编号 $1$ 到 $n$，这些草场由若干条单行道相连。奶牛贝西是美味牧草的鉴赏家，她想到达尽可能多的草场去品尝牧草。


贝西总是从 $1$ 号草场出发，最后回到 $1$ 号草场。她想经过尽可能多的草场，贝西在通一个草场只吃一次草，所以一个草场可以经过多次。因为草场是单行道连接，这给贝西的品鉴工作带来了很大的不便，贝西想偷偷逆向行走一次，但最多只能有一次逆行。问，贝西最多能吃到多少个草场的牧草。

## 输入格式

INPUT: (file grass. In) 

The first line of input contains N and M, giving the number of fields and the number of one-way paths (1 <= N, M <= 100,000). 

The following M lines each describe a one-way cow path.  Each line contains two distinct field numbers X and Y, corresponding to a cow path from X to Y.  The same cow path will never appear more than once.

输入：


第一行：草场数 $n$，道路数 $m$。


以下 $m$ 行，每行 $x$ 和 $y$ 表明有 $x$ 到 $y$ 的单向边，不会有重复的道路出现。

## 输出格式

OUTPUT: (file grass. Out) 

A single line indicating the maximum number of distinct fields Bessie

Can visit along a route starting and ending at field 1, given that she can

Follow at most one path along this route in the wrong direction.

输出：


一个数，逆行一次最多可以走几个草场。

## 样例 #1

### 样例输入 #1

```
7 10 
1 2 
3 1 
2 5 
2 4 
3 7 
3 5 
3 6 
6 5 
7 2 
4 7
```

### 样例输出 #1

```
6
```

## 提示

SOLUTION NOTES:

Here is an ASCII drawing of the sample input:

```cpp
v---3-->6
7   | \ |
^\  v  \|
| \ 1   |
|   |   v
|   v   5
4<--2---^
```

Bessie can visit pastures 1, 2, 4, 7, 2, 5, 3, 1 by traveling

Backwards on the path between 5 and 3.  When she arrives at 3 she

Cannot reach 6 without following another backwards path.

## 题解
我们本题因为有从 1-1 的需求，我们可以贪心的发现，如果我们从一个强连通分量上，我们可以随意走，因此，**我们考虑进行我们的缩点。然后我们再用 SPFA 跑一次以 1 为起点的最长路，记为 $dist[1]$,然后我们再用 SPFA 跑一个以 1 为重点的最长路**，然后我们就变成了在我们的 DAG 上进行我们操作得问题，我们可以考虑用我们的分层图：对于原图上的每一条边，**从原图的指向点到新图的起始点连一条边，边权与原边相同，代表逆向走一条边**。逆向走了一条边，就不能再逆向走了，所以从上面的一层（新图）无法回到下面的一层。

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<stack>
#include<queue>
using namespace std;
const int maxn=100010;
const int inf=2e9;
vector<int>G[maxn];
vector<int>G1[maxn*2];
int n,m,u,v,op,index_,dfn[maxn],low[maxn],bcc[maxn],siz[maxn*2],cnt,dist[maxn*2];
bool tf[maxn*2];
stack<int>st;
queue<int>q;
void dfs(int cur)
{
    dfn[cur]=low[cur]=++index_;
    tf[cur]=true;
    st.push(cur);
    for(int i=0;i<G[cur].size();i++)
    {
        if(!dfn[G[cur][i]])
        {
            dfs(G[cur][i]);
            low[cur]=min(low[cur],low[G[cur][i]]);
        }
        else if(tf[G[cur][i]])low[cur]=min(low[cur],dfn[G[cur][i]]);
    }
    if(dfn[cur]==low[cur])
    {
        cnt++;
        while(st.top()!=cur)
        {
            bcc[st.top()]=cnt;
            tf[st.top()]=false;
            siz[cnt]++;
            st.pop();
        }
        bcc[st.top()]=cnt;
        tf[st.top()]=false;
        siz[cnt]++;
        st.pop();
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    while(m--)
    {
        scanf("%d%d",&u,&v);
        G[u].push_back(v);
    }
    for(int i=1;i<=n;i++)if(!dfn[i])dfs(i);
    for(int i=1;i<=cnt;i++)siz[cnt+i]=siz[i];
    for(int i=1;i<=n;i++)for(int j=0;j<G[i].size();j++)if(bcc[i]!=bcc[G[i][j]])
    {
        G1[bcc[i]].push_back(bcc[G[i][j]]);
        G1[bcc[G[i][j]]].push_back(bcc[i]+cnt);
        G1[bcc[i]+cnt].push_back(bcc[G[i][j]]+cnt);
    }
    tf[bcc[1]]=true;q.push(bcc[1]);
    while(!q.empty())
    {
        int x=q.front();
        for(int i=0;i<G1[x].size();i++)if(dist[G1[x][i]]<dist[x]+siz[x])
        {
            dist[G1[x][i]]=dist[x]+siz[x];
            if(!tf[G1[x][i]])tf[G1[x][i]]=true,q.push(G1[x][i]);
        }
        q.pop();tf[x]=false;
    }
    printf("%d\n",dist[bcc[1]+cnt]);
    return 0;
}
```