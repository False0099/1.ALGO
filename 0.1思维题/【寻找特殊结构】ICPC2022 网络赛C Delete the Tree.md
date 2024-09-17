Alice wants to delete a tree. She can do the following operations:

·Delete: Delete a vertex in the tree and all the edges connected to it. 
· Shrink: Choose a vertex $x$ that has exactly two vertices connected to it; suppose the vertices
 are $u,v$ Alice can delete $x$ and the edges $(u,x),(x,v)$ and add a new edge $(u,v)$.

Alice wants to achieve her goal using the least number of Delete operations. Please help her.

## 输入：
The first line contains one integer $T\left(1\leq T\leq10^6\right)$, denoting the number of test cases. For each test case:
 The first line contains one integer $n\left(1\leq n\leq10^6\right)$, denoting the size of the tree.
 Then $n-1$ lines follow, each containing two integers $u,v$, denoting the edge that connects $u$ and $v$
 On the tree.
 It is guaranteed that the sum of $n$ will not exceed $10^6.$

## 输出：
For each test cases, output a single integer, denoting the least number of Delete operations that Alice must. Use.

## 样例：
```
2
2
1 2
5
1 2
1 3
2 4
2 5
```

```
2
3
```

## 题解
我们本题的方法是：推导我们的结论：我们进行**删除的次数就是我们的叶子结点的个数**！

原因如下：我们发现，我们对一条链进行操作，我们的操作次数一定就是我们的 $2$,因为我们有两个端点，这个时候，我们发现，我们的每一个子树的贡献都可以分开来分别计算。计算我们把这一颗子树缩水成一个点所需要的代价是多少，我们显然就会有：
$dp[i]=\sum dp[son]+count(son)-1$ 最后我们的答案显然就有：$ans=dp[1]+2$。

于是，我们最后只需要统计我们的字数个数即可。

