# 知识点
  ## [[虚拟远点]] [[Dijstra算法]] [[求最值]]
# 题目
 有一天，琪琪想乘坐公交车去拜访她的一位朋友。由于琪琪非常容易晕车，所以她想尽快到达朋友家。现在给定你一张城市交通路线图，上面包含城市的公交站台以及公交线路的具体分布。已知城市中共包含 n 个车站（编号1~n）以及 m 条公交线路。每条公交线路都是 **单向的**，从一个车站出发直接到达另一个车站，两个车站之间可能存在多条公交线路。琪琪的朋友住在 s 号车站附近。琪琪可以在任何车站选择换乘其它公共汽车。请找出琪琪到达她的朋友家（附近的公交车站）需要花费的最少时间。

#### 输入格式

输入包含多组测试数据。

每组测试数据第一行包含三个整数 n,m,s，分别表示车站数量，公交线路数量以及朋友家附近车站的编号。

接下来 m行，每行包含三个整数 p,q,t，表示存在一条线路从车站 p到达车站 q，用时为 t。

接下来一行，包含一个整数 w，表示琪琪家附近共有 w 个车站，她可以在这 w 个车站中选择一个车站作为始发站。

再一行，包含 w 个整数，表示琪琪家附近的 w 个车站的编号。

#### 输出格式

每个测试数据输出一个整数作为结果，表示所需花费的最少时间。

如果无法达到朋友家的车站，则输出 -1。

每个结果占一行。

#### 数据范围

$n≤1000,m≤20000$  
$1≤s≤n$ 
$0<w<n0$   
$0<t≤1000$

#### 输入样例：

```
5 8 5
1 2 2
1 5 3
1 3 4
2 4 7
2 5 6
2 3 5
3 5 1
4 5 1
2
2 3
4 3 4
1 2 3
1 3 4
2 3 2
1
1
```

#### 输出样例：

```
1
-1
```

# 思路
·我们对于多个起点同一个中点，我们可以取巧的构造一个虚拟原点，这样就不用去在每一个原点上跑 dij 或 spfa 。直接省掉一个数量级的时间复杂度
·于是这个问题就变成了从虚拟原点到最后的终点的最短路问题
·
# AC 代码
```cpp
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 1010, M = 20010, INF = 0x3f3f3f3f;

int n, m, T;
int h[N], e[M], w[M], ne[M], idx;
int dist[N], q[N];
bool st[N];

void add(int a, int b, int c)
{
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++ ;
}

void spfa()
{
    int scnt;
    scanf("%d", &scnt);

    memset(dist, 0x3f, sizeof dist);

    int hh = 0, tt = 0;
    while (scnt -- )
    {
        int u;
        scanf("%d", &u);
        dist[u] = 0;
        q[tt ++ ] = u;
        st[u] = true;
    }

    while (hh != tt)
    {
        int t = q[hh ++ ];
        if (hh == N) hh = 0;

        st[t] = false;
        for (int i = h[t]; ~i; i = ne[i])
        {
            int j = e[i];
            if (dist[j] > dist[t] + w[i])
            {
                dist[j] = dist[t] + w[i];
                if (!st[j])
                {
                    q[tt ++ ] = j;
                    if (tt == N) tt = 0;
                    st[j] = true;
                }
            }
        }
    }
}

int main()
{
    while (scanf("%d%d%d", &n, &m, &T) != -1)
    {
        memset(h, -1, sizeof h);
        idx = 0;

        while (m -- )
        {
            int a, b, c;
            scanf("%d%d%d", &a, &b, &c);
            add(a, b, c);
        }

        spfa();

        if (dist[T] == INF) dist[T] = -1;
        printf("%d\n", dist[T]);
    }

    return 0;
}

作者：yxc
链接：https://www.acwing.com/activity/content/code/content/143197/
来源：AcWing
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
```
# 备注
