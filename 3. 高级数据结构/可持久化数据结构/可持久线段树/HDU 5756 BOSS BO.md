There is a tree with $N$ nodes, whose root is 1.  
  
There are $Q$ queries for you,for each query,we will give $K$ numbers,which are $A_1,A_2,\dots,A_K$.  
  
For every node $x\in[1,N]$ in the tree,we assume it's good if there is not a node $y\in A$,such that $y$ is the ancient of $x$ or $y=x$  
  
And we will give two numbers $T , P$ to show the property of each query.  
  
1.when $T=1$,you should output the sum of the distance between every good node and $P$.  
  
2.when $T=2$,you should output the minimum distance between every good node and $P$.  
  
3.when $T=3$,you should output the maximum distance between every good node and $P$.  
  
Let the distance between nodes in the tree be the shortest path between these two nodes.And we assume the length of each edge is 1.  
  
Specially,the distance between two same nodes is 0.  
  
For each query,if there is no nodes that is good,just output -1.

Input

There are several test cases.  
  
For each test case,the first line contains two numbers $N$ and $Q$.  
  
For the following $N-1$ lines,each line contains two numbers $u$ and $v$,indicating there is a edge between $u$ and $v$ in tree.  
  
For the following $Q$ lines,each line contains some numbers,which are $K,P',T,A_1,A_2,\dots,A_K$ in order.  
  
