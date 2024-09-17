#树上主席树 #在线 #主席树求区间第k大 #LCA #最近公共祖先
# Count on a tree

## 题目描述

给定一棵 $n$ 个节点的树，每个点有一个权值。有 $m$ 个询问，每次给你 $u,v,k$，你需要回答 $u \text{ xor last}$ 和 $v$ 这两个节点间第 $k$ 小的点权。  

其中 $\text{last}$ 是上一个询问的答案，定义其初始为 $0$，即第一个询问的 $u$ 是明文。

## 输入格式

第一行两个整数 $n,m$。

第二行有 $n$ 个整数，其中第 $i$ 个整数表示点 $i$ 的权值。

后面 $n-1$ 行每行两个整数 $x,y$，表示点 $x$ 到点 $y$ 有一条边。

最后 $m$ 行每行两个整数 $u,v,k$，表示一组询问。

## 输出格式

$m$ 行，每行一个正整数表示每个询问的答案。

## 样例 #1

### 样例输入 #1

```
8 5
105 2 9 3 8 5 7 7
1 2
1 3
1 4
3 5
3 6
3 7
4 8
2 5 1
0 5 2
10 5 3
11 5 4
110 8 2
```

### 样例输出 #1

```
2
8
9
105
7
```

## 提示

【数据范围】  
对于 $100\%$ 的数据，$1\le n,m \le 10^5$，点权在 $[1, 2 ^ {31} - 1]$ 之间。

暴力自重。。。

来源：bzoj 2588 Spoj 10628.

本题数据为洛谷自造数据，使用 [CYaRon](https://github.com/luogu-dev/cyaron) 耗时 5 分钟完成数据制作。

## 题解
我们这一题采用我们的树上主席树来进行我们的操作
前置知识是主席树。在利用主席树求解区间第 K 小数时可以发现，主席树是一种类似前缀和的数据结构，具有和前缀和类似的区间加减及差分等优秀性质。在求解线性区间的第 K 小数时，我们需要将该区间内的所有数值信息扔到一棵主席树中，并在这棵主席树上左右递归，以找到第 K 小数；同样的，我们可以类比树上前缀和的操作，定义$s[u]$为从根节点到第u 号节点的“前缀主席树”（感性理解谢谢）。那么，包含u 到v 上所有数值信息的主席树就应该是：

$$s[u]+s[v]−s[lca(u,v)]−s[fa[lca(u,v)]]$$

理解上式后，问题基本可以解决了。另外注意离散化和主席树的代码细节。代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
// 离散化操作
#define id(x) (lower_bound(b+1,b+L+1,a[x])-b)
#define rid(x) (b[x])

const int MAXN = 100005;

struct Node {
    int l, r, sum;
}node[10000005];
int head[MAXN],cnt;

vector<int> G[MAXN];

int N, M, L, lastans;
int a[MAXN], b[MAXN];
int f[MAXN][19], dep[MAXN];

inline void build(Node &u, int l, int r) {
    u.sum = 0;
    if (l == r) return;
    int mid = (l + r) >> 1;
    build(node[u.l = ++cnt], l, mid);
    build(node[u.r = ++cnt], mid + 1, r);
}

inline void insert(Node c, Node &u, int l, int r, int p) {
    u.sum = c.sum + 1;
    if (l == r) return;
    int mid = (l + r) >> 1;
    if(p <= mid)
        insert(node[c.l], node[u.l = ++cnt], l, mid, p), u.r = c.r;
    else
        insert(node[c.r], node[u.r = ++cnt], mid+1, r, p), u.l = c.l;
}

inline void dfs(int u, int fa) {
    insert(node[head[fa]], node[head[u] = ++cnt], 1, L, id(u));
    f[u][0] = fa;
    dep[u] = dep[fa] + 1;
    for (register int i = 1; i <= 18; ++i)
        f[u][i] = f[f[u][i-1]][i-1];
    for (vector<int>::iterator it = G[u].begin(); it != G[u].end(); it++) {
        int v = *it;
        if (v == fa) continue;
        dfs(v, u);
    }
}

inline int Lca(int u, int v) {
    if (dep[u] < dep[v]) swap(u, v);
    for (register int i = 18; i >= 0; --i) {
        if (dep[f[u][i]] >= dep[v]) u = f[u][i];
    }
    if (u == v) return u;
    for (register int i = 18; i >= 0; --i) {
        if (f[u][i] != f[v][i])
            u = f[u][i], v = f[v][i];
    }
    return f[u][0];
}

inline int query(Node x, Node y, Node z, Node w, int l, int r, int k) {
    if (l == r) return l;
    int sum = node[x.l].sum + node[y.l].sum - node[z.l].sum - node[w.l].sum;
    int mid = (l + r) >> 1;
    if(sum >= k) return query(node[x.l], node[y.l], node[z.l], node[w.l], l, mid, k);
    return query(node[x.r], node[y.r], node[z.r], node[w.r], mid+1, r, k - sum);
}

inline int querypath(int u, int v, int k) {
    int lca = Lca(u, v);
    return rid(query(node[head[u]], node[head[v]], node[head[lca]], node[head[f[lca][0]]], 1, L, k));
}

int main() {
    scanf("%d%d", &N, &M);
    for (register int i = 1; i <= N; ++i)
        scanf("%d", &a[i]), b[i] = a[i];
    for (register int i = 1; i < N; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        G[u].push_back(v);
        G[v].push_back(u);
    }
    sort(b + 1, b + N + 1);
    L = unique(b + 1, b + N + 1) - (b + 1);
    build(node[head[0] = ++cnt], 1, L);
    dfs(1, 0);
    for (register int i = 1; i <= M; ++i) {
        int u, v, k;
        scanf("%d%d%d", &u, &v, &k);
        int nowans = querypath(u^lastans, v, k);
        printf("%d\n", nowans);
        lastans = nowans;
    }
}
```