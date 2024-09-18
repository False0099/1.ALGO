#include<bits/stdc++.h>
using namespace std;
using ll = long long;

struct ODT {
    struct node {
        int l, r;
        mutable ll v;
        node(int l, int r = -1, ll v = 0) : l(l), r(r), v(v) {}
        bool operator<(const node &o) const {
            return l < o.l;
        }
    };
    set<node> s;
    vector<node> t1,t2;
    int sum=0;//区间一次和(特殊)
    ODT() {
        s.clear();
    }
    auto split(int pos) {
        auto it = s.lower_bound(node(pos));
        if (it != s.end() && it->l == pos) return it;
        it--;
        int l = it->l, r = it->r;
        ll v = it->v;
        s.erase(it);
        s.insert(node(l, pos - 1, v));
        return s.insert(node(pos, r, v)).first;
    }
    //区间赋值[推平]
    void assign(int l, int r, ll x) {
        auto itr = split(r + 1), itl = split(l) , it=itl;
        for(;itl!=itr;++itl){
            sum-=itl->v*(itl->r-itl->l+1);
        }
        s.erase(it, itr);
        s.insert(node(l, r, x));
        sum+=x*(r-l+1);
    }
    //区间加[l~r]每一个数加x
    void add(int l, int r, ll x) {
        auto itr = split(r + 1), itl = split(l);
        for (auto it = itl; it != itr; it++) {
            it->v += x;
        }
    }
    //区间第k小
    ll kth(int l, int r, int k) {
        vector<pair<ll, int>> a;
        auto itr = split(r + 1), itl = split(l);
        for (auto it = itl; it != itr; it++) {
            a.push_back(pair<ll, int>(it->v, it->r - it->l + 1));
        }
        sort(a.begin(), a.end());
        for (auto x : a) {
            auto val = x.first;
            auto len = x.second;
            k -= len;
            if (k <= 0) return val;
        }
        return 0;
    }

    ll power(ll a, int b, int mod) {
        a %= mod;
        ll res = 1;
        for (; b; b /= 2, a = a * a % mod) {
            if (b % 2) {
                res = res * a % mod;
            }
        }
        return res;
    }
    //区间幂次和
    ll powersum(int l, int r, int x, int mod) {
        auto itr = split(r + 1), itl = split(l);
        ll ans = 0;
        for (auto it = itl; it != itr; it++) {
            ans = (ans + power(it->v, x, mod) * (it->r - it->l + 1) % mod) % mod;
        }
        return ans;
    }
    //区间一次和
    ll sum_one(int l,int r,ll mod){
        ll ret=0;
        auto itl=split(l),itr=split(r+1);
        for(;itl!=itr;itl++){
            ret=(ret+(itl->r-itl->l+1)*itl->v)%mod;
        }
        return ret;
    }
    // 匹配暴力搜索（质数搭配欧拉筛）
    void query(int l,int r){
        auto itr=split(r+1),itl=split(l);
		int res = 0;
		for (; itl != itr; itl ++ ){
			// if (itl->v <= 1e7 && !st[itl->v])
			// 	res += itl->r - itl->l + 1;
        }
        cout<<res<<"\n";
    }
    void insert(const int& x,vector<int>& a){
        for(int i=1;i<=x;++i){
            s.insert(node(i,i,a[i]));
        }
    }
    void insert(int l,int r,int v){
        s.insert(node{l,r,v});
    }
};



//ODT++
const ll MOD = 1e9+7;
struct node {
    int l, r;
    mutable ll v;
    node(int l=0, int r = -1, ll v = 0) : l(l), r(r), v(v) {}
    bool operator<(const node &o) const {
        return l < o.l;
    }
};
#define MAXN 500010
node a[MAXN],b[MAXN];
struct ODT {
    set<node> s;
    ODT() {
        s.clear();
    }
    auto split(int pos) {
        auto it = s.lower_bound(node(pos));
        if (it != s.end() && it->l == pos) return it;
        it--;
        int l = it->l, r = it->r;
        ll v = it->v;
        s.erase(it);
        s.insert(node(l, pos - 1, v));
        return s.insert(node(pos, r, v)).first;
    }
    //区间赋值[推平]
    void assign(int l, int r, ll x) {
        auto itr = split(r + 1), itl = split(l) , it=itl;
        s.erase(it, itr);
        s.insert(node(l, r, x));
    }
    //区间加[l~r]每一个数加x
    void add(int l, int r, ll x) {
        auto itr = split(r + 1), itl = split(l);
        for (auto it = itl; it != itr; it++) {
            (it->v += x)%=MOD;
        }
    }
    //区间第k小
    ll kth(int l, int r, int k) {
        vector<pair<ll, int>> a;
        auto itr = split(r + 1), itl = split(l);
        for (auto it = itl; it != itr; it++) {
            a.push_back(pair<ll, int>(it->v, it->r - it->l + 1));
        }
        sort(a.begin(), a.end());
        for (auto x : a) {
            auto v = x.first;
            auto len = x.second;
            k -= len;
            if (k <= 0) return v;
        }
        return 0;
    }

