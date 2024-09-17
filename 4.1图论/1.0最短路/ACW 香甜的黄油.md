# 知识点
  ## [[]]
# 题目
 农夫 John 发现了做出全威斯康辛州最甜的黄油的方法：糖。

把糖放在一片牧场上，他知道 N 只奶牛会过来舔它，这样就能做出能卖好价钱的超甜黄油。

当然，他将付出额外的费用在奶牛上。

农夫 John 很狡猾，就像以前的巴甫洛夫，他知道他可以训练这些奶牛，让它们在听到铃声时去一个特定的牧场。

他打算将糖放在那里然后下午发出铃声，以至他可以在晚上挤奶。

农夫 John 知道每只奶牛都在各自喜欢的牧场（一个牧场不一定只有一头牛）。

给出各头牛在的牧场和牧场间的路线，找出使所有牛到达的路程和最短的牧场（他将把糖放在那）。

数据保证至少存在一个牧场和所有牛所在的牧场连通。

输入格式
第一行: 三个数：奶牛数 N，牧场数 P，牧场间道路数 C。

第二行到第 N+1 行: 1 到 N 头奶牛所在的牧场号。

第 N+2 行到第 N+C+1 行：每行有三个数：相连的牧场 A、B，两牧场间距 D，当然，连接是双向的。

输出格式
共一行，输出奶牛必须行走的最小的距离和。

## 数据范围
1≤N≤500
,
2≤P≤800
,
1≤C≤1450
,
1≤D≤255
## 输入样例 ：
3 4 5
2
3
4
1 2 1
1 3 5
2 3 7
2 4 3
3 4 5
## 输出样例 ：
8

# 思路
·我们不难发现，如果我们想要求目标的那个农场，我们就只需要找到一个点，使得这一个点到所有其他点的距离和最小。我们于是可以求出所有点到其他点的单源最短路后，再统计出距离和。最后比较每个点的距离和大小后就能得到答案了。
·
·
# AC 代码
```cpp
#include<iostream>
#include<cstring>
#include<vector>
#include<queue>

#define x first
#define y second

using namespace std;

typedef pair<int, int> PII;

const int N = 3000;

int n, p, m;
int h[N], e[N], ne[N], w[N], idx;
int dist[N], cnt[N];
bool st[N];
int res = 0x3f3f3f3f;

void add(int a, int b, int c)
{
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
}

void dijikstra(int op)
{
    memset(dist, 0x3f, sizeof dist);
    memset(st, 0, sizeof st);
    dist[op] = 0;

    priority_queue<PII, vector<PII>, greater<PII>> heap;
    heap.push({ 0,op });

    while (heap.size())
    {
        auto t = heap.top();
        heap.pop();

        int ver = t.y;
        if (st[ver]) continue;
        st[ver] = true;

        for (int i = h[ver]; ~i; i = ne[i])
        {
            int j = e[i];
            if (dist[j] > dist[ver] + w[i])
            {
                dist[j] = dist[ver] + w[i];
                heap.push({ dist[j],j });
            }
        }
    }

    int sum = 0;
    for (int i = 1; i <= p; i++)
        if (cnt[i]&& dist[i] > 0x3f3f3f3f / 2) return;
        else sum += cnt[i] * dist[i];

    res = min(res, sum);
}

int main()
{
    cin >> n >> p >> m;
    for (int i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        cnt[x]++;
    }

    memset(h,-1,sizeof h);
    for (int i = 0; i < m; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;
        add(a, b, c), add(b, a, c);
    }

    for (int i = 1; i <= p; i++)
        dijikstra(i);

    cout << res;

    return 0;
}
```
# 备注
