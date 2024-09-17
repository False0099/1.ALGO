# Nikita and LCM

## 题目描述

Nikita is a student passionate about number theory and algorithms. He faces an interesting problem related to an array of numbers.

Suppose Nikita has an array of integers $ a $ of length $ n $ . He will call a subsequence $ ^\dagger $ of the array special if its [least common multiple (LCM)](https://en.wikipedia.org/wiki/Least_common_multiple) is not contained in $ a $ . The LCM of an empty subsequence is equal to $ 0 $ .

Nikita wonders: what is the length of the longest special subsequence of $ a $ ? Help him answer this question!

 $ ^\dagger $ A sequence $ b $ is a subsequence of $ a $ if $ b $ can be obtained from $ a $ by the deletion of several (possibly, zero or all) elements, without changing the order of the remaining elements. For example, $ [5,2,3] $ is a subsequence of $ [1,5,7,8,2,4,3] $ .

## 输入格式

Each test contains multiple test cases. The first line of input contains a single integer $ t $ ( $ 1 \le t \le 2000 $ ) — the number of test cases. The description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 1 \le n \le 2000 $ ) — the length of the array $ a $ .

The second line of each test case contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le 10^9 $ ) — the elements of the array $ a $ .

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2000 $ .

## 输出格式

For each test case, output a single integer — the length of the longest special subsequence of $ a $ .

## 样例 #1

### 样例输入 #1

```
6
5
1 2 4 8 16
6
3 2 10 20 60 1
7
2 3 4 6 12 100003 1200036
9
2 42 7 3 6 7 7 1 6
8
4 99 57 179 10203 2 11 40812
1
1
```

### 样例输出 #1

```
0
4
4
5
8
0
```

## 提示

In the first test case, the LCM of any non-empty subsequence is contained in $ a $ , so the answer is $ 0 $ .

In the second test case, we can take the subsequence $ [3, 2, 10, 1] $ , its LCM is equal to $ 30 $ , which is not contained in $ a $ .

In the third test case, we can take the subsequence $ [2, 3, 6, 100\, 003] $ , its LCM is equal to $ 600\, 018 $ , which is not contained in $ a $ .

## 题解
我们本体注意到，我们可以**暴力的求出我们的所有序列的对应的 lcm 的值**，这是因为，我们的 lcm 和我们的 gcd 类似，并且如果我们的 lcm **超过固定之后，可以直接添加**，因此，我们可以考虑下面的算法：
我们先暴力求出我们的每一个 `lcm` 可以有多少，然后再对每一个具体的 `lcm` 值，去找我们的对应的子序列的长度是多少，因为我们的 `lcm` 值域较大，所以我们就可以通过 map 来进行实现：
```
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
const int N=1e5+10;
const int inf=100000009;
int a[N];
int l[N];
int r[N];
void solve(){
	int n;
	cin>>n;
	map<int,int>mp;
	set<int> st;
	for(int i=0;i<n;i++){
		cin>>a[i];
		st.insert(a[i]);
	}
	for(int i=0;i<n;i++){
		map<int,int> tmp=mp;
		mp[a[i]]++;
		for(auto u:tmp){
			int num=u.first;
			int dig=u.second;
			int lcm=num*a[i]/__gcd(num,a[i]);
			if(lcm>5e9){
				lcm=inf;
			}
			mp[lcm]=max(mp[lcm],dig+1);
		}
	}
	int ans=0;
	for(auto u:mp){
		int num=u.first;
		int dig=u.second;
		//cout<<num<<endl;
		if(st.count(num)){
			continue;
		}else{
			ans=max(ans,dig);
		}
	}
	cout<<ans<<endl;
}
signed main(){
	ios::sync_with_stdio(false),cin.tie(0);	
	int t;
	cin>>t;
	while(t--){
		solve(); 
	}
}
```