# [PA 2010] Riddle

## 题目描述

$n$ 个点 $m$ 条边的无向图被分成 $k$ 个部分。每个部分包含一些点。

请选择一些关键点，使得每个部分**恰**有一个关键点，且每条边**至少**有一个端点是关键点。

## 输入格式

第一行三个整数 $n,m,k$。

接下来 $m$ 行，每行两个整数 $a,b$，表示有一条 $a,b$ 间的边。

接下来 $k$ 行，每行第一个整数为 $w$，表示这个部分有 $w$ 个点；接下来 $w$ 个整数，为在这个部分中的点的编号。

## 输出格式

若可能选出请输出 `TAK`，否则输出 `NIE`。

## 样例 #1

### 样例输入 #1

```
6 5 2
1 2
3 1
1 4
5 2
6 2
3 3 4 2
3 1 6 5
```

### 样例输出 #1

```
TAK
```

## 提示

#### 数据规模与约定

对于全部的测试点，保证 $1\le k,w\le n\le 10^6$，$\sum w=n$，$1\le a,b\le n$，$0\le m\le 10^6$。

## 题解
我们这一题需要把我们的约束进行转换，一种约束是：我们每一种颜色都恰有一个关键点，一种是我们的每条边至少有一个点是关键点。我们的一种朴素的思路就是对于我们的每一条边，当作我们的一个约束条件，进行我们的 $2-SAT$ .

也就是说，对于一条边 $(u,v)$，如果 $u$ 不是关键点，那么我们的 $v$ 一定是，如果我们的 $v$ 不是，那么我们的 $u$ 一定是。那么我们就可以把我们的一个点拆位两个，一个表示我们这个点是关键点，我们的这个点不是关键点。

我们考虑我们颜色的限制，假设我们同种颜色中的 5 个当中选中了一个，那么我们的其他四个都不是我们的关键点。另一种是，我们其他四个都不成立，推导出我们的某一个成立，这个是不符合我们的 2-SAT 的问题的，我们考虑进行转换。

对于每“部分”点内的条件转化，首先可以发现每个“部分”至少一个黑点这一条件是无用的。因为若该部分内有至少两个点之间有连边，那么就至少有一个黑点；否则任意两个点之间都没有连边，随便找一个点定为黑点就行。而每个“部分”内只有至多一个黑点一条件，直接处理是将“部分”中每个点 $x$ 对“部分”中其他所有点 $y$,从 $x_1$ 向 $y_0$ 连边。这样做边数是 $O(n^2)$ 级别的，空间、时间都会炸。

我们可以考虑对于每一种颜色连接一个辅助前缀点，连接这个点表示我们和 $0-i$ 的都联通，同样也建立一个辅助后缀点，连接这个点表示我们和 $i-n$ 的都联通。建立这样的前缀后缀点的时间复杂度为 $o(n)$。而我们的每一次连边实际上也只需要和我们的前缀，后缀连边即可，这样我们连边的时间复杂度就变为了 $o(n)$。
![[Pasted image 20240314201041.png]]

![[Pasted image 20240314201047.png]]

那么我们建立我们的这种前缀后缀会不会对我们的答案造成影响呢？答案是并不会，因为我们的 Tarjan 算法只考虑我们两个点之间的连通性是否成环，我们的前缀和后缀显然对于我们的成环是没有任何帮助的。所以我们就可以通过我们的连边来得到我们的答案。

```cpp
//i：不选点i；i+n：选点i
#include<bits/stdc++.h>
using namespace std;

const int N=1e6+10,EN=N*2+N*2,EM=N*2+N*(2*2+2);
int n,m,k;
int h[EN],e[EM],ne[EM],idx;
int part[N];
int vidx;
int pre[N],suf[N];
int dfn[EN],low[EN],num;
int belong[EN],scc;
int st[EN],top;
bool in_st[EN];

void add(int u,int v)
{
    e[++idx]=v,ne[idx]=h[u],h[u]=idx;
    return ;
}

void tarjan(int u)
{
    dfn[u]=low[u]=++num;
    st[++top]=u,in_st[u]=true;
    for(int i=h[u];i!=0;i=ne[i])
    {
        int v=e[i];
        if(!dfn[v])
        {
            tarjan(v);
            low[u]=min(low[u],low[v]);
        }
        else if(in_st[v]) low[u]=min(low[u],dfn[v]);
    }
    if(dfn[u]==low[u])
    {
        scc++;
        int z;
        do
        {
            z=st[top--];
            belong[z]=scc;
            in_st[z]=false;
        }while(z!=u);
    }
    return ;
}

int main()
{
    scanf("%d%d%d",&n,&m,&k);
    for(int i=1;i<=m;i++)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        add(u,v+n),add(v,u+n);
    }
    vidx=2*n;
    for(int i=1;i<=k;i++)
    {
        int w;
        scanf("%d",&w);
        for(int i=1;i<=w;i++) scanf("%d",&part[i]);
        pre[part[1]]=part[1];
        for(int i=2;i<=w;i++)
        {
            pre[part[i]]=++vidx;
            add(pre[part[i]],pre[part[i-1]]),add(pre[part[i]],part[i]);
        }
        suf[part[w]]=part[w];
        for(int i=w-1;i>=2;i--)
        {
            suf[part[i]]=++vidx;
            add(suf[part[i]],suf[part[i+1]]),add(suf[part[i]],part[i]);
        }
        for(int i=1;i<=w;i++)
        {
            if(i!=1) add(part[i]+n,pre[part[i-1]]);
            if(i!=w) add(part[i]+n,suf[part[i+1]]);
        }
    }
    for(int i=1;i<=vidx;i++) if(!dfn[i]) tarjan(i);
    for(int i=1;i<=n;i++)
        if(belong[i]==belong[i+n])
        {
            puts("NIE");
            return 0;
        }
    puts("TAK");
    return 0;
}
```