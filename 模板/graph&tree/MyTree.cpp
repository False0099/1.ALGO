#include<bits/stdc++.h>
using namespace std;
struct Tree {
    int n;
    vector<vector<int>> ver, val;
    vector<int> lg, dep, wid;//深度，宽度
    Tree(int n) {
        this->n = n;
        ver.resize(n + 1);
        val.resize(n + 1, vector<int>(30));
        lg.resize(n + 1);
        dep.resize(n + 1);
        for (int i = 1; i <= n; i++) { //预处理 log
            lg[i] = lg[i - 1] + (1 << lg[i - 1] == i);
        }
    }
    void add(int x, int y) {
        ver[x].push_back(y);
    }
    void dfs(int x, int fa) {
        val[x][0] = fa; // 储存 x 的父节点
        dep[x] = dep[fa] + 1;
        for (int i = 1; i <= lg[dep[x]]; i++) {
            val[x][i] = val[val[x][i - 1]][i - 1];
        }
        for (auto y : ver[x]) {
            if (y == fa) continue;
            dfs(y, x);
        }
    }
    int lca(int x, int y) {
        if (dep[x] < dep[y]) swap(x, y);
        while (dep[x] > dep[y]) {
            x = val[x][lg[dep[x] - dep[y]] - 1];
        }
        if (x == y) return x;
        for (int k = lg[dep[x]] - 1; k >= 0; k--) {
            if (val[x][k] == val[y][k]) continue;
            x = val[x][k];
            y = val[y][k];
        }
        return val[x][0];
    }
    int calc(int x, int y) { // 倍增查询两点间距离
        return dep[x] + dep[y] - 2 * dep[lca(x, y)];
    }
    void work(int root = 1) { // 在此初始化
        dfs(root, 0);
        bfs(root);
    }
    void bfs(int rt){
        queue<int> q,tmp;
        q.push(rt);
        int ind=0;
        while(ind<n){
            while(q.size()){
                int x=q.front();
                ind++;
                q.pop();
                for(auto &v: ver[x]){
                    tmp.push(v);
                }
            } 
            int cnt=0;
            while(tmp.size()){
                q.push(tmp.front());
                tmp.pop();
                cnt++;
            }
            wid.push_back(cnt);
        }
    }
};