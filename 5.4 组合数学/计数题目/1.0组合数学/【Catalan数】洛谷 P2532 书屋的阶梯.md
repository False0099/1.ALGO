# [AHOI2012] 树屋阶梯

## 题目描述

![](https://cdn.luogu.com.cn/upload/pic/1630.png) 

 ![](https://cdn.luogu.com.cn/upload/pic/1631.png)

## 输入格式

一个正整数 $N$，表示阶梯的高度。

## 输出格式

一个正整数，表示搭建方法的个数。**注**：搭建方法的个数可能很大。

## 样例 #1

### 样例输入 #1

```
3
```

### 样例输出 #1

```
5
```

## 提示

- 对于 $40\%$ 的数据，满足 $1\le N\le 20$。
- 对于 $80\%$ 的数据，满足 $1\le N\le 300$。
- 对于 $100\%$ 的数据，满足 $1\le N\le 500$。

## 题解
由Catalan数的第二定义，我们可以发现，我们所求的答案就是第n个Catalan数

```cpp
#include<iostream>
#include<stdio.h>
using namespace std;
int f[550][500];//f[i][j]表示第i个数的第j位。 
int len=1;
void add(int u)
{
	for(int i=1;i<=len;i++)
		f[u][i]=f[u-1][i]+f[u][i];
	for(int i=1;i<=len;i++)
	{
		f[u][i+1]+=f[u][i]/10;
		f[u][i]%=10;
	}
	if(f[u][len+1])len++;
}
int main()
{
	int n,p;
	cin>>n;
	f[1][1]=1;
	for(int i=2;i<=n+1;i++)
		for(int j=1;j<=i;j++)
			add(j);
	for(int i=len;i>0;i--)
		cout<<f[n][i];
}
```