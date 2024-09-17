# Tree

## 题目描述

给定一棵 $n$ 个节点的树，每条边有边权，求出树上两点距离小于等于 $k$ 的点对数量。

## 输入格式

第一行输入一个整数 $n$，表示节点个数。  

第二行到第 $n$ 行每行输入三个整数 $u,v,w$ ，表示 $u$ 与 $v$ 有一条边，边权是 $w$。  

第 $n+1$ 行一个整数 $k$ 。

## 输出格式

一行一个整数，表示答案。

## 样例 #1

### 样例输入 #1

```
7
1 6 13 
6 3 9 
3 5 7 
4 1 3 
2 4 20 
4 7 2 
10
```

### 样例输出 #1

```
5
```

## 提示

**数据规模与约定**

对于全部的测试点，保证：  

- $1\leq n\leq 4\times 10^4$。
- $1\leq u,v\leq n$。
- $0\leq w\leq 10^3$。
- $0\leq k\leq 2\times 10^4$。

## 题解
我们要统计我们树上距离小于 k 的路径数，我们就可以把我们的问题分解成下面两类：
1. 两个点的 lca 位根节点
2. 两个点的 lca 不在根节点上

我们每一次进行下面的操作：
1. 统计所有穿过 rt 的路径的大小，（我们**要么通过一些数据结构，要么通过容斥原理**）
2. 对于所有的子节点，我们直接求我们的穿过该子节点的路径

```伪代码
int work(int u){
	rt=find_rt();
	ans=solve(rt);
	for(v in son[u]){
		ans+=work(v);
	}
	return ans;
}
```

我们在这里，使得我们的 rt 是我们的重心，这样我们能够获得更加简单的答案，和更加快速的性质

## 题解
如果求**等于 K**的路径条数，非常简单。

本题求**小于等于K**的路径条数，可以考虑改变统计答案的方法。

原本统计答案是对于一个路径长度len，判断K-len在之前的子树中出现多少次。

现在统计答案是对于一个路径长度len，判断小于等于K-len的数在之前的子树中出现多少次。

之前我们用一个桶数组f来辅助，f[i]表示i这个值是否出现过。

现在我们用树状数组维护桶数组，即可用一个log的复杂度来平衡单点修改和求前缀和的复杂度。

点分治O(logn)，枚举子树O(n)，统计答案O(logn)，由于使用树状数组，常数较小。

```cpp
#include<iostream>
#include<cstring>
#include<cstdio>

using namespace std;

inline int rd(){
    int ret=0,f=1;char c;
    while(c=getchar(),!isdigit(c))f=c=='-'?-1:1;
    while(isdigit(c))ret=ret*10+c-'0',c=getchar();
    return ret*f;
}

const int MAXN=262144;
const int INF=1<<29;

int n,m;

struct Edge{
    int next,to,w;
}e[MAXN<<1];
int ecnt,head[MAXN];
inline void add(int x,int y,int w){
    e[++ecnt].next = head[x];
    e[ecnt].to = y;
    e[ecnt].w = w;
    head[x] = ecnt;
}

int t[MAXN];
void update(int x,int val){
    for(int i=x;i<=m;i+=i&-i)t[i]+=val;
}
int query(int x){
    if(x==0) return 0;
    int ret=0;
    for(int i=x;i;i-=i&-i)ret+=t[i];
    return ret;
}

bool vis[MAXN];

int siz[MAXN];
void getsiz(int x,int pre){
    siz[x]=1;
    for(int i=head[x];i;i=e[i].next){
        int v=e[i].to;
        if(vis[v]||v==pre) continue;
        getsiz(v,x);
        siz[x]+=siz[v];
    }
}
int mn=INF,root;
void getroot(int x,int pre,int tot){
    int mx=0;
    for(int i=head[x];i;i=e[i].next){
        int v=e[i].to;
        if(vis[v]||v==pre) continue;
        mx=max(mx,siz[v]);
        getroot(v,x,tot);
    }
    mx=max(mx,tot-siz[x]);
    if(mx<mn) mn=mx,root=x;
}
int s[MAXN],sav[MAXN];

void dfs(int x,int pre,int dis){
    if(dis>m) return;
    s[++s[0]]=dis;sav[++sav[0]]=dis;
    for(int i=head[x];i;i=e[i].next){
        int v=e[i].to;
        if(vis[v]||v==pre) continue;
        dfs(v,x,dis+e[i].w);
    }
}

int ans;

void dac(int x){//Divide and Conquer :)
    sav[0]=0;mn=n;
    getsiz(x,-1);
    getroot(x,-1,siz[x]);
    int u=root;vis[u]=1;
    for(int i=head[u];i;i=e[i].next){
        int v=e[i].to;
        if(vis[v]) continue;
        s[0]=0;dfs(v,u,e[i].w); 
        for(int j=s[0];j>=1;j--){
            if(s[j]>m) continue;
            ans+=query(m-s[j]);
        }
        for(int j=s[0];j>=1;j--){
            if(s[j]>m) continue;
            update(s[j],1);
            ans++;
        }
    }
    for(int i=sav[0];i>=1;i--){
        if(sav[i]>m) continue;
        update(sav[i],-1);
    }
    //清空树状数组
    for(int i=head[u];i;i=e[i].next){
        int v=e[i].to;
        if(vis[v]) continue;
        dac(v);
    }
}
        
int main(){
    n=rd();
    int x,y,w;
    for(int i=1;i<n;i++){
        x=rd();y=rd();w=rd();
        add(x,y,w);add(y,x,w);
    }
    m=rd();
    dac(1);
    cout<<ans;
    return 0;
}
```


