有一个树形的水系，由 $N-1$ 条河道和 $N$ 个交叉点组成。

我们可以把交叉点看作树中的节点，编号为 $1 \sim N$，河道则看作树中的无向边。

每条河道都有一个容量，连接 $x$ 与 $y$ 的河道的容量记为 $c(x,y)$。

河道中单位时间流过的水量不能超过河道的容量。

有一个节点是整个水系的发源地，可以源源不断地流出水，我们称之为源点。

除了源点之外，树中所有度数为 $1$ 的节点都是入海口，可以吸收无限多的水，我们称之为汇点。

也就是说，水系中的水从源点出发，沿着每条河道，最终流向各个汇点。

在整个水系稳定时，每条河道中的水都以单位时间固定的水量流向固定的方向。

除源点和汇点之外，其余各点不贮存水，也就是流入该点的河道水量之和等于从该点流出的河道水量之和。

整个水系的流量就定义为源点单位时间发出的水量。

在流量不超过河道容量的前提下，求哪个点作为源点时，整个水系的流量最大，输出这个最大值。

#### 输入格式

输入第一行包含整数 $T$，表示共有 $T$ 组测试数据。

每组测试数据，第一行包含整数 $N$。

接下来 $N-1$ 行，每行包含三个整数 $x,y,z$，表示 $x，y$ 之间存在河道，且河道容量为 $z$。

节点编号从 $1$ 开始。

#### 输出格式

每组数据输出一个结果，每个结果占一行。

数据保证结果不超过 $2^{31}-1$。

#### 数据范围

$N \le 2 \times 10^5$

#### 输入样例：

```
1
5
1 2 11
1 4 13
3 4 5
4 5 10
```

#### 输出样例：

```
26
```


## 题解
我们本题是一个标准的换根 dp，即求出以每个数为给是，我们最后的贡献分别是多少。
对于这类问题，我们一般有下面的思路：
1. 我们对我们的树进行第一次扫描，然后看我们以某个点为根时，我们的结果时多少
2. 从我们的结点开始，考虑每一次把根还给我们的子节点时，我们能够获得的改变是多少。

本题，我们的朴素做法是先计算出我们从跟开始，所能经过最大流量就是我们的 $Ds[x]=\sum min(Ds[y],c(x,y)),c(x,y)$。对于我们的每一个 s，我们可以在 $o(n)$ 的时间内求出我们的 $D_{s}$ 数组，如果我们愿意，我们就可以 $o(n^2)$ 的求出我们的数组。

当然，如果我们愿意，我们可以使用“二次扫描与换根法”来代替我们源点的枚举，我们任选一个原点作为我们根节点，记为 $root$,然后我们求出 $D_{root}$,设 $F(x)$ 表示我们把 x 作为原点的最大流量是多少，对于 $x=root$，显然，
假设 $F(x)$ 已经被求出，考虑其子节点 $F(y)$ 的求法：我们每一个 $F(y)$ 包含两个部分：1. 从 y 流向以 y 为根的子树的流量，已经计算并保存在 $D(y)$ 中。2. 从 y 沿着父节点 x 的河道，进而流向水系中其他部分的流量。![[Pasted image 20231019111454.png]]

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <cmath>
using namespace std;
const int N=200001;
int t,n,u,v,w,head[N],numE=0,d[N],du[N],dp[N],ans,s;
struct Edge{
    int next,to,dis;
}e[2*N];
void addEdge(int from,int to,int dis){
    e[++numE].next=head[from];
    e[numE].to=to;
    e[numE].dis=dis;
    head[from]=numE;
}
int dfs_(int x,int l){
    int p=0;d[x]=0;
    for(int j=head[x];j;j=e[j].next){
        int v=e[j].to;
        if(v==l)continue;
        p+=min(e[j].dis,dfs_(v,x));
    }
    if(du[x]!=1)return d[x]=p; 
    else return e[head[x]].dis;
}
void dfs(int x,int l){
    for(int j=head[x];j;j=e[j].next){
        int v=e[j].to;
        if(v==l)continue;
        if(du[x]==1)dp[v]=e[j].dis+d[v];
        else dp[v]=d[v]+min(e[j].dis,dp[x]-min(e[j].dis,d[v]));
        ans=max(ans,dp[v]);
        dfs(v,x);
    }
}
int main() {
    scanf("%d",&t);
    while(t--){
        memset(head,0,sizeof(head));
        memset(d,0,sizeof(d));
        memset(dp,0,sizeof(dp));
        memset(du,0,sizeof(du));
        numE=0;ans=0;
        scanf("%d",&n);
        for(int i=1;i<n;i++){
            scanf("%d%d%d",&u,&v,&w);
            addEdge(u,v,w);addEdge(v,u,w);
            du[u]++;du[v]++;
        }
        dp[1]=dfs_(1,-1);
        dfs(1,-1);
        printf("%d\n",max(dp[1],ans));
    }
    return 0;
}
```