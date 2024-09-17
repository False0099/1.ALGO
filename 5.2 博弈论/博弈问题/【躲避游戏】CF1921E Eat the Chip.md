# Eat the Chip

## 题面翻译

有一个棋盘，上面有两个棋子，一个称作 $a$，一个称作 $b$，$a$ 可以向下，左下，右下走，$b$ 可以向上，左上，右上走。

如果一个棋子不能再走，即 $a$ 碰到了下边界或 $b$ 碰到了上边界则平局，输出 `Draw`。

如果一个棋子进入了对方**当前**所在格子，这一方直接胜利，$a$ 胜利输出 `Alice`，$b$ 胜利输出 `Bob`，保证双方初始所在位置不同。

棋盘大小 $h\times w$，初始 $a$ 的坐标为 $(x_a,y_a)$，初始 $b$ 的坐标为 $(x_b,y_b)$，$a$ 先移动。多组数据。

数据范围 $1\le x_a,x_b\le h\le10^6,1\le y_a,y_b\le w\le10^9,1\le T\le10^4$。

## 题目描述

Alice and Bob are playing a game on a checkered board. The board has $ h $ rows, numbered from top to bottom, and $ w $ columns, numbered from left to right. Both players have a chip each. Initially, Alice's chip is located at the cell with coordinates $ (x_a, y_a) $ (row $ x_a $ , column $ y_a $ ), and Bob's chip is located at $ (x_b, y_b) $ . It is guaranteed that the initial positions of the chips do not coincide. Players take turns making moves, with Alice starting.

On her turn, Alice can move her chip one cell down or one cell down-right or down-left (diagonally). Bob, on the other hand, moves his chip one cell up, up-right, or up-left. It is not allowed to make moves that go beyond the board boundaries.

More formally, if at the beginning of Alice's turn she is in the cell with coordinates $ (x_a, y_a) $ , then she can move her chip to one of the cells $ (x_a + 1, y_a) $ , $ (x_a + 1, y_a - 1) $ , or $ (x_a + 1, y_a + 1) $ . Bob, on his turn, from the cell $ (x_b, y_b) $ can move to $ (x_b - 1, y_b) $ , $ (x_b - 1, y_b - 1) $ , or $ (x_b - 1, y_b + 1) $ . The new chip coordinates $ (x', y') $ must satisfy the conditions $ 1 \le x' \le h $ and $ 1 \le y' \le w $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1921E/132ee8f6414f793fc5ccbac975e03978861ca953.png) Example game state. Alice plays with the white chip, Bob with the black one. Arrows indicate possible moves. A player immediately wins if they place their chip in a cell occupied by the other player's chip. If either player cannot make a move (Alice—if she is in the last row, i.e. $ x_a = h $ , Bob—if he is in the first row, i.e. $ x_b = 1 $ ), the game immediately ends in a draw.

What will be the outcome of the game if both opponents play optimally?

## 输入格式

Each test consists of multiple test cases. The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases. This is followed by the description of the test cases.

Each test case consists of a single line containing six integers $ h $ , $ w $ , $ x_a $ , $ y_a $ , $ x_b $ , $ y_b $ ( $ 1 \le x_a, x_b \le h \le 10^6 $ , $ 1 \le y_a, y_b \le w \le 10^9 $ ) — the dimensions of the board and the initial positions of Alice's and Bob's chips. It is guaranteed that either $ x_a \ne x_b $ or $ y_a \ne y_b $ .

It is guaranteed that the sum of $ h $ over all test cases does not exceed $ 10^6 $ .

## 输出格式

For each test case, output "Alice" if Alice wins, "Bob" if Bob wins, and "Draw" if neither player can secure a victory. You can output each letter in any case (lowercase or uppercase). For example, the strings "bOb", "bob", "Bob", and "BOB" will be accepted as Bob's victory.

## 样例 #1

### 样例输入 #1

```
12
6 5 2 2 5 3
4 1 2 1 4 1
1 4 1 3 1 1
5 5 1 4 5 2
4 4 1 1 4 4
10 10 1 6 10 8
10 10 2 6 10 7
10 10 9 1 8 1
10 10 8 1 10 2
10 10 1 1 2 1
10 10 1 3 4 1
10 10 3 1 1 1
```

### 样例输出 #1

```
Alice
Bob
Draw
Draw
Draw
Alice
Draw
Draw
Bob
Alice
Alice
Draw
```

## 题解
我们首先注意到，我们每一次，我们都会让我们的 $x$ 发生改变，并且我们每一次改变的量都是相同的。于是，我们就可以直到，如果我们的 $x$ 和 $y$ 相遇，那么我们执行操作的**次数**是固定的。

现在，我们可以考虑先判断，哪些情况是不可能的
1. 我们的 $Alice$ 在 $Bob$ 的下面，那么我们最后一定是平局

接下来，我们就可以计算出我们的次数是多少次，我们首先不难判断出，我们可以操作的次数分别是多少，因为我们是 $x$ 先操作，所以我们的操作步数就是我们的 $|x_{1}-x_{2}|/2$ 上取整。那么我们之后就变成了下面的这一个游戏：

给你两个数 $a,b$ ，Alice 先手，每一次可以让我们的 $a$ 选择+1 或者-1 或者不变，但是 a 不能超过一个指定的范围，Bob 后手，可以进行的操作相同。并且我们的次数也已经给出，问你是否存在必胜策略。

这个时候，我们的策略是显然的，我们每一次看我们应该尽可能让我们两个之间的绝对值拉大，然后再去判断，我们是否能够保证我们的次数在我们的一定范围之内。

```
#include <iostream>
using namespace std;
void work()
{
    int n, m, xa, ya, xb, yb;
    scanf("%d%d%d%d%d%d", &n, &m, &xa, &ya, &xb, &yb);
    if (xa > xb) //如果鲍勃已经在爱丽丝上方，那就肯定平局。
    {
        puts("Draw");
        return;
    }
    int xc = xb - xa;
    if (ya == yb)
    {
        if (xc & 1)
            puts("Alice");
        else
            puts("Bob");
        return;
    }
    if (xc & 1) // 爱丽丝追鲍勃
    {
        while (xa < xb)
        {
            if (yb < ya) // 往鲍勃的方向追
                ya --;
            else if (yb > ya)
                ya ++;
            else		// 如果已经在同一列
            {
                puts("Alice");
                return;
            }
            xa ++;
            if (xa == xb && ya == yb)
            {
                puts("Alice");
                return;
            }
            if (yb < ya && yb > 1) // 往反方向躲
                yb --;
            else if (yb > ya && yb < m)
                yb ++;
            xb --;
            if (xa == xb && ya == yb)
            {
                puts("Alice");
                return;
            }
        }
        puts("Draw");
    }
    else 	// 爱丽丝躲鲍勃
    {
        while (xa < xb)
        {
            if (yb < ya)
            {
                if (ya < m)
                    ya ++;
            }
            else if (ya < yb)
            {
                if (1 < ya)
                    ya --;
            }
            else
            {
                if (xb - xa <= 1)
                    puts("Draw");
                else
                    puts("Bob");
                return;
            }
            xa ++;
            if (xa == xb && ya == yb)
            {
                puts("Bob");
                return;
            }
            if (yb < ya)
                yb ++;
            else
                yb --;
            xb --;
            if (xa == xb && ya == yb)
            {
                puts("Bob");
                return;
            }
        }
        puts("Draw");
    }
}
int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
        work();
    return 0;
}
```