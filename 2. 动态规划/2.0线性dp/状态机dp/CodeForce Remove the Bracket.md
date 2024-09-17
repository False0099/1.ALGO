# 知识点
  ## [[动态规划]]
# 题目 
# Remove the Bracket

## 题面翻译

### 题目描述

RSJ 得到了一个长为 $n$ 的序列 $a_1,a_2, \ldots, a_n$ 和一个正整数 $s$，他想要计算 $\prod\limits_{i=1}^n a_i$。对于 $a_2,a_3, \ldots, a_{n-1}$ 中的每一个，他都选取了一对**非负整数** $x_i,y_i$ 使得 $x_i + y_i = a_i$ 且 $(x_i-s) \cdot (y_i-s) \geq 0$。他使用如下的方法计算：

$$
\begin{aligned}
\text{Product} &= a_1 \cdot a_2 \cdot a_3 \cdot \ldots \cdot a_n \\
&= a_1 \cdot (x_2+y_2) \cdot (x_3+y_3) \cdot (x_4 + y_4) \cdot \ldots \cdot (x_{n-1}+y_{n-1}) \cdot a_n \\
&\overset{\text{?}}{=} a_1 \cdot x_2+y_2 \cdot x_3+y_3 \cdot x_4 + y_4 \cdot \ldots \cdot x_{n-1}+y_{n-1} \cdot a_n
\end{aligned}
$$

但是他在计算时出现了错误，不小心把括号弄丢了（式子第 $3$ 行）。于是，他想要知道写错了的式子（$F = a_1 \cdot x_2+y_2 \cdot x_3+y_3 \cdot x_4 + y_4 \cdot \ldots \cdot x_{n-1}+y_{n-1} \cdot a_n$）的最小值是多少。

~~这是原本的题面，审核改成了现在的样子（真就 remove the bracket 了，导致赛时式子有歧义，在此向大家道歉~~

### 输入格式

输入第一行一个正整数 $t$（$1\le t\le 10^4$）表示数据组数。

每组数据两行，第一行两个正整数 $n,s$（$3 \le n \le 2 \cdot 10^5$，$0 \le s \le 2 \cdot 10^5$），含义见题目描述。

第二行 $n$ 个正整数 $a_1,a_2,\ldots,a_n$（$0 \le a_i \le 2 \cdot 10^5$）表示序列 $a$。

保证所有测试数据的 $n$ 之和不超过 $2\cdot 10^5$。

### 输出格式

每组测试数据输出一行一个正整数表示 $F$ 的最小值。

### 样例解释

第一组测试数据中，$2\cdot 0+0\cdot 1+0\cdot 3+0\cdot 4 = 0$。

第二组测试数据中，$5\cdot 1+2\cdot 2+2\cdot 2+1\cdot 5 = 18$。

## 题目描述

RSJ has a sequence $ a $ of $ n $ integers $ a_1, a_2, \ldots, a_n $ and an integer $ s $ . For each of $ a_2, a_3, \ldots, a_{n-1} $ , he chose a pair of non-negative integers $ x_i $ and $ y_i $ such that $ x_i+y_i=a_i $ and $ (x_i-s) \cdot (y_i-s) \geq 0 $ .

Now he is interested in the value $ $$$F = a_1 \cdot x_2+y_2 \cdot x_3+y_3 \cdot x_4 + \ldots + y_{n - 2} \cdot x_{n-1}+y_{n-1} \cdot a_n. $ $ </p><p>Please help him find the minimum possible value  $ F $  he can get by choosing  $ x\_i $  and  $ y\_i$$ $ optimally. It can be shown that there is always at least one valid way to choose them.

## 输入格式

Each test contains multiple test cases. The first line contains an integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

The first line of each test case contains two integers $ n $ , $ s $ ( $ 3 \le n \le 2 \cdot 10^5 $ ; $ 0 \le s \le 2 \cdot 10^5 $ ).

The second line contains $ n $ integers $ a_1, a_2,\ldots, a_n $ ( $ 0 \le a_i \le 2 \cdot 10^5 $ ).

It is guaranteed that the sum of $ n $ does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, print the minimum possible value of $ F $ .

## 样例 #1

### 样例输入 #1

```
10
5 0
2 0 1 3 4
5 1
5 3 4 3 5
7 2
7 6 5 4 3 2 1
5 1
1 2 3 4 5
5 2
1 2 3 4 5
4 0
0 1 1 1
5 5
4 3 5 6 4
4 1
0 2 1 0
3 99999
200000 200000 200000
6 8139
7976 129785 12984 78561 173685 15480
```

### 样例输出 #1

```
0
18
32
11
14
0
16
0
40000000000
2700826806
```

## 提示

In the first test case, $ 2\cdot 0+0\cdot 1+0\cdot 3+0\cdot 4 = 0 $ .

In the second test case, $ 5\cdot 1+2\cdot 2+2\cdot 2+1\cdot 5 = 18 $ .

# 思路
·我们先推导性质：如果想要结果最优，一定满足将数组分解成一个大数和一个小数，且这个极差越大越好，否则不可能是最优解。
·于是，我们就可以在这个基础上先预处理出每一个区间所能分解出的极差最大的分解方法，并且我们可以把最大的记为 $1$，极小的记为 $0$，我们于是在每一个位置的乘积就只会有下面几种情况 $0*0，1*1，1*0，0*1$，$dp[i][j]$ 表示处理了前 i 组，第 i 组取上/下界的最小值，我们可以写出转移方程 
$dp[i][0] = min(dp[i - 1][0] + maxi[i - 1] * mini[i], dp[i - 1][1] + mini[i - 1] * mini[i])$
$dp[i][1] = min(dp[i - 1][0] + maxi[i - 1] * maxi[i], dp[i - 1][1] + mini[i - 1] * maxi[i])$

# AC 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
long long t, n, s, a[200005], maxi[200005], mini[200005], dp[200005][2];
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> t;
    while(t--) {
        cin >> n >> s;
        for(int i = 1; i <= n; i++) {
            cin >> a[i];
            if(a[i] >= 2 * s)
                maxi[i] = a[i] - s, mini[i] = s;
            else
                mini[i] = max(0ll, a[i] - s), maxi[i] = a[i] - mini[i];
        }
        dp[2][0] = a[1] * mini[2], dp[2][1] = a[1] * maxi[2];
        for(int i = 3; i < n; i++)
            dp[i][0] = min(dp[i - 1][0] + maxi[i - 1] * mini[i], dp[i - 1][1] + mini[i - 1] * mini[i]);
            dp[i][1] = min(dp[i - 1][0] + maxi[i - 1] * maxi[i], dp[i - 1][1] + mini[i - 1] * maxi[i]);
        cout << min(dp[n - 1][0] + a[n] * maxi[n - 1], dp[n - 1][1] + a[n] * mini[n - 1]) << '\n';
    }
    return 0;
}
```
# 备注
