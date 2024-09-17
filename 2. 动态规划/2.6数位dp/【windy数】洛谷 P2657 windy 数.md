# [SCOI 2009] windy 数

## 题目背景

Windy 定义了一种 windy 数。

## 题目描述

不含前导零且相邻两个数字之差至少为 $2$ 的正整数被称为 windy 数。Windy 想知道，在 $a$ 和 $b$ 之间，包括 $a$ 和 $b$ ，总共有多少个 windy 数？

## 输入格式

输入只有一行两个整数，分别表示 $a$ 和 $b$。

## 输出格式

输出一行一个整数表示答案。

## 样例 #1

### 样例输入 #1

```
1 10
```

### 样例输出 #1

```
9
```

## 样例 #2

### 样例输入 #2

```
25 50
```

### 样例输出 #2

```
20
```

## 提示

#### 数据规模与约定

对于全部的测试点，保证 $1 \leq a \leq b \leq 2 \times 10^9$。

### 题解
典型的数位 dp 问题，只需要套一个模板即可

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int n;
int c[N];
void solve(int a){
	int len=0;
	while(a){
		c[++len]=a%10;
		a/=10;
	}
}
long long dp[N][N];
void dfs(int level,int last,bool lead,bool limit){
	if(level==n){
		return 0;
	}
	long long ans=0;
	if(!lead&&!limit&&dp[level][last]!=-1){
		return dp[level][last];
	}
	int up=(limit?c[level]:9);
	for(int i=0;i<=9;i++){
		if(lead&&i==0){
			ans+=dfs(level-1,-2,true,limit&&i==up);
		}
		if(abs(i-last)<2) continue;
		else{
			ans+=dfs(level-1,i,false,limit&&i==up);
		}
	}
	if(!limit&&!lead){
		dp[pos][last]=ans;
	}
	return ans;
}
int main(){
	int a,b;
	cin>>a>>b;
} 
```