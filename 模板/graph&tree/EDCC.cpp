#include<bits/stdc++.h>
using namespace std;
using pii = pair<int,int>;

struct EDCC{
    int n;
    vector<vector<pii>> g;
    vector<int> dfn,low,dcc,siz;
    vector<bool> isbridge;
    stack<int> st;
    set<pii> bridge;
    vector<vector<int>> dccs; 
    int id=0,col=0;
    EDCC(vector<vector<pii>> g):g(g),n(g.size()-1){
        dfn.resize(n+1,0);
        low.resize(n+1,0);
        dcc.resize(n+1,0);
        siz.resize(n+1,0);
        isbridge.resize(n<<1|1,0);
        build();
    }
    void tarjan(int u,int last){
        dfn[u]=low[u]=++id;
        st.push(u);
        for(auto &[v,w]:g[u]){
            if(w==(last^1)) continue;
            if(!dfn[v]){
                tarjan(v,w);
                low[u]=min(low[u],low[v]);
                if(dfn[u]<low[v]){
                    int mx=min(u,v),my=max(u,v);
                    bridge.insert({mx,my});
                    isbridge[w]=isbridge[w^1]=true;
                }
            }else{
                low[u]=min(low[u],dfn[v]);
            }
        }
        if(dfn[u]==low[u]){
            int v;col++;
            vector<int> tmp;
            do{
                v=st.top();st.pop();
                dcc[v]=col;
                tmp.push_back(v);
                ++siz[col];
            }while(v!=u);
            dccs.push_back(tmp);
        }
    }
    void build(){
        for(int i=1;i<=n;i++){
            if(!dfn[i]) tarjan(i,0);
        }
    }
    pair<vector<vector<int>>,int> rebuild(){
        vector<vector<int>> newg(col+1);
        vector<int> deg(col+1,0);
        for(int i=1;i<=n;i++){
            for(auto &[v,w]:g[i]){
                if(dcc[i]!=dcc[v]){
                    newg[dcc[i]].push_back(dcc[v]);
                }
            }
        }
        return {newg,col};
    }
};

void add(vector<vector<pii>> &g,int u,int v,int id){
    g[u].push_back({v,id<<1});
    g[v].push_back({u,id<<1|1});
}




//（无向图）割边缩点 可以在O(n+m)复杂度内求解图中全部割边、划分边双（颜色相同的点位于同一个边双连通分量中）。
struct EDCC {
    int n, now, cnt;
    vector<vector<int>> ver;
    vector<int> dfn, low, col, S;
    set<array<int, 2>> bridge;

    EDCC(int n) : n(n), ver(n + 1), low(n + 1) {
        dfn.resize(n + 1, -1);
        col.resize(n + 1, -1);
        now = cnt = 0;
    }
    void add(int x, int y) {
        ver[x].push_back(y);
        ver[y].push_back(x);
    }
    void tarjan(int x, int fa) {
        dfn[x] = low[x] = now++;
        S.push_back(x);
        for (auto y : ver[x]) {
            if (y == fa) continue;
            if (dfn[y] == -1) {
                bridge.insert({x, y}); // 储存割边
                tarjan(y, x);
                low[x] = min(low[x], low[y]);
            } else if (col[y] == -1 && dfn[y] < dfn[x]) {
                bridge.insert({x, y});
                low[x] = min(low[x], dfn[y]);
            }
        }
        if (dfn[x] == low[x]) {
            int pre;
            cnt++;
            do {
                pre = S.back();
                col[pre] = cnt;
                S.pop_back();
            } while (pre != x);
        }
    }
    auto work() { // [cnt 新图的顶点数量, bridge 全部割边]
        for (int i = 1; i <= n; i++) { // 避免图不连通
            if (dfn[i] == -1) {
                tarjan(i, 0);
            }
        }

        vector<int> siz(cnt + 1); // siz 每个边双中点的数量
        vector<vector<int>> adj(cnt + 1); // adj 新图
        for (int i = 1; i <= n; i++) {
            siz[col[i]]++;
            for (auto j : ver[i]) {
                int x = col[i], y = col[j];
                if (x != y) {
                    adj[x].push_back(y);
                }
            }
        }
        return tuple<int,vector<vector<int>>,vector<int>,vector<int>>{cnt, adj, col, siz};
    }
};