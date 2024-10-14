# Rendez-vous de Marian et Robin

## 题目描述

In the humble act of meeting, joy doth unfold like a flower in bloom.



Absence makes the heart grow fonder. Marian sold her last ware at the Market at the same time Robin finished training at the Major Oak. They couldn't wait to meet, so they both start without delay.

The travel network is represented as $ n $ vertices numbered from $ 1 $ to $ n $ and $ m $ edges. The $ i $ -th edge connects vertices $ u_i $ and $ v_i $ , and takes $ w_i $ seconds to travel (all $ w_i $ are even). Marian starts at vertex $ 1 $ (Market) and Robin starts at vertex $ n $ (Major Oak).

In addition, $ h $ of the $ n $ vertices each has a single horse available. Both Marian and Robin are capable riders, and could mount horses in no time (i.e. in $ 0 $ seconds). Travel times are halved when riding. Once mounted, a horse lasts the remainder of the travel. Meeting must take place on a vertex (i.e. not on an edge). Either could choose to wait on any vertex.

Output the earliest time Robin and Marian can meet. If vertices $ 1 $ and $ n $ are disconnected, output $ -1 $ as the meeting is cancelled.

## 输入格式

The first line of the input contains a single integer $ t $ ( $ 1\leq t \leq 10^4 $ ) — the number of test cases.

The first line of each test case consists of three integers $ n $ , $ m $ , $ h $ ( $ 2 \le n \le 2 \cdot 10^5, \; 1 \le m \le 2 \cdot 10^5, \; 1 \le h \le n $ ) — the number of vertices, the number of edges and the number of vertices that have a single horse.

The second line of each test case contains $ h $ distinct integers $ a_1, a_2, \ldots, a_h $ ( $ 1 \le a_i \le n $ ) — the vertices that have a single horse available.

Then follow $ m $ lines of each test case, each with three integers $ u_i $ , $ v_i $ , $ w_i $ ( $ 1\le u_i, v_i \le n, \; 2\le w_i \le 10^6 $ ) — meaning that there is an edge between vertices $ u_i $ and $ v_i $ with travel cost $ w_i $ seconds without a horse.

There are no self loops or multiple edges. By good fortune, all $ w_i $ are even integers.

It is guaranteed that the sums of both $ n $ and $ m $ over all test cases do not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output a single integer, the earliest time Robin and Marian can meet. If it is impossible for them to meet, output $ -1 $ .

## 样例 #1

### 样例输入 #1

```
6
2 1 1
1
1 2 10
3 1 2
2 3
1 2 10
3 3 1
2
1 2 4
1 3 10
2 3 6
4 3 2
2 3
1 2 10
2 3 18
3 4 16
3 2 1
2
1 2 4
1 3 16
7 7 1
3
1 5 2
2 6 12
1 2 12
6 4 8
7 3 4
6 3 4
7 6 4
```

### 样例输出 #1

```
5
-1
6
19
14
12
```

## 提示

In the first test case, Marian rides from vertex $ 1 $ to vertex $ 2 $ , Robin waits.

In the second test case, vertices $ 1 $ and $ 3 $ are not connected.

In the third test case, both Marian and Robin travel to vertex $ 2 $ to meet.

In the fourth test case, Marian travels to vertex $ 2 $ without a horse, mounts the horse at vertex $ 2 $ and rides to vertex $ 3 $ to meet Robin.

In the fifth test case, Marian travels to vertex $ 2 $ without a horse, mounts the horse at vertex $ 2 $ and rides back to vertex $ 1 $ and then to vertex $ 3 $ . Robin waits.

## 题解
我们本题考虑能否从我们的分层最短路的角度来进行处理，我们设我们的 $dist[i][0]$ 表示我们从 0 点触发，到达我们的 i 点，并且我们不骑马所需要的最短距离。我们还可以设 $dist[i][1]$ 表示我们现在有马，并且此时到达我们的 i 点的时候，我们需要的总距离是多少。

这个时候，可以显然通过我们的 dij 类 dp 来进行处理

```
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll INF = LLONG_MAX / 2;

struct Edge {
    int to;
    ll w;
};

void solve() {
    int n, m, h;
    cin >> n >> m >> h;

    vector<bool> have_horse(n + 1, false);
    vector<vector<Edge>> adj(n + 1);
    vector<vector<ll>> dist_0(n + 1, vector<ll>(2, INF));
    vector<vector<ll>> dist_n(n + 1, vector<ll>(2, INF));

    for (int i = 0; i < h; ++i) {
        int u;
        cin >> u;
        have_horse[u] = true;
    }

    for (int i = 0; i < m; ++i) {
        int a, b;
        ll w;
        cin >> a >> b >> w;
        adj[a].push_back({b, w});
        adj[b].push_back({a, w});
    }

    auto dijkstra = [&](int start, vector<vector<ll>>& dist) {
        typedef pair<ll, pair<int, int>> State; // {distance, {node, state}}
        priority_queue<State, vector<State>, greater<State>> pq;
        dist[start][0] = 0;
        pq.push({0, {start, 0}});

        while (!pq.empty()) {
            auto [d, u_state] = pq.top();
            pq.pop();
            int u = u_state.first;
            int state = u_state.second;

            if (d > dist[u][state]) continue;

            if (have_horse[u] && dist[u][1] > dist[u][state]) {
                dist[u][1] = dist[u][state];
                pq.push({dist[u][1], {u, 1}});
            }

            for (const auto& edge : adj[u]) {
                int v = edge.to;
                ll w = edge.w;
                if (state == 1) {
                    w /= 2;
                }
                if (dist[v][state] > dist[u][state] + w) {
                    dist[v][state] = dist[u][state] + w;
                    pq.push({dist[v][state], {v, state}});
                }
            }
        }
    };

    // 从节点 1 出发的 Dijkstra
    dijkstra(1, dist_0);

    // 从节点 n 出发的 Dijkstra
    dijkstra(n, dist_n);

    ll ans = INF;
    for (int i = 1; i <= n; ++i) {
        ll dist_start = min(dist_0[i][0], dist_0[i][1]);
        ll dist_end = min(dist_n[i][0], dist_n[i][1]);
        ans = min(ans, max(dist_start, dist_end));
    }

    if (ans == INF) {
        cout << -1 << endl;
    } else {
        cout << ans << endl;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}

```