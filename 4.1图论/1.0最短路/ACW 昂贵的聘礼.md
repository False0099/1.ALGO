# 知识点
  ## [[单源最短路问题]]
# 题目
 年轻的探险家来到了一个印第安部落里。

在那里他和酋长的女儿相爱了，于是便向酋长去求亲。

酋长要他用 10000 个金币作为聘礼才答应把女儿嫁给他。

探险家拿不出这么多金币，便请求酋长降低要求。

酋长说：”嗯，如果你能够替我弄到大祭司的皮袄，我可以只要 8000 金币。如果你能够弄来他的水晶球，那么只要 5000 金币就行了。”

探险家就跑到大祭司那里，向他要求皮袄或水晶球，大祭司要他用金币来换，或者替他弄来其他的东西，他可以降低价格。

探险家于是又跑到其他地方，其他人也提出了类似的要求，或者直接用金币换，或者找到其他东西就可以降低价格。

不过探险家没必要用多样东西去换一样东西，因为不会得到更低的价格。

探险家现在很需要你的帮忙，让他用最少的金币娶到自己的心上人。

另外他要告诉你的是，在这个部落里，等级观念十分森严。

地位差距超过一定限制的两个人之间不会进行任何形式的直接接触，包括交易。

他是一个外来人，所以可以不受这些限制。

但是如果他和某个地位较低的人进行了交易，地位较高的的人不会再和他交易，他们认为这样等于是间接接触，反过来也一样。

因此你需要在考虑所有的情况以后给他提供一个最好的方案。

为了方便起见，我们把所有的物品从 1 开始进行编号，酋长的允诺也看作一个物品，并且编号总是 1
。

每个物品都有对应的价格 P，主人的地位等级 L，以及一系列的替代品 Ti 和该替代品所对应的”优惠” Vi
。

如果两人地位等级差距超过了 M，就不能”间接交易”。

你必须根据这些数据来计算出探险家最少需要多少金币才能娶到酋长的女儿。

## 输入格式
输入第一行是两个整数 M，N，依次表示地位等级差距限制和物品的总数。

接下来按照编号从小到大依次给出了 N 个物品的描述。

每个物品的描述开头是三个非负整数 P、L、X，依次表示该物品的价格、主人的地位等级和替代品总数。

接下来 X 行每行包括两个整数 T 和 V，分别表示替代品的编号和”优惠价格”。

## 输出格式
输出最少需要的金币数。

## 数据范围
1≤N≤100
,
1≤P≤10000
,
1≤L, M≤N
,
0≤X < N
## 输入格式
1 4
10000 3 2
2 8000
3 5000
1000 2 1
4 200
3000 2 1
4 200
50 2 0
## 输出格式
5250

# 思路
·我们首先构造一个虚拟原点 o，并且将这个点与所有点都连一条线，此时的 dist 就表示我们购买每一个物品所花费的最小代价。
·此外，对于题目中要求的等级需求，我们可以通过在跑 dij 时限定每一个物品的上界和下界的方法，来确定我们所能跑到的结果，保证满足等级差不超过 k
·虚拟原点不需要实际构造出来，只需要在建立队列的时候一开始就把所有物品放进去就可以了。
# AC 代码
```cpp
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

const int N = 110 * 110, INF = 0x3f3f3f3f, M = N;
typedef pair<int, int> PII;

int n, m;
int h[N], e[M], w[M], ne[M], idx,  L[N];
int dist[N];
bool st[N];

void add(int a, int b, int c)  // 添加一条边a->b，边权为c
{
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++ ;
}

int dijkstra(int down, int up)
{
    memset(dist, 0x3f, sizeof dist);
    memset(st, 0, sizeof st);

    priority_queue<PII, vector<PII>, greater<> > heap;
    heap.push({0, 0}), dist[0] = 0;

    while (heap.size())
    {
        auto t = heap.top().second; heap.pop();

        if (st[t]) continue ;
        st[t] = true ;

        for (int i = h[t]; ~i; i = ne[i]) 
        {
            int j = e[i];
            if (L[j] >= down && L[j] <= up && dist[j] > dist[t] + w[i]) 
            {
                dist[j] = dist[t] + w[i];
                heap.push({dist[j], j});
            }
        }
    }

    return dist[1];
}

int main()
{
    scanf("%d%d", &m, &n);

    memset(h, -1, sizeof h);

    for (int i = 1; i <= n; i ++ )
    {
        int price, cnt;
        scanf("%d%d%d", &price, &L[i], &cnt);
        add(0, i, price);
        while (cnt -- )
        {
            int id, cost;
            scanf("%d%d", &id, &cost);
            add(id, i, cost);
        }
    }

    int res = INF;
    for (int i = L[1] - m; i <= L[1]; i ++ ) 
        res = min(res, dijkstra(i, i + m));

    printf("%d\n", res);

    return 0;
}


```
# 备注
