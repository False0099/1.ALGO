# Soldier and Badges

## 题面翻译

给 n 个数，每次操作可以将一个数 +1，要使这 n 个数都不相同，求最少要加多少？
1<= n <=3000 

感谢@凉凉提供的翻译

## 题目描述

Colonel has $ n $ badges. He wants to give one badge to every of his $ n $ soldiers. Each badge has a coolness factor, which shows how much it's owner reached. Coolness factor can be increased by one for the cost of one coin.

For every pair of soldiers one of them should get a badge with strictly higher factor than the second one. Exact values of their factors aren't important, they just need to have distinct factors.

Colonel knows, which soldier is supposed to get which badge initially, but there is a problem. Some of badges may have the same factor of coolness. Help him and calculate how much money has to be paid for making all badges have different factors of coolness.

## 输入格式

First line of input consists of one integer $n$ ( $1<=n<=3000$ ).

Next line consists of $n$ integers $a_{i}$ ( $1<=a_{i}<=n$ ), which stand for coolness factor of each badge.

## 输出格式

Output single integer — minimum amount of coins the colonel has to pay.

## 样例 #1

### 样例输入 #1

```
4
1 3 1 4
```

### 样例输出 #1

```
1
```

## 样例 #2

### 样例输入 #2

```
5
1 2 3 2 5
```

### 样例输出 #2

```
2
```

## 提示

In first sample test we can increase factor of first badge by $ 1 $ .

In second sample test we can increase factors of the second and the third badge by $ 1 $ .

## 题解
我们本题的相对于其他的隔壁相同问题来说要更加简单一点，因为我们本题只支持一种操作，就是让我们的某一个元素去加一。
于是，我们就一种方法就是以我们当前的集合的最小值为我们后序序列的起点。之后，再让我们的每一个元素都能够找到离自己最近的，没有出现的哪一个元素，即可。于是，我们就可以通过一个类似于桶排序的方法，记录出我们每一个元素对应的 cnt 是多少。之后再去进行计算即可。

同时，又因为我们每的移动可以拆分到我们的每一步当中去，所以，我们只需要简单的去进行我们的枚举即可。
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=6060;
int cnt[N];
#define int long long
signed main(){
	int n;
	cin>>n;
	for(int i=0;i<n;i++){
		int u;
		cin>>u;
		cnt[u]++;
	}
	int ans=0;
	for(int i=1;i<=2*n;i++){
		if(cnt[i]>1){
			cnt[i+1]+=cnt[i]-1;
			ans+=cnt[i]-1;
		}else{
			continue;
		}
	}
	cout<<ans<<endl;
}

```