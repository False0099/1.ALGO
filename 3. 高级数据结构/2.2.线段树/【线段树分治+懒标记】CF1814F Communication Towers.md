# Communication Towers

## 题面翻译

有一张 $n$ 个点 $m$ 条边的无向图，第 $i$ 个点只在第 $L_i$ 到 $R_i$ 这段时间出现。你需要对于每个点 $i$，判断是否存在一个时刻 $x$ ，使得 $i$ 和 $1$ 联通。

$n\leq 2\times 10^5,m\leq 4\times 10^5$

$1\leq L_i\leq R_i\leq 2\times 10^5$

## 题目描述

There are $ n $ communication towers, numbered from $ 1 $ to $ n $ , and $ m $ bidirectional wires between them. Each tower has a certain set of frequencies that it accepts, the $ i $ -th of them accepts frequencies from $ l_i $ to $ r_i $ .

Let's say that a tower $ b $ is accessible from a tower $ a $ , if there exists a frequency $ x $ and a sequence of towers $ a=v_1, v_2, \dots, v_k=b $ , where consecutive towers in the sequence are directly connected by a wire, and each of them accepts frequency $ x $ . Note that accessibility is not transitive, i. e if $ b $ is accessible from $ a $ and $ c $ is accessible from $ b $ , then $ c $ may not be accessible from $ a $ .

Your task is to determine the towers that are accessible from the $ 1 $ -st tower.

## 输入格式

The first line contains two integers $ n $ and $ m $ ( $ 1 \le n \le 2 \cdot 10^5 $ ; $ 0 \le m \le 4 \cdot 10^5 $ ) — the number of communication towers and the number of wires, respectively.

Then $ n $ lines follows, the $ i $ -th of them contains two integers $ l_i $ and $ r_i $ ( $ 1 \le l_i \le r_i \le 2 \cdot 10^5 $ ) — the boundaries of the acceptable frequencies for the $ i $ -th tower.

Then $ m $ lines follows, the $ i $ -th of them contains two integers $ v_i $ and $ u_i $ ( $ 1 \le v_i, u_i \le n $ ; $ v_i \ne u_i $ ) — the $ i $ -th wire that connects towers $ v_i $ and $ u_i $ . There are no two wires connecting the same pair of towers.

## 输出格式

In a single line, print distinct integers from $ 1 $ to $ n $ in ascending order — the indices of the communication towers that are accessible from the $ 1 $ -st tower.

## 样例 #1

### 样例输入 #1

```
6 5
3 5
1 2
2 4
2 3
3 3
4 6
1 3
6 1
3 5
3 6
2 3
```

### 样例输出 #1

```
1 3 5 6
```

## 样例 #2

### 样例输入 #2

```
3 1
2 3
1 4
1 1
1 3
```

### 样例输出 #2

```
1
```

## 样例 #3

### 样例输入 #3

```
5 5
1 3
2 3
2 2
3 5
2 4
1 2
2 3
3 4
4 1
4 5
```

### 样例输出 #3

```
1 2 3 4 5
```

## 题解
本题是我们的 HDU 7436 传送的双倍经验？我们的要维护和我们的某一个特殊点相连的所有点，我们就可以采用我们的并查集上懒标记传递的方法来进行。
```
#include <bits/stdc++.h>
#define int long long
#define endl '\n'
using namespace std;

const int INF = 0x3f3f3f3f3f3f3f3f;
const int N = 2e5 + 10;

struct Msg {
    int x, y, sz;
} stk[N];

int top = 0;
int tag[N];
mt19937 rnd(time(0));

struct Dsu {
    int fa[N], sz[N],rk[N];
    
    void init(int n) {
        for (int i = 1; i <= n; i++) {
            fa[i] = i;
            sz[i] = 1;
            rk[i] = rnd();
        }
    }
    
    int find(int x) {
        return x == fa[x] ? x : find(fa[x]);
    }
    
    bool same(int x, int y) {
        return find(x) == find(y);
    }
    
    void merge(int x, int y) {
        x = find(x), y = find(y);
        if (x == y) return;
        if (sz[x] > sz[y]) swap(x, y);
        fa[x] = y;
        tag[x] -= tag[y];
        sz[y] += sz[x];
        stk[++top] = {x, y, sz[x]};
    }
    
    void resume() {
        Msg t = stk[top--];
        int y = fa[t.x];
        int x = t.x;
        sz[y] -= sz[x];
        tag[x] += tag[y];
        fa[x] = x;
    }
} dsu;

struct node {
    int l, r;
    vector<pair<int, int>> edges;
} tr[N << 2];

void build(int u, int l, int r) {
    tr[u].l = l;
    tr[u].r = r;
    tr[u].edges.clear();
    if (l == r) return;
    int mid = (l + r) / 2;
    build(u << 1, l, mid);
    build(u << 1 | 1, mid + 1, r);
}

void assign(int u, int l, int r, int e1, int e2) {
    if (l <= tr[u].l && tr[u].r <= r) {
        tr[u].edges.push_back({e1, e2});
        return;
    }
    int mid = (tr[u].l + tr[u].r) / 2;
    if (l <= mid) assign(u << 1, l, r, e1, e2);
    if (r > mid) assign(u << 1 | 1, l, r, e1, e2);
}

void dfs(int u) {
    int pref = top;
    for (auto [u, v] : tr[u].edges) {
        dsu.merge(u, v);
    }
    if (tr[u].l == tr[u].r) {
        tag[dsu.find(1)]++;
    } else {
        dfs(u << 1);
        dfs(u << 1 | 1);
    }
    while (pref != top) {
        dsu.resume();
    }
}

void init() {
    // Any initialization logic can go here if needed.
}


void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> l(n+1);
    vector<int> r(n+1);
    for (int i = 1; i <= n; i++) {
        cin >> l[i] >> r[i];
    }
    int max_time = *max_element(begin(r)+1,end(r));
    dsu.init(n);
    build(1, 0, max_time);
    
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        assign(1, max(l[u], l[v]), min(r[u], r[v]), u, v);
    }
    dfs(1);
    for (int i = 1; i <= n; i++) {
        if (tag[i]) {
            cout << i << " ";
        }
    }
    cout << endl;
}

signed main() {
    ios::sync_with_stdio(false), cin.tie(0);
    int t = 1; // Set to 1 for a single test case; adjust as needed.
    init();
    while (t--) {
        solve();
    }
}
```