    ll power(ll a, int b) {
        a %= MOD;
        ll res = 1;
        for (; b; b /= 2, a = a * a % MOD) {
            if (b % 2) {
                res = res * a % MOD;
            }
        }
        return res;
    }
    //区间幂次和
    ll powersum(int l, int r, int x) {
        auto itr = split(r + 1), itl = split(l);
        ll ans = 0;
        for (auto it = itl; it != itr; it++) {
            ans = (ans + power(it->v, x) * (it->r - it->l + 1) % MOD) % MOD;
        }
        return ans;
    }
    //区间一次和
    ll sum_one(int l,int r){
        ll ret=0;
        auto itl=split(l),itr=split(r+1);
        for(;itl!=itr;itl++){
            (ret+=(ll)(itl->r-itl->l+1)*itl->v)%=MOD;
        }
        return ret;
    }
    // 匹配暴力搜索（质数搭配欧拉筛）
    void query(int l,int r){
        auto itr=split(r+1),itl=split(l);
		int res = 0;
		for (; itl != itr; itl ++ ){
			// if (itl->v <= 1e7 && !st[itl->v])
			// 	res += itl->r - itl->l + 1;
        }
        cout<<res<<"\n";
    }
    void insert(const int& x,vector<int>& a){
        for(int i=1;i<=x;++i){
            s.insert(node(i,i,a[i]));
        }
    }
    void insert(int l,int r,int v){
        s.insert(node{l,r,v});
    }

    void copy(int l1,int r1,int l2,int r2){
        auto it1r=split(r1+1),it1l=split(l1);
        int len=0;
        for(auto it=it1l;it!=it1r;++it)
        {
            a[++len].l=it->l;
            a[len].r=it->r;
            a[len].v=it->v;
        }
        auto it2r=split(r2+1),it2l=split(l2);
        s.erase(it2l,it2r);
        for(int i=1;i<=len;++i)
        {
            s.insert(node(a[i].l - l1 + l2,a[i].r - l1 + l2,a[i].v));
        }
    }
    void Swap(int l1,int r1,int l2,int r2){
        if(l1>l2){swap(l1,l2);swap(r1,r2);}
        int len1=0,len2=0;
        auto it1r=split(r1+1),it1l=split(l1);
        for(auto it=it1l;it!=it1r;++it)
        {
            a[++len1].l=it->l;
            a[len1].r=it->r;
            a[len1].v=it->v;
        }
        auto it2r=split(r2+1),it2l=split(l2);
        for(auto it=it2l;it!=it2r;++it)
        {
            b[++len2].l=it->l;
            b[len2].r=it->r;
            b[len2].v=it->v;
        }
        it1r=split(r1+1),it1l=split(l1);
        s.erase(it1l,it1r);
        it2r=split(r2+1),it2l=split(l2);
        s.erase(it2l,it2r);
        for(int i=1;i<=len2;++i)s.insert(node(b[i].l - l2 + l1,b[i].r - l2 + l1,b[i].v));
        for(int i=1;i<=len1;++i)s.insert(node(a[i].l - l1 + l2,a[i].r - l1 + l2,a[i].v));
    }	
    void reverse(int l,int r){
        if(l>r)swap(l,r);
        auto it2=split(r+1),it1=split(l);
        int len=0;
        for(auto it=it1;it!=it2;++it)
        {
            a[++len].l=it->l;
            a[len].r=it->r;
            a[len].v=it->v;
        }
        s.erase(it1,it2);
        for(int i=1;i<=len;++i)
        {
            s.insert(node(r-a[i].r+l, r-a[i].l+l, a[i].v));
        }
    }
    void print(int n){
        for(auto it=s.begin();it!=s.end()&&it->r<=n;++it){
            for(int i=it->l;i<=it->r;++i) cout<<it->v<<" ";
        }
        cout<<"\n";
    }
};