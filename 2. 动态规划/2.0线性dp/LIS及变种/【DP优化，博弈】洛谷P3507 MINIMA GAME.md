
 # 知识点
  ## [[动态规划]] [[博弈论]]
# 题目
 # [POI 2010]GRA-The Minima Game

## 题目描述

Alice and Bob learned the minima game, which they like very much, recently.

The rules of the game are as follows.

A certain number of cards lies on a table, each inscribed with a positive integer.

The players make alternate moves, Alice making the first one.

A move consists in picking an arbitrary positive number of cards from the table.

For such move the player receives a number of points equal to the minimum    of the numbers inscribed on the cards he collected.

The game ends when the last card is removed from the table.

The goal of each player is maximizing the difference between their and their opponent's score.

Alice and Bob have duly noted that there is an optimal strategy in the game.

Thus they are asking you to write a program that, for a given set of cards,    determines the outcome of the game when both players play optimally.

给出 N 个正整数，AB 两个人轮流取数，A 先取。每次可以取任意多个数，直到 N 个数都被取走。每次获得的得分为取的数中的最小值，A 和 B 的策略都是尽可能使得自己的得分减去对手的得分更大。在这样的情况下，最终 A 的得分减去 B 的得分为多少。

## 输入格式

In the first line of the standard input there is one integer ![](http://main.edu.pl/images/OI17/gra-en-tex.1.png) (![](http://main.edu.pl/images/OI17/gra-en-tex.2.png)) given,      denoting the number of cards.

The second line holds ![](http://main.edu.pl/images/OI17/gra-en-tex.3.png) positive integers ![](http://main.edu.pl/images/OI17/gra-en-tex.4.png) (![](http://main.edu.pl/images/OI17/gra-en-tex.5.png)),      separated by single spaces, that are inscribed on the cards.

## 输出格式

Your program should print out a single line with a single integer to the standard      output - the number of points by which Alice wins over Bob, assuming they both play optimally;      if it is Bob who has more points, the result should be negative.

## 样例 #1

### 样例输入 #1

```
3
1 3 1
```

### 样例输出 #1

```
2
```

## 提示

$1≤n≤10^6,1≤k_i≤10^9$

# 思路
·
·
·
# AC 代码
```cpp

```
# 题解
首先我们这一题的朴素 $o(n^2)$ 做法比较简单，我们只需要枚举我们的中间端点 j，然后我们就有：
$$A[i]=max(A[i],a[j+1]-A[j]);\quad(j\in[0,i-1])$$

然后，我们现在去考虑我们的 $o(n)$ 做法，假设我们现在有
很显然我们每次更新$A[i]$都把前面所有的$A[j]$都枚举一遍是很浪费时间的，我们只需要知道最大的$a[j+1]-A[j]$是多少就可以了，而$A[i]$正是在不断的储存着i以前最大的$a[j+1]-A[j]$，所以方程就变成了：


$$A[i]=max(A[i-1],a[i]-A[i-1]);$$