# Yet Another Minimization Problem

## 题面翻译

定义某数组 $x$ 的权值为

$$\sum\limits_{i=1}^n\sum\limits_{j=i+1}^n(x_i+x_j)^2$$

现在，给定两个长度为 $n$ 的数组 $a,b$。你可以执行若干次操作，每次操作选择一个下标 $i$，并交换 $a_i,b_i$。求在进行操作之后两个数组的权值之和最小能够达到多少。

数据范围：

- $t$ 组数据，$1\leqslant t\leqslant 40$。
- $1\leqslant n,\sum n\leqslant 100$。
- $1\leqslant a_i,b_i\leqslant 100$。

Translated by Eason_AC

## 题目描述

You are given two arrays $ a $ and $ b $ , both of length $ n $ .

You can perform the following operation any number of times (possibly zero): select an index $ i $ ( $ 1 \leq i \leq n $ ) and swap $ a_i $ and $ b_i $ .

Let's define the cost of the array $ a $ as $ \sum_{i=1}^{n} \sum_{j=i + 1}^{n} (a_i + a_j)^2 $ . Similarly, the cost of the array $ b $ is $ \sum_{i=1}^{n} \sum_{j=i + 1}^{n} (b_i + b_j)^2 $ .

Your task is to minimize the total cost of two arrays.

## 输入格式

Each test case consists of several test cases. The first line contains a single integer $ t $ ( $ 1 \leq t \leq 40 $ ) — the number of test cases. The following is a description of the input data sets.

The first line of each test case contains an integer $ n $ ( $ 1 \leq n \leq 100 $ ) — the length of both arrays.

The second line of each test case contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \leq a_i \leq 100 $ ) — elements of the first array.

The third line of each test case contains $ n $ integers $ b_1, b_2, \ldots, b_n $ ( $ 1 \leq b_i \leq 100 $ ) — elements of the second array.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 100 $ .

## 输出格式

For each test case, print the minimum possible total cost.

## 样例 #1

### 样例输入 #1

```
3
1
3
6
4
3 6 6 6
2 7 4 1
4
6 7 2 4
2 5 3 5
```

### 样例输出 #1

```
0
987
914
```

## 提示

In the second test case, in one of the optimal answers after all operations $ a = [2, 6, 4, 6] $ , $ b = [3, 7, 6, 1] $ .

The cost of the array $ a $ equals to $ (2 + 6)^2 + (2 + 4)^2 + (2 + 6)^2 + (6 + 4)^2 + (6 + 6)^2 + (4 + 6)^2 = 508 $ .

The cost of the array $ b $ equals to $ (3 + 7)^2 + (3 + 6)^2 + (3 + 1)^2 + (7 + 6)^2 + (7 + 1)^2 + (6 + 1)^2 = 479 $ .

The total cost of two arrays equals to $ 508 + 479 = 987 $ .

## 题解
我们本题很显然给出了一个式子，我们不妨来推一下我们的式子：
$\sum_{i=1}^{n}\sum_{j=i+1}^{n}(a_{i}+a_{j})^2+\sum_{i=1}^{n}\sum_{j=i+1}^{n}(b_{i}+b_{j})^2$。之后，我们展开我们的上述式子：
$\sum_{i=1}^n\sum_{j=i+1}^{n}(a_{i}^2+2a_{i}a_{j}+a_{j}^2)+b_{i}^2+2b_{i}b_{j}+b_{j}^2$。我们提取我们的公因式：
$\sum_{i=1}^n(n-i)(a_{i}^2+b_{i}^2)\sum_{j=i+1}^{n}(2a_{i}a_{j}+a_{j}^2)+2b_{i}b_{j}+b_{j}^2$
在进行一次提取：
$(n-1)\sum_{i=1}^na_{i}^2+b_{i}^2+\sum_{i=1}^n\sum_{j=i+1}^{n}a_{i}a_{j}+b_{i}b_{j}$

之后，因为我们的和一定，所以我们的前半部分是定制，我们只需要考虑最小化我们的：$\sum_{i=1}^n\sum_{j=i+1}^{n}a_{j}a_{i}+b_{i}b_{j}$ ，在 $\sum a+b$ 已知的条件下。而对于上面的式子，我们又可以转换为：$\sum_{i=1}^na_{i}*prea[i+1]+b_{i}*preb[i+1]$,又因为我们的值域一定，所以我们可以考虑暴力把我们的后缀和权值设置为我们的状态，然后每一次转移就有：
$f[i][suf]=max(f[i+1][suf-a[i]]+calc(a[i],suf-a[i]),f[i+1][suf-b[i]]+calc(b[i],suf-b[i])$

其中我们的 $calc$ 函数就是我们前面的：$a_{i}*prea[i+1]+b_{i}*preb[i+1]$。
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=110;
int dp[N][N*N];
int calc(int a,int b,int suf,int sum){
	return a*suf+b*(sum-suf);
}
void solve(){
	int n;
	cin>>n;
	vector<int> a(n+1);
	vector<int> b(n+1);
	vector<int> sum(n+2,0);
	int const_number=0;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		const_number+=(n-1)*a[i]*a[i];
	}
	for(int i=1;i<=n;i++){
		cin>>b[i];
		const_number+=(n-1)*b[i]*b[i];
	}
	for(int i=n;i>=1;i--){
		sum[i]=sum[i+1]+a[i]+b[i];
	}
	memset(dp,0x3f3f3f3f3f,sizeof dp);
	for(int i=n;i>=1;i--){
		if(i==n){
			dp[i][a[i]]=0;
			dp[i][b[i]]=0;
		}
		for(int j=0;j<N*N;j++){
			if(j-a[i]>=0){
				dp[i][j]=min(dp[i][j],dp[i+1][j-a[i]]+calc(a[i],b[i],j-a[i],sum[i+1]));
			}
			if(j-b[i]>=0){
				dp[i][j]=min(dp[i][j],dp[i+1][j-b[i]]+calc(b[i],a[i],j-b[i],sum[i+1]));
			}
		}
	}
//	for(int i=n;i>=0;i--){
//		for(int j=0;j<=1000;j++){
//			cout<<"i="<<i<<"j="<<j<<"ans="<<dp[i][j]<<endl;
//		}
//		puts("");
//	}
	int ans=0x3f3f3f3f3f;
	for(int m=0;m<N*N;m++){
		ans=min(ans,dp[1][m]);
	}
//	cout<<const_number<<endl;
	
	cout<<2*ans+const_number<<endl;
	
}
signed main(){
	int t;
	cin>>t;
	while(t--){
		solve();
	}
} 
```
