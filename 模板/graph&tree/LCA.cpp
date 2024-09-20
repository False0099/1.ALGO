vector<vector<int>> p(n+1,vector<int>(30));
vector<int> lg(n+1), dep(n+1);
auto build = [&](int root){
    for (int i = 1; i <= n; i++) { 
        lg[i] = lg[i - 1] + (1 << lg[i - 1] == i);
    }
    function<void(int,int)> dfs = [&](int x,int fa){
        p[x][0] = fa; 
        dep[x] = dep[fa] + 1;
        for (int i = 1; i <= lg[dep[x]]; i++) {
            p[x][i] = p[p[x][i - 1]][i - 1];
        }
        for (auto y : g[x]) {
            if (y == fa) continue;
            dfs(y, x);
        }
    };
    dfs(root, 0);
};
auto lca = [&](int x,int y){
    if (dep[x] < dep[y]) swap(x, y);
    while (dep[x] > dep[y]) {
        x = p[x][lg[dep[x] - dep[y]] - 1];
    }
    if (x == y) return x;
    for (int k = lg[dep[x]] - 1; k >= 0; k--) {
        if (p[x][k] == p[y][k]) continue;
        x = p[x][k];
        y = p[y][k];
    }
    return p[x][0];
};
build(1);




struct Tree {
    int n;
    vector<vector<int>> ver, val;
    vector<int> lg, dep;
    Tree(int n) {
        this->n = n;
        ver.resize(n + 1);
        val.resize(n + 1, vector<int>(30));
        lg.resize(n + 1);
        dep.resize(n + 1);
        for (int i = 1; i <= n; i++) { 
            lg[i] = lg[i - 1] + (1 << lg[i - 1] == i);
        }
    }
    void add(int x, int y) { 
        ver[x].push_back(y);
        ver[y].push_back(x);
    }
    void dfs(int x, int fa) {
        val[x][0] = fa; 
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
    int calcDis(int x, int y) { 
        return dep[x] + dep[y] - 2 * dep[lca(x, y)];
    }
    void work(int root = 1) { 
        dfs(root, 0);
    }
};