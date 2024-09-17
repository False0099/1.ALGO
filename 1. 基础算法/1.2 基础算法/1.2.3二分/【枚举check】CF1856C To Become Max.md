# To Become Max

## 题面翻译

给定两个正整数 $n$ 和 $k$，以及一个长度为 $n$ 的序列 $a$，你可以进行不超过 $k$ 次如下操作（以下两个步骤合称一次操作）：

- 选择一个 $i$ 满足 $1 \le i < n$，且 $a_i \le a_{i + 1}$。

- 将 $a_i$ 增加 $1$。

求操作完成后，$\max \limits_{i = 1} ^ {n} a_i$ 的最大可以是多少。

多测，共 $t$ 组数据。

对于所有数据，保证 $1 \le t \le 100$，$1 \le n, \sum n \le 1000$，$1 \le k, a_i \le 10 ^ 8$。

## 题目描述

You are given an array of integers $ a $ of length $ n $ .

In one operation you:

- Choose an index $ i $ such that $ 1 \le i \le n - 1 $ and $ a_i \le a_{i + 1} $ .
- Increase $ a_i $ by $ 1 $ .

Find the maximum possible value of $ \max (a_1, a_2, \ldots a_n) $ that you can get after performing this operation at most $ k $ times.

## 输入格式

Each test contains multiple test cases. The first line of input contains a single integer $ t $ ( $ 1 \le t \le 100 $ ) — the number of test cases. The description of the test cases follows.

The first line of each test case contains two integers $ n $ and $ k $ ( $ 2 \le n \le 1000 $ , $ 1 \le k \le 10^{8} $ ) — the length of the array $ a $ and the maximum number of operations that can be performed.

The second line of each test case contains $ n $ integers $ a_1, a_2,\ldots, a_n $ ( $ 1 \le a_i \le 10^{8} $ ) — the elements of the array $ a $ .

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 1000 $ .

## 输出格式

For each test case output a single integer — the maximum possible maximum of the array after performing at most $ k $ operations.

## 样例 #1

### 样例输入 #1

```
6
3 4
1 3 3
5 6
1 3 4 5 1
4 13
1 1 3 179
5 3
4 3 2 2 2
5 6
6 5 4 1 5
2 17
3 5
```

### 样例输出 #1

```
4
7
179
5
7
6
```

## 提示

In the first test case, one possible optimal sequence of operations is: $ [\color{red}{1}, 3, 3] \rightarrow [2, \color{red}{3}, 3] \rightarrow [\color{red}{2}, 4, 3] \rightarrow [\color{red}{3}, 4, 3] \rightarrow [4, 4, 3] $ .

In the second test case, one possible optimal sequence of operations is: $ [1, \color{red}{3}, 4, 5, 1] \rightarrow [1, \color{red}{4}, 4, 5, 1] \rightarrow [1, 5, \color{red}{4}, 5, 1] \rightarrow [1, 5, \color{red}{5}, 5, 1] \rightarrow [1, \color{red}{5}, 6, 5, 1] \rightarrow [1, \color{red}{6}, 6, 5, 1] \rightarrow [1, 7, 6, 5, 1] $ .


## 题解
我们本题如果采用二分答案，那么我们的难点就是在于怎么计算我们答案对应得次数。
我们不难发现，如果我们达到最佳，最后形成的应该是一个从左到右依次递减 1 得数列，这样我们就能达到我们的“理论最佳”。
我们考虑在我们的某一个子列中生成我们的最佳数组，我们于是可以考虑 $O(n^2)$ 的枚举我们的子序列的长度，并且求把这一段变得最佳我们所需要的

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

const int N = 1010;
int t, n, k, maxx;
int a[N];

bool check(long long mid)
{	
	for (int i = 1; i < n; i ++ )
	{
		long long cnt = 0, t = mid;
		for (int j = i; j < n; j ++ )
		{
			if(j == n - 1 && t - (long long)a[j] > 1ll * max(0, a[j + 1] - a[j] + 1)) //a[n-1] 需要加的步数不得大于 a[n-1] 最多能加的步数 
			{
				cnt = 1e18;
				break;
			}
			if(t <= 1ll * a[j]) break;
			cnt += (t - 1ll * a[j]);
			t --;
		}
		if(cnt <= 1ll * k) return 1;
	}
	return 0;
}

int main()
{
	in(t);
	while (t -- )
	{
		in(n); in(k);
		for (int i = 1; i <= n; i ++ ) in(a[i]);
		
		maxx = 0;
		for (int i = 1; i <= n; i ++ ) maxx = max(maxx, a[i]);
		
		long long l = (long long)maxx + 1ll, r = 1e18, mid;
		while (l <= r)
		{
			mid = l + r >> 1ll;
			if(check(mid)) l = mid + 1ll;
			else r = mid - 1ll;
		}
		printf("%lld\n", l - 1ll);
	}
	return 0;
}
```