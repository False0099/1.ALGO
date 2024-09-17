# Sum of Two Numbers

## 题面翻译

给定一个 $n$，选取任意满足条件的两个非负整数 $x,y$ ,使得 $x,y$ 满足如下条件：

- $x+y=n$
- $x,y$ 的各位数字之和相差不超过 $1$

多测，共有 $T$ 组数据。

## 题目描述

The sum of digits of a non-negative integer $ a $ is the result of summing up its digits together when written in the decimal system. For example, the sum of digits of $ 123 $ is $ 6 $ and the sum of digits of $ 10 $ is $ 1 $ . In a formal way, the sum of digits of $ \displaystyle a=\sum_{i=0}^{\infty} a_i \cdot 10^i $ , where $ 0 \leq a_i \leq 9 $ , is defined as $ \displaystyle\sum_{i=0}^{\infty}{a_i} $ .

Given an integer $ n $ , find two non-negative integers $ x $ and $ y $ which satisfy the following conditions.

- $ x+y=n $ , and
- The sum of digits of $ x $ and the sum of digits of $ y $ differ by at most $ 1 $ .

It can be shown that such $ x $ and $ y $ always exist.

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10\, 000 $ ).

Each test case consists of a single integer $ n $ ( $ 1 \leq n \leq 10^9 $ )

## 输出格式

For each test case, print two integers $ x $ and $ y $ .

If there are multiple answers, print any.

## 样例 #1

### 样例输入 #1

```
5
1
161
67
1206
19
```

### 样例输出 #1

```
1 0
67 94
60 7
1138 68
14 5
```

## 提示

In the second test case, the sum of digits of $ 67 $ and the sum of digits of $ 94 $ are both $ 13 $ .

In the third test case, the sum of digits of $ 60 $ is $ 6 $ , and the sum of digits of $ 7 $ is $ 7 $ .


## 题解
同时，我们本体也存在一种随机化的做法，我们可以在我们的 $1e9$ 当中随即找到两个数字，然后检查我们的这两个数字的绝对值之差是否是超过我们的 $1e_{9}$ 的，如果是的，我们就直接退出。
```
#include <bits/stdc++.h>

using namespace std;

typedef long long LL;
typedef pair<int, int> PII;

int main()
{
	auto solve = [&]()
	{
		int n;
		cin >> n;
		while (true)
		{
			auto get_dig = [&](int x)
			{
				int res = 0;
				while (x)
				{
					res += x % 10;
					x /= 10;
				}
				return res;
			};

			int x = (LL)rand() * rand() % n + 1;
			int y = n - x;
			if (abs(get_dig(x) - get_dig(y)) <= 1)
				return cout << x << ' ' << y << '\n', 0;
		}
	};

	int T;
	cin >> T;
	while (T --)
		solve();
	return 0;
}

```