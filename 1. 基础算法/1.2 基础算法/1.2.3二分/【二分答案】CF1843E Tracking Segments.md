# Tracking Segments

## 题面翻译

有一个长度为 $n$，初始全为 $0$ 的序列。我们定义一个区间是美丽的，当且仅当区间内 $1$ 的个数严格大于 $0$ 的个数。现给定 $m$ 个区间和 $q$ 次修改，每次修改可以将该位置上的 $0$ 变成 $1$。对于每组数据，求出最少第几次修改后，给定的 $m$ 个区间中至少一个是美丽的。数据保证每次修改各不相同。

## 题目描述

You are given an array $ a $ consisting of $ n $ zeros. You are also given a set of $ m $ not necessarily different segments. Each segment is defined by two numbers $ l_i $ and $ r_i $ ( $ 1 \le l_i \le r_i \le n $ ) and represents a subarray $ a_{l_i}, a_{l_i+1}, \dots, a_{r_i} $ of the array $ a $ .

Let's call the segment $ l_i, r_i $ beautiful if the number of ones on this segment is strictly greater than the number of zeros. For example, if $ a = [1, 0, 1, 0, 1] $ , then the segment $ [1, 5] $ is beautiful (the number of ones is $ 3 $ , the number of zeros is $ 2 $ ), but the segment $ [3, 4] $ is not is beautiful (the number of ones is $ 1 $ , the number of zeros is $ 1 $ ).

You also have $ q $ changes. For each change you are given the number $ 1 \le x \le n $ , which means that you must assign an element $ a_x $ the value $ 1 $ .

You have to find the first change after which at least one of $ m $ given segments becomes beautiful, or report that none of them is beautiful after processing all $ q $ changes.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

The first line of each test case contains two integers $ n $ and $ m $ ( $ 1 \le m \le n \le 10^5 $ ) — the size of the array $ a $ and the number of segments, respectively.

Then there are $ m $ lines consisting of two numbers $ l_i $ and $ r_i $ ( $ 1 \le l_i \le r_i \le n $ ) —the boundaries of the segments.

The next line contains an integer $ q $ ( $ 1 \le q \le n $ ) — the number of changes.

The following $ q $ lines each contain a single integer $ x $ ( $ 1 \le x \le n $ ) — the index of the array element that needs to be set to $ 1 $ . It is guaranteed that indexes in queries are distinct.

It is guaranteed that the sum of $ n $ for all test cases does not exceed $ 10^5 $ .

## 输出格式

For each test case, output one integer — the minimum change number after which at least one of the segments will be beautiful, or $ -1 $ if none of the segments will be beautiful.

## 样例 #1

### 样例输入 #1

```
6
5 5
1 2
4 5
1 5
1 3
2 4
5
5
3
1
2
4
4 2
1 1
4 4
2
2
3
5 2
1 5
1 5
4
2
1
3
4
5 2
1 5
1 3
5
4
1
2
3
5
5 5
1 5
1 5
1 5
1 5
1 4
3
1
4
3
3 2
2 2
1 3
3
2
3
1
```

### 样例输出 #1

```
3
-1
3
3
3
1
```

## 提示

In the first case, after first 2 changes we won't have any beautiful segments, but after the third one on a segment $ [1; 5] $ there will be 3 ones and only 2 zeros, so the answer is 3.

In the second case, there won't be any beautiful segments.

## 题解
我们同时注意到，我们的答案是可二分的，因此，我们可以二分找到我们的这一个答案
check 函数考虑计算我们的 0-1 串的对应匹配数，我们考虑**使用前缀和来进行统计**。这样，我们就可以 $o(1)$ 的得到，我们的区间是不是满足我们的预置条件。
```
#include <bits/stdc++.h>
#define endl '\n'
using namespace std;
const int N=1e5+10;
int a[N];
struct node{
	int l;
	int r;
}Line[N];
int pos[N];
int sum[N]; 
void solve(){
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		int l,r;
		cin>>l>>r;
		Line[i]={l,r};
	}
	int q;
	cin>>q;
	for(int i=1;i<=q;i++){
		cin>>pos[i];
	}
	int l=0,r=q+1;
	auto check=[&](int mid){
		for(int i=1;i<=mid;i++){
			sum[pos[i]]=1;
		}
		for(int i=1;i<=n;i++){
			sum[i]=sum[i]+sum[i-1];
		}
		bool tag=false;
		for(int i=1;i<=m;i++){
			int r=Line[i].r;
			int l=Line[i].l;
			if(sum[r]-sum[l-1]>(r-l+1)/2){
				tag=true;
				break;
			}
		}	
		for(int i=1;i<=n;i++){
			sum[i]=0;
		}
		return tag;
	};
	while(l<r){
		int mid=l+r>>1;
		if(check(mid)){
			r=mid;
		}else{
			l=mid+1;
		}
	}
	//cout<<check(3)<<" ";
	//cout<<check(2)<<" ";
	if(l>q){
		cout<<-1<<endl;
	}else{
		cout<<l<<endl;
	}
}
int main(){
	int t;
	cin>>t;
	while(t--){
		solve();
	}
}
```