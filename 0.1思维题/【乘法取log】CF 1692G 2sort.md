# 2^Sort

## 题面翻译

给你一个长度为 $n \ (\sum n < 2\cdot 10^5)$ 的数组 $a$，问你在这个数组中，有多少个长度为 $k + 1 \ (1\le k < n)$ 的区间，符合以下的条件：

$$
2^0 \cdot a_i < 2^1 \cdot a_{i + 1} < 2^2 \cdot a_{i + 2} < \dotsi < 2^k \cdot a_{i + k}\\

\footnotesize{注：i 为这个区间开始的位置}
$$

由 [tzyt](https://www.luogu.com.cn/user/394488) 翻译

## 题目描述

Given an array $ a $ of length $ n $ and an integer $ k $ , find the number of indices $ 1 \leq i \leq n - k $ such that the subarray $ [a_i, \dots, a_{i+k}] $ with length $ k+1 $ (not with length $ k $ ) has the following property:

- If you multiply the first element by $ 2^0 $ , the second element by $ 2^1 $ , ..., and the ( $ k+1 $ )-st element by $ 2^k $ , then this subarray is sorted in strictly increasing order.

 More formally, count the number of indices $ 1 \leq i \leq n - k $ such that $ $$$2^0 \cdot a_i < 2^1 \cdot a_{i+1} < 2^2 \cdot a_{i+2} < \dots < 2^k \cdot a_{i+k}. $ $$ $

## 输入格式

The first line contains an integer $ t $ ( $ 1 \leq t \leq 1000 $ ) — the number of test cases.

The first line of each test case contains two integers $ n $ , $ k $ ( $ 3 \leq n \leq 2 \cdot 10^5 $ , $ 1 \leq k < n $ ) — the length of the array and the number of inequalities.

The second line of each test case contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ 1 \leq a_i \leq 10^9 $ ) — the elements of the array.

The sum of $ n $ across all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output a single integer — the number of indices satisfying the condition in the statement.

## 样例 #1

### 样例输入 #1

```
6
4 2
20 22 19 84
5 1
9 5 3 2 1
5 2
9 5 3 2 1
7 2
22 12 16 4 3 22 12
7 3
22 12 16 4 3 22 12
9 3
3 9 12 3 9 12 3 9 12
```

### 样例输出 #1

```
2
3
2
3
1
0
```

## 提示

In the first test case, both subarrays satisfy the condition:

- $ i=1 $ : the subarray $ [a_1, a_2, a_3] = [20,22,19] $ , and $ 1 \cdot 20 < 2 \cdot 22 < 4 \cdot 19 $ .
- $ i=2 $ : the subarray $ [a_2, a_3, a_4] = [22,19,84] $ , and $ 1 \cdot 22 < 2 \cdot 19 < 4 \cdot 84 $ .

 In the second test case, three subarrays satisfy the condition: - $ i=1 $ : the subarray $ [a_1, a_2] = [9,5] $ , and $ 1 \cdot 9 < 2 \cdot 5 $ .
- $ i=2 $ : the subarray $ [a_2, a_3] = [5,3] $ , and $ 1 \cdot 5 < 2 \cdot 3 $ .
- $ i=3 $ : the subarray $ [a_3, a_4] = [3,2] $ , and $ 1 \cdot 3 < 2 \cdot 2 $ .
- $ i=4 $ : the subarray $ [a_4, a_5] = [2,1] $ , but $ 1 \cdot 2 = 2 \cdot 1 $ , so this subarray doesn't satisfy the condition.

## 题解
本题相当于问，我们在原数列中，有多少个连续的数满足 $a_{i+1}>a_{i}*2$,我们需要求出我们的答案。或者我们也可以不等号两侧同时取 log，来帮助我们进行思考。

```cpp
#include<bits/stdc++.h>
#define pb push_back
#define int long long
#define lowbit(x) (x & (-x))
using namespace std;

int n, k, t, now, ans, a[200010];

signed main()
{
	cin >> t;
	while (t--)
	{
		cin >> n >> k;
		for (int i = 1;i <= n;i++)
		cin >> a[i];
		now = 1;
		ans = 0;
		for (int i = 2;i <= n;i++)
		if (a[i] * 2 <= a[i - 1])
		{
			if (i - now >= k)
			{
				ans += i - now - k;
			}
			now = i;
		}//求出符合条件的每一段。
		if (n - now + 1 >= k && a[n] * 2 > a[n - 1])
		ans += n - now + 1 - k;//对于最后一段，不要忘记去统计答案。
		cout << ans << endl;
	}
}
```