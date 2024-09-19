#include<bits/stdc++.h>
using namespace std;
struct BipGraph{
    vector<vector<int>> adj;
    vector<int> color;
    int n;
    BipGraph(int n):n(n){
        adj.resize(n+1);
        color.resize(n+1);
    }
    void add(int a,int b){
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    bool dfs(int u,int c){
        color[u] = c;
        for(auto v:adj[u]){
            int b = v;                   
            if(!color[b]){
                if(!dfs(b, 3 - c)) return false;
            }
            else if(color[b] && color[b] != 3 - c){                                     
                return false;                   
            }
        }
        return true;
    }
    bool check(){
        for(int i=1;i<=n;i++){
            if(!color[i]){
                if(!dfs(i,1)){
                    return false;
                }
            }
        }
        return true;
    }
};