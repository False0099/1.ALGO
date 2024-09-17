# Bubble Sort

## 题面翻译

给定 $n$，求所有 $[1,n]$ 排列中逆序对个数的平均值，以分数形式输出。

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=242&page=show_problem&problem=3155

[PDF](https://uva.onlinejudge.org/external/120/p12004.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA12004/7274489195310e61414344341952c40f91061ff2.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA12004/8d9bc5b19690e707092921e6d02dc5f96907a226.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA12004/8337f49686b0fe71f9c33e0b28f0c9208e4c6678.png)

## 样例 #1

### 样例输入 #1

```
2
1
2
```

### 样例输出 #1

```
Case 1: 0
Case 2: 1/2
```

## 题解
本题采用随机变量指示器的方法，我们考虑计算每一个可能的组合对于我们的逆序对的贡献是多少。

这里，我们的逆序对贡献定义为：$X_{ij}$,其中我们的 T 事件表示在我们的随机序列 A 中 $i<j\land a[i]<a[j]$。

然后现在，我们就有：
$X=\sum_{i<j} X_{ij}$

两侧同时求期望，我们就有：
$$\text{到}E[X]=E\left[\sum_{i<j}X_{i,j}\right]$$

又有期望的线性性质 $E[X+Y]=E[X]+F[Y]$, 于是有

1.1

$$
E[X]=\sum_{i<j}E[X_{i,j}]=\sum_{i=1}^{n-1}\sum_{j=i+1}^{n}E[X_{i,j}]\quad1
$$


引入这一指示器变量的原因在于：上述问题中的 $X_{i,j}$ 显然存在依赖关系，但因为引入了指示器随机变量这一概念并有了这一强有力的断言，使得我们能够将 $\forall i<j$ 的 $E[X_{i,j}]$ 独立看待。那么，我们现在可以得出，对于 $\forall i,j$, $E[X_{i,j}]$ 的值是一样的，并且尝试去计算这个值。

对于任意 $X_{i,j}$ 都是一个指示器随机变量，其值非 0 即 1。根据期望的定义，它的期望值就是 $Pr\{T\}$ , 即 $T$ 事件发生的概率。现在只需求出 $Pr\{T\}$ 便可解决整个问题。显然有：

$$X_{i,j}=Pr\{T\}=\frac{\sum\limits_{i=1}^n\sum\limits_{j=1}^{i-1}1}{\left(\sum\limits_{i=1}^n\sum\limits_{j=1}^n1\right)-n}=\frac{\frac{n(n-1)}2}{n(n-1)}=\frac12\quad1.2$$

$$\begin{gathered}
\text{回带至 1.1 式,得:} \\
\begin{aligned}E[X]=\sum_{i=1}^n\sum_{j=i+1}^nE[X_{i,j}]=\sum_{i=1}^n\sum_{j=i+1}^n\frac{1}{2}=\frac{n(n-1)}{4}\end{aligned} 
\end{gathered}$$

