## 题目描述
TXT 又宅又爱 Miku，因此她的房间里全是只会吃大米的 FuFu ，被勒令速速整理。

TXT 的收纳箱有 N 格，以 0∼N−1为编号。

收纳箱的每个格子最多只能同时盛放一只 FuFu。

在她拥有若干只 FuFu 后，她会随机选择一个格子 A，从第 A 个格子开始逐个遍历接下来的每个格子A,A+1,A+2…N−1，当遍历到的格子中没有 FuFu 时，她会将手中的一个 FuFu 放进这个格子里，直到所有 FuFu 都放进收纳箱中或遍历完第 N−1 个格子为止，如果手中还有 FuFu 没有放入收纳箱，那么 TXT 只能忍痛丢弃这些只会吃大米的废物 FuFu 。

有时，TXT 也会随机选取一些连续的格子，将这些格子清空。

TXT进行了 M 个操作，这些操作分为以下两种：

- "1 A F" ，表示 TXT 新买了F 只 FuFu ，并打算从格子 A 开始，尝试将它们放入。
- "2 A B" ，表示 TXT 将第 A∼B 个格子清理干净，清空其中所有的 FuFu 。

请你分析 TXT 的操作，并回答问题。

## 输入格式
第一行包含整数 T (1≤T≤10) ，表示共有 T 组测试数据。

每组数据第一行包含两个整数 N,M (2≤N,M≤50000) 。

接下来 M 行，每行描述一个事件，其中 0≤A≤B≤N−1,1≤F≤10000 。


## 输出格式

每个事件输出一行答案。

对于事件 11，如果存在可以放入格子中的 FuFu，则输出在本次事件中第一个放入 FuFu 的格子编号和最后一个放入 FuFu 的格子编号。如果不存在可以放入格子中的 FuFu ，则输出 "Can not put any one." 。

对于事件 2，输出在本次事件中被清理的 FuFu 数量。

每组数据输出完毕后，输出一个空行。

## 样例 #1

### 样例输入 #1

```
2
10 5
1 3 5
2 4 5
1 1 8
2 3 6
1 8 8
10 6
1 2 5
2 3 4
1 0 8
2 2 5
1 4 4
1 2 3
```

### 样例输出 #1

```
3 7
2
1 9
4
Can not put any one.

2 6
2
0 9
4
4 5
2 3


```

## 题解
我们本题要**求出的时我们的某个区间内有的空花瓶的总数**

首先，我们列出我们可能需要的操作：
操作 1：查询我们的区间 $[l,n]$ 内的所有可能位置的和是多少。这一步我们可以通过我们的线段树维护我们的空位来实现

操作 2：查询我们的区间 $[l,n]$ 中所有可能的空位的位置有哪些。这一个操作相对来说比较麻烦，我们需要利用类似于我们的主席树求第 K 大的思路来求解我们在哪个位置需要安置我们的位置。

在这里，我们就可以通过我们的一个

## 代码
```cpp
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 50005;

struct Node
{
    int l, r;
    int sum, lazy;
}tr[N * 4];

int n, m;

void pushup(int u)
{
    tr[u].sum = tr[u << 1].sum + tr[u << 1 | 1].sum;
}

void pushdown(int u)
{
    auto& root = tr[u], &left = tr[u << 1], &right = tr[u << 1 | 1];
    if(root.lazy != -1)
    {
        left.lazy = right.lazy = root.lazy;
        left.sum = (left.r - left.l + 1) * root.lazy;
        right.sum = (right.r - right.l + 1) * root.lazy;
        root.lazy = -1;
    }
}

void build(int u, int l, int r)
{
    tr[u] = {l, r};
    tr[u].lazy = -1;
    if(l == r)
    {
        tr[u].sum = 1;
        return;
    }
    int mid = l + r >> 1;
    build(u << 1, l, mid), build(u << 1 | 1, mid + 1, r);
    pushup(u);
}

int query_sum(int u, int l, int r)
{
    if(l <= tr[u].l && r >= tr[u].r) return tr[u].sum;
    pushdown(u);
    int mid = tr[u].l + tr[u].r >> 1;
    int res = 0;
    if(l <= mid) res += query_sum(u << 1, l, r);
    if(r > mid) res += query_sum(u << 1 | 1, l, r);
    return res;
}

int query_pos(int u, int l, int r, int k, int cnt)
{
    if(tr[u].l == tr[u].r)
    {
        if(tr[u].sum == 0) return -1;
        if(tr[u].sum == 1) return tr[u].l;
    }
    pushdown(u);
    int mid = tr[u].l + tr[u].r >> 1;
    int left = 0, right = 0, ans = -1;
    if(l <= mid) left = query_sum(u << 1, l, mid);
    if(r > mid) right = query_sum(u << 1 | 1, mid + 1, r);
    //如果分配的个数大于左边的个数，优先去看右边区间够不够
    if(k > left) ans = query_pos(u << 1 | 1, l, r, k - left, cnt); 
    //否则看左边区间够不够
    else ans = query_pos(u << 1, l, r, k, cnt);

    if(ans == -1)
    {
        if(left == 0) return -1; //left = 0并且右边区间不够放，返回-1
        ans = query_pos(u << 1, l, r, k, cnt);//left != 0，右边没有空位了，看左边
    }
    return ans;
}

void modify(int u, int l, int r, int c)
{
    if(l <= tr[u].l && r >= tr[u].r)
    {
        tr[u].sum = (tr[u].r - tr[u].l + 1) * c;
        tr[u].lazy = c;
        return;
    }
    pushdown(u);
    int mid = tr[u].l + tr[u].r >> 1;
    if(l <= mid) modify(u << 1, l, r, c);
    if(r > mid) modify(u << 1 | 1, l, r, c);
    pushup(u);
}

void solve()
{
    scanf("%d%d", &n, &m);
    build(1, 0, n - 1);
    while(m -- )
    {
        int op, x, y;
        scanf("%d%d%d", &op, &x, &y);
        if(op == 1)
        {
            int e = query_pos(1, x, n - 1, y, y);//在区间中找y个花（第y个的位置）
            if(e == -1)
            {
                puts("Can not put any one.");
                continue;
            }
            int s = query_pos(1, x, n - 1, 1, 1);//在区间中找1个花(第一个位置)
            printf("%d %d\n", s, e);
            modify(1, s, e, 0);
        }
        else
        {
            printf("%d\n", y - x + 1 - query_sum(1, x, y));
            modify(1, x, y, 1);
        }
    }
    puts("");
}

int main()
{
    int t;
    scanf("%d", &t);
    while(t -- ) solve();
    return 0;
}
```