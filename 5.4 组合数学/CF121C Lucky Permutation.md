# Lucky Permutation

## 题面翻译

定义：幸运数字是指只含 4 和 7 的数字。

求在 1 到 $n$ 的第 $k$ 个全排列中有多少元素的下标和值都是幸运数。

$1 \leq n,k\leq 10^9$

## 题目描述

Petya loves lucky numbers. Everybody knows that lucky numbers are positive integers whose decimal representation contains only the lucky digits 4 and 7. For example, numbers 47, 744, 4 are lucky and 5, 17, 467 are not.

One day Petya dreamt of a lexicographically $ k $ -th permutation of integers from $ 1 $ to $ n $ . Determine how many lucky numbers in the permutation are located on the positions whose indexes are also lucky numbers.

## 输入格式

The first line contains two integers $ n $ and $ k $ $ (1<=n, k<=10^{9}) $ — the number of elements in the permutation and the lexicographical number of the permutation.

## 输出格式

If the $ k $ -th permutation of numbers from $ 1 $ to $ n $ does not exist, print the single number "-1" (without the quotes). Otherwise, print the answer to the problem: the number of such indexes $ i $ , that $ i $ and $ a_{i} $ are both lucky numbers.

## 样例 #1

### 样例输入 #1

```
7 4
```

### 样例输出 #1

```
1
```

## 样例 #2

### 样例输入 #2

```
4 7
```

### 样例输出 #2

```
1
```

## 提示

A permutation is an ordered set of $ n $ elements, where each integer from $ 1 $ to $ n $ occurs exactly once. The element of permutation in position with index $ i $ is denoted as $ a_{i} $ ( $ 1<=i<=n $ ). Permutation $ a $ is lexicographically smaller that permutation $ b $ if there is such a $ i $ ( $ 1<=i<=n $ ), that $ a_{i}&lt; b_{i} $ , and for any $ j $ ( $ 1<=j&lt; i $ ) $ a_{j}=b_{j} $ . Let's make a list of all possible permutations of $ n $ elements and sort it in the order of lexicographical increasing. Then the lexicographically $ k $ -th permutation is the $ k $ -th element of this list of permutations.

In the first sample the permutation looks like that:

1 2 3 4 6 7 5

The only suitable position is 4.

In the second sample the permutation looks like that:

2 1 3 4

The only suitable position is 4.