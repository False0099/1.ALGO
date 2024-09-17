# [ABC 327 F] Apples

## 题面翻译

## 问题描述

有几棵苹果树排在一条数线上，$N$ 个苹果从树上掉下来。  
具体地说，每个 $1\leq i\leq N$ 都有一个苹果在时间 $T_i$ 落在坐标 $X_i$ 处。

高桥有一个耐久度为 $D$、长度为 $W$ 的篮子，他可以做以下动作**次**。

> 选择正整数 $S$ 和 $L$。他在 $S-0.5$ 时将篮子放在 $L-0.5\leq x\leq L+W-0.5$ 范围内，并在 $S+D-0.5$ 时将其取回。他可以得到从放置篮子到取回篮子这段时间内掉落在篮子覆盖范围内的所有苹果。

篮子放好后他不能移动，取回后也不能再放。  
求他能得到的苹果的最大数量。

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc327/tasks/abc327_f

数直線上にりんごの木が並んでおり、 $ N $ 個のりんごが木から落ちてきます。  
具体的には $ 1\leq\ i\leq\ N $ について、時刻 $ T_i $ に座標 $ X_i $ にりんごが落ちてきます。

高橋君は耐久性が $ D $ , 長さ $ W $ のカゴを持っており、**一度だけ** 次の行動を取ることができます。

> 正整数 $ S $, $ L $ を選ぶ。高橋君は時刻 $ S-0.5 $ に $ L-0.5\leq\ x\leq\ L+W-0.5 $ の範囲を覆うようにカゴを設置し、時刻 $ S+D-0.5 $ に回収する。高橋君はカゴを設置してから回収するまでの間に、カゴが設置されていた範囲に落ちてきたりんごをすべて得ることができる。

高橋君は一度設置したカゴを動かしたり、回収したカゴを再度設置することはできません。  
高橋君が得られるりんごの数の最大値を求めてください。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ N $ $ D $ $ W $ $ T_1 $ $ X_1 $ $ T_2 $ $ X_2 $ $ \vdots $ $ T_N $ $ X_N $

## 输出格式

高橋君が得られるりんごの数の最大値を出力せよ。

## 样例 #1

### 样例输入 #1

```
8 4 3
1 1
3 4
6 4
5 2
4 2
4 3
5 5
7 3
```

### 样例输出 #1

```
5
```

## 提示

### 制約

- $ 1\ \leq\ N\leq\ 2\times\ 10^5 $
- $ 1\ \leq\ D\leq\ 2\times\ 10^5 $
- $ 1\ \leq\ W\leq\ 2\times\ 10^5 $
- $ 1\ \leq\ T_i\leq\ 2\times\ 10^5 $
- $ 1\ \leq\ X_i\leq\ 2\times\ 10^5 $
- $ (T_i, X_i) $ はすべて異なる。
- 入力はすべて整数

### Sample Explanation 1

高橋君は $ S=3 $, $ L=2 $ を選ぶと、時刻 $ 2.5 $ から $ 6.5 $ までカゴを $ 1.5\leq\ x\leq\ 4.5 $ の範囲に設置します。このとき、 - 時刻 $ T_2=3 $ に 座標 $ X_2=4 $ に落ちてくるりんご - 時刻 $ T_3=6 $ に 座標 $ X_3=4 $ に落ちてくるりんご - 時刻 $ T_4=5 $ に 座標 $ X_4=2 $ に落ちてくるりんご - 時刻 $ T_5=4 $ に 座標 $ X_5=2 $ に落ちてくるりんご - 時刻 $ T_6=4 $ に 座標 $ X_6=3 $ に落ちてくるりんご の $ 5 $ 個のりんごを得ることができます。 どのように行動しても $ 6 $ 個以上のりんごを得ることはできないため、$ 5 $ を出力します。


## 题解
我们这一题相当于问我们的一个二维数点问题，问我们在边长为 $n,m$ 的矩形能够获得的最大权值是多少，这里我们显然可以用我们的二维数点问题来解决：即先把我们的二维转化为一维，然后再去计算我们所有位置中的最大值是多少。把我们的每一个星星看成两个区间修改。
```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 2e5 + 10;

int n, d, w, res;
pair<int, int> a[N];

struct Tree
{
	int l, r, v, add;
}tr[N << 2];

#define ls (u << 1)
#define rs (u << 1 | 1)

void pushup(int u)
{
	tr[u].v = max(tr[ls].v, tr[rs].v);
}

void calc(int u, int x)
{
	tr[u].add += x;
	tr[u].v += x;
}

void pushdown(int u)
{
	calc(ls, tr[u].add);
	calc(rs, tr[u].add);
	tr[u].add = 0;
}

void build(int u, int l, int r)
{
	tr[u] = {l, r, 0, 0};
	if (l != r)
	{
		int mid = l + r >> 1;
		build(ls, l, mid), build(rs, mid + 1, r);
		pushup(u);
	}
}

void modify(int u, int l, int r, int x)
{
	if (tr[u].l >= l && tr[u].r <= r) calc(u, x);
	else
	{
		int mid = tr[u].l + tr[u].r >> 1;
		pushdown(u);
		if (l <= mid) modify(ls, l, r, x);
		if (r > mid) modify(rs, l, r, x);
		pushup(u);
	}
}

int query(int u, int l, int r)
{
	if (tr[u].l >= l && tr[u].r <= r) return tr[u].v;
	int mid = tr[u].l + tr[u].r >> 1, res = -2e9;
	if (l <= mid) res = query(ls, l, r);
	if (r > mid) res = max(res, query(rs, l, r));
	return res;
}

int main()
{
	cin >> n >> d >> w;
	
	for (int i = 1; i <= n; ++ i )
		cin >> a[i].first >> a[i].second;
	
	sort(a + 1, a + n + 1);
	
	build(1, 1, N - 1);

	for (int i = 1, j = 1; j <= n; ++ j )
	{
		modify(1, max(1, a[j].second - w + 1), a[j].second, 1);
		
		while (i <= j && a[j].first - a[i].first + 1 > d)
			modify(1, max(1, a[i].second - w + 1), a[i].second, -1),
			++ i;
		
		if (a[j].first - a[i].first + 1 <= d)
			res = max(res, query(1, 1, N - 1));
	}
	
	cout << res;
	return 0;
}
```