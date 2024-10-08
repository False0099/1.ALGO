## 描述：
给定大小为 $n$ 的有标号有根树，以 1 为根，求在树外引出一个点向树内任意连边使得构成的**简单图**不含**三元环**的方案数。答案对 $998244353$ 取模。

## 输入：
第一行一个正整数 $n$。  
第二行 $n-1$ 个正整数，分别表示 $p_2,p_3,\dots,p_n$，为 $2,3,\dots,n$ 节点的父亲节点编号。

## 输出：
一行一个整数表示答案

## 样例：
6
1 1 2 2 3

23

## 题解
我们本体等价于我们的**树上独立集**，我们可以采用我们的标准的树形 dp, $dp[i][0]$ 表示我们在某一个结点选或者不选，选的话我们就把这个点加入我们的独立集合当中，否则我们就天转到另一个。这样，我们就可以完成本题的 dp 转移：
$$dp_{u,0}=\prod_{v\in son_u}(dp_{v,0}+dp_{v,1})$$

