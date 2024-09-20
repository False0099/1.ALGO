#include<bits/stdc++.h>
using namespace std;

struct VDCC{
    int n;
    vector<vector<int>> g;
    vector<int> dfn,low,siz;
    vector<vector<int>> dcc;
    stack<int> st;
    int id=0,col=0;
    vector<bool> cut;
    set<int> point;
    VDCC(vector<vector<int>> g):g(g),n(g.size()-1){
        dfn.resize(n+1,0);
        low.resize(n+1,0);
        dcc.resize(n+1);
        siz.resize(n+1,0);
        cut.resize(n+1,0);
        build();
    }
    void tarjan(int u,int root){
        low[u]=dfn[u]=++id;
        st.push(u);
        if(u==root&&!g[u].size()){
            dcc[++col].push_back(u);
            return;
        }
        int son=0;
        for(auto v:g[u]){
            if(!dfn[v]){
                tarjan(v,root);
                low[u]=min(low[u],low[v]);
                if(dfn[u]<=low[v]){
                    son++;
                    if(u!=root||son>1){
                        cut[u]=true;
                        point.insert(u);
                    }
                    int x;col++;
                    do{
                        x=st.top();
                        dcc[col].push_back(x);
                        st.pop();
                    }while(x!=v);
                    dcc[col].push_back(u);
                }
            }else{
                low[u]=min(low[u],dfn[v]);
            }
        }
    }
    void build(){
        for (int i=1;i<=n;i++){
            if(!dfn[i]){
                tarjan(i,i);
            }
        }
    }
    pair<vector<vector<int>>,int> rebuild(){
        vector<vector<int>> adj(col+1);
        for (int i=1;i<=col;i++){
            if(!dcc[i].size()){
                continue;
            }
            for(auto j:dcc[i]){
                if(cut[j]){
                    adj[i].push_back(cut[j]);
                    adj[cut[j]].push_back(i);
                }
            }
        }
        return {adj,col};
    }
};

void add(vector<vector<int>> &g,int u,int v){
    if(u!=v){
        g[u].push_back(v);
        g[v].push_back(u);
    }
}


//（无向图）割点缩点 可以在O(n+m)复杂度内求解图中全部割点、划分点双（颜色相同的点位于同一个点双连通分量中）。
struct V_DCC {
    int n;
    vector<vector<int>> ver, col;
    vector<int> dfn, low, S;
    int now, cnt;
    vector<bool> point; // 记录是否为割点

    V_DCC(int n) : n(n) {
        ver.resize(n + 1);
        dfn.resize(n + 1);
        low.resize(n + 1);
        col.resize(2 * n + 1);
        point.resize(n + 1);
        S.clear();
        cnt = now = 0;
    }
    void add(int x, int y) {
        if (x == y) return; // 手动去除重边
        ver[x].push_back(y);
        ver[y].push_back(x);
    }
    void tarjan(int x, int root) {
        low[x] = dfn[x] = now++;
        S.push_back(x);
        if (x == root && !ver[x].size()) { // 特判孤立点
            ++cnt;
            col[cnt].push_back(x);
            return;
        }

        int flag = 0;
        for (auto y : ver[x]) {
            if (!dfn[y]) {
                tarjan(y, root);
                low[x] = min(low[x], low[y]);
                if (dfn[x] <= low[y]) {
                    flag++;
                    if (x != root || flag > 1) {
                        point[x] = true; // 标记为割点
                    }
                    int pre = 0;
                    cnt++;
                    do {
                        pre = S.back();
                        col[cnt].push_back(pre);
                        S.pop_back();
                    } while (pre != y);
                    col[cnt].push_back(x);
                }
            } else {
                low[x] = min(low[x], dfn[y]);
            }
        }
    }
    pair<int, vector<vector<int>>> rebuild() { // [新图的顶点数量, 新图]
        work();
        vector<vector<int>> adj(cnt + 1);
        for (int i = 1; i <= cnt; i++) {
            if (!col[i].size()) { // 注意，孤立点也是 V-DCC
                continue;
            }
            for (auto j : col[i]) {
                if (point[j]) { // 如果 j 是割点
                    adj[i].push_back(point[j]);
                    adj[point[j]].push_back(i);
                }
            }
        }
        return {cnt, adj};
    }
    void work() {
        for (int i = 1; i <= n; ++i) { // 避免图不连通
            if (!dfn[i]) {
                tarjan(i, i);
            }
        }
    }
};