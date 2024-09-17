# Maximum White Subtree

## 题面翻译

- 给定一棵 $n$ 个节点无根树，每个节点 $u$ 有一个颜色 $a_u$，若 $a_u$ 为 $0$ 则 $u$ 是黑点，若 $a_u$ 为 $1$ 则 $u$ 是白点。
- 对于每个节点 $u$，选出一个**包含** $u$ 的连通子图，设子图中白点个数为 $cnt_1$，黑点个数为 $cnt_2$，请最大化 $cnt_1 - cnt_2$。并输出这个值。
- $1 \leq n \leq 2 \times 10^5$，$0 \leq a_u \leq 1$。

## 题目描述

You are given a tree consisting of $ n $ vertices. A tree is a connected undirected graph with $ n-1 $ edges. Each vertex $ v $ of this tree has a color assigned to it ( $ a_v = 1 $ if the vertex $ v $ is white and $ 0 $ if the vertex $ v $ is black).

You have to solve the following problem for each vertex $ v $ : what is the maximum difference between the number of white and the number of black vertices you can obtain if you choose some subtree of the given tree that contains the vertex $ v $ ? The subtree of the tree is the connected subgraph of the given tree. More formally, if you choose the subtree that contains $ cnt_w $ white vertices and $ cnt_b $ black vertices, you have to maximize $ cnt_w - cnt_b $ .

## 输入格式

The first line of the input contains one integer $ n $ ( $ 2 \le n \le 2 \cdot 10^5 $ ) — the number of vertices in the tree.

The second line of the input contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ 0 \le a_i \le 1 $ ), where $ a_i $ is the color of the $ i $ -th vertex.

Each of the next $ n-1 $ lines describes an edge of the tree. Edge $ i $ is denoted by two integers $ u_i $ and $ v_i $ , the labels of vertices it connects $ (1 \le u_i, v_i \le n, u_i \ne v_i $ ).

It is guaranteed that the given edges form a tree.

## 输出格式

Print $ n $ integers $ res_1, res_2, \dots, res_n $ , where $ res_i $ is the maximum possible difference between the number of white and black vertices in some subtree that contains the vertex $ i $ .

## 样例 #1

### 样例输入 #1

```
9
0 1 1 1 0 0 0 0 1
1 2
1 3
3 4
3 5
2 6
4 7
6 8
5 9
```

### 样例输出 #1

```
2 2 2 2 2 1 1 0 2
```

## 样例 #2

### 样例输入 #2

```
4
0 0 1 0
1 2
1 3
1 4
```

### 样例输出 #2

```
0 -1 1 -1
```

## 提示

The first example is shown below:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1324F/e1f60f9681db9f4f9199c7a23c4eb447ad36532b.png)

The black vertices have bold borders.

In the second example, the best subtree for vertices $ 2, 3 $ and $ 4 $ are vertices $ 2, 3 $ and $ 4 $ correspondingly. And the best subtree for the vertex $ 1 $ is the subtree consisting of vertices $ 1 $ and $ 3 $ .

## 题解
首先不妨钦定 1 是这棵树的根。我们考虑过一个点 $u$ 的连通块 i 可以被分为两部分，第一部分是以 $u$ 为根的子树内的部分，第二部分是 $u$ 为根的子树外的部分。如果能分别计算出这两部分的最大值，显然将他们加起来就是 $u$ 所在连通块的最大值。

首先考虑第一部分的计算，是一个基础的树形 dp, 设 $f_u$ 是考虑以 $u$ 为根的子树，$u$ 所在的连通块的最大值。转移为

$$
f_u=\text{colour}_u+\sum_{v\in\text{Subtree}(u)}\max(f_v,0)
$$

其中若 $a_u=1$,则 $\operatorname{colour}_u=1$,否则 colour $_u--1$。即枚举 $u$ 的每个子节点 $v$,若 $f_v$ 大于 0, 则将 $v$ 子树内的连通块与 $u$ 联通。


考虑第二部分的计算，也是一个树形 dp。设 $g_u$ 是整张图去掉以 $u$ 为根的子树，但保留点 $u$ 以后构成的图中，$u$ 所在的连通块的最大值形象地说，$g_u$ 所代表的连通块要么只有 $u$ 一个节点，要么与 $u$ 直接相连的只有 $u$ 的父亲一个节点。

设 $u$ 的父亲为 $p$, $u$ 的转移一定来自 $g_p$ 和 $u$ 的兄弟节点的子树。即
$$
g_u=\text{colour}_u+\max(0,g_p+\sum_{v\in\text{Subtree}(p)}^{v\neq u}\max(f_v,0))
$$

注意到 $g_u$ 的最后一个 $\Sigma$ 长得很像 $f_p$ 的计算过程，我们考虑用 $f_p$ 来表示这个式子。由于

$$
f_p=\mathrm{colour}_p+\sum_{v\in\mathrm{Subtree}(p)}\max(f_v,0)
$$

所以
 $\max(f_v,0))=f_p-\max(0,f_u)-\operatorname{colour}_p$
$$\begin{aligned}\text{因此}\\\\g_u&=\text{colour}_u+\max(0,g_p+f_p-\max(0,f_u)-\mathrm{colour}_p)\end{aligned}$$

最后考虑统计答案，我们注意到 color $_u$ 被算了两遍，所以要在 $g_u$ 中减去一遍。当然，去掉 color $_u$ 以后，$g_u$ 也可以整个不选。因此

$$
ans_u=f_u+\max(0,g_u-\mathrm{colour}_u)
$$

做两次 dfs 即可，总时间复杂度 $O(n)$。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
int f[N],h[N],ne[N<<1],e[N<<1],idx,n,a[N],t[N];
void add(int u,int v) {ne[++idx]=h[u],e[idx]=v,h[u]=idx;}
void dfs1(int u,int father)
{
	f[u]=a[u];
	for(int i=h[u];~i;i=ne[i])
	{
		int j=e[i];
		if(j == father) continue ;
		dfs1(j,u); f[u]+=max(f[j],0);
	}
}
void dfs2(int u,int father)
{
	t[u]=f[u]; t[u]+=max(t[father]-max(f[u],0),0);
	for(int i=h[u];~i;i=ne[i])
	{
		int j=e[i];
		if(j == father) continue ;
		dfs2(j,u);
	}
}
int main()
{
	memset(h,-1,sizeof h); scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	for(int i=1;i<=n;i++) if(! a[i]) a[i]=-1;
	for(int i=1;i<n;i++)
	{
		int u,v; scanf("%d%d",&u,&v);
		add(u,v); add(v,u);
	}
	dfs1(1,0); dfs2(1,0);
	for(int i=1;i<=n;i++) printf("%d ",t[i]);
	return 0;
}
```
