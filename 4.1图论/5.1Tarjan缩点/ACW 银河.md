# 知识点
  ## [[有向图的强连通分量求法]] [[Tarjan算法]] [[差分约束]]
# 题目
 银河中的恒星浩如烟海，但是我们只关注那些最亮的恒星。我们用一个正整数来表示恒星的亮度，数值越大则恒星就越亮，恒星的亮度最暗是 1
。

现在对于 N 颗我们关注的恒星，有 M对亮度之间的相对关系已经判明。

你的任务就是求出这 N颗恒星的亮度值总和至少有多大。

# 输入格式
第一行给出两个整数 N和 M。

之后 M行，每行三个整数 T, A, B，表示一对恒星 (A, B)之间的亮度关系。恒星的编号从 1开始。

如果 T=1，说明 A和 B亮度相等。
如果 T=2，说明 A的亮度小于 B的亮度。
如果 T=3，说明 A的亮度不小于 B的亮度。
如果 T=4，说明 A 的亮度大于 B 的亮度。
如果 T=5，说明 A的亮度不大于 B的亮度。

# 输出格式
输出一个整数表示结果。

若无解，则输出 −1
。

# 数据范围
N≤100000, M≤100000
# 输入样例 ：
5 7 
1 1 2 
2 3 2 
4 4 1 
3 4 5 
5 4 5 
2 3 5 
4 5 1 
# 输出样例 ：
11

# 思路
·我们不难发现，如果只看题目的话，我们很容易觉得这就是一个差分约束的问题，事实上也是这样，但为什么我们会打上一个 tarjan 算法的标签，原因在于我们可以用强连通量去更快的求正环。
·总而言之，1 tarjan·2 缩点+建图·3 topo 序 dp 最长路
# AC 代码
```cpp
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long LL;

const int N = 100010, M = 600010;

int n, m;
int h[N], hs[N], e[M], ne[M], w[M], idx;
int dfn[N], low[N], timestamp;
int stk[N], top;
bool in_stk[N];
int id[N], scc_cnt, sz[N];
int dist[N];

void add(int h[], int a, int b, int c)
{
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++ ;
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
            sz[scc_cnt] ++ ;
        } while (y != u);
    }
}

int main()
{
    scanf("%d%d", &n, &m);
    memset(h, -1, sizeof h);
    memset(hs, -1, sizeof hs);

    for (int i = 1; i <= n; i ++ ) add(h, 0, i, 1);

    while (m -- )
    {
        int t, a, b;
        scanf("%d%d%d", &t, &a, &b);
        if (t == 1) add(h, b, a, 0), add(h, a, b, 0);
        else if (t == 2) add(h, a, b, 1);
        else if (t == 3) add(h, b, a, 0);
        else if (t == 4) add(h, b, a, 1);
        else add(h, a, b, 0);
    }

    tarjan(0);

    bool success = true;
    for (int i = 0; i <= n; i ++ )
    {
        for (int j = h[i]; ~j; j = ne[j])
        {
            int k = e[j];
            int a = id[i], b = id[k];
            if (a == b)
            {
                if (w[j] > 0)
                {
                    success = false;
                    break;
                }
            }
            else add(hs, a, b, w[j]);
        }
        if (!success) break;
    }

    if (!success) puts("-1");
    else
    {
        for (int i = scc_cnt; i; i -- )
        {
            for (int j = hs[i]; ~j; j = ne[j])
            {
                int k = e[j];
                dist[k] = max(dist[k], dist[i] + w[j]);
            }
        }

        LL res = 0;
        for (int i = 1; i <= scc_cnt; i ++ ) res += (LL)dist[i] * sz[i];

        printf("%lld\n", res);
    }

    return 0;
}

作者：yxc
链接：https://www.acwing.com/activity/content/code/content/155909/
来源：AcWing
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
```
# 备注
