# 知识点
  ## [[Floyd算法]]
# 题目
 给定一张无向图，求图中一个至少包含 3 个点的环，环上的节点不重复，并且环上的边的长度之和最小。

该问题称为无向图的最小环问题。

你需要输出最小环的方案，若最小环不唯一，输出任意一个均可。

## 输入格式
第一行包含两个整数 N 和 M，表示无向图有 N 个点，M 条边。

接下来 M 行，每行包含三个整数 u，v，l，表示点 u 和点 v 之间有一条边，边长为 l。

## 输出格式
输出占一行，包含最小环的所有节点（按顺序输出），如果不存在则输出 No solution.。

## 数据范围
1≤N≤100
,
1≤M≤10000
,
1≤l<500
## 输入样例 ：
5 7
1 4 1
1 3 300
3 1 10
1 2 16
2 3 100
2 5 15
5 3 20
## 输出样例 ：
1 3 5 2

# 思路
·对于求环的问题，我们可以枚举三个点，一个是起始点，一个是中间点，一个是结尾点，我们必须要保证起始点和结尾点之间有边，中间点和结尾点之间有直接边。所以我们就可以直接通过枚举来计算
·注意：我们给出的方案，并不能完全遍历所有环，存在一些环是无法被遍历的，但这些无法遍历的环事实上也不可能是最小环。
·
# AC 代码
```cpp
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 110, INF = 0x3f3f3f3f;

int n, m;
int d[N][N], g[N][N];
int pos[N][N];
int path[N], cnt;

void get_path(int i, int j)
{
    if (pos[i][j] == 0) return;

    int k = pos[i][j];
    get_path(i, k);
    path[cnt ++ ] = k;
    get_path(k, j);
}

int main()
{
    cin >> n >> m;

    memset(g, 0x3f, sizeof g);
    for (int i = 1; i <= n; i ++ ) g[i][i] = 0;

    while (m -- )
    {
        int a, b, c;
        cin >> a >> b >> c;
        g[a][b] = g[b][a] = min(g[a][b], c);
    }

    int res = INF;
    memcpy(d, g, sizeof d);
    for (int k = 1; k <= n; k ++ )
    {
        for (int i = 1; i < k; i ++ )//因为k是最大点，所以我们保持
            for (int j = i + 1; j < k; j ++ )
                if ((long long)d[i][j] + g[j][k] + g[k][i] < res)
                {
                    res = d[i][j] + g[j][k] + g[k][i];//d[i][j]表示从i到j的最小距离，g[a][b]表示一条直接存在的边。
                    //而且我们一定能保证，d[i][j]与g[j][k],g[k][i]不是一条路
                    cnt = 0;
                    path[cnt ++ ] = k;
                    path[cnt ++ ] = i;
                    get_path(i, j);
                    path[cnt ++ ] = j;
                }
		//预处理floyd算法
        for (int i = 1; i <= n; i ++ )
            for (int j = 1; j <= n; j ++ )
                if (d[i][j] > d[i][k] + d[k][j])
                {
                    d[i][j] = d[i][k] + d[k][j];
                    pos[i][j] = k;
                }
    }

    if (res == INF) puts("No solution.");
    else
    {
        for (int i = 0; i < cnt; i ++ ) cout << path[i] << ' ';
        cout << endl;
    }

    return 0;
}
```
# 备注
