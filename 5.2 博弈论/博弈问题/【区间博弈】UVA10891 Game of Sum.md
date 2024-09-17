# Game of Sum

## 题面翻译

## 题目描述

有一个长度为 $n$ 的整数序列，两个游戏者 $A$ 和 $B$ 轮流取数，$A$ 先取。每次玩家只能从左端或者右端取任意数量的数，但不能两边都取。所有数都被取走视为游戏结束，然后统计每个人取走的数之和，作为各自的得分。两个人采取的策略都是让自己得分尽可能高，并且两个人都很机智，求 $A$ 得分 - $B$ 得分后的结果。

## 输入格式

输入包含多组数据，每组数据第一行为正整数 $n(1\leq n\leq 100)$ ，第二行为给定的整数序列，输入结束标志是 $n=0$ 。

## 输出格式

对于每组数据，输出 $A$ 和 $B$ 都采取最优策略下，$A$ 的得分 $-B$ 的得分。


感谢 @额冻豆腐提供的翻译

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=20&page=show_problem&problem=1832

[PDF](https://uva.onlinejudge.org/external/108/p10891.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10891/c6dee7bf4345b5a58b0b8644fb06c07608c40ef3.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10891/83cb3fa2fcfea3c8bec0c4ba3875f296b670fb9c.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10891/21063ea1ae5b572ff629bddc7e3854ff11afd4d9.png)

## 样例 #1

### 样例输入 #1

```
4
4 -10 -20 7
4
1 2 3 4
0
```

### 样例输出 #1

```
7
10
```

## 题解
我们看到题目中要求的 $A-B$ 的结果最大，我们就已经不难想到，我们只需要每一步都取到“最优”，我们的结果一定也是最优的。

而我们前面的题目中存在一个两侧取一个的，那个可以通过我们的贪心。我们可以定义 $f(l,r)$ 表示在我们的剩余区间为 $(l,r)$ 的情况下，我们能够获得的最大的分数是多少。那么根据我们的**极大极小原则**，我们能够获得的分数就是：

$$dp_{i,j}=sum(i,j)-\min(dp_{i,j-1},dp_{i,j-2},\ldots,dp_{i,i},dp_{i+1,j},dp_{i+2,j},\ldots,dp_{j,j})$$

而我们如果只是这样的转移，那么我们的复杂度显然是 $o(n^3)$ 的。

考虑区间内 $dp$ 数组的最小值完全可以通过递推 $O(1)$ 得到。设 $z_{i,j}=$$$\min(dp_{i,j},dp_{i,j-1},dp_{i,j-2},\ldots,dp_{i,i}),y_{i,j}=\min(dp_{i,j},dp_{i+1,j},dp_{i+2,j},dp_{j,j})。$$
则每次处理完 $dp_{i,j}$ 时，我们都可以顺便维护 $z_{i,j}$ 和 $y_{i,j}$。
则新的状态转移方程式为
$$dp_{i,j}=sum_j-sum_{i-1}-\min(0,z_{i,j-1},y_{i+1,j})$$

同样的，我们的 $z_{ij},y_{ij}$ 可以在我们的地推过程中动态的求出，于是我们本体就能够解决了。

```
#include<bits/stdc++.h>
using namespace std;
#define N 105
int n,a,z[N][N],y[N][N],dp[N][N],sum[N];
int read(){
	int w=0,f=1;
	char ch=getchar();
	while (ch>'9'||ch<'0') {
		if (ch=='-') f=-1;
		ch=getchar();
	}
	while (ch>='0'&&ch<='9') {
		w=(w<<3)+(w<<1)+(ch^48);
		ch=getchar();
	}
	return w*f;
} 
int main(){
	while (1){
		if ((n=read())==0) break;
		for (int i=1;i<=n;i++) dp[i][i]=z[i][i]=y[i][i]=a=read(),sum[i]=sum[i-1]+a;
		for (int i=2;i<=n;i++){
			for (int l=1;l<=n-i+1;l++){
				int r=l+i-1;
				int x=min(0,min(z[l][r-1],y[l+1][r]));
				dp[l][r]=sum[r]-sum[l-1]-x;
				z[l][r]=min(z[l][r-1],dp[l][r]);
				y[l][r]=min(y[l+1][r],dp[l][r]);
			}
		}
		printf("%d\n",2*dp[1][n]-sum[n]);
	}
	return 0;
}

```