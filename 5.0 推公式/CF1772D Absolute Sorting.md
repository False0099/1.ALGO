# Absolute Sorting

## 题面翻译

给定一个长度为 $n$ 的正整数序列 $a$，选择一个整数 $x$，将所有的 $a_i$ 变为 $|x-a_i|$，求能满足 $a_1\le a_2\le...\le a_n$ 和 $0\le x\le 10^9$ 的一个解 $x$。如果存在这样的一个 $x$ 请直接输出，如果无解请输出 $-1$.

数据范围：$1\le a_i\le10^8，2\le n\le2\cdot 10^5,1\le t\le2\cdot 10^4$。

## 题目描述

You are given an array $ a $ consisting of $ n $ integers. The array is sorted if $ a_1 \le a_2 \le \dots \le a_n $ .

You want to make the array $ a $ sorted by applying the following operation exactly once:

- Choose an integer $ x $ , then for every $ i \in [1, n] $ , replace $ a_i $ by $ |a_i - x| $ .

Find any value of $ x $ that will make the array sorted, or report that there is no such value.

## 输入格式

The first line contains one integer $ t $ ( $ 1 \le t \le 2 \cdot 10^4 $ ) — the number of test cases.

Each test case consists of two lines. The first line contains one integer $ n $ ( $ 2 \le n \le 2 \cdot 10^5 $ ). The second line contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ 1 \le a_i \le 10^8 $ ).

Additional constraint on the input: the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, print any integer $ x $ ( $ 0 \le x \le 10^9 $ ) that makes the array sorted. It can be shown that if such an integer $ x $ exists, there is at least one such integer between $ 0 $ and $ 10^9 $ .

If there is no such integer, then print $ -1 $ . If there are multiple suitable values of $ x $ , print any of them.

## 样例 #1

### 样例输入 #1

```
8
5
5 3 3 3 5
4
5 3 4 5
8
1 2 3 4 5 6 7 8
6
10 5 4 3 2 1
3
3 3 1
3
42 43 42
2
100000000 99999999
6
29613295 52036613 75100585 78027446 81409090 73215
```

### 样例输出 #1

```
4
-1
0
42
2
-1
100000000
40741153
```

## 提示

In the first test case, after using $ x = 4 $ , the array becomes $ [1, 1, 1, 1, 1] $ .

In the third test case, after using $ x = 0 $ , the array becomes $ [1, 2, 3, 4, 5, 6, 7, 8] $ .

In the fourth test case, after using $ x = 42 $ , the array becomes $ [32, 37, 38, 39, 40, 41] $ .

## 题解
我们本题假设我们的 $i<j$,假如我们有
$a_{i}\leq a_{j}$, $|a_{i}-x|\leq |a_{j}-x|$,那么我们就可以转化为：$x\leq \frac{a_{i}+a_{j}}{2}$,同理，如果我们有 $a_{i}>a_{j}$,那么我们的 $x\geq\frac{(a_{i}+a_{j})}{2}$
于是，我们就可以考虑两个相邻的数字即可，我们就可以用我们的 set 维护我们的 x 的上下界

```cpp
#include<bits/stdc++.h>
#define int long long
#define db double
#define inf 2e18
#define mp make_pair
#define fi first
#define se second
#define pr printf
#define ps puts
#define pb push_back
#define For(i,a,b) for(i=a;i<=b;i++)
#define FOR(i,a,b) for(i=a;i>=b;i--)
using namespace std;
const int N=2e5+10;
int n,m,a[N],b[N];
set<int> s;
int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar();
	}
	return x*f;
}
void solve(){
	int i,j,l,r,ramax_min,ramin_max;
	l=0;r=1e9;
	s.clear();
	s.insert(a[n]);
	set<int>::iterator it;
	FOR(i,n-1,1){
		it=s.lower_bound(a[i]);
		if(it!=s.end()){
			if(*it==a[i]){
				it++;
			}
			if(it!=s.end()){
				ramax_min=*it;
				r=min(r,(a[i]+ramax_min)/2);
			}
		} 
		it=s.lower_bound(a[i]);
		if(it!=s.begin()){
			ramin_max=*(--it);
			l=max(l,(a[i]+ramin_max-1)/2+1);
		} 
		s.insert(a[i]);
	}
	if(l>r) ps("-1");
	else pr("%lld\n",l);
}
signed main(){
	int t,i,j;
	t=read();
	while(t--){
		n=read();
		For(i,1,n) a[i]=read();
		solve();
	}
	return 0;
}
```