如果我们的 **K 特别大的时候，我们就需要采用另一种做法**，我们要运用我们的容斥原理，我们用我们计算的朴素情况，拿去减掉我们的不合法的情况，我们**拿出从 root 到下面所有点的路径**，我们计算所有这些路径能够拼凑出多少个满足条件的，然后**减去所有来自同一颗子树的路径**，这一部分我们可以用我们的 calc 来**递归的解决**


```
#include<bits/stdc++.h>
using namespace std;
#define il inline
#define re register
#define inf 123456789
il int read()
{
    re int x = 0, f = 1; re char c = getchar();
    while(c < '0' || c > '9') { if(c == '-') f = -1; c = getchar();}
    while(c >= '0' && c <= '9') x = x * 10 + c - 48, c = getchar();
    return x * f;
}
#define rep(i, s, t) for(re int i = s; i <= t; ++ i)
#define drep(i, s, t) for(re int i = t; i >= s; -- i)
#define Next(i, u) for(re int i = head[u]; i; i = e[i].next)
#define mem(k, p) memset(k, p, sizeof(k))
#define maxn 40005
struct edge{int v, w, next;}e[maxn << 1];
int n, m, head[maxn], cnt, k, ans;
int dp[maxn], vis[maxn], sum, dis[maxn], rt, size[maxn], rev[maxn], tot;
il void add(int u, int v, int w)
{
    e[++ cnt] = (edge){v, w, head[u]}, head[u] = cnt;
    e[++ cnt] = (edge){u, w, head[v]}, head[v] = cnt;
}
il void getrt(int u, int fr)
{
    size[u] = 1, dp[u] = 0;
    Next(i, u)
    {
        int v = e[i].v;
        if(v == fr || vis[v]) continue;
        getrt(v, u);
        size[u] += size[v], dp[u] = max(dp[u], size[v]);
    }
    dp[u] = max(dp[u], sum - size[u]);
    if(dp[u] < dp[rt]) rt = u;
}
il void getdis(int u, int fr)
{
    rev[++ tot] = dis[u];
    Next(i, u)
    {
        int v = e[i].v;
        if(v == fr || vis[v]) continue;
        dis[v] = dis[u] + e[i].w;
        getdis(v, u);
    }
}
il int doit(int u, int w)
{
    tot = 0, dis[u] = w, getdis(u, 0);
    sort(rev + 1, rev + tot + 1);
    int l = 1, r = tot, ans = 0;
    while(l <= r) (rev[l] + rev[r] <= k) ? (ans += r - l, ++ l) : (-- r);
    return ans;
}
il void solve(int u)
{
    vis[u] = 1, ans += doit(u, 0);
    Next(i, u)
    {
        int v = e[i].v;
        if(vis[v]) continue;
        ans -= doit(v, e[i].w);
        sum = size[v], dp[0] = n, rt = 0;
        getrt(v, u), solve(rt);
    }
}
int main()
{
    n = read();
    rep(i, 1, n - 1){int u = read(), v = read(), w = read(); add(u, v, w);}
    k = read(), dp[0] = sum = n, getrt(1, 0), solve(rt);
    printf("%d", ans);
    return 0;
}
```