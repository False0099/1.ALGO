
# Permutations & Primes

## 题面翻译

你需要构造一个长度为 $n$ 的序列，使其满足以下条件：
- 包含 $1\sim n$ 的所有数
- 最大化满足如下条件的 $(l,r)$ 的对数：$1\leq l\leq r\leq n$ 且 $\operatorname{MEX}(a_l,a_{l+1}\dots a_{r-1},a_r)$ 为质数

构造任意一种即可。

共 $T$ 组数据。

by @ [Larryyu](https://www.luogu.com.cn/user/475329)

## 题目描述

You are given a positive integer $ n $ .

In this problem, the $ \operatorname{MEX} $ of a collection of integers $ c_1, c_2,\dots, c_k $ is defined as the smallest positive integer $ x $ which does not occur in the collection $ c $ .

The primality of an array $ a_1,\dots, a_n $ is defined as the number of pairs $ (l, r) $ such that $ 1 \le l \le r \le n $ and $ \operatorname{MEX}(a_l,\dots, a_r) $ is a prime number.

Find any permutation of $ 1,2,\dots, n $ with the maximum possible primality among all permutations of $ 1,2,\dots, n $ .

Note:

- A prime number is a number greater than or equal to $ 2 $ that is not divisible by any positive integer except $ 1 $ and itself. For example, $ 2,5,13 $ are prime numbers, but $ 1 $ and $ 6 $ are not prime numbers.
- A permutation of $ 1,2,\dots, n $ is an array consisting of $ n $ distinct integers from $ 1 $ to $ n $ in arbitrary order. For example, $ [2,3,1,5,4] $ is a permutation, but $ [1,2,2] $ is not a permutation ( $ 2 $ appears twice in the array), and $ [1,3,4] $ is also not a permutation ( $ n=3 $ but there is $ 4 $ in the array).

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10^4 $ ). The description of the test cases follows.

The only line of each test case contains a single integer $ n $ ( $ 1 \le n \le 2 \cdot 10^5 $ ).

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output $ n $ integers: a permutation of $ 1,2,\dots, n $ that achieves the maximum possible primality.

If there are multiple solutions, print any of them.

## 样例 #1

### 样例输入 #1

```
3
2
1
5
```

### 样例输出 #1

```
2 1
1
5 2 1 4 3
```

## 提示

In the first test case, there are $ 3 $ pairs $ (l, r) $ with $ 1 \le l \le r \le 2 $ , out of which $ 2 $ have a prime $ \operatorname{MEX}(a_l,\dots, a_r) $ :

- $ (l, r) = (1,1) $ : $ \operatorname{MEX}(2) = 1 $ , which is not prime.
- $ (l, r) = (1,2) $ : $ \operatorname{MEX}(2,1) = 3 $ , which is prime.
- $ (l, r) = (2,2) $ : $ \operatorname{MEX}(1) = 2 $ , which is prime.

 Therefore, the primality is $ 2 $ .In the second test case, $ \operatorname{MEX}(1) = 2 $ is prime, so the primality is $ 1 $ .

In the third test case, the maximum possible primality is $ 8 $ .


## 题解
注意：**1 不是质数**！我们需要考虑 1 放在什么位置，才能保证**尽可能多**的被覆盖，首先，1 如果放在头和尾，那么我们这个数被选中的可能性肯定是不如放在我们的中间的。我们放在中间才可能。
其次，我们考虑 2 的位置，2 是一个质数，那么这个数字应该**尽可能少**的出现在我们的区间段中，所以我们最好就是把这个元素放在我们的尾部。

同理，我们考虑 3 的位置，3 是一个质数，我们这个数字应该**尽可能少**的出现在我们的区间段中，所以我们最好就是把这个元素放在我们的尾部。

综上，我们的构造方案就是把 1 放中间，2，3 放两边，所以我们就把我们的 2，3 放在两端。其他位置我们就随便放就行了。

```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
	int t,n;
	cin>>t;
	while(t--)
	{
		cin>>n;
		if(n==1)//特判
		{
			cout<<1<<endl;
			continue;
		}
		if(n==2)
		{
			cout<<"1 2"<<endl;
			continue;
		}
		if(n==3)
		{
			cout<<"2 1 3"<<endl;
			continue;
		}
		if(n==4)
		{
			cout<<"3 1 4 2"<<endl;
			continue;
		}
		cout<<"2 ";//最小质数
		for(int i=1;i<=(n-3)/2;i++) cout<<3+i<<' ';
		cout<<"1 ";//1在中间
		for(int i=4+(n-3)/2;i<=n;i++) cout<<i<<' ';
		cout<<"3"<<endl;//次小质数
	}
	return 0;
} 
```