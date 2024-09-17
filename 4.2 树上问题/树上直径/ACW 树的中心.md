# 知识点
  ## [[动态规划]] [[树形DP]] [[DFS]] [[求最值]]
# 题目
 给定一棵树，树中包含 $n$ 个结点（编号 $1-n$ ）和 $n−1$ 条无向边，每条边都有一个权值。

请你在树中找到一个点，使得该点到树中其他结点的最远距离最近。

#### 输入格式

第一行包含整数 $n$。

接下来 $n−1$  行，每行包含三个整数 $a_{i},b_{i},c_{i}$ 表示点 $a_{i}$ 和 $b_{i}$ 之间存在一条权值为 $c_{i}$ 的边。

#### 输出格式

输出一个整数，表示所求点到树中其他结点的最远距离。

#### 数据范围

$1≤n≤10000$,  
$1≤ai,bi≤n$  
$1≤ci≤10^5$

#### 输入样例：

```
5 
2 1 1 
3 2 1 
4 3 1 
5 1 1
```

#### 输出样例：

```
2
```

# 思路
·朴素思路，就先求出每一个节点的最大距离，然后再去找里面的最短一个点就可以了。
·对于每一个点而言，我们可以根据方向来划分，第一个方向是向下走，第二个方向是向上走。向下走的路是可以直接通过 dfs 来首先求出，同时我们还要求出来一个向下走的第二大节点以防不备，并且存储这两个点的具体位置。向上走的路我们则需要在之前得到的向下走的路的的基础上再去加。
·向上走的路径我们可以通过我们之前求得的数组 d[1] 、d[2]来计算出来。
# AC 代码
```cpp
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 10010, M = N * 2, INF = 0x3f3f3f3f;

int n;
int h[N], e[M], w[M], ne[M], idx;
int d1[N], d2[N], p1[N], up[N];
bool is_leaf[N];

void add(int a, int b, int c)
{
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++ ;
}

int dfs_d(int u, int father)
{
    d1[u] = d2[u] = -INF;
    for (int i = h[u]; i != -1; i = ne[i])
    {
        int j = e[i];
        if (j == father) continue;
        int d = dfs_d(j, u) + w[i];
        if (d >= d1[u])
        {
            d2[u] = d1[u], d1[u] = d;
            p1[u] = j;
        }
        else if (d > d2[u]) d2[u] = d;
    }

    if (d1[u] == -INF)
    {
        d1[u] = d2[u] = 0;
        is_leaf[u] = true;
    }

    return d1[u];
}

void dfs_u(int u, int father)
{
    for (int i = h[u]; i != -1; i = ne[i])
    {
        int j = e[i];
        if (j == father) continue;

        if (p1[u] == j) up[j] = max(up[u], d2[u]) + w[i];
        else up[j] = max(up[u], d1[u]) + w[i];

        dfs_u(j, u);
    }
}

int main()
{
    cin >> n;
    memset(h, -1, sizeof h);
    for (int i = 0; i < n - 1; i ++ )
    {
        int a, b, c;
        cin >> a >> b >> c;
        add(a, b, c), add(b, a, c);
    }

    dfs_d(1, -1);
    dfs_u(1, -1);

    int res = d1[1];
    for (int i = 2; i <= n; i ++ )
        if (is_leaf[i]) res = min(res, up[i]);
        else res = min(res, max(d1[i], up[i]));

    printf("%d\n", res);

    return 0;
}
```
# 备注
