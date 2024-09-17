# Prefix Permutation Sums

## 题面翻译

给你一个长度为 $n - 1$ 的数组，是否能找出一个长度为 $n$ 的排列，求出这个排列的前缀和，去掉前缀和数组的任意一个元素之后和原来的数组相等。

例如 $[6, 8, 12, 15]$，可以是排列 $[1, 5, 2, 4, 3]$ 的前缀和 $[1, 6, 8, 12, 15]$ 去掉元素 $1$。

## 题目描述

Your friends have an array of $n$ elements, calculated its array of prefix sums and passed it to you, accidentally losing one element during the transfer. Your task is to find out if the given array can matches permutation.

A permutation of $n$ elements is an array of $n$ numbers from $1$ to $n$ such that each number occurs exactly one times in it.

The array of prefix sums of the array $ a $ — is such an array $ b $ that $ b_i = \sum_{j=1}^i a_j, 1 \le i \le n $ .

For example, the original permutation was $ [1, 5, 2, 4, 3] $ . Its array of prefix sums — $ [1, 6, 8, 12, 15] $ . Having lost one element, you can get, for example, arrays $ [6, 8, 12, 15] $ or $ [1, 6, 8, 15] $ .

It can also be shown that the array $ [1, 2, 100] $ does not correspond to any permutation.

## 输入格式

The first line contains a positive number $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases. The description of the test cases follows.

The first line of the description of each test case contains a positive number $ n $ ( $ 2 \le n \le 2 \cdot 10^5 $ ) — the size of the initial array.

The second line of the description of each test case contains $ n - 1 $ positive number $ a_i $ ( $ 1 \le a_i \le 10^{18} $ ), $ a_{i-1} < a_i $ — elements of the array of prefix sums.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output "YES" if such a permutation exists, and "NO" otherwise.

You can output "YES" and "NO" in any case (for example, the strings "yEs", "yes" and "Yes" will be recognized as a positive response).

## 样例 #1

### 样例输入 #1

```
12
5
6 8 12 15
5
1 6 8 15
4
1 2 100
4
1 3 6
2
2
3
1 2
4
3 7 10
5
5 44 46 50
4
1 9 10
5
13 21 36 42
5
1 2 3 1000000000000000000
9
9 11 12 20 25 28 30 33
```

### 样例输出 #1

```
YES
YES
NO
YES
YES
NO
YES
NO
NO
NO
NO
NO
```

## 提示

In the fourth example, for example, the permutation $ [1, 2, 3, 4] $ is suitable. In the fifth example, for example, the permutation $ [2, 1] $ is suitable. In the seventh example, for example, the permutation $ [1, 2, 4, 3] $ is suitable.

## 题解
**坑点：
1. 注意开 long long。
2. 我们要把一开始的数组差分一次后才是我们的目标数组。

首先，我们先对我们的数组进行一个差分，差分后，如果我们的差分数组中有超过两个相同的值，那么我们就直接认为不可行，输出-1 即可。
如果我们的差分数组有一个大于 n 的值，那么我们先不管他，先考虑其他的元素，然后再拿我们剩下的没有包含的元素看能不能组成我们这个大于 n 的值，如果可以，我们就继续，不行，我们就跳过
如果我们的差分数组中有一个数出现了两次，那么我们将其中的一个忽略，看剩下的没选过的能不能合成拿个玩意儿，如果可以，那么我们就成功了。否则我们失败。
**如果都不满足，我们就补充一个数字**

```cpp
#include<bits/stdc++.h>
#define ll long long
#define MAXN 200010
using namespace std;
 
ll read(){
	char ch=getchar();
	ll s=0, w=1;
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){s=s*10+ch-'0';ch=getchar();}
	return s*w; 
}
 
ll a[MAXN];
ll b[MAXN];
bool vis[MAXN];
 
int main(){
	ll T = read();
	
	while(T--){
		ll n;
		n = read();
		
		ll pos = 0;
		
		for(ll i = 1; i <= 2 * n; i++){
			vis[i] = false;
		}
		
		bool f = true;
		
		for(ll i = 1; i <= n-1; i++){
			a[i] = read();
		}
		
		for(ll i = 1; i <= n-1; i++){
			if(a[i] > n * (n+1) / 2){
				f = false;
				break;
			}
			b[i] = a[i] - a[i-1];
			if(vis[b[i]] || b[i] > n){
				if(pos){
					f = false;
					break;
				}
				pos = b[i];
			}
			vis[b[i]] = true;
		}
		
		if(!f){
			cout << "NO\n";
			continue;
		}
		
		if(pos == 0){
			cout << "YES\n";
			continue;
		} 
		
		ll pos1 = 0, pos2 = 0;
		
		for(ll i = 1; i <= n; i++){
			if(!vis[i]){
				if(pos1 == 0){
					pos1 = i;
				}else{
					pos2 = i;
				}
			}
		}
		
		cout << (pos1 + pos2 == pos ? "YES" : "NO") << endl;
		
	}
	return 0;
}
```