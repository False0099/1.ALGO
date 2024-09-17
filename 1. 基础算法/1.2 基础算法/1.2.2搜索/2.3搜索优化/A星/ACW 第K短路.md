# 知识点
  ## [[A star 算法]]
# 题目
 

# 思路

***另外，这一题求第 k 短路的思路是，不管什么，直接把所有点都加入到我们的当前的这个队列中。然后再每一次从队列中出队我们的距离，出队了几次，就是到这个点的第几短路。这么做显然是数据过大的，那么我们就要 A star 去优化

**对于 A star 算法，我们朴素的理解是，壳子上还是沿用原来的 dij 算法。即一个点一次出队后就不可能再去更新这个点。
但是对于 A * 算法而言，我们的更新依据不是之前的找到最短的边，相反，我们要依据到当前点的已知距离加上该点到结果的期望距离来排序。这样我们就能缩短搜索所需要的时间
其中期望距离要求必须小于等于该点到最终点的实际距离

# AC 代码
```cpp
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>

#define x first
#define y second

using namespace std;

typedef pair<int, int> PII;
typedef pair<int, PII> PIII;
const int N = 1010, M = 200010;

int n, m, S, T, K;
int h[N], rh[N], e[M], w[M], ne[M], idx;
int dist[N], cnt[N];
bool st[N];

void add(int h[],int a,int b,int c)
{
    e[idx] = b;
    w[idx] = c;
    ne[idx] = h[a];
    h[a] = idx++;
}

void dijkstra()//先预处理期望函数,我们反向处理
{
    priority_queue<PII,vector<PII>,greater<PII>> heap;
    heap.push({0,T});//终点
    memset(dist, 0x3f, sizeof dist);
    dist[T] = 0;

    while(heap.size())
    {
        auto t = heap.top();
        heap.pop();

        int ver = t.y;
        if(st[ver]) continue;
        st[ver] = true;

        for(int i=rh[ver];i!=-1;i=ne[i])
        {
            int j = e[i];
            if(dist[j]>dist[ver]+w[i])
            {
                dist[j] = dist[ver] + w[i];
                heap.push({dist[j],j});
            }
        }
    }
}

int astar()
{
    priority_queue<PIII, vector<PIII>, greater<PIII>> heap;//自动排序
    // 谁的d[u]+f[u]更小 谁先出队列
    heap.push({dist[S], {0, S}});
    while(heap.size())
    {
        auto t = heap.top();
        heap.pop();
        int ver = t.y.y,distance = t.y.x;
        
        cnt[ver]++;
        if(ver==)
        //如果终点已经被访问过k次了 则此时的ver就是终点T 返回答案

        if(cnt[T]==K) return distance;

        for(int i=h[ver];i!=-1;i=ne[i])
        {
            int j = e[i];
            /* 
            如果走到一个中间点都cnt[j]>=K，则说明j已经出队k次了，且astar()并没有return distance,
            说明从j出发找不到第k短路(让终点出队k次)，
            即继续让j入队的话依然无解，
            那么就没必要让j继续入队了
            */
            if(cnt[j] < K)
            {
                // 按 真实值+估计值 = d[j]+f[j] = dist[S->t] + w[t->j] + dist[j->T] 堆排
                // 真实值 dist[S->t] = distance+w[i]
                heap.push({distance+w[i]+dist[j],{distance+w[i],j}});
            }
        }
    }
    // 终点没有被访问k次
    return -1;
}

int main()
{
    cin >> m >> n;
    memset(h,-1,sizeof h);
    memset(rh,-1,sizeof rh);
    for(int i=0;i<n;i++)
    {
        int a,b,c;
        cin >> a >> b >> c;
        add(h,a,b,c);
        add(rh,b,a,c);
    }
    cin >> S >> T >> K;
    // 起点==终点时 则d[S→S] = 0 这种情况就要舍去 ,总共第K大变为总共第K+1大 
    if (S == T) K ++ ;
    // 从各点到终点的最短路距离 作为估计函数f[u]
    dijkstra();
    cout << astar();
    return 0;
}

作者：仅存老实人
链接：https://www.acwing.com/solution/content/21233/
来源：AcWing
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
```
# 备注
