You are given a **directed** graph $G$ with $n$ vertices and $m$ edges between them.

Initially, graph $H$ is the same as graph $G$. Then you decided to perform the following actions:

-   If there exists a triple of vertices $a$, $b$, $c$ of $H$, such that there is an edge from $a$ to $b$ and an edge from $b$ to $c$, but there is no edge from $a$ to $c$, add an edge from $a$ to $c$.
-   Repeat the previous step as long as there are such triples.

Note that the number of edges in $H$ can be up to $n^2$ after performing the actions.

You also wrote some values on vertices of graph $H$. More precisely, vertex $i$ has the value of $a_i$ written on it.

Consider a simple path consisting of $k$ **distinct** vertices with indexes $v_1, v_2, \ldots, v_k$. The length of such a path is $k$. The value of that path is defined as $\sum_{i = 1}^k a_{v_i}$.

A simple path is considered the longest if there is no other simple path in the graph with greater length.

Among all the longest simple paths in $H$, find the one with the smallest value.

## 题解
本题要求我们求最长路的最短值，首先要最长，然后才是我们的最短，
我们思路就是进行我们的缩点，把我们图转换为我们的有向无环图，因为要求我们的最长路，所以缩点后形成的强连通分量，我们一定要全部走完，否则我们一定不是最长路，然后我们再按照我们的拓扑序进行我们的距离求解即可。
```cpp
#include<iostream>
#include<cstring>
#include<vector>
using namespace std;
using LL = long long;
struct SCC{
    vector<vector<int> > g, scc;
    vector<int> dfn, low, stk, id;
    vector<bool> ins;
    int ts, n;

    SCC(const vector<vector<int> > &g) : g(g){
        n = (int)g.size();
        dfn.assign(n, 0);
        low.assign(n, 0);
        id.assign(n, -1);
        ins.assign(n, false);
        stk.reserve(n);
        ts = 0;
        build();
    }

    void tarjan(int u){
        dfn[u] = low[u] = ++ts;
        stk.push_back(u);
        ins[u] = 1;
        for(auto j : g[u]){
            if (!dfn[j]){
                tarjan(j);
                low[u] = min(low[u], low[j]);
            }
            else if (ins[j]) low[u] = min(low[u], dfn[j]);
        }
        if (dfn[u] == low[u]){
            int scc_cnt = scc.size();
            scc.push_back({});
            int y;
            do{
                y = stk.back();
                stk.pop_back();
                id[y] = scc_cnt;
                ins[y] = 0;
                scc.back().push_back(y);
            }while(y != u);
        }
    }

    void build(){
        for(int i = 0; i < n; i++){
            if (!dfn[i]){
                tarjan(i);
            }
        }
    }
};

int main(){

    cin.tie(0);
    cout.tie(0);
    ios::sync_with_stdio(0);

    int T;
    cin >> T;
    while(T--){
        int n, m;
        cin >> n >> m;
        vector<int> a(n);
        for(int i = 0; i < n; i++) cin >> a[i];
        vector<vector<int> > g(n);
        while(m--){
            int a, b;
            cin >> a >> b;
            a--, b--;
            g[a].push_back(b);
        }
        SCC scc(g);
        scc.build();
        const int s = scc.scc.size();
        vector<int> cnt(s);
        vector<LL> sum(s);
        auto &p = scc.scc;
        vector<pair<int, LL> > dp(n);
        for(int i = 0; i < s; i++){
            cnt[i] = p[i].size();
            for(auto x : p[i]){
                sum[i] -= a[x];
            }
            dp[i] = {cnt[i], sum[i]};
        }
        
        for(int i = 0; i < s; i++){
            for(auto x : p[i]){//p是我们的连通分量
                for(auto j : g[x]){//j是我们的相邻的连通分量
                    if (scc.id[j] != i){
                        int k = scc.id[j];
                        pair<int, LL> t = {cnt[i] + dp[k].first, sum[i] + dp[k].second};
                        dp[i] = max(dp[i], t);
                    }
                }
            }
        }
        auto ans = *max_element(dp.begin(), dp.end());
        cout << ans.first << ' ' << -ans.second << '\n';
    }

}
```