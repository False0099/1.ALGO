# [USACO 08 MAR] Cow Jogging G

## 题目描述

贝西终于尝到了懒惰的后果，决定每周从谷仓到池塘慢跑几次来健身。当然，她不想跑得太累，所以她只打算从谷仓慢跑下山到池塘，然后悠闲地散步回谷仓。

同时，贝西不想跑得太远，所以她只想沿着通向池塘的最短路径跑步。一共有 $M$ 条道路，其中每一条都连接了两个牧场。这些牧场从 $1$ 到 $N$ 编号，如果 $X>Y$，则说明牧场 $X$ 的地势高于牧场 $Y$，即下坡的道路是从 $X$ 通向 $Y$ 的，$N$ 为贝西所在的牛棚（最高点），$1$ 为池塘（最低点）。

然而，一周之后，贝西开始对单调的路线感到厌烦，她希望可以跑不同的路线。比如说，她希望能有 $K$ 种不同的路线。同时，为了避免跑得太累，她希望这 $K$ 条路线是从牛棚到池塘的路线中最短的 $K$ 条。如果两条路线包含的道路组成的序列不同，则这两条路线被认为是不同的。

请帮助贝西算算她的训练强度，即将牧场网络里最短的 $K$ 条路径的长度分别算出来。你将会被提供一份牧场间路线的列表，每条道路用 $(X_i, Y_i, D_i)$ 表示，意为从 $X_i$ 到 $Y_i$ 有一条长度为 $D_i$ 的下坡道路。

## 输入格式

第一行三个用空格分开的整数 $N,M,K$，其中。

第二行到第 $M+1$ 行每行有三个用空格分开的整数 $X_i,Y_i,D_i$，描述一条下坡的道路。

## 输出格式

共 $K$ 行，在第 $i$ 行输出第 $i$ 短的路线长度，如果不存在则输出 $-1$。如果出现多种有相同长度的路线，务必将其全部输出。

## 样例 #1

### 样例输入 #1

```
5 8 7 
5 4 1 
5 3 1 
5 2 1 
5 1 1 
4 3 4 
3 1 1 
3 2 1 
2 1 1
```

### 样例输出 #1

```
1 
2 
2 
3 
6 
7 
-1
```

## 提示

#### 样例 1 解释

这些路线分别为 $(5\to 1)$、$(5\to 3\to 1)$、$(5\to 2\to 1)$、$(5\to 3\to 2\to 1)$、$(5\to 4\to 3\to 1)$ 和 $(5\to 4\to 3\to 2\to 1)$。

#### 数据规模与约定

对于全部的测试点，保证 $1 \le N \le 1,000$，$1 \le M \le 1\times10^4$，$1 \le K \le 100$，$1 \le Y_i < X_i\le N$，$1 \le D_i \le 1\times 10^6$，


## 题解
我们本题的题目要求已经非常的明确，就是要求我们从起点出发到达终点的第 K 短路是多少。于是我们就可以通过我们的 A star 算法来计算我们的第 K 短路，并且记录他们的对应路径。

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
        if(ver==T&&cnt[T]!=K){
        	cout<<distance<<endl;
		}
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
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    cin >> n >> m>>K;
    memset(h,-1,sizeof h);
    memset(rh,-1,sizeof rh);
    for(int i=0;i<m;i++)
    {
        int a,b,c;
        cin >> a >> b >> c;
        add(h,a,b,c);
        add(rh,b,a,c);
    }
    S=n;
    T=1;
  
    // 起点==终点时 则d[S→S] = 0 这种情况就要舍去 ,总共第K大变为总共第K+1大 
    if (S == T) K ++ ;
    // 从各点到终点的最短路距离 作为估计函数f[u]
    dijkstra();
    cout << astar();
    return 0;
}

```