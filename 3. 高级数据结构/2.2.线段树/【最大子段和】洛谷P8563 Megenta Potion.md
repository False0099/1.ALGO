# Magenta Potion

## 题目描述

给定一个长为 $n$ 的整数序列 $a$，其中所有数的绝对值均大于等于 $2$。有 $q$ 次操作，格式如下：

$\texttt{1 i k}$，表示将 $a_i$ 修改为 $k$。保证 $k $ 的绝对值大于等于 $2$。

$\texttt{2 l r}$，考虑 $[l,r]$ 的子区间（包括本身）中乘积最大的的区间乘积 $M$。如果 $M>2^{30}$，输出 `Too large`，否则输出 $M$。特别地，空区间的元素乘积定义为 $1$。

## 输入格式

第一行两个正整数表示 $n,q$。

第二行输入 $n$ 个**整数**表示 $a_i$。

接下来 $q$ 行，每行三个整数表示一次询问，格式见上。

## 输出格式

对于每次 $\tt2$ 操作输出一行表示询问的答案。

## 样例 #1

### 样例输入 #1

```
5 7
2 2 3 4 5
2 1 5
1 3 -3
2 1 5
2 3 3
1 1 100000
1 2 100000
2 1 2
```

### 样例输出 #1

```
240
20
1
Too large
```

## 提示

对于所有的数据，$2\le |a_i|,|k| \le 10^9$，$1 \le n,q \le 2\times 10^5$，$1 \le l \le r \le n$。



$\textsf A$：保证 $a_i,k \ge 2$。

$\textsf B$：保证对于每一组询问，对应的 $r-l \ge 100$。

## 题解
本题的思路是直接求（），我们本题要维护我们的区间最大连续乘是多少，又因为我们可正可负，所以我们可以考虑维护下面几个数值：1. 后缀最大乘积，2. 后缀最小乘积，3. 前缀最大乘积 4. 前缀最小乘积 5.答案

注意，如果我们计算的某一个区间的绝对值已经是超过我们的 $2^{30}$,我们就要直接跳过这个区间，并打上一个标记。或者我们可以更暴力的，采用我们的 `__int128` 来进行我们的计算。

```cpp
#include <bits/stdc++.h>
using namespace std;

#define ll __int128

const int N = 2e5 + 5, INF = 2e9, MOD = 1e9 + 7;

inline ll read()
{
	ll op = 1, x = 0;
	char ch = getchar();
	while ((ch < '0' || ch > '9') && ch != '-') ch = getchar();
	while (ch == '-')
	{
		op = -op;
		ch = getchar();
	}
	while (ch >= '0' and ch <= '9')
	{
		x = (x << (ll)1) + (x << (ll)3) + (ch ^ 48);
		ch = getchar();
	}
	return x * op;
}

inline void write(ll x)
{
	if (x < 0) putchar('-'), x = -x;
	if (x > 9) write(x / 10);
	putchar(x % 10 + '0');
}

int n, q;
ll a[N], nans = LLONG_MIN;
bool flag;

class SegmentTree
{
public:
	struct Node
	{
		int l, r;
		ll lmaxn, rmaxn, mul, res;
		ll lminn, rminn, totalres;
		bool is_bigger;
	}tr[N << 2];
	Node merge(Node x, Node y)
	{
		if (x.l == -1) return y;
		if (y.l == -1) return x;
		Node z;
		z.mul = x.mul * y.mul;
		z.l = x.l, z.r = y.r;
		z.lmaxn = max({x.lmaxn, x.mul * y.lmaxn, x.mul * y.lminn, (ll)1, z.mul});
		z.rmaxn = max({(ll)1, y.rmaxn, y.mul * x.rmaxn, y.mul * x.rminn, z.mul});
		z.res = max({ x.res, y.res, x.rmaxn * y.lmaxn, z.mul, (ll)1 });
		z.lminn = min({x.lminn, x.mul * y.lminn, z.mul, (ll)1, x.mul * y.lmaxn});
		z.rminn = min({y.rminn, y.mul * x.rminn, z.mul, (ll)1, y.mul * x.rmaxn});
		z.totalres = max({x.totalres, y.totalres, (ll)1, z.res, x.rminn * y.lminn});
		if (z.totalres > (__int128)1 << 30)
		{
			z.is_bigger = 1;
		}
		else z.is_bigger = 0;
		z.is_bigger |= (x.is_bigger | y.is_bigger);
		return z;
	}
	void pushup(int u)
	{
		tr[u] = merge(tr[u << 1], tr[u << 1 | 1]);
	}
	void build(int u, int l, int r)
	{
		tr[u] = { l, r, a[l], a[l], a[l], a[l], a[l], a[l], a[l], 0 };
		tr[u].lmaxn = tr[u].rmaxn = tr[u].res = max(tr[u].res, (ll)1);
		tr[u].lminn = tr[u].rminn = min(tr[u].lminn, (ll)1);
		tr[u].totalres = max(tr[u].totalres, (ll)1);
		if (l == r) return;
		int mid = l + r >> 1;
		build(u << 1, l, mid);
		build(u << 1 | 1, mid + 1, r);
		pushup(u);
	}
	void update(int u, int p, ll x)
	{
		if (tr[u].l == tr[u].r)
		{
			tr[u].lmaxn = tr[u].rmaxn = tr[u].res = max(x, (ll)1);
			tr[u].lminn = tr[u].rminn = min(x, (ll)1);
			tr[u].totalres = max(x, (ll)1);
			tr[u].mul = x;
			return;
		}
		int mid = tr[u].l + tr[u].r >> 1;
		if (p <= mid) update(u << 1, p, x);
		else update(u << 1 | 1, p, x);
		pushup(u);
	}
	Node query(int u, int l, int r)
	{
		if (tr[u].l >= l and tr[u].r <= r) 
		{
			return tr[u];
		}
		int mid = tr[u].l + tr[u].r >> 1;
		Node ret;
		ret.l = -1;
		if (l <= mid) ret = query(u << 1, l, r);
		if (r > mid) ret = merge(ret, query(u << 1 | 1, l, r));
		return ret;
	}
}t;

int main()
{
	//freopen("C:\\Users\\60215\\Downloads\\T1ex1.in", "r", stdin);
	//freopen("C:\\Users\\60215\\Downloads\\tt.out", "w", stdout);
	// freopen("*.out", "w", stdout);
	scanf("%d%d", &n, &q);
	for (int i = 1; i <= n; i++) a[i] = read();
	t.build(1, 1, n);
	while (q--)
	{
		int opt;
		scanf("%d", &opt);
		if (opt == 1)
		{
			int x;
			scanf("%d", &x);
			ll y = read();
			t.update(1, x, y);
		}
		else
		{
			int l, r;
			scanf("%d%d", &l, &r);
			SegmentTree::Node ans = t.query(1, l, r);
			if (ans.is_bigger) printf("Too large\n");
			else
			{
				ll res = max((ll)1, ans.totalres);
				write(res);
				printf("\n");
			}
		}
	}
	return 0;
}

```
