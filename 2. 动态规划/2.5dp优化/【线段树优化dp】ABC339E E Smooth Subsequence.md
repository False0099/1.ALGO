### Problem Statement

You are given a sequence $A = (A_1, A_2, \ldots, A_N)$ of length $N$.

Find the maximum length of a subsequence of $A$ such that the absolute difference between any two adjacent terms is at most $D$.

A subsequence of a sequence $A$ is a sequence that can be obtained by deleting zero or more elements from $A$ and arranging the remaining elements in their original order.

### Constraints

-   $1 \leq N \leq 5 \times 10^5$
-   $0 \leq D \leq 5 \times 10^5$
-   $1 \leq A_i \leq 5 \times 10^5$
-   All input values are integers.

### Input

The input is given from Standard Input in the following format:

```
$N$ $D$
$A_1$ $A_2$ $\ldots$ $A_N$
```


### Output

Print the answer.

### Sample Input 1

```
4 2
3 5 1 2
```

### Sample Output 1

```
3
```

The subsequence $(3, 1, 2)$ of $A$ has absolute differences of at most $2$ between adjacent terms.
### Sample Input 2

```
5 10
10 20 100 110 120
```

### Sample Output 2

```
3
```

## 题解
我们这一题的 dp 非常好想，我们令我们的 $dp[i]$ 表示我们到 i 位置时，我们的数列的最大长度是多少。然后，我们就只需要进行一个转移：$dp[i]=min(dp[j])+1$，其中我们的 $j$ 要求满足 $(k\leq |i-j|)$。于是，我们就可以通过我们的线段树来进行我们的优化，我们的线段树中存储具体的数值对应的 dp 是多少，然后每一次查询我们就查询区间内的最大值。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define pii pair<int, int>
#define pdd pair<double, double>
#define pll pair<ll, ll>
#define endl '\n'
typedef long long ll;
struct info {
    int maxv;
};
info operator + (const info &l, const info &r) {
    info a;
    a.maxv = max(l.maxv, r.maxv);
    return a;
}

const int N = 5e5+50;
struct node {
    info val;
} tr[N * 4];
int a[N];
void update(int id)
{
    tr[id].val = tr[id*2].val + tr[id*2+1].val;
}
void build(int id, int l, int r)
{
    if(l == r) 
        tr[id].val = {a[l]};
    else {
        int mid = l+r >> 1;
        build(id*2, l, mid);
        build(id*2+1, mid+1, r);
        update(id);
    }
}
void change(int id, int l, int r, int pos, int val)
{
    if(l == r)
        tr[id].val = {val};
    else {
        int mid = l+r >> 1;
        if(pos <= mid) change(id*2, l, mid, pos, val);
        else change(id*2+1, mid+1, r, pos, val);
        update(id);
    }
}
info query(int id, int l, int r, int ql, int qr)
{
    if(l == ql && r == qr) return tr[id].val;
    int mid = l+r >> 1;
    if(qr <= mid) return query(id*2, l, mid, ql, qr);
    else if(ql > mid) return query(id*2+1, mid+1, r, ql, qr);
    else return query(id*2, l, mid, ql, mid) + 
    query(id*2+1, mid+1, r, mid+1, qr);
}
int main()
{
    cout << fixed << setprecision(10);
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    int n, d;
    cin >> n >> d;
    vector<int> v(n+5);
    for(int i=1; i<=n; i++)
        cin >> v[i];
    int maxn = 5e5;
    build(1, 1, maxn);
    for(int i=1; i<=n; i++) {
        int maxx = query(1, 1, maxn, max(1, v[i]-d), min(v[i]+d, maxn)).maxv;
        change(1, 1, maxn, v[i], maxx+1);
    }
    cout << query(1, 1, maxn, 1, maxn).maxv << endl;
    return 0;
}
```