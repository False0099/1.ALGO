# 知识点
  ## [[线段树]]
# 题目
给定一个正整数数列 a 1, a 2,…, an，每一个数都在 0∼p−1 之间。

可以对这列数进行两种操作：

添加操作：向序列后添加一个数，序列长度变成 n+1
；
询问操作：询问这个序列中最后 L个数中最大的数是多少。
程序运行的最开始，整数序列为空。

一共要对整数序列进行 m 次操作。

写一个程序，读入操作的序列，并输出询问操作的答案。

## 输入格式
第一行有两个正整数 m, p，意义如题目描述；

接下来 m行，每一行表示一个操作。

如果该行的内容是 Q L，则表示这个操作是询问序列中最后 L个数的最大数是多少；

如果是 A t，则表示向序列后面加一个数，加入的数是 (t+a) mod p。其中，t是输入的参数，a是在这个添加操作之前最后一个询问操作的答案（如果之前没有询问操作，则 a=0）。

第一个操作一定是添加操作。对于询问操作，L>0 且不超过当前序列的长度。

## 输出格式
对于每一个询问操作，输出一行。该行只有一个数，即序列中最后 L个数的最大数。

## 数据范围
$1≤m≤2×10^5$

$1≤p≤2×10^9$
,
$0≤t<p$
	
## 输入样例：
10 100
A 97
Q 1
Q 1
A 17
Q 2
A 63
Q 1
Q 1
Q 3
A 99
## 输出样例 ：
97
97
97
60
60
97
## 样例解释
最后的序列是 97,14,60,96
。

# 思路
***这一题就是典型的又要求修改区间，又要求修改后的结构。那我们就可以用线段树去解决这个问题。而当中的数据转移又是一个重要的点，这里的数据转移操作也是很简单的，母区间的最大值显然就是子区间的最大值相加。

# AC 代码
```cpp
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long LL;

const int N = 200010;

int m, p;
struct Node
{
    int l, r;
    int v;  // 区间[l, r]中的最大值
}tr[N * 4];

void pushup(int u)  // 由子节点的信息，来计算父节点的信息
{
    tr[u].v = max(tr[u << 1].v, tr[u << 1 | 1].v);
}

void build(int u, int l, int r)//构建线段树的长度关系
{
    tr[u] = {l, r};
    if (l == r) return;
    int mid = l + r >> 1;
    build(u << 1, l, mid), build(u << 1 | 1, mid + 1, r);
}

int query(int u, int l, int r)//查询以u为根节点l到r区间上的和
{
    if (tr[u].l >= l && tr[u].r <= r) return tr[u].v;   // 树中节点，已经被完全包含在[l, r]中了

    int mid = tr[u].l + tr[u].r >> 1;
    int v = 0;
    if (l <= mid) v = query(u << 1, l, r);
    if (r > mid) v = max(v, query(u << 1 | 1, l, r));

    return v;
}

void modify(int u, int x, int v)
{
    if (tr[u].l == x && tr[u].r == x) tr[u].v = v;
    else
    {
        int mid = tr[u].l + tr[u].r >> 1;
        if (x <= mid) modify(u << 1, x, v);
        else modify(u << 1 | 1, x, v);
        pushup(u);
    }
}


int main()
{
    int n = 0, last = 0;
    scanf("%d%d", &m, &p);
    build(1, 1, m);

    int x;
    char op[2];
    while (m -- )
    {
        scanf("%s%d", op, &x);
        if (*op == 'Q')
        {
            last = query(1, n - x + 1, n);
            printf("%d\n", last);
        }
        else
        {
            modify(1, n + 1, ((LL)last + x) % p);
            n ++ ;
        }
    }

    return 0;
}


```
# 备注
