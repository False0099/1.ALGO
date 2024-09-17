# Maximum Subsequence

## 题面翻译

给一个数列和 m，在数列任选若干个数，使得他们的和对 m 取模后最大

Translated by @xzyxzy

## 题目描述

You are given an array $ a $ consisting of $ n $ integers, and additionally an integer $ m $ . You have to choose some sequence of indices $ b_{1}, b_{2},..., b_{k} $ ( $ 1<=b_{1}&lt; b_{2}&lt;...&lt; b_{k}<=n $ ) in such a way that the value of ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF888E/3a3d2e76b5bca3303d7d35912be232a5cadb1203.png) is maximized. Chosen sequence can be empty.

Print the maximum possible value of ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF888E/3a3d2e76b5bca3303d7d35912be232a5cadb1203.png).

## 输入格式

The first line contains two integers $ n $ and $ m $ ( $ 1<=n<=35 $ , $ 1<=m<=10^{9} $ ).

The second line contains $ n $ integers $ a_{1} $ , $ a_{2} $ , ..., $ a_{n} $ ( $ 1<=a_{i}<=10^{9} $ ).

## 输出格式

Print the maximum possible value of ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF888E/3a3d2e76b5bca3303d7d35912be232a5cadb1203.png).

## 样例 #1

### 样例输入 #1

```
4 4
5 2 4 1
```

### 样例输出 #1

```
3
```

## 样例 #2

### 样例输入 #2

```
3 20
199 41 299
```

### 样例输出 #2

```
19
```

## 提示

In the first example you can choose a sequence $ b={1,2} $ , so the sum ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF888E/08d6750b1b23699a8b513ddd01c316f10e6a789c.png) is equal to $ 7 $ (and that's $ 3 $ after taking it modulo $ 4 $ ).

In the second example you can choose a sequence $ b={3} $ .

## 题解
首先，我们可以发现，这是一个关于我们的取模后最大值的问题，对于这种 NP 问题，我们考虑采用我们的暴力做法。

我们如果直接枚举我们的序列是什么，那么我们最后的复杂度就是我们的 $2^n$，不满足我们的条件。

于是，我们可以考虑我们的折半搜索，以我们的中点为界，我们搜索出每一边对我们的取模后的结果是多少。

然后，我们再去通过我们的一个双指针，计算出我们的两边相加的最大值是多少。

```cpp
#include <bits/stdc++.h>//祝大家学习愉快！

using namespace std;

const int maxn=3e5+10;
int a[40],fr[maxn],bk[maxn];
int cnt=0,tot=0,n,mod,mid;

void dfs1(int i,int val){
	if(i==mid){
		fr[++cnt]=val;
		fr[++cnt]=(val+a[mid])%mod;
		return;
	}
	dfs1(i+1,val);
	dfs1(i+1,(val+a[i])%mod);
}
void dfs2(int i,int val){
	if(i==n){
		bk[++tot]=val;
		bk[++tot]=(val+a[n])%mod;
		return;
	}
	dfs2(i+1,val);
	dfs2(i+1,(val+a[i])%mod);
}

int main(){
	
	int ans=0;
	
	scanf("%d %d",&n,&mod);
	
	mid=n>>1;
	
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	
	if(n==1){//特判 n=1 的情况
		printf("%d\n",a[1]%mod);
		return 0;
	}
	
	dfs1(1,0);
	dfs2(mid+1,0);//折半搜索
	
	sort(fr+1,fr+cnt+1);
	sort(bk+1,bk+tot+1);
	
	int i=0,j=tot;
	
	while(i<=cnt){
		while(fr[i]+bk[j]>=mod) j--;
		ans=max(ans,fr[i]+bk[j]);
		i++;
	}
	
	ans=max(ans,fr[i]+bk[j]-mod);
	
	printf("%d\n",ans);
	
	return 0;
}
```