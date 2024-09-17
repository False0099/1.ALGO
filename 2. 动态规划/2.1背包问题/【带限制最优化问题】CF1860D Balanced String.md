# Balanced String

## 题面翻译

给你一个长为 $n$ 的 $01$ 字符串 ，每次操作交换两个元素，求最少几次操作能使字符串的**顺序对个数与逆序对个数相等**。

## 题目描述

You are given a binary string $ s $ (a binary string is a string consisting of characters 0 and/or 1).

Let's call a binary string balanced if the number of subsequences 01 (the number of indices $ i $ and $ j $ such that $ 1 \le i < j \le n $ , $ s_i=0 $ and $ s_j=1 $ ) equals to the number of subsequences 10 (the number of indices $ k $ and $ l $ such that $ 1 \le k < l \le n $ , $ s_k=1 $ and $ s_l=0 $ ) in it.

For example, the string 1000110 is balanced, because both the number of subsequences 01 and the number of subsequences 10 are equal to $ 6 $ . On the other hand, 11010 is not balanced, because the number of subsequences 01 is $ 1 $ , but the number of subsequences 10 is $ 5 $ .

You can perform the following operation any number of times: choose two characters in $ s $ and swap them. Your task is to calculate the minimum number of operations to make the string $ s $ balanced.

## 输入格式

The only line contains the string $ s $ ( $ 3 \le |s| \le 100 $ ) consisting of characters 0 and/or 1.

Additional constraint on the input: the string $ s $ can be made balanced.

## 输出格式

Print a single integer — the minimum number of swap operations to make the string $ s $ balanced.

## 样例 #1

### 样例输入 #1

```
101
```

### 样例输出 #1

```
0
```

## 样例 #2

### 样例输入 #2

```
1000110
```

### 样例输出 #2

```
0
```

## 样例 #3

### 样例输入 #3

```
11010
```

### 样例输出 #3

```
1
```

## 样例 #4

### 样例输入 #4

```
11001100
```

### 样例输出 #4

```
2
```

## 提示

In the first example, the string is already balanced, the number of both 01 and 10 is equal to $ 1 $ .

In the second example, the string is already balanced, the number of both 01 and 10 is equal to $ 6 $ .

In the third example, one of the possible answers is the following one: 11010 $ \rightarrow $ 01110. After that, the number of both 01 and 10 is equal to $ 3 $ .

In the fourth example, one of the possible answers is the following one: 11001100 $ \rightarrow $ 11001010 $ \rightarrow $ 11000011. After that, the number of both 01 and 10 is equal to $ 8 $ .

## 题解
我们已知，每次操作后，我们 0 的数量和 1 的数量不会改变，00 和 11 的数量也不会改变，长度为 2 的子序列数不变。
我们的 01 和 10 的最终数量就是
$K=\dfrac{n(n-1)-cnt_{1}\times (cnt_{1}-1)-cnt_{0}\times(cnt_{0}-1)}{2}$
于是我们就可以设我们的 $dp[i][j][k]$ 表示前 i 个元素中有 j 个 1，01 和 11 的数量为 k 的最小代价是多少，我们的转移就可以写出
假设我们第 i 个元素填 0，那么哦我们有 $dp[i][j][k]=dp[i-1][j][k]$,我们第 i 个元素填 1，那么哦我们有 
$dp[i][j][k]=dp[i-1][j-1][k-i]+[s_{i}\neq 1]$

