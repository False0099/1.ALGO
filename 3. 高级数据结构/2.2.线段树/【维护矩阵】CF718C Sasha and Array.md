# Sasha and Array

## 题面翻译

- 在本题中，我们用 $f_i$ 来表示第 $i$ 个斐波那契数（$f_1=f_2=1,f_i=f_{i-1}+f_{i-2}(i\ge 3)$）。
- 给定一个 $n$ 个数的序列 $a$。有 $m$ 次操作，操作有两种：
    1. 将 $a_l\sim a_r$ 加上 $x$。
    2. 求 $\displaystyle\left(\sum_{i=l}^r f_{a_i}\right)\bmod (10^9+7)$。
- $1\le n,m\le 10^5$，$1\le a_i\le 10^9$。

## 题目描述

Sasha has an array of integers $ a_{1}, a_{2},..., a_{n} $ . You have to perform $ m $ queries. There might be queries of two types:

1. 1 l r x — increase all integers on the segment from $ l $ to $ r $ by values $ x $ ;
2. 2 l r — find ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF718C/9868345ffca37ba44cd594bdeb805f21011d5d1d.png), where $ f (x) $ is the $ x $ -th Fibonacci number. As this number may be large, you only have to find it modulo $ 10^{9}+7 $ .

In this problem we define Fibonacci numbers as follows: $ f (1)=1 $ , $ f (2)=1 $ , $ f (x)=f (x-1)+f (x-2) $ for all $ x>2 $ .

Sasha is a very talented boy and he managed to perform all queries in five seconds. Will you be able to write the program that performs as well as Sasha?

## 输入格式

The first line of the input contains two integers $ n $ and $ m $ ( $ 1<=n<=100000 $ , $ 1<=m<=100000 $ ) — the number of elements in the array and the number of queries respectively.

The next line contains $ n $ integers $ a_{1}, a_{2},..., a_{n} $ ( $ 1<=a_{i}<=10^{9} $ ).

Then follow $ m $ lines with queries descriptions. Each of them contains integers $ tp_{i} $ , $ l_{i} $ , $ r_{i} $ and may be $ x_{i} $ ( $ 1<=tp_{i}<=2 $ , $ 1<=l_{i}<=r_{i}<=n $ , $ 1<=x_{i}<=10^{9} $ ). Here $ tp_{i}=1 $ corresponds to the queries of the first type and $ tp_{i} $ corresponds to the queries of the second type.

It's guaranteed that the input will contains at least one query of the second type.

## 输出格式

For each query of the second type print the answer modulo $ 10^{9}+7 $ .

## 样例 #1

### 样例输入 #1

```
5 4
1 1 2 1 1
2 1 5
1 2 4 2
2 2 4
2 1 5
```

### 样例输出 #1

```
5
7
9
```

## 提示

Initially, array $ a $ is equal to $ 1 $ , $ 1 $ , $ 2 $ , $ 1 $ , $ 1 $ .

The answer for the first query of the second type is $ f (1)+f (1)+f (2)+f (1)+f (1)=1+1+1+1+1=5 $ .

After the query 1 2 4 2 array $ a $ is equal to $ 1 $ , $ 3 $ , $ 4 $ , $ 3 $ , $ 1 $ .

The answer for the second query of the second type is $ f (3)+f (4)+f (3)=2+3+2=7 $ .

The answer for the third query of the second type is $ f (1)+f (3)+f (4)+f (3)+f (1)=1+2+3+2+1=9 $ .

## 题解
我们本题的需要维护的是我们的某一个斐波那契数列和，说起我们的斐波那契数列，我们应该考虑到一个矩阵加速斐波那契数列的方法。

我们考虑每一次我们的序列+x，然后求他的斐波那契和，就相当于我们给我们的区间上进行了 x 次矩阵乘。乘以我们的转移矩阵。

于是，我们考虑对于用我们的线段树来维护一个矩阵，我们每一次选定一个做区间和一个右区间，然后再对我们的区间进行一个乘法。(类似于我们的一个线段树维护区间乘法)

