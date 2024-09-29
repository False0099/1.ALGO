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
本题我们首先注意到，如果我们的每一个数位之间存在进位，那么我们的情况会比较复杂，我们不妨**从简单的情况开始下手**，例如我们可以先从我们的两个加起来是不进位这一种情况来优先考虑，首先我们就有：
我们的 $a_{i}+b_{i}=c_{i}$,并且我们还需要我们的 $a_{i}$ 和我们的 $b_{i}$ 的绝对值差不超过 1，我们**想到平分思想**首先，如果我们的和是一个偶数，显然，我们只需要取我们的 $\frac{a}{2}$ 和 $\frac{a}{2}$ 即可。

考虑我们是一个奇数的情况，我们考虑对我们的每一个位置都去进行拆分，首先我们就有我们可以把我们的没一个位子拆分为一个偶数加上一个奇数，然后我们就必然会产生 1 的绝对差。这个时候，我们如果还有下一位，那么我们只需要**交叉**即可抵消掉我们之前的 1 的绝对值之差。

综上，我们有结果：
```
#include <bits/stdc++.h>
#define re register

using namespace std;

int T;
string n;

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> T;
	while (T--){
		int x = 0,y = 0;
		bool r = false;
		cin >> n;
		for (re int i = 0;n[i];i++){
			int num = n[i] - '0';
			if (num & 1){
				if (r){
					x = x * 10 + num / 2 + 1;
					y = y * 10 + num / 2;
				}
				else{
					x = x * 10 + num / 2;
					y = y * 10 + num / 2 + 1;
				}
				r ^= 1;
			}
			else{
				x = x * 10 + num / 2;
				y = y * 10 + num / 2;
			}
		}
		cout << x << " " << y << "\n";
	}
	return 0;
}
```