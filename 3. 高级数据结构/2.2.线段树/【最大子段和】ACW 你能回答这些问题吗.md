# 知识点
  ## [[线段树]]
# 题目
 给定长度为 N的数列 A，以及 M条指令，每条指令可能是以下两种之一：

1 x y，查询区间 [x, y]中的最大连续子段和，即 maxx≤l≤r≤y{∑i=lrA[i]}。
2 x y，把 A[x]改成 y。
对于每个查询指令，输出一个整数表示答案。

## 输入格式
第一行两个整数 N, M。

第二行 N个整数 A[i]。

接下来 M行每行 3个整数 k, x, y，k=1表示查询（此时如果 x>y，请交换 x,），k=2表示修改。

## 输出格式
对于每个查询指令输出一个整数表示答案。

每个答案占一行。

## 数据范围
N≤500000, M≤100000
,
−1000≤A[i]≤1000
## 输入样例：
5 3
1 2 -3 4 5
1 2 3
2 2 -1
1 3 2
## 输出样例 ：
2
-1

# 思路
***这里我们看到，就很难不想到用线段树去算一下。
***用线段树的一个关键在于怎么转移数据，我们要求连续区间内的最大长度，我们就可以算出每一个区间内的最大前缀，最大后缀，总长度，区间内的最大长度。那么区间内的最大长度就等于 max（子区间内的最大长度，左区间的最大后缀+右区间的最大前缀）
区间内的最大前缀=（第一个的最大前缀，左区间和加上右最大前缀）
区间内的最大后缀=（第二个的最大后缀，有区间加上左的最大后缀）

# AC 代码
```cpp

#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 500010;

int n, m;
int w[N];
struct Node
{
    int l, r;
    int sum, lmax, rmax, tmax;
}tr[N * 4];

void pushup(Node &u, Node &l, Node &r)
{
    u.sum = l.sum + r.sum;
    u.lmax = max(l.lmax, l.sum + r.lmax);
    u.rmax = max(r.rmax, r.sum + l.rmax);
    u.tmax = max(max(l.tmax, r.tmax), l.rmax + r.lmax);
}

void pushup(int u)
{
    pushup(tr[u], tr[u << 1], tr[u << 1 | 1]);
}

void build(int u, int l, int r)
{
    if (l == r) tr[u] = {l, r, w[r], w[r], w[r], w[r]};
    else
    {
        tr[u] = {l, r};
        int mid = l + r >> 1;
        build(u << 1, l, mid), build(u << 1 | 1, mid + 1, r);
        pushup(u);
    }
}

void modify(int u, int x, int v)
{
    if (tr[u].l == x && tr[u].r == x) tr[u] = {x, x, v, v, v, v};
    else
    {
        int mid = tr[u].l + tr[u].r >> 1;
        if (x <= mid) modify(u << 1, x, v);
        else modify(u << 1 | 1, x, v);
        pushup(u);
    }
}

Node query(int u, int l, int r)
{
    if (tr[u].l >= l && tr[u].r <= r) return tr[u];
    else
    {
        int mid = tr[u].l + tr[u].r >> 1;
        if (r <= mid) return query(u << 1, l, r);
        else if (l > mid) return query(u << 1 | 1, l, r);
        else
        {
            auto left = query(u << 1, l, r);
            auto right = query(u << 1 | 1, l, r);
            Node res;
            pushup(res, left, right);
            return res;
        }
    }
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i ++ ) scanf("%d", &w[i]);
    build(1, 1, n);

    int k, x, y;
    while (m -- )
    {
        scanf("%d%d%d", &k, &x, &y);
        if (k == 1)
        {
            if (x > y) swap(x, y);
            printf("%d\n", query(1, x, y).tmax);
        }
        else modify(1, x, y);
    }

    return 0;
}

作者：yxc
链接：https://www.acwing.com/activity/content/code/content/167568/
来源：AcWing
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
```
# 备注
