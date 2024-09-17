# Vasya and Magic Matrix

## 题面翻译

一个 $n$ 行 $m$ 列的矩阵, 每个位置有权值 $a_{i,j}$

给定一个出发点, 每次可以等概率的移动到一个权值小于当前点权值的点（不能移动就停止）,同时得分加上两个点之间欧几里得距离的平方 (欧几里得距离: $\sqrt{(x_1-x_2)^2+(y_1-y_2)^2}$)), 问得分的期望, 对 998244353 取模。

## 题目描述

Vasya has got a magic matrix $ a $ of size $ n \times m $ . The rows of the matrix are numbered from $ 1 $ to $ n $ from top to bottom, the columns are numbered from $ 1 $ to $ m $ from left to right. Let $ a_{ij} $ be the element in the intersection of the $ i $ -th row and the $ j $ -th column.

Vasya has also got a chip. Initially, the chip is in the intersection of the $ r $ -th row and the $ c $ -th column (that is, in the element $ a_{rc} $ ). Vasya performs the following process as long as possible: among all elements of the matrix having their value less than the value of the element with the chip in it, Vasya randomly and equiprobably chooses one element and moves his chip to this element.

After moving the chip, he adds to his score the square of the Euclidean distance between these elements (that is, between the element in which the chip is now and the element the chip was moved from). The process ends when there are no elements having their values less than the value of the element with the chip in it.

Euclidean distance between matrix elements with coordinates $ (i_1, j_1) $ and $ (i_2, j_2) $ is equal to $ \sqrt{(i_1-i_2)^2 + (j_1-j_2)^2} $ .

Calculate the expected value of the Vasya's final score.

It can be shown that the answer can be represented as $ \frac{P}{Q} $ , where $ P $ and $ Q $ are coprime integer numbers, and $ Q \not\equiv 0~(mod ~ 998244353) $ . Print the value $ P \cdot Q^{-1} $ modulo $ 998244353 $ .

## 输入格式

The first line of the input contains two integers $ n $ and $ m $ $ (1 \le n, m \le 1\, 000) $ — the number of rows and the number of columns in the matrix $ a $ .

The following $ n $ lines contain description of the matrix $ a $ . The $ i $ -th line contains $ m $ integers $ a_{i 1}, a_{i 2}, \dots, a_{im} ~ (0 \le a_{ij} \le 10^9) $ .

The following line contains two integers $ r $ and $ c $ $ (1 \le r \le n, 1 \le c \le m) $ — the index of row and the index of column where the chip is now.

## 输出格式

Print the expected value of Vasya's final score in the format described in the problem statement.

## 样例 #1

### 样例输入 #1

```
1 4
1 1 2 1
1 3
```

### 样例输出 #1

```
2
```

## 样例 #2

### 样例输入 #2

```
2 3
1 5 7
2 3 1
1 2
```

### 样例输出 #2

```
665496238
```

## 提示

In the first example, Vasya will move his chip exactly once. The expected value of the final score is equal to $ \frac{1^2 + 2^2+ 1^2}{3} = 2 $ .


## 题解
首先，我们这一题可以现根据我们的给定的矩阵，来建立一个图，表示我们矩阵上的某一个点。之后，如果我们想要表示我们的转移，我们就可以计算我们从这个点开始所能走过的路径和除以我们能走过的路径数，

于是我们的期望就可以写成
$\sum(x_{i}-x_{j})^2+(y_{i}-y_{j})^2+f_{j}$,这一点，我们把我们的式子拆开后，就可以用我们的前缀和进行优化了。


```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<stack>
#include<cstring>
#include<queue>
#include<algorithm>
#include<map>
#define int long long 
using namespace std; 
const int N=1e6+9;
const int mod=998244353;
struct node{
	int x,y;
	int val;
}a[N];
int f[N];
int n,m;
int A[N],Aon[N];//A记录 x^2 的前缀和, Aon 记录 x 的前缀和 
int B[N],Bon[N];//B记录 y^2 的前缀和, Bon 记录 y 的前缀和 
int F[N];//F记录 f^2 的前缀和 
int s,t;
int read()
{
	int f=1,x=0;
	char s=getchar();
	while(s<'0'||s>'9'){if(s=='-')f=-1;s=getchar();}
	while(s>='0'&&s<='9'){x=(x<<1)+(x<<3)+(s^'0');s=getchar();}
	return f*x;
}
bool cmp(node a,node b)
{
	return a.val<b.val;
}
int quick(int x,int p)
{
	int ret=1;
	while(p)
	{
		if(p&1) ret=ret*x%mod;
		x=x*x%mod;
		p>>=1;	
	} 
	return ret;
}
int top;
int Sum[N];
void Prepare()
{
	for(int i=1;i<=top;i++)
		A[i]=(A[i-1]+(a[i].x)*(a[i].x))%mod;
	for(int i=1;i<=top;i++)
		B[i]=(B[i-1]+(a[i].y)*(a[i].y))%mod;
	for(int i=1;i<=top;i++)
		Aon[i]=(Aon[i-1]+a[i].x)%mod;
	for(int i=1;i<=top;i++)
		Bon[i]=(Bon[i-1]+a[i].y)%mod; 
}
void DP(int i,int Num)
{
	int Inv=quick(Num,mod-2);
	f[i]=(f[i]+A[Num])%mod;//小的数的x的平方
	f[i]=(f[i]+B[Num])%mod;//小的数的y的平方
	f[i]=(f[i]-2*Aon[Num]*a[i].x%mod+mod)%mod;//减去x*以前的x的两倍
	f[i]=(f[i]-2*Bon[Num]*a[i].y%mod+mod)%mod;
	f[i]=(f[i]+Num*(a[i].x)*(a[i].x)%mod)%mod;
	f[i]=(f[i]+Num*(a[i].y)*(a[i].y)%mod)%mod; 
	f[i]=(f[i]+Sum[Num])%mod;
	f[i]=f[i]*Inv%mod; 
	Sum[i]=(Sum[i-1]+f[i])%mod;
}
signed main()
{
	n=read();
	m=read();
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			a[++top].x=i;
			a[top].y=j;
			a[top].val=read();
		}
	s=read(); t=read();
	sort(a+1,a+1+top,cmp);
	Prepare(); 
	int last=0;
	for(int i=1;i<=top;i++)
	{
		if(a[i].val!=a[i-1].val)
			last=i-1;//更新小的个数
		DP(i,last); 
		if(a[i].x==s and a[i].y==t)
			return printf("%lld\n",f[i]),0;
	}
	return 0;
}
```