# 知识点
  ## [[线段树]]
# 题目
 给定一个长度为 N的数列 A，以及 M条指令，每条指令可能是以下两种之一：

C l r d，表示把 A[l], A[l+1],…, A[r]都加上 d
。
Q l r，表示询问 A[l], A[l+1],…, A[r]的最大公约数 (GCD)。
对于每个询问，输出一个整数表示答案。

## 输入格式
第一行两个整数 N, M。

第二行 N个整数 A[i]。

接下来 M行表示 M条指令，每条指令的格式如题目描述所示。

## 输出格式
对于每个询问，输出一个整数表示答案。

每个答案占一行。

## 数据范围
N≤500000, M≤100000

1≤A[i]≤1018

|d|≤1018

保证数据在计算过程中不会超过 long long 范围。

## 输入样例：
5 5
1 3 5 7 9
Q 1 5
C 1 5 1
Q 1 5
C 3 3 6
Q 2 4
## 输出样例：
1
2
4

# 思路
***我们这把也是同样的要去维护一个数组，同时还要多次查询，那么我们还是考虑一下线段树

***最大公约数有一个美妙的性质（gcd (a, b, c）=gcd (gcd (a, b), c); 因此因此我们也可以借此来维护我们的结构。

# AC 代码
```cpp
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long LL;

const int N = 500010;

int n, m;
LL w[N];
struct Node
{
    int l, r;
    LL sum, d;
}tr[N * 4];

LL gcd(LL a, LL b)
{
    return b ? gcd(b, a % b) : a;
}

void pushup(Node &u, Node &l, Node &r)
{
    u.sum = l.sum + r.sum;
    u.d = gcd(l.d, r.d);
}

void pushup(int u)
{
    pushup(tr[u], tr[u << 1], tr[u << 1 | 1]);
}

void build(int u, int l, int r)
{
    if (l == r)
    {
        LL b = w[r] - w[r - 1];
        tr[u] = {l, r, b, b};
    }
    else
    {
        tr[u].l = l, tr[u].r = r;
        int mid = l + r >> 1;
        build(u << 1, l, mid), build(u << 1 | 1, mid + 1, r);
        pushup(u);
    }
}

void modify(int u, int x, LL v)
{
    if (tr[u].l == x && tr[u].r == x)
    {
        LL b = tr[u].sum + v;
        tr[u] = {x, x, b, b};
    }
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
    for (int i = 1; i <= n; i ++ ) scanf("%lld", &w[i]);
    build(1, 1, n);

    int l, r;
    LL d;
    char op[2];
    while (m -- )
    {
        scanf("%s%d%d", op, &l, &r);
        if (*op == 'Q')
        {
            auto left = query(1, 1, l);
            Node right({0, 0, 0, 0});
            if (l + 1 <= r) right = query(1, l + 1, r);
            printf("%lld\n", abs(gcd(left.sum, right.d)));
        }
        else
        {
            scanf("%lld", &d);
            modify(1, l, d);
            if (r + 1 <= n) modify(1, r + 1, -d);
        }
    }

    return 0;
}
```
# 备注