```cpp
// By YoungNeal
#include<cstdio>
#include<cctype>
#define N 100005
#define int long long
const int mod=1e9+7;

int n,m;
int val[N];

struct Matrix{
	int m[4][4];

	void clear(){
		for(int i=0;i<4;i++){
			for(int j=0;j<4;j++)
				m[i][j]=0;
		}
	}

	void init(){
		for(int i=0;i<4;i++)
			m[i][i]=1;
	}

	void print(){
		for(int i=1;i<=2;i++){
			for(int j=1;j<=2;j++)
				printf("i=%I64d,j=%I64d,m=%I64d\n",i,j,m[i][j]);
		}
	}

	bool empty(){
		if(m[1][1]!=1) return 0;
		if(m[1][2]!=0) return 0;
		if(m[2][1]!=0) return 0;
		if(m[2][2]!=1) return 0;
		return 1;
	}

	Matrix operator*(const Matrix &y) const {
		Matrix z; z.clear();
		for(int i=1;i<=2;i++){
			for(int k=1;k<=2;k++){
				for(int j=1;j<=2;j++)
					z.m[i][j]=(z.m[i][j]+m[i][k]*y.m[k][j])%mod;
			}
		}
		return z;
	}

	friend Matrix operator+(Matrix a,Matrix b){
		Matrix c;c.clear();
		for(int i=1;i<=2;i++){
			for(int j=1;j<=2;j++)
				c.m[i][j]=(a.m[i][j]+b.m[i][j])%mod;
		}
		return c;
	}

};

Matrix dw,fir;
Matrix mat[N<<2],lazy[N<<2];

int getint(){
	int x=0;char ch=getchar();
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	return x;
}

Matrix ksm(Matrix a,int b){
	Matrix ret; ret.clear(); ret.init();
	while(b){
		if(b&1) ret=ret*a;
		a=a*a;
		b>>=1;
	}
	return ret;
}

void pushup(int cur){
	mat[cur]=mat[cur<<1]+mat[cur<<1|1];
}

void build(int cur,int l,int r){
	mat[cur].clear();
	lazy[cur].clear();
	lazy[cur].init();
	if(l==r){
		mat[cur]=fir*ksm(dw,val[l]-1);
		return;
	}
	int mid=l+r>>1;
	build(cur<<1,l,mid);
	build(cur<<1|1,mid+1,r);
	pushup(cur);
}

void pushdown(int cur,int l,int r){
	if(lazy[cur].empty()) return;
	mat[cur<<1]=mat[cur<<1]*lazy[cur];
	lazy[cur<<1]=lazy[cur<<1]*lazy[cur];
	mat[cur<<1|1]=mat[cur<<1|1]*lazy[cur];
	lazy[cur<<1|1]=lazy[cur<<1|1]*lazy[cur];
	lazy[cur].clear();
	lazy[cur].init();
}

void modify(int cur,int ql,int qr,int l,int r,Matrix x){
	if(ql<=l and r<=qr){
		mat[cur]=mat[cur]*x;
		lazy[cur]=lazy[cur]*x;
		return;
	}
	pushdown(cur,l,r);
	int mid=l+r>>1;
	if(ql<=mid)
		modify(cur<<1,ql,qr,l,mid,x);
	if(mid<qr)
		modify(cur<<1|1,ql,qr,mid+1,r,x);
	pushup(cur);
}

Matrix query(int cur,int ql,int qr,int l,int r){
	if(ql<=l and r<=qr)
		return mat[cur];
	pushdown(cur,l,r);
	Matrix ret;ret.clear();
	int mid=l+r>>1;
	if(ql<=mid)
		ret=ret+query(cur<<1,ql,qr,l,mid);
	if(mid<qr)
		ret=ret+query(cur<<1|1,ql,qr,mid+1,r);
	return ret;
}

signed main(){
	dw.clear(); fir.clear();
	dw.m[1][1]=1;fir.m[1][1]=1;
	dw.m[1][2]=1;fir.m[1][2]=1;
	dw.m[2][1]=1;fir.m[2][1]=0;
	dw.m[2][2]=0;fir.m[2][2]=0;
	n=getint(),m=getint();
	for(int i=1;i<=n;i++)
		val[i]=getint();
	build(1,1,n);
	while(m--){
		if(getint()==1){
			int l=getint(),r=getint(),x=getint();
			modify(1,l,r,1,n,ksm(dw,x));
		}
		else{
			int l=getint(),r=getint();
			printf("%I64d\n",query(1,l,r,1,n).m[1][2]%mod);
		}
	}
	return 0;
}
```