# Bracket Coloring

## 题面翻译

如果一个括号序列符合以下两个条件中的一个，那么它是优美的：

1、序列的任意一个前缀中，左括号的个数不少于右括号的个数，且整个序列中，左括号的个数等于右括号的个数。

2、序列的任意一个前缀中，右括号的个数不少于左括号的个数，且整个序列中，左括号的个数等于右括号的个数。

给定一个括号序列，你需要把它分成若干组，使得每一组的括号构成的序列都是优美的。求最少需要分成多少组，并输出分组方案。如果无解，输出 $ -1 $。

## 题目描述

A regular bracket sequence is a bracket sequence that can be transformed into a correct arithmetic expression by inserting characters "1" and "+" between the original characters of the sequence. For example:

- The bracket sequences " ()()" and " (())" are regular (the resulting expressions are: " (1)+(1)" and " ((1+1)+1)");
- The bracket sequences ")(", " (" and ")" are not.

A bracket sequence is called beautiful if one of the following conditions is satisfied:

- It is a regular bracket sequence;
- If the order of the characters in this sequence is reversed, it becomes a regular bracket sequence.

For example, the bracket sequences " ()()", " (())", ")))(((", "))()((" are beautiful.

You are given a bracket sequence $ s $ . You have to color it in such a way that:

- Every bracket is colored into one color;
- For every color, there is at least one bracket colored into that color;
- For every color, if you write down the sequence of brackets having that color in the order they appear, you will get a beautiful bracket sequence.

Color the given bracket sequence $ s $ into the minimum number of colors according to these constraints, or report that it is impossible.

## 输入格式

The first line contains one integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

Each test case consists of two lines. The first line contains one integer $ n $ ( $ 2 \le n \le 2 \cdot 10^5 $ ) — the number of characters in $ s $ . The second line contains $ s $ — a string of $ n $ characters, where each character is either " (" or ")".

Additional constraint on the input: the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, print the answer as follows:

- If it is impossible to color the brackets according to the problem statement, print $ -1 $ ;
- Otherwise, print two lines. In the first line, print one integer $ k $ ( $ 1 \le k \le n $ ) — the minimum number of colors. In the second line, print $ n $ integers $ c_1, c_2, \dots, c_n $ ( $ 1 \le c_i \le k $ ), where $ c_i $ is the color of the $ i $ -th bracket. If there are multiple answers, print any of them.

## 样例 #1

### 样例输入 #1

```
4
8
((())))(
4
(())
4
))((
3
(()
```

### 样例输出 #1

```
2
2 2 2 1 2 2 2 1
1
1 1 1 1
1
1 1 1 1
-1
```