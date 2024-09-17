# Number Game

## 题面翻译

一共有 $t$ 组数据，每次有一个序列 $a$ ，两个人对它进行操作，一共进行 $k$ 个回合。在第 $i$ 个回合中，第一个人必须在序列 $a$ 不为空的情况下删除序列 $a$ 任意一个**小于等于** $k-i+1$ 的数。接着，第二个人必须在序列 $a$ 不为空的情况下将 $k-i+1$ 加到序列 $a$ 中任意一个数上。当 $k$ 个回合结束时，如果第一个人每一回合都操作过了，第一个人就赢了，否则就输了。求保证让第一个人赢的情况下 $k$ 最大是多少。

## 题目描述

Alice and Bob are playing a game. They have an array of positive integers $ a $ of size $ n $ .

Before starting the game, Alice chooses an integer $ k \ge 0 $ . The game lasts for $ k $ stages, the stages are numbered from $ 1 $ to $ k $ . During the $ i $ -th stage, Alice must remove an element from the array that is less than or equal to $ k - i + 1 $ . After that, if the array is not empty, Bob must add $ k - i + 1 $ to an arbitrary element of the array. Note that both Alice's move and Bob's move are two parts of the same stage of the game. If Alice can't delete an element during some stage, she loses. If the $ k $ -th stage ends and Alice hasn't lost yet, she wins.

Your task is to determine the maximum value of $ k $ such that Alice can win if both players play optimally. Bob plays against Alice, so he tries to make her lose the game, if it's possible.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 100 $ ) — the number of test cases.

The first line of each test case contains a single integer $ n $ ( $ 1 \le n \le 100 $ ) — the size of the array $ a $ .

The second line contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ 1 \le a_i \le n $ ).

## 输出格式

For each test case, print one integer — the maximum value of $ k $ such that Alice can win if both players play optimally.

## 样例 #1

### 样例输入 #1

```
4
3
1 1 2
4
4 4 4 4
1
1
5
1 3 2 1 1
```

### 样例输出 #1

```
2
0
1
3
```


## 题解
