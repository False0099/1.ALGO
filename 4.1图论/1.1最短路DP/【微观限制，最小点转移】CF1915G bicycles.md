# Bicycles

## 题面翻译

### 题目描述

给定 $n$ 个城市和 $m$ 条连接两个城市 $u_i$ 和 $v_i$ 的双向道路，长度为 $w_i$。

现在城市 $n$ 举办了一场派对，住在城市 $1$ 的 Slavic 想要去参加。在城市之间往返需要骑自行车，而 Slavic 没有自行车，所以他需要在这些城市里购买自行车以赶到城市 $n$。

从 $1$ 到 $n$ 的每个城市 $j$ 里都有且仅有一辆自行车可供购买，每辆自行车的速度系数为 $s_j$。

当 Slavic 骑上编号为 $j$ 的自行车后，他可以在任何时刻和任何地点通过一条道路 $i$，花费 $w_i\times s_j$ 的时间。

求 Slavic 骑车从城市 $1$ 赶到城市 $n$ 参加派对所需的最短时间。

### 输入格式
第一行包含一个整数 $ t\,  (  1 \leq t \leq 100  )$，代表测试数据组数。

每组数据的第一行包含两个整数 $n$ 和 $m$，代表城市的数量和道路的数量。

接下来的 $m$ 行中，第 $i$ 行包含三个整数 $u_i$、$v_i$ 和 $w_i$，代表一条连接城市 $u_i$ 和 $v_i$，长度为 $w_i$ 的双向道路。

每组数据的最后一行包含 $n$ 个整数 $ s_1, \ldots, s_n $，代表在城市 $i$ 可供购买的自行车的速度系数。

### 输出格式

对于每组测试数据，输出一个整数，代表从城市 $1$ 到达城市 $n$ 所需的最短时间。



### 数据范围
$ 2 \leq n \leq 1000 $，$ n - 1 \leq m \leq 1000 $，$ 1 \leq s_i \leq 1000 $；

$ 1 \le u_i, v_i \le n $ , $ u_i \neq v_i $，$ 1 \leq w_i \leq 10^5$；

所有测试数据的 $\sum n$、$\sum m$ 不超过 $1000$。

保证存在方案能从城市 $1$ 到达城市 $n$。

By Misaka 16172

## 题目描述

All of Slavic's friends are planning to travel from the place where they live to a party using their bikes. And they all have a bike except Slavic. There are $ n $ cities through which they can travel. They all live in the city $ 1 $ and want to go to the party located in the city $ n $ . The map of cities can be seen as an undirected graph with $ n $ nodes and $ m $ edges. Edge $ i $ connects cities $ u_i $ and $ v_i $ and has a length of $ w_i $ .

Slavic doesn't have a bike, but what he has is money. Every city has exactly one bike for sale. The bike in the $ i $ -th city has a slowness factor of $ s_{i} $ . Once Slavic buys a bike, he can use it whenever to travel from the city he is currently in to any neighboring city, by taking $ w_i \cdot s_j $ time, considering he is traversing edge $ i $ using a bike $ j $ he owns.

Slavic can buy as many bikes as he wants as money isn't a problem for him. Since Slavic hates traveling by bike, he wants to get from his place to the party in the shortest amount of time possible. And, since his informatics skills are quite rusty, he asks you for help.

What's the shortest amount of time required for Slavic to travel from city $ 1 $ to city $ n $ ? Slavic can't travel without a bike. It is guaranteed that it is possible for Slavic to travel from city $ 1 $ to any other city.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \leq t \leq 100 $ ) — the number of test cases. The description of the test cases follows.

The first line of each test case contains two space-separated integers $ n $ and $ m $ ( $ 2 \leq n \leq 1000 $ ; $ n - 1 \leq m \leq 1000 $ ) — the number of cities and the number of roads, respectively.

