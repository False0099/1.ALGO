# The way home

## 题面翻译

一个人在一张有向图的 $1$ 号结点，他要去到 $n$ 结点。每条边 $(a_i,b_i)$ 有边权 $s_i$，表示走过这条边需要花 $s_i$ 元。这个人一开始有 $p$ 元，到了一个点 $u$，他可以进行若干次演出，每次演出收获 $w_u$ 元。问到达 $n$ 的最小演出次数，若无解输出 ```-1```。

## 题目描述

The famous magician Borya Budini traveled through the country $ X $ , which consists of $ n $ cities. However, an accident happened, and he was robbed in the city number $ 1 $ . Now Budini will have a hard way home to the city number $ n $ .He's going to get there by plane. In total, there are $ m $ flights in the country, $ i $ -th flies from city $ a_i $ to city $ b_i $ and costs $ s_i $ coins. Note that the $ i $ -th flight is one-way, so it can't be used to get from city $ b_i $ to city $ a_i $ . To use it, Borya must be in the city $ a_i $ and have at least $ s_i $ coins (which he will spend on the flight).

After the robbery, he has only $ p $ coins left, but he does not despair! Being in the city $ i $ , he can organize performances every day, each performance will bring him $ w_i $ coins.

Help the magician find out if he will be able to get home, and what is the minimum number of performances he will have to organize.

## 输入格式

Each test consists of multiple test cases. The first line contains a single integer $ t $ ( $ 1 \le t \le 80 $ ) – the number of test cases. The description of test cases follows.

The first line contains three integers $ n $ , $ m $ and $ p $ ( $ 2 \le n \le 800 $ , $ 1 \le m \le 3000 $ , $ 0 \le p \le 10^9 $ ) — the number of cities, the number of flights and the initial amount of coins.

The second line contains $ n $ integers $ w_1, w_2, \ldots, w_n $ $ (1 \le w_i \le 10^9) $ — profit from representations.

The following $ m $ lines each contain three integers $ a_i $ , $ b_i $ and $ s_i $ ( $ 1 \le a_i, b_i \le n $ , $ 1 \le s_i \le 10^9 $ ) — the starting and ending city, and the cost of $ i $ -th flight.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 800 $ and the sum of $ m $ over all test cases does not exceed $ 10000 $ .

## 输出格式

For each test case print a single integer — the minimum number of performances Borya will have to organize to get home, or $ -1 $ if it is impossible to do this.

## 样例 #1

### 样例输入 #1

```
4
4 4 2
7 4 3 1
1 2 21
3 2 6
1 3 8
2 4 11
4 4 10
1 2 10 1
1 2 20
2 4 30
1 3 25
3 4 89
4 4 7
5 1 6 2
1 2 5
2 3 10
3 4 50
3 4 70
4 1 2
1 1 1 1
1 3 2
```

### 样例输出 #1

```
4
24
10
-1
```

## 提示

In the first example, it is optimal for Borya to make $ 4 $ performances in the first city, having as a result $ 2 + 7 \cdot 4 = 30 $ coins, and then walk along the route $ 1-3-2-4 $ , spending $ 6+8+11=25 $ coins. In the second example, it is optimal for Borya to make $ 15 $ performances in the first city, fly to $ 3 $ city, make $ 9 $ performances there, and then go to $ 4 $ city.


## 题解
我们本题与我们的 [[【坐标dp】ABC344F Earn to advance]] 的区别是在于：我们再 ABC 中的题目，我们到达某一个结点之后，我们的后续节点不可能再去更新我们的这一个结点，而与之相比，我们本题中可能存在我们的环。

令 $dp_{i,j}$ 表示当前走到第 $i$ 号节点，在 $i$ 之前经过的节点中 $w$ 最大的节点编号为 $j$, 此时的最小表演数和最大剩余钱数。

转移方式：优先考虑表演数小的，当表演数相同时，再考虑剩余钱数人的。结合 dijkstra 算法进行求解即可。

```cpp
#include<bits/stdc++.h>
#define IL inline
#define int long long
#define pr pair <int,int>
#define ft first
#define sd second
#define pb push_back
#define mpr make_pair
using namespace std;
const int N = 8e2 + 10,inf = 1e18 + 10;
bool _u;
struct node {
	int ans,rst,a,b;
	node() {}
	node(int _x,int _y,int _z,int _w) : ans(_x),rst(_y),a(_z),b(_w) {}
	bool operator < (const node &x) const {
		return ans == x.ans ? rst < x.rst : ans > x.ans;
	}
}dp[N][N]; // dp[i][j] 表示当前走到第 i号节点，在 i 之前经过的节点中 w 最大的节点编号为 j，此时的最小表演数和最大剩余钱数	
priority_queue <node> Q;
vector <pr> e[N];
int T,n,m,p,ans,w[N];
bool _v;
IL int read() {
	int x = 0,f = 1;
	char c = getchar();
	while(c < '0' || c > '9') {
		if(c == '-')	f = -1;
		c = getchar();
	}
	while(c >= '0' && c <= '9') {
		x = (x << 1) + (x << 3) + (c ^ 48);
		c = getchar();
	}
	return x * f;
}
signed main() {
	clock_t st = clock();
//	freopen("1.in","r",stdin);
//	freopen("1.out","w",stdout);
//	cerr << abs(&_u - &_v) / 1048576.0 << " MB" << endl;
	T = read();
	while(T --) {
		memset(dp,0x3f,sizeof(dp));
		n = read(),m = read(),p = read(),ans = inf;
		for(int i = 1;i <= n;i ++)	w[i] = read(),e[i].clear();
		for(int i = 1,u,v,s;i <= m;i ++)	u = read(),v = read(),s = read(),e[u].pb(mpr(v,s));
		dp[1][0] = node(0,p,1,0),Q.push(dp[1][0]);
		while(!Q.empty()) {
			node p = Q.top();Q.pop();
			int val = p.ans,my = p.rst,i = p.a,j = p.b;
			if(val > dp[i][j].ans || my < dp[i][j].rst)	continue;
			if(w[i] > w[j])	j = i;
			for(auto v : e[i]) {
				int to = v.ft,ct = v.sd,tm = max(1ll * 0,(int)ceil(1.0 * (ct - my) / w[j])),rt = tm * w[j] + my - ct;
				if(dp[to][j].ans > val + tm || (dp[to][j].ans == val + tm && dp[to][j].rst < rt)) {
					dp[to][j] = node(val + tm,rt,to,j);
					Q.push(dp[to][j]);
				}
			}
		}
		for(int i = 1;i <= n;i ++)	ans = min(ans,dp[n][i].ans);
		printf("%lld\n",ans == inf ? -1 : ans);
	}
//	cerr << (clock() - st) * 1.0 / CLOCKS_PER_SEC << " s" << endl;
	return 0;
}
```