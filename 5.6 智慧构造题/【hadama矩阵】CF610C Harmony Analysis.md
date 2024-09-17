# Harmony Analysis

## 题面翻译

给定 $k$，求 $2^k$ 个 $2^k$ 维向量满足每个向量的坐标表示中任意一维都为 $1$ 或 $-1$，且这些向量两两点积为 $0$。

$0\leq k\leq 9$。

## 题目描述

The semester is already ending, so Danil made an effort and decided to visit a lesson on harmony analysis to know how does the professor look like, at least. Danil was very bored on this lesson until the teacher gave the group a simple task: find $ 4 $ vectors in $ 4 $ -dimensional space, such that every coordinate of every vector is $ 1 $ or $ -1 $ and any two vectors are orthogonal. Just as a reminder, two vectors in $ n $ -dimensional space are considered to be orthogonal if and only if their scalar product is equal to zero, that is:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF610C/1ed68100811c8d9a7f92461867e21d565afe33d0.png).Danil quickly managed to come up with the solution for this problem and the teacher noticed that the problem can be solved in a more general case for $ 2^{k} $ vectors in $ 2^{k} $ -dimensinoal space. When Danil came home, he quickly came up with the solution for this problem. Can you cope with it?

## 输入格式

The only line of the input contains a single integer $ k $ ( $ 0<=k<=9 $ ).

## 输出格式

Print $ 2^{k} $ lines consisting of $ 2^{k} $ characters each. The $ j $ -th character of the $ i $ -th line must be equal to ' $ * $ ' if the $ j $ -th coordinate of the $ i $ -th vector is equal to $ -1 $ , and must be equal to ' $ + $ ' if it's equal to $ +1 $ . It's guaranteed that the answer always exists.

If there are many correct answers, print any.

## 样例 #1

### 样例输入 #1

```
2
```

### 样例输出 #1

```
++**
+*+*
++++
+**+
```

## 提示

Consider all scalar products in example:

- Vectors $ 1 $ and $ 2 $ : $ (+1)·(+1)+(+1)·(-1)+(-1)·(+1)+(-1)·(-1)=0 $
- Vectors $ 1 $ and $ 3 $ : $ (+1)·(+1)+(+1)·(+1)+(-1)·(+1)+(-1)·(+1)=0 $
- Vectors $ 1 $ and $ 4 $ : $ (+1)·(+1)+(+1)·(-1)+(-1)·(-1)+(-1)·(+1)=0 $
- Vectors $ 2 $ and $ 3 $ : $ (+1)·(+1)+(-1)·(+1)+(+1)·(+1)+(-1)·(+1)=0 $
- Vectors $ 2 $ and $ 4 $ : $ (+1)·(+1)+(-1)·(-1)+(+1)·(-1)+(-1)·(+1)=0 $
- Vectors $ 3 $ and $ 4 $ : $ (+1)·(+1)+(+1)·(-1)+(+1)·(-1)+(+1)·(+1)=0 $

## 题解
我们本题的前置知识是：**Hardama**矩阵，我们的**Hardama**矩阵是由+1 和-1 构成的且满足 $H_{n}\times H_{n}^{T}=nI$,（其中 $I$ 为 $n$ 阶方阵）。我们定义如下：

$H_1=[1]$

$H_2=\begin{bmatrix}1&1\\1&-1\end{bmatrix}$
 
$H_4=\begin{bmatrix}1&1&1&1\\1&-1&1&-1\\1&1&-1&-1\\1&-1&-1&1\end{bmatrix}$

  
对于我们的 $n$ 阶 **Hardama**矩阵，我们有：

$$
H_{2^k}=\begin{bmatrix}H_{2^{k-1}}&H_{2^{k-1}}\\H_{2^{k-1}}&-H_{2^{k-1}}\end{bmatrix}
$$


通过我们的上面的公式，我们就可以任意的构造出我们的 $2^k$ 阶**Hardama**矩阵。

在本题中，我们只需要直接输出我们**Hardama**矩阵即可。
```cpp
#include <stdio.h>
#include <string.h>
#include <bits/stdc++.h>
using namespace std;

const int MAXN=1e3+55;
int hmat[MAXN][MAXN],n;
void Hadamard(int n){
	for(int i=0;i<n;++i)
    for(int j=0;j<n;++j){       
		int cnt=0;
		for(int k=i&j;k;k>>=1) cnt+=k&1;
	    hmat[i][j]=((cnt&1)?-1:1);
    }
}
int main(){
	scanf("%d",&n);
	n=(1ll<<n);
	Hadamard(n);
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			if(hmat[i][j]==1){
				cout<<"+";
			}else{
				cout<<"*";
			}
		}
		puts("");
	}
	return 0;
}
```

