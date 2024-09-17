# [ABC 354 F] Useless for LIS

## 题面翻译

- 给定一个长度为 $n$ 的序列 $a$。求出所有 $i$ 使得存在任意一个 $a$ 的最长上升子序列包含 $i$。多测。
- $1 \le T, n, \sum n \le 2 \times 10^5$，$1 \le a_i \le 10^9$。

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc354/tasks/abc354_f

長さ $ N $ の整数列 $ A $ が与えられます。

$ t\ =\ 1,\ 2,\ \dots\ ,N $ について、 $ A_t $ が $ A $ の最長増加部分列に含まれることがあるか判定してください。

$ A_t $ が $ A $ の最長増加部分列に含まれることがあるとは、以下のことをいいます。

- 最長増加部分列の長さを $ L $ とする。各要素が $ 1 $ 以上 $ N $ 以下の単調増加な整数列 $ i\ =\ (i_1,\ i_2,\ \dots\ ,i_L)\ (i_1\ であって以下をすべて満たすものが存在する。 $
  
  
  - $ A_{i_1} $
  - ある $ k\ (1\ \leq\ k\ \leq\ L) $ が存在して $ i_k\ =\ t $ である

$ T $ 個のテストケースが与えられるので、それぞれについて答えを求めてください。

最長増加部分列とは？列 $ A $ の部分列とは $ A $ の要素をいくつか抜き出して元の順に並べてできる列を指します。

列 $ A $ の最長増加部分列とは、 $ A $ の狭義単調増加な部分列のうち列の長さが最大のものを指します。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ T $ $ \mathrm{case}_1 $ $ \mathrm{case}_2 $ $ \vdots $ $ \mathrm{case}_T $

ここで $ \mathrm{case_i} $ は $ i $ 番目のケースの入力を意味する。各ケースは以下の形式で与えられる。

> $ N $ $ A_1 $ $ A_2 $ $ \cdots $ $ A_N $

## 输出格式

以下の形式で出力せよ。

> $ \mathrm{answer}_1 $ $ \mathrm{answer}_2 $ $ \vdots $ $ \mathrm{answer}_T $

ここで $ \mathrm{answer}_i $ は $ i $ 番目のケースの出力を意味する。各ケースについては、次の通りである。

$ A_t $ が $ A $ の最長増加部分列に含まれることがある $ t $ が $ m $ 個存在し、昇順に $ i_1,\ i_2,\ \dots\ ,i_m $ であったとする。このとき、以下の形式で出力せよ。

> $ m $ $ i_1 $ $ i_2 $ $ \cdots $ $ i_m $

## 样例 #1

### 样例输入 #1

```
1
5
2 1 4 5 3
```

### 样例输出 #1

```
4
1 2 3 4
```

## 样例 #2

### 样例输入 #2

```
2
6
2 5 3 4 3 4
5
10000 1000 100 1 10
```

### 样例输出 #2

```
5
1 3 4 5 6
2
4 5
```

## 提示

### 制約

- $ 1\ \leq\ T\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ A_i\ \leq\ 10^9 $
- 全てのテストケースにおける $ N $ の総和は $ 2\ \times\ 10^5 $ 以下

### Sample Explanation 1

最長増加部分列の $ 1 $ つは $ (2,\ 4,\ 5) $ で、長さは $ 3 $ です。$ (1,\ 4,\ 5) $ も最長増加部分列の $ 1 $ つです。しかし、 $ A_5 $ を含む最長増加部分列はありません。 よって、 $ 1,\ 2,\ 3,\ 4 $ を出力します。

## 题解
我们本题首先可以考虑通过我们的树状数组首先求出我们**以 i 为起点的最长 LIS**和**以 i 为终点的最长 LIS**，然后我们有：如果对于一个点，他是我们的毕竟点，那么我们有 $f[i]+g[i]=ans[i]-1$

这样，我们就完成了本题：

```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 1145e4;

int n, len, a[N], f[N], g[N];

struct BIT {
	int tr[N];
	set<int> S;
	inline void modify(const int u, const int x) {
		for (register int i = u; i <= len; i += i & -i)
			tr[i] = max(tr[i], x),
			S.insert(i);
	}
	inline int query(const int u) {
		register int res = 0;
		for (register int i = u; i; i -= i & -i)
			res = max(res, tr[i]);
		return res;
	}
	void clear() {
		for (int i : S) tr[i] = 0;
		S.clear();
	}
}A, B;

int nums[N];

int main() {
	int T; cin >> T;
	while (T -- ) {
		cin >> n;
		for (int i = 1; i <= n; ++ i ) cin >> a[i], nums[i] = a[i];
		
		A.clear(), B.clear();
		
		sort(nums + 1, nums + n + 1);
		len = unique(nums + 1, nums + n + 1) - nums - 1;
		
		int res = 0;
		for (int i = 1; i <= n; ++ i ) {
			a[i] = lower_bound(nums + 1, nums + len + 1, a[i]) - nums;
			f[i] = A.query(a[i] - 1) + 1;
			A.modify(a[i], f[i]);
			res = max(res, f[i]);
		}
		
		for (int i = n; i; -- i ) {
			g[i] = B.query(len - a[i]) + 1;
			B.modify(len - a[i] + 1, g[i]);
			res = max(res, g[i]);
		}
		
		vector<int> ans;
		for (int i = 1; i <= n; ++ i )
			if (f[i] + g[i] - 1 == res) ans.push_back(i);
		
		cout << ans.size() << '\n';
		for (int t : ans) cout << t << ' ';
		puts("");
	} return 0;
}
```