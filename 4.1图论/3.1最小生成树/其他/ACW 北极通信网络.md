# 知识点
  ## [[树的构建]] [[长期项目/算法/算法知识点/图论/最小生成树]] [[二分、三分]] [[求最值]]
# 题目
 北极的某区域共有 n座村庄，每座村庄的坐标用一对整数 (x, y)表示。为了加强联系，决定在村庄之间建立通讯网络，使每两座村庄之间都可以直接或间接通讯。通讯工具可以是无线电收发机，也可以是卫星设备。无线电收发机有多种不同型号，不同型号的无线电收发机有一个不同的参数 d，两座村庄之间的距离如果不超过 d，就可以用该型号的无线电收发机直接通讯，d值越大的型号价格越贵。现在要先选择某一种型号的无线电收发机，然后统一给所有村庄配备，数量不限，但型号都是相同的。配备卫星设备的两座村庄无论相距多远都可以直接通讯，但卫星设备是有限的，只能给一部分村庄配备。

现在有 k台卫星设备，请你编一个程序，计算出应该如何分配这 k台卫星设备，才能使所配备的无线电收发机的 d值最小。

# 思路
·我们首先考虑建图的方法，我们先通过输入的点来处理点与点之间的距离依此来建立所有的点之间的边。
·原来的问题可以转换为求一个最小的边 d 使得由小于这个 d 的所有的边的构成的连通块的个数小于 k。如果对应的点对（d, k）是易求的，那么我们就可以用二分的想法去算
·但因为这题我们可以用 kruskal 算法，这样我们就可以避开使用二分。因为每一次 kruskal 算法意味着我们在更新了 k 条按顺序排列的边后我们所能得到的最小的连通块个数。这个可以通过查询更新后的并查集来获得
# AC 代码
```cpp
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cmath>

#define x first
#define y second

using namespace std;

typedef pair<int, int> PII;

const int N = 510, M = N * N / 2;

int n, k, m;
struct Edge
{
    int a, b;
    double w;
    bool operator< (const Edge &t) const
    {
        return w < t.w;
    }
}e[M];
PII q[M];
int p[N];

double get_dist(PII a, PII b)
{
    int dx = a.x - b.x;
    int dy = a.y - b.y;
    return sqrt(dx * dx + dy * dy);
}

int find(int x)
{
    if (p[x] != x) p[x] = find(p[x]);
    return p[x];
}

int main()
{
    cin >> n >> k;
    for (int i = 0; i < n; i ++ ) cin >> q[i].x >> q[i].y;
    for (int i = 0; i < n; i ++ )
        for (int j = 0; j < i; j ++ )
            e[m ++ ] = {i, j, get_dist(q[i], q[j])};

    sort(e, e + m);
    for (int i = 0; i < n; i ++ ) p[i] = i;

    int cnt = n;
    double res = 0;
    for (int i = 0; i < m; i ++ )
    {
        if (cnt <= k) break;

        int a = find(e[i].a), b = find(e[i].b);
        double w = e[i].w;
        if (a != b)
        {
            p[a] = b;
            cnt -- ;
            res = w;
        }
    }

    printf("%.2lf\n", res);

    return 0;
}

```
# 备注
## 本题也存在用 dfs 求连通块后再用二分求解的方法，但相对的时间复杂度会更高一些。