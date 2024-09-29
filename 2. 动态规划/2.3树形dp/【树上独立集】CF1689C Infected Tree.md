# Infected Tree

## 题面翻译

给定一棵以 $1$ 号节点为根的二叉树，总节点个数为 $n$。

现在 $1$ 号节点感染了病毒，病毒每一回合都会去感染与该节点直接相连的节点，而你在这一回合里可以选择删除任意一个没有被病毒感染（尚未被删除）的点，这样就断开了它与其直接相连的点得关系.

询问最多可以有多少不被病毒感染的点，被删除的点不算做不被病毒感染的点

## 题目描述

Byteland is a beautiful land known because of its beautiful trees.

Misha has found a binary tree with $ n $ vertices, numbered from $ 1 $ to $ n $ . A binary tree is an acyclic connected bidirectional graph containing $ n $ vertices and $ n - 1 $ edges. Each vertex has a degree at most $ 3 $ , whereas the root is the vertex with the number $ 1 $ and it has a degree at most $ 2 $ .

Unfortunately, the root got infected.

The following process happens $ n $ times:

- Misha either chooses a non-infected (and not deleted) vertex and deletes it with all edges which have an end in this vertex or just does nothing.
- Then, the infection spreads to each vertex that is connected by an edge to an already infected vertex (all already infected vertices remain infected).

As Misha does not have much time to think, please tell him what is the maximum number of vertices he can save from the infection (note that deleted vertices are not counted as saved).

## 输入格式

There are several test cases in the input data. The first line contains a single integer $ t $ ( $ 1\leq t\leq 5000 $ ) — the number of test cases. This is followed by the test cases description.

The first line of each test case contains one integer $ n $ ( $ 2\leq n\leq 3\cdot 10^5 $ ) — the number of vertices of the tree.

The $ i $ -th of the following $ n-1 $ lines in the test case contains two positive integers $ u_i $ and $ v_i $ ( $ 1 \leq u_i, v_i \leq n $ ), meaning that there exists an edge between them in the graph.

It is guaranteed that the graph is a binary tree rooted at $ 1 $ . It is also guaranteed that the sum of $ n $ over all test cases won't exceed $ 3\cdot 10^5 $ .

## 输出格式

For each test case, output the maximum number of vertices Misha can save.

## 样例 #1

### 样例输入 #1

```
4
2
1 2
4
1 2
2 3
2 4
7
1 2
1 5
2 3
2 4
5 6
5 7
15
1 2
2 3
3 4
4 5
4 6
3 7
2 8
1 9
9 10
9 11
10 12
10 13
11 14
11 15
```

### 样例输出 #1

```
0
2
2
10
```

## 提示

In the first test case, the only possible action is to delete vertex $ 2 $ , after which we save $ 0 $ vertices in total.

In the second test case, if we delete vertex $ 2 $ , we can save vertices $ 3 $ and $ 4 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1689C/1f479df0f6df9637a1dfee43da055c650bdae647.png)

## 题解
首先，因为我们这是一个**二叉树**，最多只有两个儿子，然后我们的 dp 就非常好转移了，我们设我们的 $dp[i]$ 表示我们根节点 i 被感染，我们能够获得的最大的价值是多少，然后我们就可以用我们的 $dp[i]=max(siz[lson]-1+dp[rson],siz[rson]-1+dp[lson])$
来表示。
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;
const int INF = 0x3f3f3f3f, MAXN = 3e5 + 10;
vector<int> tre[MAXN];
int ch[MAXN], dp[MAXN];
void dfs(int u, int f) {
    ch[f] ++;
    int all = 0;
    for(int v : tre[u]) if(v != f) {
        dfs(v, u);
        ch[u] += ch[v];
        all += dp[v];
    }
    for(int v : tre[u]) if(v != f) {
        dp[u] = max(dp[u], all - dp[v] + ch[v]);
    }
}
void solve() {
    int n;
    cin >> n;
    for(int i = 1; i < n; i ++) {
        int a, b;
        cin >> a >> b;
        tre[a].push_back(b);
        tre[b].push_back(a);
    }
    dfs(1, 0);
    cout << dp[1] << '\n';
    for(int i = 0; i <= n; i ++) {
        tre[i].clear();
        dp[i] = 0;
        ch[i] = 0;
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int _ = 1;
    cin >> _;
    while(_ --) {
        solve();
    }
    return 0;
}
```