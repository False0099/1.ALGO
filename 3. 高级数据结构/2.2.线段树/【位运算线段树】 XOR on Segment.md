# XOR on Segment

## 题面翻译

- 给定 $n$ 个数的序列 $a$。$m$ 次操作，操作有两种：
    1. 求 $\displaystyle\sum_{i=l}^r a_i$。
    2. 把 $a_l\sim a_r$ 异或上 $x$。
- $1\le n\le 10^5$，$1\le m\le 5\times 10^4$，$0\le a_i\le 10^6$，$1\le x\le 10^6$。

## 题目描述

You've got an array $ a $ , consisting of $ n $ integers $ a_{1}, a_{2},..., a_{n} $ . You are allowed to perform two operations on this array:

1. Calculate the sum of current array elements on the segment $ [l, r] $ , that is, count value $ a_{l}+a_{l+1}+...+a_{r} $ .
2. Apply the xor operation with a given number $ x $ to each array element on the segment $ [l, r] $ , that is, execute ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF242E/a6ed6800239445c652bf1618450a09b2fce8b86d.png). This operation changes exactly $ r-l+1 $ array elements.

Expression ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF242E/a0b0fe9e9428287337c0277ea02ca07fcf0a01a7.png) means applying bitwise xor operation to numbers $ x $ and $ y $ . The given operation exists in all modern programming languages, for example in language C++ and Java it is marked as "^", in Pascal — as "xor".

You've got a list of $ m $ operations of the indicated type. Your task is to perform all given operations, for each sum query you should print the result you get.

## 输入格式

The first line contains integer $ n $ ( $ 1<=n<=10^{5} $ ) — the size of the array. The second line contains space-separated integers $ a_{1}, a_{2},..., a_{n} $ ( $ 0<=a_{i}<=10^{6} $ ) — the original array.

The third line contains integer $ m $ ( $ 1<=m<=5·10^{4} $ ) — the number of operations with the array. The $ i $ -th of the following $ m $ lines first contains an integer $ t_{i} $ ( $ 1<=t_{i}<=2 $ ) — the type of the $ i $ -th query. If $ t_{i}=1 $ , then this is the query of the sum, if $ t_{i}=2 $ , then this is the query to change array elements. If the $ i $ -th operation is of type $ 1 $ , then next follow two integers $ l_{i}, r_{i} $ ( $ 1<=l_{i}<=r_{i}<=n $ ). If the $ i $ -th operation is of type $ 2 $ , then next follow three integers $ l_{i}, r_{i}, x_{i} $ ( $ 1<=l_{i}<=r_{i}<=n, 1<=x_{i}<=10^{6} $ ). The numbers on the lines are separated by single spaces.

## 输出格式

For each query of type $ 1 $ print in a single line the sum of numbers on the given segment. Print the answers to the queries in the order in which the queries go in the input.

Please, do not use the %lld specifier to read or write 64-bit integers in С++. It is preferred to use the cin, cout streams, or the %I 64 d specifier.

## 样例 #1

### 样例输入 #1

```
5
4 10 3 13 7
8
1 2 4
2 1 3 3
1 2 4
1 3 3
2 2 5 5
1 1 5
2 1 2 10
1 2 3
```

### 样例输出 #1

```
26
22
0
34
11
```

## 样例 #2

### 样例输入 #2

```
6
4 7 4 0 7 3
5
2 2 3 8
1 1 5
2 3 5 1
2 4 5 6
1 2 3
```

### 样例输出 #2

```
38
28
```

## 题解
我们对于位运算的一个思路就是把我们的每一位都拆开计算，然后再把我们的区间异或变为我们的区间取反操作。然后我们就可以把我们的线段树中维护的信息变成我们的每一个位。
```cpp
#include<iostream>
#include<cstdio>
#define ll int
#define re register
using namespace std;
struct node{
	ll l,r,tag;
	long long sum;
}tree[400010][22];
ll n,m,maxk,maxx,a[100001];
long long ans,ans2;
inline ll read()
{
	re ll r=0,w=1;
	re char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-') w=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		r=(r<<3)+(r<<1)+(ch^48);
		ch=getchar();
	}
	return r*w;
}
inline void pushup(ll x,ll k){tree[x][k].sum=tree[x<<1][k].sum+tree[x<<1|1][k].sum;}
inline void pushdown(ll x,ll k)
{
	if(tree[x][k].tag){
		re ll p=tree[x][k].tag;
		tree[x][k].tag=0;
		tree[x<<1][k].tag+=p;
		tree[x<<1|1][k].tag+=p;
		if(p&1){
			tree[x<<1][k].sum=(tree[x<<1][k].r-tree[x<<1][k].l+1)-tree[x<<1][k].sum;
			tree[x<<1|1][k].sum=(tree[x<<1|1][k].r-tree[x<<1|1][k].l+1)-tree[x<<1|1][k].sum;
		}
	}
}
void build(ll x,ll l,ll r)
{
	for(int k=1;k<=21;k++)
		tree[x][k].l=l,tree[x][k].r=r;
	if(l==r)
	{
		for(int k=1;k<=21;k++)
			if(a[l]&(1<<(k-1)))
				tree[x][k].sum=1;
		return ;
	}
	re ll mid=l+r>>1;
	build(x<<1,l,mid);
	build(x<<1|1,mid+1,r);
	for(int k=1;k<=21;k++)
		tree[x][k].sum=tree[x<<1][k].sum+tree[x<<1|1][k].sum;
}
void qurey(ll x,ll k,ll l,ll r)
{
	if(tree[x][k].l>=l&&tree[x][k].r<=r)
	{
		ans+=tree[x][k].sum<<(k-1);
		return ;
	}
	re ll mid=tree[x][k].l+tree[x][k].r>>1;
	pushdown(x,k);
	if(mid>=l) qurey(x<<1,k,l,r);
	if(mid<r) qurey(x<<1|1,k,l,r);
	pushup(x,k);
}
void change(ll x,ll k,ll l,ll r)
{
	if(tree[x][k].l>=l&&tree[x][k].r<=r)
	{
		tree[x][k].sum=(tree[x][k].r-tree[x][k].l+1)-tree[x][k].sum;
		tree[x][k].tag++;
		return ;
	}
	re ll mid=tree[x][k].l+tree[x][k].r>>1;
	pushdown(x,k);
	if(mid>=l) change(x<<1,k,l,r);
	if(mid<r) change(x<<1|1,k,l,r);
	pushup(x,k);
}
int main()
{
	n=read();
	for(int i=1;i<=n;i++)
		a[i]=read();
	build(1,1,n);
	m=read();
	ll opt,l,r,inx,k;
	for(int i=1;i<=m;i++)
	{
		opt=read();l=read();r=read();
		if(opt==1){
			ans=0;
			for(int k=1;k<=21;k++)
			{
				ans2=0;
				qurey(1,k,l,r);
				ans+=ans2;
			}
			printf("%lld\n",ans);
		}
		else{
			inx=read();
			for(int k=1;1<<(k-1)<=inx;k++)
				if(inx&(1<<(k-1)))
					change(1,k,l,r);
		}
	}
	return 0;
}
```