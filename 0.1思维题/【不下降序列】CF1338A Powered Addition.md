# Powered Addition

## 题面翻译

一个数列，每个数可以选择一些 $j$，使得这个数加上 $\sum {2^{j-1}}$（$j$ 不一定要连续）。希望加上这些值后的数列成为不降序列。最小化使用到的的 $j$ 的最大值。

## 题目描述

You have an array $ a $ of length $ n $ . For every positive integer $ x $ you are going to perform the following operation during the $ x $ -th second:

- Select some distinct indices $ i_{1}, i_{2}, \ldots, i_{k} $ which are between $ 1 $ and $ n $ inclusive, and add $ 2^{x-1} $ to each corresponding position of $ a $ . Formally, $ a_{i_{j}} := a_{i_{j}} + 2^{x-1} $ for $ j = 1, 2, \ldots, k $ . Note that you are allowed to not select any indices at all.

You have to make $ a $ nondecreasing as fast as possible. Find the smallest number $ T $ such that you can make the array nondecreasing after at most $ T $ seconds.

Array $ a $ is nondecreasing if and only if $ a_{1} \le a_{2} \le \ldots \le a_{n} $ .

You have to answer $ t $ independent test cases.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 10^{4} $ ) — the number of test cases.

The first line of each test case contains single integer $ n $ ( $ 1 \le n \le 10^{5} $ ) — the length of array $ a $ . It is guaranteed that the sum of values of $ n $ over all test cases in the input does not exceed $ 10^{5} $ .

The second line of each test case contains $ n $ integers $ a_{1}, a_{2}, \ldots, a_{n} $ ( $ -10^{9} \le a_{i} \le 10^{9} $ ).

## 输出格式

For each test case, print the minimum number of seconds in which you can make $ a $ nondecreasing.

## 样例 #1

### 样例输入 #1

```
3
4
1 7 6 5
5
1 2 3 4 5
2
0 -4
```

### 样例输出 #1

```
2
0
3
```

## 提示

In the first test case, if you select indices $ 3, 4 $ at the $ 1 $ -st second and $ 4 $ at the $ 2 $ -nd second, then $ a $ will become $ [1, 7, 7, 8] $ . There are some other possible ways to make $ a $ nondecreasing in $ 2 $ seconds, but you can't do it faster.

In the second test case, $ a $ is already nondecreasing, so answer is $ 0 $ .

In the third test case, if you do nothing at first $ 2 $ seconds and select index $ 2 $ at the $ 3 $ -rd second, $ a $ will become $ [0, 0] $ .

## 题解
本题我们要求我们通过我们的若干次操作，能够构造出我们的不下降数组，这里，我们的操作是：对于每一个元素，可以任意选择一个 $j$,使得我们的 $a[i]+=(1\ll j)-1$。最后要我们最小化我们的最大的 j。

本题我们首先明确，如果我们想要最快的构造，那么我们构造出来的数字和我们之前数字之前的差应该尽可能的小，那么**我们就有结论**：我们构造的数值最接近的一个数列应该是满足: $a[i]=max_{0}^{i} a[k]$,这个时候我们的差值就是我们的 $max-a[i]$。

那么这个时候知道了我们构造的数字，我们想要知道我们的对应的 $j$ 是多少就很简单了。我们既可以选择枚举，也可以选择预处理出倍数后二分。

```
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define inf 0x3f3f3f3f
void solve(){
	int n;
	cin>>n;
	vector<int> a(n);
	for(int i=0;i<n;i++){
		cin>>a[i];
	}
	int ans=0;
	int pre_max=-inf;
	auto calc=[&](int num){
		for(int i=62;i>=0;i--){
			if((num>>i)&1==1){
				return i;
			}
		}	
	};
	for(int i=0;i<n;i++){
		pre_max=max(pre_max,a[i]);
		int u=pre_max-a[i];
		if(u>0){
			ans=max(ans,calc(u)+1);
		}
	}
	cout<<ans<<'\n';
}
signed main(){
	int t;
	cin>>t;
	while(t--){
		solve();
	}
}
```