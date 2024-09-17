For a sequence S1, S2, ... , SN, and a pair of integers (i, j), if 1 <= i <= j <= N and Si < Si+1 < Si+2 < ... < Sj-1 < Sj , then the sequence Si, Si+1, ... , Sj is a **CIS** (Continuous Increasing Subsequence). The longest **CIS** of a sequence is called the **LCIS** (Longest Continuous Increasing Subsequence).  
Now we consider a tree rooted at node 1. Nodes have values. We have Q queries, each with two nodes u and v. You have to find the shortest path from u to v. And write down each nodes' value on the path, from u to v, inclusive. Then you will get a sequence, and please show us the length of its **LCIS**.  

Input

The first line has a number T (T <= 10) , indicating the number of test cases.  
For each test case, the first line is a number N (N <= 105), the number of nodes in the tree.  
The second line comes with N numbers v1, v2, v3 ... , vN, describing the value of node 1 to node N. (1 <= vi <= 109)  
The third line comes with N - 1 numbers p2, p3, p4 ... , pN, describing the father nodes of node 2 to node N. Node 1 is the root and will have no father.  
Then comes a number Q, it is the number of queries. (Q <= 105)  
For next Q lines, each with two numbers u and v. As described above.

Output

For test case X, output "Case X:" at the first line.  
Then output Q lines, each with an answer to the query.  
There should be a blank line ***BETWEEN*** each test case.

Sample

|Inputcopy|Outputcopy|
|---|---|
|1<br>5<br>1 2 3 4 5<br>1 1 3 3<br>3<br>1 5<br>4 5<br>2 5|Case #1 :<br>3<br>2<br>3|


## 题解
我们这一题也是相当于把我们的树上问题转换到数组上的一个案例，本题要求我们求从 u 到 v 路径构成的数组的最大 LCIS，**最长连续子串**，我们可以**用线段树合并的思路**，维护我们最右端的值，最右端的大小，最左端的值，最左端的大小，合计长的的最大值，如果这一题是一个树上问题，我们考虑用我们的树链剖分，把我们的树上问题转换为一个链上问题。

