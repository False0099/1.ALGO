# [USACO 08 MAR] Land Acquisition G

## 题目描述

Farmer John 准备扩大他的农场，眼前他正在考虑购买 $N$ 块长方形的土地。

如果 FJ 单买一块土地，价格就是土地的面积。但他可以选择并购一组土地，并购的价格为这些土地中最大的长乘以最大的宽。比如 FJ 并购一块 $3 \times 5$ 和一块 $5 \times 3$ 的土地，他只需要支付 $5 \times 5=25$ 元，比单买合算。

FJ 希望买下所有的土地。他发现，将这些土地分成不同的小组来并购可以节省经费。给定每份土地的尺寸，请你帮助他计算购买所有土地所需的最小费用。

## 输入格式

第一行一个整数 $N$（$1 \leq N \leq 5 \times 10^4$）。

接下来 $N$ 行，每行两个整数 $w_i$ 和 $l_i$，代表第 $i$ 块土地的长和宽。保证土地的长和宽不超过 $10^6$。

## 输出格式

输出买下所有土地的最小费用。

## 样例 #1

### 样例输入 #1

```
4 
100 1 
15 15 
20 5 
1 100
```

### 样例输出 #1

```
500
```

## 提示

将所有土地分为三组：

- 第一块土地为第一组，花费 $100 \times 1=100$；
- 第二，三块土地为第二组，花费 $20 \times 15=300$；
- 第四块土地为第三组，花费 $1 \times 100=100$；

总花费为 $500$，可以证明不存在更优的方案。

## 题解

首先发现如果一块土地的长和宽都小于另一块土地，那么购买它不用花费任何代价。
将剩下的土地按长从小到大排序，那么宽是从大到小的。
然后，我们对于剩余的部分进行一个 dp，我们设 $f[i]$ 表示我们前 i 个的最小花费是多少，那么我们就有：
$$f_i=\min_{j=1}^i\{f_{j-1}+w_ih_j\}$$

这么做，我们的复杂度是我们的 $o(n^2)$ 的，我们于是需要我们去进行我们的斜率优化。

```cpp
#include<cstdio>
#include<algorithm>
#define RG register
#define R RG int
#define G c=getchar()
#define Calc(i,j) (f[j-1]-f[i-1])/(a[i].h-a[j].h)
//method1:求出临界值
//method2:求出斜率
using namespace std;
const int N=1e5+9;
int q[N];
double f[N],k[N];
//method1:k_i为决策直线q_i与q_i+1的临界值（交点）
//method2:k_i为决策点q_i与q_i+1所连成直线的斜率
struct Land{
	int w,h;//结构体排序
	inline bool operator<(RG Land&x)const{
		return h>x.h||(h==x.h&&w>x.w);
	}
}a[N];
inline int in(){
	RG char G;
	while(c<'-')G;
	R x=c&15;G;
	while(c>'-')x=x*10+(c&15),G;
	return x;
}
int main(){
	R n=in(),i,h,t;
	for(i=1;i<=n;++i)
		a[i].w=in(),a[i].h=in();
	sort(a+1,a+n+1);
	for(h=i=1;i<=n;++i)//双指针扫描去除无用矩形
		if(a[h].w<a[i].w)a[++h]=a[i];
	n=h;
	for(h=i=1,t=0;i<=n;++i){
		while(h<t&&k[t-1]>=Calc(q[t],i))--t;//维护临界值/斜率单调
		k[t]=Calc(q[t],i);q[++t]=i;//加入决策直线/决策点
		while(h<t&&k[h]<=a[i].w)++h;//弹出已经不优的决策
		f[i]=(double)a[q[h]].h*a[i].w+f[q[h]-1];//求出最优解
	}
	printf("%.0lf\n",f[n]);
	return 0;
}
```