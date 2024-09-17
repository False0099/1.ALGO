# 
## 题目描述
给定一个长度为n的序列，一开始你可以把一个标记放在任何位置，ALICE和BOB可以将这个标记移动到在这个位置的左侧，比这个位置靠左且比这个数小的位置。不能移动就算失败，问有哪些位置是先手必胜的？

## 输入格式
The first line contains a single integer t (1≤t≤104) — the number of test cases.

The first line of each test case contains a single integer n (1≤n≤3⋅105) – the number of elements in the permutation.

The second line contains n integers p1,p2,…,pn (1≤pi≤n1). All pi are distinct.

The sum of n over all test cases doesn't exceed 3⋅105


## 输出格式
For each test case, print a single integer — the number of lucky elements in the permutation.

## 样例 #1

### 样例输入 #1

```
4
3
2 1 3
2
2 1
3
1 2 3
4
2 1 4 3

```

### 样例输出 #1

```
1
0
1
2

```

## 题解
我们采用一个数组$dp[i]$,来表示i位置是否是必胜的。那么我们的转移就是一个类似于区间转移的操作，去找i前面所有比$a[i]$大的数所在的位置，并且如果这个位置是必败态，那么我们才认为i位置是必胜态，并且停止更新，我们的答案也相应的++，
其中，我们就需要维护一个数据结构，用来统计，在某个位置的逆序数和他们的位置，这个时候，我们就需要用到我们的树状数组了。

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 3e5 + 5;
typedef long long ll;
const int maxv = 4e6 + 5;
typedef pair<ll, ll> pll;
 
 
int a[N];
 
struct MIT
{
ll tr[N];
int lowbit(int x) {
    return x & (-x);
}
 
void add(int u, int v) {
    for (int i = u; i < N; i += lowbit(i)) {
        tr[i] += v;
    }
}
 
ll query(int x) {
    ll res = 0;
 
    for (int i = x; i > 0; i -= lowbit(i)) {
        res += tr[i];
    }
 
    return res;
}
};
 
MIT t1,t2;
//树状数组t1维护的是到目前为止，前方有多少个比自己小的点

//树状数组t2则是维护的比自己小的点的信息
 
void solve()
{
	int n;
	cin>>n;
	int cnt=0;
	memset(t1.tr,0,sizeof t1.tr);
	memset(t2.tr,0,sizeof t2.tr);
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++){
		int x1=t1.query(a[i]);
		int x2=t2.query(a[i]);
		if(x1==0){//x1==0代表当前点前方没有点，根据题意，这种状态也为必败态
			t1.add(a[i],1);//那么我们直接把它加入到t1即可
		}
		else if(x2==0){
			t2.add(a[i],1);//如果当前点前方全为必败态，那么当前点就是必胜态
			t1.add(a[i],1);
			cnt++;
		}
 
	}
	cout<<cnt<<endl;
 
}
 
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int t = 1;
	cin >> t;
	while (t--)
	{
		solve();
	}
	system("pause");
	return 0;
}
```