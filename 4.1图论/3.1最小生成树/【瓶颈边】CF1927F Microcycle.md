## 题目：
Given an undirected weighted graph with $n$ vertices and $m$ edges. There is at most one edge between each pair of vertices in the graph, and the graph does not contain loops (edges from a vertex to itself). The graph is not necessarily connected.

A cycle in the graph is called simple if it doesn't pass through the same vertex twice and doesn't contain the same edge twice.

Find any simple cycle in this graph in which the weight of the lightest edge is minimal.

**Input**

The first line of the input contains a single integer $t$ ($1 \le t \le 10^4$) — the number of test cases. Then follow the descriptions of the test cases.

The first line of each test case contains two integers $n$ and $m$ ($3 \le n \le m \le \min(\frac{n\cdot(n - 1)}{2}, 2 \cdot 10^5)$) — the size of the graph and the number of edges.

The next $m$ lines of the test case contain three integers $u$, $v$, and $w$ ($1 \le u, v \le n$, $u \ne v$, $1 \le w \le 10^6$) — vertices $u$ and $v$ are connected by an edge of weight $w$.

It is guaranteed that there is at most one edge between each pair of vertices. Note that under the given constraints, there is always at least one simple cycle in the graph.

It is guaranteed that the sum of the values of $m$ for all test cases does not exceed $2 \cdot 10^5$.

**Output**

For each test case, output a pair of numbers $b$ and $k$, where:

-   $b$ — the minimum weight of the edge in the found cycle,
-   $k$ — the number of vertices in the found cycle.

On the next line, output $k$ numbers from $1$ to $n$  — the vertices of the cycle in traversal order.

Note that the answer always exists, as under the given constraints, there is always at least one simple cycle in the graph.


## 题解
我们本题要求我们的最小边权环，这里，我们的边权是我们的环中所有边种最小的那一个。

我们仿照 Kruskal 生成树的方法，但是这里我们需要注意，因为我们要求权重最小的，所以我们的边要从大到小排序，然后，我们每一次加边都去检查能否形成一个环，如果可以，那么我们的答案就是这一个边。
```cpp
#include <bits/stdc++.h>

using i64 = long long;
struct DSU {
    std::vector<int> f, siz;
    
    DSU() {}
    DSU(int n) {
        init(n);
    }
    
    void init(int n) {
        f.resize(n);
        std::iota(f.begin(), f.end(), 0);
        siz.assign(n, 1);
    }
    
    int find(int x) {
        while (x != f[x]) {
            x = f[x] = f[f[x]];
        }
        return x;
    }
    
    bool same(int x, int y) {
        return find(x) == find(y);
    }
    
    bool merge(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y) {
            return false;
        }
        siz[x] += siz[y];
        f[y] = x;
        return true;
    }
    
    int size(int x) {
        return siz[find(x)];
    }
};
void solve() {
    int n, m;
    std::cin >> n >> m;
    
    std::vector<std::array<int, 3>> edges(m);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        std::cin >> u >> v >> w;
        u--, v--;
        edges[i] = {w, u, v};
    }
    std::sort(edges.begin(), edges.end(), std::greater());
    
    int ans = 1E9;
    DSU dsu(n);
    int U, V;
    std::vector<std::vector<int>> adj(n);
    for (auto [w, u, v] : edges) {
        if (!dsu.merge(u, v)) {
            ans = w;
            U = u;
            V = v;
        } else {
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
    }
    
    std::vector<int> path;
    auto dfs = [&](auto self, int x, int p) -> bool {
        if (x == V) {
            path.push_back(x);
            return true;
        }
        for (auto y : adj[x]) {
            if (y == p) {
                continue;
            }
            if (self(self, y, x)) {
                path.push_back(x);
                return true;
            }
        }
        return false;
    };
    dfs(dfs, U, -1);
    
    std::cout << ans << " " << path.size() << "\n";
    for (auto x : path) {
        std::cout << x + 1 << " \n"[x == path.back()];
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int t;
    std::cin >> t;
    
    while (t--) {
        solve();
    }
    
    return 0;
}
```