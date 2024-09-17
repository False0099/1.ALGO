#特殊限制 #根号 #全排列 #找规律 #递归
# Build Permutation

## 题面翻译

我们认为一个序列 $a$ 是优秀的，当且仅当其任意一个元素加上其下标是完全平方数。

形式化地， $\forall i\in[0,n), \sqrt{a_i+i}\in\mathbb{N}$ 。

给定 $n$，求 $0$ 至 $n-1$ 的一个优秀排列，或者判断不存在这样的排列。

值得注意的是，本题中特殊规定下标从 $0$ 开始，到 $n-1$ 结束。

多测，$\sum n\leq10^5$ 。

## 题目描述

A  $ \mathbf{0} $ -indexed array $ a $ of size $ n $ is called good if for all valid indices $ i $ ( $ 0 \le i \le n-1 $ ), $ a_i + i $ is a perfect square $ ^\dagger $ .

Given an integer $ n $ . Find a permutation $ ^\ddagger $ $ p $ of $ [0,1,2,\ldots, n-1] $ that is good or determine that no such permutation exists.

 $ ^\dagger $ An integer $ x $ is said to be a perfect square if there exists an integer $ y $ such that $ x = y^2 $ .

 $ ^\ddagger $ An array $ b $ is a permutation of an array $ a $ if $ b $ consists of the elements of $ a $ in arbitrary order. For example, $ [4,2,3,4] $ is a permutation of $ [3,2,4,4] $ while $ [1,2,2] $ is not a permutation of $ [1,2,3] $ .

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

The only line of each test case contains a single integer $ n $ ( $ 1 \le n \le 10^5 $ ) — the length of the permutation $ p $ .

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 10^5 $ .

## 输出格式

For each test case, output $ n $ distinct integers $ p_0, p_1, \dots, p_{n-1} $ ( $ 0 \le p_i \le n-1 $ ) — the permutation $ p $ — if the answer exists, and $ -1 $ otherwise.

## 样例 #1

### 样例输入 #1

```
3
3
4
7
```

### 样例输出 #1

```
1 0 2 
0 3 2 1 
1 0 2 6 5 4 3
```

## 提示

In the first test case, we have $ n=3 $ . The array $ p = [1, 0, 2] $ is good since $ 1 + 0 = 1^2 $ , $ 0 + 1 = 1^2 $ , and $ 2 + 2 = 2^2 $

In the second test case, we have $ n=4 $ . The array $ p = [0, 3, 2, 1] $ is good since $ 0 + 0 = 0^2 $ , $ 3 + 1 = 2^2 $ , $ 2+2 = 2^2 $ , and $ 1+3 = 2^2 $ .

## 题解
这一道题一开始看起来有点令人无从下手，不妨先手算，从小的 n 出发找规律。

|n|a0​|a1​|a2​|a3​|a4​|a5​|a6​|a7​|a8​|a9​|
|---|---|---|---|---|---|---|---|---|---|---|
|1|0||||||||||
|2|1|0|||||||||
|3|1|0|2||||||||
|4|0|3|2|1|||||||
|5|4|3|2|1|0||||||
|6|0|3|2|1|5|4|||||
|7|1|0|2|6|5|4|3||||
|8|1|0|7|6|5|4|3|2|||
|9|0|8|7|6|5|4|3|2|1||
|10|9|8|7|6|5|4|3|2|1|0|

发现什么了吗？

最显然地，若 n 为完全平方数 +1，那么 a 为一个降序序列，从n−1 一直到 0。

再观察一下，可以发现当 n=6 时前 4 项和 n=4 的情况一样，接下来为从 5 开始的降序序列； n=7 时前 3 项和 n=3 的情况一样，接下来为从 6 开始的降序序列，以此类推……直到 n=9 时前 1 项和 n=1 时相同。

那么我们就可以用递归的方法来解决这道题了。对于 n，首先找到其降序序列的起始点应该为2−n+1；对于前面的部分递归处理即可。

代码：

```cpp
#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 1e5+10;

int ans[N];

void solve(int n) {
	if (n == 1) {ans[0] = 0; return ;}
	if (n == (int)sqrt(n)*(int)sqrt(n)) {ans[0] = 0; for (int i = 1; i < n; ++i) ans[i] = n-i; return ;}
	if (n == (int)sqrt(n)*(int)sqrt(n)+1) {for (int i = 0; i < n; ++i) ans[i] = n-i-1; return ;}
	 
	int begin = ((int)sqrt(n)+1)*((int)sqrt(n)+1) - n + 1;
	for (int i = begin; i < n; ++i) ans[i] = n-1-(i-begin);
	solve(begin);
}

int main() {
	int t;
	scanf("%d", &t);
	while (t -- ) {
		int n;
		scanf("%d", &n);
		solve(n);
		for (int i = 0; i < n; ++i) printf("%d ", ans[i]);
		puts("");
	}
	return 0;
}
```