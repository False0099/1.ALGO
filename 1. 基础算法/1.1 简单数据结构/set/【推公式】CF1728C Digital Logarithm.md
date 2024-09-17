#集合增删

# Digital Logarithm

## 题面翻译

### 题目大意

我们定义 $f(x)$ 表示取出 $x$ 在**十进制**下的位数。( 如 $f(114514) = 6, \; f(998244353) = 9$ )。形式化讲，就是 $f(x) = \lfloor \log_{10} x \rfloor + 1$。

给定两个数组 $a$ 和 $b$，求执行若干次以下操作后使得 $a$ 和 $b$ **排序后**相等的最小操作次数。

操作方法如下：

- 选择一个下标 $i$，将 $a_i$ 赋值为 $f(a_i)$ **或者**将 $b_i$ 赋值为 $f(b_i)$。

### 输入格式

第一行一个整数 $T \; (1 \leqslant T \leqslant 10^4)$ 表示测试样例组数。

对于每组测试样例，第一行为一个整数 $n \; (1 \leqslant n \leqslant 2 \cdot 10^5)$ 表示数组长度。

接下来的两行分别有 $n$ 个整数，表示数组 $a$ 和 $b \; (1 \leqslant a_i,b_i < 10^9)$。

数据保证 $\sum n \leqslant 2 \cdot 10^5$

### 输出格式

对于每组测试样例，输出包含一行一个整数，表示最小操作次数。

$Translated \; by \; Zigh$

## 题目描述

Let's define $ f (x) $ for a positive integer $ x $ as the length of the base-10 representation of $ x $ without leading zeros. I like to call it a digital logarithm. Similar to a digital root, if you are familiar with that.

You are given two arrays $ a $ and $ b $ , each containing $ n $ positive integers. In one operation, you do the following:

1. Pick some integer $ i $ from $ 1 $ to $ n $ ;
2. Assign either $ f (a_i) $ to $ a_i $ or $ f (b_i) $ to $ b_i $ .

Two arrays are considered similar to each other if you can rearrange the elements in both of them, so that they are equal (e. g. $ a_i = b_i $ for all $ i $ from $ 1 $ to $ n $ ).

What's the smallest number of operations required to make $ a $ and $ b $ similar to each other?

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of testcases.

The first line of the testcase contains a single integer $ n $ ( $ 1 \le n \le 2 \cdot 10^5 $ ) — the number of elements in each of the arrays.

The second line contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ 1 \le a_i < 10^9 $ ).

The third line contains $ n $ integers $ b_1, b_2, \dots, b_n $ ( $ 1 \le b_j < 10^9 $ ).

The sum of $ n $ over all testcases doesn't exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each testcase, print the smallest number of operations required to make $ a $ and $ b $ similar to each other.

## 样例 #1

### 样例输入 #1

```
4
1
1
1000
4
1 2 3 4
3 1 4 2
3
2 9 3
1 100 9
10
75019 709259 5 611271314 9024533 81871864 9 3 6 4865
9503 2 371245467 6 7 37376159 8 364036498 52295554 169
```

### 样例输出 #1

```
2
0
2
18
```

## 提示

In the first testcase, you can apply the digital logarithm to $ b_1 $ twice.

In the second testcase, the arrays are already similar to each other.

In the third testcase, you can first apply the digital logarithm to $ a_1 $ , then to $ b_2 $ .

## 题解
因为我们这一题涉及到我们的**集合删数**，所以我们用我们的**multiset**能够很好的模拟我们的这个删除的操作。或者，我们也可以用我们的优先队列来模拟我们的整个过程，两个相比，我们的 `multiset` 可以访问任意位置，而我们的 priority_queue 相对来说不能，但是我们的代码也更加简单一点。

于是，我们这一题就可以通过我们的优先队列来处理，我们每一次都取我们的队列中的最大值，然后比较两个是否相同，相同就两个都弹出，否则，我们就选取我们某一个集合中的最大值，然后对这个数字进行我们的函数操作。最后，我们的操作次数就是我们的答案。
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int len(int x)
{
	int cnt = 0;
	while (x)
	{
		cnt++;
		x = x / 10;
	}
	return cnt;
}
void solve()
{
	priority_queue<int, vector<int>, less<int>>a, b;
	int n, x, y;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &x);
		a.push(x);
	}
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &x);
		b.push(x);
	}
	int ans = 0;
	while (!a.empty())
	{
		x = a.top();
		y = b.top();
		if (x > y)
		{
			a.pop();
			a.push(len(x));
			ans++;
		}
		else if (x < y)
		{
			b.pop();
			b.push(len(y));
			ans++;
		}
		else
		{
			a.pop();
			b.pop();
		}
	}
	printf("%d\n", ans);
}
int main()
{
	int T = 1;
	scanf("%d", &T);
	while (T--)solve();
	return 0;
}
```