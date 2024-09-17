# Diverse Substrings

## 题面翻译

定义一个数字串是**多变的**当且仅当其中所有数字的重复次数均不超过其中不同数字的种类数。

给定一个由 $0$ 到 $9$ 组成的长为 $n$ 的数字串 $s$，求其不同的**多变的**子串 $s_{[l,r]}$ 的个数。

## 题目描述

A non-empty digit string is diverse if the number of occurrences of each character in it doesn't exceed the number of distinct characters in it.

For example:

- String "7" is diverse because 7 appears in it $ 1 $ time and the number of distinct characters in it is $ 1 $ ;
- String "77" is not diverse because 7 appears in it $ 2 $ times and the number of distinct characters in it is $ 1 $ ;
- String "1010" is diverse because both 0 and 1 appear in it $ 2 $ times and the number of distinct characters in it is $ 2 $ ;
- String "6668" is not diverse because 6 appears in it $ 3 $ times and the number of distinct characters in it is $ 2 $ .

You are given a string $ s $ of length $ n $ , consisting of only digits $ 0 $ to $ 9 $ . Find how many of its $ \frac{n (n+1)}{2} $ substrings are diverse.

A string $ a $ is a substring of a string $ b $ if $ a $ can be obtained from $ b $ by deletion of several (possibly, zero or all) characters from the beginning and several (possibly, zero or all) characters from the end.

Note that if the same diverse string appears in $ s $ multiple times, each occurrence should be counted independently. For example, there are two diverse substrings in "77" both equal to "7", so the answer for the string "77" is $ 2 $ .

## 输入格式

Each test contains multiple test cases. The first line contains a single integer $t$ ( $1 \le t \le 10^4$ ) — the number of test cases.

The first line of each test case contains a single integer $n$ ( $1 \le n \le 10^5$ ) — the length of the string $s$ .

The second line of each test case contains a string $s$ of length $n$ . It is guaranteed that all characters of $ s $ are digits from $ 0 $ to $ 9 $ .

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 10^5 $ .

## 输出格式

For each test case print one integer — the number of diverse substrings of the given string $ s $ .

## 样例 #1

### 样例输入 #1

```
7
1
7
2
77
4
1010
5
01100
6
399996
5
23456
18
789987887987998798
```

### 样例输出 #1

```
1
2
10
12
10
15
106
```

## 提示

In the first test case, the diverse substring is "7".

In the second test case, the only diverse substring is "7", which appears twice, so the answer is $ 2 $ .

In the third test case, the diverse substrings are "0" ( $ 2 $ times), "01", "010", "1" ( $ 2 $ times), "10" ( $ 2 $ times), "101" and "1010".

In the fourth test case, the diverse substrings are "0" ( $ 3 $ times), "01", "011", "0110", "1" ( $ 2 $ times), "10", "100", "110" and "1100".

In the fifth test case, the diverse substrings are "3", "39", "399", "6", "9" ( $ 4 $ times), "96" and "996".

In the sixth test case, all $ 15 $ non-empty substrings of "23456" are diverse.

## 题解
因为数字最多只有 10 个，若子串为多变的那么每个数字出现次数不超过 10 次。所以子串长度不超过 100.

那么我们暴力枚举 i，从 i 往后暴力枚举 100 个数，检查是否满足条件即可。过程可以用桶轻松实现。

```cpp
/********************
  *	author:Spouter_27
  *	place:spst Alego
  * with:marmoreal_777
  ******************/
#include<bits/stdc++.h>
using namespace std;
//#define int long long
typedef long long ll;
const ll N=2e5+10;
ll n,T,t[10];
string a;
void init(){
}
void solve(){
	scanf("%lld\n",&n);
	getline(cin,a);
	ll ans=0;
	for(int i=0;i<n;i++){
		memset(t,0,sizeof(t));
		ll cnt=0,maxn=0;
		for(int j=i;j<min(n,i+101ll);j++){
			t[a[j]-'0']++;
			if(t[a[j]-'0']==1)	cnt++;
			maxn=max(maxn,t[a[j]-'0']);
			if(maxn<=cnt)	ans++;
		}
	}
	printf("%lld\n",ans);
	
}
signed main(){
	scanf("%lld",&T);
	init();
	while(T--){
		solve();
	}
	return 0;
}
/*
exSample:

*/
```