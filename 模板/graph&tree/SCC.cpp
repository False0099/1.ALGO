#include<bits/stdc++.h>
using namespace std;

struct SCC{
    int n;
    vector<vector<int>> g;
    vector<int> dfn,low,scc,siz;
    vector<bool> vis;
    stack<int> st;
    int id=0,col=0;
    SCC(vector<vector<int>> &g):g(g),n(g.size()-1){
        dfn.resize(n+1,0);
        low.resize(n+1,0);
        scc.resize(n+1,0);
        siz.resize(n+1,0);
        vis.resize(n+1,0);
        build();
    }
    void tarjan(int u){
        dfn[u]=low[u]=++id;
        st.push(u);
        vis[u]=true;
        for(auto &v:g[u]){
            if(!dfn[v]){
                tarjan(v);
                low[u]=min(low[u],low[v]);
            }else if(vis[v]){
                low[u]=min(low[u],dfn[v]);
            }
        }
        if(dfn[u]==low[u]){
            col++;
            int v;
            do{
                v=st.top();st.pop();
                vis[v]=false;
                scc[v]=col;
                siz[col]++;
            }while(v!=u);
        }
    }
    void build(){
        for(int i=1;i<=n;i++){
            if(!dfn[i]){
                tarjan(i);
            }
        }
    }
    pair<vector<vector<int>>,int> rebuild(){
        vector<vector<int>> newg(col+1);
        for(int i=1;i<=n;i++){
            for(auto &v:g[i]){
                if(scc[i]!=scc[v]){
                    newg[scc[i]].push_back(scc[v]);
                }
            }
        }
        return {newg,col};
    }
};

void add(vector<vector<int>> &g,int u,int v){
    if(u!=v){
        g[u].push_back(v);
        g[v].push_back(u);
    }
}


const int N = 1e5+50;
int n,id,col;
vector<int> g[N];
int dfn[N],low[N],scc[N],siz[N];
stack<int> st;
bool vis[N];
void tarjan(int u){
    dfn[u]=low[u]=++id;
    st.push(u);
    vis[u]=true;
    for(auto &v:g[u]){
        if(!dfn[v]){
            tarjan(v);
            low[u]=min(low[u],low[v]);
        }else if(vis[v]){
            low[u]=min(low[u],dfn[v]);
        }
    }
    if(low[u]==dfn[u]){
        int v;col++;
        do{
            v=st.top();st.pop();
            scc[v]=col;
            siz[col]++;
            vis[v]=false;
        }while(u!=v);
    }
}
void build(){
    for(int i=1;i<=n;i++){
        if(!dfn[i]){
            tarjan(i);
        }
    }
}
void add(int u,int v){
    if(u!=v){
        g[u].push_back(v);
        g[v].push_back(u);
    }
}
auto rebuild=[&](){
    vector<vector<int>> newg(col+1);
    for(int i=1;i<=n;i++){
        for(auto &v:g[i]){
            if(scc[i]!=scc[v]){
                newg[scc[i]].push_back(scc[v]);
            }
        }
    }
    return newg;
};