# Wizards and Huge Prize

## 题面翻译

最开始你有 $k$ 的容积，有 $n$ 轮比赛，每轮比赛胜率为 $p_i$，比赛分为两种（具体种类有输入给出，若 $a_i \geq 1$ 则为第一种，若 $a_i=-1$ 则为第二种），第一种的奖品是增加 $a_i$ 的容积，第二种奖品是获得一个物品，体积为 1，$n$ 轮比赛结束后所有物品都能被装下的方案才是合法方案（即容积大于等于物品个数），问赢得比赛总场数大于等于 $l$ 时方案合法的概率。

## 题目描述

One must train much to do well on wizardry contests. So, there are numerous wizardry schools and magic fees.

One of such magic schools consists of $ n $ tours. A winner of each tour gets a huge prize. The school is organised quite far away, so one will have to take all the prizes home in one go. And the bags that you've brought with you have space for no more than $ k $ huge prizes.

Besides the fact that you want to take all the prizes home, you also want to perform well. You will consider your performance good if you win at least $ l $ tours.

In fact, years of organizing contests proved to the organizers that transporting huge prizes is an issue for the participants. Alas, no one has ever invented a spell that would shrink the prizes... So, here's the solution: for some tours the winner gets a bag instead of a huge prize. Each bag is characterized by number $ a_{i} $ — the number of huge prizes that will fit into it.

You already know the subject of all tours, so you can estimate the probability $ p_{i} $ of winning the $ i $ -th tour. You cannot skip the tour under any circumstances.

Find the probability that you will perform well on the contest and will be able to take all won prizes home (that is, that you will be able to fit all the huge prizes that you won into the bags that you either won or brought from home).

## 输入格式

The first line contains three integers $ n $ , $ l $ , $ k $ ( $ 1<=n<=200,0<=l, k<=200 $ ) — the number of tours, the minimum number of tours to win, and the number of prizes that you can fit in the bags brought from home, correspondingly.

The second line contains $ n $ space-separated integers, $ p_{i} $ ( $ 0<=p_{i}<=100 $ ) — the probability to win the $ i $ -th tour, in percents.

The third line contains $ n $ space-separated integers, $ a_{i} $ ( $ 1<=a_{i}<=200 $ ) — the capacity of the bag that will be awarded to you for winning the $ i $ -th tour, or else -1, if the prize for the $ i $ -th tour is a huge prize and not a bag.

## 输出格式

Print a single real number — the answer to the problem. The answer will be accepted if the absolute or relative error does not exceed $ 10^{-6} $ .

## 样例 #1

### 样例输入 #1

```
3 1 0
10 20 30
-1 -1 2
```

### 样例输出 #1

```
0.300000000000
```

## 样例 #2

### 样例输入 #2

```
1 1 1
100
123
```

### 样例输出 #2

```
1.000000000000
```

## 提示

In the first sample we need either win no tour or win the third one. If we win nothing we wouldn't perform well. So, we must to win the third tour. Other conditions will be satisfied in this case. Probability of wining the third tour is 0.3.

In the second sample we win the only tour with probability 1.0, and go back home with bag for it.

## 题解
我们本题的思路是：设置我们的 $dp[i][j][k]$ 表示我们进行了 $i$ 轮比赛，赢了 $j$ 厂，现在**剩余**背包容量为 $k$ 的概率为多少。注意到我们的容量增加，相等于我们的 $k\to k+1$,因此我们的转移就可以通过我们的刷表法携程：
$dp[i+1][j+1][k-a[i]]+=p*dp[i][j][k]$,其中要求我们的 $k-a[i]$ 一定要大于 0.
$dp[i+1][j][k]+=(1-p)*dp[i][j][k]$，这个可以任意转移。

考虑我们的时间复杂度，最坏情况下能够到达 $o(n^3)$,显然不能够支持我们通过本题。于是我们考虑其他可能的方案。

```cpp
#include<bits/stdc++.h>
using namespace std;
namespace Acc{
	const int N = 2e2+10;
#define db double
	db dp[N][N][N*2],p[N],ans;
	int a[N],n,l,k,m;
	void work(){
		cin>>n>>l>>m;
		for(int i=1;i<=n;i++)cin>>p[i],p[i]/=100;
		for(int i=1;i<=n;i++)cin>>a[i];
		dp[0][0][m+200]=1;
		for(int i=0;i<n;i++){
			for(int j=0;j<=i;j++){
				for(int k=0;k<=400;k++){
					int t=min(400,k+a[i+1]);
					dp[i+1][j][k]+=dp[i][j][k]*(1-p[i+1]);
					if(t>=0)dp[i+1][j+1][t]+=dp[i][j][k]*p[i+1];
				}
			}
		}
		for(int i=l;i<=n;i++)for(int j=200;j<=400;j++)ans+=dp[n][i][j];
		cout<<fixed<<setprecision(10)<<ans;
	}
#undef db
}
int main(){
	return Acc::work(),0;
}
```