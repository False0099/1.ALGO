# Range Update Point Query

## 题面翻译

## 题意描述

给定一个数列 $ a_1, a_2, \cdots, a_n $，你需要对这个序列进行如下的两种操作：

- $ 1 $ $ l $ $ r $ — 对于任意的 $ l \le i \le r$，将 $ a_i $ 修改为 $ a_i $ 的数位之和。
- $ 2 $ $ x $ — 输出 $ a_x $ .

## 输入格式

第一行包括一个整数 $ t $ ($ 1 \le t \le 1000 $) ，为测试数据的组数。

每组测试数据的第一行包括两个整数 $ n $，$ q $ ($ 1 \le n, q \le 2 \times 10 ^ 5 $)，其中 $ n $ 是数列的长度，$ q $ 是询问的个数。

每组测试数据的第二行包括 $ n $ 整数，为 $ a_1, a_2, \cdots, a_n $ ($ 1 \le a_i \le 10 ^ 9 $) 。

接下来的 $ q $ 行包括以下两种形式的操作：

- $ 1 $ $ l $ $ r $ ( $ 1 \leq l \leq r \leq n $ ) — 对于任意的 $ l \le i \le r$，将 $ a_i $ 修改为 $ a_i $ 的数位之和。
- $ 2 $ $ x $ ( $ 1 \leq x \leq n $ ) — 输出 $ a_x $。

每组测试数据包含至少一个操作二。

所有测试数据的 $n$ 的总和不会超过 $2 \times 10 ^ 5$。

所有测试数据的 $q$ 的总和不会超过 $2 \times 10 ^ 5$。

## 输出格式

对于每一组测试数据，按照输入给出的顺序输出操作二的答案。

## 提示

第一组测试数据的操作过程如下：

- 开始时，$ a = [1, 420, 69, 1434, 2023] $。
- 对 $ l=2 $，$ r=3 $ 执行操作, 完成后 $ a $ 变为 $ [1, \textcolor{red}{6}, \textcolor{red}{15}, 1434, 2023] $。
- 询问 $ x=2 $ , $ x=3 $ 以及 $ x=4 $，输出 $ 6 $，$ 15 $ 以及 $ 1434 $。
- 对 $ l=2 $ , $ r=5 $ 执行操作，完成后 $ a $ 变为 $ [1, \textcolor{red}{6}, \textcolor{red}{6}, \textcolor{red}{12}, \textcolor{red}{7}] $。
- 询问 $ x=1 $，$ x=3 $ 以及 $ x=5 $，输出 $ 1 $，$ 6 $ 以及 $ 7 $。

## 题目描述

Given an array $ a_1, a_2, \dots, a_n $ , you need to handle a total of $ q $ updates and queries of two types:

- $ 1 $ $ l $ $ r $ — for each index $ i $ with $ l \leq i \leq r $ , update the value of $ a_i $ to the sum of the digits of $ a_i $ .
- $ 2 $ $ x $ — output $ a_x $ .

## 输入格式

The first line of the input contains an integer $ t $ ( $ 1 \leq t \leq 1000 $ ) — the number of testcases.

The first line of each test case contains two integers $ n $ and $ q $ ( $ 1 \le n, q \le 2 \cdot 10^5 $ ) — the size of the array and the number of queries, respectively.

The second line of each test case contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ 1 \le a_i \le 10^9 $ ).

The next $ q $ lines of each test case are of two forms:

- $ 1 $ $ l $ $ r $ ( $ 1 \leq l \leq r \leq n $ ) — it means, for each index $ i $ with $ l \leq i \leq r $ , you should update the value of $ a_i $ to the sum of its digits.
- $ 2 $ $ x $ ( $ 1 \leq x \leq n $ ) — it means you should output $ a_x $ .

There is at least one query of the second type.

The sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

The sum of $ q $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output the answers of queries of the second type, in the order they are given.

## 样例 #1

### 样例输入 #1

```
3
5 8
1 420 69 1434 2023
1 2 3
2 2
2 3
2 4
1 2 5
2 1
2 3
2 5
2 3
9999 1000
1 1 2
2 1
2 2
1 1
1
2 1
```

### 样例输出 #1

```
6
15
1434
1
6
7
36
1
1
```

## 提示

In the first test case, the following process occurs:

- Initially, $ a = [1, 420, 69, 1434, 2023] $ .
- The operation is performed for $ l=2 $ , $ r=3 $ , yielding $ [1, \textcolor{red}{6}, \textcolor{red}{15}, 1434, 2023] $ .
- We are queried for $ x=2 $ , $ x=3 $ , and $ x=4 $ , and output $ 6 $ , $ 15 $ , and $ 1434 $ .
- The operation is performed for $ l=2 $ , $ r=5 $ , yielding $ [1, \textcolor{red}{6}, \textcolor{red}{6}, \textcolor{red}{12}, \textcolor{red}{7}] $ .
- We are queried for $ x=1 $ , $ x=3 $ , and $ x=5 $ , and output $ 1 $ , $ 6 $ , and $ 7 $ .

## 题解
我们这一题有点想我们的**开根号**那一题的线段树，对于每一个区间修改，我们看这个数是否已经是不超过 10 的了，如果是，那么我们这次就相当于没修改，否则，我们直接暴力修改。
查询也就是维护一下的问题，总的时间复杂度应该还是可以的（吧？）

```cpp
#include<algorithm>
#include<iostream>
using namespace std;
struct Segment{int l,r,w;bool d;}s[800001];
int T,n,q;
void build(int u,int l,int r){
	s[u].l=l,s[u].r=r,s[u].w=0;
	if(l==r){cin>>s[u].w,s[u].d=s[u].w<10;return;}
	build(u*2,l,(l+r)/2);build(u*2+1,(l+r)/2+1,r);
	s[u].d=s[u*2].d&&s[u*2+1].d;
}
void change(int u){
	int now=0;
	while(s[u].w) now+=s[u].w%10,s[u].w/=10;
	s[u].w=now,s[u].d=s[u].w<10;
}
void update(int u,int l,int r){
	if(s[u].l>r||s[u].r<l||s[u].d) return;
	if(s[u].l==s[u].r) change(u);
	else{
		update(u*2,l,r),update(u*2+1,l,r);
		s[u].d=s[u*2].d&&s[u*2+1].d;
	}
}
int query(int u,int p){
	if(s[u].l>p||s[u].r<p) return 0;
	if(s[u].l==s[u].r) return s[u].w;
	return max(query(u*2,p),query(u*2+1,p));
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	for(cin>>T;T;T--){
		cin>>n>>q,build(1,1,n);
		while(q--){
			static int l,r,opt;
			cin>>opt;
			if(opt==1) cin>>l>>r,update(1,l,r);
			else cin>>l,cout<<query(1,l)<<'\n';
		}
	}
	return 0;
}
```