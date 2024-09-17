# Ilya and Escalator

## 题面翻译

有 $n$ 个人排成一列 $,$ 每秒中队伍最前面的人 $p$ 的概率走上电梯 $($ 一旦走上就不会下电梯 $),$ 或者有 $1-p$ 的概率不动

问你 $T$ 秒过后 $,$ 在电梯上的人的数量的期望 $.$ 

感谢@Kelin 提供的翻译

## 题目描述

Ilya got tired of sports programming, left university and got a job in the subway. He was given the task to determine the escalator load factor.

Let's assume that $ n $ people stand in the queue for the escalator. At each second one of the two following possibilities takes place: either the first person in the queue enters the escalator with probability $ p $ , or the first person in the queue doesn't move with probability $ (1-p) $ , paralyzed by his fear of escalators and making the whole queue wait behind him.

Formally speaking, the $ i $ -th person in the queue cannot enter the escalator until people with indices from $ 1 $ to $ i-1 $ inclusive enter it. In one second only one person can enter the escalator. The escalator is infinite, so if a person enters it, he never leaves it, that is he will be standing on the escalator at any following second. Ilya needs to count the expected value of the number of people standing on the escalator after $ t $ seconds.

Your task is to help him solve this complicated task.

## 输入格式

The first line of the input contains three numbers $ n, p, t $ ( $ 1<=n, t<=2000 $ , $ 0<=p<=1 $ ). Numbers $ n $ and $ t $ are integers, number $ p $ is real, given with exactly two digits after the decimal point.

## 输出格式

Print a single real number — the expected number of people who will be standing on the escalator after $ t $ seconds. The absolute or relative error mustn't exceed $ 10^{-6} $ .

## 样例 #1

### 样例输入 #1

```
1 0.50 1
```

### 样例输出 #1

```
0.5
```

## 样例 #2

### 样例输入 #2

```
1 0.50 4
```

### 样例输出 #2

```
0.9375
```

## 样例 #3

### 样例输入 #3

```
4 0.20 2
```

### 样例输出 #3

```
0.4
```


## 题解
我们这一题的思想就是采用我们的贡献法，计算 T 时刻有 j 个人上车期望次数是多少，然后再乘以出现的频率，而这里，我们的期望就需要用我们的概率乘以贡献来计算，我们设 $T$ 时刻，有 $j$ 个人已经上车，那么我们就有 $dp[T][j]=p\times dp[t-1][j-1]+(1-p)dp[t-1][j]$
于是我们这一个状态的贡献就是 $dp[t][j]*j$,最后我们只需要一个简单的计算即可。

```cpp
#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 2000 + 3, MAX_T = 2000 + 3;
int n, t;

double p, dp[MAX_T][MAX_N];

int main() {
    scanf("%d%lf%d", &n, &p, &t);

    dp[0][0] = 1;

    for (int i = 0; i < t; ++i) {
        dp[i + 1][n] += dp[i][n];
        for (int j = 0; j < n; ++j) if (dp[i][j] > 1e-10) {
            dp[i + 1][j + 1] += dp[i][j] * p;
            dp[i + 1][j] += dp[i][j] * (1 - p);
        }
    }

    double ans = 0;
    for (int i = 0; i <= n; ++i) ans += i * dp[t][i];
    printf("%.6f\n", ans);
    return 0;
}
```