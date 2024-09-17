# Zero Tree

## 题面翻译

题目描述

一棵树是一个有 n 个节点与正好 n-1 条边的图；并且符合以下条件：对于任意两个节点之间有且只有一条简单路径。

我们定义树 T 的子树为一棵所有节点是树 T 节点的子集，所有边是 T 边的子集的树。

给定一颗有 n 个节点的树，假设它的节点被编号为 1 到 n。每个节点有一个权值，$v_i$ 表示编号为 i 的节点的权值。你需要进行一些操作，每次操作符合以下规定：

    - 在给定的这棵树中选择一棵子树，并保证子树中含有节点1
    - 把这棵子树中的所有节点加上或减去1

你需要计算至少需要多少次操作来让所有的节点的权值归零。
输入数据

第一行包含一个整数 n，表示树中节点的数量

接下来的 n-1 行，一行两个整数 u, v，表示 u 和 v 之间有一条边 (u!=v)。

最后一行包含 n 个整数 $v_i$，用空格隔开，表示每个节点的权值
输出数据

一行一个整数，输出最小需要的操作次数。
输入样例
```
3
1 2
1 3
1 -1 1
```
输出样例
```
3
```
数据规模
对于 $30\%$ 的数据，$n\leq100,|vi|\leq1000$

对于 $50\%$ 的数据，$n\leq10^4$

对于 $100\%$ 的数据，$n\leq10^5,|vi|\leq10^9$

Translated by 首相大大

## 题目描述

A tree is a graph with $ n $ vertices and exactly $ n-1 $ edges; this graph should meet the following condition: there exists exactly one shortest (by number of edges) path between any pair of its vertices.

A subtree of a tree $ T $ is a tree with both vertices and edges as subsets of vertices and edges of $ T $ .

You're given a tree with $ n $ vertices. Consider its vertices numbered with integers from 1 to $ n $ . Additionally an integer is written on every vertex of this tree. Initially the integer written on the $ i $ -th vertex is equal to $ v_{i} $ . In one move you can apply the following operation:

1. Select the subtree of the given tree that includes the vertex with number 1.
2. Increase (or decrease) by one all the integers which are written on the vertices of that subtree.

Calculate the minimum number of moves that is required to make all the integers written on the vertices of the given tree equal to zero.

## 输入格式

The first line of the input contains $ n $ ( $ 1<=n<=10^{5} $ ). Each of the next $ n-1 $ lines contains two integers $ a_{i} $ and $ b_{i} $ ( $ 1<=a_{i}, b_{i}<=n; a_{i}≠b_{i} $ ) indicating there's an edge between vertices $ a_{i} $ and $ b_{i} $ . It's guaranteed that the input graph is a tree.

The last line of the input contains a list of $ n $ space-separated integers $ v_{1}, v_{2},..., v_{n} $ ( $ |v_{i}|<=10^{9} $ ).

## 输出格式

Print the minimum number of operations needed to solve the task.

Please, do not write the %lld specifier to read or write 64-bit integers in С++. It is preferred to use the cin, cout streams or the %I 64 d specifier.

## 样例 #1

### 样例输入 #1

```
3
1 2
1 3
1 -1 1
```

### 样例输出 #1

```
3
```

## 题解
我们首先不考虑我们的原问题，我们考虑我们在一个链上，每次我们可以给数组的后缀加一或者减一，问我们变成全 0 数组需要的最小次数。
本题我们要利用一个结论：如果我们的一个操作是在后缀 or 子树 or 前缀加，那么我们的最优策略一定是在保证我们的前缀满足条件的基础上，计算我们当前位置还应该操作多少次。

很显然，我们可以通过枚举我们的后缀，然后计算这个后缀变成我们的目标需要进行多少次加操作，需要进行多少次减操作。分别记为 $f_{1}[i],g_{1}[i]$,然后我们每一次操作就可以由我们下一次操作继承过来，如果我们进行操作后，我们的位置值不为 0，我们就调整我们这个位置的 $f$ 或者 g。

这么做的一大根据是：调整我们的根节点比调整我们的子节点所花费的更少。因此，我们转换到树上问题时，就可以对我们的子树结点信息取 max 后赋值给我们的根节点。


```cpp
#include <bits/stdc++.h>
#define rep(i, n) for (int i = 0; i < (n); ++i)

using std::cin;
using std::cout;
using std::vector;
using std::function;
using ll = long long;

inline void chmax(ll &x, ll y) { if (x < y) x = y; }

int main() {
    int n;
    cin >> n;

    vector<vector<int>> to(n);
    rep(i, n-1) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        to[a].push_back(b);
        to[b].push_back(a);
    } 

    vector<int> w(n);
    rep(i, n) cin >> w[i];

    vector dp(n, vector<ll>(2));
    function<void(int, int)> dfs = [&](int v, int p) -> void {
        for (int u : to[v]) {
            if (u == p) continue;
            dfs(u, v);
            chmax(dp[v][0], dp[u][0]);
            chmax(dp[v][1], dp[u][1]);
        }
        ll x = w[v] + dp[v][0] - dp[v][1];//关键
        dp[v][x>0] += abs(x);
    };

    dfs(0, -1);

    ll ans = dp[0][0] + dp[0][1];
    cout << ans << '\n';

    return 0;
}


```