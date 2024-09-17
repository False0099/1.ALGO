#异或 #相同数组 #操作数限制
# Powerful Ksenia

## 题面翻译

给 $n$ 个正整数 $a_i$, $1 \le a_i\le10^9$.

每次操作是选三个不同的下标 $i,j,k$ ，让 $a_i,a_j,a_k$ 都变成 $a_i \oplus a_j\oplus a_k$ 也就是这三个数的异或和.

让你判断是否能在 $n$ 次操作内，使这 $n$ 个正整数的值变成相同的.

若能，第一行输出 YES，第二行输出 $m$ 表示操作数两，接下来 $m$ 行每行三个整数，描述一次操作；

若不能，输出 NO.

## 题目描述

Ksenia has an array $ a $ consisting of $ n $ positive integers $ a_1, a_2, \ldots, a_n $ .

In one operation she can do the following:

- Choose three distinct indices $ i $ , $ j $ , $ k $ , and then
- change all of $ a_i, a_j, a_k $ to $ a_i \oplus a_j \oplus a_k $ simultaneously, where $ \oplus $ denotes the [bitwise XOR operation](https://en.wikipedia.org/wiki/Bitwise_operation#XOR).

She wants to make all $ a_i $ equal in at most $ n $ operations, or to determine that it is impossible to do so. She wouldn't ask for your help, but please, help her!

## 输入格式

The first line contains one integer $ n $ ( $ 3 \leq n \leq 10^5 $ ) — the length of $ a $ .

The second line contains $ n $ integers, $ a_1, a_2, \ldots, a_n $ ( $ 1 \leq a_i \leq 10^9 $ ) — elements of $ a $ .

## 输出格式

Print YES or NO in the first line depending on whether it is possible to make all elements equal in at most $ n $ operations.

If it is possible, print an integer $ m $ ( $ 0 \leq m \leq n $ ), which denotes the number of operations you do.

In each of the next $ m $ lines, print three distinct integers $ i, j, k $ , representing one operation.

If there are many such operation sequences possible, print any. Note that you do not have to minimize the number of operations.

## 样例 #1

### 样例输入 #1

```
5
4 2 1 7 2
```

### 样例输出 #1

```
YES
1
1 3 4
```

## 样例 #2

### 样例输入 #2

```
4
10 4 49 22
```

### 样例输出 #2

```
NO
```

## 提示

In the first example, the array becomes $ [4 \oplus 1 \oplus 7, 2, 4 \oplus 1 \oplus 7, 4 \oplus 1 \oplus 7, 2] = [2, 2, 2, 2, 2] $ .

## 题解
首先，当我们的个数为奇数时，我们一定可以找到一个对应的构造：方法如下：
首先，如果序列里除了某个数 $p$ 以外，能够两两配对，使得每对数相等，设我们的 $\frac{n-1}{2}$ 对下标分别是 $(u_{1},v_{1}),(u_{2},v_{2})\dots$,接下来，我们只需要依次操作 $(p,u_{1},v_{1})\dots\left( p,u_{{n-\frac{1}{2}},\dots} \right)$ 即可。这样就能使得我们序列里所有数都等于 $a_{p}$,
但我们一开始并不是一定就是这种状态，我们考虑怎么样才能转移到这种状态，我们可以依次对所有 $i=1,3,5\dots n-2$ 做操作 $(i,i+1,i+1)$,这样我们就能让所有的 $(i,i+1)$ 相等。最后剩下 $p=n$ ，在进行上述操作即可。

当我们的 $n$ 为偶数时，我们发现：**每一次操作，不会改变我们的异或和**，因此，如果我们这 $n$ 个数异或后和不为 0，那么我们一定不能达到我们的目标状态，我们直接输出 false 即可。反之，我们可以采用下面的构造方法：我们随便拿出来一个数，剩下的就变成了我们的 $n-1$ 个操作的方案，这个正是我们奇数个的方案。

于是我们的代码就有下面的形式：
```cpp
// problem: CF1438D
#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define mk make_pair
#define lob lower_bound
#define upb upper_bound
#define fi first
#define se second
#define SZ(x) ((int)(x).size())

typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;

template<typename T> inline void ckmax(T& x, T y) { x = (y > x ? y : x); }
template<typename T> inline void ckmin(T& x, T y) { x = (y < x ? y : x); }

const int MAXN = 1e5;
int n, a[MAXN + 5];
struct Oper_t {
	int i, j, k;
	Oper_t() {}
	Oper_t(int _i, int _j, int _k) { i = _i, j = _j, k = _k; }
};
void solve_odd() {
	cout << "YES" << endl;
	vector<Oper_t> ans;
	for (int i = 1; i <= n - 2; i += 2) {
		ans.pb(Oper_t(i, i + 1, i + 2));
	}
	for (int i = 1; i <= n - 2; i += 2) {
		ans.pb(Oper_t(i, i + 1, n));
	}
	cout << SZ(ans) << endl;
	for (int i = 0; i < SZ(ans); ++i) {
		cout << ans[i].i << " " << ans[i].j << " " << ans[i].k << endl;
	}
}
void solve_even() {
	int xorsum = 0;
	for (int i = 1; i <= n; ++i) xorsum ^= a[i];
	if (xorsum) {
		cout << "NO" << endl;
		return;
	}
	--n;
	solve_odd();
}
int main() {
	cin >> n;
	for (int i = 1; i <= n; ++i) cin >> a[i];
	if (n % 2 == 0) {
		solve_even();
	} else {
		solve_odd();
	}
	return 0;
}

```