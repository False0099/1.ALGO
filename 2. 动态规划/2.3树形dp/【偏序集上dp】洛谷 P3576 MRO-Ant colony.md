
# 题目
 # [POI 2014]MRO-Ant colony

## 题目背景

[English Edition](/paste/44plylwf)

## 题目描述

正在寻找食物的蚂蚁们来到了一座山。

这座山有 $n$ 个洞穴，并有 $n-1$ 条道路连接这些洞穴。也就是说，所有的洞穴和道路组成了一个树形结构。

对于每个只有一条道路连接的洞穴，都有一个出入口使得该洞穴与外界相连。

在**每个出入口**处，都有 $g$ 群蚂蚁，第 $i$ 群蚂蚁的大小为 $m_i$。

蚂蚁群会一个接一个地进入山中，当且仅当山中没有蚂蚁，下一群蚂蚁才会进入。

进入山后，蚂蚁们会按如下方式行动：

- 如果蚂蚁们进入了一个洞穴，该洞穴有 $d$ 条道路与之相连（不包括它们进入该洞穴经过的道路），则蚂蚁们会分为大小相等的 $d$ 个蚁群，每个蚁群各选择一条道路，使得一个道路恰好有一条蚁群经过，特别地，如果 $d=0$（即蚁群到达了出口），蚂蚁们会从该出口离开山。
- 根据上文，假如这个蚁群有 $x$ 只蚂蚁，则每个蚁群会有 $\left \lfloor \dfrac{x}{d} \right \rfloor$ 只蚂蚁，多余的蚂蚁将会消失（至于怎么消失，这并不重要 :)）。

下面这张图就是一个例子：大小为 $m$ 的蚁群到达了一个洞穴，该洞穴有 $3$ 条道路（除了它们进入该洞穴时经过的道路），则该蚁群分割成了三个大小为 $\left \lfloor \dfrac{m}{3} \right \rfloor$ 的蚁群。

![](https://cdn.luogu.com.cn/upload/pic/6972.png)

在其中一条道路上，有一只食蚁兽，当经过该道路的蚁群大小恰好为 $k$ 时，它会把这个蚁群的蚂蚁全部吃掉。

现在请你求出食蚁兽一共吃掉多少只蚂蚁。

## 输入格式

第一行三个整数 $n, g, k$。

之后一行 $g$ 个整数，分别为 $m_1, m_2,\dots, m_g$。

之后 $n-1$ 行，每行两个整数 $a, b$，表示在 $a, b$ 之间有一条边。

输入的第一条边是食蚁兽所在的边。

## 输出格式

输出一行一个整数，表示所有被吃掉的蚁群的大小之和。

## 样例 #1

### 样例输入 #1

```
7 5 3
3 4 1 9 11
1 2
1 4
4 3
4 5
4 6
6 7
```

### 样例输出 #1

```
21
```

## 提示

对于 $100\%$ 的数据，$2\le n,g\le10^6$，$1\le k,m_i\le10^9$，$1\le a_i,b_i\le n$。

# 思路
注意到，如果我们采用我们的暴力方法的话，我们的预期时间复杂度是 $o(n^2)$ 的，那么我们只能骗一点暴力分，是不太划算的。

于是我们回顾我们的过程，其实我们可以发现，如果我们以我们的边对应的那两个点作为子树去计算和我们以每一个点为子树的结果是一样的。于是我们可以枚举我们从 a 节点出发，给我们的答案的贡献是多少。

假设我们第 i 个节点存在数量大于等于 $dp_{1}[i]$ 的蚂蚁，小于 $dp_{2}[i]$ 的蚂蚁能够对我们的答案有贡献，那么我们的转移方程就可以写成：
$$\begin{aligned}dp1_v&=dp1_u\cdot(c_u-1)\\\\dp2_v&=(dp2_u+1)\cdot(c_u-1)-1\end{aligned}$$

其中 $c_{u}$ 表示 u 节点的度。

最后对于每一个叶子结点 $i$,在 $m$ 数组中二分查找大于等于 $dp1_i$ 且小于等于 $dp2_i$ 的数量，


# AC 代码
```cpp
#include <bits/stdc++.h>
#define rep(x, l, r) for(int x = l; x <= r; x++)
using namespace std;
typedef long long ll;

const ll INF = 1 << 30;
const int MAXN = 1e7 + 5;

int n, m, k, cnt, root1, root2;
int head[MAXN], nxt[MAXN << 1], to[MAXN << 1];
int a[MAXN];
ll dp1[MAXN], dp2[MAXN], c[MAXN];

void addedge(int u, int v){
	cnt++;
	nxt[cnt] = head[u];
	head[u] = cnt;
	to[cnt] = v;
}

void add(int u, int v){
	addedge(u, v);
	addedge(v, u);
	c[u]++; c[v]++;
}

void dfs(int u, int fa){
	for(int e = head[u]; e; e = nxt[e]){
		int v = to[e];
		if(v == fa) continue;
		dp1[v] = min(INF, dp1[u] * (c[u] - 1));//防止炸longlong//判断我们每个节点的上线，下线
		dp2[v] = min(INF, (dp2[u] + 1) * (c[u] - 1) - 1); //计算我们当前点的下线
		dfs(v, u);
	}
}

int main(){
	scanf("%d%d%d", &n, &m, &k);
	rep(i, 1, m) scanf("%d", &a[i]);
	sort(a + 1, a + m + 1);
	scanf("%d%d", &root1, &root2);
	//由第一个和第二个建边
	add(0, root1);//建一个0点与两个根节点连边
	add(0, root2);
	rep(i, 1, n - 2){
		int x, y;
		scanf("%d%d", &x, &y);
		add(x, y);//建单向边
	}
	dp1[0] = dp2[0] = k;//初始化范围
	dfs(0, -1);
	ll ans = 0;//
	rep(i, 1, n)//找所有的叶节点
		if(c[i] == 1){
			ans += upper_bound(a + 1, a + m + 1, dp2[i]) - lower_bound(a + 1, a + m + 1, dp1[i]);
		}
	printf("%lld\n", ans * k);//最后记得要乘上k
	return 0;
}
```
# 备注
