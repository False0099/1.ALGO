# Circle Game

## 题面翻译

在坐标轴上，有一个以 $(0,0)$ 为圆点，$d$ 为半径的圆。  
现在 Ashish 和 Utkarsh 玩游戏，Ashish 是先手。  
在 $(0,0)$ 处有一颗棋子，两人轮流将棋子向上或向右移动 $k$ 个单位，棋子不能移出圆，谁无法移动谁输。  

Translate by leapfrog

## 题目描述

Utkarsh is forced to play yet another one of Ashish's games. The game progresses turn by turn and as usual, Ashish moves first.

Consider the 2 D plane. There is a token which is initially at  $ (0,0) $ . In one move a player must increase either the $ x $ coordinate or the $ y $ coordinate of the token by exactly $ k $ . In doing so, the player must ensure that the token stays within a (Euclidean) distance $ d $ from $ (0,0) $ .

In other words, if after a move the coordinates of the token are $ (p, q) $ , then $ p^2 + q^2 \leq d^2 $ must hold.

The game ends when a player is unable to make a move. It can be shown that the game will end in a finite number of moves. If both players play optimally, determine who will win.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \leq t \leq 100 $ ) — the number of test cases.

The only line of each test case contains two space separated integers $ d $ ( $ 1 \leq d \leq 10^5 $ ) and $ k $ ( $ 1 \leq k \leq d $ ).

## 输出格式

For each test case, if Ashish wins the game, print "Ashish", otherwise print "Utkarsh" (without the quotes).

## 样例 #1

### 样例输入 #1

```
5
2 1
5 2
10 3
25 4
15441 33
```

### 样例输出 #1

```
Utkarsh
Ashish
Utkarsh
Utkarsh
Ashish
```

## 提示

In the first test case, one possible sequence of moves can be

 $ (0, 0) \xrightarrow{\text{Ashish }} (0, 1) \xrightarrow{\text{Utkarsh }} (0, 2) $ .

Ashish has no moves left, so Utkarsh wins.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1451D/00adebe318fd60c39c1fde9564efcda9489c81f2.png)

## 题解
我们本题的想法是：通过我们的**结果来反推**我们的初始状态，我们不难发现，我们应该有下面几种可能的情况：
![[Pasted image 20240428222007.png]]
在我们的这一个图上，我们用红色点标记必胜点，蓝色点标记必败点。
![[Pasted image 20240428222038.png]]

此时，我们不难发现一个规律：对角线上的胜负状态相同，如下如：
![[Pasted image 20240428222109.png]]

 由此我们得到一个解法：直接判断直线 $y=x$ 上最远的可达的点是否必败，具体只要看这个点的右边或上面的点是否可达就行了。那么为什么这样是对的呢？

首先必败状态会造成其左和其下都是必胜状态，于是显然其左下为必败状态。然后必胜状态需满足其上或其右为必败状态，于是其左或其下为必败状态，显然其左下为必胜状态。

```
#include<cstdio>
#define ll long long
int t,d,k,x;
int main()
{
    scanf(" %d",&t);
    while(t--)
    {
        scanf(" %d %d",&d,&k);
        x=0.70710678*d/k;//(x,x)为 y=x 上最远可达的点
        if((ll)k*k*(x*(x+1ll)<<1|1)<=(ll)d*d)puts("Ashish");//即 (kx)^2+(k(x+1))^2<=d^2，故 (kx,k(x+1)) 可达，先手必胜
        else puts("Utkarsh");
    }
    return 0;
}

```