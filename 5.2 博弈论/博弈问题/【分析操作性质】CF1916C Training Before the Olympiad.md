# Training Before the Olympiad

## 题面翻译

有一个正整数序列 $a$，两人进行游戏，规则如下：

- 当序列中只有一个元素时，游戏结束。
- 否则，两人交替操作，每次需要选出 $a$ 中的两个元素 $a_i,a_j(i\ne j)$，将它们删除并插入一个值为 $\lfloor\frac{a_i+a_j}{2}\rfloor\cdot 2$ 的元素。

先手希望使得最终 $a$ 中留下的数最大化，后手希望最小化，两人都按最优策略进行游戏，求对于给定的长为 $n$ 的序列 $a$ 的每个非空前缀，对该前缀进行游戏的结果，即最后留下的数。每个测试点 $t$ 组测试用例。

## 题目描述

Masha and Olya have an important team olympiad coming up soon. In honor of this, Masha, for warm-up, suggested playing a game with Olya:

There is an array $ a $ of size $ n $ . Masha goes first, and the players take turns. Each move is described by the following sequence of actions:

 $ \bullet $ If the size of the array is $ 1 $ , the game ends.

 $ \bullet $ The player who is currently playing chooses two different indices $ i $ , $ j $ ( $ 1 \le i, j \le |a| $ ), and performs the following operation — removes $ a_i $ and $ a_j $ from the array and adds to the array a number equal to $ \lfloor \frac{a_i + a_j}{2} \rfloor \cdot 2 $ . In other words, first divides the sum of the numbers $ a_i $ , $ a_j $ by $ 2 $ rounding down, and then multiplies the result by $ 2 $ .

Masha aims to maximize the final number, while Olya aims to minimize it.

Masha and Olya decided to play on each non-empty prefix of the initial array $ a $ , and asked for your help.

For each $ k = 1, 2, \ldots, n $ , answer the following question. Let only the first $ k $ elements of the array $ a $ be present in the game, with indices $ 1, 2, \ldots, k $ respectively. What number will remain at the end with optimal play by both players?

## 输入格式

The first line contains an integer $ t $ ( $ 1 \leq t \leq 10^4 $ ) — the number of test cases.

The first line of each test case contains a single integer $ n $ ( $ 1 \le n \le 10^5 $ ) — the size of the array.

The second line contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \leq a_i \leq 10^9 $ ) — the array on which Masha and Olya play.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 10^5 $ .

## 输出格式

For each test case, output $ n $ integers. The $ k $ -th of these numbers should be equal to the number that will remain at the end with optimal play by both players, on the array consisting of the first $ k $ elements of the array $ a $ .

## 样例 #1

### 样例输入 #1

```
4
1
31
6
6 3 7 2 5 4
3
3 10 11
5
7 13 11 19 1
```

### 样例输出 #1

```
31 
6 8 16 18 22 26 
3 12 24 
7 20 30 48 50
```

## 提示

In the third test case, for a prefix of length $ 1 $ , the answer is $ 3 $ . For a prefix of length $ 2 $ , Masha has only one move, so the answer is $ 12 $ . For a prefix of length $ 3 $ , Masha has three possible moves: she chooses $ 3 $ and $ 10 $ , then the final number is $ 22 $ , $ 3 $ and $ 11 $ , then the final number is $ 24 $ , $ 10 $ and $ 11 $ , then the final number is $ 22 $ , so Masha will choose $ 3 $ and $ 11 $ and get $ 24 $ .

## 题解
我们经过观察，我们不难发现，我们如果想让我们最后的答案尽可能的小，我们每一次一定是选择我们的一个奇数一个偶数，这样我们每一次就可以吃掉 1 的回扣（）。

那么，我们最后因为我们答案是希望得到一个偶数，那么我们一定是选择两个偶数，这样既能够消除掉对方的可操作数量，还能让自己的操作数保持不变。

于是，我们只需要模拟上面的过程，就能得到我们的答案。

```
#include<bits/stdc++.h>
using namespace std;
long long T,n,a,sum,num;//要开longlong 10^5个10^9的和轻松爆int
int main()
{
	scanf("%lld",&T);
	while(T--)
	{
		scanf("%lld",&n),sum=num=0;//别忘了清零
		for(int i=1;i<=n;++i)
		{
			scanf("%lld",&a),sum+=a,num+=a%2;//统计总和和奇数个数
			if(i==1) printf("%lld ",sum); //如果是第一个，直接就是答案，不需要考虑奇数
			else printf("%lld ",sum-num/3-(num%3==1));
		}
		puts("");
	}
	return 0;
}

```