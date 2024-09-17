# Wooden Toy Festival

## 题面翻译

$T$ 组评测，每组数据给定长度 $n$ 与长度为 $n$ 的序列 $a$，你需要选三个数 $x,y,z$，输出可得到的最小的 $\max\{\min\{|a_i-x|,|a_i-y|,|a_i-z|\}\}$。

## 题目描述

In a small town, there is a workshop specializing in woodwork. Since the town is small, only three carvers work there.

Soon, a wooden toy festival is planned in the town. The workshop employees want to prepare for it.

They know that $ n $ people will come to the workshop with a request to make a wooden toy. People are different and may want different toys. For simplicity, let's denote the pattern of the toy that the $ i $ -th person wants as $ a_i $ ( $ 1 \le a_i \le 10^9 $ ).

Each of the carvers can choose an integer pattern $ x $ ( $ 1 \le x \le 10^9 $ ) in advance, different carvers can choose different patterns. $ x $ is the integer. During the preparation for the festival, the carvers will perfectly work out the technique of making the toy of the chosen pattern, which will allow them to cut it out of wood instantly. To make a toy of pattern $ y $ for a carver who has chosen pattern $ x $ , it will take $ |x - y| $ time, because the more the toy resembles the one he can make instantly, the faster the carver will cope with the work.

On the day of the festival, when the next person comes to the workshop with a request to make a wooden toy, the carvers can choose who will take on the job. At the same time, the carvers are very skilled people and can work on orders for different people simultaneously.

Since people don't like to wait, the carvers want to choose patterns for preparation in such a way that the maximum waiting time over all people is as small as possible.

Output the best maximum waiting time that the carvers can achieve.

## 输入格式

The first line of the input contains an integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

Then follow the descriptions of the test cases.

The first line of a test case contains a single integer $ n $ ( $ 1 \le n \le 2 \cdot 10^5 $ ) — the number of people who will come to the workshop.

The second line of a test case contains $ n $ integers $ a_1, a_2, a_3, \dots, a_n $ ( $ 1 \le a_i \le 10^9 $ ) — the patterns of toys.

The sum of all $ n $ values over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

Output $ t $ numbers, each of which is the answer to the corresponding test case — the best maximum waiting time that the carvers can achieve.

## 样例 #1

### 样例输入 #1

```
5
6
1 7 7 9 9 9
6
5 4 2 1 30 60
9
14 19 37 59 1 4 4 98 73
1
2
6
3 10 1 17 15 11
```

### 样例输出 #1

```
0
2
13
0
1
```

## 提示

In the first example, the carvers can choose patterns $ 1 $ , $ 7 $ , $ 9 $ for preparation.

In the second example, the carvers can choose patterns $ 3 $ , $ 30 $ , $ 60 $ for preparation.

In the third example, the carvers can choose patterns $ 14 $ , $ 50 $ , $ 85 $ for preparation.

## 题解
我们这一题要我们最小化我们的 $max\{min\{|a_{i}-x|,|a_{i}-y|,|a_{i}-z|\}\}$ 
就相当于求我们的 $min_{i=1}^n(max(min(|a_{i}-x|,|a_{i}-y|,|a_{i}-z|))$
我们于是可以考虑用我们的二分答案法，先考虑枚举我们的答案是多少，即我们的 $max(min(|a_{i}-x|,|a_{i}-y|,|a_{i}-z|))=t$
然后我们检查对于每个 t 是否存在对应合法的 $x,y,z$ 为了能够覆盖到 $a_{1}$,我们的 x 应该尽可能的往大了取，我们令我们的 $x=a_{i}+k$，直观来说，我们看下图：
![[无标题 12.png]]

```cpp
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n,a[200001],sum;
int up(int x){
	if(x&1)return x/2+1;
	else return x/2;
}
bool check(int x){
	int l=1,r=1;
	int cnt=0;
	while(++cnt){
		if(cnt==4)return 0;
		while(r<n&&a[r+1]<=a[l]+2*x)r++;
		if(r==n)break;
		l=r+1,r++;
	}
	return 1;
}
signed main(){
	scanf("%lld",&t);
	while(t--){
		scanf("%lld",&n);
		for(int i=1;i<=n;i++)scanf("%lld",&a[i]);
		if(n<=3){
			puts("0");
			continue;
		}
		sort(a+1,a+n+1);
		int l=0,r=up(a[n]-a[1]),ans;
		while(l<=r){
			int mid=(l+r)>>1;
			if(check(mid))ans=mid,r=mid-1;
			else l=mid+1;
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```
```