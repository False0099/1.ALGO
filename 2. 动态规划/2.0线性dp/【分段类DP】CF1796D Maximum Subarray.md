# Maximum Subarray

## 题面翻译

你得到了一个序列 $a_1,a_2,\cdots,a_n$，由 $n$ 个整数组成。并且你还得到了两个整数 $k,x$。

你需要执行**一次**操作：选择**恰好 $k$ 个不同**的位置加上 $x$，其余位置减去 $x$。

比如说：如果 $a=[2,-1,2,3],k=1,x=2$，然后我们选择第一个位置，操作之后的 $a=[4,-3,0,1]$。

定义 $f(a)$ 为 $a$ 序列的子串的最大可能和。$a$ 的子串是 $a$ 的一部分，即序列 $a_i,a_{i+1},\cdots a_j$ 对于某个 $1\le i\le j\le n$。同时，空数组也应该被考虑，它的和为 $0$。

让 $a'$ 为 $a$ 操作后的序列，输出 $f(a')$ 的最大可能值。

$1\le t\le 10^4;\;1\le n,\sum n\le 2\cdot 10^5;\;0\le k\le \min(20,n);\;-10^9\le a_i,x\le 10^9$

## 题目描述

You are given an array $ a_1, a_2, \dots, a_n $ , consisting of $ n $ integers. You are also given two integers $ k $ and $ x $ .

You have to perform the following operation exactly once: add $ x $ to the elements on exactly $ k $ distinct positions, and subtract $ x $ from all the others.

For example, if $ a = [2, -1, 2, 3] $ , $ k = 1 $ , $ x = 2 $ , and we have picked the first element, then after the operation the array $ a = [4, -3, 0, 1] $ .

Let $ f (a) $ be the maximum possible sum of a subarray of $ a $ . The subarray of $ a $ is a contiguous part of the array $ a $ , i. e. the array $ a_i, a_{i + 1}, \dots, a_j $ for some $ 1 \le i \le j \le n $ . An empty subarray should also be considered, it has sum $ 0 $ .

Let the array $ a' $ be the array $ a $ after applying the aforementioned operation. Apply the operation in such a way that $ f (a') $ is the maximum possible, and print the maximum possible value of $ f (a') $ .

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

The first line of each test case contains three integers $ n $ , $ k $ and $ x $ ( $ 1 \le n \le 2 \cdot 10^5 $ ; $ 0 \le k \le \min (20, n) $ ; $ -10^9 \le x \le 10^9 $ ).

The second line contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ -10^9 \le a_i \le 10^9 $ ).

The sum of $ n $ over all test cases doesn't exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, print one integer — the maximum possible value of $ f (a') $ .

## 样例 #1

### 样例输入 #1

```
4
4 1 2
2 -1 2 3
2 2 3
-1 2
3 0 5
3 2 4
6 2 -8
4 -1 9 -3 7 -8
```

### 样例输出 #1

```
5
7
0
44
```

## 题解
本题我们考虑下面的处理方法，首先，我们有：**把一个元素进行单独处理，其他的不处理，等价于我们先都不处理，再枚举我们处理哪一个**。

在本题中，我们就可以先去枚举我们要在哪些位置改变，这里我们可以通过我们的**动态规划**来进行处理，我们设 $f[i][j]$ 表示我们以 $i$ 结尾，进行 $j$ 次操作的最大值是多少。

我们于是就有下面的转移：$f[i][j]=max\{f[i-1][j]+a[i],f[i-1][j-1]+a[i]+2x,0\}$

这个时候，我们就有下面的代码：这里，我们需要注意我们的下面的细节：
1. 我们的 $i<j$ 就没有意义
2. 在 $i=j$ 的时候，我们需执行我们的 $f[i-1][j-1]$ 的转移，并且只能这么转移。

```
// LUOGU_RID: 115129041
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=2e5+10;
const int maxk=25;
const int inf=1e15;
int t,n,k,val,f[maxn][maxk],a[maxn];
signed main()
{
	scanf("%lld",&t);
	while(t--)
	{
		scanf("%lld%lld%lld",&n,&k,&val);
		for(int i=1;i<=n;i++)scanf("%lld",&a[i]),a[i]-=val;
		for(int i=1;i<=n;i++)
		{
			for(int j=0;j<=k;j++)f[i][j]=-inf;
		}
		for(int i=1;i<=n;i++)
		{
			for(int j=0;j<=min(i,k);j++)
			{	
				if((i-1)>=j)
				{
					f[i][j]=max(f[i][j],a[i]);//只保留最后一位
					f[i][j]=max(f[i][j],f[i-1][j]+a[i]);
				}
				if(j>0)
				{
					f[i][j]=max(f[i][j],a[i]+2*val);
					f[i][j]=max(f[i][j],f[i-1][j-1]+a[i]+2*val);
				}
			}
		}
		int ans=0;
		for(int i=1;i<=n;i++)
		{
			for(int j=0;j<=min(i,k);j++)
			{
				if(n-i+j>=k)//够修改
				{
					ans=max(ans,f[i][j]);	
				} 
			}
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```