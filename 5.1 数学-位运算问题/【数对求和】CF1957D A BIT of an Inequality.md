# A BIT of an Inequality

## 题目描述

You are given an array $ a_1, a_2, \ldots, a_n $ . Find the number of tuples ( $ x, y, z $ ) such that:

- $1 \leq x \leq y \leq z \leq n$ , and
- $f (x, y) \oplus f (y, z) > f (x, z)$ .

We define $f (l, r) = a_l \oplus a_{l + 1} \oplus \ldots \oplus a_{r}$ , where $\oplus$ denotes the [bitwise XOR operation](https://en.wikipedia.org/wiki/Bitwise_operation#XOR).

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \leq t \leq 10^4 $ ) — the number of test cases.

The first line of each test case contains a single integer $ n $ ( $ 1 \leq n \leq 10^5 $ ).

The second line of each test case contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \leq a_i \leq 10^9 $ ).

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 10^5 $ .

## 输出格式

For each test case, output a single integer on a new line — the number of described tuples.

## 样例 #1

### 样例输入 #1

```
3
3
6 2 4
1
3
5
7 3 7 2 1
```

### 样例输出 #1

```
4
0
16
```

## 提示

In the first case, there are 4 such tuples in the array $ [6, 2, 4] $ :

- ( $ 1 $ , $ 2 $ , $ 2 $ ): $ (a_1 \oplus a_2) \oplus (a_2) = 4 \oplus 2 > (a_1 \oplus a_2) = 4 $
- ( $ 1 $ , $ 1 $ , $ 3 $ ): $ (a_1) \oplus (a_1 \oplus a_2 \oplus a_3) = 6 \oplus 0 > (a_1 \oplus a_2 \oplus a_3) = 0 $
- ( $ 1 $ , $ 2 $ , $ 3 $ ): $ (a_1 \oplus a_2) \oplus (a_2 \oplus a_3) = 4 \oplus 6 > (a_1 \oplus a_2 \oplus a_3) = 0 $
- ( $ 1 $ , $ 3 $ , $ 3 $ ): $ (a_1 \oplus a_2 \oplus a_3) \oplus (a_3) = 0 \oplus 4 > (a_1 \oplus a_2 \oplus a_3) = 0 $

In the second test case, there are no such tuples.

## 题解
首先，我们这一题按照我们的一般的数对求和的思路，我们写出我们的表达式：
$$
\sum_{i=0}^n\sum_{j=1}^n\sum_{k=1}^n[f(x,y)\oplus f(y,z)>f(x,z)]
$$

之后，我们考虑化简我们的上面的表达式，具体来讲可以从下面的几个方面来化简：
1. 化简我们的内部的限制函数
2. 把我们外部的无关循环变量删除：
3. 交换我们的顺序
我们这里只需要做我们的第一步，我们就有：
$$
\sum_{i=0}^n\sum_{j=1}^n\sum_{k=1}^n[pre(x-1)\oplus pref(y)\oplus pref(y-1)\oplus pref(z)>pref(x-1)\oplus pref(z)]
$$
再进一步，我们就有：
$$
pref(x-1)\oplus pref(z-1)\oplus a[y]>pref(x-1)\oplus pref(z-1)
$$

那么这种情况下，枚举我们的 $x,z$ 显然不现实，甚至会导致我们进入枚举我们的 $o(n^3)$ 的情况。

我们的理想的方法当然是枚举我们的 $y$,这个时候，我们如果想要我们的答案满足我们的要求。

我们不妨记我们当前的 $a[y]$ 的值为 $x$，我们注意到，对这个 $x$ 进行**二进制拆分**后，我们的第一个为 0 的位置对于我们的异或是没有任何影响的，只有我们的为 1 的位置对于我们的异或才有影响，因此，我们就可以通过枚举我们的第一个 1。

**我们考虑为 1 时，哪些异或和能够让我们的结果变化**。注意到，我们如果 $pref(x-1)\oplus pref(z)$ 在这一位上的答案为 0，那么这一对 $(x,y)$ 就一定能够对我们的答案做出贡献。

因而，我们只需要统计我们的所有在这一位上的前缀 1 的个数和后缀 1 的个数，前缀 0 的个数，后缀 0 的个数，相乘相加即可得到我们的 $y$ 作为中间数字时的贡献。

最后累加即可。

```
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e5+10;
int a[N][32];
int bb[N][32];
int b[N];
int pref[N][32];
int suf[N][32];
void solve(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>b[i];
		for(int j=0;j<32;j++){
			bb[i][j]=(b[i]>>j)&1;
			if(i==1){
				pref[0][j]=0;
				suf[n+1][j]=0;
			}
		}
		b[i]^=b[i-1];
	}
	
	for(int i=1;i<=n;i++){
		int u;
		u=b[i];
		for(int j=0;j<32;j++){
			a[i][j]=(u>>j)&1;
			pref[i][j]=pref[i-1][j]+a[i][j];//前缀1 
		}
	}
	
	for(int i=n;i>=1;i--){
		for(int j=0;j<32;j++){
			suf[i][j]=suf[i+1][j]+a[i][j];//后缀1 
		}
	}
	
	int ans=0; 
	for(int i=1;i<=n;i++){
		int pos=-1;
		for(int j=31;j>=0;j--){
			if(bb[i][j]==1){
				pos=j;
				break;
			}
		}
		if(pos==-1){
			continue;
		}
		ans+=pref[i-1][pos]*suf[i][pos]+(i-pref[i-1][pos])*((n-i+1)-suf[i][pos]);
	}
	cout<<ans<<'\n';
}
signed main(){
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	int t;
	cin>>t;
	while(t--){
		solve();
	}
}
```