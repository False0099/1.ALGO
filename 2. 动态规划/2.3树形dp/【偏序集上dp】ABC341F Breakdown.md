### Problem Statement

You are given a simple undirected graph consisting of $N$ vertices and $M$ edges. For $i = 1, 2, \ldots, M$, the $i$ \-th edge connects vertices $u_i$ and $v_i$. Also, for $i = 1, 2, \ldots, N$, vertex $i$ is assigned a positive integer $W_i$, and there are $A_i$ pieces placed on it.

As long as there are pieces on the graph, repeat the following operation:

-   First, choose and remove one piece from the graph, and let $x$ be the vertex on which the piece was placed.
-   Choose a (possibly empty) set $S$ of vertices adjacent to $x$ such that $\sum_{y \in S} W_y \lt W_x$, and place one piece on each vertex in $S$.

Print the maximum number of times the operation can be performed.

It can be proved that, regardless of how the operation is performed, there will be no pieces on the graph after a finite number of iterations.

### Constraints

-   All input values are integers.
-   $2 \leq N \leq 5000$
-   $1 \leq M \leq \min \lbrace N(N-1)/2, 5000 \rbrace$
-   $1 \leq u_i, v_i \leq N$
-   $u_i \neq v_i$
-   $i \neq j \implies \lbrace u_i, v_i \rbrace \neq \lbrace u_j, v_j \rbrace$
-   $1 \leq W_i \leq 5000$
-   $0 \leq A_i \leq 10^9$

### Input

The input is given from Standard Input in the following format:

```
$N$ $M$
$u_1$ $v_1$
$u_2$ $v_2$
$\vdots$
$u_M$ $v_M$
$W_1$ $W_2$ $\ldots$ $W_N$
$A_1$ $A_2$ $\ldots$ $A_N$
```

### Output

Print the answer.

### Sample Input 1

```
6 6
1 2
2 3
3 1
3 4
1 5
5 6
9 2 3 1 4 4
1 0 0 0 0 1
```

### Sample Output 1

```
5
```

In the following explanation, let $A = (A_1, A_2, \ldots, A_N)$ represent the numbers of pieces on the vertices. Initially, $A = (1, 0, 0, 0, 0, 1)$.

Consider performing the operation as follows:

-   Remove one piece from vertex $1$ and place one piece each on vertices $2$ and $3$. Now, $A = (0, 1, 1, 0, 0, 1)$.
-   Remove one piece from vertex $2$. Now, $A = (0, 0, 1, 0, 0, 1)$.
-   Remove one piece from vertex $6$. Now, $A = (0, 0, 1, 0, 0, 0)$.
-   Remove one piece from vertex $3$ and place one piece on vertex $2$. Now, $A = (0, 1, 0, 0, 0, 0)$.
-   Remove one piece from vertex $2$. Now, $A = (0, 0, 0, 0, 0, 0)$.

In this procedure, the operation is performed five times, which is the maximum possible number of times.

## 题解
我们本题首先来解释一下为什么这个游戏是会结束的，因为我们每一次转移都是从我们的一个高点到一个低点。因此每一次转以后，我们的转移次数一定是变小的。

接下来，我们思考如果在一个点上放了棋子，那么他最多能够移动的距离是多少。

这里，我们给出一个结论，如果我们在一个点上进行移动，那么她所有可选的路径一定构成一颗树。感性的理解，如果不是一棵树的话，那么肯定存在环，这与我们的题目中的转移要求是不符合的。

于是，我们就把我们的原问题转换为了一个树形 dp 问题，也就是我们从一个节点出发，我们可以走过的最长的路是多少。



这里，我们首先让我们的“叶子”节点为 0。

接下来，假设我们已经知道了每一个点对应的位置是多少，那么我们似乎就可以求出我们的 $dp[i]=\sum dp[son]$,以一个类似于背包的方式去转移。

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<ll, ll>;
const int N = 5005;
int n, m;
vector<int> es[N];
int cnt[N], A[N], W[N];

int dfs(int u) {
  if (cnt[u]) return cnt[u];
  int C = W[u] - 1;
  vector<int> dp(C + 1, 0);
  for (int v : es[u]) {
    int c = W[v];
    if (c > C) continue;
    int w = dfs(v);
    for (int j = C; j >= c; j--) {
      dp[j] = max(dp[j], dp[j - c] + w);
    }
  }
  cnt[u] = 1 + dp[C];
  return cnt[u];
}

int main() {
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  cin >> n >> m;
  int u, v;
  while (m--) {
    cin >> u >> v;
    es[u].push_back(v);
    es[v].push_back(u);
  }
  for (int i = 1; i <= n; i++) cin >> W[i];
  for (int i = 1; i <= n; i++) cin >> A[i];
  ll ans = 0;
  for (int i = 1; i <= n; i++) {
    ans += 1ll * dfs(i) * A[i];
  }
  cout << ans;
  return 0;
}
```