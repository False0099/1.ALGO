### Problem Statement

You are given an integer sequence $A = (A_1, A_2, \ldots, A_N)$.

Find the number of pairs of integers $(L, R)$ that satisfy the following conditions:

-   $1 \leq L \leq R \leq N$
-   There is a number that appears exactly once among $A_L, A_{L + 1}, \ldots, A_R$. More precisely, there is an integer $x$ such that exactly one integer $i$ satisfies $A_i = x$ and $L \leq i \leq R$.

### Constraints

-   $2 \leq N \leq 2 \times 10^5$
-   $1 \leq A_i \leq N$
-   All input values are integers.

### Input

The input is given from Standard Input in the following format:

`
$N$
$A_1$ $A_2$ $\ldots$ $A_N$


## 样例：
```text
5
2 2 1 2 1
```

```
12
```


```
4
4 4 4 4
```

```
4
```
## 题解
首先我们本题的第一要义是能够读懂我们的题目，本题要求我们的区间，并且我们的区间要满足：我们的区间内的存在一个数，他在这个区间内只出现了一次。

那么我们考虑下面的这种做法：我们考虑先预处理出我们的 $posl[i],posr[i]$，表示我们这个数的左侧和右侧第一次出现这个数的位置在哪里，然后我们在这一个区间内的数都可以选，我们可以把我们的上面所说的转换为：$l\in(pol[i],i]$, $r\in[posr[i],i)$

然后我们需要考虑我们的去重问题，首先，容斥原理我们一定是不考虑的，因为我们的 n 范围太大，于是，我们只能能考虑另一种方法，就是通过我们的矩形面积并来去重。

在这里，因为我们的值域范围有限，所以我们可以考虑使用把我们的每一个选数范围都映射为一个矩形，然后我们再求我们的举行的面积之并即可。

```cpp
#include<bits/stdc++.h>
#define lc(p) ((p)*2)
#define rc(p) ((p)*2+1)
#define mkpr make_pair
#define LL long long
using namespace std;
int n,a[200005],l[200005],r[200005];
map<int,int>mp;
LL ans;
struct Edge{
	int ll,rr,hh,ff;
}e[200005<<1];
int edgecnt,cnt;
void add_edge(int l,int r,int h,int f){
	e[++edgecnt].ll=l;
	e[edgecnt].rr=r;
	e[edgecnt].hh=h;
	e[edgecnt].ff=f;
}
bool cmp(Edge a,Edge b){
	if(a.hh==b.hh)return a.ff>b.ff;
	return a.hh<b.hh; 
}
struct Tree{
	int sum,len;
}tr[200005<<2];
void pushup(int p,int l,int r){
	if(tr[p].sum) tr[p].len=r-l+1;
	else if(l==r)tr[p].len=0;
	else tr[p].len=tr[lc(p)].len+tr[rc(p)].len;
}
void modify(int p,int l,int r,int ql,int qr,int val){
	if(ql<=l&&r<=qr){
		tr[p].sum+=val;
		pushup(p,l,r);
		return ;
	}
	int mid=(l+r)>>1;
	if(ql<=mid)modify(lc(p),l,mid,ql,qr,val);
	if(qr>mid)modify(rc(p),mid+1,r,ql,qr,val);
	pushup(p,l,r);
}
int main() {
	cin>>n;
	for(int i=1; i<=n; i++)cin>>a[i];
	for(int i=1; i<=n; i++) {
		l[i]=mp[a[i]]+1;
		mp[a[i]]=i;
	}
	mp.clear();
	for(int i=n; i>=1; i--) {
		if(mp[a[i]])r[i]=mp[a[i]]-1;
		else r[i]=n;
		mp[a[i]]=i;
	}
	for(int i=1;i<=n;i++){
		add_edge(i,r[i]+1,l[i],1);
		add_edge(i,r[i]+1,i+1,-1);
	}
	sort(e+1,e+1+edgecnt,cmp);
	for(int i=1;i<edgecnt;i++){
		modify(1,1,n+1,e[i].ll,e[i].rr-1,e[i].ff);
		ans+=1ll*tr[1].len*(e[i+1].hh-e[i].hh);
	}
	cout<<ans;
	return 0;
}
```