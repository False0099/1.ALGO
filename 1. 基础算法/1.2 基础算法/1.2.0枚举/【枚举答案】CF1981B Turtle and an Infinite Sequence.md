# Turtle and an Infinite Sequence

## 题目描述

There is a sequence $ a_0, a_1, a_2, \ldots $ of infinite length. Initially $ a_i = i $ for every non-negative integer $ i $ .

After every second, each element of the sequence will simultaneously change. $ a_i $ will change to $ a_{i - 1} \mid a_i \mid a_{i + 1} $ for every positive integer $ i $ . $ a_0 $ will change to $ a_0 \mid a_1 $ . Here, $ | $ denotes [bitwise OR](https://en.wikipedia.org/wiki/Bitwise_operation#OR).

Turtle is asked to find the value of $ a_n $ after $ m $ seconds. In particular, if $ m = 0 $ , then he needs to find the initial value of $ a_n $ . He is tired of calculating so many values, so please help him!

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10^4 $ ). The description of the test cases follows.

The first line of each test case contains two integers $ n, m $ ( $ 0 \le n, m \le 10^9 $ ).

## 输出格式

For each test case, output a single integer — the value of $ a_n $ after $ m $ seconds.

## 样例 #1

### 样例输入 #1

```
9
0 0
0 1
0 2
1 0
5 2
10 1
20 3
1145 14
19198 10
```

### 样例输出 #1

```
0
1
3
1
7
11
23
1279
19455
```

## 提示

After $ 1 $ second, $ [a_0, a_1, a_2, a_3, a_4, a_5] $ will become $ [1, 3, 3, 7, 7, 7] $ .

After $ 2 $ seconds, $ [a_0, a_1, a_2, a_3, a_4, a_5] $ will become $ [3, 3, 7, 7, 7, 7] $ .

## 题解
本题我们可以通过我们的枚举答案的方法来计算得到我们的最终结果，例如我们可以**拆分我们的二进制位**，考虑我们的每一个二进制位的贡献。
设当前在考虑第 $d$ 个二进制位，那么 $a_i=\left\lfloor\frac i{2^d}\right\rfloor$ mod 2。
每过一秒，一个 1 会往左边和右边"扩散"1 格。如果 $a_n$ 一开始就是 1 那么答案的这一位就是 1。否则 $a_n$ 处于一个 0 的连续段中，我们需要计算这个连续段左边的 1 和右边的 1 能否"扩散"到 $a_n$。设 $x=n$ mod $2^{d+1}$,那么 $0\leq x\leq2^d-1$。左边的 1 扩散到 $a_n$ 需要 $x+1$ 秒，右边的 1 扩散到 $a_n$ 需要 $2^d-x$ 秒。所以若 $\min(x+1,2^d-x)\leq m$ 那么 $a_n$ 就能变成 1。特别地，若 $n<2^d$ 那么左边没有 1, 所以这种情况若 $2^d-x\leq m$ 那么 $a_n$ 就能变成 1。



时间复杂度：每个测试用例 $O(\log(n+m))$。