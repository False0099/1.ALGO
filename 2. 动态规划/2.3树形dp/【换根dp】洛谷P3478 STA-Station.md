# [POI 2008] STA-Station

## 题目描述

给定一个 $n$ 个点的树，请求出一个结点，使得以这个结点为根时，所有结点的深度之和最大。

一个结点的深度之定义为该节点到根的简单路径上边的数量。

## 输入格式

第一行有一个整数，表示树的结点个数 $n$。  
接下来 $(n - 1)$ 行，每行两个整数 $u, v$，表示存在一条连接 $u, v$ 的边。

## 输出格式

**本题存在 Special Judge**。

输出一行一个整数表示你选择的结点编号。如果有多个结点符合要求，输出任意一个即可。

## 样例 #1

### 样例输入 #1

```
8
1 4
5 6
4 5
6 7
6 8
2 4
3 4
```

### 样例输出 #1

```
7
```

## 提示

#### 样例 1 解释

输出 $7$ 和 $8$ 都是正确答案。

#### 数据规模与约定

对于全部的测试点，保证 $1 \leq n \leq 10^6$，$1 \leq u, v \leq n$，给出的是一棵树。

## 题解
本题是我们的换根 dp 的典中典题目，我们的思路是：先固定我们某一个点为根节点，然后我们计算出以这个根节点转移到我们的子节点的时候，我们的最终结果是多少。

我们考虑推式子，我们假设我们在我们的 u 结点的时候，我们的答案是：
$f[root]=\sum_{v\in son[root]} dep[v]$。
那么我们把我们转换到它的某一个子节点的时候，我们既有有：
$f[v]=\sum_{v\in son[v]}dep[v]-1+(n-siz)$

也就是说，对于我们的 $x$,它的父亲为 $y$,那么我们就有：
$f[x]=f[y]-size[x]+n-size[x].$

```
#include<bits/stdc++.h>
using namespace std;
const int maxn=1000010;
struct edge
{
	int to,nxt;
}e[maxn<<1];
int n,cnt,id;
int head[maxn];
long long ans;
long long f[maxn],dep[maxn],size[maxn];
inline void add(int u,int v)
{
	e[++cnt].nxt=head[u];
	head[u]=cnt;
	e[cnt].to=v;
}
void dfs1(int x,int fa)
{
	size[x]=1;dep[x]=dep[fa]+1;
	for(int i=head[x];i;i=e[i].nxt)
	{
		int y=e[i].to;
		if(y==fa) continue;
		dfs1(y,x);
		size[x]+=size[y];
	}
}
void dfs2(int x,int fa)
{
	for(int i=head[x];i;i=e[i].nxt)
	{
		int y=e[i].to;
		if(y==fa) continue;
		f[y]=f[x]+n-2*size[y];
		dfs2(y,x);
	}
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<n;i++)
	{
		int u,v;scanf("%d%d",&u,&v);
		add(u,v),add(v,u);
	}
	dfs1(1,0);
	for(int i=1;i<=n;i++) f[1]+=dep[i];
	dfs2(1,0);
	for(int i=1;i<=n;i++) if(ans<f[i]) ans=f[i],id=i;
	printf("%d",id);
	return 0;
}

```