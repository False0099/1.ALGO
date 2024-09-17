# Multiplicity

## 题面翻译

从序列 $\{a_1,\ a_2,\ ..\ ,\ a_n\}$ 中选出**非空**子序列 $\{b_1,\ b_2,\ ..\ ,\ b_k\}$，一个子序列合法需要满足 $\forall\ i \in [1,\ k],\ i\ |\ b_i$。求有多少互不相等的合法子序列，答案对 $10^9 + 7$ 取模。

序列 $\{1,\ 1\}$ 有 $2$ 种选法得到子序列 $\{1\}$，但 $1$ 的来源不同，认为这两个子序列不相等。

## 题目描述

You are given an integer array $ a_1, a_2, \ldots, a_n $ .

The array $ b $ is called to be a subsequence of $ a $ if it is possible to remove some elements from $ a $ to get $ b $ .

Array $ b_1, b_2, \ldots, b_k $ is called to be good if it is not empty and for every $ i $ ( $ 1 \le i \le k $ ) $ b_i $ is divisible by $ i $ .

Find the number of good subsequences in $ a $ modulo $ 10^9 + 7 $ .

Two subsequences are considered different if index sets of numbers included in them are different. That is, the values ​of the elements ​do not matter in the comparison of subsequences. In particular, the array $ a $ has exactly $ 2^n - 1 $ different subsequences (excluding an empty subsequence).

## 输入格式

The first line contains an integer $ n $ ( $ 1 \le n \le 100\, 000 $ ) — the length of the array $ a $ .

The next line contains integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le 10^6 $ ).

## 输出格式

Print exactly one integer — the number of good subsequences taken modulo $ 10^9 + 7 $ .

## 样例 #1

### 样例输入 #1

```
2
1 2
```

### 样例输出 #1

```
3
```

## 样例 #2

### 样例输入 #2

```
5
2 2 1 22 14
```

### 样例输出 #2

```
13
```

## 提示

In the first example, all three non-empty possible subsequences are good: $ \{1\} $ , $ \{1, 2\} $ , $ \{2\} $

In the second example, the possible good subsequences are: $ \{2\} $ , $ \{2, 2\} $ , $ \{2, 22\} $ , $ \{2, 14\} $ , $ \{2\} $ , $ \{2, 22\} $ , $ \{2, 14\} $ , $ \{1\} $ , $ \{1, 22\} $ , $ \{1, 14\} $ , $ \{22\} $ , $ \{22, 14\} $ , $ \{14\} $ .

Note, that some subsequences are listed more than once, since they occur in the original array multiple times.

## 题解
本题我们看到**求我们的合法子序列的个数**，我们**首先应该思考能不能用 dp 来解决**。我们发现，我们可以设 $dp[i][j]$ 表示我们把第 $i$ 位对应我们序列的第 $j$ 的方案数，我们就可以有：
1. 如果我们 $a[i]\%j==0$，那么我们就有 $dp[i][j]=dp[i-1][j-1]+dp[i][j]$
2. 如果我们没有上面的条件，那么我们就有：
$dp[i][j]=dp[i-1][j]$

注意到，我们可以通过我们的滚动数组来减去我们的第一位。并且我们的暴力情况下，上面的时间复杂度是 $o(nk)$ 的，其中 $k$ 表示我们的值域。

之后，我们注意到，我们上面的 $a[i]\%j$ 可以转换为我们的下面的条件：如果我们的 $a[i]$ 模 $j$ 位 0，也就是说，**j 是 $a[i]$ 的因数**。于是，我们就可以对于每一个数，美剧他的质因子，然后只更新对应的质因子即可，最后的复杂度是 $o(n\sqrt{n })$ 的。

```
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+10;
int f[N];
const int mod=1e9+7;
signed main(){
	ios::sync_with_stdio(false),cin.tie(0);
	int n;
	cin>>n;
	vector<int> a(n);
	int maxx=0;
	for(int i=0;i<n;i++){
		cin>>a[i];
		maxx=max(maxx,a[i]);
	}
	f[0]=1;
	int cnt=0;
	for(int i=0;i<n;i++){
		int u=a[i];
		vector<int> t;
		for(int j=1;j*j<=u;j++){
			if(a[i]%j==0){
				if(j!=a[i]/j){
					t.push_back(j);
					t.push_back(a[i]/j);
				}else{
					t.push_back(j);
				}
			}
		}
		sort(t.begin(),t.end());
		reverse(t.begin(),t.end());
		for(auto u:t){
			f[u]=(f[u-1]+f[u])%mod; 
		}
	}
	int ans=0;
	for(int i=1;i<=n;i++){
		ans=(ans+f[i])%mod;
	}
	cout<<ans<<endl; 
}
```