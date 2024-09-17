### Problem Statement

You are given an undirected graph $G$ with $N$ vertices and $M$ edges. For $i = 1, 2, \ldots, M$, the $i$ \-th edge is an undirected edge connecting vertices $u_i$ and $v_i$.

A graph with $N$ vertices is called **good** if the following condition holds for all $i = 1, 2, \ldots, K$:

-   there is no path connecting vertices $x_i$ and $y_i$ in $G$.

The given graph $G$ is good.

You are given $Q$ independent questions. Answer all of them. For $i = 1, 2, \ldots, Q$, the $i$ \-th question is as follows.

-   Is the graph $G^{(i)}$ obtained by adding an undirected edge connecting vertices $p_i$ and $q_i$ to the given graph $G$ good?

### Constraints

-   $2 \leq N \leq 2 \times 10^5$
-   $0 \leq M \leq 2 \times10^5$
-   $1 \leq u_i, v_i \leq N$
-   $1 \leq K \leq 2 \times 10^5$
-   $1 \leq x_i, y_i \leq N$
-   $x_i \neq y_i$
-   $i \neq j \implies \lbrace x_i, y_i \rbrace \neq \lbrace x_j, y_j \rbrace$
-   For all $i = 1, 2, \ldots, K$, there is no path connecting vertices $x_i$ and $y_i$.
-   $1 \leq Q \leq 2 \times 10^5$
-   $1 \leq p_i, q_i \leq N$
-   $p_i \neq q_i$
-   All input values are integers.


### Input

The input is given from Standard Input in the following format:


$N$ $M$
$u_1$ $v_1$
$u_2$ $v_2$
$\vdots$
$u_M$ $v_M$
$K$
$x_1$ $y_1$
$x_2$ $y_2$
$\vdots$
$x_K$ $y_K$
$Q$
$p_1$ $q_1$
$p_2$ $q_2$
$\vdots$
$p_Q$ $q_Q$


### Output

Print $Q$ lines. For $i = 1, 2, \ldots, Q$, the $i$ \-th line should contain the answer to the $i$ \-th question: `Yes` if the graph $G^{(i)}$ is good, and `No` otherwise.


## 题解
我们本题的想法是：通过我们的并查集维护我们的连通性，而对于我们的要求 $(a,b)$ 不连通，我们可以把 $a$ 的父节点和 $b$ 的父节点构成的点对存在一个 map 种，然后对于每一个查询，直接去 map 中找我们对应的点对是否存在，如果存在，我们就直接退出，否则，我们就继续即可。