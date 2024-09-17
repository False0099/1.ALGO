Alice and Bob are playing a game on a checkered board. The board has $h$ rows, numbered from top to bottom, and $w$ columns, numbered from left to right. Both players have a chip each. Initially, Alice's chip is located at the cell with coordinates $(x_a, y_a)$ (row $x_a$, column $y_a$), and Bob's chip is located at $(x_b, y_b)$. It is guaranteed that the initial positions of the chips do not coincide. Players take turns making moves, with Alice starting.

On her turn, Alice can move her chip one cell down or one cell down-right or down-left (diagonally). Bob, on the other hand, moves his chip one cell up, up-right, or up-left. It is not allowed to make moves that go beyond the board boundaries.

More formally, if at the beginning of Alice's turn she is in the cell with coordinates $(x_a, y_a)$, then she can move her chip to one of the cells $(x_a + 1, y_a)$, $(x_a + 1, y_a - 1)$, or $(x_a + 1, y_a + 1)$. Bob, on his turn, from the cell $(x_b, y_b)$ can move to $(x_b - 1, y_b)$, $(x_b - 1, y_b - 1)$, or $(x_b - 1, y_b + 1)$. The new chip coordinates $(x', y')$ must satisfy the conditions $1 \le x' \le h$ and $1 \le y' \le w$.

![](https://espresso.codeforces.com/dbc362298c0158c22f271eca8a6d5611b3ae09a5.png) Example game state. Alice plays with the white chip, Bob with the black one. Arrows indicate possible moves.

A player immediately wins if they place their chip in a cell occupied by the other player's chip. If either player cannot make a move (Alice—if she is in the last row, i.e. $x_a = h$, Bob—if he is in the first row, i.e. $x_b = 1$), the game immediately ends in a draw.

What will be the outcome of the game if both opponents play optimally?

**Input**

Each test consists of multiple test cases. The first line contains a single integer $t$ ($1 \le t \le 10^4$) — the number of test cases. This is followed by the description of the test cases.

Each test case consists of a single line containing six integers $h$, $w$, $x_a$, $y_a$, $x_b$, $y_b$ ($1 \le x_a, x_b \le h \le 10^6$, $1 \le y_a, y_b \le w \le 10^9$) — the dimensions of the board and the initial positions of Alice's and Bob's chips. It is guaranteed that either $x_a \ne x_b$ or $y_a \ne y_b$.

It is guaranteed that the sum of $h$ over all test cases does not exceed $10^6$.

**Output**

For each test case, output "Alice" if Alice wins, "Bob" if Bob wins, and "Draw" if neither player can secure a victory. You can output each letter in any case (lowercase or uppercase). For example, the strings "bOb", "bob", "Bob", and "BOB" will be accepted as Bob's victory.

## 题解
我们这一题是我们一个典型的博弈题，我们的博弈题就是要找我们每一次移动一定会改变的量。我们发现，我们每一次移动，我们两者之间的纵坐标差一定会减一，于是，我们就可以根据我们的纵坐标之间的差来判断。如果我们**纵坐标差为奇数，那么我们只可能是我们的后手获胜或者是平局**，如果我们的纵坐标差为偶书，那么我们只可能是我们的先手获胜或者平局。

现在，我们的观建就变成了怎么判断我们的平局。我们发现有下面几种情况都满足才可能是获胜的：
1. 两者之间的横坐标差小于等于 1
2. 我们的移动方向是正的
3. 没有到右边界或者左边界

```
#include<bits/stdc++.h>
using namespace std;
#define pii pair<int, int>
#define pdd pair<double, double>
typedef long long ll;

inline void solve()
{
    int h, w, xa, ya, xb, yb;
    cin >> h >> w;
    cin >> xa >> ya >> xb >> yb;
    if(xa >= xb) {
        puts("Draw");
        return;
    }
    vector<pii> da(3), db(3);
    da[0] = {1, 0};
    da[1] = {1, -1};
    da[2] = {1, 1};
    db[0] = {-1, 0};
    db[1] = {-1, -1};
    db[2] = {-1, 1};
    for(int i=0; i<3; i++) {
        pii ta = {xa+da[i].first,ya+da[i].second};
        pii tb = {xb, yb};
        if(ta == (pii){xb, yb}) {
            puts("Alice");
            return;
        }
        if(ta == (pii){xb-2, yb}) {
            puts("Alice");
            return;
        }
        if(tb == (pii){xa+2, ya}) {
            puts("Bob");
            return;
        }
    }
    int k = xb - xa;
    int t = 0;
    if(k % 2) {
        if(ya > yb+1) {
            //(k+1)/2
            if(ya - (k+1)/2 <= 1) {
                puts("Alice");
                return;
            } 
        } else if(ya+1 < yb) {
            if(ya + (k+1)/2 >= w) {
                puts("Alice");
                return;
            }
        } else {
            puts("Alice");
            return;
        }
    }
    if(k % 2 == 0) {
        if(yb > ya) {
            //(k+1)/2
            if(yb - k/2 <= 1) {
                puts("Bob");
                return;
            } 
        } else if(yb < ya) {
            if(yb + k/2 >= w) {
                puts("Bob");
                return;
            }
        } else {
            puts("Bob");
            return;
        }
    }
    puts("Draw");
    // puts("Draw");
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t;
    cin >> t;
    while(t --)
        solve();
    return 0;
}
```