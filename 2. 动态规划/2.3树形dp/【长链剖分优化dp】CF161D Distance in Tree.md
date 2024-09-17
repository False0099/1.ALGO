# Distance in Tree

## 题面翻译

## 题目大意
输入点数为 $N$ 一棵树

求树上长度恰好为 $K$ 的路径个数
## 输入格式

第一行两个数字 $N,K$,如题意

接下来的 $N-1$ 行中, 每行两个整数 $u,v$ 表示一条树边 $(u,v)$

## 输出格式

一个整数 $ans$,如题意

在 $Codeforces$ 上提交时记得用 $\%I64d$ 哦.QwQ

## 数据范围
$1 \leq n \leq 50000$

$1 \leq k \leq 500$

感谢@Zhang_RQ 提供的翻译

## 题目描述

A tree is a connected graph that doesn't contain any cycles.

The distance between two vertices of a tree is the length (in edges) of the shortest path between these vertices.

You are given a tree with $ n $ vertices and a positive number $ k $ . Find the number of distinct pairs of the vertices which have a distance of exactly $ k $ between them. Note that pairs ( $ v $ , $ u $ ) and ( $ u $ , $ v $ ) are considered to be the same pair.

## 输入格式

The first line contains two integers $ n $ and $ k $ ( $ 1<=n<=50000 $ , $ 1<=k<=500 $ ) — the number of vertices and the required distance between the vertices.

Next $ n-1 $ lines describe the edges as " $ a_{i} $ $ b_{i} $ " (without the quotes) ( $ 1<=a_{i}, b_{i}<=n $ , $ a_{i}≠b_{i} $ ), where $ a_{i} $ and $ b_{i} $ are the vertices connected by the $ i $ -th edge. All given edges are different.

## 输出格式

Print a single integer — the number of distinct pairs of the tree's vertices which have a distance of exactly $ k $ between them.

Please do not use the %lld specifier to read or write 64-bit integers in С++. It is preferred to use the cin, cout streams or the %I 64 d specifier.

## 样例 #1

### 样例输入 #1

```
5 2
1 2
2 3
3 4
2 5
```

### 样例输出 #1

```
4
```

## 样例 #2

### 样例输入 #2

```
5 3
1 2
2 3
3 4
4 5
```

### 样例输出 #2

```
2
```

## 提示

In the first sample the pairs of vertexes at distance 2 from each other are (1, 3), (1, 5), (3, 5) and (2, 4).

## 题解
我们本体是求我们树上长度恰好为 K 的的路径个数，因为我们这一题数据范围较小，我们可以不使用点分治，长链剖分等思路。

我们可以采用我们的暴力 $dp[i][j]$ 表示以 i 为根节点，距离为 j 的的节点数有多少个。

于是，我们的转移就可以有：

```cpp
cnt=dp[i][k]*dp[son][need-k];
dp[i][k]=dp[son][k-1]
```


最后我们的答案就可以如下所示：
```cpp
#include<bits/stdc++.h> using namespace std; const int N=5e4+10; int f[N][610],n,k,res,h[N],ne[N<<1],e[N<<1],idx; void add(int u,int v) {ne[++idx]=h[u],e[idx]=v,h[u]=idx;} void dfs(int u,int father) { f[u][0]=1; for(int i=h[u];~i;i=ne[i]) { int j=e[i]; if(j == father) continue ; dfs(j,u); for(int t=0;t<k;t++) res+=f[u][t]*f[j][k-t-1]; for(int t=0;t<k;t++) f[u][t+1]+=f[j][t]; } } int main() { memset(h,-1,sizeof h); scanf("%d%d",&n,&k); for(int i=1;i<n;i++) { int u,v; scanf("%d%d",&u,&v); add(u,v); add(v,u); } dfs(1,0); printf("%d",res); return 0; }
```