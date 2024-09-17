# Sheikh (Easy version)

## 题面翻译

$q$ 次询问，每次求 $[L, R]$ 内任意子区间的和减去该区间的异或值得到的差的最大值，若有多个最大值，取区间长度最短的，若仍有多个区间，任取一个输出即可。在简单版本中，保证 $q = 1$，$L$ = 1，$R = n$。

## 题目描述

This is the easy version of the problem. The only difference is that in this version $ q = 1 $ .

You are given an array of integers $ a_1, a_2, \ldots, a_n $ .

The cost of a subsegment of the array $ [l, r] $ , $ 1 \leq l \leq r \leq n $ , is the value $ f (l, r) = \operatorname{sum}(l, r) - \operatorname{xor}(l, r) $ , where $ \operatorname{sum}(l, r) = a_l + a_{l+1} + \ldots + a_r $ , and $ \operatorname{xor}(l, r) = a_l \oplus a_{l+1} \oplus \ldots \oplus a_r $ ( $ \oplus $ stands for [bitwise XOR](https://en.wikipedia.org/wiki/Bitwise_operation#XOR)).

You will have $ q = 1 $ query. Each query is given by a pair of numbers $ L_i $ , $ R_i $ , where $ 1 \leq L_i \leq R_i \leq n $ . You need to find the subsegment $ [l, r] $ , $ L_i \leq l \leq r \leq R_i $ , with maximum value $ f (l, r) $ . If there are several answers, then among them you need to find a subsegment with the minimum length, that is, the minimum value of $ r - l + 1 $ .

## 输入格式

Each test consists of multiple test cases. The first line contains an integer $ t $ ( $ 1 \leq t \leq 10^4 $ ) — the number of test cases. The description of test cases follows.

The first line of each test case contains two integers $ n $ and $ q $ ( $ 1 \leq n \leq 10^5 $ , $ q = 1 $ ) — the length of the array and the number of queries.

The second line of each test case contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 0 \leq a_i \leq 10^9 $ ) — array elements.

 $ i $ -th of the next $ q $ lines of each test case contains two integers $ L_i $ and $ R_i $ ( $ 1 \leq L_i \leq R_i \leq n $ ) — the boundaries in which we need to find the segment.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

It is guaranteed that $ L_1 = 1 $ and $ R_1 = n $ .

## 输出格式

For each test case print $ q $ pairs of numbers $ L_i \leq l \leq r \leq R_i $ such that the value $ f (l, r) $ is maximum and among such the length $ r - l + 1 $ is minimum. If there are several correct answers, print any of them.

## 样例 #1

### 样例输入 #1

```
6
1 1
0
1 1
2 1
5 10
1 2
3 1
0 2 4
1 3
4 1
0 12 8 3
1 4
5 1
21 32 32 32 10
1 5
7 1
0 1 0 1 0 1 0
1 7
```

### 样例输出 #1

```
1 1
1 1
1 1
2 3
2 3
2 4
```

## 提示

In the first test case, $ f (1, 1) = 0 - 0 = 0 $ .

In the second test case, $ f (1, 1) = 5 - 5 = 0 $ , $ f (2, 2) = 10 - 10 = 0 $ . Note that $ f (1, 2) = (10 + 5) - (10 \oplus 5) = 0 $ , but we need to find a subsegment with the minimum length among the maximum values of $ f (l, r) $ . So, only segments $ [1, 1] $ and $ [2, 2] $ are the correct answers.

In the fourth test case, $ f (2, 3) = (12 + 8) - (12 \oplus 8) = 16 $ .

There are two correct answers in the fifth test case, since $ f (2, 3) = f (3, 4) $ and their lengths are equal.

## 题解
我们首先有结论**我们的在固定左端点的时候，我们的右端点我们渠道我们的最右端一定是最大的**，也就是换句话说，我们有下面的公式恒成立:
$$f(l,r+1)\geq f(l,r)。$$

也就是说，对于沃恩的给定区间上，我们的右端点变化时，我们的函数值是单调递增的。也就是说，我们可以有下面的做法：
1. 我们先去找到我们的目的值，也就是我们的 $f(l_{i},r_{i})$
2. 我们总断电，然后再去通过我们的双指针计算出我们的右端点对应可以渠道什么位置。
```
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1e6 + 10;
inline int read(){
	int r = 0,w = 1;
	char c = getchar();
	while (c < '0' || c > '9'){
		if (c == '-'){
			w = -1;
		}
		c = getchar();
	}
	while (c >= '0' && c <= '9'){
		r = (r << 3) + (r << 1) + (c ^ 48);
		c = getchar();
	}
	return r * w;
}
int n, q, ar[N], sum[N], g[N];//sum：前缀和 g：前缀异或 
int get_sum(int l, int r)
{
	return sum[r] - sum[l - 1] - (g[r] ^ g[l - 1]);//计算差值 
}
signed main()
{
	int _;
	_ = read();
	while (_ --)
	{
		n = read(), q = read();for(int i = 1;i <= n; ++ i) ar[i] = read(), sum[i] = sum[i - 1] + ar[i], g[i] = g[i - 1] ^ ar[i];
		int l = 1, r = 1;
		int res = sum[n] - g[n];
		int ll = read(), rr = read();
		for(int i = 1;i <= n; ++ i)//枚举左端点
		{
			if(r < i) r = i;
			while(r <= n && get_sum(i, r) < res)
			{
				++ r;
			}
            if(r > n) break;
			if(rr - ll + 1 > r - i + 1) ll = i, rr = r;  
		}
		cout << ll << " " << rr << "\n";
	}
	return 0;
}
```