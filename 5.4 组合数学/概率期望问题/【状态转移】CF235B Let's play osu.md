# Let's Play Osu!

## 题面翻译

你在玩一个叫做 Osu 的游戏（某音游）！我们来简化一下游戏规则。一局游戏中需要点击 n 次。每一次点击有两种结果：正确或失误。我们定义正确为符号"O"，失误为"X"，那么整局游戏可以被写成一个长度为 n 的由字符"X"或"O"组成的字符串。

用这个字符串你可以用以下的方法计算游戏的得分：对于一个极大的连续的"O"连击，将连击的次数的平方加入到总得分中（即连续的"O"的个数的平方）。举例说明，如果你的游戏序列为"OOXOOOXXOO"，那么极大连续的“O”连击共有三个: "OO"，"OOO"，"OO"，所以你的总得分为 2^2 + 3^2 + 2^2= 17 。如果整局游戏里没有一次成功的点击那么总得分就为 0 。

你现在知道了第 i 次 ( 1<=i<=n )点击成功的概率为 p_i，换句话说，字符串中第 i 个字符有 p_i 的概率成为"O"，有 1-p_i 的概率成为"X"，你的任务是算出你游戏总得分的期望值。

输入输出格式
输入格式：
第一行包含一个整数表示点击的次数 n ( 1<=n<=10^5 ) 第二行包含 n 个由空格间隔开的实数 p_1, p_2,..., p_n  ( 0<=p_i<=1 )
输入的 p_i 最多为六位小数

输出格式：
输出一个实数——你游戏的期望得分。你的答案必须与标准答案的误差不超过 10^{-6}

样例一说明
3 位字符串一共有 8 种不同的情况。每一种出现的概率为 0.125
所以期望得分是 (9+4+2+1+4+1+1)/8=2.75

感谢@凄魉提供的翻译

## 题目描述

You're playing a game called Osu! Here's a simplified version of it. There are $ n $ clicks in a game. For each click there are two outcomes: correct or bad. Let us denote correct as "O", bad as "X", then the whole play can be encoded as a sequence of $ n $ characters "O" and "X".

Using the play sequence you can calculate the score for the play as follows: for every maximal consecutive "O"s block, add the square of its length (the number of characters "O") to the score. For example, if your play can be encoded as "OOXOOOXXOO", then there's three maximal consecutive "O"s block "OO", "OOO", "OO", so your score will be $ 2^{2}+3^{2}+2^{2}=17 $ . If there are no correct clicks in a play then the score for the play equals to $ 0 $ .

You know that the probability to click the $ i $ -th $ (1<=i<=n) $ click correctly is $ p_{i} $ . In other words, the $ i $ -th character in the play sequence has $ p_{i} $ probability to be "O", $ 1-p_{i} $ to be "X". You task is to calculate the expected score for your play.

## 输入格式

The first line contains an integer $ n $ ( $ 1<=n<=10^{5} $ ) — the number of clicks. The second line contains $ n $ space-separated real numbers $ p_{1}, p_{2},..., p_{n} $ $ (0<=p_{i}<=1) $ .

There will be at most six digits after the decimal point in the given $ p_{i} $ .

## 输出格式

Print a single real number — the expected score for your play. Your answer will be considered correct if its absolute or relative error does not exceed $ 10^{-6} $ .

## 样例 #1

### 样例输入 #1

```
3
0.5 0.5 0.5
```

### 样例输出 #1

```
2.750000000000000
```

## 样例 #2

### 样例输入 #2

```
4
0.7 0.2 0.1 0.9
```

### 样例输出 #2

```
2.489200000000000
```

## 样例 #3

### 样例输入 #3

```
5
1 1 1 1 1
```

### 样例输出 #3

```
25.000000000000000
```

## 提示

For the first example. There are 8 possible outcomes. Each has a probability of 0.125.

- "OOO" $ → $ $ 3^{2}=9 $ ;
- "OOX" $ → $ $ 2^{2}=4 $ ;
- "OXO" $ → $ $ 1^{2}+1^{2}=2 $ ;
- "OXX" $ → $ $ 1^{2}=1 $ ;
- "XOO" $ → $ $ 2^{2}=4 $ ;
- "XOX" $ → $ $ 1^{2}=1 $ ;
- "XXO" $ → $ $ 1^{2}=1 $ ;
- "XXX" $ → $ $ 0 $ .

So the expected score is ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF235B/429494dd4621ffc251be5afa17bcee704d7359f4.png)

## 题解
其实我们这一题最重要的一点，是怎么把我们的**状态变换转换为我们的期待**。我们这一题的状态变化其实是很好象的，其实我们本题一共无非也就两种，一种是和前一个接上了，另一个是和前一个没有接上。

那么我们因为我们是求期望，我们就**对于上面的两种情况取平均**就是**我们的最后的答案**，但是我们注意到，我们这一题中，我们要求我们的 $x_{i}^2$ 的平均数，这个显然是 u 不能一步直接推到的。我们需要通过我们的其他方式来推导得到。

我们就需要推到，我们的**二次方期望之间的递推关系**，显然，我们需要在两者之间做差，我们就有：$(x^2)=(x-1)^2+2x-1$ 这个式子就告诉我们的**二次项的地推可以通过我们的一次项来得到**。

而我们**恰好发现，我们的二次方期望就是我们的答案**，于是，我们直接进行一个答案的输出即可

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5 + 10;
int n;
double p1[N], p2[N], f[N];

int main() {
	scanf("%d", &n);
	for(int i = 1 ; i <= n ; ++ i) {
		double p; scanf("%lf", &p);
		p1[i] = p * (p1[i - 1] + 1);
		f[i] = f[i - 1] + p * (1 + 2 * p1[i - 1]);
	}
	printf("%.10lf\n", f[n]);
}
```