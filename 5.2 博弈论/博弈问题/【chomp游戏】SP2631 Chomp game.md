# CLK - Chomp

## 题目描述

In Martin Gardner's book «Mathematical Games» the game of «Chomp!» is described as follows.   
  
 For the game of «Chomp!» you need some pieces which are initially placed on a rectangular playing field and removed from it during the game. (If you are playing on paper then you can use a grid with zeros and cross them out during the game instead.) The game is played by 2 players, and moves are made in turns.   
  
 Each turn is played as follows. The player chooses one piece, and removes all pieces which lie in the top-right rectangle, i.e., the rectangle having the chosen piece as the bottom-left corner. Thus, turn by turn, the players bite off pieces of the rectangular cookie, biting into it from the north-east (and the game takes its name from the chomp of their jaws). The winner is the player who forces his/her opponent to chomp the last, poisoned piece in the bottom left corner of the initial field.

![Game Chomp](https://cdn.luogu.com.cn/upload/vjudge_pic/SP2631/7fccaceaf6ee0e0f7170d5d2d908deccb3f516ae.png)  
_Fig 1. Example of one particular game in "Chomp!". In the initial state the pieces make up a 5х6 rectangle_   
Those are the rules. And now imagine the following situation. Two players begin to play the game of «Chomp!» on a 10 x 10 rectangular field. You can see an intermediate position which was obtained after some turn. The opponents are thinking deeply. How the game will end is not clear, because it's humans who are playing, not computers… By the way, talking of computers: write a program, which for the given position output its outcome. Is the player whose turn it is to move able to win, even if his/her opponent uses the best possible strategy?

## 输入格式

The first line of input contains the total number of tests M, followed by M lines, with ten numbers on each of them (describing a single position on the playing field). These ten numbers are separated by spaces and describe the number of pieces in each column (columns are enumerated from left to right).

## 输出格式

You must output exactly M lines, containing the letter W if it is possible for the player who takes the next turn to win (even in case of the best possible strategy for the other player), or L otherwise.

## 样例 #1

### 样例输入 #1

```
3
2 2 0 0 0 0 0 0 0 0
2 1 0 0 0 0 0 0 0 0
10 10 10 10 10 10 10 10 10 10
```

### 样例输出 #1

```
W
L
W
```

## 题解
我们这一题是我们的 chomp 游戏，chomp 游戏，就是给定一个 $m\times n$ 的棋盘，给个格子上有一块饼干，其中 $(1,1)$ 有毒，两人先后操作，每次选择一个点，吃点其作为左上角的极大子矩阵中的所有饼干，迟到毒饼干的输。

玄学：如果 $n=m=1$ 必败（我们的初始态是我们的必败态），否则，先手必胜，我们的策略是取我们的最右下角

同时我们这个游戏还可以扩展到我们的 n 维以及我们的偏序关系上
1. 在我们的一维关系中，我们有：
![[Pasted image 20231118170304.png]]

2. 在我们的二维中，我们有：
![[Pasted image 20231118170319.png]]

3. 在我们的三维中，我们有：
除非我们是先手必败态，否则我们一定存在一种操作，能够让我们的操作更优

4. 约数游戏：给定一个大于 1 的自然数 N，两个游戏参与者轮流选择大于 1 的正约数，但不能选择之前被选择过的因子的倍数，

5. 删数游戏：给定整数集合 $[1-n]$，两个人轮流从中选择一个数字，并将它和他的约数从集合中删除，删除最后一个数的人获胜。
先手必胜

6. 有限偏序集上的 chomp 游戏：
![[Pasted image 20231118170755.png]]

![[Pasted image 20231118170811.png]]
我们取最大元即可