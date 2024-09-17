# Score of a Tree

## 题面翻译

给你一个 $n$ 个结点根为 $1$ 的树。在 $t = 0$ 时，每个结点都有一个值，为 $0$ 或 $1$。

在每一个 $t > 0$ 时，每个结点的值都会变成其子结点在 $t - 1$ 时的值的异或和。

定义 $S(t)$ 为 $t$ 时所有结点值的和。

定义 $F(A)$ 为树在 $0 \le t \le 10^{100}$ 中所有 $S(t)$ 的和。其中 $A$ 为树在时刻 $0$ 时每个结点的值。

求所有 $2^n$ 个 $F(A)$ 的和。

## 题目描述

You are given a tree of $ n $ nodes, rooted at $ 1 $ . Every node has a value of either $ 0 $ or $ 1 $ at time $ t=0 $ .

At any integer time $ t>0 $ , the value of a node becomes the [bitwise XOR](https://en.wikipedia.org/wiki/Bitwise_operation#XOR) of the values of its children at time $ t - 1 $ ; the values of leaves become $ 0 $ since they don't have any children.

Let $ S (t) $ denote the sum of values of all nodes at time $ t $ .

Let $ F (A) $ denote the sum of $ S (t) $ across all values of $ t $ such that $ 0 \le t \le 10^{100} $ , where $ A $ is the initial assignment of $ 0 $ s and $ 1 $ s in the tree.

The task is to find the sum of $ F (A) $ for all $ 2^n $ initial configurations of $ 0 $ s and $ 1 $ s in the tree. Print the sum modulo $ 10^9+7 $ .

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10^5 $ ). The description of the test cases follows.

The first line of each test case contains $ n $ ( $ 1 \le n \le 2 \cdot 10^5 $ ) — the number of nodes in the tree.

The next $ n-1 $ lines of each test case contain two integers each — $ u $ , $ v $ indicating an edge between $ u $ and $ v $ ( $ 1 \le u, v \le n $ ).

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

Output the sum modulo $ 10^9+7 $ for each test case.

## 样例 #1

### 样例输入 #1

```
1
6
1 2
1 3
3 4
3 5
3 6
```

### 样例输出 #1

```
288
```

## 提示

Let us find $ F (A) $ for the configuration $ A = [0,1,0,0,1,1] $ ( $ A[i] $ denotes the value of node $ i $ ). Initially (at $ t = 0 $ ) our tree is as shown in the picture below. In each node, two values are shown: the number and the value of this node. $ S (0) $ for this configuration is $ 3 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1777D/10211706e57f1b1e88b0d4ddb7c1af191838660c.png)At $ t = 1 $ the configuration changes to $ [1,0,0,0,0,0] $ . The tree looks as shown below. $ S (1) = 1 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1777D/c3bc7f260147d61f562afc931fe76e6b883432c7.png)At $ t = 2 $ the configuration changes to $ [0,0,0,0,0,0] $ . The tree looks as shown below. $ S (2) = 0 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1777D/fa1abea375196a437b8f0800465795a0a4b9553a.png)For all $ t>2 $ , the graph remains unchanged, so $ S (t)=0 $ for all $ t > 2 $ . So, for the initial configuration $ A = [0,1,0,0,1,1] $ , the value of $ F (A) = 3 + 1 = 4 $ .

Doing this process for all possible $ 2^{6} $ configurations yields us an answer of $ \textbf{288} $ .

## 题解
**题目定义的这些量我们一个也不会高效的求。那么只能利用对称性整体考虑了。**

![[Pasted image 20240716133519.png]]
本题我们需要我们能够**推导我们的结论**，首先，我们的第 $i$ 个结点，在第 $k$ 轮后的结果，就是我们的这个节点的 $k$ 级儿子的所有权值的**异或和**。

现在只考虑每个子树内相同深度的点集在 $2^n$ 种情况中的贡献。

根据异或的性质可知，当且仅当点集内有奇数个 1 时才会造成贡献，而满足这种情况的方案数为 $\sum_{i=1}^{cnt}[i\equiv$$1\pmod{2}]\binom{cnt}i$,也就是 $2^cnt-1$ 种。其中 cnt 为点集的大小。

为什么呢？根据二项式定理可知：
$$\sum_{i=0}^{cnt}(-1)^i\cdot\begin{pmatrix}cnt\\i\end{pmatrix}=(-1+1)^{cnt}=0$$
$$\sum_{i=0}^{cnt}\begin{pmatrix}cnt\\i\end{pmatrix}=(1+1)^{cnt}=2^{cnt}$$
所以 $\sum_i=1^{cnt}[i\equiv1\pmod2)]\binom{cnt}i=\frac{2^{cnt}-0}2=2^{cnt-1}$。

因此每个点集的贡献数为 $2^{cnt-1}\times2^{n-cnt}=2^{n-1}$。也就是说，我们每一个点在每一次的贡献的可能性方案数对应有 $2^{n}$ 种，于是我们就可以通过我们的上诉方法进行地推即可。
