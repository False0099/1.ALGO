# Sereja and Swaps

## 题面翻译

给一个长为 n 的序列，以及交换次数 k，每次可以在原先的序列中任意交换两个数交换后找一个最大子串和，输出其可能的最大值。 
1 <= n <= 200; 1 <=k <=10

## 题目描述

As usual, Sereja has array $ a $ , its elements are integers: $ a[1], a[2],..., a[n] $ . Let's introduce notation:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF425A/32568eeb8040eb1aa136af55c788f7e656cb44a9.png)A swap operation is the following sequence of actions:

- Choose two indexes $ i, j $ $ (i≠j) $ ;
- Perform assignments $ tmp=a[i], a[i]=a[j], a[j]=tmp $ .

What maximum value of function $ m (a) $ can Sereja get if he is allowed to perform at most $ k $ swap operations?

## 输入格式

The first line contains two integers $ n $ and $ k $ $ (1<=n<=200; 1<=k<=10) $ . The next line contains $ n $ integers $ a[1] $ , $ a[2] $ , $ ... $ , $ a[n] $ $ (-1000<=a[i]<=1000) $ .

## 输出格式

In a single line print the maximum value of $ m (a) $ that Sereja can get if he is allowed to perform at most $ k $ swap operations.

## 样例 #1

### 样例输入 #1

```
10 2
10 -1 2 2 2 2 2 2 -1 10
```

### 样例输出 #1

```
32
```

## 样例 #2

### 样例输入 #2

```
5 10
-1 -1 -1 -1 -1
```

### 样例输出 #2

```
-1
```

## 题解
我们本题的思路是：因为我们我们不能通过任何方法确定我们最后的最大子段和是哪一段，所以我们的思路一是通过**枚举我们的区间**，假设我们把这一段作为我们的最大子段和，我们的答案是多少，因为我们会枚举所有的区间，所以我们不需要担心我们的时间复杂度。

另外，在我们固定了一个区间的情况下，我们就相对来说比较好想到我们的贪心，我们把我们的区间内的最小数和我们的区间外的最大数进行交换，直到我们的区间内的最小数大于等于我们的区间外的最大树或者我们的交换次数已经用完。

我们每一次就统计我们的答案，然后再去跟我们原来的答案进行计算比较即可。

而对于我们的实现，我们有两种思路，我们的第一种思路是我们每一次枚举我们的区间后，把我们的在区间内的数字进行排序，然后把我们的区间外的数字也进行排序，这样，我们就可以以 $o(n^3k)$ 的时间复杂度结束本题。

```cpp
#include <set>
#include <vector>
#include <stdio.h>
#include <algorithm>
using namespace std;
int n, k, a[210], b[210], c(-2e5); // b 记录 a 的前缀和，c 记录答案
#define ins insert
#define lb lower_bound
#define out_ins(i) out.ins(lb(out.begin(), out.end(), a[i], greater<int>()), a[i]); \
			if (out.size() > k) out.pop_back() // 在 out 中插入 a[i]
int main()
{
	scanf("%d%d", &n, &k); 
	for (int i(1); i <= n; ++i) { scanf("%d", &a[i]); b[i] = a[i] + b[i - 1]; }
	for (int l(1); l <= n; ++l)
	{
		multiset<int> in; vector<int> out;
		for (int i(l); i <= n; ++i) in.ins(a[i]);
		for (int i(1); i < l; ++i) { out_ins(i); }
		for (int r(n); r >= l; --r)
		{
			int p(0), d(b[r] - b[l - 1]); // p 代表 out 中的指针，d 记录 [l, r] 的答案
			for (int i : in)
			{
				if (p == out.size()) break;
				if (out[p] <= i) break; // 调换 in[p] 与 out[p] 不会优化答案，跳出循环
				d += out[p++] - i;
			}
			if (d > c) c = d;
			in.erase(in.lb(a[r]));
			out_ins(r);
		}
	}
	printf("%d\n", c);
	return 0;
} 

```