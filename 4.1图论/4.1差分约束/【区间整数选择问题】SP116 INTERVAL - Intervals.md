# INTERVAL - Intervals

## 题面翻译

有 $n$ 个区间，在区间 $[a_i,b_i]$ 中至少取任意互不相同的 $c_i$ 个整数。求在满足 $n$ 个区间的情况下，至少要取多少个正整数。

### 输入格式

**本题有多组数据**。

第一行的一个整数 $T$ 表示数据个数。

对于每组数据：

第一行包含一个整数 $n(1\leq n\leq 50000)$ 表示区间数。

以下 $n$ 行描述区间。

输入的第 $i+1$ 行包含三个整数 $a_i,b_i,c_i$，由空格分开。其中 $0\leq a_i\leq b_i\leq 50000，1\leq c_i\leq b_i-a_i+1$。

### 输出格式

对于每组数据，输出一个对于 $n$ 个区间 $[a_i,b_i]$ 
至少取 $c_i$ 个不同整数的数的总个数。

### 样例

Input：

```
1
5
3 7 3
8 10 3
6 8 1
1 3 1
10 11 1
```

Output：

```
6
```


### 样例解释

可以取 $3,4,5,8,9,10$，为符合条件且取数个数最少的一组解。

## 题目描述

You are given n closed integer intervals \[a $ _{i} $ , b $ _{i} $ \] and n integers c $ _{1} $ , ..., c $ _{n} $ .

   
### Task

Write a program that:

- Reads the number of intervals, their endpoints and integers c $ _{1} $ , ..., c $ _{n} $ from the standard input,
- Computes the minimal size of a set Z of integers which has at least c $ _{i} $ common elements with interval \[a $ _{i} $ , b $ _{i} $ \], for each i = 1, 2, ..., n,
- Writes the answer to the standard output.

## 输入格式

The input begins with the integer t, the number of test cases. Then t test cases follow.

 For each test case the first line of the input contains an integer n (1 <= n <= 50000) - the number of intervals. The following n lines describe the intervals. Line (i+1) of the input contains three integers a $ _{i} $ , b $ _{i} $ and c $ _{i} $ separated by single spaces and such that 0 < = a $ _{i} $ < = b $ _{i} $ <= 50000 and 1 < = c $ _{i} $ < = b $ _{i} $ -a $ _{i} $ +1.

## 输出格式

For each test case the output contains exactly one integer equal to the minimal size of set Z sharing at least c $ _{i} $ elements with interval \[a $ _{i} $ , b $ _{i} $ \], for each i= 1, 2, ..., n.

## 样例 #1

### 样例输入 #1

```
1
5
3 7 3
8 10 3
6 8 1
1 3 1
10 11 1
```

### 样例输出 #1

```
6
```

## 题解
我们记我们的 $s[i]$ 表示我们从 0 节点到我们的 $i$ 节点的所有可能的种类个数有多少个，又因为我们的区间有 $c$ 个一定要选，所以我们就满足：$s[r]-s[l-1]\geq c$,但这些只能是我们的一个部分条件，我们还需要一些隐藏的条件：比如：我们每一个数只能选择一次，那么就有：$s[r]-s[r-1]\leq 1$, $0\geq s[r]-s[r-1]$。

```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
#include <cmath>
#include <cstdlib>
#include <queue>
//头文件请忽略
using namespace std;
const int maxn=500010;
int ver[maxn],head[maxn],edge[maxn],Next[maxn],tot,d[maxn];//d[i]表示从1到i至少需要多少个整数 
int n;
queue<int>q;
bool v[maxn+5]; 
void add(int x,int y,int z){
	ver[++tot]=y,edge[tot]=z,Next[tot]=head[x],head[x]=tot;
}//加边函数
void SPFA(){
	memset(d,-1,sizeof(d));
	memset(v,0,sizeof(v));
	d[0]=0;v[0]=1;//以0号节点为起点
	q.push(0);
	while(q.size()){
		int x=q.front();
		q.pop();
		v[x]=0;
		for(int i=head[x];i;i=Next[i]){
			int y,z;
			y=ver[i];
			z=edge[i];
			if(d[y]<d[x]+z){
				d[y]=d[x]+z;
				if(!v[y])	q.push(y),v[y]=1;
			}
		}
	}
}
int main(){
	int t;
	scanf("%d",&t);
	scanf("\n");
	for(int k=1;k<=t;k++){
		tot=0;
		int mn=-1000; 
		memset(ver,0,sizeof(ver));
		memset(head,0,sizeof(head));
		memset(Next,0,sizeof(Next));
		memset(edge,0,sizeof(edge));//多组数据记得清空
		scanf("%d",&n);
		for(int i=1;i<=n;i++){
			int a=0,b=0,c=0;
			scanf("%d%d%d",&a,&b,&c);
			add(a,b+1,c);
			mn=max(mn,b);//建图
		}
		for(int i=1;i<=mn+1;i++){
			add(i-1,i,0);
			add(i,i-1,-1);
		}//建图
		SPFA();//spfa求最长路
		if(k<t){
			printf("%d\n",d[mn+1]); 
		}else{
			printf("%d",d[mn+1]); 
		}
		
	}

	return 0;
}
```