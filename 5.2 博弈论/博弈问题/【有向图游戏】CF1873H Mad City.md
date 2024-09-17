# Mad City

## 题面翻译

# 题目描述
Marcel 和 Valeriu 住在一座包含 $n$ 座建筑物和 $n$ 条无向边的城市。

初始时，Marcel 和 Valeriu 分别处于建筑物 $a$ 和建筑物 $b$。 Marcel 想要抓住 Valeriu。Valeriu 被 Marcel 抓住，当且仅当二人在某一时刻处于同一条边或同一座建筑物中。

在每次行动中，他们会选择移动到一个相邻的建筑物中，或停留在原地。由于 Valeriu 十分了解 Marcel，Valeriu 能够预测出 Marcel 的下一步行动。Valeriu 可以利用这些信息来制定行动路线。二人同时开始和结束行动。

对于任何两个建筑物，有且仅有一条路径将二者相连。

假设二人都绝顶聪明，判断 Valeriu 是否能够永远不被 Marcel 抓住。
# 输入格式
**本题有多组测试数据。**

第一行包含一个整数 $t （1\le t\le 1000）$，代表测试数据的组数。

对于每组测试数据，第一行包含三个整数 $n，a，b（3\le n\le 2\times10^5，1\le a，b\le n）$，分别表示建筑物的数目、Marcel 与 Valeriu 的初始位置。

接下来的 $n$ 行，每行包含两个整数 $u_i，v_i（1 \le u_i，v_i\le n）$，表示存在一条连接建筑物 $u$ 和 $v$ 的无向边。数据保证不存在自环或重边。

所有测试数据中的 $n$ 之和不超过 $2\times 10^5$。

数据保证图是联通的。

# 输出格式
对于每组测试数据，如果 Marce 永远无法追上 Valeriu，在单独的一行中输出 `YES`，否则输出 `NO`（输出不区分字母的大小写，例如假设某组测试数据中 Marce 永远无法追上 Valeriu，输出 `Yes`，`yes` 或 `YeS` 都被视为正确答案）。

## 题目描述

Marcel and Valeriu are in the mad city, which is represented by $ n $ buildings with $ n $ two-way roads between them.

Marcel and Valeriu start at buildings $ a $ and $ b $ respectively. Marcel wants to catch Valeriu, in other words, be in the same building as him or meet on the same road.

During each move, they choose to go to an adjacent building of their current one or stay in the same building. Because Valeriu knows Marcel so well, Valeriu can predict where Marcel will go in the next move. Valeriu can use this information to make his move. They start and end the move at the same time.

It is guaranteed that any pair of buildings is connected by some path and there is at most one road between any pair of buildings.

Assuming both players play optimally, answer if Valeriu has a strategy to indefinitely escape Marcel.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \leq t \leq 1000 $ ) — the number of test cases.

The first line of each test case contains three space-separated integers $ n $ , $ a $ , $ b $ ( $ 3 \leq n \leq 2 \cdot 10^5 $ ; $ 1 \leq a, b \leq n $ ) — the number of buildings (which equals the number of roads) and the starting buildings of Marcel and Valeriu.

The following $ n $ lines each contain two integers $ u_i $ , $ v_i $ ( $ 1 \le u_i, v_i \le n $ , $ u_i \neq v_i $ ) — there is a road between buildings $ u_i $ and $ v_i $ . There is at most one road between any unordered pair of buildings.

The sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

The roads are given that it is possible to get from any building to any other building going along the roads.

## 输出格式

For each test case output "YES" if Valeriu can escape Marcel forever and "NO" otherwise.

You can output the answer in any case (for example, the strings "yEs", "yes", "Yes" and "YES" will be recognized as a positive answer).

## 样例 #1

### 样例输入 #1

```
6
3 2 1
2 1
3 2
1 3
4 1 4
1 4
1 2
1 3
2 3
4 1 2
1 2
2 3
2 4
3 4
7 1 1
4 1
2 1
5 3
4 6
4 2
7 5
3 4
8 5 3
8 3
5 1
2 6
6 8
1 2
4 8
5 7
6 7
10 6 1
1 2
4 3
5 8
7 8
10 4
1 9
2 4
8 1
6 2
3 1
```

