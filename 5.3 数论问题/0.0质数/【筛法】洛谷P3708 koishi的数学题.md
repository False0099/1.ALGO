# Koishi 的数学题

## 题目描述

Koishi 在 Flandre 的指导下成为了一名数学大师，她想了一道简单的数学题。

输入一个整数 $n$，设 $\displaystyle f(x) = \sum_{i=1}^n x \bmod i$，你需要输出 $f(1), f(2), \ldots , f(n)$。

按照套路，Koishi 假装自己并不会做这道题，就来求你帮忙辣。

## 输入格式

一个正整数 $n$。

## 输出格式

一行用空格分隔的 $n$ 个整数 $f(1), f(2), \ldots , f(n)$。

## 样例 #1

### 样例输入 #1

```
10
```

### 样例输出 #1

```
9 16 22 25 29 27 29 24 21 13
```

## 提示

对于 $20\%$ 的数据，$n \le 1000$。  
对于 $60\%$ 的数据，$n \le 10^5$。  
对于 $100\%$ 的数据，$1 \le n \le 10^6$。

## 题解
我们首先考虑我们的模运算是比较困难的，于是我们需要考虑转换到其他的式子，我们这里利用到我们的下面一个式子：
$$x\%i=x-i\cdot\lfloor\frac xi\rfloor $$

于是，我们就可以替换后得到：
$$f(x)=\sum_{i=1}^n\color{red}{\underbrace{x}_i}-i\cdot\lfloor\frac xi\rfloor=nx-\sum_{i=1}^xi\cdot\lfloor\frac xi\rfloor $$

我们如果直接去求的画，我们是不能做出来的，我们考虑去计算我们的差分，我们有：

$\begin{aligned}f(i)-f(i-1)=n-\sum_{i=1}^ni(\lfloor\frac xi\rfloor-\lfloor\frac{x-1}i\rfloor)\end{aligned}$ 
对于后面的$\sum$分类讨论：
1. $i|n$ 很明显多了一个 $i$ 
2. 反正没有多

 所以，后面的 $\sum$ 相当于是 $\sum _d|xd$, 也就是 $\sigma(x)$,也就是一个数的因数和。

 所以就可以 $O(n)$ 线性筛或 $O(nlogn)$ 的暴力计算 $\sigma$ 来解决此题啦！

```cpp
#include<cstdio>
#include<iostream>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<queue>
#include<map> 
using namespace std;
#define re register int
inline int read(){
    int x=0,ff=1;char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')ff=-1;c=getchar();}
    while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
    return x*ff;
}
int n,tot=0,a[1000005];
void prime(){
    for(int i=2;i<=n;i++){
        for(int j=i;j<=n/i;j++){
            a[i*j]+=i+j;
            if(i==j)a[i*j]-=i;
        }
    }
}
signed main(){
    n=read();printf("%d ",n-1);
    if(n==1)return 0;
    printf("%d ",2*(n-2));
    prime();
    for(int i=3;i<=n;i++){
        tot+=(i-2);
        tot-=a[i];
        printf("%d ",tot+(n-i)*i);
    }
    printf("\n");
    return 0;
}
```