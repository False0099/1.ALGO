# [CEOI 2019] Dynamic Diameter

## 题目描述

有一棵树，含 $n$ 个节点，边带权。

会有 $q$ 次修改，每次会将树上的一条边的边权进行修改，在每次修改后，您需要求出每次修改后，这棵树的直径上的边权和。

**本题强制在线。**

## 输入格式

第一行为三个整数 $n,q,w$，分别表示点的个数，询问的个数和边权的上限。

接下来 $n-1$ 行，每一行为三个整数 $a_i,b_i,c_i$，表示 $a_i$ 到 $b_i$ 有一条边权为 $c_i$ 的边。

接下来 $q$ 行，每行两个经过加密的整数 $d_j,e_j$。

解密方式如下：
- $d_j'=(d_j+\text{last})\bmod(n-1)$
- $e_j'=(e_j+\text{last})\bmod w$

其中 $\text{last}$ 表示上一个询问的答案，初值为 $0$。

表示将第 $d_j'+1$ 条边的边权改为 $e_j'$。

## 输出格式

共输出 $q$ 行，一行一个整数，第 $i$ 行的整数表示在第 $i$ 次修改后的直径上的权值总和。

## 样例 #1

### 样例输入 #1

```
4 3 2000
1 2 100
2 3 1000
2 4 1000
2 1030
1 1020
1 890
```

### 样例输出 #1

```
2030
2080
2050
```

## 样例 #2

### 样例输入 #2

```
10 10 10000
1 9 1241
5 6 1630
10 5 1630
2 6 853
10 1 511
5 3 760
8 3 1076
4 10 1483
7 10 40
8 2051
5 6294
5 4168
7 1861
0 5244
6 5156
3 3001
8 5267
5 3102
8 3623
```

### 样例输出 #2

```
6164
7812
8385
6737
6738
7205
6641
7062
6581
5155
```

## 提示

#### 样例 1 解释

