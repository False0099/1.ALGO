# [AGC 005 B] Minimum Sum

## 题面翻译

给定数组 $A$，求

$$ \sum_{i = 1}^n \sum_{j = i}^n \min_{i \leq k \leq j} a_k $$

数据保证 $A$ 为 $[1, n]$ 的正整数排列。

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc005/tasks/agc005_b

すぬけ君はある日友人から長さ $ N $ の順列 $ a_1,\ a_2,\ ...,\ a_N $ を貰いました。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/AT_agc005_b/7385c80af4629f5f6d11fed58e1b38d3c006d06d.png)

を求めてください。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ N $ $ a_1 $ $ a_2 $ $ ... $ $ a_N $

## 输出格式

$ 1 $ 行に答えを出力する。

なお、32 bit 整数型に答えが収まるとは限らないことに注意すること。

## 样例 #1

### 样例输入 #1

```
3
2 1 3
```

### 样例输出 #1

```
9
```

## 样例 #2

### 样例输入 #2

```
4
1 3 2 4
```

### 样例输出 #2

```
19
```

## 样例 #3

### 样例输入 #3

```
8
5 4 8 1 2 6 7 3
```

### 样例输出 #3

```
85
```

## 提示

### 制約

- $ 1\ ≦\ N\ ≦\ 200,000 $
- $ (a_1,\ a_2,\ ...,\ a_N) $ は $ (1,\ 2,\ ...,\ N) $ を並び替えたものである

## 题解
本体是 CF 817 D 的三倍经验，
```
#include <bits/stdc++.h>
#define int long long
const int N=1e6+10;
int a[N],l[N],r[N],top,stk[N],ans;
using namespace std;
signed main(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	top=0;
	for(int i=1;i<=n;i++){
		while(top&&a[stk[top]]>=a[i]){
			top--;
		}
		if(top==0){
			l[i]=0;
		}else{
			l[i]=stk[top];
		}
		stk[++top]=i;
	}
	top=0;
	for(int i=n;i>=1;i--){
		while(top&&a[stk[top]]>a[i]){
			top--;
		}
		if(top==0){
			r[i]=n+1;
		}else{
			r[i]=stk[top];
		}
		stk[++top]=i;
	}
	for(int i=1;i<=n;i++){
		ans+=a[i]*(i-l[i])*(r[i]-i);
	}
	top=0;
	for(int i=1;i<=n;i++){
		while(top&&a[stk[top]]<=a[i]){
			top--;
		}
		if(top==0){
			l[i]=0;
		}else{
			l[i]=stk[top];
		}
		stk[++top]=i;
	}
	top=0;
	for(int i=n;i>=1;i--){
		while(top&&a[stk[top]]<a[i]){
			top--;
		}
		if(top==0){
			r[i]=n+1;
		}else{
			r[i]=stk[top];
		}
		stk[++top]=i;
	}
	for(int i=1;i<=n;i++){
		ans-=0;
	}
	cout<<abs(ans)<<endl;
}
```