```cpp
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
#define lson l,mid,rt<<1
#define rson mid+1,r,rt<<1|1
typedef long long ll;
const int MAXN=1e5+1;
int w[MAXN];// 各个顶点权值
int n,m;
vector<int> edge[MAXN];
 
int p[MAXN], dep[MAXN], sz[MAXN], son[MAXN];
void dfs1(int rt=1, int fa=0){
    p[rt]=fa, dep[rt]=dep[fa]+1, sz[rt]=1, son[rt]=0;
    for (auto &to : edge[rt]) {
        if (to==fa) continue;
        dfs1(to, rt);
        sz[rt]+=sz[to];
        if (sz[to]>sz[son[rt]]){
            son[rt]=to;
        }
    }
}
 
int id[MAXN], nw[MAXN], top[MAXN], ind;
void dfs2(int rt=1, int tp=1){
    id[rt]=++ind, nw[ind]=w[rt], top[rt]=tp;
    if (!son[rt]) return;
    dfs2(son[rt], tp);
    for (auto &to : edge[rt]) {
        if (to==son[rt] || to==p[rt]){
            continue;
        }
        dfs2(to, to);
    }
}
 
 
struct node{
    int l, r;
    int lmax,rmax,fmax;
    int LMAX,RMAX,FMAX;
    int vl, vr;
 
    void init(int L=0, int R=0){
        lmax=rmax=fmax=LMAX=RMAX=FMAX=vl=vr=0;
        l=L,r=R;
    }
 
    void reverse(){
        swap(lmax,RMAX), swap(rmax,LMAX),swap(fmax, FMAX);
        swap(vl,vr);
    }
 
}tree[MAXN<<2];
 
void push_up(node &rt, const node& l_rt, const node& r_rt){
    const int llen=l_rt.r-l_rt.l+1, rlen=r_rt.r-r_rt.l+1;
    rt.fmax = max({l_rt.fmax, r_rt.fmax, l_rt.vr<r_rt.vl ? l_rt.rmax+r_rt.lmax : 0});
    rt.lmax = l_rt.lmax + (l_rt.lmax==llen && l_rt.vr<r_rt.vl ? r_rt.lmax : 0);
    rt.rmax = r_rt.rmax + (r_rt.rmax==rlen && l_rt.vr<r_rt.vl ? l_rt.rmax : 0);
 
    rt.FMAX = max({l_rt.FMAX, r_rt.FMAX, l_rt.vr>r_rt.vl ? l_rt.RMAX+r_rt.LMAX : 0});
    rt.LMAX = l_rt.LMAX + (l_rt.LMAX==llen && l_rt.vr>r_rt.vl ? r_rt.LMAX : 0);
    rt.RMAX = r_rt.RMAX + (r_rt.RMAX==rlen && l_rt.vr>r_rt.vl ? l_rt.RMAX : 0);
    rt.vl=l_rt.vl, rt.vr=r_rt.vr;
}
 
void push_up(int rt){
    push_up(tree[rt], tree[rt<<1], tree[rt<<1|1]);
}
 
void build(int l,int r,int rt){
    tree[rt] = {l,r,1,1,1,1,1,1,nw[l],nw[l]};
    if (l>=r) return;
    int mid=(l+r)>>1;
    build(lson);
    build(rson);
    push_up(rt);
}
 
node query(int ul,int ur,int l,int r,int rt){
//    cout<<"interval [ul,ur]"<<"["<<ul<<","<<ur<<"], "<<""<<"[l,r]:["<<l<<","<<r<<"]"<<endl;
    if (ul <= l && r <= ur) return tree[rt];
    int mid = (l+r)>>1;
    if (ur<=mid) return query(ul, ur, lson);
    if (ul>mid) return query(ul,ur,rson);
 
    node left = query(ul,ur,lson);
    node right = query(ul,ur, rson);
    node res;
    res.init(left.l,right.r);
    push_up(res, left, right);
    return res;
}
 
node merge(const node& l, const node& r){
    if (!l.l) return r;
    if (!r.l) return l;
    node res;
    res.init(l.l,r.r);
    push_up(res,l,r);
    return res;
}
 
int query_route(int a,int b){
    node la,lb;
    la.init(),lb.init();
    int flag=0;
//    cout<<"route 1"<<endl;
    while (top[a]!=top[b]){
//        cout<<"dep:"<<dep[top[a]]<<", "<<dep[top[b]]<<endl;
        if (dep[top[a]] < dep[top[b]]) swap(a,b), swap(la,lb),flag^=1;
//        cout<<"id:"<<id[top[a]]<<", "<<id[a]<<endl;
        la = merge(query(id[top[a]], id[a],1,n,1), la);
        a=p[top[a]];
    }
//    cout<<"route 2"<<endl;
    if (id[a]>id[b]){
        swap(a,b), swap(la,lb),flag^=1;
    }
//    cout<<"route 3"<<endl;
    lb= merge(query(id[a],id[b],1,n,1),lb);
    if (flag) swap(la,lb);
    la.reverse();
    return merge(la,lb).fmax;
}
 
int main(){
    int kase;
    cin>>kase;
    for (int i = 1; i <= kase; ++i) {
        printf("Case #%d:\n", i); ind = 0;
        scanf("%d", &n);
        for (int i=1;i<=n;++i) {
            scanf("%d",&w[i]);
            edge[i].clear();
        }
        int father;
        for (int i = 2; i <= n; ++i) {
            scanf("%d",&father);
            edge[father].push_back(i);
        }
 
        dfs1();
        dfs2();
        build(1,n,1);
        scanf("%d", &m);
        int a,b;
        for (int i = 0; i < m; ++i) {
            scanf("%d %d",&a,&b);
//            cout<<"a:"<<a<<",b:"<<b<<endl;
            printf("%d\n", query_route(a,b));
        }
        if (i!=kase) puts("");
    }
    return 0;
}
```