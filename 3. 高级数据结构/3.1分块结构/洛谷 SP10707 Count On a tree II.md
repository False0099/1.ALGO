# COT 2 - Count on a tree II

## 题面翻译

- 给定 $n$ 个结点的树，每个结点有一种颜色。
- $m$ 次询问，每次询问给出 $u,v$，回答 $u,v$ 之间的路径上的结点的不同颜色数。
- $1\le n\le 4\times 10^4$，$1\le m\le 10^5$，颜色是不超过 $2 \times 10^9$ 的非负整数。

## 题目描述

You are given a tree with **N** nodes. The tree nodes are numbered from **1** to **N**. Each node has an integer weight.

We will ask you to perform the following operation:

- **u v** : ask for how many different integers that represent the weight of nodes there are on the path from **u** to **v**.

## 输入格式

In the first line there are two integers **N** and **M**. (**N** <= 40000, **M** <= 100000)

In the second line there are **N** integers. The i-th integer denotes the weight of the i-th node.

In the next **N-1** lines, each line contains two integers **u** **v**, which describes an edge (**u**, **v**).

In the next **M** lines, each line contains two integers **u** **v**, which means an operation asking for how many different integers that represent the weight of nodes there are on the path from **u** to **v**.

## 输出格式

For each operation, print its result.

## 样例 #1

### 样例输入 #1

```
8 2
105 2 9 3 8 5 7 7
1 2
1 3
1 4
3 5
3 6
3 7
4 8
2 5
7 8
```

### 样例输出 #1

```
4
4
```

## 题解
我们可以先利用欧拉序，把我们的原问题转化：令 $Z=lca(u,v)$ ，那么在欧拉序李，从 $(u\to v)$ 的这一条路就等于欧拉序上 $pst[v],pre[u]$ 这一段再加上 LCA，再减去这一段区间内出现了两次的数字（这一点我们可以通过我们的修改操作时实现。），就是我们这条路径上的所有点。
之后，我们就只需要**在欧拉序上做莫队**，这也是我们的**树上莫队**

总结：
1. 重链剖分确定我们的欧拉序和我们的 lca
2. 

```cpp
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cmath>
#include <vector>
#define N 200000
using namespace std;
struct node
{
	int l,r,ll,rr,id,lca;
}q[N+5];
int n,m,a[N+5],st[N+5],ed[N+5],dfn[N+5],f[N+5],num,size[N+5],his[N+5],dep[N+5],son[N+5],top[N+5],c[N+5],tmp,blo,l=1,r,use[N+5],ans[N+5],data[N+5];
vector <int> d[N+5];
void dfs1(int u,int fa)  //树剖第一次深搜
{
	f[u]=fa;st[u]=++num;//出现的起始位置
	size[u]=1;his[num]=u;
	dep[u]=dep[fa]+1;
	vector <int>::iterator it;
	for (it=d[u].begin();it!=d[u].end();it++)
	{
		int v=(*it);
		if (v==fa)continue;
		dfs1(v,u);
		size[u]+=size[v];
		if (size[v]>size[son[u]])son[u]=v;
	}
	ed[u]=++num;his[num]=u;
}
void dfs2(int u,int to)   //树剖第二次深搜
{
	top[u]=to;
	if (son[u])dfs2(son[u],to);
	vector <int>::iterator it;
	for (it=d[u].begin();it!=d[u].end();it++)
	{
		int v=(*it);
		if (v!=son[u]&&v!=f[u])dfs2(v,v);
	}
}
int Lca(int x,int y)   //树剖求lca
{
	while (top[x]!=top[y])
	{
		if (dep[top[x]]<dep[top[y]])swap(x,y);
		x=f[top[x]];
	}
	if (dep[x]>dep[y])swap(x,y);
	return x;
}
void add(int x)
{
	tmp+=(++c[a[x]]==1);//添加操作的影响
}
void del(int x)
{
	tmp-=(--c[a[x]]==0);//删除操作的影响
}
void calc(int x)     //对点进行加入或删除
{
	(!use[x])?add(x):del(x);
	use[x]^=1;
}
int cmp(node x,node y)   //排序
{
	return (x.ll==y.ll)?(x.ll%2==1?x.r<y.r:x.r>y.r):x.l<y.l;
}
int main()
{
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++)
		scanf("%d",&a[i]),data[i]=a[i];
    sort(data+1,data+n+1);
    for(int i=1;i<=n;i++)a[i]=lower_bound(data+1,data+n+1,a[i])-data;  //离散化
	int x,y;
	for (int i=1;i<n;i++)
	{
		scanf("%d%d",&x,&y);
		d[x].push_back(y);
		d[y].push_back(x);
	}
	dfs1(1,0); 
	dfs2(1,1);
	blo=n*2/sqrt(m*2/3);
	for (int i=1;i<=m;i++)
	{
		scanf("%d%d",&x,&y);
		if (st[x]>st[y])swap(x,y);  //保证stx<sty
		q[i].id=i;
		q[i].lca=Lca(x,y);  
		if (q[i].lca==x)    //x,y在以x为根的子树中
		{
			q[i].l=st[x];
			q[i].r=st[y];
			q[i].ll=st[x]/blo;//对欧拉序分块
			q[i].rr=st[y]/blo;//对欧拉序分块
			q[i].lca=0;
		}
		else
		{
			q[i].l=ed[x];
			q[i].r=st[y];
			q[i].ll=ed[x]/blo;
			q[i].rr=st[y]/blo;
		}
	}
	sort(q+1,q+m+1,cmp);
	for (int i=1;i<=m;i++)
	{
		while (l>q[i].l)calc(his[--l]);
		while (r<q[i].r)calc(his[++r]);
		while (l<q[i].l)calc(his[l++]);
		while (r>q[i].r)calc(his[r--]);
		if (q[i].lca)calc(q[i].lca);
		ans[q[i].id]=tmp;
		if (q[i].lca)calc(q[i].lca);
	}
	for (int i=1;i<=m;i++)
		printf("%d\n",ans[i]);
	return 0;
}
```
