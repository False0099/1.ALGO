# Everything Nim

## 题面翻译

### 题目描述
Alice 和 Bob 在用 $n\ (n\le 2\times 10^5 )$ 堆石子做游戏。在其中一位玩家的回合里，他可以选择一个不超过当前所有**非空**堆中石子数量**最小值**的**正整数** $k$，并从目前所有非空堆中移除 $k$ 颗石子。当一名玩家在他的回合中无法进行操作时（此时所有石子堆都是空的），即判为负。

现在给出 $n$ 堆石子的初始石子数，已知 Alice 先手且两人都足够聪明，请你判断最后谁会获胜。

### 输入格式

输入包含多组数据。

第一行一个整数 $T\ (T\le 10^4 ) $，表示输入数据组数。

对于每组数据，第一行包含一个整数 $n\ (n\le 2\times 10^5 ) $，表示石子堆数；第二行包含 $n$ 个整数 $a_{1\sim n}\ (a_i\le 10^9 ) $，表示第 $i$ 堆石子的数量。

题目保证对于单个测试点的所有数据，满足 $\sum n\le2\times10^5$。

---
### 输出格式

对于每组测试数据，输出一行一个字符串，表示胜者的名字。如 Alice 获胜则输出 `Alice`，否则输出 `Bob`。

## 题目描述

Alice and Bob are playing a game on $ n $ piles of stones. On each player's turn, they select a positive integer $ k $ that is at most the size of the smallest nonempty pile and remove $ k $ stones from each nonempty pile at once. The first player who is unable to make a move (because all piles are empty) loses.

Given that Alice goes first, who will win the game if both players play optimally?

## 输入格式

The first line of the input contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases. The description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 1 \le n \le 2\cdot 10^5 $ ) — the number of piles in the game.

The next line of each test case contains $ n $ integers $ a_1, a_2, \ldots a_n $ ( $ 1 \le a_i \le 10^9 $ ), where $ a_i $ is the initial number of stones in the $ i $ -th pile.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2\cdot 10^5 $ .

## 输出格式

For each test case, print a single line with the name of the winner, assuming both players play optimally. If Alice wins, print "Alice", otherwise print "Bob" (without quotes).

## 样例 #1

### 样例输入 #1

```
7
5
3 3 3 3 3
2
1 7
7
1 3 9 7 4 2 100
3
1 2 3
6
2 1 3 4 2 4
8
5 7 2 9 6 3 3 2
1
1000000000
```

### 样例输出 #1

```
Alice
Bob
Alice
Alice
Bob
Alice
Alice
```

## 提示

In the first test case, Alice can win by choosing $ k=3 $ on her first turn, which will empty all of the piles at once.

In the second test case, Alice must choose $ k=1 $ on her first turn since there is a pile of size $ 1 $ , so Bob can win on the next turn by choosing $ k=6 $ .

## 题解
**本题涉及到一种经典的方法，我们先拿 n-1, 下一个人强制就要拿 1 个，以此我们可以控制任意的先后手顺序**。


我们本题从正面考虑不方便考虑，我们倒着考虑我们也难以去倒推，我们可能是由哪些状态转移过来的。首先，我们考虑我们的必败态，我们**只有一个堆**，那么我们的最优策略一定是先手必胜。那么我们之后的扩展就一定是必败态。

首先当一次取的数量是根据地 $i$ 堆取时，所有数量小于 $i$ 的堆肯定都被取完了，所以我们可以把 $\{a_n\}$ 从小到大去重排序。

不妨设 $dp_i$ 表示对于第 $i$ 到 $n$ 个堆，已经刚好取完前 $i-1$ 堆，先手是否必胜 (必胜为 1，否则为0) 。注意到：记 $d_i=a_i-a_{i-1}$,这代表了当前 $i-1$ 个堆刚好取完后 $a_i$ 的剩余棋子数。

若$d_i= 1,$ $dp_i= dp_i+ 1\oplus 1$,即先手只能取完。否则，如果 $dp_{i+1}=1$,先手可以取到只剩一个石子，后手必须下一次取这个剩下的一个，先手可以在 $i+1$ 处取得先手，必胜；如果 $dp_{i+1}=0$,先手直接取完这一堆，后手必须在 $i+1$ 处处于先手，先手必胜。

由此有 $dp_n=1,dp_i=\begin{cases}dp_{i+1}\oplus1&a_i-a_{i-1}=1\\1&a_i-a_{i-1}\neq1\end{cases}$,特别的，$a_0=0$。


