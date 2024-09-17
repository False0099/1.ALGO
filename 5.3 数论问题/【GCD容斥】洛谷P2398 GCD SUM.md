# GCD SUM

## 题目描述

求

$$\sum_{i=1}^n \sum_{j=1}^n \gcd(i, j)$$

## 输入格式

第一行一个整数 $n$。

## 输出格式

第一行一个整数表示答案。

## 样例 #1

### 样例输入 #1

```
2
```

### 样例输出 #1

```
5
```

## 提示

对于 $30\%$ 的数据，$n\leq 3000$。

对于 $60\%$ 的数据，$7000\leq n\leq 7100$。

对于 $100\%$ 的数据，$n\leq 10^5$。

## 题解
本题考虑到存在我们的下面的方法来进行求和，我们考虑枚举所有的 gcd 值再去进行计算。显然，我们这个时候就可以有：
$\sum \sum gcd(i,j)=\sum_{k=1}^n k*cnt[k]$,其中我们的 $cnt[k]$ 表示我们 gcd 为 k 的元素有多少个。

我们考虑一种**经典的容斥原理**，我们把我们的 $gcd$ 为 $k$ ，认为是一个**交集**，而我们的交集则可以通过我们的求 $gcd$ 为 $k的倍数$，然后再去不断地减去即可得到我们的答案。

定义：
$f(k)=\sum_i^n\sum_j^m[gcd(i,j)=k]$
即 $f(k)$ 表示 $gcd(i,j)=k$ 的数对个数
根据容斥原理，$f(k)=$ 以 k 为公约数的数对个数-以 k 的倍数为最大公约数的数对个数。即 $f(k)=\lfloor n/x\rfloor*\lfloor m/x\rfloor-\sum f[k*i]$,其中 $k*i<=n$，从 $min(n,m)$ 开始倒着计算，即可用 nlogn 复杂度求出所有的 $f(k)$。

```
#include<cstdio>

#define N 100001

long long f[N];

int main()
{
	int n;
	scanf("%d",&n);
	for(int i=n;i;--i)
	{
		f[i]=1ll*(n/i)*(n/i);
		for(int j=i+i;j<=n;j+=i) f[i]-=f[j];
	}
	long long ans=0;
	for(int i=1;i<=n;++i) ans+=i*f[i];
	printf("%lld",ans);
}

```
