# Modulo Sum

## 题面翻译

# 题面描述

给出 $1$ 个长度为 $n$ 的序列，以及 $1$ 个正整数 $m$。问这个原序列中是否存在非空子序列，使其元素之和能被 $m$ 整除。

# 输入格式

第 $1$ 行，有 $2$ 个正整数，分别为原序列的长度 $n$ 和除数 $m$。
（数据范围：$1 \leqslant n \leqslant 10^{6}$，$2 \leqslant m \leqslant 10^{3}$）
第 $2$ 行，有 $n$ 个自然数，表示该原序列的元素 $a_i$。
（数据范围：$0 \leqslant a_i \leqslant 10^{9}$）

# 输出格式

仅 $1$ 行，如果存在符合条件的子序列，输出 **YES**，否则输出 **NO**。

# 样例解释

- 第 $1$ 组样例的解释：
存在符合条件的子序列 $\{2,3\}$，其元素之和为 $2 + 3 = 5$，$5$ 可以被 $5$ 整除。
- 第 $2$ 组样例的解释：
由于原序列中只有 $1$ 个元素，因此它只有 $1$ 个子序列 $\{5\}$，但显然 $5$ 不可以被 $6$ 整除。
- 第 $3$ 组样例的解释：
存在符合条件的子序列 $\{3,3\}$，其元素之和为 $3 + 3 = 6$，$6$ 可以被 $6$ 整除。
- 第 $4$ 组样例的解释：
选择整个原序列作为子序列，其元素之和为 $5 + 5 + 5 + 5 + 5 + 5 = 30$，$30$ 可以被 $6$ 整除。

Translated by Sooke

## 题目描述

You are given a sequence of numbers $ a_{1}, a_{2},..., a_{n} $ , and a number $ m $ .

Check if it is possible to choose a non-empty subsequence $ a_{ij} $ such that the sum of numbers in this subsequence is divisible by $ m $ .

## 输入格式

The first line contains two numbers, $ n $ and $ m $ ( $ 1<=n<=10^{6} $ , $ 2<=m<=10^{3} $ ) — the size of the original sequence and the number such that sum should be divisible by it.

The second line contains $ n $ integers $ a_{1}, a_{2},..., a_{n} $ ( $ 0<=a_{i}<=10^{9} $ ).

## 输出格式

In the single line print either "YES" (without the quotes) if there exists the sought subsequence, or "NO" (without the quotes), if such subsequence doesn't exist.

## 样例 #1

### 样例输入 #1

```
3 5
1 2 3
```

### 样例输出 #1

```
YES
```

## 样例 #2

### 样例输入 #2

```
1 6
5
```

### 样例输出 #2

```
NO
```

## 样例 #3

### 样例输入 #3

```
4 6
3 1 1 3
```

### 样例输出 #3

```
YES
```

## 样例 #4

### 样例输入 #4

```
6 6
5 5 5 5 5 5
```

### 样例输出 #4

```
YES
```

## 提示

In the first sample test you can choose numbers $ 2 $ and $ 3 $ , the sum of which is divisible by $ 5 $ .

In the second sample test the single non-empty subsequence of numbers is a single number $ 5 $ . Number $ 5 $ is not divisible by $ 6 $ , that is, the sought subsequence doesn't exist.

In the third sample test you need to choose two numbers $ 3 $ on the ends.

In the fourth sample test you can take the whole subsequence.

## 题解
我们本题首先，假设我们的 $n\in(0,1000)$,那么我们本题就可以通过我们的简单的 0-1 背包判断是否可行来计算，但是我们这里，因为我们的 $n\in(0,1000000)$,我们继续用 0-1 背包就会超时。

我们考虑到我们的鸽巢原理，如果我们的 $n>m$,那么我们一定可以构造出一个序列，满足我们的题目的要求，原理在于，我们的 $m*x\%x=0$,于是，我们只需要考虑我们的 $n<m$ 的情况，这种情况下，我们的完全可以通过我们的 0-1 背包来计算。

```cpp
// LUOGU_RID: 150942948
#include <bits/stdc++.h>
using namespace std;
const int N=4010;
int a[N];
int f[N][N];
int main(){
	int n,m;
	cin>>n>>m;
	if(n>m){
		cout<<"YES"<<endl;
		exit(0);
	}
	//vector<int> a(n+1,0);
	for(int i=1;i<=n;i++){
		cin>>a[i];
		a[i]=a[i]%m;
		f[i][(a[i])%m]=1;
	}
	f[0][0]=true;
	for(int i=1;i<=n;i++){
		for(int j=0;j<m;j++){
			if(i==1&&j==0){
				//f[i][j]|=f[i-1][j];
				f[i][(j+a[i])%m]|=f[i-1][j];
			}else{
				f[i][j]|=f[i-1][j];
				f[i][(j+a[i])%m]|=f[i-1][j];
			}
			//f[i][(j+a[i])%m]|=f[i-1][j];
		}
	}
//	for(int i=1;i<=n;i++){
//		for(int j=0;j<m;j++){
//			cout<<f[i][j]<<" ";
//		}
//		puts("");
//	}
	for(int i=1;i<=n;i++){
		if(f[i][0]==1){
			cout<<"YES"<<endl;
			exit(0);
		}
	}
	cout<<"NO"<<endl;
}
```