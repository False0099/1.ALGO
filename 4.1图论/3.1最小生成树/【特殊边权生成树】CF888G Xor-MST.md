# Xor-MST

## 题面翻译

- 给定 $n$ 个结点的无向完全图。每个点有一个点权为 $a_i$。连接 $i$ 号结点和 $j$ 号结点的边的边权为 $a_i\oplus a_j$。
- 求这个图的 MST 的权值。
- $1\le n\le 2\times 10^5$，$0\le a_i< 2^{30}$。

## 题目描述

You are given a complete undirected graph with $ n $ vertices. A number $ a_{i} $ is assigned to each vertex, and the weight of an edge between vertices $ i $ and $ j $ is equal to $ a_{i}xora_{j} $ .

Calculate the weight of the minimum spanning tree in this graph.

## 输入格式

The first line contains $ n $ ( $ 1<=n<=200000 $ ) — the number of vertices in the graph.

The second line contains $ n $ integers $ a_{1} $ , $ a_{2} $ , ..., $ a_{n} $ ( $ 0<=a_{i}<2^{30} $ ) — the numbers assigned to the vertices.

## 输出格式

Print one number — the weight of the minimum spanning tree in the graph.

## 样例 #1

### 样例输入 #1

```
5
1 2 3 4 5
```

### 样例输出 #1

```
8
```

## 样例 #2

### 样例输入 #2

```
4
1 2 3 4
```

### 样例输出 #2

```
8
```


## 题解
我们考虑我们最小生成树的步骤，我们每一次操作都是找出我们的最小边，然后用这个边去更新我们的结点。然后我们就能发现，对于本题来说，我们的瓶颈就是在于怎么在不枚举 $n^2$ 条边的前提下，完成我们的排序。

我们首先考虑把我们的每一个元素都插入到我们的 Trie 当中，然后，我们发现，如果我们一个 $a_{i}$ 和 $a_{j}$ 在我们的在 $rt-lca$ 路径上的值一定为 0. 

我们对于任意两个结点，我们找到他们的分离节点（$lca$）并进行标记，不难发现，我们的标记点一共只有我们的 $n-1$ 个。而我们的标记点和我们的 MST 树是相对应的。

然后发现，对于任意一个标记点，要想让它左右子树内的结束节点联通，最优的方法就是在左右子树内各只找一个（叶子）节点，然后把它们连起来。

而在图上，怎么求出我们的标记点？我们能够发现，一个点如果是标记点，那么一定满足：这个结点有两个儿子，反之亦然。

对于怎么找到我们的左右子树中的结点，我们的方法是使用我们的启发式合并。

```cpp
#include<bits/stdc++.h>

#define N 200010
#define ll long long
#define INF 0x7fffffff

using namespace std;

const int B=29;

int n,poww[35],a[N];
int ch[30*N][2],size[30*N],L[30*N],R[30*N];
int node;

void insert(int x,int id)
{
	int u=0;
	for(int i=B;i>=0;i--)
	{
		bool v=(x>>i)&1;
		if(!ch[u][v]) ch[u][v]=++node;
		u=ch[u][v];
		size[u]++;
		if(!L[u]) L[u]=id;
		R[u]=id;
	}
}

int query(int u,int x,int bit)
{
	if(bit<0) return 0;
	bool v=(x>>bit)&1;
	if(ch[u][v]) return query(ch[u][v],x,bit-1);
	else return query(ch[u][v^1],x,bit-1)+poww[bit];
}

ll dfs(int u,int bit)
{
	if(ch[u][0]&&ch[u][1])
	{
		bool v=(size[ch[u][1]]<size[ch[u][0]]);
		int ans=INF;
		for(int i=L[ch[u][v]];i<=R[ch[u][v]];i++)
			ans=min(ans,query(ch[u][v^1],a[i],bit-1)+poww[bit]);
		return dfs(ch[u][0],bit-1)+dfs(ch[u][1],bit-1)+ans;
	}
	if(ch[u][0]) return dfs(ch[u][0],bit-1);
	if(ch[u][1]) return dfs(ch[u][1],bit-1);
	return 0;
}

int main()
{
	poww[0]=1;
	for(int i=1;i<=B;i++)
		poww[i]=poww[i-1]<<1;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++)
		insert(a[i],i);
	printf("%lld\n",dfs(0,B));
	return 0;
}

```