# Little Pony and Expected Maximum

## 题面翻译

暮暮刚刚在和她的朋友——AJ（苹果杰克）、FS（小蝶）、RD（云宝黛西）玩 Ludo 游戏。但是她马品没攒够总是输。回到城堡过后，她对游戏用的骰子产生了兴趣。

题目描述

这个骰子有 M 面：骰子的第一面有一个点，第二面有两个点，以此类推，第 m 面含有 M 点。暮暮确信的是，当掷骰子时，每一面都有 1/m 的可能性出现，并且每次投掷的概率都是都是独立的。请你帮助她计算掷 N 次骰子后每次得到的点数中最大值的期望。

输入输出格式

输入格式：

一行两个整数 m 和 n (1 ≤ m, n ≤ 10^5).

输出格式：

输出一行一个实数，与答案误差不大于 10^-4

## 题目描述

Twilight Sparkle was playing Ludo with her friends Rainbow Dash, Apple Jack and Flutter Shy. But she kept losing. Having returned to the castle, Twilight Sparkle became interested in the dice that were used in the game.

The dice has $ m $ faces: the first face of the dice contains a dot, the second one contains two dots, and so on, the $ m $ -th face contains $ m $ dots. Twilight Sparkle is sure that when the dice is tossed, each face appears with probability ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF453A/b5732959c34191186d5d84c95f93d0143eb6fff6.png). Also she knows that each toss is independent from others. Help her to calculate the expected maximum number of dots she could get after tossing the dice $ n $ times.

## 输入格式

A single line contains two integers $ m $ and $ n $ ( $ 1<=m, n<=10^{5} $ ).

## 输出格式

Output a single real number corresponding to the expected maximum. The answer will be considered correct if its relative or absolute error doesn't exceed $ 10^{-4} $ .

## 样例 #1

### 样例输入 #1

```
6 1
```

### 样例输出 #1

```
3.500000000000
```

## 样例 #2

### 样例输入 #2

```
6 3
```

### 样例输出 #2

```
4.958333333333
```

## 样例 #3

### 样例输入 #3

```
2 2
```

### 样例输出 #3

```
1.750000000000
```

## 提示

Consider the third test example. If you've made two tosses:

1. You can get 1 in the first toss, and 2 in the second. Maximum equals to 2.
2. You can get 1 in the first toss, and 1 in the second. Maximum equals to 1.
3. You can get 2 in the first toss, and 1 in the second. Maximum equals to 2.
4. You can get 2 in the first toss, and 2 in the second. Maximum equals to 2.

The probability of each outcome is 0.25, that is expectation equals to:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF453A/a611917193fd806daca7707d914db660d20dd0a4.png)You can read about expectation using the following link: http://en.wikipedia.org/wiki/Expected\_value

## 题解
一道期望 DP

$$\begin{aligned}
E(\mathrm{max})& =\sum_{i=1}^mP(\max=i)\times i  \\
&=\sum_{i=1}^m(P(\max\leq i)-P(\max\leq i-1))\times i \\
&=\sum_{i=1}^m(\frac{i^n}{m^n}-\frac{(i-1)^n}{m^n})\times i \\
&=\sum_{i=1}^m((\frac im)^n-(\frac{i-1}m)^n)\times i
\end{aligned}$$


```cpp
#include<cstdio>
#include<cmath>
using namespace std;
double n,m,ans;
int main(){
	scanf("%lf%lf",&m,&n);
	for(double i=1;i<=m;i++)
	ans+=i*(pow(i/m,n)-pow((i-1)/m,n));
	printf("%.12lf\n",ans);
}
```