The $ i $ -th of the following $ m $ lines each contain three integers $ u_i $ , $ v_i $ , $ w_i $ ( $ 1 \le u_i, v_i \le n $ , $ u_i \neq v_i $ ; $ 1 \leq w_i \leq 10^5 $ ), denoting that there is a road between cities $ u_i $ and $ v_i $ of length $ w_i $ . The same pair of cities can be connected by more than one road.

The next line contains $ n $ integers $ s_1, \ldots, s_n $ ( $ 1 \leq s_i \leq 1000 $ ) — the slowness factor of each bike.

The sum of $ n $ over all test cases does not exceed $ 1000 $ , and the sum of $ m $ over all test cases does not exceed $ 1000 $ .

Additional constraint on the input: it is possible to travel from city $ 1 $ to any other city.

## 输出格式

For each test case, output a single integer denoting the shortest amount of time Slavic can reach city $ n $ starting from city $ 1 $ .

## 样例 #1

### 样例输入 #1

```
3
5 5
1 2 2
3 2 1
2 4 5
2 5 7
4 5 1
5 2 1 3 3
5 10
1 2 5
1 3 5
1 4 4
1 5 8
2 3 6
2 4 3
2 5 2
3 4 1
3 5 8
4 5 2
7 2 8 4 1
7 10
3 2 8
2 1 4
2 5 7
2 6 4
7 1 2
4 3 5
6 4 2
6 7 1
6 7 4
4 5 9
7 6 5 4 3 2 1
```

### 样例输出 #1

```
19
36
14
```


## 题解
图上 DP 典题，我们考虑设置我们的状态 $dp[i][j]$ 表示我们到达 $i$ 点时，我们选用的单车为 $j$ 所花费的时间是多少，于是，我们的转移就有：
$$
dp[v][j]=min(dp[v][j],dp[i][j]+w[j]*s[i])
$$
$$
dp[v][u]=min(dp[v][u],dp[i][j]+w[j]*s[u])
$$

这里能这么转移是因为我们的 $i$ 和 n 都足够小，所以我们可以通过上面的式子转移得到我们的答案。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=1010;
const int M=1010;
#define int long long
long long dist[N][N];//到i点用的k自行车的最小时间 
int w[M<<1],e[M<<1],ne[M<<1],h[N],idx;
int s[N];
typedef pair<int,int> PII;
typedef pair<int,pair<int,int>> PIII;
void dij(){
	memset(dist,0x3f3f3f3f3f,sizeof dist);
	priority_queue<PIII,vector<PIII>,greater<PIII>> q;
	q.push({0,{1,1}});
	dist[1][1]=0;
	while(q.size()){
		//auto u=q.front();
		int val=q.top().first;
		int u=q.top().second.first;
		int bike=q.top().second.second;
		q.pop();
		for(int i=h[u];i!=-1;i=ne[i]){
			int v=e[i];
			if(dist[v][bike]>dist[u][bike]+w[i]*s[bike]){
				dist[v][bike]=dist[u][bike]+w[i]*s[bike];
				q.push({dist[v][bike],{v,bike}});
			}
			if(dist[v][u]>dist[u][bike]+w[i]*s[u]){
				dist[v][u]=dist[u][bike]+w[i]*s[u];
				q.push({dist[v][u],{v,u}});
			}
		}
	}
} 
void add(int a,int b,int c){
	e[idx]=b;
	w[idx]=c;
	ne[idx]=h[a];
	h[a]=idx++; 
}
void solve(){
	int n,m;
	cin>>n>>m;
	memset(h,-1,sizeof h);
	for(int i=0;i<m;i++){
		int a,b,c;
		cin>>a>>b>>c;
		add(a,b,c);
		add(b,a,c);
	}
	
	for(int i=1;i<=n;i++){
		cin>>s[i];
	}
	dij();
	long long ans=0x3f3f3f3f3f;
	for(int i=1;i<=n;i++){
		ans=min(ans,dist[n][i]);
	}
	cout<<ans<<endl;
}
signed main(){
	int t;
	cin>>t;
	while(t--){
		solve();
	}
}
```