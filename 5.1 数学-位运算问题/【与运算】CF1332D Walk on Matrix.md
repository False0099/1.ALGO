# Walk on Matrix

## 题面翻译

有这么一个问题：

> 有一个 $n \times m$ 的矩阵 $a_{n, m}$，矩阵的每个位置都有一个数，要求寻找一个每次只能向右或向下走的从 $(1, 1)$ 至 $(n, m)$ 的路径，最大化路径上的数的按位与之和。
>
> $1 \leq n, m \leq 500$，$0 \leq a_{i, j} \leq 3 \times 10^5$。

现在给出解决该问题的一个**错误** dp 算法（见题面图片），请构造一组数据，hack 掉这个算法，使得正确答案比错误的输出**恰好**大 $k$。

$0 \leq k \leq 10^5$。

## 题目描述

Bob is playing a game named "Walk on Matrix".

In this game, player is given an $ n \times m $ matrix $ A=(a_{i, j}) $ , i.e. the element in the $ i $ -th row in the $ j $ -th column is $ a_{i, j} $ . Initially, player is located at position $ (1,1) $ with score $ a_{1,1} $ .

To reach the goal, position $ (n, m) $ , player can move right or down, i.e. move from $ (x, y) $ to $ (x, y+1) $ or $ (x+1, y) $ , as long as player is still on the matrix.

However, each move changes player's score to the [bitwise AND](https://en.wikipedia.org/wiki/Bitwise_operation#AND) of the current score and the value at the position he moves to.

Bob can't wait to find out the maximum score he can get using the tool he recently learnt — dynamic programming. Here is his algorithm for this problem.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1332D/f77be4abbc0e4a1768015d201a26d68f6c552a32.png)However, he suddenly realize that the algorithm above fails to output the maximum score for some matrix $ A $ . Thus, for any given non-negative integer $ k $ , he wants to find out an $ n \times m $ matrix $ A=(a_{i, j}) $ such that

- $ 1 \le n, m \le 500 $ (as Bob hates large matrix);
- $ 0 \le a_{i, j} \le 3 \cdot 10^5 $ for all $ 1 \le i\le n, 1 \le j\le m $ (as Bob hates large numbers);
- The difference between the maximum score he can get and the output of his algorithm is exactly $ k $ .

It can be shown that for any given integer $ k $ such that $ 0 \le k \le 10^5 $ , there exists a matrix satisfying the above constraints.

Please help him with it!

## 输入格式

The only line of the input contains one single integer $ k $ ( $ 0 \le k \le 10^5 $ ).

## 输出格式

Output two integers $ n $ , $ m $ ( $ 1 \le n, m \le 500 $ ) in the first line, representing the size of the matrix.

Then output $ n $ lines with $ m $ integers in each line, $ a_{i, j} $ in the $ (i+1) $ -th row, $ j $ -th column.

## 样例 #1

### 样例输入 #1

```
0
```

### 样例输出 #1

```
1 1
300000
```

## 样例 #2

### 样例输入 #2

```
1
```

### 样例输出 #2

```
3 4
7 3 3 1
4 8 3 6
7 7 7 3
```

## 提示

In the first example, the maximum score Bob can achieve is $ 300000 $ , while the output of his algorithm is $ 300000 $ .

In the second example, the maximum score Bob can achieve is $ 7\&3\&3\&3\&7\&3=3 $ , while the output of his algorithm is $ 2 $ .

## 题解
我们本题给你了一个错误的算法，要求你把这个错误的算法 hack 掉。想知道为什么这一个算法是错误的，我们就要首先知道他**错在哪里**。我们首先给出一个问题，是不是**最大的就一定是最优的**，答案是否定的，我们有 $10000\&1<1\&1$。因此，我们最大的不一定就是最优的。

那么我们考虑**怎么样去构造**，我们注意到，我们考虑“骗”这个 $\operatorname{dp}$,让他选择一个看似更大的答案，最后把这个答案给卡掉，就可以让 $\operatorname{dp}$ 的答案为 0,最后让这个方案的真正答案为 $k$,差值就是 $k$ 了。
我们发现 $k_{max}<2^{17}<10^5$,那么也就是说，如果我们令一个值为 $2^{17}+k$,那么 $2^{17}$ 和 $k$ 的二进制位是不会相互影响的，也就是不发生进位的，或者说 $k\&2^{17}=0$。

这很好，因为这样就让题目变得非常简单了，我们可以构造以下这个矩阵：
$$n=2,m=3$$
$$\begin{bmatrix}2^{17}+k&2^{17}&0\\k&2^{17}+k&k\end{bmatrix}$$
就可以完美解决这个问题了

为什么？

我们可以一步一步看这个矩阵，首先显然的，我们不会走到 (1,3), 因此我们迫使 $(1,1)\to(n,m)$ 的走法只有两种：走 (1,2)或者 (2,1)我们发现 $dp[1][2]=2^{17},dp[2][1]=k$ 那为什么 (2,2)这个位置放的又是 $2^{17}+k$ ?因为这样能够保证 $dp[2][2]$ 从 $dp[1][2]$ 取值，这样就进入了我们的圈套

最后 (2,3)再放一个 $k$,此时的 $dp[2][2]=2^{17}$, $dp[2][3]$ 又只能从 $dp[2][2]$ 取值，所以我们就成功让 $\deg$ 输出了 0

这时我们发现 $\operatorname{dp}$ 选择的是走 (1,2)那一边，并且不难发现如果走 (2,1), 答案就恰好为 $k$ 了因此 $\operatorname{dp}$ 答案与正确答案的差值正好就是 $k$ 了
```
//Code By CXY07
#include<bits/stdc++.h>
using namespace std;

//#define int long long

int k;

signed main () {
	scanf("%d",&k);
	printf("%d %d\n",2,3);
	printf("%d %d %d\n",(1 << 17) + k,(1 << 17),0);
	printf("%d %d %d\n",k,(1 << 17) + k,k);
	return 0;//End.
}

```