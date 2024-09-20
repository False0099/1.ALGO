#include<bits/stdc++.h>
using namespace std;
#define INF 0x3f3f3f3f

//稠密图
const int N = 550;
int g[N][N],d[N],v[N];
struct Prim{
    int n;
    Prim(int n):n(n){
        memset(g,INF,sizeof(g));
        memset(d,INF,sizeof(d));
    }
    void add(int x,int y,int w){
        g[x][y]=g[y][x]=min(g[x][y],w);
    }
    int work() {
        int ans = 0;
        for (int i = 0; i < n; ++ i) {
            int t = -1;
            for (int j = 1; j <= n; ++ j)
                if (v[j] == 0 && (t == -1 || d[j] < d[t]))
                    t = j;
            v[t] = 1; 
            if (i && d[t] == INF) return INF;
            if (i) ans += d[t];
            for (int j = 1; j <= n; ++ j) d[j] = min(d[j], g[t][j]); 
        }
        return ans;
    }
};