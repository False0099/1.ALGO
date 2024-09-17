# 知识点

# 题目
 有一个 m行 n列的点阵，相邻两点可以相连。一条纵向的连线花费一个单位，一条横向的连线花费两个单位。某些点之间已经有连线了，试问至少还需要花费多少个单位才能使所有的点全部连通。

# 输入格式
第一行输入两个正整数 m和 n。

以下若干行每行四个正整数 x 1, y 1, x 2, y 2，表示第 x 1行第 y 1列的点和第 x 2行第 y 2列的点已经有连线。
输入保证|x 1−x 2|+|y 1−y 2|=1。

# 输出格式
输出使得连通所有点还需要的最小花费。

# 数据范围
1≤m, n≤1000

0≤已经存在的连线数≤10000
# 输入样例：
2 2
1 1 2 1
输出样例：
3

# 思路
`对于这样的问题，我们首先可以想到先把已经确定的边给合并了，再对剩下的编曲进行一个最小树的生成，这么做对于正值边是显然可行的，但要注意，对于负值边就不一定了`
·之后我们就把原来的二维坐标给一维话，便于我们生成一个并查集。具体的一维话方法也就是按照点出现的顺序来作为他的一维映射结果
·这样的话我们就可以简单的从二维映射到一维，并依次来建边，实现最小生成树算法。
# AC 代码
```cpp
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 1010, M = N * N, K = 2 * N * N;

int n, m, k;
int ids[N][N];
struct Edge
{
    int a, b, w;
}e[K];
int p[M];

int find(int x)
{
    if (p[x] != x) p[x] = find(p[x]);
    return p[x];
}

void get_edges()
{
    int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, 1, 0, -1}, dw[4] = {1, 2, 1, 2};

    for (int z = 0; z < 2; z ++ )
        for (int i = 1; i <= n; i ++ )
            for (int j = 1; j <= m; j ++ )
                for (int u = 0; u < 4; u ++ )
                    if (u % 2 == z)
                    {
                        int x = i + dx[u], y = j + dy[u], w = dw[u];
                        if (x && x <= n && y && y <= m)
                        {
                            int a = ids[i][j], b = ids[x][y];
                            if (a < b) e[k ++ ] = {a, b, w};
                        }
                    }
}//将二维的坐标和距离映射到一维

int main()
{
    cin >> n >> m;

    for (int i = 1, t = 1; i <= n; i ++ )
        for (int j = 1; j <= m; j ++, t ++ )
            ids[i][j] = t;

    for (int i = 1; i <= n * m; i ++ ) p[i] = i;

    int x1, y1, x2, y2;
    while (cin >> x1 >> y1 >> x2 >> y2)
    {
        int a = ids[x1][y1], b = ids[x2][y2];
        p[find(a)] = find(b);
    }

    get_edges();

    int res = 0;
    for (int i = 0; i < k; i ++ )
    {
        int a = find(e[i].a), b = find(e[i].b), w = e[i].w;
        if (a != b)
        {
            p[a] = b;
            res += w;
        }
    }

    cout << res << endl;

    return 0;
}

作者：yxc
链接：https://www.acwing.com/activity/content/code/content/148150/
来源：AcWing
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
```
# 备注
