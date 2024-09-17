The world is a grid with $n$ rows and $m$ columns. The rows are numbered $0, 1, \ldots, n-1$, while the columns are numbered $0, 1, \ldots, m-1$. In this world, the columns are **cyclic** (i.e. the top and the bottom cells in each column are adjacent). The cell on the $i$ \-th row and the $j$ \-th column ($0 \le i \lt n, 0 \le j \lt m$) is denoted as $(i,j)$.

**At time $0$**, the cell $(i,j)$ (where $0 \le i \lt; n, 0 \le j \lt; m$) contains either a **rock** or **nothing**. The state of cell $(i,j)$ can be described using the integer $a_{i,j}$:

-   If $a_{i,j} = 1$, there is a rock at $(i,j)$.
-   If $a_{i,j} = 0$, there is nothing at $(i,j)$.

As a result of aftershocks from the earthquake, the columns follow tectonic plate movements: each column moves cyclically **upwards** at a velocity of $1$ cell per unit of time. Formally, for some $0 \le i \lt; n, 0 \le j \lt; m$, if $(i,j)$ contains a rock at the moment, it will move from $(i, j)$ to $(i - 1, j)$ (or to $(n - 1, j)$ if $i=0$).

The robot called RT is initially positioned at $(0,0)$. It has to go to $(n-1,m-1)$ to carry out an earthquake rescue operation (to the bottom rightmost cell). The earthquake doesn't change the position of the robot, they only change the position of rocks in the world.

Let RT's current position be $(x,y)$ ($0 \le x \lt; n, 0 \le y \lt; m$), it can perform the following operations:

-   Go one cell cyclically upwards, i.e. from $(x,y)$ to $((x+n-1) \bmod n, y)$ using $1$ unit of time.
-   Go one cell cyclically downwards, i.e. $(x,y)$ to $((x+1) \bmod n, y)$ using $1$ unit of time.
-   Go one cell to the right, i.e. $(x,y)$ to $(x, y+1)$ using $1$ unit of time. (RT may perform this operation only if $y \lt; m-1$.)

**Note that RT cannot go left using the operations nor can he stay at a position.**

Unfortunately, RT will explode upon colliding with a rock. As such, when RT is at $(x,y)$ and there is a rock at $((x+1) \bmod n, y)$ or $((x+2) \bmod n, y)$, RT cannot move down or it will be hit by the rock.

![](https://espresso.codeforces.com/54b91480f21e9db9b3082078e8c3f561bbc98d16.png)

Similarly, if $y+1 \lt; m$ and there is a rock at $((x+1) \bmod n, y+1)$, RT cannot move right or it will be hit by the rock.

![](https://espresso.codeforces.com/fc36b41ba5b0aaf6e7cb0cd14e3d7753ff8ce551.png)

However, it is worth noting that if there is a rock at $(x \bmod n, y+1)$ and $((x+1) \bmod n, y)$, RT can still move right safely.

![](https://espresso.codeforces.com/aea04e7014e8732ae282cc6fc1cc10e0bcf293db.png)

Find the minimum amount of time RT needs to reach $(n-1,m-1)$ without colliding with any rocks. If it is impossible to do so, output $-1$.

**Input**

The first line of the input contains one integer $t$ ($1 \le t \le 10^4$) — the number of test cases.

In each test case, the first line contains two integers $n$, $m$ ($3 \le n, m \le 10^3$) — the size of the planet's boundaries.

Each of the next $n$ lines contains $m$ integers. The $(j+1)$ \-th integer on the $(i+1)$ \-th line ($0 \le i \lt; n, 0 \le j \lt; m$) is $a_{i,j}$ ($0 \le a_{i,j} \le 1$), which denotes whether or not there is a rock at $(i,j)$ at time $0$.

**Additionally, it is guaranteed that $a_{0,0} = 0$, and $a_{i, m-1} = 0$ for $0 \le i \lt; n$.** In other words, there is no rock at RT's initial position as well as column $m-1$.

The sum of $n \cdot m$ over all test cases does not exceed $10^6$.

## 题解
本题的思路在于：我们所有石头都动等于所有石头都不动，只有我和终点在动。在这种视角下，我们就有下面几种移动方式：
1. 保持不动：等价于原来的向上移动两个
2. 向左下移动一格
3. 向右下移动
4. 向正下方移动两格。

然后我们考虑终点的变化。我们发现，我们每移动一次，我们终点就会向下移动一格，于是，我们就可以先求出我们到达最后一列每一个格子的最小时间是多少，再计算我们的终点循环到这个位置所需要的时间是多少，就能得到我们的答案。

```cpp

```