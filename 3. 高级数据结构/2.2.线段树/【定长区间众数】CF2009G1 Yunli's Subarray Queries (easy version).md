# Yunli's Subarray Queries (easy version)

## 题目描述

This is the easy version of the problem. In this version, it is guaranteed that $ r=l+k-1 $ for all queries.

For an arbitrary array $ b $ , Yunli can perform the following operation any number of times:

- Select an index $ i $ . Set $ b_i = x $ where $ x $ is any integer she desires ( $ x $ is not limited to the interval $ [1, n] $ ).

Denote $ f (b) $ as the minimum number of operations she needs to perform until there exists a consecutive subarray $ ^{\text{∗}} $ of length at least $ k $ in $ b $ .

Yunli is given an array $ a $ of size $ n $ and asks you $ q $ queries. In each query, you must output $ \sum_{j=l+k-1}^{r} f ([a_l, a_{l+1}, \ldots, a_j]) $ . Note that in this version, you are only required to output $ f ([a_l, a_{l+1}, \ldots, a_{l+k-1}]) $ .

 $ ^{\text{∗}} $ If there exists a consecutive subarray of length $ k $ that starts at index $ i $ ( $ 1 \leq i \leq |b|-k+1 $ ), then $ b_j = b_{j-1} + 1 $ for all $ i < j \leq i+k-1 $ .

## 输入格式

The first line contains $ t $ ( $ 1 \leq t \leq 10^4 $ ) — the number of test cases.

The first line of each test case contains three integers $ n $ , $ k $ , and $ q $ ( $ 1 \leq k \leq n \leq 2 \cdot 10^5 $ , $ 1 \leq q \leq 2 \cdot 10^5 $ ) — the length of the array, the length of the consecutive subarray, and the number of queries.

The following line contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ 1 \leq a_i \leq n $ ).

The following $ q $ lines contain two integers $ l $ and $ r $ ( $ 1 \leq l \leq r \leq n $ , $ r=l+k-1 $ ) — the bounds of the query.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ and the sum of $ q $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

Output $ \sum_{j=l+k-1}^{r} f ([a_l, a_{l+1}, \ldots, a_j]) $ for each query on a new line.

## 样例 #1

### 样例输入 #1

```
3
7 5 3
1 2 3 2 1 2 3
1 5
2 6
3 7
8 4 2
4 3 1 1 2 4 3 2
3 6
2 5
5 4 2
4 5 1 2 3
1 4
2 5
```

### 样例输出 #1

```
2
3
2
2
2
2
1
```

## 提示

In the first query of the first testcase, $ b=[1,2,3,2,1] $ . Yunli can make a consecutive subarray of length $ 5 $ in $ 2 $ moves:

- Set $ b_4=4 $
- Set $ b_5=5 $

 After operations $ b=[1, 2, 3, 4, 5] $ .In the second query of the first testcase, $ b=[2,3,2,1,2] $ . Yunli can make a consecutive subarray of length $ 5 $ in $ 3 $ moves:

- Set $ b_3=0 $
- Set $ b_2=-1 $
- Set $ b_1=-2 $

 After operations $ b=[-2, -1, 0, 1, 2] $ .

## 题解
我们有一个很经典的 trick，如果我们希望我们的最终结果是一个等差数列，我们可以让我们的每一个对应的位置都变为 $a[i]-i$,然后我们再要求我们的每一个位置都是相同的即可。

于是，考虑贪心的修改，我们显然希望我们的区间都修改为区间内出现次数最多的那一个数字，然后，我们再去进行操作即可。

因为在本题中我们的区间是定长的，所以我们可以通过我们的权值线段树来进行处理。我们权值线段树维护我们的一个区间内出现次数的最多的元素是什么。

```
#include <bits/stdc++.h>
#define int long long
#define endl '\n'
int INF = 0x3f3f3f3f3f3f3f3f;
using namespace std;
typedef pair<int, int> PII;
void init()
{
}
const int N = 4e5 + 10;
class SegmentTree
{
public:
    struct Node
    {
        int l, r;
        int maxx;
    } tr[N << 2];
    Node merge(Node x, Node y)
    {
        if (x.l == -1)
            return y;
        if (y.l == -1)
            return x;
        Node z;
        z.l = min(x.l, y.l);
        z.r = max(x.r, y.r);
        z.maxx = max(x.maxx, y.maxx);
        return z;
    } // 这里需要改
    void pushup(int u)
    {
        tr[u] = merge(tr[u << 1], tr[u << 1 | 1]);
    }
    void build(int u, int l, int r)
    {
        tr[u] = {l, r, 0};
        if (l == r)
            return;
        int mid = l + r >> 1;
        build(u << 1, l, mid);
        build(u << 1 | 1, mid + 1, r);
        pushup(u);
    }
    void update(int u, int p, int x)
    {
        if (tr[u].l == tr[u].r)
        {
            // 这里需要改
            tr[u].maxx += x;
            return;
        }
        int mid = tr[u].l + tr[u].r >> 1;
        if (p <= mid)
            update(u << 1, p, x);
        else
            update(u << 1 | 1, p, x);
        pushup(u);
    }
    Node query(int u, int l, int r)
    {
        if (tr[u].l >= l and tr[u].r <= r)
        {
            return tr[u];
        }
        int mid = tr[u].l + tr[u].r >> 1;
        Node ret;
        ret.l = -1;
        if (l <= mid)
            ret = query(u << 1, l, r);
        if (r > mid)
            ret = merge(ret, query(u << 1 | 1, l, r));
        return ret;
    }
} t;
void solve()
{
    int n, m, q;
    cin >> n >> m >> q;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
        a[i] -= i;
        a[i] += n;
    }
    t.build(1, 1, 2 * n);
    for (int i = 1; i <= m; i++)
    {
        t.update(1, a[i], 1);
    }
    vector<int> w(n + 1);
    w[1] = m - t.query(1, 1, 2 * n).maxx;
    for (int i = 2; i + m - 1 <= n; i++)
    {
        t.update(1, a[i + m - 1], 1);
        t.update(1, a[i - 1], -1);
        w[i] = m - t.query(1, 1, 2 * n).maxx;
        // cout<<m-t.query(1,1,n).maxx<<endl;
    }
    while (q--)
    {
        int l, r;
        cin >> l >> r;
        cout << w[l] << endl;
    }
}
signed main()
{
    ios::sync_with_stdio(false), cin.tie(0);
    int t;
    t = 1;
    cin >> t;
    init();
    while (t--)
    {
        solve();
    }
}
```