# Blood Cousins

## 题面翻译

### 题面描述

有一个家族关系森林，描述了 $n$（$1\leq n\leq 10 ^ 5$）人的家庭关系，成员编号为 $1$ 到 $n$ 。

如果 $a$ 是 $b$ 的父亲，那么称 $a$ 为 $b$ 的 $1$ 级祖先；如果 $b$ 有一个 $1$ 级祖先，$a$ 是 $b$ 的 $1$ 级祖先的 $k-1$ 级祖先，那么称 $a$ 为 $b$ 的 $k$ 级祖先。

家庭关系保证是一棵森林，树中的每个人都至多有一个父母，且自己不会是自己的祖先。

如果存在一个人 $z$ ，是两个人 $a$ 和 $b$ 共同的 $p$ 级祖先：那么称 $a$ 和 $b$ 为 $p$ 级表亲。

$m$（$1\leq m\leq 10 ^ 5$）次询问，每次询问给出一对整数 $v$ 和 $p$，求编号为 $v$ 的人有多少个 $p$ 级表亲。

### 输入格式

第一个正整数 $n$ 表示家族里共有 $n$ 个人。

接下来一行 $n$ 个数 $r_1, r_2, \ldots, r_n$，表示 $r_i$ 是 $i$ 的父亲；如果 $r_i$ 为 $0$，那么 $i$ 就是根节点。

第三行一个整数 $m$ 表示询问数量。

接下来 $m$ 行，每行两个整数 $v_i$ 和 $p_i$，数字间用空格间隔；表示一组询问，即询问编号为 $v$ 的人有多少个 $p$ 级表亲。

保证输入合法。

### 输出格式

输出一行 $m$ 个数。对于每次询问，输出其答案。数字间用空格间隔。

## 题目描述

Polycarpus got hold of a family relationship tree. The tree describes family relationships of $ n $ people, numbered 1 through $ n $ . Each person in the tree has no more than one parent.

Let's call person $ a $ a 1-ancestor of person $ b $ , if $ a $ is the parent of $ b $ .

Let's call person $ a $ a $ k $ -ancestor $ (k&gt; 1) $ of person $ b $ , if person $ b $ has a 1-ancestor, and $ a $ is a $ (k-1) $ -ancestor of $ b $ 's 1-ancestor.

Family relationships don't form cycles in the found tree. In other words, there is no person who is his own ancestor, directly or indirectly (that is, who is an $ x $ -ancestor for himself, for some $ x $ , $ x&gt; 0 $ ).

Let's call two people $ x $ and $ y $ $ (x≠y) $ $ p $ -th cousins $ (p&gt; 0) $ , if there is person $ z $ , who is a $ p $ -ancestor of $ x $ and a $ p $ -ancestor of $ y $ .

Polycarpus wonders how many counsins and what kinds of them everybody has. He took a piece of paper and wrote $ m $ pairs of integers $ v_{i} $ , $ p_{i} $ . Help him to calculate the number of $ p_{i} $ -th cousins that person $ v_{i} $ has, for each pair $ v_{i} $ , $ p_{i} $ .

## 输入格式

The first input line contains a single integer $ n $ $ (1<=n<=10^{5}) $ — the number of people in the tree. The next line contains $ n $ space-separated integers $ r_{1}, r_{2},..., r_{n} $ , where $ r_{i} $ $ (1<=r_{i}<=n) $ is the number of person $ i $ 's parent or 0, if person $ i $ has no parent. It is guaranteed that family relationships don't form cycles.

The third line contains a single number $ m $ $ (1<=m<=10^{5}) $ — the number of family relationship queries Polycarus has. Next $ m $ lines contain pairs of space-separated integers. The $ i $ -th line contains numbers $ v_{i} $ , $ p_{i} $ $ (1<=v_{i}, p_{i}<=n) $ .

## 输出格式

Print $ m $ space-separated integers — the answers to Polycarpus' queries. Print the answers to the queries in the order, in which the queries occur in the input.

## 样例 #1

### 样例输入 #1

```
6
0 1 1 0 4 4
7
1 1
1 2
2 1
2 2
4 1
5 1
6 1
```

### 样例输出 #1

```
0 0 1 0 0 1 1
```

## 题解
我们本题有两个需要注意的点，第一个是我们的树不是连通的，也就是说我们是一个森林。并且我们每一个树都是有根的。
下一步我们想找我们一个的 K 级孩子，我们可以转换为求深度，我们假设现在的深度位 $dep$,那么我们的深度为 $K$ 的孩子的大小就应该是 $dep+K$。

而需要对于哪些点求他们的 K 级孩子，需要我们通过我们的倍增来进行预处理。

```cpp
#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

const int MAXN = 100010;

int n, m;

struct edge{
	int ne, to;
}e[MAXN];
int fir[MAXN], num = 0;
inline void join(int a, int b)
{
	e[++num].ne = fir[a];
	e[num].to = b;
	fir[a] = num;
}
int rt[MAXN], tot = 0;

int siz[MAXN], son[MAXN], f[MAXN][24], dep[MAXN], lg[MAXN];

void dfs1(int u)
{
	siz[u] = 1; dep[u] = dep[f[u][0]] + 1;
	for(int i=1;i<=lg[dep[u]];i++)
		f[u][i] = f[f[u][i-1]][i-1];
	for(int i=fir[u];i;i=e[i].ne)
	{
		int v = e[i].to;
		dfs1(v);
		siz[u] += siz[v];
		if(siz[son[u]] < siz[v]) son[u] = v;
	}
}
inline int kthparent(int u, int k)
{
	for(int i=lg[dep[u]];i>=0;i--)
		if(dep[u] - dep[f[u][i]] <= k) k -= dep[u] - dep[f[u][i]], u = f[u][i];
	return u;
}

struct qrys{
	int x, k, pa, ans;
}a[MAXN];
vector<int> vp[MAXN];

int cnt[MAXN], nowson = 0;
void calc(int u, int val)
{
	cnt[dep[u]] += val;
	for(int i=fir[u];i;i=e[i].ne)
	{
		int v = e[i].to;
		if(v == nowson) continue;
		calc(v, val);
	}
}

void dfs(int u, bool is)
{
	for(int i=fir[u];i;i=e[i].ne)
	{
		int v = e[i].to;
		if(v == son[u]) continue;
		dfs(v, 0);
	}
	if(son[u]) 
	{
		dfs(son[u], 1);
		nowson = son[u];
	}
	calc(u, 1);
	nowson = 0;
	for(int i=0;i<vp[u].size();i++)
		a[vp[u][i]].ans = cnt[dep[a[vp[u][i]].x]]-1;
	if(!is) calc(u, -1);
}

int main()
{
	scanf("%d",&n);
	lg[0] = -1;
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&f[i][0]);
		if(f[i][0]) join(f[i][0], i);
		else rt[++tot] = i;
		lg[i] = lg[i>>1] + 1;
	}
	for(int i=1;i<=tot;i++)
		dfs1(rt[i]);
	scanf("%d",&m);
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",&a[i].x,&a[i].k);
		a[i].pa = kthparent(a[i].x, a[i].k);
		vp[a[i].pa].push_back(i);
	}
	for(int i=1;i<=tot;i++)
		dfs(rt[i], 0);
	for(int i=1;i<=m;i++)
		printf("%d%c",a[i].ans," \n"[i==m]);
	return 0;
}
```