# Sorting By Multiplication

## 题面翻译

现在有一个有 $n$ 个元素的数组 $A$。

你可以对数组 $A$ 执行任意次操作（可以为 $0$ 次），每一次操作，你可以选择一个 $l$ 和 $r$（$1\le l\le r\le n$），以及**任意**一个整数 $x$，对于所有满足 $l\le k\le r$ 的 $k$，$A_k$ 将乘以 $x$。

求让 $A$ 数组**严格升序**（$A_1< A_2<\dots<A_n$）的最少操作次数。

## 题目描述

You are given an array $ a $ of length $ n $ , consisting of positive integers.

You can perform the following operation on this array any number of times (possibly zero):

- Choose three integers $ l $ , $ r $ and $ x $ such that $ 1 \le l \le r \le n $ , and multiply every $ a_i $ such that $ l \le i \le r $ by $ x $ .

Note that you can choose any integer as $ x $ , it doesn't have to be positive.

You have to calculate the minimum number of operations to make the array $ a $ sorted in strictly ascending order (i. e. the condition $ a_1 < a_2 < \dots < a_n $ must be satisfied).

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

The first line of each test case contains one integer $ n $ ( $ 1 \le n \le 2 \cdot 10^5 $ ) — the length of the array $ a $ .

The second line of each test case contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ 1 \le a_i \le 10^9 $ ) — the array $ a $ .

Additional constraint on the input: the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, print one integer — the minimum number of operations required to make $ a $ sorted in strictly ascending order.

## 样例 #1

### 样例输入 #1

```
3
5
1 1 2 2 2
6
5 4 3 2 5 1
3
1 2 3
```

### 样例输出 #1

```
3
2
0
```

## 提示

In the first test case, we can perform the operations as follows:

- $ l = 2 $ , $ r = 4 $ , $ x = 3 $ ;
- $ l = 4 $ , $ r = 4 $ , $ x = 2 $ ;
- $ l = 5 $ , $ r = 5 $ , $ x = 10 $ .

 After these operations, the array $ a $ becomes $ [1, 3, 6, 12, 20] $ .In the second test case, we can perform one operation as follows:

- $ l = 1 $ , $ r = 4 $ , $ x = -2 $ ;
- $ l = 6 $ , $ r = 6 $ , $ x = 1337 $ .

 After these operations, the array $ a $ becomes $ [-10, -8, -6, -4, 5, 1337] $ .In the third test case, the array $ a $ is already sorted.
## 题解
我们本题的思路是：如果我们构造出来的是符合条件的，我们有下面的思路：如果我们的某一个部分原本就是单调递增的，我们就直接把这一段都同意算作一次。否则我们就要去再乘一次。

但是，我们这么做连我们的样例都不能通过，我们有5 4 3 2 5 1 实际只需要 2 次，而我们采用上面的算法，计算了 5 次，于是我们注意到我们的题目中说，我们可以乘一个负数，那么我们对于我们的**单调递减前缀**，我们就可以统一乘以个-1，这样我们就能递减变递增了。

于是，我们就可以先预处理出我们如果不进行任何处理，我们需要多少次乘法。就有：
```cpp
int ans=n;
for(int i=1;i<n;i++){
	if(a[i]>a[i-1]){
		ans--;
	}
}
```

之后，我们再去处理我们的单调递减前缀，这里，我们需要通过我们的贪心，我们的前缀最长能扩展多少，我们就扩展多少即可。
```cpp
bool isprefix
for(int i=1;i<n;i++){
	if(a[i]<a[i-1]&&isprefix){
		ans--;
	}
	if(isprefix&&a[i]>a[i-1]){
		ifprefix=false;
	}
}
```


```cpp
#include <bits/stdc++.h>
using namespace std;
void solve(){
	int n;
	cin>>n;
	vector<int> a(n);
	for(int i=0;i<n;i++){
		cin>>a[i];
	}
	if(n==1){
		cout<<0<<endl;
		return;
	}
	int ans=0;
	int res=0;
	vector<int> ope_1(n);
	for(int i=1;i<n;i++){
		if(a[i]<=a[i-1]){
			res++;
			ope_1[i]=1;
		}
	}
	ans=res;
	for(int i=0;i<n;i++){
		if(i==0){
			ope_1[i]=0;
		}else{
			ope_1[i]=ope_1[i-1]+ope_1[i];
		}
	}
	int left_ope=1; 
	for(int i=1;i<n-1;i++){
		if(a[i]>=a[i-1]){
			left_ope++;
		}
		res=left_ope+ope_1[n-1]-ope_1[i+1];
		ans=min(ans,res);
	}
	cout<<ans<<endl;
}
int main(){
	int t;
	cin>>t;
	while(t--){
		solve();
	}
}
```