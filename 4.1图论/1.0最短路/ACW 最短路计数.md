# 知识点
  ## [[单源最短路问题]]
# 题目
 给出一个 N 个顶点 M 条边的无向无权图，顶点编号为 1 到 N。

问从顶点 1 开始，到其他每个点的最短路有几条。

## 输入格式
第一行包含 2 个正整数 N, M，为图的顶点数与边数。

接下来 M 行，每行两个正整数 x, y，表示有一条顶点 x 连向顶点 y 的边，请注意可能有自环与重边。

## 输出格式
输出 N 行，每行一个非负整数，第 i 行输出从顶点 1 到顶点 i 有多少条不同的最短路，由于答案有可能会很大，你只需要输出对 100003 取模后的结果即可。

如果无法到达顶点 i 则输出 0。

## 数据范围
1≤N≤105
,
1≤M≤2×105
## 输入样例 ：
5 7
1 2
1 3
2 4
3 4
2 3
4 5
4 5
## 输出样例 ：
1
1
1
2
4

# 思路
·我们发现，这里要求最短路计数，而众所周知，我们在动态规划中也有一类最短路计数问题，所以我们不妨设置一个 cnt 数组，来统计我们到每一个边的最短路的次数，每一次我们更新，我们现在的 cnt 的次数，就要加上这个点前面哪一个点的 cnt 的次数。
·
·
# AC 代码
```cpp
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 100010, M = 400010, mod = 100003;

int n, m;
int h[N], e[M], ne[M], idx;
int dist[N], cnt[N];
int q[N];

void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++ ;
}

void bfs()
{
    memset(dist, 0x3f, sizeof dist);
    dist[1] = 0;
    cnt[1] = 1;

    int hh = 0, tt = 0;
    q[0] = 1;

    while (hh <= tt)
    {
        int t = q[hh ++ ];

        for (int i = h[t]; ~i; i = ne[i])
        {
            int j = e[i];
            if (dist[j] > dist[t] + 1)
            {
                dist[j] = dist[t] + 1;
                cnt[j] = cnt[t];
                q[ ++ tt] = j;
            }
            else if (dist[j] == dist[t] + 1)
            {
                cnt[j] = (cnt[j] + cnt[t]) % mod;
            }
        }
    }
}

int main()
{
    scanf("%d%d", &n, &m);
    memset(h, -1, sizeof h);

    while (m -- )
    {
        int a, b;
        scanf("%d%d", &a, &b);
        add(a, b), add(b, a);
    }

    bfs();

    for (int i = 1; i <= n; i ++ ) printf("%d\n", cnt[i]);

    return 0;
}

作者：yxc
链接：https://www.acwing.com/activity/content/code/content/143195/
来源：AcWing
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
```
# 备注
