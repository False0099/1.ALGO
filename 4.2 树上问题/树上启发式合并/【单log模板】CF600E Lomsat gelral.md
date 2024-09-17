# Lomsat gelral

## 题面翻译

- 有一棵  $n$ 个结点的以  $1$ 号结点为根的**有根树**。
- 每个结点都有一个颜色，颜色是以编号表示的， $i$ 号结点的颜色编号为  $c_i$。
- 如果一种颜色在以  $x$ 为根的子树内出现次数最多，称其在以  $x$ 为根的子树中占**主导地位**。显然，同一子树中可能有多种颜色占主导地位。
- 你的任务是对于每一个  $i\in[1,n]$，求出以  $i$ 为根的子树中，占主导地位的颜色的编号和。
-  $n\le 10^5,c_i\le n$

## 题目描述

You are given a rooted tree with root in vertex $ 1 $ . Each vertex is coloured in some colour.

Let's call colour $ c $ dominating in the subtree of vertex $ v $ if there are no other colours that appear in the subtree of vertex $ v $ more times than colour $ c $ . So it's possible that two or more colours will be dominating in the subtree of some vertex.

The subtree of vertex $ v $ is the vertex $ v $ and all other vertices that contains vertex $ v $ in each path to the root.

For each vertex $ v $ find the sum of all dominating colours in the subtree of vertex $ v $ .

## 输入格式

The first line contains integer $ n $ ( $ 1<=n<=10^{5} $ ) — the number of vertices in the tree.

The second line contains $ n $ integers $ c_{i} $ ( $ 1<=c_{i}<=n $ ), $ c_{i} $ — the colour of the $ i $ -th vertex.

Each of the next $ n-1 $ lines contains two integers $ x_{j}, y_{j} $ ( $ 1<=x_{j}, y_{j}<=n $ ) — the edge of the tree. The first vertex is the root of the tree.

## 输出格式

Print $ n $ integers — the sums of dominating colours for each vertex.

## 样例 #1

### 样例输入 #1

```
4
1 2 3 4
1 2
2 3
2 4
```

### 样例输出 #1

```
10 9 3 4
```

## 样例 #2

### 样例输入 #2

```
15
1 2 3 1 2 3 3 1 1 3 2 2 1 2 3
1 2
1 3
1 4
1 14
1 15
2 5
2 6
2 7
3 8
3 9
3 10
4 11
4 12
4 13
```

### 样例输出 #2

```
6 5 4 3 2 3 3 1 1 3 2 2 1 2 3
```

## 题解
我们本题是启发式合并的模板，我们本题的思想通过 map 暴力维护我们区间的最大值是什么已经不必赘述。
```cpp
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;
#define int long long
const int N = 1e5 + 10, M = 2 * N, INF = 1e9;
int n, m
int a[N];//a表示我们的每个点对应的颜色
int h[N], e[M], ne[M], idx;
int son[N], l[N], r[N], rw[N], sz[N], ts;、//l指起始，r指起始+结束-1，rw指我们dfs序对应的点号
int cnt[N], sum, maxv;//cnt作用类似于map
int ans[N];//每一个询问的答案

void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

void update(int u, int v)
{
    cnt[a[u]] += v;
    if(cnt[a[u]] > maxv) maxv = cnt[a[u]], sum = a[u];
    else if(cnt[a[u]] == maxv) sum += a[u];
}

void dfs1(int u, int fa)
{
    sz[u] = 1, l[u] = ++ ts, rw[ts] = u;
    for(int i = h[u]; ~i ; i = ne[i])
    {
        int j = e[i];
        if(j == fa) continue;
        dfs1(j, u);
        sz[u] += sz[j];
        if(sz[j] > sz[son[u]]) son[u] = j;
    }
    r[u] = ts;
}

void dfs2(int u, int fa, int del)
{
    for(int i = h[u]; ~i ; i = ne[i])
    {
        int j = e[i];
        if(j == son[u] || j == fa) continue;
        dfs2(j, u, 1);
    }

    if(son[u]) dfs2(son[u], u, 0);

    for(int i = h[u]; ~i ; i = ne[i])
    {
        int j = e[i];
        if(j == son[u] || j == fa) continue;
        for(int k = l[j] ; k <= r[j] ; k ++ )//更新子树区间内的所有信息
            update(rw[k], 1); // 子树合并
    }
    update(u, 1);
    ans[u] = sum;

    if(del)
    {
        for(int k = l[u]; k <= r[u] ; k ++ ) 
            update(rw[k], -1);
        maxv = sum = 0;
    }
}

signed main()
{
    ios::sync_with_stdio(0), cin.tie(0);
    cin >> n;
    memset(h, -1, sizeof h);
    for(int i = 1; i <= n ; i ++ ) cin >> a[i];
    for(int i = 1 ; i < n ; i ++ )
    {
        int a, b;
        cin >> a >> b;
        add(a, b), add(b, a);
    }

    dfs1(1, 0);
    dfs2(1, 0, 1);
    for(int i = 1; i <= n ; i ++ ) cout << ans[i] << " ";
    cout << endl;
}
```