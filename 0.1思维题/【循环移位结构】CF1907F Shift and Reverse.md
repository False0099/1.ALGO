# Shift and Reverse

## 题面翻译

给定一个整数数组 $a_1,a_2,...,a_n$，你可以对其进行两种操作：

* 移位：将最后一个元素移动到第一位，并将其他元素后移，得到数组 $a_n,a_1,a_2,...,a_{n-1}$。
* 翻转：将整个数组翻转过来，得到数组 $a_n,a_{n-1},...,a_2,a_1$。

你的任务是用最少得操作次数来使数组变为单调不降，做不到就输出 `-1`。

## 题目描述

Given an array of integers $ a_1, a_2, \ldots, a_n $ . You can make two types of operations with this array:

- Shift: move the last element of array to the first place, and shift all other elements to the right, so you get the array $ a_n, a_1, a_2, \ldots, a_{n-1} $ .
- Reverse: reverse the whole array, so you get the array $ a_n, a_{n-1}, \ldots, a_1 $ .

Your task is to sort the array in non-decreasing order using the minimal number of operations, or say that it is impossible.

## 输入格式

The first line of input contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases. Descriptions of test cases follow.

The first line of each test case contains an integer $ n $ ( $ 1\le n \le 10^5 $ ) — size of the array.

The second line of each test case contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le 10^9 $ ) — elements of the array.

It is guaranteed that sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case output the number $ k $ , the minimal number of operations you need to sort the array. If it is impossible to sort the array using these operations, output $ -1 $ .

## 样例 #1

### 样例输入 #1

```
11
5
3 2 1 5 4
5
1 1 2 1 1
4
3 7 10 5
5
1 2 3 4 5
2
5 1
3
3 4 1
5
4 1 3 4 4
3
5 1 1
4
2 5 5 4
5
2 2 1 1 2
2
5 5
```

### 样例输出 #1

```
3
2
-1
0
1
1
3
1
2
2
0
```

## 提示

In the first test case of the example, to sort the array \[ $ 3, 2, 1, 5, 4 $ \] you need to perform $ 3 $ operations:

- Shift to obtain the array \[ $ 4, 3, 2, 1, 5 $ \];
- Shift to obtain the array \[ $ 5, 4, 3, 2, 1 $ \];
- Reverse to obtain the array \[ $ 1, 2, 3, 4, 5 $ \].

In the third test case of the example, it can be shown that it is impossible to sort the array using the given operations.

In the seventh test case of the example, to sort the array \[ $ 4, 1, 3, 4, 4 $ \] you need to perform $ 3 $ operations:

- Reverse to obtain the array \[ $ 4, 4, 3, 1, 4 $ \];
- Shift to obtain the array \[ $ 4, 4, 4, 3, 1 $ \];
- Reverse to obtain the array \[ $ 1, 3, 4, 4, 4 $ \].

## 题解
首先，我们本题应该先判断我们是否可行，如果我们是可行的，那么我们一定能通过若干次循环右移操作，先得到我们的 $12345$ 或者我们的 $54321$，然后再根据我们的结果来决定我们是否可以反转。**而我们这里的 12345 和我们的 54321**就是我们的特殊结构。

而我们是否能够通过我们的循环右移得到我们的答案，则可以通过我们倍增我们的数组拼接在我们的尾部，然后再去判断我们的新数组中是否存在 $12345$ 或者 $54321$ 来得到的。

这个时候，我们可以考虑能否得到我们的答案，对于每一种我们的答案，我们都有两种可能的决策，一种是先把我们的元素反转后，再去移动到我们的对应位置，另一类是先移动到对应的位置，然后再去反转。这个时候，我们的第一类计算次数，就是我们的 $x+1$.我们的第二类的计算次数就是我们的 $n-x+1$