### 样例输出 #1

```
YES
NO
YES
NO
NO
YES
```

## 提示

In the first test case the graph looks as follows:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1873H/57f112414d9feb302cde3eb9ce7e3d32cb62f4f0.png)  Marcel starts at building $ 2 $ , while Valeriu starts at building $ 1 $ . Valeriu knows which way Marcel will move around the triangle, and he can simply always move in the same way to avoid Marcel forever. In the second test case the graph looks as follows:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1873H/9bfe57c1a5f70fb94cfe6f768eb4a55a5ee0a3f6.png)  Marcel starts at building $ 1 $ , while Valeriu starts at building $ 4 $ . Marcel can go to building $ 4 $ on his first move and win, since Valeriu must either go to building $ 1 $ (then he meets Marcel on the road from $ 1 $ to $ 4 $ ) or stay at building $ 4 $ (then he meets Marcel at building $ 4 $ ). So there is no strategy for Valeriu to win.

## 题解
我们这一题根据我们给定的条件，我们一定可以断言，我们的图是一颗基环树。
我们可以发现，只要到了我们的环上，我们就能永久的逃脱，而基环树最多只有一个环，所以我们可以推断，$A$ 点到我们 $tag$ 点的距离是否是小于我们 $A$ 点到 $B$ 点的距离，如果是，那么我们一定可以逃脱，反之，我们就永远不能逃脱。

这里，我们的 tag 点是指我们这一个点到我们环的最近距离。

```cpp
#include<bits/stdc++.h>
#define maxn 200060
#define inf 0x3f3f3f3f
using namespace std;

int t;
int n, a, b;
int head[maxn << 1], nxt[maxn << 1], to[maxn << 1], cnt, rd[maxn];
//建无向图，一定要开二倍空间！！
bool vist[maxn], visd[maxn];
int tagn, disa, disb;

void add_edge(int u, int v)//链式前向星建图
{
	nxt[++ cnt] = head[u];
	head[u] = cnt;
	to[cnt] = v;
}

void clean()
{
	memset(rd, 0, sizeof(int)*(n + 10));
	memset(head, 0, sizeof(int)*(n + 10));
	memset(nxt, 0, sizeof(int)*(n + 10));
	memset(to, 0, sizeof(int)*(n + 10));
	memset(visd, false, sizeof(bool)*(n + 10));
	memset(vist, false, sizeof(bool)*(n + 10));
	tagn = 0, cnt = 0, disa = inf, disb = inf;
}

void topu(int x) //拓扑
{
	vist[x] = true;
	for(int i = head[x]; i; i = nxt[i])
	{
		int y = to[i];
		if(vist[y] || rd[y] == 0) continue;
		rd[y] --; rd[x] --;
		if(x == tagn) tagn = y; //点被删，转移 tag 位置 
		if(rd[y] != 1) continue;
		topu(y);
	}
	vist[x] = false;
}

void dfs(int x, int js) //爆搜搜距离 
{
	visd[x] = true;
	if(x == a) disa = min(disa, js);
	if(x == b) disb = min(disb, js);
	for(int i = head[x]; i; i = nxt[i])
	{
		int y = to[i];
		if(visd[y]) continue;
		dfs(y, js + 1);
	}
	visd[x] = false;
}

void _run()
{	
	cin >> n >> a >> b;
	clean();
	tagn = b;
	for(int i = 1; i <= n; i ++)
	{
		int u, v;
		cin >> u >> v;
		add_edge(u, v);
		add_edge(v, u);
		rd[u] ++; rd[v] ++;
	}
	
	for(int i = 1; i <= n; i ++)
		if(rd[i] == 1) topu(i);
	
	if(rd[b] >= 2 && a != b) {cout << "YES\n"; return;}
	else if(a == b) {cout << "NO\n"; return;}
	
	dfs(tagn, 0);
	if(disa > disb) cout << "YES\n";
	else cout << "NO\n";
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	
	cin >> t;
	while(t --) _run();
	
	return 0;
}
```