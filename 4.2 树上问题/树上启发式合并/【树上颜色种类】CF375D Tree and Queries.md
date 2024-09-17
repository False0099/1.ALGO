# Tree and Queries

## 题面翻译

- 给定一棵 $n$ 个节点的树，根节点为 $1$。每个节点上有一个颜色 $c_i$。$m$ 次操作。操作有一种：
	1. `u k`：询问在以 $u$ 为根的子树中，出现次数 $\ge k$ 的颜色有多少种。
- $2\le n\le 10^5$，$1\le m\le 10^5$，$1\le c_i,k\le 10^5$。

## 题目描述

You have a rooted tree consisting of $ n $ vertices. Each vertex of the tree has some color. We will assume that the tree vertices are numbered by integers from 1 to $ n $ . Then we represent the color of vertex $ v $ as $ c_{v} $ . The tree root is a vertex with number 1.

In this problem you need to answer to $ m $ queries. Each query is described by two integers $ v_{j}, k_{j} $ . The answer to query $ v_{j}, k_{j} $ is the number of such colors of vertices $ x $ , that the subtree of vertex $ v_{j} $ contains at least $ k_{j} $ vertices of color $ x $ .

You can find the definition of a rooted tree by the following link: http://en.wikipedia.org/wiki/Tree\_ (graph\_theory).

## 输入格式

The first line contains two integers $ n $ and $ m $ $ (2<=n<=10^{5}; 1<=m<=10^{5}) $ . The next line contains a sequence of integers $ c_{1}, c_{2},..., c_{n} $ $ (1<=c_{i}<=10^{5}) $ . The next $ n-1 $ lines contain the edges of the tree. The $ i $ -th line contains the numbers $ a_{i}, b_{i} $ $ (1<=a_{i}, b_{i}<=n; a_{i}≠b_{i}) $ — the vertices connected by an edge of the tree.

Next $ m $ lines contain the queries. The $ j $ -th line contains two integers $ v_{j}, k_{j} $ $ (1<=v_{j}<=n; 1<=k_{j}<=10^{5}) $ .

## 输出格式

Print $ m $ integers — the answers to the queries in the order the queries appear in the input.

## 样例 #1

### 样例输入 #1

```
8 5
1 2 2 3 3 2 3 3
1 2
1 5
2 3
2 4
5 6
5 7
5 8
1 2
1 3
1 4
2 3
5 3
```

### 样例输出 #1

```
2
2
1
0
1
```

## 样例 #2

### 样例输入 #2

```
4 1
1 2 3 4
1 2
2 3
3 4
1 1
```

### 样例输出 #2

```
4
```

## 提示

A subtree of vertex $ v $ in a rooted tree with root $ r $ is a set of vertices $ {u : dist (r, v)+dist (v, u)=dist (r, u)} $ . Where $ dist (x, y) $ is the length (in edges) of the shortest path between vertices $ x $ and $ y $ .

## 题解
我们所谓启发式合并，就是要计算子树对于根节点的贡献，然后来加速我们的计算。我们每一次只采用一个数组来计算每一个节点上的信息，因此，所有能归结为子节点对父节点做贡献的问题，我们理论上都可以用启发式合并来进行优化。
在本题中，我们子树中能对我们的根节点做贡献的点，要求这个点的颜色出现的次数是大于 k 次的，而且因为我们的**更新是连续的**，所以对于一个子树中，如果一个颜色出现的次数超过了 m 次，那么从 $1-m$ 一定都会被更新 1，**也就不需要用我们的树状数组计算**。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10, M = 2 * N, INF = 1e9;
int n, m;
int a[N];//a表示我们的每个点对应的颜色
int h[N], e[M], ne[M], idx;
int son[N], l[N], r[N], rw[N], sz[N], ts;//l指起始，r指起始+结束-1，rw指我们dfs序对应的点号
int cnt[N], f[N],sum, maxv;//cnt统计子树下每一种颜色有多少个 ,大于等于i的有多少种颜色 
int ans[N];//每一个询问的答案
vector<pair<int,int>> quu[N];
void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

void update(int u, int v)
{
	if(v==1){
		cnt[a[u]]+=v;
		f[cnt[a[u]]]++;
	}else if(v==-1){
		f[cnt[a[u]]]--;
		cnt[a[u]]+=v;
	}
}

void dfs1(int u, int fa)
{
    sz[u] = 1, l[u] = ++ ts, rw[ts] = u;
    for(int i = h[u]; ~i ; i = ne[i])
    {
        int j = e[i];
        if(j == fa) continue;
        dfs1(j, u);
        sz[u] += sz[j];
        if(sz[j] > sz[son[u]]) son[u] = j;
    }
    r[u] = ts;
}

void dfs2(int u, int fa, int del)
{
    for(int i = h[u]; ~i ; i = ne[i])
    {
        int j = e[i];
        if(j == son[u] || j == fa) continue;
        dfs2(j, u, 1);
    }

    if(son[u]) dfs2(son[u], u, 0);

    for(int i = h[u]; ~i ; i = ne[i])
    {
        int j = e[i];
        if(j == son[u] || j == fa) continue;
        for(int k = l[j] ; k <= r[j] ; k ++ )//更新子树区间内的所有信息
            update(rw[k], 1); // 子树合并
    }
    update(u, 1);
    for(auto tmp:quu[u]){
    	int k=tmp.first;
    	int id=tmp.second;
    	ans[id]=f[k];
	}
    if(del)
    {
        for(int k = l[u]; k <= r[u] ; k ++ ) 
            update(rw[k], -1);
    }
}

signed main()
{
    ios::sync_with_stdio(0), cin.tie(0);
    int q; 
	cin >> n>>q;
    memset(h, -1, sizeof h);
    for(int i = 1; i <= n ; i ++ ) cin >> a[i];
    for(int i = 1 ; i < n ; i ++ )
    {
        int a, b;
        cin >> a >> b;
        add(a, b), add(b, a);
    }
    
	for(int i=1;i<=q;i++){
		int u,k;
		cin>>u>>k;
		quu[u].push_back({k,i});
	}
    dfs1(1, 0);
    dfs2(1, 0, 1);
    for(int i = 1; i <= q ; i ++ ) cout << ans[i] << " ";
    cout << endl;
}
```