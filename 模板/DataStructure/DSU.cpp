//my DSU
struct DSU{
    vector<int> p,siz;
    DSU(){}
    DSU(int n){
        init(n);
    }
    void init(int n){
        p.resize(n+1);
        iota(p.begin(),p.end(),0);
        siz.assign(n+1,1);
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
        siz[a]+=siz[b];
        p[b]=a;
        return true;
    }
    int getSize(int x){
        return siz[find(x)];
    }
};

//simplified
vector<int> p(n+2,0),siz(n+2,1);
iota(all(p),0);
function<int(int)> find = [&](int x){
    if(x!=p[x]){
        p[x]=find(p[x]);
    }
    return p[x];
};
auto merge=[&](int a,int b){
    a=find(a);
    b=find(b);
    if(a==b) return false;
    p[b]=a;
    siz[a]+=siz[b];
    return true;
};


struct DSU {
    vector<int> p, siz, edge, cyc, val;//val 带权

    DSU(int n) {
        p.resize(n + 1);
        iota(p.begin(), p.end(), 0);
        siz.resize(n + 1, 1);
        edge.resize(n + 1);
        cyc.resize(n + 1);
        val.resize(n + 1, 0);
    }
    int find(int x) {
        if(p[x]!=x){
            int t=p[x];
            p[x]=find(p[x]);
            // val[x]+=val[t]; //带权更新操作
        }    
        return p[x];
    }
    bool merge(int x, int y) { // 设x是y的祖先
        if (x == y) cyc[find(x)] = 1;
        x = find(x), y = find(y);
        edge[x]++;
        if (x == y) return false;
        if (x < y) swap(x, y); // 将编号小的合并到大的上
        p[y] = x;
        cyc[x] |= cyc[y], siz[x] += siz[y], edge[x] += edge[y];

		// val[find(x)]=val[y]-val[x]+s; //带权合并操作
        return true;
    }
    bool same(int x, int y) {
        return find(x) == find(y);
    }
    bool Acyclic(int x) { // 判断连通块内是否存在自环
        return cyc[find(x)];
    }
    int size(int x) { // 输出连通块中点的数量
        return siz[find(x)];
    }
    int E(int x) { // 输出连通块中边的数量
        return edge[find(x)];
    }
};
