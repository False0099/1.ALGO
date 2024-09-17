# Board Game

## 题面翻译

$\texttt{Polycarp}$ 和 $\texttt{Vasiliy}$ 各有一个棋子，它们分别在 $(x_p,y_p)$ 和 $(x_v,y_v)$。每人只能移动自己的棋子。

若 $\texttt {Polycarp}$ 的棋子在 $(x,y)$，则 $\texttt {Polycarp}$ 一次移动可以将其移动到 $(x-1,y)$ 或者 $(x,y-1)$；若 $\texttt {Vasiliy}$ 的棋子在 $(x,y)$，则 $\texttt {Vasiliy}$ 一次移动可以将其移动到 $(x-1,y),(x,y-1)$ 或 $(x-1,y-1)$。二人都不能移动到不合法位置。

如果 $(x,y)$ 满足以下任一条，那么它是不合法的：

+ $x<0$。

+ $y<0$。

+ 别人的棋子在 $(x,y)$。

每次操作可以在以下事情中任选一件做：

+ 移动一次棋子

+ 什么都不做

$\texttt{Polycarp}$ 先手，两人轮流操作。

将棋子移动到 $(0,0)$ 的人获得胜利。

现在假设 $\texttt{Polycarp}$ 和 $\texttt{Vasiliy}$ 都足够聪明，问谁能胜利。

$0\le x_p,y_p,x_v,y_v\le 10^5$，保证最开始时两个棋子不在同一位置并且没有棋子在 $(0,0)$。

## 题目描述

Polycarp and Vasiliy love simple logical games. Today they play a game with infinite chessboard and one pawn for each player. Polycarp and Vasiliy move in turns, Polycarp starts. In each turn Polycarp can move his pawn from cell $ (x, y) $ to $ (x-1, y) $ or $ (x, y-1) $ . Vasiliy can move his pawn from $ (x, y) $ to one of cells: $ (x-1, y), (x-1, y-1) $ and $ (x, y-1) $ . Both players are also allowed to skip move.

There are some additional restrictions — a player is forbidden to move his pawn to a cell with negative $ x $ -coordinate or $ y $ -coordinate or to the cell containing opponent's pawn The winner is the first person to reach cell $ (0,0) $ .

You are given the starting coordinates of both pawns. Determine who will win if both of them play optimally well.

## 输入格式

The first line contains four integers: $ x_{p}, y_{p}, x_{v}, y_{v} $ ( $ 0<=x_{p}, y_{p}, x_{v}, y_{v}<=10^{5}) $ — Polycarp's and Vasiliy's starting coordinates.

It is guaranteed that in the beginning the pawns are in different cells and none of them is in the cell $ (0,0) $ .

## 输出格式

Output the name of the winner: "Polycarp" or "Vasiliy".

## 样例 #1

### 样例输入 #1

```
2 1 2 2
```

### 样例输出 #1

```
Polycarp
```

## 样例 #2

### 样例输入 #2

```
4 7 7 4
```

### 样例输出 #2

```
Vasiliy
```

## 提示

In the first sample test Polycarp starts in $ (2,1) $ and will move to $ (1,1) $ in the first turn. No matter what his opponent is doing, in the second turn Polycarp can move to $ (1,0) $ and finally to $ (0,0) $ in the third turn.

## 题解
我们本题用脚都能看得出来，我们是   `Vasiliy` 的赢面是更大的，因为他既能够用我们的 `Polycarp` 的操作，也能够用我们的其他人的操作。

那么我们首先应该考虑，怎么让我们的 `Vasiliy` 先输，我们如果想让我们的 `Vasiliy` 先输，那么我们一定是只能是下面的几种情况出现的：
1. 我们的 `Polycarp` 到我们的重点的距离非常近，也就是说，我们 `Polycarp` 到我们的终点的曼哈顿距离小于我们的 `Vasiliy` 到我们的终点的最小操作次数，也就是我们的 $max(x,y)$。
2. 或者我们的 polycarp 正好挡在我们的 vasiliy 的必经之路上, 也就是说，Polycarp 的 $x$ 轴与 $y$ 轴都没有 Vasiliy 的 $x$ 轴与 $y$ 轴大，那 Vasiliy 自然不会超过。

于是我们就写出来我们的代码：
```
#include<bits/stdc++.h>
using namespace std;
int a,b,c,d;
int main(){
   cin>>a>>b>>c>>d;
   if(a+b<=c)cout<<"Polycarp";//情况一
   else if(a+b<=d)cout<<"Polycarp";//情况二
   else if(a<=c&&b<=d)cout<<"Polycarp";//情况三
   else cout<<"Vasiliy";//情况四
   return 0;
}

```