# [ABC 302 F] Merge Set

## 题面翻译

有 $N$ 个集合 $S_1,S_2,\dots,S_N$，其中 $\left| S_i \right| = A_i,\ S_{i, j} \in [1, M]$。

每次选择两个满足 $\left| S_i \cap S_j \right| \ge 1$ 的集合 $S_i,S_j$，将它们删掉并加上一个新集合 $S_i \cup S_j$。

问最少多少次操作使得存在一个集合 $S_i$ 满足 $1,M \in S_i$。

- $ 1\ \le\ N\ \le\ 2\ \times\ 10^5 $
- $ 2\ \le\ M\ \le\ 2\ \times\ 10^5 $
- $ 1\ \le\ \sum\limits_{i=1}^{N}\ A_i\ \le\ 5\ \times\ 10^5 $
- $ 1\ \le\ S_{i, j}\ \le\ M (1\ \le\ i\ \le\ N, 1\ \le\ j\ \le\ A_i) $
- $ S_{i, j}\ \neq\ S_{i, k}(1\ \le\ j\ <\ k\ \le\ A_i) $

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc302/tasks/abc302_f

黒板に $ 1 $ 以上 $ M $ 以下の整数からなる集合 $ N $ 個 $ S_1, S_2,\dots, S_N $ が書かれています。ここで、$ S_i\ =\ \lbrace\ S_{i, 1}, S_{i, 2},\dots, S_{i, A_i}\ \rbrace $ です。

あなたは、以下の操作を好きな回数（$ 0 $ 回でもよい）行うことが出来ます。

- $ 1 $ 個以上の共通した要素を持つ $ 2 $ 個の集合 $ X, Y $ を選ぶ。$ X, Y $ の $ 2 $ 個を黒板から消し、新たに $ X\cup\ Y $ を黒板に書く。
 
ここで、$ X\cup\ Y $ とは $ X $ か $ Y $ の少なくともどちらかに含まれている要素のみからなる集合を意味します。

$ 1 $ と $ M $ が両方含まれる集合を作ることが出来るか判定してください。出来るならば、必要な操作回数の最小値を求めてください。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ N $ $ M $ $ A_1 $ $ S_{1,1} $ $ S_{1,2} $ $ \dots $ $ S_{1, A_1} $ $ A_2 $ $ S_{2,1} $ $ S_{2,2} $ $ \dots $ $ S_{2, A_2} $ $ \vdots $ $ A_N $ $ S_{N, 1} $ $ S_{N, 2} $ $ \dots $ $ S_{N, A_N} $

## 输出格式

$ 1 $ と $ M $ が両方含まれる集合を作ることが出来るならば必要な操作回数の最小値を、出来ないならば `-1` を出力せよ。

## 样例 #1

### 样例输入 #1

```
3 5
2
1 2
2
2 3
3
3 4 5
```

### 样例输出 #1

```
2
```

## 样例 #2

### 样例输入 #2

```
1 2
2
1 2
```

### 样例输出 #2

```
0
```

## 样例 #3

### 样例输入 #3

```
3 5
2
1 3
2
2 4
3
2 4 5
```

### 样例输出 #3

```
-1
```

## 样例 #4

### 样例输入 #4

```
4 8
3
1 3 5
2
1 2
3
2 4 7
4
4 6 7 8
```

### 样例输出 #4

```
2
```

## 提示

### 制約

- $ 1\ \le\ N\ \le\ 2\ \times\ 10^5 $
- $ 2\ \le\ M\ \le\ 2\ \times\ 10^5 $
- $ 1\ \le\ \sum_{i=1}^{N}\ A_i\ \le\ 5\ \times\ 10^5 $
- $ 1\ \le\ S_{i, j}\ \le\ M (1\ \le\ i\ \le\ N, 1\ \le\ j\ \le\ A_i) $
- $ S_{i, j}\ \neq\ S_{i, k}(1\ \le\ j\ <\ k\ \le\ A_i) $
- 入力は全て整数である。
 
### Sample Explanation 1

まず、$ \lbrace\ 1,2\ \rbrace $ と $ \lbrace\ 2,3\ \rbrace $ を選んで消し、$ \lbrace\ 1,2,3\ \rbrace $ を追加します。 そして、$ \lbrace\ 1,2,3\ \rbrace $ と $ \lbrace\ 3,4,5\ \rbrace $ を選んで消し、$ \lbrace\ 1,2,3,4,5\ \rbrace $ を追加します。 すると $ 2 $ 回の操作で $ 1 $ と $ M $ を両方含む集合を作ることが出来ます。$ 1 $ 回の操作では目標を達成できないため、答えは $ 2 $ です。

### Sample Explanation 2

始めから $ S_1 $ が $ 1, M $ を共に含むため、必要な操作回数の最小値は $ 0 $ 回です。

## 题解
我们本题的思路是：通过我们的一个转换，我们直接在哥哥之间连边的复杂度是 $o(N^2)$ 的，我们这个时候，就需要根据我们的兴致来进行优化。建 $m$ 个元素的点和 $n$ 个集合的点，每个集合向该集合内的元素连一条边权为0的边，元素向集合连一条边权为1的边，然后跑 $1\sim m$ 的最短路。注意到得到的答案是合并1和 $m$ 的最少的集合数量，所以答案要减一。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef pair<int, int> PII;
const int N = 5e5 + 5, M = N, INF = 0x3f3f3f3f;
const LL mod = 1e9 + 7;
int n, m;
int h[N], nxt[M << 1], to[M << 1], val[M << 1], cnt;
int dist[N];
bool st[N];
void add(int u, int v, int w)
{
	to[++ cnt] = v, val[cnt] = w, nxt[cnt] = h[u], h[u] = cnt;
}
void dijkstra(int s)
{
	for(int i = 1;i <= n + m;i ++) dist[i] = INF, st[i] = false;
	priority_queue<PII, vector<PII>, greater<PII> > q;
	dist[s] = 0;
	q.push({0, s});
	while(q.size())
	{
		int u = q.top().second;
		q.pop();
		if(st[u]) continue;
		st[u] = true;
		for(int i = h[u];i;i = nxt[i])
		{
			int v = to[i], w = val[i];
			if(dist[v] > dist[u] + w)
			{
				dist[v] = dist[u] + w;
				q.push({dist[v], v});
			}
		}
	}
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
	cin >> n >> m;
	for(int i = 1; i <= n; i ++)
	{
		int len;
		cin >> len;
		while(len --)
		{
			int x;
			cin >> x;
			add(i, n + x, 0);
			add(n + x, i, 1);
		}
	}
	dijkstra(n + 1);
	if(dist[n + m] == INF) dist[n + m] = 0;
	cout << dist[n + m] - 1 << '\n';
    return 0;
}

```