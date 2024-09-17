# [USACO 10 MAR] Great Cow Gathering G

## 题目描述

Bessie 正在计划一年一度的奶牛大集会，来自全国各地的奶牛将来参加这一次集会。当然，她会选择最方便的地点来举办这次集会。

每个奶牛居住在 $N$ 个农场中的一个，这些农场由 $N-1$ 条道路连接，并且从任意一个农场都能够到达另外一个农场。道路 $i$ 连接农场 $A_i$ 和 $B_i$，长度为 $L_i$。集会可以在 $N$ 个农场中的任意一个举行。另外，每个牛棚中居住着 $C_i$ 只奶牛。

在选择集会的地点的时候，Bessie 希望最大化方便的程度（也就是最小化不方便程度）。比如选择第 $X$ 个农场作为集会地点，它的不方便程度是其它牛棚中每只奶牛去参加集会所走的路程之和（比如，农场 $i$ 到达农场 $X$ 的距离是 $20$，那么总路程就是 $C_i\times 20$）。帮助 Bessie 找出最方便的地点来举行大集会。

## 输入格式

第一行一个整数 $N$ 。

第二到 $N+1$ 行：第 $i+1$ 行有一个整数 $C_i$。

第 $N+2$ 行到 $2N$ 行：第 $i+N+1$ 行为 $3$ 个整数：$A_i,B_i$ 和 $L_i$。

## 输出格式

一行一个整数，表示最小的不方便值。

## 样例 #1

### 样例输入 #1

```
5 
1 
1 
0 
0 
2 
1 3 1 
2 3 2 
3 4 3 
4 5 3
```

### 样例输出 #1

```
15
```

## 提示

$1\leq N\leq 10^5$，$1\leq A_i\leq B_i\leq N$，$0 \leq C_i,L_i \leq 10^3$。


## 题解
因为本题涉及到的是子树相关的问题，于是就是通过我们的换根 dp，来求解，我们首先固定一个点，求出以这个点为起点能够获得的最大权值是多少，我们记为 $dp[root]$,
观察如果已经知道1号节点所需的时间

那么，我们可以做如下假设：

① 所有的牛首先到达了1号节点

② 3号节点以及他子树上的节点都需要退回1->3的路径的长度

③ 除了3号节点以及他子树上的节点都需要前进1->3的路径的长度

通过上面的三条东西，我们就可以从任意一个父节点推出子节点的时间

所以，又是一遍 O(n)的计算就可以推出最终的答案

```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
#define MAX 200100
#define ll long long
inline ll read()
{
      register ll x=0,t=1;
      register char ch=getchar();
      while((ch<'0'||ch>'9')&&ch!='-')ch=getchar();
      if(ch=='-'){t=-1;ch=getchar();}
      while(ch<='9'&&ch>='0'){x=x*10+ch-48;ch=getchar();}
      return x*t;
}

ll dis[MAX],C[MAX],Q[MAX],f[MAX],Sum,Ans=1000000000000000000;

struct Line
{
      ll v,next,w;
}e[MAX];

ll h[MAX],cnt=1,N;

inline void Add(ll u,ll v,ll w)
{
      e[cnt]=(Line){v,h[u],w};
      h[u]=cnt++;
}
//使用两遍DFS
//第一遍以任意点为根节点计算一遍
//dis[i]表示以i为根的子树到根的距离之和 
ll DFS(ll u,ll ff)
{
      ll tot=0;
      for(ll i=h[u];i;i=e[i].next)
      {
               ll v=e[i].v;
               if(v!=ff)
               {
                      ll s=DFS(v,u);//子树上牛的数量 
                      dis[u]+=dis[v]+e[i].w*s;//统计 
                   tot+=s;//牛的个数
               }
      }
      return Q[u]=tot+C[u];
}
//第二遍计算偏移后的值
//先可以假设走到当前节点的父节点
//再让当前自己点所有牛退回来，父节点的所有牛走过去即可 
void DFS2(ll u,ll ff)
{
       for(ll i=h[u];i;i=e[i].next)
       {
                  ll v=e[i].v;
                  if(v!=ff)
                  {
                           ll ss=e[i].w;
                           f[v]=f[u]-Q[v]*ss+(Sum-Q[v])*ss;
                           DFS2(v,u);
                  }
       }
}

int main()
{
      N=read();
      for(ll i=1;i<=N;++i)
        C[i]=read();
      for(ll i=1;i<=N;++i)
        Sum+=C[i];//统计牛的总数 
      for(ll i=1;i<N;++i)
      {
                 ll u=read(),v=read(),w=read();
                 Add(u,v,w);
                 Add(v,u,w);
      }
      
      DFS(1,1);//求出以1为聚集处的结果 
      
      DFS2(1,1);//求出其他的偏移值
      
      for(ll i=1;i<=N;++i)
            Ans=min(Ans,f[i]);
      
        cout<<Ans+dis[1]<<endl;
        
        return 0;
}
```