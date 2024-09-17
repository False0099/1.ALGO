# Writing Code

## 题面翻译

## 题目描述：

有 $n$ 个程序员，每个程序员都可以写任意行代码，总共要编写 $m$ 行代码，这 $m$ 行代码可以由多个程序员来编写。但是第 $i$ 个程序员在一行代码中会出现 $a_i$ 个 bug。现在希望知道有多少种方案能使得这 $m$ 行代码中的 bug 的数量不超过 $b$ 个。  
两个方案不同当且仅当某个程序员编写的代码量（行数）不同。  

## 输入格式：

输入第一行包含四个整数 $n,m,b,mod$。  
接下来一行 $n$ 个整数 $a_i$。 

## 输出格式：

输出一行一个整数，表示 $m$ 行代码 bug 数量不超过 $b$ 的方案数对 $mod$ 取模后的答案。

## 提示说明：

$1 \le n,m \le 500,0 \le b \le 500;1 \le mod \le 10^9+7;0 \le a_i \le 500$

Translated by @Mine_King

## 题目描述

Programmers working on a large project have just received a task to write exactly $ m $ lines of code. There are $ n $ programmers working on a project, the $ i $ -th of them makes exactly $ a_{i} $ bugs in every line of code that he writes.

Let's call a sequence of non-negative integers $ v_{1}, v_{2},..., v_{n} $ a plan, if $ v_{1}+v_{2}+...+v_{n}=m $ . The programmers follow the plan like that: in the beginning the first programmer writes the first $ v_{1} $ lines of the given task, then the second programmer writes $ v_{2} $ more lines of the given task, and so on. In the end, the last programmer writes the remaining lines of the code. Let's call a plan good, if all the written lines of the task contain at most $ b $ bugs in total.

Your task is to determine how many distinct good plans are there. As the number of plans can be large, print the remainder of this number modulo given positive integer $ mod $ .

## 输入格式

The first line contains four integers $ n $ , $ m $ , $ b $ , $ mod $ ( $ 1<=n, m<=500 $ , $ 0<=b<=500 $ ; $ 1<=mod<=10^{9}+7 $ ) — the number of programmers, the number of lines of code in the task, the maximum total number of bugs respectively and the modulo you should use when printing the answer.

The next line contains $ n $ space-separated integers $ a_{1}, a_{2},..., a_{n} $ ( $ 0<=a_{i}<=500 $ ) — the number of bugs per line for each programmer.

## 输出格式

Print a single integer — the answer to the problem modulo $ mod $ .

## 样例 #1

### 样例输入 #1

```
3 3 3 100
1 1 1
```

### 样例输出 #1

```
10
```

## 样例 #2

### 样例输入 #2

```
3 6 5 1000000007
1 2 3
```

### 样例输出 #2

```
0
```

## 样例 #3

### 样例输入 #3

```
3 5 6 11
1 2 1
```

### 样例输出 #3

```
0
```


## 题解
如果我们没有前置条件的情况下，我们这一题就是一个很典的多重背包问题，二维价值，于是我们的状态转移就可以写成：
$dp[i][j][k]=\sum_{t=1}^{max}dp[i-1][j-t][k-t*a[i]]$

不难发现，上面的 dp 需要 $o(n^4)$ 的时间，确实挺不错的，差点每缓过来。于是我们考虑优化：
1. 时间上的优化，考虑到我们是一个无限背包，所以我们的状态转移方程应该可以写出：$dp[i][j][k]=dp[i-1][j][k]+dp[i][j-1][k-w[i]]$,这样，我们就可以省去我们枚举 t 的时间。
**注意，在上面的转移方程中，我们的 k 要从 0 开始枚举，如果我们的 $k-w[i]$ 不满足转移条件时，我们要直接跳过**

2. 空间上的优化，注意到，我们的 $dp[i]$ 一定是由我们的 $dp[i-1]$ 和 $dp[i]$ 转移而来的，所以我们可以考虑直接省略掉我们的第一维，然后就可以通过本题。