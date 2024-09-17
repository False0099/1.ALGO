# Factorial Divisibility

## 题面翻译

### 题面翻译

给定两个正整数 $n$ 和 $x$ 和一个正整数序列 $a_1 \sim a_n$。

请问 $\sum_{i = 1}^n a_i!$ 是否能被 $x!$ 整除。如果能则输出一个字符串 $\texttt{Yes}$，不能则输出字符串 $\texttt{No}$。

### 输入格式

第一行两个正整数 $n$ 和 $x$。

第二行 $n$ 个正整数 $a_1 \sim a_n$。

### 输出格式

一行一个字符串，输出 $\texttt{Yes}$ 或 $\texttt{No}$。

## 题目描述

You are given an integer $ x $ and an array of integers $ a_1, a_2, \ldots, a_n $ . You have to determine if the number $ a_1! + a_2! + \ldots + a_n! $ is divisible by $ x! $ .

Here $ k! $ is a factorial of $ k $ — the product of all positive integers less than or equal to $ k $ . For example, $ 3! = 1 \cdot 2 \cdot 3 = 6 $ , and $ 5! = 1 \cdot 2 \cdot 3 \cdot 4 \cdot 5 = 120 $ .

## 输入格式

The first line contains two integers $ n $ and $ x $ ( $ 1 \le n \le 500\, 000 $ , $ 1 \le x \le 500\, 000 $ ).

The second line contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le x $ ) — elements of given array.

## 输出格式

In the only line print "Yes" (without quotes) if $ a_1! + a_2! + \ldots + a_n! $ is divisible by $ x! $ , and "No" (without quotes) otherwise.

## 样例 #1

### 样例输入 #1

```
6 4
3 2 2 2 3 3
```

### 样例输出 #1

```
Yes
```

## 样例 #2

### 样例输入 #2

```
8 3
3 2 2 2 2 2 1 1
```

### 样例输出 #2

```
Yes
```

## 样例 #3

### 样例输入 #3

```
7 8
7 7 7 7 7 7 7
```

### 样例输出 #3

```
No
```

## 样例 #4

### 样例输入 #4

```
10 5
4 3 2 1 4 3 2 4 3 4
```

### 样例输出 #4

```
No
```

## 样例 #5

### 样例输入 #5

```
2 500000
499999 499999
```

### 样例输出 #5

```
No
```

## 提示

In the first example $ 3! + 2! + 2! + 2! + 3! + 3! = 6 + 2 + 2 + 2 + 6 + 6 = 24 $ . Number $ 24 $ is divisible by $ 4! = 24 $ .

In the second example $ 3! + 2! + 2! + 2! + 2! + 2! + 1! + 1! = 18 $ , is divisible by $ 3! = 6 $ .

In the third example $ 7! + 7! + 7! + 7! + 7! + 7! + 7! = 7 \cdot 7! $ . It is easy to prove that this number is not divisible by $ 8! $ .

## 题解
本题我们要求一个数组的阶乘和能够整除我们的某一个阶乘，这里我们有一个结论，我们如果我们的阶乘和能够整除我们的某一个结成，**当且仅当我们的阶乘之和可以转换为我们的若干个原来阶乘的和，且没有其他的元素剩余**。这个是我们的**整除带给我们的结论**，转换为人话就是：$\sum a_{i}!=k*x!$。于是，我们就可以考虑能不能把我们的阶乘都转换为我们的 $x!$ 的这一种形式。

首先，如果我们的结成的项是大于我们的 x 的，那么我们一定是可以组合成我们的原来的要求的，这一点因为我们的结成定义。

其次，如果我们的最后的结果是