Let the answer of last query be $lastans$,then $P=(P' + lastAns)~\mod{N} + 1$.  
  
If the answer of last query is -1 or it's the first query,then $lastans=0$.  
  
Let the number of test cases be $T$,we guarantee $T=30$.  
  
$80\%$ test cases satisfy $N,K,Q \le 10000$ ,$\sum{K} \le 20000$.  
  
$100\%$ test cases satisfy ~$P, N,K \le 50000$,$Q \le 100000$,$\sum{K} \le 200000$.

Output

You should output Q lines in total,each line contains a number indicating the answer of each query.  

Sample

|Inputcopy|Outputcopy|
|---|---|
|6 5<br>1 3<br>2 1<br>4 2<br>6 4<br>5 6<br>3 5 3<br>3 3 3<br>3 4 3<br>4 5 1<br>3 3 1<br>1 5 6<br>3 5 2<br>3 4 2<br>3 3 3<br>6 5 3|3<br>-1<br>-1<br>3<br>2|

## 题解
我们可以用主席树对于所有点，维护出他到所有点的距离，大致过程：
对于一号店，他到所有点的距离为该点的深度-1.
接着我们 DFS 一整颗数，每到一个结点就将子树中的点距离-1，不是子树的点距离+1，我们就可以得到每一个点的 DFS 序，这样我们只需要用主席树支持区间加减、维护区间和、区间最小值、区间最大值即可。

```cpp
#include <bits/stdc++.h>

using namespace std;

#define LL long long
#define pii pair<int, int>
#define MP make_pair
#define ls i << 1
#define rs ls | 1
#define md (ll + rr >> 1)
#define inf 0x3f3f3f3f
#define mod 1000000007
#define N 100020
#define M 500020

int n, Q;
int fst[N], vv[M], nxt[M], e;
int st[N], ed[N], dep[N], lab[N], dc;
int sum[N*50], mx[N*50], mi[N*50], add[N*50], ch[N*50][2];
int rt[N], tot;
pii a[N*5];
void init(){
    memset(fst, -1, sizeof fst); e = 0;
}
void adde(int u, int v){
    vv[e] = v, nxt[e] = fst[u], fst[u] = e++;
}
void dfs(int u, int p, int d){
    dep[u] = d;
    st[u] = ++dc;
    lab[dc] = u;
    for(int i = fst[u]; ~i; i = nxt[i]){
        int v = vv[i];
        if(v == p) continue;
        dfs(v, u, d + 1);
    }
    ed[u] = dc;
}
void push_up(int i, int ll, int rr){
    sum[i] = sum[ch[i][0]] + sum[ch[i][1]] + (rr - ll + 1) * add[i];
       mx[i] = max(mx[ch[i][0]], mx[ch[i][1]]) + add[i];
    mi[i] = min(mi[ch[i][0]], mi[ch[i][1]]) + add[i];
}    
int build(int ll, int rr){
    int k = ++tot;
    if(ll == rr){
        sum[k] = mx[k] = mi[k] = dep[lab[ll]] - 1;
        ch[k][0] = ch[k][1] = add[k] = 0;
        return k;
    }
    sum[k] = mx[k] = mi[k] = add[k] = 0;
    ch[k][0] = build(ll, md);
    ch[k][1] = build(md + 1, rr);
    push_up(k, ll, rr);
    return k;
}
int update(int l, int r, int v, int ll, int rr, int i){
    int k = ++tot;
    sum[k] = sum[i], add[k] = add[i];
    mx[k] = mx[i], mi[k] = mi[i];
    ch[k][0] = ch[i][0], ch[k][1] = ch[i][1];
    if(l == ll && r == rr){
        add[k] += v;
        sum[k] += (r - l + 1) * v;
        mx[k] += v;
        mi[k] += v;
        return k;
    }
    if(r <= md) ch[k][0] = update(l, r, v, ll, md, ch[i][0]);
    else if(l > md) ch[k][1] = update(l, r, v, md + 1, rr, ch[i][1]);
    else{
        ch[k][0] = update(l, md, v, ll, md, ch[i][0]);
        ch[k][1] = update(md + 1, r, v, md + 1, rr, ch[i][1]);
    }
    push_up(k, ll, rr);
    return k;
}
void dfs1(int u, int p){
    for(int i = fst[u]; ~i; i = nxt[i]){
        int v = vv[i];
        if(v == p) continue;
        rt[v] = update(st[v], ed[v], -1, 1, n, rt[u]);
        if(st[v] > 1)
            rt[v] = update(1, st[v] - 1, 1, 1, n, rt[v]);
        if(ed[v] < n)
            rt[v] = update(ed[v] + 1, n, 1, 1, n, rt[v]);
        dfs1(v, u);
    }
}
int query(int l, int r, int t, int ll, int rr, int i){
    if(l == ll && r == rr){
        if(t == 1) return sum[i];
        else if(t == 2) return mi[i];
        else return mx[i];
    }
    if(r <= md){
        int ret = query(l, r, t, ll, md, ch[i][0]);
        if(t == 1) ret += (r - l + 1) * add[i];
        else ret += add[i];
        return ret;
    }
    else if(l > md){
        int ret = query(l, r, t, md + 1, rr, ch[i][1]);
        if(t == 1) ret += (r - l + 1) * add[i];
        else ret += add[i];
        return ret;
    }
    else{
        int ret1 = query(l, md, t, ll, md, ch[i][0]);
        int ret2 = query(md + 1, r, t, md + 1, rr, ch[i][1]);
        if(t == 1) return ret1 + ret2 + (r - l + 1) * add[i];
        if(t == 2) return min(ret1, ret2) + add[i];
        if(t == 3) return max(ret1, ret2) + add[i];
    }
}
int main(){
    while(scanf("%d%d", &n, &Q) != EOF){
        init();
        for(int i = 1; i < n; ++i){
            int u, v;
            scanf("%d%d", &u, &v);
            adde(u, v);
            adde(v, u);
        }
        dc = 0;
        dfs(1, -1, 1);
        tot = 0;
        rt[1] = build(1, n);
        dfs1(1, -1);
        int K, P, PP, t, ans = 0;
        while(Q--){
            scanf("%d%d%d", &K, &P, &t);
            P = (P + ans) % n + 1;
            bool ok = 0;
            for(int i = 1; i <= K; ++i){
                int x;
                scanf("%d", &x);
                a[i] = MP(st[x], ed[x]);
                if(x == 1) ok = 1;
            }
            if(ok){
                puts("-1"); ans = 0;
                continue;
            }
            sort(a + 1, a + 1 + K);
            a[++K] = MP(n + 1, n + 1);
            if(t == 1) ans = 0;
            if(t == 2) ans = inf;
            if(t == 3) ans = -inf;
            int pre = 1;
            for(int i = 1; i <= K; ++i){
                if(pre < a[i].first){
                    if(t == 1) ans += query(pre, a[i].first - 1, t, 1, n, rt[P]);
                    else if(t == 2)
                        ans = min(ans, query(pre, a[i].first - 1, t, 1, n, rt[P]));
                    else
                        ans = max(ans, query(pre, a[i].first - 1, t, 1, n, rt[P]));    
                }
                pre = max(pre, a[i].second + 1);
            }
            printf("%d\n", ans);
        }
    }    
    return 0;
}
```