# [ABC 360 F] InterSections

## 题面翻译

给定 $N$ 个闭区间 $[L_i,R_i]$。

- 定义区间 $[l_a,r_a]$ 与区间 $[l_b,r_b]$ **相交**，当且仅当 $l_a\lt l_b\lt r_a\lt r_b$ 或 $l_b\lt l_a\lt r_b\lt r_a$；
- 定义 $f(l,r)$ 为 $N$ 个区间中，与 $[l,r]$ 相交的区间的数量。

对于 $\forall 0\le l\lt r\le 10^9$，找出一组能使 $f(l,r)$ 取到最大值的 $[l,r]$。若有多解，则输出 $l$ 最小的；若仍有多解，输出 $r$ 最小的。

$1\le N\le 10^5$，$1\le L_i\lt R_i\le 10^9$。

$\text{Statement fixed by @Starrykiller.}$

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc360/tasks/abc360_f

$ 1 $ から $ N $ までの番号のついた $ N $ 個の区間が与えられます。区間 $ i $ は $ [L_i, R_i] $ です。

区間 $ [l_a, r_a] $ と区間 $ [l_b, r_b] $ は $ (l_a\ <\ l_b\ <\ r_a\ <\ r_b) $ または $ (l_b\ <\ l_a\ <\ r_b\ <\ r_a) $ を満たすとき、**交差する**といいます。

$ f (l, r) $ を $ 1\ \leq\ i\ \leq\ N $ を満たし、区間 $ [l, r] $ と区間 $ i $ が交差する $ i $ の個数と定義します。

$ 0\ \leq\ l\ <\ r\ \leq\ 10^{9} $ を満たす**整数**の組 $ (l, r) $ において、 $ f (l, r) $ の最大値を達成する $ (l, r) $ の組のうち $ l $ が最小のものを答えてください。そのような組が複数存在する場合はさらにそのうちで $ r $ が最小のものを答えてください ($ 0\ \leq\ l\ <\ r $ より、答えるべき $ (l, r) $ の組は一意に定まります)。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ N $ $ L_1 $ $ R_1 $ $ L_2 $ $ R_2 $ $ \vdots $ $ L_N $ $ R_N $

## 输出格式

答えとなる組 $ (l, r) $ を次の形式で出力せよ。

> $ l $ $ r $

## 样例 #1

### 样例输入 #1

```
5
1 7
3 9
7 18
10 14
15 20
```

### 样例输出 #1

```
4 11
```

## 样例 #2

### 样例输入 #2

```
11
856977192 996441446
298251737 935869360
396653206 658841528
710569907 929136831
325371222 425309117
379628374 697340458
835681913 939343451
140179224 887672320
375607390 611397526
93530028 581033295
249611310 775998537
```

### 样例输出 #2

```
396653207 887672321
```

## 提示

### 制約

- $ 1\ \leq\ N\ \leq\ 10^{5} $
- $ 0\ \leq\ L_i\ <\ R_i\ \leq\ 10^{9} $ $ (1\ \leq\ i\ \leq\ N) $
- 入力は全て整数である

### Sample Explanation 1

$ f (l, r) $ の最大値は $ 4 $ であり、$ f (l, r)=4 $ となる $ (l, r) $ のうち $ l $ の最小値は $ 4 $ です。 $ f (l, r)=4 $ かつ $ l=4 $ を満たす $ (l, r) $ は以下の $ 5 $ 通りです。 - $ (l, r)=(4,11) $ - $ (l, r)=(4,12) $ - $ (l, r)=(4,13) $ - $ (l, r)=(4,16) $ - $ (l, r)=(4,17) $ このうち、$ r $ の最小値は $ 11 $ であるため、$ 4 $ と $ 11 $ を出力します。


## 题解
本题我们的一个关键是找到我们的**线段交**和我们的**矩形之间的关系**。我们最好的办法就是将我们的对应的线段交**转换为我们的矩形**。

我们这个时候就有：我们**计算我们的每一个举行的贡献**，考虑与 $[L_i,R_i]$ 相交的 $[l,r]$ 需要满足什么条件：
$1.L_i<l<R_i<r$,可以得出 $L_i+1\leq l\leq R_i-1,R_i+1\leq r\leq10^9;$


$2.l<L_i<r<R_i$,可以得出 $0\leq l\leq L_i-1,L_i+1\leq r\leq R_i-1$。

建立平面直角坐标系，$x$ 轴表示 $l$, $y$ 轴表示 $r$。可以发现，上面的情况 1 转化为左下角 $(L_i+1,R_i+$ 1), 右上角 $\left(R_i-1,10^9\right)$ 的矩形，情况 2 转化为左下角 $\left(0,L_i+1\right)$,右上角 $\left(L_i-1,R_i-1\right)$ 的矩形。那么问题变为在平面直角坐标系找到一个点，使它被最多的矩形覆盖，扫描线即可。


