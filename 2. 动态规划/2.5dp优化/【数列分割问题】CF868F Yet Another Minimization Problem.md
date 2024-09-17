# Yet Another Minimization Problem

## 题面翻译

题目描述：给定一个序列 $a$，要把它分成 $k$ 个子段。每个子段的费用是**其中相同元素的对数**。求所有子段的费用之和的最小值。

输入格式：第一行输入 $n$（序列长度）和 $k$（需分子段数）。接下来一行有 $n$ 个数，第 $i$ 个数表示序列的第 $i$ 个元素 $a_i$。

输出格式：输出一个数，费用和的最小值。

$2 \leq n \leq 10^5$，$2 \leq k \leq \min(n,20)$，$1 \leq a_i \leq n$ 。

## 题目描述

You are given an array of $ n $ integers $ a_{1}...\ a_{n} $ . The cost of a subsegment is the number of unordered pairs of distinct indices within the subsegment that contain equal elements. Split the given array into $ k $ non-intersecting non-empty subsegments so that the sum of their costs is minimum possible. Each element should be present in exactly one subsegment.

## 输入格式

The first line contains two integers $ n $ and $ k $ ( $ 2<=n<=10^{5} $ , $ 2<=k<=min\ (n, 20)) $ — the length of the array and the number of segments you need to split the array into.

The next line contains $ n $ integers $ a_{1}, a_{2},..., a_{n} $ ( $ 1<=a_{i}<=n $ ) — the elements of the array.

## 输出格式

Print single integer: the minimum possible total cost of resulting subsegments.

## 样例 #1

### 样例输入 #1

```
7 3
1 1 3 3 3 2 1
```

### 样例输出 #1

```
1
```

## 样例 #2

### 样例输入 #2

```
10 2
1 2 1 2 1 2 1 2 1 2
```

### 样例输出 #2

```
8
```

## 样例 #3

### 样例输入 #3

```
13 3
1 2 2 2 1 2 1 1 1 2 2 1 1
```

### 样例输出 #3

```
9
```

## 提示

In the first example it's optimal to split the sequence into the following three subsegments: $ [1] $ , $ [1,3] $ , $ [3,3,2,1] $ . The costs are $ 0 $ , $ 0 $ and $ 1 $ , thus the answer is $ 1 $ .

In the second example it's optimal to split the sequence in two equal halves. The cost for each half is $ 4 $ .

In the third example it's optimal to split the sequence in the following way: $ [1,2,2,2,1] $ , $ [2,1,1,1,2] $ , $ [2,1,1] $ . The costs are $ 4 $ , $ 4 $ , $ 1 $ .


## 题解
我们首先考虑暴力转移，我们设我们的 $f[i][k]$ 表示我们把我们的序列进行到 i 分成了 k 段，我们的答案是多少。

于是，我们就可以有：
$f[i][k]=f[j][k-1]+calc(i,j)$

其中我们的 $calc(i,j)$ 表示我们 $i,j$ 区间内我们相同的数的对数是多少。

很显然，我们的 $calc(i,j)$ 是 $o(n)$ 的，而我们的 $f[i][j]$ 也是 $o(20n)$ 的，因此暴力的复杂度就是我们的 $o(20n^2)$,显然不能通过。

于是我们考虑这么一种方法：我们维护一对 $l,r$，我们记录 $[l,r]$ 中每个数字出现的次数，这样我们在 $l$ 或 $r$ 改变 1 时可以 $o(1)$ 的计算出我们的答案。

剩下的就是我们的 dp 优化，我们在这里暂时按下不表