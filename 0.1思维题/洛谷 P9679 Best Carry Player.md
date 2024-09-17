# [ICPC 2022 Jinan R] Best Carry Player

## 题面翻译

### 简要题面

这里我们定义一个电脑运行 $a+b$ 的速度是 $a+b$ 中出现的进位的次数。

给定一个数组 $a_1,a_2,...,a_n$，请找出正确的排序使得计算这个数组的和时运行的速度最短，请找出最少的进位次数。

### 输入格式

**本题有多组数据**。

第一行一个整数 $T$，表示数据组数。

对于每组数据：

第一行一个整数 $n$。  

接下来一行 $n$ 个整数，表示输入的数组 $a$。

### 输出格式

对于每组数据，输出最小的进位次数。

### 数据范围

对于 $100 \%$ 的数据： $1 \leq \sum n \leq 10^5$， $1 \leq a_i \leq 10^9$

## 题目描述

Prof. Pang is given $n$ numbers $a_1,\ldots, a_n$. It is easy to add the numbers up using a computer. But Prof. Pang treasures his computer so much and wants to reduce its workload. He decides to simulate the following program by hand. 

![](https://cdn.luogu.com.cn/upload/image_hosting/ajtj92in.png)


Unlike a computer, the time needed for Prof. Pang to simulate the program is proportional to the total number of **carries**(which means “进位” in Chinese) when calculating $s+a[i]$ for each $i$ from $1$ to $n$. Prof. Pang adds numbers **by column addition in base-ten**, just like what we normally do in primary school. For example, there are two carries in the following addition.

![](https://cdn.luogu.com.cn/upload/image_hosting/c779jeox.png)

Please permute the array $a_1,\ldots, a_n$ so that the total number of carries when Prof. Pang simulates the program is as small as possible. (By ''permute an array'', we mean that you can change the order of the elements arbitrarily.)

## 输入格式

The first line contains one integer $T~(1\le T \le 10^5)$, the number of test cases.

For each test case, the first line contains one positive integer $n~(1\le n \le 10^5)$. The next line contains $n$ integers $a_1,\ldots, a_n~(1 \le a_i\le 10^9)$ denoting the numbers Prof. Pang is given. 

It is guaranteed that the sum of $n$ over all test cases is no more than $10^5$.

## 输出格式

For each test case, output one line containing the minimum amount of carries.

## 样例 #1

### 样例输入 #1

```
2
3
9 99 999
1
12345
```

### 样例输出 #1

```
5
0
```