# Lomsat gelral

## 题面翻译

- 有一棵  $n$ 个结点的以  $1$ 号结点为根的**有根树**。
- 每个结点都有一个颜色，颜色是以编号表示的， $i$ 号结点的颜色编号为  $c_i$。
- 如果一种颜色在以  $x$ 为根的子树内出现次数最多，称其在以  $x$ 为根的子树中占**主导地位**。显然，同一子树中可能有多种颜色占主导地位。
- 你的任务是对于每一个  $i\in[1,n]$，求出以  $i$ 为根的子树中，占主导地位的颜色的编号和。
-  $n\le 10^5,c_i\le n$

## 题目描述

You are given a rooted tree with root in vertex $ 1 $ . Each vertex is coloured in some colour.

Let's call colour $ c $ dominating in the subtree of vertex $ v $ if there are no other colours that appear in the subtree of vertex $ v $ more times than colour $ c $ . So it's possible that two or more colours will be dominating in the subtree of some vertex.

The subtree of vertex $ v $ is the vertex $ v $ and all other vertices that contains vertex $ v $ in each path to the root.

For each vertex $ v $ find the sum of all dominating colours in the subtree of vertex $ v $ .

## 输入格式

The first line contains integer $ n $ ( $ 1<=n<=10^{5} $ ) — the number of vertices in the tree.

The second line contains $ n $ integers $ c_{i} $ ( $ 1<=c_{i}<=n $ ), $ c_{i} $ — the colour of the $ i $ -th vertex.

Each of the next $ n-1 $ lines contains two integers $ x_{j}, y_{j} $ ( $ 1<=x_{j}, y_{j}<=n $ ) — the edge of the tree. The first vertex is the root of the tree.

## 输出格式

Print $ n $ integers — the sums of dominating colours for each vertex.

## 样例 #1

### 样例输入 #1

```
4
1 2 3 4
1 2
2 3
2 4
```

### 样例输出 #1

```
10 9 3 4
```

## 样例 #2

### 样例输入 #2

```
15
1 2 3 1 2 3 3 1 1 3 2 2 1 2 3
1 2
1 3
1 4
1 14
1 15
2 5
2 6
2 7
3 8
3 9
3 10
4 11
4 12
4 13
```

### 样例输出 #2

```
6 5 4 3 2 3 3 1 1 3 2 2 1 2 3
```

## 题解
我们第一个思路是通过我们的启发式合并来快速的求出我们每一个节点的颜色有哪些。而我们的更优的思路就是通过我们的线段树合并，
我们对于每一个结点建立一个关于我们 $cnt$ 数组的线段树，最后我们对于每一个结点，合并他和他的所有子树的线段树到一个点上，就能实现我们的最终答案。
```cpp
#include<cstdio>
#include<vector>
#include<cstring>
#include<iostream>
#include<algorithm>
#define lson tr[now].l
#define rson tr[now].r
#define int long long
using namespace std;

struct tree
{
	int l,r,sum,val,ans;
}tr[5000050];

int rt[100010],cl[100010],cnt,n,anss[100010];
vector<int> g[100010];

int push_up(int now)
{
	if(tr[lson].sum>tr[rson].sum)
	{
		tr[now].sum=tr[lson].sum;
		tr[now].val=tr[lson].val;
		tr[now].ans=tr[lson].ans;
	}
	if(tr[rson].sum>tr[lson].sum)
	{
		tr[now].sum=tr[rson].sum;
		tr[now].val=tr[rson].val;
		tr[now].ans=tr[rson].ans;
	}
	if(tr[lson].sum==tr[rson].sum)
	{
		tr[now].sum=tr[lson].sum;
		tr[now].val=tr[lson].val;
		tr[now].ans=tr[lson].ans+tr[rson].ans;
	}
}

int update(int &now,int l,int r,int pos,int v)
{
	if(!now) now=++cnt;
	if(l==r)
	{
		tr[now].val=l;
		tr[now].sum+=v;
		tr[now].ans=l;
		return 0;
	}
	int mid=(l+r)>>1;
	if(pos<=mid) update(lson,l,mid,pos,v);
	else update(rson,mid+1,r,pos,v);
	push_up(now);
}

int merge(int a,int b,int l,int r)
{
	if(!a) return b;
	if(!b) return a;
	if(l==r)
	{
		tr[a].val=l;
		tr[a].sum+=tr[b].sum;
		tr[a].ans=l;
		return a;
	}
	int mid=(l+r)>>1;
	tr[a].l=merge(tr[a].l,tr[b].l,l,mid);
	tr[a].r=merge(tr[a].r,tr[b].r,mid+1,r);
	push_up(a);
	return a;
}

int dfs(int now,int f)
{
	for(int i=0;i<g[now].size();i++)
	{
		if(g[now][i]==f) continue;
		dfs(g[now][i],now);
		merge(rt[now],rt[g[now][i]],1,100000);
	}
	update(rt[now],1,100000,cl[now],1);
	anss[now]=tr[rt[now]].ans;
}

int main()
{
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&cl[i]);
		rt[i]=i;
		cnt++;
	}
	int from,to;
	for(int i=1;i<n;i++)
	{
		scanf("%lld%lld",&from,&to);
		g[from].push_back(to);
		g[to].push_back(from);
	}
	dfs(1,0);
	for(int i=1;i<=n;i++)
	{
		printf("%lld ",anss[i]);
	}
}
```