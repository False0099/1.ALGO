# Sequential Nim

## 题面翻译

有 $n$ 堆石子，第 $i$ 堆有 $a_i$ 个。有两个人在玩取石子游戏。

两个人轮流取石子，每次取编号最小且有石子的堆。每个人可以在一堆石子中取走若干个（至少取 $1$ 个），当一个人没有石子可以取了，他就输了。

现在给出每堆石子的数量，假设两人的都采用最优策略，问最后是先手 (first) 胜利还是后手 (second) 胜利。

## 题目描述

There are $ n $ piles of stones, where the $ i $ -th pile has $ a_i $ stones. Two people play a game, where they take alternating turns removing stones.

In a move, a player may remove a positive number of stones from the first non-empty pile (the pile with the minimal index, that has at least one stone). The first player who cannot make a move (because all piles are empty) loses the game. If both players play optimally, determine the winner of the game.

## 输入格式

The first line contains a single integer $ t $ ( $ 1\le t\le       1000 $ ) — the number of test cases. Next $ 2 t $ lines contain descriptions of test cases.

The first line of each test case contains a single integer $ n $ ( $ 1\le n\le 10^5 $ ) — the number of piles.

The second line of each test case contains $ n $ integers $ a_1,\ldots, a_n $ ( $ 1\le a_i\le 10^9 $ ) — $ a_i $ is equal to the number of stones in the $ i $ -th pile.

It is guaranteed that the sum of $ n $ for all test cases does not exceed $ 10^5 $ .

## 输出格式

For each test case, if the player who makes the first move will win, output "First". Otherwise, output "Second".

## 样例 #1

### 样例输入 #1

```
7
3
2 5 4
8
1 1 1 1 1 1 1 1
6
1 2 3 4 5 6
6
1 1 2 1 2 2
1
1000000000
5
1 2 2 1 1
3
1 1 1
```

### 样例输出 #1

```
First
Second
Second
First
First
Second
First
```

## 提示

In the first test case, the first player will win the game. His winning strategy is:

1. The first player should take the stones from the first pile. He will take $ 1 $ stone. The numbers of stones in piles will be $ [1, 5, 4] $ .
2. The second player should take the stones from the first pile. He will take $ 1 $ stone because he can't take any other number of stones. The numbers of stones in piles will be $ [0,         5, 4] $ .
3. The first player should take the stones from the second pile because the first pile is empty. He will take $ 4 $ stones. The numbers of stones in piles will be $ [0, 1, 4] $ .
4. The second player should take the stones from the second pile because the first pile is empty. He will take $ 1 $ stone because he can't take any other number of stones. The numbers of stones in piles will be $ [0, 0, 4] $ .
5. The first player should take the stones from the third pile because the first and second piles are empty. He will take $ 4 $ stones. The numbers of stones in piles will be $ [0, 0,         0] $ .
6. The second player will lose the game because all piles will be empty.

## 题解
我们可以发现对于若干堆 (第一堆数量大于 1), 有这么一个贪心的取法：比如第一堆堆数量为 $n(n>1)$ 。先手先取 $n-1$ 个。这样后手只能取 1 个 (无法不取)。这样，先手就可以先取第二堆。
后几堆的取法同上，直到先手可以先取最后一堆。对于最后一堆，先手直接取完。获胜。
那如果中间有一堆数量为 1，那么对于这一堆的前一堆，直接全部取完，后手只能取完这堆数量为 1的堆。照样可以获得下一堆的先手。
以此类推。我们可以发现，影响最后结果的，只有前缀 1 的数量。容易发现，如果前缀 1 数量为偶数个，在轮流取完后，那么第一个非 1 堆，是先手先取。即先手会胜利。如果是奇数个，那么第一个非 1 堆，是后手先取。即后手会胜利。

特殊的，如果这堆只有 1。那么偶数个胜利的为后手，奇数个胜利的为先手。
(为什么是前缀而不是总数？)