const int N = 5e5+10;
#define ls(x) x<<1
#define rs(x) x<<1|1
struct Node{
    int l,r;
    int v;
}tr[N*4];
int a[N],add[N<<2],mul[N<<2];
int p;
void pushup(int u){
    tr[u].v=tr[ls(u)].v+tr[rs(u)].v;
    tr[u].v%=p;
}
void build(int u,int l,int r){
    if(l==r){
        tr[u]={l,r,a[l]};
        return;
    }
    tr[u]={l,r};
    int mid=l+r>>1;
    build(ls(u),l,mid);build(rs(u),mid+1,r);
    pushup(u);
}
void apply1(int u,int v){
    tr[u].v=(tr[u].v+v*(tr[u].r-tr[u].l+1))%p;
    add[u]=(add[u]+v)%p;
}
void apply2(int u,int v){
    add[u]=(add[u]*v)%p;
    mul[u]=mul[u]*v%p;
    tr[u].v=tr[u].v*v%p;
}
void pushdown(int u){
    if(mul[u]!=1){
        apply2(ls(u),mul[u]);
        apply2(rs(u),mul[u]);
        mul[u]=1;
    }   
    if(add[u]){
        apply1(ls(u),add[u]);
        apply1(rs(u),add[u]);
        add[u]=0;
    }
}
void modify1(int u,int l,int r,int v){
    if(tr[u].l>=l&&tr[u].r<=r){
        apply2(u,v);
        return;
    }
    pushdown(u);
    int mid=tr[u].l+tr[u].r>>1;
    if(l<=mid){
        modify1(ls(u),l,r,v);
    }
    if(r>mid){
        modify1(rs(u),l,r,v);
    }
    pushup(u);
}
void modify2(int u,int l,int r,int v){
    if(tr[u].l>=l&&tr[u].r<=r){
        apply1(u,v);
        return;
    }
    pushdown(u);
    int mid=tr[u].l+tr[u].r>>1;
    if(l<=mid){
        modify2(ls(u),l,r,v);
    }
    if(r>mid){
        modify2(rs(u),l,r,v);
    }
    pushup(u);
}
int query(int u,int l,int r){
    if(tr[u].l>=l&&tr[u].r<=r){
        return tr[u].v;
    }
    pushdown(u);
    int mid=tr[u].l+tr[u].r>>1;
    int res=0;
    if(l<=mid){
        res=query(ls(u),l,r);
    }
    if(r>mid){
        res+=query(rs(u),l,r);
        res%=p;
    }
    return res%p;
}


template <class T> struct Segt_ {
    struct node {
        int l, r;
        T w, add, mul = 1; // 注意初始赋值
    };
    vector<T> w;
    vector<node> t;

    Segt_(int n) {
        w.resize(n + 1);
        t.resize((n << 2) + 1);
        build(1, n);
    }
    Segt_(vector<int> in) {
        int n = in.size() - 1;
        w.resize(n + 1);
        for (int i = 1; i <= n; i++) {
            w[i] = in[i];
        }
        t.resize((n << 2) + 1);
        build(1, n);
    }
    void pushdown(node &p, T add, T mul) { // 在此更新下递函数
        p.w = p.w * mul + (p.r - p.l + 1) * add;
        p.add = p.add * mul + add;
        p.mul *= mul;
    }
    void pushup(node &p, node &l, node &r) { // 在此更新上传函数
        p.w = l.w + r.w;
    }
#define GL (k << 1)
#define GR (k << 1 | 1)
    void pushdown(int k) { // 不需要动
        pushdown(t[GL], t[k].add, t[k].mul);
        pushdown(t[GR], t[k].add, t[k].mul);
        t[k].add = 0, t[k].mul = 1;
    }
    void pushup(int k) { // 不需要动
        pushup(t[k], t[GL], t[GR]);
    }
    void build(int l, int r, int k = 1) {
        if (l == r) {
            t[k] = {l, r, w[l]};
            return;
        }
        t[k] = {l, r};
        int mid = (l + r) / 2;
        build(l, mid, GL);
        build(mid + 1, r, GR);
        pushup(k);
    }
    void modify(int l, int r, T val, int k = 1) { // 区间修改
        if (l <= t[k].l && t[k].r <= r) {
            t[k].w += (t[k].r - t[k].l + 1) * val;
            t[k].add += val;
            return;
        }
        pushdown(k);
        int mid = (t[k].l + t[k].r) / 2;
        if (l <= mid) modify(l, r, val, GL);
        if (mid < r) modify(l, r, val, GR);
        pushup(k);
    }
    void modify2(int l, int r, T val, int k = 1) { // 区间修改
        if (l <= t[k].l && t[k].r <= r) {
            t[k].w *= val;
            t[k].add *= val;
            t[k].mul *= val;
            return;
        }
        pushdown(k);
        int mid = (t[k].l + t[k].r) / 2;
        if (l <= mid) modify2(l, r, val, GL);
        if (mid < r) modify2(l, r, val, GR);
        pushup(k);
    }
    T ask(int l, int r, int k = 1) { // 区间询问，不合并
        if (l <= t[k].l && t[k].r <= r) {
            return t[k].w;
        }
        pushdown(k);
        int mid = (t[k].l + t[k].r) / 2;
        T ans = 0;
        if (l <= mid) ans += ask(l, r, GL);
        if (mid < r) ans += ask(l, r, GR);
        return ans;
    }
    void debug(int k = 1) {
        cout << "[" << t[k].l << ", " << t[k].r << "]: ";
        cout << "w = " << t[k].w << ", ";
        cout << "add = " << t[k].add << ", ";
        cout << "mul = " << t[k].mul << ", ";
        cout << endl;
        if (t[k].l == t[k].r) return;
        debug(GL), debug(GR);
    }
};