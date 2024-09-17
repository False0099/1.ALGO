# Maximum AND

## 题面翻译

## 题目描述

给出两个长度为 $n$ 的数组 $a,b$ ，规定 $f(a,b)$ 表示以下操作：

1. 创建一个长度为 $n$ 的 $c$ 数组，满足 $c_i=a_i \oplus b_i$ （此处的 $\oplus$ 表示[按位异或](https://baike.baidu.com/item/%E5%BC%82%E6%88%96/10993677?fr=aladdin)）。
2. 则 $f(a, b) = c_1\space\& c_2\space\& \cdots \& c_n$。

你可以将 $b$ 数组进行任意的排列（包括保留原始情况），试求出最大的 $f(a,b)$ 。

## 输入格式
第一行一个 $t\ (1\le t \le 10^4)$ ，表示数据组数。

对于每组数据：
	
第一行一个 $n\ (1 \le n \le 10^5)$ ，表示 $a,b$ 数组的长度。

第二行 $n$ 个自然数 $a_1,a_2......a_n(1 \le a_i \lt 2^{30})$

第三行 $n$ 个自然数 $b_1,b_2......b_n(1 \le b_i \lt 2^{30})$

数据保证单个数据测试点内，所有 $n$ 之和不超过 $10^5$.

## 输出格式
对于每一个测试点，一行一个正整数表示     $f(a,b)$ 的最大值。

## 题目描述

You are given two arrays $ a $ and $ b $ , consisting of $ n $ integers each.

Let's define a function $ f (a, b) $ as follows:

- Let's define an array $ c $ of size $ n $ , where $ c_i = a_i \oplus b_i $ ( $ \oplus $ denotes bitwise XOR);
- the value of the function is $ c_1 \mathbin{\&} c_2 \mathbin{\&} \cdots \mathbin{\&} c_n $ (i.e. bitwise AND of the entire array $ c $ ).

Find the maximum value of the function $ f (a, b) $ if you can reorder the array $ b $ in an arbitrary way (leaving the initial order is also an option).

## 输入格式

The first line contains one integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

The first line of each test case contains one integer $ n $ ( $ 1 \le n \le 10^5 $ ) — the size of arrays $ a $ and $ b $ .

The second line contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ 0 \le a_i < 2^{30} $ ).

The third line contains $ n $ integers $ b_1, b_2, \dots, b_n $ ( $ 0 \le b_i < 2^{30} $ ).

The sum of $ n $ over all test cases does not exceed $ 10^5 $ .

## 输出格式

For each test case print one integer — the maximum value of the function $ f (a, b) $ if you can reorder the array $ b $ in an arbitrary way.

## 样例 #1

### 样例输入 #1

```
3
5
1 0 0 3 3
2 3 2 1 0
3
1 1 1
0 0 3
8
0 1 2 3 4 5 6 7
7 6 5 4 3 2 1 0
```

### 样例输出 #1

```
2
0
7
```

## 题解
我们本题要求我们的和值最大，对于和最大的问题，我们的想法一般是按位贪心，每一次优先考虑能否满足让我们的最高位为 1.

这里，我们的想法就是把我们的 1 数组按照从小到大排序，并且钦定我们的对应关系就是我们排序的对应关系。然我们的 2 数组按照从大到小排序。如果我们满足：每一位上的异或值都为 1，那么我们就认为这个二进制数有贡献。**并且，我们这个位置正好把我们的元素分成了两个集合，一个集合内我们的元素全都为 1，另一个集合内全都为 0**。

这样，我们考虑下一位时，我们只需要分类讨论，如果我们前一位已经匹配，那么我们就要再保留前一位顺序的基础上，再去匹配其他位置。
如果我们这一位没有匹配，我们则需要把当前位推平（赋值为 1），然后我们再去排序匹配，这样我们才能得到我们的贪心最大值。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 100005
int t,n,a[N],b[N],ans;
bool check(int x)
{
	vector<int> u,v;
	for(int i=1;i<=n;i++)
	{
		u.push_back(a[i]&x);
		v.push_back((b[i]&x)^x);
	}
	sort(u.begin(),u.end());
	sort(v.begin(),v.end());
	return u==v;
}
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		ans=0;
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
			scanf("%d",&a[i]);
		for(int i=1;i<=n;i++)
			scanf("%d",&b[i]);
		for(int i=29;i>=0;i--)
		{
			if(check(ans|(1<<i)))
				ans|=(1<<i);
		}
		printf("%d\n",ans);
	}
	return 0;
}
```