# Linova and Kingdom

## 题面翻译

给定 $n$ 个节点的有根树，根是 $1$ 号节点。

你可以选择 $k$ 个节点将其设置为工业城市，其余设置为旅游城市。

对于一个工业城市，定义它的幸福值为工业城市到根的路径经过的旅游城市的数量。

你需要求出所有工业城市的幸福值之和的最大可能值。

$2\leq n \leq 2\cdot 10^5,1 \leq k<n$

翻译 by Meatherm

## 题目描述

Writing light novels is the most important thing in Linova's life. Last night, Linova dreamed about a fantastic kingdom. She began to write a light novel for the kingdom as soon as she woke up, and of course, she is the queen of it.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1336A/776211708d76e2738717d34c412159f730c6de15.png)There are $ n $ cities and $ n-1 $ two-way roads connecting pairs of cities in the kingdom. From any city, you can reach any other city by walking through some roads. The cities are numbered from $ 1 $ to $ n $ , and the city $ 1 $ is the capital of the kingdom. So, the kingdom has a tree structure.

As the queen, Linova plans to choose exactly $ k $ cities developing industry, while the other cities will develop tourism. The capital also can be either industrial or tourism city.

A meeting is held in the capital once a year. To attend the meeting, each industry city sends an envoy. All envoys will follow the shortest path from the departure city to the capital (which is unique).

Traveling in tourism cities is pleasant. For each envoy, his happiness is equal to the number of tourism cities on his path.

In order to be a queen loved by people, Linova wants to choose $ k $ cities which can maximize the sum of happinesses of all envoys. Can you calculate the maximum sum for her?

## 输入格式

The first line contains two integers $ n $ and $ k $ ( $ 2\le n\le 2 \cdot 10^5 $ , $ 1\le k< n $ ) — the number of cities and industry cities respectively.

Each of the next $ n-1 $ lines contains two integers $ u $ and $ v $ ( $ 1\le u, v\le n $ ), denoting there is a road connecting city $ u $ and city $ v $ .

It is guaranteed that from any city, you can reach any other city by the roads.

## 输出格式

Print the only line containing a single integer — the maximum possible sum of happinesses of all envoys.

## 样例 #1

### 样例输入 #1

```
7 4
1 2
1 3
1 4
3 5
3 6
4 7
```

### 样例输出 #1

```
7
```

## 样例 #2

### 样例输入 #2

```
4 1
1 2
1 3
2 4
```

### 样例输出 #2

```
2
```

## 样例 #3

### 样例输入 #3

```
8 5
7 5
1 7
6 1
3 7
8 3
2 1
4 5
```

### 样例输出 #3

```
9
```

## 提示

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1336A/550bbb250626ee83a75f7874e99bb74967e95572.png)

In the first example, Linova can choose cities $ 2 $ , $ 5 $ , $ 6 $ , $ 7 $ to develop industry, then the happiness of the envoy from city $ 2 $ is $ 1 $ , the happiness of envoys from cities $ 5 $ , $ 6 $ , $ 7 $ is $ 2 $ . The sum of happinesses is $ 7 $ , and it can be proved to be the maximum one.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1336A/42ded7a124702f40fc5538e5ca404a7c3df59128.png)

In the second example, choosing cities $ 3 $ , $ 4 $ developing industry can reach a sum of $ 3 $ , but remember that Linova plans to choose exactly $ k $ cities developing industry, then the maximum sum is $ 2 $ .

## 题解
我们本题的思路是：通过一个类似于我们的 [[【LCA和】洛谷 P3177 树上染色]]问题，去计算。

我们考虑把一个黑色点放在我们的该节点我们的贡献是多少。
首先有个结论：如果有个点被选，那么所有它的后代节点都要被选，因为这样才能达到最大贡献，而这个节点又会让所有后代节点的贡献-1, 所以这个节点对答案的贡献为 -siz $_u$,然后者虑正贡献，显然就是它到根节点的路径上的节点数 (除去本身), 即 $\operatorname{dep}_u-1$,综上对于节点 $u$,它的贡献是 $\operatorname{dep}_u-1$，综上所诉，对于节点 u，他的贡献就是我们的 $-\mathrm{siz}_u+1+dep_{u}$,丢到优先队列里贪心取一手即可。
