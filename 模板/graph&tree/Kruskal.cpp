#include<bits/stdc++.h>
using namespace std;
//稀疏图
struct DSU{
    vector<int> p,size;
    DSU(){}
    DSU(int n){
        init(n);
    }
    void init(int n){
        p.resize(n+1);
        iota(p.begin(),p.end(),0);
        size.assign(n+1,1);
    }
    bool same(int a,int b){
        return find(a)==find(b);
    }
    int find(int x){
        if(p[x]!=x) p[x]=find(p[x]);
        return p[x];
    }
    bool merge(int a,int b){
        a=find(a);
        b=find(b);
        if(same(a,b)){
            return false;
        }
        size[b]+=size[a];
        p[a]=b;
        return true;
    }
    int getSize(int x){
        return size[find(x)];
    }
};
struct Kruskal{
    struct Edge{
        int u,v,w;
    };
    int n,k;
    int maxn=-0x3f3f3f3f;//求权值最长路
    vector<Edge> g;
    Kruskal(int n,int k=1){
        this->n=n;
        this->k=k;
    }
    void add(int u,int v,int w){
        g.push_back({u,v,w});
    }
    int work(){
        DSU d(n);
        int ans=0,cnt=0;
        sort(g.begin(),g.end(),[&](Edge a,Edge b){
            return a.w<b.w;
        });
        for(int i=0;i<g.size();i++){
            int eu=d.find(g[i].u);
            int ev=d.find(g[i].v);
            if(eu==ev){
                continue;
            }
            ans+=g[i].w;
            maxn=max(maxn,g[i].w);
            d.merge(ev,eu);
            if(++cnt==n-k){
                break;
            }
        }
        if(cnt!=n-k){
            return 0x80808080;
        }
        return ans;
    }
};