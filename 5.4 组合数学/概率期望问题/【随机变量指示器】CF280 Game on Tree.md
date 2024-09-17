# Game on Tree

## 题面翻译

**题目描述**

给定一棵有根树，结点编号从 $1$ 到 $n$。根结点为 $1$ 号结点。

对于每一次操作，等概率的选择一个**尚未被删去**的结点并将它及其子树全部删去。当所有结点被删除之后，游戏结束；也就是说，删除 $1$ 号结点后游戏即结束。

要求求出删除所有结点的期望操作次数。

**输入格式**

第一行，一个正整数 $n$ 表示结点数量。

接下来 $n-1$ 行每行两个数，表示树上的一条连接 $a_i$ 与 $b_i$ 的边 $(a_i,b_i)$

保证给定的数据是一棵树。

**输出格式**

输出一个实数，表示期望操作次数。答案误差在 $10^{-6}$ 之内则认为正确。

**样例解释**

在第一个样例中，有两种情况：

一种是直接删除根（即 $1$ 号结点），另一种是先删去 $2$ 号结点，再删除 $1$ 号结点。

操作次数的期望是 $1\times \dfrac12+2\times\dfrac12=1.5$。

在第二个样例中，情况更为复杂。其中有两种情况会将问题转化成第一个样例，而剩下的一种情况会一次全部删除。

操作次数的期望是 $1\times\dfrac13+(1+1.5)\times\dfrac23=\dfrac13+\dfrac53=2$。

## 题目描述

Momiji has got a rooted tree, consisting of $ n $ nodes. The tree nodes are numbered by integers from $ 1 $ to $ n $ . The root has number $ 1 $ . Momiji decided to play a game on this tree.

The game consists of several steps. On each step, Momiji chooses one of the remaining tree nodes (let's denote it by $ v $ ) and removes all the subtree nodes with the root in node $ v $ from the tree. Node $ v $ gets deleted as well. The game finishes when the tree has no nodes left. In other words, the game finishes after the step that chooses the node number $ 1 $ .

Each time Momiji chooses a new node uniformly among all the remaining nodes. Your task is to find the expectation of the number of steps in the described game.

## 输入格式

The first line contains integer $ n $ $ (1<=n<=10^{5}) $ — the number of nodes in the tree. The next $ n-1 $ lines contain the tree edges. The $ i $ -th line contains integers $ a_{i} $ , $ b_{i} $ $ (1<=a_{i}, b_{i}<=n; a_{i}≠b_{i}) $ — the numbers of the nodes that are connected by the $ i $ -th edge.

It is guaranteed that the given graph is a tree.

## 输出格式

Print a single real number — the expectation of the number of steps in the described game.

The answer will be considered correct if the absolute or relative error doesn't exceed $ 10^{-6} $ .

## 样例 #1

### 样例输入 #1

```
2
1 2
```

### 样例输出 #1

```
1.50000000000000000000
```

## 样例 #2

### 样例输入 #2

```
3
1 2
1 3
```

### 样例输出 #2

```
2.00000000000000000000
```

## 提示

In the first sample, there are two cases. One is directly remove the root and another is remove the root after one step. Thus the expected steps are:

 $ 1×(1/2)+2×(1/2)=1.5 $ In the second sample, things get more complex. There are two cases that reduce to the first sample, and one case cleaned at once. Thus the expected steps are:

 $ 1×(1/3)+(1+1.5)×(2/3)=(1/3)+(5/3)=2 $

## 题解
我们这一题的思路还是采用我们的贡献法，我们设 $x_{i}$ 表示，我们删除 i 节点及其子树需要对 i 操作的次数的期望。

而显然，我们如果要进行操作，那么我们一定是不能对这个节点的父亲节点进行操作的，也就是说，我们这一个点进行操作的概率就是：i 节点在随机序列中在所有祖先的前面的概率。也就是：$\dfrac{1}{dep[i]}$

因此，我们的代码就很简单。


```cpp
#include<cstdio>
double ans=0.00;
int cnt=0;
int h[100005],to[200005],ver[200005];
inline int read() {
    register int x=0,f=1;register char s=getchar();
    while(s>'9'||s<'0') {if(s=='-') f=-1;s=getchar();}
    while(s>='0'&&s<='9') {x=x*10+s-'0';s=getchar();}
    return x*f;
}
inline void add(int x,int y) {to[++cnt]=y;ver[cnt]=h[x];h[x]=cnt;}
inline void dfs(int x,int dep,int fa) {
    ans+=1.00/dep;
    for(register int i=h[x],y;i;i=ver[i]) {if((y=to[i])==fa) continue; dfs(y,dep+1,x);}
}
int main() {
    int n=read();
    for(register int i=1,x,y;i<n;++i) {x=read();y=read();add(x,y);add(y,x);}
    dfs(1,1,-1); printf("%.6lf\n",ans);
    return 0;
}
```