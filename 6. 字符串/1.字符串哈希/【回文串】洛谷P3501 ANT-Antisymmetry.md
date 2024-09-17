# [POI 2010] ANT-Antisymmetry

## 题目描述

Byteasar studies certain strings of zeroes and ones.

Let ![](http://main.edu.pl/images/OI17/ant-en-tex.1.png) be such a string. By ![](http://main.edu.pl/images/OI17/ant-en-tex.2.png) we will denote the reversed (i.e., "read backwards") string ![](http://main.edu.pl/images/OI17/ant-en-tex.3.png),    and by ![](http://main.edu.pl/images/OI17/ant-en-tex.4.png) we will denote the string obtained from ![](http://main.edu.pl/images/OI17/ant-en-tex.5.png) by changing all the zeroes to ones and ones to zeroes.

Byteasar is interested in antisymmetry, while all things symmetric bore him.

Antisymmetry however is not a mere lack of symmetry.

We will say that a (nonempty) string ![](http://main.edu.pl/images/OI17/ant-en-tex.6.png) is antisymmetric if, for every position ![](http://main.edu.pl/images/OI17/ant-en-tex.7.png) in ![](http://main.edu.pl/images/OI17/ant-en-tex.8.png),    the ![](http://main.edu.pl/images/OI17/ant-en-tex.9.png)-th last character is different than the ![](http://main.edu.pl/images/OI17/ant-en-tex.10.png)-th (first) character.

In particular, a string ![](http://main.edu.pl/images/OI17/ant-en-tex.11.png) consisting of zeroes and ones is antisymmetric if and only if    ![](http://main.edu.pl/images/OI17/ant-en-tex.12.png).

For example, the strings 00001111 and 010101 are antisymmetric, while 1001 is not.

In a given string consisting of zeroes and ones we would like to determine the number of contiguous    nonempty antisymmetric fragments.

Different fragments corresponding to the same substrings should be counted multiple times.

对于一个 01 字符串，如果将这个字符串 0 和 1 取反后，再将整个串反过来和原串一样，就称作“反对称”字符串。比如 00001111 和 010101 就是反对称的，1001 就不是。

现在给出一个长度为 N 的 01 字符串，求它有多少个子串是反对称的。

## 输入格式

The first line of the standard input contains an integer ![](http://main.edu.pl/images/OI17/ant-en-tex.13.png) (![](http://main.edu.pl/images/OI17/ant-en-tex.14.png)) that denotes the length of the string.

The second line gives a string of 0 and/or 1 of length ![](http://main.edu.pl/images/OI17/ant-en-tex.15.png).

There are no spaces in the string.

## 输出格式

The first and only line of the standard output should contain a single integer,      namely the number of contiguous (non empty) fragments of the given string      that are antisymmetric.

## 样例 #1

### 样例输入 #1

```
8
11001011
```

### 样例输出 #1

```
7
```

## 提示

7 个反对称子串分别是：01（出现两次），10（出现两次），0101，1100 和 001011

$n \le 5 \times 10^5$

## 题解
我们本题的难点在于：
1. 不能快速枚举子区间
2. 怎么以 $o(1)$ 的判断一个子串是符合要求的。

这里，我们用到了类似于我们的 manacher 算法的思想：我们考虑枚举我们的中轴。

不难得出，每个反对称字符串的长度一定是偶数，这样我们就可以枚举每个字符串中间的空隙 (中轴), 然后二分配合 hash 求中轴为 $l$ 的最长反对称字符串长度 $l$,每次 $ans$ 加上 $l/2$ 就是最终答案。这是因为，如果一个串 $s$ 为反对称字符串，那么 $s$ 所有以 $l$ 为中轴的子串都是反对称字符串，这样的子串共 $l/2$

 个。可以自己模拟一下试试。实际实现中，二分的是 $l/2$,这样更方便一些。
