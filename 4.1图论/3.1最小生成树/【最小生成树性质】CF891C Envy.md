# Envy

## 题面翻译

给出一个$ n $ 个点$ m $条边的无向图，每条边有边权，共$ Q $次询问，每次给出$ k_i $条边，问这些边能否同时在一棵最小生成树上。

感谢@mengbierr 提供的翻译

## 题目描述

For a connected undirected weighted graph $ G $ , MST (minimum spanning tree) is a subgraph of $ G $ that contains all of $ G $ 's vertices, is a tree, and sum of its edges is minimum possible.

You are given a graph $ G $ . If you run a MST algorithm on graph it would give you only one MST and it causes other edges to become jealous. You are given some queries, each query contains a set of edges of graph $ G $ , and you should determine whether there is a MST containing all these edges or not.

## 输入格式

The first line contains two integers $ n $ , $ m $ ( $ 2<=n, m<=5·10^{5} $ , $ n-1<=m $ ) — the number of vertices and edges in the graph and the number of queries.

The $ i $ -th of the next $ m $ lines contains three integers $ u_{i} $ , $ v_{i} $ , $ w_{i} $ ( $ u_{i}≠v_{i} $ , $ 1<=w_{i}<=5·10^{5} $ ) — the endpoints and weight of the $ i $ -th edge. There can be more than one edges between two vertices. It's guaranteed that the given graph is connected.

The next line contains a single integer $ q $ ( $ 1<=q<=5·10^{5} $ ) — the number of queries.

 $ q $ lines follow, the $ i $ -th of them contains the $ i $ -th query. It starts with an integer $ k_{i} $ ( $ 1<=k_{i}<=n-1 $ ) — the size of edges subset and continues with $ k_{i} $ distinct space-separated integers from $ 1 $ to $ m $ — the indices of the edges. It is guaranteed that the sum of $ k_{i} $ for $ 1<=i<=q $ does not exceed $ 5·10^{5} $ .

## 输出格式

For each query you should print "YES" (without quotes) if there's a MST containing these edges and "NO" (of course without quotes again) otherwise.

## 样例 #1

### 样例输入 #1

```
5 7
1 2 2
1 3 2
2 3 1
2 4 1
3 4 1
3 5 2
4 5 2
4
2 3 4
3 3 4 5
2 1 7
2 1 2
```

### 样例输出 #1

```
YES
NO
YES
NO
```

## 提示

This is the graph of sample:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF891C/d7f37868e211da76f9c523f75a033c3f4d56f21c.png)Weight of minimum spanning tree on this graph is $ 6 $ .

MST with edges $ (1,3,4,6) $ , contains all of edges from the first query, so answer on the first query is "YES".

Edges from the second query form a cycle of length $ 3 $ , so there is no spanning tree including these three edges. Thus, answer is "NO".
## 题解
考虑我们的最小生成时性质：
1. 我们最小生成树的**边权集合**是确定的，也就是说，我们有多少种边，每种边用多少个是确定的的。
2. 另外，我们的不同的边权是互不影响的。如果我们确定了所有小于 $x$ 的边，那么对于我们的大于 $x$ 的边怎么连接和我们的前面的没有关系。

利用上面性质，对于我们的一条边，我们首先将我们的边按照边权划分为若干个集合，每次对于一个集合，我们检查这个集合上的边是否都能在同一个最小生成树上。然后最后，如果我们每一个集合都可以满足我们的条件，那么我们最后就输出 true。

接下来的问题：怎么**判断一个集合上的权值相同的边都可以在一个最小生成树上**？我们首先考虑从小向大去更新我们的内容，我们先把所有权值小于等于 $x$ 的边连接后形成的 mst 是什么，

那么我们就可以有下面的离线做法：
1. 我们把所有的询问离线，然后把我们的所有询问涉及的边**按照我们的边权进行排序**。并对每一个询问，按照他对我们答案的分类划分
2. 对于一个询问集中的价值边分类，我们去检查我们这个边能否更新前面的 $x-1$ 权值生成树，如果可以，我们就继续，如果不可以，我们认为这个循环不可行
3. 完成一个询问到第二个询问时，我们就去撤销我们的并查集操作后再去进行我们的下一个操作。
4. 检查完所有询问后，我们考虑把我们当前权值的所有边都加入到我们的并查集当中，然后再去用来判定我们的下一个边。


