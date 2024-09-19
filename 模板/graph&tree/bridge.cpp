#include<bits/stdc++.h>
using namespace std;

struct LowLink{
    int n;
    vector<vector<int>> g;
    vector<int> dfn,low;
    set<pair<int,int>> bridge;
    int id=0;
    LowLink(vector<vector<int>> g):g(g),n(g.size()-1){
        dfn.resize(n+1,0);
        low.resize(n+1,0);
        build();
    }
    void tarjan(int u,int fa){
        dfn[u]=low[u]=++id;
        for(auto v:g[u]){
            if(dfn[v]&&v!=fa){
                low[u]=min(low[u],dfn[v]);
            }
            if(!dfn[v]){
                tarjan(v,u);
                if(dfn[u]<low[v]){
                    int tx=min(u,v);
                    int ty=max(u,v);
                    bridge.insert({tx,ty});
                }
                low[u]=min(low[u],low[v]);
            }
        }
    }
    void build(){
        for(int i=1;i<=n;i++){
            if(!dfn[i]) tarjan(i,i);
        }
    }
};