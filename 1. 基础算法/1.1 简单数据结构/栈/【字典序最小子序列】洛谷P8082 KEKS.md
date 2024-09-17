# [COCI 2011-2012 #4 ] KEKS

## 题目描述

给定正整数 $N,K$ 和一个 $N$ 位数，求在 $N$ 位数中删除 $K$ 位后剩下的数的最大值。

## 输入格式

第一行，两个整数 $N,K$。

第二行，一个 $N$ 位整数。保证没有前导 $0$。

## 输出格式

输出剩下的数的最大值。

## 样例 #1

### 样例输入 #1

```
4 2
1924
```

### 样例输出 #1

```
94
```

## 样例 #2

### 样例输入 #2

```
7 3
1231234
```

### 样例输出 #2

```
3234
```

## 样例 #3

### 样例输入 #3

```
10 4
4177252841
```

### 样例输出 #3

```
775841
```

## 提示

**【数据规模与约定】**

- 对于 $50\%$ 的数据，$N \le 1000$。
- 对于 $100\%$ 的数据，$1 \le K \lt N \le 5 \times 10^5$。

**【提示与说明】**

**题目译自 [COCI 2011-2012](https://hsin.hr/coci/archive/2011_2012/) [CONTEST #4](https://hsin.hr/coci/archive/2011_2012/contest4_tasks.pdf) _Task 3 KEKS_。**

**本题分值按 COCI 原题设置，满分 $100$。**


## 题解
我们本题不难发现，我们要求删除 K 个元素之后的数字最大，也就是要求我们删除了 K 个元素之后，我们的答案是最大的。那么我们的思路就很简单了，我们用一个单调栈存储我们每一个左端点对应的右侧有没有比他还要大的，并且根据我们是否 pop 来计算我们的次数，如果超过或者等于我们的 K，我们就直接 break，答案也就很显然了。

```
#include <bits/stdc++.h>
using namespace std;
int main(){
	int n,k;
	cin>>n>>k;
	string s;
	cin>>s;
	stack<int> stk;
	for(int i=0;s[i];i++){
		while(stk.size()&&k&&s[stk.top()]-'0'<s[i]-'0'){
			k--;
			stk.pop();
		}
		stk.push(i);
	}
	while(k){
		stk.pop();
		k--;
	}
	stack<int> ans;
	while(stk.size()){
		ans.push(stk.top());
		stk.pop();
	}
	while(ans.size()){
		cout<<s[ans.top()];
		ans.pop();
	}
}
```