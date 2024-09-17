# 
## 题目描述
有三个正整数a,b,c(0<a,b,c<10^6)，其中c不等于b。若a和c的最大公约数为b，现已知a和b，求满足条件的最小的c。

## 输入格式
第一行输入一个n，表示有n组测试数据，接下来的n行，每行输入两个正整数a,b。


## 输出格式

输出对应的c，每组测试数据占一行。

## 样例 #1

### 样例输入 #1

```
2
6 2
12 4

```

### 样例输出 #1

```
4
8

```


## 题解
暴力枚举b-ab中的所有数，并以此判断每个数是否符合要求。

## 代码
```cpp
#include<stdio.h>
int gcd(int a,int b)			//用gcd算法求出a与b的最大公约数 
{
	if(b==0)
	{
		return a;
	}
	else
	{
		return gcd(b,a%b);
	}
}
int main()
{
	int a,b,c,i,n;
	
	scanf("%d",&n);
	while(n--)
	{
		scanf("%d %d",&a,&b);	//输入a,b 
		
		for(i=2*b;i<a;i+=b)		 
		{
			if(gcd(a,i)==b)
			{
				printf("%d\n",i);
				break;
			}
		}
		
	}
	return 0;
}

```