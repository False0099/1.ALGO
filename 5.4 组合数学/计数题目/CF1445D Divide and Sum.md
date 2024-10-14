## 题意：
给你一个长度为 $2n$ 的数组 $a$ 。考虑将数组 $a$ 分割为长度分别为 $n$ 的两个子序列 $p$ 和 $q$ （数组 $a$ 中的每个元素都应恰好位于一个子序列中：要么位于 $p$ 中，要么位于 $q$ 中）。

让我们对 $p$ 和 $q$ 进行非递减排序，分别用 $x$ 和 $y$ 表示排序后的版本。那么分区的代价定义为 $f(p, q) = \sum_{i = 1}^n |x_i - y_i|$ 。

求数组 $a$ 所有正确分区的总和 $f(p, q)$ 。由于答案可能太大，请打印其余数取模 $998244353$ 。

You are given an array $a$ of length $2n$. Consider a partition of array $a$ into two subsequences $p$ and $q$ of length $n$ each (each element of array $a$ should be in exactly one subsequence: either in $p$ or in $q$).

Let's sort $p$ in non-decreasing order, and $q$ in non-increasing order, we can denote the sorted versions by $x$ and $y$, respectively. Then the cost of a partition is defined as $f(p, q) = \sum_{i = 1}^n |x_i - y_i|$.

Find the sum of $f(p, q)$ over all correct partitions of array $a$. Since the answer might be too big, print its remainder modulo $998244353$.

**Input**

The first line contains a single integer $n$ ($1 \leq n \leq 150\,000$).

The second line contains $2n$ integers $a_1, a_2, \ldots, a_{2n}$ ($1 \leq a_i \leq 10^9$) — elements of array $a$.

## 题解
本题考虑贡献，我们考虑每一个数字对于我们的结果的贡献是多少，显然，如果我们的某一个数是前 $K$ 大的数字，那么他无论怎么放，都是找不到一个比他还要小的数字的，所以这一个位置对于我们的最终答案的贡献一定是整数，反之，如果是一个后 $N$ 大的数字，无论怎么放，都是找不到一个比他还要大的数字的，所以最后的贡献一定是负数。

所以最后我们的答案就是前 N 大减去前 N 小，然后结果再去呈上我们的组合数即可。
```
#include<bits/stdc++.h>
#define int long long//不开long long见祖宗
#define mod 998244353
using namespace std;
int n,a[150000*2+5],f[150000*2+5],inv[150000*2+5],ans;
int ksm(int x,int y)//由于要用到逆元求组合数，所以要快速幂
{	int res=1;
	while(y)
	{	if(y&1)res=x*res%mod;
		x=x*x%mod;
		y>>=1;
	}
	return res;
}
signed main()
{	cin>>n;
	for(register int i=1;i<=2*n;++i)cin>>a[i];
	sort(a+1,a+n+n+1);//排序
	f[0]=1;
	for(register int i=1;i<=2*n;++i)//求逆元
	{	f[i]=f[i-1]*i%mod;
		inv[i]=ksm(f[i],mod-2);
	}
	for(register int i=2*n;i>=1;--i)//计算答案
	{	if(i<=n)ans=(ans+mod-f[2*n]*inv[n]%mod*inv[n]%mod*a[i]%mod)%mod;//若为小的n个数，则减
		else ans=(ans+f[2*n]*inv[n]%mod*inv[n]%mod*a[i]%mod)%mod;//若为大的n个数，则加
	}
	cout<<ans;
	return 0;
}
```