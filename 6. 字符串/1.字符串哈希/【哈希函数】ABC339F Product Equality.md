# [ABC 339 F] Product Equality

## 题面翻译

给定长度为 $n$ 的数组 $a$，求满足如下条件的**有序**三元组 $(i,j,k)$ 的数量。
- $1 \le i,j,k \le n$
- $a_i \times a_j = a_k$

数据范围：$1 \le n \le 1000$，$\color{red}1 \le a_i < 10^{1000}$。

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc339/tasks/abc339_f

$ N $ 個の整数 $ A_1, A_2,\dots, A_N $ が与えられます。  
 以下の条件を満たす整数の組 $ (i, j, k) $ の個数を求めてください。

- $ 1\ \le\ i, j, k\ \le\ N $
- $ A_i\ \times\ A_j\ =\ A_k $

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ N $ $ A_1 $ $ A_2 $ $ \vdots $ $ A_N $

## 输出格式

答えを整数として出力せよ。

## 样例 #1

### 样例输入 #1

```
5
2
3
6
12
24
```

### 样例输出 #1

```
6
```

## 样例 #2

### 样例输入 #2

```
11
1
2
3
4
5
6
123456789123456789
123456789123456789
987654321987654321
987654321987654321
121932631356500531347203169112635269
```

### 样例输出 #2

```
40
```

## 样例 #3

### 样例输入 #3

```
9
4
4
4
2
2
2
1
1
1
```

### 样例输出 #3

```
162
```

## 提示

### 制約

- $ 1\ \le\ N\ \le\ 1000 $
- $ \color{red}{1\ \le\ A_i\ <\ 10^{1000}} $
 
### Sample Explanation 1

問題文中の条件を満たす $ (i, j, k) $ の組は以下の $ 6 $ 通りです。 - $ (1,2,3) $ - $ (1,3,4) $ - $ (1,4,5) $ - $ (2,1,3) $ - $ (3,1,4) $ - $ (4,1,5) $

### Sample Explanation 2

各整数 $ A_i $ の値が非常に大きくなりうることに注意してください。

### Sample Explanation 3

$ A_i $ の値に重複がありうることに注意してください。

## 题解
我们本题的思路是：如果我们两个数乘积相等-》我们两个数取模后乘积相等。但是这一个条件只是我们的一个充要条件，于是，为了增加我们的准确性，我们可以采用双哈希的方法，一个是采用模数 114514191981000001，另一个采用我们的自然溢出，得到的结果就作为我们的判断依据。

```
//Author: gsczl71
//Copyright (c) 2024 gsczl71 All rights reserved.

#include<bits/stdc++.h>
#define ll long long
#define i128 __int128
#define ull unsigned long long
#define pii pair<int,int>
#define pll pair<long long, long long>
#define fs first
#define sc second
#define endl '\n'
#define debug puts("AK IOI")
#define re register
#define pb push_back
#define mem(a,x) memset((a),(x),sizeof(a))
#define vi vector<int>
using namespace std;
// #define int unsigned long long
// const int mod = 1e9+7;
//const int mod = 998244353;
const int inf = 0x3f3f3f3f,N = 1005,M = 2e5+5;
const ll linf = 0x3f3f3f3f3f3f3f3f;
long long mod = 11451419198101111;
int n;
ll a[N];
unordered_map<ll,int> mp;
void solve(){
	cin>>n;
	for(int i = 1;i <= n;i++){
		string x;cin >> x;
		for(int j = 0;x[j];j++){
			a[i] = ((__int128)a[i]*10 + (x[j])-'0')%mod;
		}mp[a[i]]++;
	}
	ll ans=0;
	for(int i = 1;i <= n;i++){
		for(int j = 1;j <= n;j++){
			ans += mp[(__int128)a[i] * a[j]%mod];
		}
	}
	cout<<ans;
}
signed main(){
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	int T=1;
//	cin >> T;
	while(T--) solve();
	return 0;
}


```