```cpp
#include <bits/stdc++.h>
#define int long long
#define endl '\n'
constexpr int INF = 1e9;
using namespace std;
typedef pair<int, int> PII;
constexpr int N = 1e6 + 10;

struct Edge {
    int l, r1, r2, ff;
} e[N << 4];

int edgecnt;

void add_edge(int l, int r1, int r2, int f) {
    e[++edgecnt] = {l, r1, r2, f};
}

bool cmp(const Edge& a, const Edge& b) {
    return a.l == b.l ? a.ff > b.ff : a.l < b.l;
}

class SegmentTree {
public:
    struct Node {
        int l, r, sum, maxx, max_id, add_tag;
    } tr[N << 2];

    Node merge(const Node& x, const Node& y) {
        if (x.l == -1) return y;
        if (y.l == -1) return x;
        Node z;
        z.l = min(x.l, y.l);
        z.r = max(x.r, y.r);
        z.sum = x.sum + y.sum;
        z.maxx = max(x.maxx, y.maxx);
        z.max_id = (z.maxx == x.maxx) ? x.max_id : y.max_id;
        z.add_tag = 0;
        return z;
    }

    void pushup(int u) {
        tr[u] = merge(tr[u << 1], tr[u << 1 | 1]);
    }

    void pushdown(int u) {
        if (tr[u].add_tag) {
            int add_tag = tr[u].add_tag;
            apply_tag(u << 1, add_tag);
            apply_tag(u << 1 | 1, add_tag);
            tr[u].add_tag = 0;
        }
    }

    void apply_tag(int u, int add_tag) {
        tr[u].add_tag += add_tag;
        tr[u].maxx += add_tag;
        tr[u].sum += add_tag * (tr[u].r - tr[u].l + 1);
    }

    void build(int u, int l, int r) {
        tr[u] = {l, r, 0, -1, l, 0};
        if (l == r) return;
        int mid = (l + r) >> 1;
        build(u << 1, l, mid);
        build(u << 1 | 1, mid + 1, r);
        pushup(u);
    }

    void update(int u, int l, int r, int p) {
        if (l > r) return;
        if (tr[u].l >= l && tr[u].r <= r) {
            apply_tag(u, p);
            return;
        }
        pushdown(u);
        int mid = (tr[u].l + tr[u].r) >> 1;
        if (l <= mid) update(u << 1, l, r, p);
        if (r > mid) update(u << 1 | 1, l, r, p);
        pushup(u);
    }

    Node query(int u, int l, int r) {
        if (tr[u].l >= l && tr[u].r <= r) return tr[u];
        pushdown(u);
        int mid = (tr[u].l + tr[u].r) >> 1;
        Node ret = {-1, -1, 0, -INF, -1, 0};
        if (l <= mid) ret = query(u << 1, l, r);
        if (r > mid) ret = merge(ret, query(u << 1 | 1, l, r));
        return ret;
    }
} t;

vector<int> lsh;

void solve() {
    int n;
    cin >> n;
    vector<PII> line(n);
    for (int i = 0; i < n; i++) {
        int l, r;
        cin >> l >> r;
        lsh.push_back(l + 1);
        lsh.push_back(r - 1);
        lsh.push_back(r + 1);
        lsh.push_back(INF);
        add_edge(0, l + 1, r - 1, 1);
        add_edge(l - 1, l + 1, r - 1, -1);
        add_edge(l + 1, r + 1, INF, 1);
        add_edge(r - 1, r + 1, INF, -1);
    }
    sort(begin(lsh), end(lsh));
    lsh.erase(unique(begin(lsh), end(lsh)), end(lsh));
    sort(e + 1, e + 1 + 4 * n, cmp);
    t.build(1, 0, lsh.size() - 1);
    int ansl = 0, ansr = 1, ans = 0;
    auto getrk = [&](int num) {
        return lower_bound(begin(lsh), end(lsh), num) - begin(lsh);
    };
    for (int i = 1; i <= 4 * n; i++) {
        t.update(1, getrk(e[i].r1), getrk(e[i].r2), e[i].ff);
        auto u = t.query(1, 0, lsh.size() - 1);
        if (u.maxx > ans) {
            ans = u.maxx;
            ansl = e[i].l;
            ansr = lsh[u.max_id];
        } else if (u.maxx == ans && e[i].l == ansl) {
            ansr = max(1ll, min(ansr, lsh[u.max_id]));
        }
    }
    cout << ansl << " " << ansr << endl;
}

signed main() {
    ios::sync_with_stdio(false), cin.tie(0);
    int t = 1;
    solve();
}
```