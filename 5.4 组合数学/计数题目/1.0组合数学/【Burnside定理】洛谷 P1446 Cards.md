# [HNOI2008] Cards

## 题目描述

小春现在很清闲，面对书桌上的 $n$ 张牌，他决定给每张牌染色，目前小春拥有 $3$ 种颜色：红色，蓝色，绿色。他询问 Sun 有多少种染色方案，Sun 很快就给出了答案。

进一步，小春要求染出 $S_r$ 张红色，$S_b$ 张蓝色，$S_g$ 张绿色。他又询问有多少种方案，Sun 想了一下，又给出了正确答案。最后小春发明了 $m$ 种不同的洗牌法，这里他又问 Sun 有多少种不同的染色方案。两种染色方法相同当且仅当其中一种可以通过任意的洗牌法（即可以使用多种洗牌法，而每种方法可以使用多次）洗成另一种。

Sun 发现这个问题有点难度，决定交给你，由于答案可能很大，你只需要求出答案对于 $P$ 取模的结果。 保证 $P$ 为一个质数。

## 输入格式

第一行输入 $5$ 个整数，依次表示：$S_r,S_b,S_g,m,P$（$m\le 60,m+1<p<100$）。其中，题面所提及的 $n$ 为 $S_r+S_b+S_g$，即 $n=S_r+S_b+S_g$。

接下来 $m$ 行，每行描述一种洗牌法，每行有 $n$ 个用空格隔开的整数 $X_1X_2...X_n$，保证其为 $1$ 到 $n$ 的一个排列，表示使用这种洗牌法，第 $i$ 位变为原来的 $X_i$ 位的牌。输入数据保证任意多次洗牌都可用这 $m$ 种洗牌法中的一种代替，且对每种洗牌法，都存在一种洗牌法使得能回到原状态。

同时，对于 $100\%$ 的数据满足 $\max\{S_r,S_b,S_g\}\le 20$ 。

## 输出格式

不同的染色方法对 $P$ 取模的结果。

## 样例 #1

### 样例输入 #1

```
1 1 1 2 7
2 3 1
3 1 2
```

### 样例输出 #1

```
2
```

## 提示

有 $2$ 种本质上不同的染色法：`RGB` 和 `RBG`，使用洗牌法 `231` 一次，可得 `GBR` 和 `BGR`，使用洗牌法 `312` 一次，可得 `BRG` 和 `GRB`。


## 题解：
Burnside定理需要用到置换和不变元，本题我们给出了置换数量$m$，我们可以推导出实际的数量$m+1$,接下来我们就对这m+1种置换，分别求出他们的对应的不变元。

对于每一种操作，我们考虑把每种置换操作建边，然后把它们缩成一些环，如果我们原来的颜色要排列成不动点，那么就需要保证环上所有点的颜色不变。

那么现在一个环内的颜色都一样，问题就变成了一些有大小的环，然后有 3 种颜色，每种颜色有一定个数但保证总的颜色个数等于所有环相加的大小，然后每用一种颜色染环都得扣除相应的环的大小个颜色，求染环的方案就是这个置换操作下不动点的个数了。

我们考虑用DP去计算我们的总共方案数：记$dp_{i,x,y,z}$表示当选完第i个环后，剩余三种颜色卡牌分别为$x,y,z$时的方案书，然后就看一下当前$x+siz_{x}$和$y+siz_{y}$是否合法。

```cpp
#include "bits/stdc++.h"
using namespace std;
const int Len = 65;
int a,b,c,m,P,n,siz[Len],to[Len],cnt,sim,sum[Len];
bool flag[Len];
int dp[2][21][21][21],ans;
void dfs(int x)
{
	if(flag[x]) return;
	sim ++;
	flag[x] |= 1;
	dfs(to[x]);
}
int qpow(int a,int b)
{
	int res = 1;
	while(b)
	{
		if(b & 1) res = res * a % P;
		a = a * a % P;
		b = b >> 1;
	}
	return res;
}
int main()
{
	scanf("%d %d %d %d %d",&a,&b,&c,&m,&P);
	n = a + b + c;
	memset(dp , 0 , sizeof dp);
	memset(flag , 0 , sizeof flag);
	dp[0][a][b][c] = 1 , cnt = 0;
	for(int i = 1 ; i <= n ; i ++) to[i] = i;
	for(int j = 1 ; j <= n ; j ++) if(!flag[j]){sim = 0 ; dfs(j) ; siz[++ cnt] = sim;}//处理环
	for(int j = 1 ; j <= n ; j ++) sum[j] = sum[j - 1] + siz[j];
	for(int j = 1 ; j <= cnt ; j ++)
		for(int x = 0 ; x <= a ; x ++)     
		    for(int y = 0 ; y <= b ; y ++)
		    {
		       	int z = n - sum[j] - x - y;
		       	if(z < 0 || z > c) continue;
		       	//printf("%d %d %d %d\n",j,x,y,z);
		        dp[j % 2][x][y][z] = 0;
		        if(x + siz[j] <= a) dp[j % 2][x][y][z] += dp[(j - 1) % 2][x + siz[j]][y][z];
		        if(y + siz[j] <= b) dp[j % 2][x][y][z] += dp[(j - 1) % 2][x][y + siz[j]][z];
		        if(z + siz[j] <= c) dp[j % 2][x][y][z] += dp[(j - 1) % 2][x][y][z + siz[j]];
				dp[j % 2][x][y][z] %= P;
			}
	ans = (ans + dp[cnt % 2][0][0][0]) % P;//计算不洗牌方法下的不动点
	int Sub = 0;
	for(int i = 1 ; i <= m ; i ++)
	{
		memset(flag , 0 , sizeof flag);
	    dp[0][a][b][c] = 1 , cnt = 0;bool flaw = 0;
		for(int j = 1 ; j <= n ; j ++) 
		{
		    scanf("%d",&to[j]);
		    if(to[j] != j) flaw |= 1;
		}
		if(!flaw){Sub ++ ; continue;}
		for(int j = 1 ; j <= n ; j ++) if(!flag[j]){sim = 0 ; dfs(j) ; siz[++ cnt] = sim;}
		for(int j = 1 ; j <= n ; j ++) sum[j] = sum[j - 1] + siz[j];
		for(int j = 1 ; j <= cnt ; j ++)
		    for(int x = 0 ; x <= a ; x ++)     
		        for(int y = 0 ; y <= b ; y ++)
		        {
		        	int z = n - sum[j] - x - y;
		        	if(z < 0 || z > c) continue;
		        	dp[j % 2][x][y][z] = 0;
		        	if(x + siz[j] <= a) dp[j % 2][x][y][z] += dp[(j - 1) % 2][x + siz[j]][y][z];
		        	if(y + siz[j] <= b) dp[j % 2][x][y][z] += dp[(j - 1) % 2][x][y + siz[j]][z];
		        	if(z + siz[j] <= c) dp[j % 2][x][y][z] += dp[(j - 1) % 2][x][y][z + siz[j]];
					dp[j % 2][x][y][z] %= P;
				}
		ans = (ans + dp[cnt % 2][0][0][0]) % P;
		for(int j = 1 ; j <= cnt ; j ++)
		    for(int x = 0 ; x <= a ; x ++)     
		        for(int y = 0 ; y <= b ; y ++) 
		        {
		        	int z = n - sum[j] - x - y;
		        	if(z < 0 || z > c) continue;
		        	dp[0][x][y][z] = dp[1][x][y][z] = 0;
				}
	}
	printf("%d\n",ans * qpow(m + 1 - Sub , P - 2) % P);
	return 0;
}
```

