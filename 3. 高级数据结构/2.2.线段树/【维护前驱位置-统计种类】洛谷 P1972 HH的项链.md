# [SDOI 2009] HH 的项链

## 题目描述

HH 有一串由各种漂亮的贝壳组成的项链。HH 相信不同的贝壳会带来好运，所以每次散步完后，他都会随意取出一段贝壳，思考它们所表达的含义。HH 不断地收集新的贝壳，因此，他的项链变得越来越长。  

有一天，他突然提出了一个问题：某一段贝壳中，包含了多少种不同的贝壳？这个问题很难回答…… 因为项链实在是太长了。于是，他只好求助睿智的你，来解决这个问题。

## 输入格式

一行一个正整数 $n$，表示项链长度。   
第二行 $n$ 个正整数 $a_i$，表示项链中第 $i$ 个贝壳的种类。

第三行一个整数 $m$，表示 HH 询问的个数。   
接下来 $m$ 行，每行两个整数 $l,r$，表示询问的区间。

## 输出格式

输出 $m$ 行，每行一个整数，依次表示询问对应的答案。

## 样例 #1

### 样例输入 #1

```
6
1 2 3 4 3 5
3
1 2
3 5
2 6
```

### 样例输出 #1

```
2
2
4
```

## 提示

【数据范围】  

对于 $20\%$ 的数据，$1\le n,m\leq 5000$；   
对于 $40\%$ 的数据，$1\le n,m\leq 10^5$；   
对于 $60\%$ 的数据，$1\le n,m\leq 5\times 10^5$；  
对于 $100\%$ 的数据，$1\le n,m,a_i \leq 10^6$，$1\le l \le r \le n$。

本题可能需要较快的读入方式，最大数据点读入数据约 20 MB

## 题解
我们这一题是非常经典的问题，需要我们统计我们区间内的种类有多少种，首先，我们能想到的一种朴素的方法，就是如果有一种新颜色，我们就让对应的颜色位置，然后我们统计的时候，就可以通过我们的前缀和知道我们哪些位置是需要我们进行修改的。

但是这种算法虽然很好，但是有一种问题就是：如果我们给我们的一个区间内添加了一个之前已经出现过的颜色，那么我们要怎么处理？

这个时候，我们就需要用到一个强有力的工具，$lastpos$ 数组，这个数组能否存储上一个和当前颜色相同的位置。那么我们现在就很简单了，现在我们只需要让我们的 $lastpos$ 位置的贡献清零，然后只计算当前位置的贡献，在离线的情况下，这是一定正确的。

比较遗憾的是，下面的做法常数比较大，有可能会被卡常，需要到时候注意：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 5, INF = 2e9;
typedef long long ll;
int n, q;
ll a[N], nans = LLONG_MIN;
int last[N];
class SegmentTree
{
public:
	struct Node
	{
		int l, r;
		ll sum;
	}tr[N << 2];
	Node merge(Node x, Node y)
	{
		if (x.l == -1) return y;
		if (y.l == -1) return x;
		Node z;
		z.l=min(x.l,y.l);
		z.r=max(x.r,y.r);
		z.sum=(x.sum+y.sum);
		return z;
	}//这里需要改 
	void pushup(int u)
	{
		tr[u] = merge(tr[u << 1], tr[u << 1 | 1]);
	}
	void build(int u, int l, int r)
	{
		tr[u] = {l, r, 0};
		if (l == r) return;
		int mid = l + r >> 1;
		build(u << 1, l, mid);
		build(u << 1 | 1, mid + 1, r);
		pushup(u);
	}
	void update(int u, int p, ll x)
	{
		if (tr[u].l == tr[u].r)
		{
			//这里需要改 
			tr[u].sum+=x;
			return;
		}
		int mid = tr[u].l + tr[u].r >> 1;
		if (p <= mid) update(u << 1, p, x);
		else update(u << 1 | 1, p, x);
		pushup(u);
	}
	Node query(int u, int l, int r)
	{
		if (tr[u].l >= l and tr[u].r <= r) 
		{
			return tr[u];
		}
		int mid = tr[u].l + tr[u].r >> 1;
		Node ret;
		ret.l = -1;
		if (l <= mid) ret = query(u << 1, l, r);
		if (r > mid) ret = merge(ret, query(u << 1 | 1, l, r));
		return ret;
	}
}t;
struct ask{
	int l,r,id,ans;	
}Ask[N];
int main()
{
	cin>>n;
	for (int i = 1; i <= n; i++){
		cin>>a[i];
	}
	cin>>q;
	for(int i=1;i<=q;i++){
		int l,r;
		cin>>l>>r;
		Ask[i]={l,r,i};
	}
	t.build(1,1,n);
	sort(Ask+1,Ask+1+q,[](ask a,ask b){
		return a.r<b.r;
	});
	for(int i=1,j=1;i<=q;i++){
		int r=Ask[i].r;
		while(j<=r){
			if(last[a[j]]){
				t.update(1,last[a[j]],-1);
			}
			last[a[j]]=j;
			t.update(1,j,1);
			j++;
		}
		Ask[i].ans=t.query(1,Ask[i].l,r).sum;
	}
	sort(Ask+1,Ask+1+q,[](ask a,ask b){
		return a.id<b.id;
	});
	for(int i=1;i<=q;i++){
		cout<<Ask[i].ans<<endl;
	}
	
}
```