# [USACO 13 MAR] Poker Hands S

## 题面翻译

Bessie 有 $n$ 堆牌，每堆牌有 $a_i$ 张。她一次可以将第 $i$ 堆到第 $j$ 堆里打一张出去，求打完 $n$ 堆牌最少的次数。

对于 $100\%$ 的数据，$1\le n\le10^5,0\le a_i\le10^5$。

## 题目描述

Bessie and her friends are playing a unique version of poker involving a deck with N (1 <= N <= 100,000) different ranks, conveniently numbered 1.. N (a normal deck has N = 13). In this game, there is only one type of hand the cows can play: one may choose a card labeled i and a card labeled j and play one card of every value from i to j.  This type of hand is called a "straight".

Bessie's hand currently holds a\_i cards of rank i (0 <= a\_i <= 100000). Help her find the minimum number of hands she must play to get rid of all her cards.

## 输入格式

\* Line 1: The integer N.

\* Lines 2.. 1+N: Line i+1 contains the value of a\_i.

## 输出格式

\* Line 1: The minimum number of straights Bessie must play to get rid of all her cards.

## 样例 #1

### 样例输入 #1

```
5 
2 
4 
1 
2 
3
```

### 样例输出 #1

```
6
```

## 提示

Bessie can play a straight from 1 to 5, a straight from 1 to 2, a straight from 4 to 5, two straights from 2 to 2, and a straight from 5 to 5, for a total of 6 rounds necessary to get rid of all her cards.

## 题解
我们不难发现，我们这一题就是我们的积木大赛的逆过程，我们统计一个差分数组 $cf[i]=d[i]-d[i-1]$,特别的，我们的 $cf[0]=0$,
然后，我们修改 $i-j$ 区间，只需要把我们的 $cf[i]-1$,然后把我们的 $cf[j+1]+1$ 就可以了。

这个时候，我们的问题就转变为：给你一个长为 $n$ 的序列，每一次可以选择两个数，对于其中的一个数进行+1 操作，一个数进行-1 操作，问我们最少需要多少次能让我们的最后数字完全相等。

为了得到我们的最优解，我们一定是先取一个正数去做减法，然后让一个负数数字做加法，我们这么做可以做的次数就是我们的 $min(abs(sum_{neg}),abs(sum_{pos}))$ 。

最后，对于我们剩下的元素，我们只需要进行单独的加一减一即可。
我们记正数总和为 $sum_{1}$,负数总和为 $sum_{2}$,
我们能够构成的配对就是我们的 $min(sum_{1},sum_{2})$, 
我们剩下的我们就需要我们一个一个的修改，所以最后我们的答案就是我们的 $min(sum_{1},abs(sum_{2}),abs(sum_{1}-sum_{2}))$,

```cpp
#include<iostream>

using namespace std;

long long n,d[100005],ans,cf[100005]={0},sum1,sum2;

int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)  cin>>d[i];
    
	for(int i=1;i<=n;i++)
	{
		cf[i]=d[i]-d[i-1];
		if(cf[i]<0)  sum1-=cf[i];
		if(cf[i]>0)  sum2+=cf[i];
	} 
    
	cout<<max(sum1,sum2)<<endl;
    
   return 0;
}
```