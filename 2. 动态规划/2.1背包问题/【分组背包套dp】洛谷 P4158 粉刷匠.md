# [SCOI 2009] 粉刷匠

## 题目描述

windy 有 $N$ 条木板需要被粉刷。每条木板被分为 $M$ 个格子。每个格子要被刷成红色或蓝色。

Windy 每次粉刷，只能选择一条木板上一段连续的格子，然后涂上一种颜色。每个格子最多只能被粉刷一次。

如果 windy 只能粉刷 $T$ 次，他最多能正确粉刷多少格子？

一个格子如果未被粉刷或者被粉刷错颜色，就算错误粉刷。

## 输入格式

第一行包含三个整数，$N,M,T$。

接下来有 $N$ 行，每行一个长度为 $M$ 的字符串，``0`` 表示红色，`1` 表示蓝色。

## 输出格式

包含一个整数，最多能正确粉刷的格子数。

## 样例 #1

### 样例输入 #1

```
3 6 3
111111
000000
001100
```

### 样例输出 #1

```
16
```

## 提示

$30\%$ 的数据，满足 $1 \le N,M \le 10,0 \le T \le 100$ 。

$100\%$ 的数据，满足 $1 \le N,M \le 50,0 \le T \le 2500$

## 题解
我们本题不难看出是一个 dp，我们只需要先统计处我们前 i 条木板粉刷 j 次的情况下，能够正确粉刷的最大棵子树，我们再用我们的 $g[i][j][k]$ 表示我们第 i 条木板上粉刷了 j 次，前 k 个格子的情况下能够正确粉刷的最大格子数。于是我们就可以**用一个类似于背包的思路来分配我们给每一条格子刷多少次**。

之后，我们又可以用我们的区间 dp 求出，我们**在一条格子上粉刷 k 次所能获得的最大值是多少**，这一点我们可以用我们的线性 dp。

```cpp
g[i][j][k]=max(g[i][j][k],g[i][j-1][q]+max(sum[i][k]-sum[i][q],k-q-sum[i][k]+sum[i][q]));
```

```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
using namespace std;
int f[51][2550],sum[51][2550];
int g[51][2550][51];
int n,m,t;
char s[150];

int main(){
	cin>>n>>m>>t;
	for(int i=1;i<=n;i++){
		cin>>s;
		sum[i][0]=0;
		for(int j=1;j<=m;j++){
			if(s[j-1]=='1') sum[i][j]=sum[i][j-1]+1;
			else sum[i][j]=sum[i][j-1];
		}
	}
	for(int i=1;i<=n;i++)
	for(int j=1;j<=m;j++)
	for(int k=1;k<=m;k++)
	for(int q=j-1;q<k;q++){
		g[i][j][k]=max(g[i][j][k],g[i][j-1][q]+max(sum[i][k]-sum[i][q],k-q-sum[i][k]+sum[i][q]));
	}
	for(int i=1;i<=n;i++)
	for(int j=1;j<=t;j++)
	for(int k=0;k<=min(j,m);k++){
	f[i][j]=max(f[i][j],f[i-1][j-k]+g[i][k][m]); }
	int ans=0;
	for(int i=1;i<=t;i++) ans=max(ans,f[n][i]);
	cout<<ans;
	
}
```


