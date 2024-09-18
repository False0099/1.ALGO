#include<bits/stdc++.h>
using namespace std;

struct CutPoint{
    int n;
    vector<vector<int>> g;
    vector<int> dfn,low,cut;
    vector<int> point;
    int id=0,cnt=0;
    CutPoint(vector<vector<int>> g):g(g),n(g.size()-1){
        dfn.resize(n+1,0);
        low.resize(n+1,0);
        cut.resize(n+1,0);
        build();
    }
    void tarjan(int u,int fa){
        dfn[u]=low[u]=++id;
        int son=0;
        for(auto &v:g[u]){
            if(!dfn[v]){
                tarjan(v,fa);
                low[u]=min(low[u],low[v]);
                if(u!=fa&&dfn[u]<=low[v]) cut[u]=true;
                if(u==fa) son++;
            }else{
                low[u]=min(low[u],dfn[v]);
            }
        }
        if(u==fa&&son>=2) cut[u]=true;
    }
    void build(){
        for(int i=1;i<=n;i++){
            if(!dfn[i]){
                tarjan(i,i);
            }
        }
        for(int i=1;i<=n;i++){
            if(cut[i]){
                point.push_back(i);
                cnt++;
            }
        }
    }
};