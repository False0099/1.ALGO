# [USACO 09 FEB] Revamping Trails G

## 题面翻译

约翰一共有 $N$ 个牧场. 由 $M$ 条布满尘埃的小径连接。小径可以双向通行。每天早上约翰从牧场 $1$ 出发到牧场 $N$ 去给奶牛检查身体。

通过每条小径都需要消耗一定的时间。约翰打算升级其中 $K$ 条小径，使之成为高速公路。在高速公路上的通行几乎是瞬间完成的，所以高速公路的通行时间为 $0$。

请帮助约翰决定对哪些小径进行升级，使他每天从 $1$ 号牧场到第 $N$ 号牧场所花的时间最短。

## 题目描述

Farmer John dutifully checks on the cows every day. He traverses some of the M (1 <= M <= 50,000) trails conveniently numbered 1.. M from pasture 1 all the way out to pasture N (a journey which is always possible for trail maps given in the test data). The N (1 <= N <= 10,000) pastures conveniently numbered 1.. N on Farmer John's farm are currently connected by bidirectional dirt trails.  Each trail i connects pastures P 1\_i and P 2\_i (1 <= P 1\_i <= N; 1 <= P 2\_i <= N) and requires T\_i (1 <= T\_i <= 1,000,000) units of time to traverse.

He wants to revamp some of the trails on his farm to save time on his long journey. Specifically, he will choose K (1 <= K <= 20) trails to turn into highways, which will effectively reduce the trail's traversal time to 0. Help FJ decide which trails to revamp to minimize the resulting time of getting from pasture 1 to N.

TIME LIMIT: 2 seconds

## 输入格式

\* Line 1: Three space-separated integers: N, M, and K

\* Lines 2.. M+1: Line i+1 describes trail i with three space-separated integers: P 1\_i, P 2\_i, and T\_i

## 输出格式

\* Line 1: The length of the shortest path after revamping no more than K edges

## 样例 #1

### 样例输入 #1

```
4 4 1 
1 2 10 
2 4 10 
1 3 1 
3 4 100
```

### 样例输出 #1

```
1
```

## 提示

K is 1; revamp trail 3->4 to take time 0 instead of 100. The new shortest path is 1->3->4, total traversal time now 1.

## 题解
我们这一题简直就是云大校赛的模板题目（）
我们这里，可以采用我们的分层图方法，我们这里因为有 K 条免费的道路，所以我们可以建立我们的 K 层图，建图时，我们要除以，我们老图上的点与我们的新一层连边时，我们都有 cost=0，这一点我们在见图的时候注意。然后我们最后要求的从 1 到 N 的最短路径，就是我们从第 0 层图的 1 到任意层的 N 的最短路径。

```cpp
```cpp
#include<bits/stdc++.h>
using namespace std;

const int maxn=100100;
const int maxm=500500;

int nextt[maxm*42],w[maxm*42],to[maxm*42],head[maxn*42],cnt=0;

void add(int u,int v,int cost)
{
	cnt++;
	nextt[cnt]=head[u];
	head[u]=cnt;
	to[cnt]=v;
	w[cnt]=cost;
}

struct node
{
	int u,dis;
	bool operator<(const node x) const
	{
		return dis>x.dis;
	}
};

priority_queue<node> q;
int dist[maxn*21];

void dij(int s)
{
	memset(dist,0x3f,sizeof(dist));
	dist[s]=0;
	q.push((node){s,0});
	while (!q.empty())
	{
		node fr=q.top();q.pop();
		int u=fr.u,dis=fr.dis;
		if (dis!=dist[u]) continue;
		for (int v=head[u];v;v=nextt[v])
			if (dist[to[v]]>dist[u]+w[v])
			{
				dist[to[v]]=dist[u]+w[v];
				q.push((node){to[v],dist[to[v]]});
			}
	}
}

int n,m,k;

int main()
{
	cin>>n>>m>>k;
	for (int i=1;i<=m;i++)
	{
		int u,v,cost;
		cin>>u>>v>>cost;
		add(u,v,cost);add(v,u,cost);
		for (int j=1;j<=k;j++)
		{
			add(n*j+u,n*j+v,cost);add(n*j+v,n*j+u,cost);
			add(n*(j-1)+u,n*j+v,0);add(n*(j-1)+v,n*j+u,0);
		}
	}
	dij(1);
	int ans=dist[n];
	for (int i=1;i<=k;i++)
	{
//		cout<<"### dist["<<i*n+n<<"]: "<<dist[i*n+n]<<endl;
		ans=min(ans,dist[i*n+n]);
	}
	cout<<ans;
	return 0;
}
```
```