# Rmq Problem / mex

## 题目描述

有一个长度为 $n$ 的数组 $\{a_1,a_2,\ldots,a_n\}$。

$m$ 次询问，每次询问一个区间内最小没有出现过的自然数。

## 输入格式

第一行，两个正整数 $n,m$。  
第二行，$n$ 个非负整数 $a_1, a_2, \ldots , a_n$。  
接下来 $m$ 行，每行两个正整数 $l,r$，表示一次询问。

## 输出格式

输出 $m$ 行，每行一个数，依次表示每个询问的答案。

## 样例 #1

### 样例输入 #1

```
5 5
2 1 0 2 1
3 3
2 3
2 4
1 2
3 5
```

### 样例输出 #1

```
1
2
3
0
3
```

## 提示

对于 $30\%$ 的数据：$1\leq n,m\leq 1000$。  
对于 $100\%$ 的数据：$1\leq n,m\leq 2\times {10}^5$，$1\leq l\leq r\leq n$，$0\leq a_i\leq 2\times 10^5$。

## 题解
首先，我们对于区间问题，我们可以考虑把我们的询问给离线下来，并且按照我们的区间右端点进行排序。

而众所周知，我们再我们的 $MEX$ 是一个排列的问题中，常常会考虑维护一个 $pos[i]$，用来存储我们第 $i$ 个数的对应位置是多少。而我们这一题也可以考虑用一个 $pos[i]$ 存储我们第 $i$ 个数对应的位置在什么地方。

但是在本题中，我们一个数字对应的位置可能不是唯一的，对于这种情况，我们要怎么办？在这里，我们的思路是：加强我们的原来的数组，我们加强为 $lastpos[i]$,表示我们上一个出现的数字是多少。

注意到，我们的这个 $lastpos[i]$ 是和我们的序列有关的，因此我们必须要离线我们的每一次查询。固定 $r$,且已知 $lastpos[i]$ 的情况下，我们怎么求出我们的每一个 $l$ 所对应的 $[l,r]$ 的区间 mex 是多少。

根据我们的 $mex$ 定义，如果我们的 $mex[l,r]=m$,那么我们一定满足 $min(lastpos[1,m-1])\leq l$,而对于怎么快速的求出我们的 $lastpos[1,m-1]$,我们可以通过我们的线段树来维护，而对于怎么快速的求出我们的 $m$，我们这里有两种方法，一种是在我们的函数外部进行二分，另一种是在我们的函数内部进行二分。

下面是在函数外部二分，时间复杂度为 $o(n\log^2n)$。
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5, INF = 2e9;
typedef long long ll;
int n, q;
ll a[N], nans = LLONG_MIN;
class SegmentTree
{
public:
	struct Node
	{
		int l, r;
		ll minn;
		
	}tr[N << 2];
	Node merge(Node x, Node y)
	{
		if (x.l == -1) return y;
		if (y.l == -1) return x;
		Node z;
		z.l=min(x.l,y.l);
		z.r=max(x.r,y.r);
		z.minn=min(x.minn,y.minn);
		return z;
	}
	void pushup(int u)
	{
		tr[u] = merge(tr[u << 1], tr[u << 1 | 1]);
	}
	void build(int u, int l, int r)
	{
		tr[u] = {l, r, -1};
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
			tr[u].minn=x;
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
	cin>>n>>q;
	for (int i = 1; i <= n; i++){
		cin>>a[i];
		a[i]++;
		a[i]=min(a[i],1ll*(n+2));
	}
	t.build(1,1,n+2);
	for(int i=1;i<=q;i++){
		int l,r;
		cin>>l>>r;
		Ask[i]={l,r,i};
	}
	sort(Ask+1,Ask+1+q,[](ask a,ask b){
		return a.r<b.r;
	});
	for(int i=1,j=1;i<=q;i++){
		int r=Ask[i].r;
		while(j<=r){
			t.update(1,a[j],j);
			j++;
		}
		int l=2,rr=n+1;
		while(l<=rr){
			int mid=l+rr>>1;
			if(t.query(1,1,mid-1).minn>=Ask[i].l){
				l=mid+1;
			}else{
				rr=mid-1;
			}
		}
		Ask[i].ans=l-1;
	}
	sort(Ask+1,Ask+1+q,[](ask a,ask b){
		return a.id<b.id;
	});
	for(int i=1;i<=q;i++){
		cout<<Ask[i].ans-1<<endl;
	}
	
}
```