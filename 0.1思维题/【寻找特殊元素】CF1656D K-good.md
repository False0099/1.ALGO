# K-good

## 题面翻译

给定一个整数 $n$，请找出一个大于等于 $2$ 的整数 $k$，使得 $n$ 可以表示成 $k$ 个除以 $k$ 的余数互不相同的正整数之和。

数据范围：

- $t$ 组数据，$1\leqslant t\leqslant 10^5$。
- $2\leqslant n\leqslant 10^{18}$。

Translated by Eason_AC

## 题目描述

We say that a positive integer $ n $ is $ k $ -good for some positive integer $ k $ if $ n $ can be expressed as a sum of $ k $ positive integers which give $ k $ distinct remainders when divided by $ k $ .

Given a positive integer $ n $ , find some $ k \geq 2 $ so that $ n $ is $ k $ -good or tell that such a $ k $ does not exist.

## 输入格式

The input consists of multiple test cases. The first line contains a single integer $ t $ ( $ 1 \leq t \leq 10^5 $ ) — the number of test cases.

Each test case consists of one line with an integer $ n $ ( $ 2 \leq n \leq 10^{18} $ ).

## 输出格式

For each test case, print a line with a value of $ k $ such that $ n $ is $ k $ -good ( $ k \geq 2 $ ), or $ -1 $ if $ n $ is not $ k $ -good for any $ k $ . If there are multiple valid values of $ k $ , you can print any of them.

## 样例 #1

### 样例输入 #1

```
5
2
4
6
15
20
```

### 样例输出 #1

```
-1
-1
3
3
5
```

## 提示

$ 6 $ is a $ 3 $ -good number since it can be expressed as a sum of $ 3 $ numbers which give different remainders when divided by $ 3 $ : $ 6 = 1 + 2 + 3 $ .

 $ 15 $ is also a $ 3 $ -good number since $ 15 = 1 + 5 + 9 $ and $ 1, 5, 9 $ give different remainders when divided by $ 3 $ .

 $ 20 $ is a $ 5 $ -good number since $ 20 = 2 + 3 + 4 + 5 + 6 $ and $ 2,3,4,5,6 $ give different remainders when divided by $ 5 $ .

## 题解
我们发现，偶们因为我们的 $k$ 可以取值到我们的 2，所以我们考虑**以二为特殊元素**，来进行我们的处理。

本题的关键是推导我们的结论，我们首先知道一个数如果可以被分解为 $k-good$ 数，那么一定满足：$(0+1+\dots+k-1)+t*k=n$,化简一下不难看出，我们最后就是要求式子：
$2n=k(2p+k+1)$ 
我们在这里需要用到一个经典技巧，就是把我们的 $k+1+2p$ 和我们的 $k$，看成是我们一个奇数和一个偶数相乘，最后的结果是我们的 $2n$。

也就是说：我们要把 $2n$ 分解为一个奇数一个偶数，两个数相乘得到的结果。而一个数字能够被分解为一个奇数乘上一个偶数，那么一定可以转换为我们的 $2^{k}*(2m+1)$，因此，我们除非一个数是我们的 $2^n$，否则我们一定可以转换为一个奇数乘上一个偶数。

```cpp
#include <bits/stdc++.h>
using namespace std;
signed main()
{
	int tc=1;
	cin>>tc;
	while(tc--){
		long long n,m=2;
		cin>>n;
		while(!(n&1))n>>=1,m<<=1;
		if(n>m)cout<<m<<"\n";
		else if(n>1)cout<<n<<"\n";
		else cout<<"-1\n";
	}
	return 0;
}

```