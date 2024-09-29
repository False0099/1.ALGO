# [ABC 351 F] Double Sum

## 题面翻译

给定一个非负整数数列 $A\ =\ (A_1,\ A_2,\ \dots,\ A_N)$ 。请计算整个数列中所有逆序对的差之和，即：

$ \displaystyle\ \sum_{i=1}^N\ \sum_{j=i+1}^N\ \max (A_j\ -\ A_i,\ 0) $

数据保证答案不超过 $ 2^{63} $

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc351/tasks/abc351_f

整数列 $ A\ =\ (A_1,\ A_2,\ \dots,\ A_N) $ が与えられます。  
 次の式を計算してください。

$ \displaystyle\ \sum_{i=1}^N\ \sum_{j=i+1}^N\ \max (A_j\ -\ A_i,\ 0) $

なお、制約下において答えが $ 2^{63} $ 未満となることは保証されています。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ N $ $ A_1 $ $ A_2 $ $ \dots $ $ A_N $

## 输出格式

式の値を出力せよ。

## 样例 #1

### 样例输入 #1

```
3
2 5 3
```

### 样例输出 #1

```
4
```

## 样例 #2

### 样例输入 #2

```
10
5 9 3 0 4 8 7 5 4 0
```

### 样例输出 #2

```
58
```

## 提示

### 制約

- $ 2\ \leq\ N\ \leq\ 4\ \times\ 10^5 $
- $ 0\ \leq\ A_i\ \leq\ 10^8 $
- 入力される値は全て整数
 
### Sample Explanation 1

$ (i,\ j)\ =\ (1,\ 2) $ のとき $ \max (A_j\ -\ A_i,\ 0)\ =\ \max (3,\ 0)\ =\ 3 $ です。 $ (i,\ j)\ =\ (1,\ 3) $ のとき $ \max (A_j\ -\ A_i,\ 0)\ =\ \max (1,\ 0)\ =\ 1 $ です。 $ (i,\ j)\ =\ (2,\ 3) $ のとき $ \max (A_j\ -\ A_i,\ 0)\ =\ \max (-2,\ 0)\ =\ 0 $ です。 これらを足し合わせた $ 3\ +\ 1\ +\ 0\ =\ 4 $ が答えとなります。

## 题解
我们本体是一个典中典的逆序对问题，因为我们要求我们的逆序对个数有多少个，于是，我们就可以考虑到我们的每一个数上，计算这一个数对我们的答案的贡献是多少。

考虑到 $\forall i<j$,只有 $A_i\leq A_j$ 才会产生贡献。所以可以维护对于每一个 $A_i$ 能产生贡献的 $A_j$。这时可以相当排序，并记录后缀和。但是排完序之后怎么处理 $A_i\leq A_j$,但是 $j<i$ 的情况呢？这时可以考虑开两个后缀和，$sum1$ 记录后面的总贡献，$sum2$ 记录后面能产生贡献的数的个数。记此时的数为 $A_i$,那么这部分的贡献就是 $sum1-sum2\times A_i$。


```
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 400005;
int n, a[N], b[N], d[N];
ll ans;
struct BIT {
	ll c[N];
	void update(int x, int d) { while (x <= n) c[x] += d, x += x & -x; }
	ll query(int x) { ll ans = 0; while (x) ans += c[x], x -= x & -x; return ans; }
} t1, t2;
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]), b[i] = d[i] = a[i];
	sort(b + 1, b + 1 + n);
	int len = unique(b + 1, b + 1 + n) - b - 1;
	for (int i = 1; i <= n; i++) d[i] = lower_bound(b + 1, b + 1 + len, d[i]) - b;
	for (int i = n; i >= 1; i--) {
		ll tmp1 = t1.query(len) - t1.query(d[i]);
		ll tmp2 = t2.query(len) - t2.query(d[i]);
		ans += tmp2 - tmp1 * a[i];
		t1.update(d[i], 1);
		t2.update(d[i], a[i]);
	}
	printf("%lld", ans);
}

```