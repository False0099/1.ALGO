#include<bits/stdc++.h>
using namespace std;
struct SDC{
    #define INFI 0x3f3f3f3f
    #define NINFI 0x80808080
    struct Node{
        int v,w;
    };
    int n;
    vector<vector<Node>> G;
    vector<int> dis;
    vector<int> cnt;
    vector<bool> in;
    SDC(int n){
        this->n=n;
        G.resize(n+1);
    }
    //存在负环为true
    bool work(int st){
        init_ori();
        dis.resize(n+1,INFI);
        in.resize(n+1,false);
        cnt.resize(n+1,0);
        queue <int> q;
        q.push(st);
        dis[st] = 0;
        in[st] = true;
        cnt[st] = 1;
        while (!q.empty()){
            int u = q.front();
            q.pop();
            in[u] = false;
            for (auto &t:G[u]){
                int v = t.v;
                int w = t.w;
                if (dis[v] > dis[u] + w){
                    dis[v] = dis[u] + w;
                    if (!in[v]){
                        cnt[v]++;
                        q.push(v);
                        in[v] = true;
                        if (cnt[v] == n+1){
                            return true;    
                        } 
                    }
                }
            }
        }
        return false;        
    }
    void add(int u,int v,int w){
        G[u].push_back({v,w});
    }
    void query(){
        for(int i=1;i<=n;i++){
            cout<<dis[i]<<" ";
        }
    }
    void init_ori(){
        for(int i=1;i<=n;i++)
            add(0,i,0);
    }
};