# Card Game

## 题面翻译

有 $n$ 张卡牌，每张卡牌上写了 $[1,n]$ 中的一个整数，卡牌上的数字互不相同。

Alex 和 Boris 在玩游戏，每人有 $n\over 2$ 张卡牌，有 $n\over 2$ 轮。第一轮 Alex 先出牌，第二轮 Boris 先出牌，以此类推。

在一轮中，若先手出的牌上写的数为 $x$，则后手必须出一张比 $x$ 大的牌，如果没有则后手失败。双方都出完了牌则是平局。

假设两人都绝顶聪明，求所有分配牌的方案中，Alex 获胜、Boris 获胜和平局的方案数。

## 题目描述

Consider a game with $ n $ cards ( $ n $ is even). Each card has a number written on it, between $ 1 $ and $ n $ . All numbers on the cards are different. We say that a card with number $ x $ is stronger than a card with number $ y $ if $ x > y $ .

Two players, Alex and Boris, play this game. In the beginning, each of them receives exactly $ \frac{n}{2} $ cards, so each card belongs to exactly one player. Then, they take turns. Alex goes first, then Boris, then Alex again, and so on.

On a player's turn, he must play exactly one of his cards. Then, if the opponent doesn't have any cards stronger than the card played, the opponent loses, and the game ends. Otherwise, the opponent has to play a stronger card (exactly one card as well). These two cards are removed from the game, and the turn ends. If there are no cards left, the game ends in a draw; otherwise it's the opponent's turn.

Consider all possible ways to distribute the cards between two players, so that each of them receives exactly half of the cards. You have to calculate three numbers:

- The number of ways to distribute the cards so that Alex wins;
- The number of ways to distribute the cards so that Boris wins;
- The number of ways to distribute the cards so that the game ends in a draw.

You may assume that both players play optimally (i. e. if a player can win no matter how his opponent plays, he wins). Two ways to distribute the cards are different if there is at least one card such that, in one of these ways, it is given to Alex, and in the other way, it is given to Boris.

For example, suppose $ n = 4 $ , Alex receives the cards $ [2, 3] $ , and Boris receives the cards $ [1, 4] $ . Then the game may go as follows:

- If Alex plays the card $ 2 $ , then Boris has to respond with the card $ 4 $ . Then, Alex's turn ends, and Boris' turn starts. Boris has only one card left, which is $ 1 $ ; he plays it, and Alex responds with the card $ 3 $ . So, the game ends in a draw;
- If Alex plays the card $ 3 $ , then Boris has to respond with the card $ 4 $ . Then, Alex's turn ends, and Boris' turn starts. Boris has only one card left, which is $ 1 $ ; he plays it, and Alex responds with the card $ 2 $ . So, the game ends in a draw.

So, in this case, the game ends in a draw.

## 输入格式

The first line contains one integer $ t $ ( $ 1 \le t \le 30 $ ) — the number of test cases.

Then, $ t $ lines follow. The $ i $ -th line contains one even integer $ n $ ( $ 2 \le n \le 60 $ ).

## 输出格式

For each test case, print three integers:

- The number of ways to distribute the cards so that Alex wins;
- The number of ways to distribute the cards so that Boris wins;
- The number of ways to distribute the cards so that the game ends in a draw.

Since the answers can be large, print them modulo $ 998244353 $ .

## 样例 #1

### 样例输入 #1

```
5
2
4
6
8
60
```

### 样例输出 #1

```
1 0 1
3 2 1
12 7 1
42 27 1
341102826 248150916 1
```

## 提示

In the first test case, Alex wins if he receives the card $ 2 $ (he plays it, and Boris cannot respond). If Alex receives the card $ 1 $ , the game ends in a draw.

In the second test case:

- Alex wins if he receives the cards $ [3, 4] $ , $ [2, 4] $ or $ [1, 4] $ ;
- Boris wins if Alex receives the cards $ [1, 2] $ or $ [1, 3] $ ;
- The game ends in a draw if Alex receives the cards $ [2, 3] $ .

## 题解
