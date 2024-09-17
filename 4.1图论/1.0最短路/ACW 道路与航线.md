# 知识点
  ## [[求最值]] [[图论]] [[Dijstra算法]] [[缩点]]
# 题目
 农夫约翰正在一个新的销售区域对他的牛奶销售方案进行调查。

他想把牛奶送到 T 个城镇，编号为 1∼T。这些城镇之间通过 R条道路 (编号为 1到 R) 和 P条航线 (编号为 1到 P) 连接。

每条道路 i或者航线 i连接城镇 Ai到 Bi，花费为 Ci。

对于道路，0≤Ci≤10,000;然而航线的花费很神奇，花费 Ci可能是负数 (−10,000≤Ci≤10,000)。

道路是双向的，可以从 Ai 到 Bi，也可以从 Bi 到 Ai，花费都是 Ci。

然而航线与之不同，只可以从 Ai到 Bi。

事实上，由于最近恐怖主义太嚣张，为了社会和谐，出台了一些政策：保证如果有一条航线可以从 Ai到 Bi，那么保证不可能通过一些道路和航线从 Bi回到 Ai。

由于约翰的奶牛世界公认十分给力，他需要运送奶牛到每一个城镇。

他想找到从发送中心城镇 S把奶牛送到每个城镇的最便宜的方案。

# 输入格式
第一行包含四个整数 T, R, P, S。

接下来 R行，每行包含三个整数（表示一个道路）Ai, Bi, Ci。

接下来 P行，每行包含三个整数（表示一条航线）Ai, Bi, Ci。

# 输出格式
第 1.. T行：第 i行输出从 S到达城镇 i的最小花费，如果不存在，则输出 NO PATH。

# 数据范围
1≤T≤25000

1≤R, P≤50000

1≤Ai, Bi, S≤T
# 输入样例 ：
6 3 3 4
1 2 5
3 4 5
5 6 10
3 5 -100
4 6 -100
1 3 -10
# 输出样例 ：
NO PATH
NO PATH
5
0
-95
-100

# 思路
·我们先打一个比方，我们把一个联通的大块看作是一个城市，城市内部分散着若干的道路。
·我们想要找到从 a-b 的最短路，我们可以首先判断 a 和 b 是不是在同一个城市里。如果是的话，我们就不用进行下一步的拓扑排序。如果不是，我们就要先找到跨城市的方法，然后再找到从一个城市到一个交通站的道路。
·我们上述的所有思想，实际上不过是优化了我们进行 dij 算法时的入堆顺序，先放入自己的连通块，再放入更新后入度为 0 的连通块。
·具体到实现上，我们就先算出所有连通块，同时储存连通块内的所有点，连通块的序号，每个连通块的出度。之后再将连通块进行拓扑排序。按照排序顺序依次将连通块内的所有点放入排序堆中。
·在进行 dij 时，如果发现一个连通块内的入度已经被我们更新为 0 了，那我们就直接把连通块放入待处理的队列中，回头再把这个连通块里的所有东西泵进去

# AC 代码
```cpp
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

#define x first
#define y second

using namespace std;

typedef pair<int, int> PII;

const int N = 25010, M = 150010, INF = 0x3f3f3f3f;

int n, mr, mp, S;
int id[N];
int h[N], e[M], w[M], ne[M], idx;
int dist[N], din[N];
vector<int> block[N];
int bcnt;
bool st[N];
queue<int> q;

void add(int a, int b, int c)
{
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++ ;
}

void dfs(int u, int bid)
{
    id[u] = bid, block[bid].push_back(u);

    for (int i = h[u]; ~i; i = ne[i])
    {
        int j = e[i];
        if (!id[j])
            dfs(j, bid);
    }
}

void dijkstra(int bid)
{
    priority_queue<PII, vector<PII>, greater<PII>> heap;

    for (auto u : block[bid])
        heap.push({dist[u], u});

    while (heap.size())
    {
        auto t = heap.top();
        heap.pop();

        int ver = t.y, distance = t.x;
        if (st[ver]) continue;
        st[ver] = true;

        for (int i = h[ver]; ~i; i = ne[i])
        {
            int j = e[i];
            if (id[j] != id[ver] && -- din[id[j]] == 0) q.push(id[j]);
            if (dist[j] > dist[ver] + w[i])//一定要更新距离，你哪怕这个点在连通块外
            {
                dist[j] = dist[ver] + w[i];
                if (id[j] == id[ver]) heap.push({dist[j], j});
            }
        }
    }
}

void topsort()
{
    memset(dist, 0x3f, sizeof dist);
    dist[S] = 0;

    for (int i = 1; i <= bcnt; i ++ )
        if (!din[i])
            q.push(i);

    while (q.size())
    {
        int t = q.front();
        q.pop();
        dijkstra(t);//在这个连通块内dij
    }
}

int main()
{
    cin >> n >> mr >> mp >> S;
    memset(h, -1, sizeof h);

    while (mr -- )
    {
        int a, b, c;
        cin >> a >> b >> c;
        add(a, b, c), add(b, a, c);
    }

    for (int i = 1; i <= n; i ++ )
        if (!id[i])
        {
            bcnt ++ ;
            dfs(i, bcnt);//先缩点。
        }

    while (mp -- )
    {
        int a, b, c;
        cin >> a >> b >> c;
        din[id[b]] ++ ;
        add(a, b, c);
    }

    topsort();

    for (int i = 1; i <= n; i ++ )
        if (dist[i] > INF / 2) cout << "NO PATH" << endl;
        else cout << dist[i] << endl;

    return 0;
}

作者：yxc
链接：https://www.acwing.com/activity/content/code/content/141218/
来源：AcWing
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
```
# 备注
