# 知识点
  ## [[有向图的强连通分量求法]]
# 题目
 一个有向图 G=(V, E) 称为半连通的 (Semi-Connected)，如果满足：∀u, v∈V，满足 u→v 或 v→u，即对于图中任意两点 u, v，存在一条 u 到 v 的有向路径或者从 v到 u 的有向路径。

若 G′=(V′, E′)满足，E′是 E中所有和 V′有关的边，则称 G′是 G的一个导出子图。

若 G′是 G的导出子图，且 G′半连通，则称 G′为 G的半连通子图。

若 G′是 G所有半连通子图中包含节点数最多的，则称 G′是 G的最大半连通子图。

给定一个有向图 G，请求出 G的最大半连通子图拥有的节点数 K，以及不同的最大半连通子图的数目 C
。

由于 C可能比较大，仅要求输出 C对 X的余数。

# 输入格式
第一行包含三个整数 N, M, X
。N, M分别表示图 G的点数与边数，X的意义如上文所述；
接下来 M行，每行两个正整数 a, b，表示一条有向边 (a, b)。

图中的每个点将编号为 1到 N，保证输入中同一个 (a, b)不会出现两次。

# 输出格式
应包含两行。第一行包含一个整数 K，第二行包含整数 C mod X。

# 数据范围
$1≤N≤10^5$
$1≤M≤10^6$
$1≤X≤10^8$
# 输入样例 ：
6 6 20070603
1 2
2 1
1 3
2 4
5 6
6 4
# 输出样例 ：
3
3

# 思路
·首先我们可以证明，任意一个强连通分量一定是半联通子图的一个部分，这样我们就可以先做一遍强连通分量，之后再去算出强连通分量构成的图的一个最大链，这个链就是我们最后要求的结果。
·
·
# AC 代码
```cpp
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <unordered_set>

using namespace std;

typedef long long LL;

const int N = 100010, M = 2000010;

int n, m, mod;
int h[N], hs[N], e[M], ne[M], idx;
int dfn[N], low[N], timestamp;
int stk[N], top;
bool in_stk[N];
int id[N], scc_cnt, scc_size[N];
int f[N], g[N];

void add(int h[], int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++ ;
}

void tarjan(int u)
{
    dfn[u] = low[u] = ++ timestamp;
    stk[ ++ top] = u, in_stk[u] = true;

    for (int i = h[u]; ~i; i = ne[i])
    {
        int j = e[i];
        if (!dfn[j])
        {
            tarjan(j);
            low[u] = min(low[u], low[j]);
        }
        else if (in_stk[j]) low[u] = min(low[u], dfn[j]);
    }

    if (dfn[u] == low[u])
    {
        ++ scc_cnt;
        int y;
        do {
            y = stk[top -- ];
            in_stk[y] = false;
            id[y] = scc_cnt;
            scc_size[scc_cnt] ++ ;
        } while (y != u);
    }
}

int main()
{
    memset(h, -1, sizeof h);
    memset(hs, -1, sizeof hs);

    scanf("%d%d%d", &n, &m, &mod);
    while (m -- )
    {
        int a, b;
        scanf("%d%d", &a, &b);
        add(h, a, b);
    }

    for (int i = 1; i <= n; i ++ )
        if (!dfn[i])
            tarjan(i);

    unordered_set<LL> S;    // (u, v) -> u * 1000000 + v
    for (int i = 1; i <= n; i ++ )
        for (int j = h[i]; ~j; j = ne[j])
        {
            int k = e[j];
            int a = id[i], b = id[k];
            LL hash = a * 1000000ll + b;
            if (a != b && !S.count(hash))
            {
                add(hs, a, b);
                S.insert(hash);
            }
        }

    for (int i = scc_cnt; i; i -- )
    {
        if (!f[i])
        {
            f[i] = scc_size[i];
            g[i] = 1;
        }
        for (int j = hs[i]; ~j; j = ne[j])
        {
            int k = e[j];
            if (f[k] < f[i] + scc_size[k])
            {
                f[k] = f[i] + scc_size[k];
                g[k] = g[i];
            }
            else if (f[k] == f[i] + scc_size[k])
                g[k] = (g[k] + g[i]) % mod;
        }
    }

    int maxf = 0, sum = 0;
    for (int i = 1; i <= scc_cnt; i ++ )
        if (f[i] > maxf)
        {
            maxf = f[i];
            sum = g[i];
        }
        else if (f[i] == maxf) sum = (sum + g[i]) % mod;

    printf("%d\n", maxf);
    printf("%d\n", sum);

    return 0;
}

作者：yxc
链接：https://www.acwing.com/activity/content/code/content/155884/
来源：AcWing
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
```
# 备注
