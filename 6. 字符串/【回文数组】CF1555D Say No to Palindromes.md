# Say No to Palindromes

## 题面翻译

定义一个字符串 $s$ 是“好的”，当且仅当 $s$ 不包含任何长度大于等于 2 的回文子串。给定一个长度为 $n$ 的字符串 $S$ 和 $m$ 个询问，每次询问给定一个区间 $[l, r]$，求字符串 $S_{l, \dots, r}$ 变成“好的”字符串至少需要修改多少个字符。本题中字符集为前三个字母（`a b c`）。数据范围 $n, m \le 200000$。

## 题目描述

Let's call the string beautiful if it does not contain a substring of length at least $ 2 $ , which is a palindrome. Recall that a palindrome is a string that reads the same way from the first character to the last and from the last character to the first. For example, the strings a, bab, acca, bcabcbacb are palindromes, but the strings ab, abbbaa, cccb are not.

Let's define cost of a string as the minimum number of operations so that the string becomes beautiful, if in one operation it is allowed to change any character of the string to one of the first $ 3 $ letters of the Latin alphabet (in lowercase).

You are given a string $ s $ of length $ n $ , each character of the string is one of the first $ 3 $ letters of the Latin alphabet (in lowercase).

You have to answer $ m $ queries — calculate the cost of the substring of the string $ s $ from $ l_i $ -th to $ r_i $ -th position, inclusive.

## 输入格式

The first line contains two integers $ n $ and $ m $ ( $ 1 \le n, m \le 2 \cdot 10^5 $ ) — the length of the string $ s $ and the number of queries.

The second line contains the string $ s $ , it consists of $ n $ characters, each character one of the first $ 3 $ Latin letters.

The following $ m $ lines contain two integers $ l_i $ and $ r_i $ ( $ 1 \le l_i \le r_i \le n $ ) — parameters of the $ i $ -th query.

## 输出格式

For each query, print a single integer — the cost of the substring of the string $ s $ from $ l_i $ -th to $ r_i $ -th position, inclusive.

## 样例 #1

### 样例输入 #1

```
5 4
baacb
1 3
1 5
4 5
2 3
```

### 样例输出 #1

```
1
2
0
1
```

## 提示

Consider the queries of the example test.

- In the first query, the substring is baa, which can be changed to bac in one operation;
- In the second query, the substring is baacb, which can be changed to cbacb in two operations;
- In the third query, the substring is cb, which can be left unchanged;
- In the fourth query, the substring is aa, which can be changed to ba in one operation.

## 题解
我们本题需要利用到我们的字符串中的一个重要的想法，或者说是关于**回文字符串构造**的一个重要的思想，就是**序列自动机**的思想。

我们考虑我们原函数中的性质，即如果一个字符串是“好”的，那么我们一定只可能是下面的几种形态：
```
ab
ac
ba
bc
ca
cb
```

于是，我们只需要枚举我们的上面六种形态的长为 $n$ 的字符串分别是什么，然后我们再去进行对应的处理即可。

这里我们应该注意我们写代码的技巧，我们可以首先开一个字典来处理我们的循环节，因为我们在有了循环节后我们的答案会相对来说比较固定。

