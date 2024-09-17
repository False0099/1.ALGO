# Vasya and a Tree

## 题面翻译

题意：

Vasya 有一棵树，它有 n 个节点，1 号节点为根节点，初始所有点的权值为0。

定义以下两个东西：

1 函数 d (i, j)

指节点 i 到 j 所经过边的数量。

2 x 节点的 k 级子树

指满足以下条件点的集合：

① x 为该点的祖先，规定自己也是自己的祖先。

② $d(i,j) \leq k$。

Vasya 有 m 条要求要你来解决：

给出 v, d, x，将以 v 节点的 d 级子树的权值加上 x。

当处理完 Vasya 所有的要求时，输出所有点的权值。

输入数据：

第 1 行包括一个整数，n（$1 \leq n \leq 3 \cdot 10^{5}$），含义如上。

第 2 行到第 n 行，包括两个整数 x 和 y（$1 \leq x,y \leq n$），用空格隔开，表示两个点之间有一条边。

第 n+1 行有一个整数 m（$1 \leq m \leq 3 \cdot 10^{5}$），表示有 m 个要求。

第 n+2 行到第 n+m+1 行，有三个整数 v, d, x（$ 1 \leq  v_{i} \leq n , 0 \leq d_{i} \leq 10^{9} , 1 \leq x_{i} \leq 10^{9}$），用空格隔开，含义如上。

输出数据：

共 1 行，包括 n 个数字，用空格隔开，第 i 个数字表示 i 号节点的权值。

样例 1 解释：

在第一次修改后，修改了 1,2,3 号节点，他们的权值加 1，所有的权值为 1,1,1,0,0。

在第二次修改后，修改了 2 号节点，他的权值加 10，所有的权值为 1,11,1,0,0。

在第三次修改后，修改了 4 号节点，他的权值加 100，所有的权值为 1,11,1,100,0。

## 题目描述

Vasya has a tree consisting of $ n $ vertices with root in vertex $ 1 $ . At first all vertices has $ 0 $ written on it.

Let $ d (i, j) $ be the distance between vertices $ i $ and $ j $ , i.e. number of edges in the shortest path from $ i $ to $ j $ . Also, let's denote $ k $ -subtree of vertex $ x $ — set of vertices $ y $ such that next two conditions are met:

- $ x $ is the ancestor of $ y $ (each vertex is the ancestor of itself);
- $ d (x, y) \le k $ .

Vasya needs you to process $ m $ queries. The $ i $ -th query is a triple $ v_i $ , $ d_i $ and $ x_i $ . For each query Vasya adds value $ x_i $ to each vertex from $ d_i $ -subtree of $ v_i $ .

Report to Vasya all values, written on vertices of the tree after processing all queries.

## 输入格式

The first line contains single integer $ n $ ( $ 1 \le n \le 3 \cdot 10^5 $ ) — number of vertices in the tree.

Each of next $ n - 1 $ lines contains two integers $ x $ and $ y $ ( $ 1 \le x, y \le n $ ) — edge between vertices $ x $ and $ y $ . It is guarantied that given graph is a tree.

Next line contains single integer $ m $ ( $ 1 \le m \le 3 \cdot 10^5 $ ) — number of queries.

Each of next $ m $ lines contains three integers $ v_i $ , $ d_i $ , $ x_i $ ( $ 1 \le v_i \le n $ , $ 0 \le d_i \le 10^9 $ , $ 1 \le x_i \le 10^9 $ ) — description of the $ i $ -th query.

## 输出格式

Print $ n $ integers. The $ i $ -th integers is the value, written in the $ i $ -th vertex after processing all queries.

## 样例 #1

### 样例输入 #1

```
5
1 2
1 3
2 4
2 5
3
1 1 1
2 0 10
4 10 100
```

### 样例输出 #1

```
1 11 1 100 0
```

## 样例 #2

### 样例输入 #2

