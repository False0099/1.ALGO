## 题面翻译

为您提供一个序列 $[a_1,a_2,...,a_n]，$ 并且 $1 \leq a_i \leq 10^9$。设 $S$ 为这列数的和。我们定义一个美丽序列 $b$：

$1.$ 保证 $1 \leq b_i \leq 10^9（1 \leq i \leq n）$

$2.$ 对于每一对相邻的数 $(b_i,b_{i+1})$，要求 $b_i整除b_{i+1}$ 或 $b_{i+1}整除b_i$。

$3.$ $2* \sum\limits_{i=1}^{n} |a_i-b_i| \leq S$

你的任务就是找到任意一个美丽序列并且输出这个序列。
数据范围：$t(1 \leq t \leq 1000),n(2 \leq n \leq50),a_i(1 \leq a_i \leq 10^9),b_i(1 \leq b_i \leq 10^9)。$

## 题目描述

You are given an array $ [a_1, a_2, \dots, a_n] $ such that $ 1 \le a_i \le 10^9 $ . Let $ S $ be the sum of all elements of the array $ a $ .

Let's call an array $ b $ of $ n $ integers beautiful if:

- $ 1 \le b_i \le 10^9 $ for each $ i $ from $ 1 $ to $ n $ ;
- For every pair of adjacent integers from the array $ (b_i, b_{i + 1}) $ , either $ b_i $ divides $ b_{i + 1} $ , or $ b_{i + 1} $ divides $ b_i $ (or both);
- $ 2 \sum \limits_{i = 1}^{n} |a_i - b_i| \le S $ .

Your task is to find any beautiful array. It can be shown that at least one beautiful array always exists.

## 输入格式

The first line contains one integer $ t $ ( $ 1 \le t \le 1000 $ ) — the number of test cases.

Each test case consists of two lines. The first line contains one integer $ n $ ( $ 2 \le n \le 50 $ ).

The second line contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ 1 \le a_i \le 10^9 $ ).

## 输出格式

For each test case, print the beautiful array $ b_1, b_2, \dots, b_n $ ( $ 1 \le b_i \le 10^9 $ ) on a separate line. It can be shown that at least one beautiful array exists under these circumstances. If there are multiple answers, print any of them.

## 样例 #1

### 样例输入 #1

```
4
5
1 2 3 4 5
2
4 6
2
1 1000000000
6
3 4 8 1 2 3
```

### 样例输出 #1

```
3 3 3 3 3
3 6
1 1000000000
4 4 8 1 3 3
```

## 题解
我们不妨从一个二进制的角度来进行考虑，我们对于每一个数字，找到离这个数字最近的一个二的幂次（小于当前数字），我们为什么这样的证明一定是正确的，因为我们满足这个条件的对应的 $b_{i}$,那么一定就会对应的满足：$b_{i}-a_{i}<a_{i}$。也因此，我们一定满足我们的原文中的和的条件。

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,x;
int main()
{
	cin>>t;
	while(t--)
	{
		cin>>n;
		for(int i=1;i<=n;i++)
		{
			cin>>x;
			int ans=1;
			while(abs(x-ans)*2>x) ans*=2;
			cout<<ans<<' ';
		}
		putchar('\n');
	}
	return 0;
}
```