# Even-Odd XOR

## 题面翻译

### 题目描述

给定一个正整数 $n$，请你找出一个长度为 $n$ 数组 $a$，满足数组是由互不相同的非负且小于 $2^{31}$ 的整数组成，并且该数组中奇数项上元素的[异或和](https://en.wikipedia.org/wiki/Bitwise_operation#XOR)与偶数项上元素的异或和要相等。

### 输入格式

输入的第一行为一个整数 $t$ $(1 \leq t \leq 629)$，表示测试点的数量。

接下来 $t$ 行，每行一个整数 $n$ $(3 \leq n \leq 2 \times 10^5)$，表示数组的长度。

保证所有测试点中 $n$ 的总和不超过 $2 \times 10^5$。

### 输出格式

对于每个测试点，在一行中输出 $n$ 个不同的满足条件的整数。

如果有多种答案，你可以输出任意一种。

### 样例解释

在第一个测试点中，奇数项的异或和为 $4 \oplus 1 \oplus 0 \oplus 7 = 2$；偶数项的异或和为 $2 \oplus 5 \oplus 6 \oplus 3 = 2$。

## 题目描述

Given an integer $ n $ , find any array $ a $ of $ n $ distinct nonnegative integers less than $ 2^{31} $ such that the [bitwise XOR](https://en.wikipedia.org/wiki/Bitwise_operation#XOR) of the elements on odd indices equals the bitwise XOR of the elements on even indices.

## 输入格式

The first line of the input contains an integer $ t $ ( $ 1 \leq t \leq 629 $ ) — the number of test cases.

Then $ t $ lines follow, each containing a single integer $ n $ $ (3 \leq n \leq 2\cdot 10^5) $ — the length of the array.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2\cdot 10^5 $ .

## 输出格式

For each test case, output one line containing $ n $ distinct integers that satisfy the conditions.

If there are multiple answers, you can output any of them.

## 样例 #1

### 样例输入 #1

```
7
8
3
4
5
6
7
9
```

### 样例输出 #1

```
4 2 1 5 0 6 7 3
2 1 3
2 1 3 0
2 0 4 5 3
4 1 2 12 3 8
1 2 3 4 5 6 7
8 2 3 7 4 0 5 6 9
```

## 提示

In the first test case the XOR on odd indices is $ 4 \oplus 1 \oplus 0 \oplus 7 = 2 $ and the XOR on even indices is $ 2 \oplus 5 \oplus 6 \oplus 3= 2 $ .

## 题解
看到异或和相等，我们第一时间就要想到一个性质：如果一个偶数和他的下一个数异或，那么它的结果一定是 1

这一题，我们可以考虑这么一种性质：**如果一个数和他的下一个数异或，我们的结果一定是 1**，于是，我们就可以知道，如果我们的 n 可以被 4 整除，我们只需要直接令 $a[i]=i$ 即可。

除此之外，我们因为我们出题人心善，给了我们 $5,6,7$ 的情况，那么我们就可以在上面这三种情况下继续每次对于一个周期 4，我们就构造对应的要求即可。

```cpp
```cpp
int w=0;
for(int i=1;i<=n-3;i++)cout<<i<<" ",w^=i;
cout<<(1<<23)<<" "<<(1<<24)<<" "<<(w^(1<<23)^(1<<24));
```
```