You are given two arrays $a$ and $b$ each consisting of $n$ integers. All elements of $a$ are pairwise distinct.

Find the number of ways to reorder $a$ such that $a_i \gt b_i$ for all $1 \le i \le n$, modulo $10^9 + 7$.

Two ways of reordering are considered different if the resulting arrays are different.

**Input**

Each test contains multiple test cases. The first line contains the number of test cases $t$ ($1 \le t \le 10^4$). The description of the test cases follows.

The first line of each test case contains a single integer $n$ ($1 \le n \le 2 \cdot 10^{5}$) — the length of the array $a$ and $b$.

The second line of each test case contains $n$ distinct integers $a_1$, $a_2$, $\ldots$, $a_n$ ($1 \le a_i \le 10^9$) — the array $a$. It is guaranteed that all elements of $a$ are pairwise distinct.

The second line of each test case contains $n$ integers $b_1$, $b_2$, $\ldots$, $b_n$ ($1 \le b_i \le 10^9$) — the array $b$.

It is guaranteed that the sum of $n$ over all test cases does not exceed $2 \cdot 10^{5}$.

**Output**

For each test case, output the number of ways to reorder array $a$ such that $a_i \gt b_i$ for all $1 \le i \le n$, modulo $10^9 + 7$.

## 题解
我们本题我们从大到小考虑 $b_{i}$,求出大于 $b_{i}$ 且未被使用的 $a_{j}$ 的个数，然后累成起来即可。一个简单朴素的乘法原理。
```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#define RI register int
#define CI const int&
using namespace std;
const int N=200005,mod=1e9+7;
int t,n,a[N],b[N],ans;
int main()
{
	for (scanf("%d",&t);t;--t)
	{
		RI i,j; for (scanf("%d",&n),ans=1,i=1;i<=n;++i) scanf("%d",&a[i]);
		for (i=1;i<=n;++i) scanf("%d",&b[i]); sort(a+1,a+n+1); sort(b+1,b+n+1);
		for (i=j=n;i>=1;--i)
		{
			while (j>=1&&a[j]>b[i]) --j; ans=1LL*ans*(n-j-(n-i))%mod;
		}
		printf("%d\n",ans);
	}
	return 0;
}

```