解密后的修改如下：
```
2 1030
0 1050
2 970
```
如图为树的边权变化过程，红边代表树的直径：
![](https://cdn.luogu.com.cn/upload/image_hosting/sswn0icz.png)
#### 数据范围
对于 $100\%$ 的数据，保证 $2\le n\le 10^5$，$1\le q\le 10^5$，$1\le w\le 2\times 10^{13}$，$1\le a_i,b_i\le n$，$0\le c_i,e_j<w$，$0\le d_j<n-1$。

详细子任务限制及分值如下表：

| 子任务编号 | 限制 | 分值 |
| :-: |:-:|:-:|
| 1 | $n,q\le 100$ 且 $w\le 10^4$ | $11$ | 
| 2 | $n,q\le 5\times 10^3$ 且 $w\le 10^4$ | $13$ | 
| 3 | $w\le 10^4$ 且边的形式均为 $(1,i)$ | $7$ | 
| 4 | $w\le 10^4$ 且边的形式均为 $(i,2\times i)$ 或 $(i,2\times i+1)$ | $18$ | 
| 5 | 保证有一条直径经过 $1$ 号节点 | $24$ | 
| 6 | 无特殊限制 | $27$ | 
#### 说明
本题译自 [Central-European Olympiad in Informatics 2019](https://ceoi.sk/) [Day 1](https://ceoi.sk/tasks/) [T2 Dynamic Diameter](https://ceoi.sk/static/statements/diameter-ENG.pdf)。

## 题解
我们本题首先需要下面几个性质：
1. 我们的直径具有可合并行，我们两个子树拼接在一起的直径，一定是我们的原来的子树直径 4 个点中某两个点的组合
2. 接下来，如果我们想快速的求出任意两点之间的距离，我们仿照我们的差分思路，转换为我们从 0 点到我们的对应点的距离。

有了前面的两个性质，我们就可以解决我们的子问题 1：求出我们一颗树上的直径。

具体做法如下：
我们利用我们的线段树来求解我们的树的直径，线段树中每一个节点对应的信息就是以这个点为根节点的子树的直径长度，以及直径的两个端点。
而在合并时，我们需要快速的求出我们树上任意两个点之间的距离，这一个我们可以通过维护我们某一个节点到根节点的距离，来得到我们的结果。这里我们是可以通过我们的一个树上差分来快速计算出来的。




而我们的子树信息则通过我们的 dfs 序加上我们的树状数组来维护，其中我们的树状数组表示我们从某个点出发到我们的根节点的值是多少。
```cpp
#include<bits/stdc++.h>

#define int long long

using namespace std;

inline int read(){
	int x=0,f=1;char c=getchar();
	for(;(c<'0'||c>'9');c=getchar()){if(c=='-')f=-1;}
	for(;(c>='0'&&c<='9');c=getchar())x=x*10+(c&15);
	return x*f;
}

const int MN=1e5+5;

int n,q,w;
int fr[MN],to[MN],val[MN];

struct BIT{
	int c[MN];
	int lowbit(int x){return x&(-x);}
	void add(int x,int k){for(int i=x;i<=n;i+=lowbit(i))c[i]+=k;}
	int sum(int x){int res=0;for(int i=x;i;i-=lowbit(i))res+=c[i];return res;}
}T;

struct Edge{
	int to,cost;
	Edge(int T,int C):to(T),cost(C){}
	Edge(){}
};

vector<Edge>G[MN];

namespace HLD{
	int dep[MN],dfn[MN],sz[MN],hson[MN],top[MN],fa[MN];
	int dis[MN],rk[MN];

	void dfs1(int u,int de){
		dep[u]=de,sz[u]=1;
		for(auto e:G[u]){
			int v=e.to,w=e.cost;
			if(v==fa[u])continue;
			dis[v]=dis[u]+w,fa[v]=u,dfs1(v,de+1),sz[u]+=sz[v];
			if(sz[v]>sz[hson[u]])hson[u]=v;
		}
	}

	int tot=0;
	void dfs2(int u,int tp){
		top[u]=tp,dfn[u]=++tot,rk[dfn[u]]=u;
		if(hson[u])dfs2(hson[u],tp);
		for(auto e:G[u]){
			int v=e.to,w=e.cost;
			if(v==fa[u]||v==hson[u])continue;
			dfs2(v,v);
		}
	}

	int LCA(int x,int y){
		while(top[x]!=top[y]){
			if(dep[top[x]]<dep[top[y]])swap(x,y);
			x=fa[top[x]];
		}
		if(dep[x]>dep[y])swap(x,y);
		return x;
	}

	int getdis(int x){return T.sum(dfn[x]);}

	int dist(int x,int y){
		int z=LCA(x,y);
		return getdis(x)+getdis(y)-getdis(z)*2;
	}

	void build(){
		for(int i=1;i<=n;i++)T.add(i,dis[rk[i]]-dis[rk[i-1]]);
	}

	void add(int x,int k){
		int l=dfn[x],r=dfn[x]+sz[x]-1;
		T.add(l,k),T.add(r+1,-k);
	}
};

struct Node{
	int u,v;
	Node(int U,int V):u(U),v(V){}
	Node(){}
};

#define ls(p) (p<<1)
#define rs(p) (p<<1|1)

struct SegTree{
	Node d[MN<<2];

	inline void build(int l,int r,int p){
		if(l==r){
			d[p].u=d[p].v=HLD::rk[l];
			return ;
		}
		int mid=(l+r)>>1;
		build(l,mid,ls(p)),build(mid+1,r,rs(p));
		pushup(p);
	}

	inline void pushup(int p){
		int x=d[ls(p)].u,y=d[ls(p)].v;
		int a=d[rs(p)].u,b=d[rs(p)].v;
		int mx=HLD::dist(x,y),ax=x,ay=y;
		int t=HLD::dist(x,a);if(t>mx)mx=t,ax=x,ay=a;
		t=HLD::dist(x,b);if(t>mx)mx=t,ax=x,ay=b;
		t=HLD::dist(y,a);if(t>mx)mx=t,ax=y,ay=a;
		t=HLD::dist(y,b);if(t>mx)mx=t,ax=y,ay=b;
		t=HLD::dist(a,b);if(t>mx)mx=t,ax=a,ay=b;
		d[p].u=ax,d[p].v=ay;
	}

	inline void modify(int l,int r,int ql,int qr,int p){
		if(l<=ql&&qr<=r)return ;
		int mid=(ql+qr)>>1;
		if(l<=mid)modify(l,r,ql,mid,ls(p));
		if(r>mid)modify(l,r,mid+1,qr,rs(p));
		pushup(p);
	}

	inline int get(){
		return HLD::dist(d[1].u,d[1].v);
	}
}Tree;

signed main(void){

#ifndef ONLINE_JUDGE
	freopen("in.in","r",stdin);
#endif

	n=read(),q=read(),w=read();
	for(int i=1;i<=n-1;i++){
		int u=read(),v=read(),w=read();
		G[u].push_back(Edge(v,w)),G[v].push_back(Edge(u,w));
		fr[i]=u,to[i]=v,val[i]=w;
	}

	HLD::dfs1(1,1),HLD::dfs2(1,1),HLD::build();int lans=0;
	Tree.build(1,n,1);

	// cout<<HLD::getdis(1)<<" "<<HLD::getdis(2)<<" "<<HLD::getdis(3)<<" "<<HLD::getdis(4)<<endl;
	// cout<<Tree.get()<<endl;

	while(q--){
		int d=(read()+lans)%(n-1)+1,e=(read()+lans)%w;
		int u;
		if(HLD::dep[fr[d]]>HLD::dep[to[d]])u=fr[d];
		else u=to[d];
		HLD::add(u,e-val[d]);val[d]=e;//对应的区间加
		Tree.modify(HLD::dfn[u],HLD::dfn[u]+HLD::sz[u]-1,1,n,1);//只修改我们的一部分线段树，不需要全部修改。
		cout<<(lans=Tree.get())<<'\n';
	}

	return 0;
}
```