```
5
2 3
2 1
5 4
3 4
5
2 0 4
3 10 1
1 2 3
2 3 10
1 1 7
```

### 样例输出 #2

```
10 24 14 11 11
```

## 提示

In the first exapmle initial values in vertices are $ 0, 0, 0, 0, 0 $ . After the first query values will be equal to $ 1, 1, 1, 0, 0 $ . After the second query values will be equal to $ 1, 11, 1, 0, 0 $ . After the third query values will be equal to $ 1, 11, 1, 100, 0 $ .

## 题解
简要题意就是给定多个操作，每次操作将**与 u 距离小于等于 k 且在 u 子树内的点**点权值加 x ，输出最终各个点的权值。
也就是说，我们这一题给定了若干个修改，要问我们到各个点的权值。我们如果只是采用暴力的修改，我们一定会 tle，所以我们就需要用我们的树上差分。

维护树上差分有两种形式。一种是自上而下的累加标记，这种一般是处理**子树区间加减**；另一种是自下而上的累加标记，这种一般处理树上一条链的区间加减。本题考查的便是前者。

这里，我们的“累加”，可以理解为我们遗产的继承，我们这里与 u 距离小于 k，也就是说我们的第 $k+1$ 代传人不能继承我们现在的遗产了。当然，我们并不知道我们的第 $K+1$ 代传人是谁，但是我们一定可以处理一下，记录为-。然后我们就可以把我们家族累积的财富传给下一代，依次类推，这个就是我们**子树区间加减**的思路。

具体在代码上，我们要注意下面细节：
1. 我们每一次家族遗传传完回到自己这里时，要记得回溯我们对 $k+1$ 代的扣除，因为我们这个时候要进入到我们的另一颗树了。
2. 我们第一次进入某一个点的时候，着一个人的财产一定是已经算明白了的，所以我们就可以直接计算我们在这个位置的答案。
```cpp
#include<bits/stdc++.h>
#define MAXN 300005
#define reg register
#define inl inline
#define int long long
using namespace std;
struct Node
{
	int dep,val;
};
int cnt,fst[MAXN],to[MAXN<<1],nxt[MAXN<<1];
int n,q,dep[MAXN],val[MAXN],ans[MAXN];
vector <Node> vec[MAXN];
inl void AddEdge(reg int u,reg int v)
{
	to[++cnt]=v;
	nxt[cnt]=fst[u];
	fst[u]=cnt;
}
void Dfs(reg int u,reg int pre,reg int sum)
{
	sum+=val[dep[u]];
	for(reg int i=0;i<(int)vec[u].size();i++)
	{
		sum+=vec[u][i].val;
		if(dep[u]+vec[u][i].dep+1<=n) val[dep[u]+vec[u][i].dep+1]-=vec[u][i].val;
	}
	ans[u]=sum;
	for(reg int i=fst[u];i;i=nxt[i])
	{
		reg int v=to[i];
		if(v==pre) continue;
		dep[v]=dep[u]+1;
		Dfs(v,u,sum);
	}
	for(reg int i=0;i<(int)vec[u].size();i++)
	{
		if(dep[u]+vec[u][i].dep+1<=n) val[dep[u]+vec[u][i].dep+1]+=vec[u][i].val;
	}
}
signed main()
{
	scanf("%lld",&n);
	for(reg int i=1;i<n;i++)
	{
		reg int x,y;
		scanf("%lld %lld",&x,&y);
		AddEdge(x,y);
		AddEdge(y,x);
	}
	scanf("%lld",&q);
	for(reg int i=1;i<=q;i++)
	{
		reg int x,y,z;
		scanf("%lld %lld %lld",&x,&y,&z);
		vec[x].push_back((Node){y,z});
	}
	dep[1]=1;
	Dfs(1,0,0);
	for(reg int i=1;i<=n;i++) printf("%lld ",ans[i]);
	return 0;
}
```