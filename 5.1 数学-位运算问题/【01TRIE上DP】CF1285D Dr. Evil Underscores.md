# Dr. Evil Underscores

## 题面翻译

有一个长度为 $n\ (1\leq n\leq 10^5)$ 的整数序列 $a_1,\cdots,a_n\ \ (0\leq a_i\leq 2^{30}-1)$，你需要找到一个非负整数 $X$ 使得 $\max(a_i\oplus X)$ 最小，其中 $\oplus$ 为按位异或运算。

输入这个序列，输出 $\max(a_i\oplus X)$ 的最小值。

## 题目描述

Today, as a friendship gift, Bakry gave Badawy $ n $ integers $ a_1, a_2, \dots, a_n $ and challenged him to choose an integer $ X $ such that the value $ \underset{1 \leq i \leq n}{\max} (a_i \oplus X) $ is minimum possible, where $ \oplus $ denotes the [bitwise XOR operation](https://en.wikipedia.org/wiki/Bitwise_operation#XOR).

As always, Badawy is too lazy, so you decided to help him and find the minimum possible value of $ \underset{1 \leq i \leq n}{\max} (a_i \oplus X) $ .

## 输入格式

The first line contains integer $ n $ ( $ 1\le n \le 10^5 $ ).

The second line contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ 0 \le a_i \le 2^{30}-1 $ ).

## 输出格式

Print one integer — the minimum possible value of $ \underset{1 \leq i \leq n}{\max} (a_i \oplus X) $ .

## 样例 #1

### 样例输入 #1

```
3
1 2 3
```

### 样例输出 #1

```
2
```

## 样例 #2

### 样例输入 #2

```
2
1 5
```

### 样例输出 #2

```
4
```

## 提示

In the first sample, we can choose $ X = 3 $ .

In the second sample, we can choose $ X = 5 $ .