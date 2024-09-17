# [AHOI 2009] 同类分布

## 题目描述

给出两个数 $a,b$，求出 $[a,b]$ 中各位数字之和能整除原数的数的个数。

## 输入格式

一行，两个整数 $a$ 和 $b$

## 输出格式

一个整数，表示答案

## 样例 #1

### 样例输入 #1

```
10 19
```

### 样例输出 #1

```
3
```

## 提示

对于所有的数据，$1 ≤ a ≤ b ≤ 10^{18}$

## 题解
我们这一题就是求一个典型的数位 dp，我们按照我们灵神的模板再稍加修改即可。但是我我们要注意一个点，就是因为我们的**模数是已经可以进行提前枚举**，并且我们的范围是并不大的。
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll l,r,dp[20][200][200];
int len,a[20],mod;
ll dfs(int pos,int sum,ll st,int limit)
{
	if(pos>len&&sum==0) return 0;
	if(pos>len) return st==0&&sum==mod?1:0;
	if(!limit&&dp[pos][sum][st]!=-1) return dp[pos][sum][st];
	ll ret=0;
	int res=limit?a[len-pos+1]:9;
	for(int i=0;i<=res;i++)
		ret+=dfs(pos+1,sum+i,(10ll*st+i)%mod,i==res&&limit);
	return limit?ret:dp[pos][sum][st]=ret;
}
ll part(ll x)
{
	len=0;
	while(x) a[++len]=x%10,x/=10;
	ll ret=0;
	for(mod=1;mod<=9*len;mod++)//枚举模数（就是各位数之和）
	{
		memset(dp,-1,sizeof dp);
	    ret+=dfs(1,0,0,1);
	}
	return ret;
}
int main()
{
    scanf("%lld%lld",&l,&r);
    printf("%lld\n",part(r)-part(l-1));
	return 0;
}
```