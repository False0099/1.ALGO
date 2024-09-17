# [COCI 2010-2011 #3 ] DIFERENCIJA

## 题目描述

给出一个长度为 $n$ 的序列 $a_i$，求出下列式子的值：

$$\sum_{i=1}^{n} \sum_{j=i}^{n} (\max_{i\le k\le j} a_k-\min_{i\le k\le j} a_k)$$



即定义一个子序列的权值为序列内最大值与最小值的差。求出所有连续子序列的权值和。

## 输入格式

输入第一行一个整数 $n$，表示序列的长度。

接下来的 $n$ 行，每行一个整数 $a_i$，描述这个序列。

## 输出格式

输出一行一个整数，表示式子的答案。

## 样例 #1

### 样例输入 #1

```
3
1
2
3
```

### 样例输出 #1

```
4
```

## 样例 #2

### 样例输入 #2

```
4
7
5
7
5
```

### 样例输出 #2

```
12
```

## 样例 #3

### 样例输入 #3

```
4
3
1
7
2
```

### 样例输出 #3

```
31
```

## 提示

#### 数据规模与约定

对于 $100\%$ 的数据，保证 $2\le n\le 3\times 10^5$，$1\le a_i\le 10^8$。

#### 说明

**题目译自 [COCI2010-2011](https://hsin.hr/coci/archive/2010_2011/) [CONTEST #3](https://hsin.hr/coci/archive/2010_2011/contest3_tasks.pdf) *T 5 DIFERENCIJA***。

## 题解
CF 817 D 的双倍经验之一，不再赘述
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