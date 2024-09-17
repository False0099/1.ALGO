给你一串序列，每次对它有四种操作，  
1.C l r d:将l到r之间所有的数+d，同时时间戳+1。  
2.Q l r:查询当前时间戳下l到r的所有数的总和。  
3.H l r t:查询时间戳t下的l到r的所有数的和。  
4.B t:将时间戳返回至t。

Input

n m  
A 1 A 2 ... A n  
... (here following the m operations. )

Output

... (for each query, simply print the result. )

Sample Input

10 5
1 2 3 4 5 6 7 8 9 10
Q 4 4
Q 1 10
Q 2 4
C 3 6 3
Q 2 4
2 4
0 0
C 1 1 1
C 2 2 -1
Q 1 2
H 1 2 1

Sample Output

4
55
9
15
0
1

## 题解
我们这一题就是我们带区间修改的主席树，我们采用的主要思路是：**将维护原数组转化为维护原数组的查分数组，这样依然是单点修改，单点查询**。详细在于我们更新的时候的操作（详情见下方代码）

```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<queue>
#include<set>
#include<string>
#include<cmath>
#include<cstring>
#define FF first
#define SS second
#define ll long long
#define pb push_back
#define pm make_pair
using namespace std;
typedef pair<int,int> PII;
const int MAX = 1e5 + 5;
struct TREE {
	int l,r;
	ll val,lazy;
} tr[MAX*40];
 
int tot;
int a[MAX];
int root[MAX];
void pushup(int cur,int l,int r) {
	tr[cur].val = tr[tr[cur].l].val + tr[tr[cur].r].val + tr[cur].lazy*(r-l+1);
} 
int build(int l,int r) {
	int cur = ++tot;
	tr[cur].lazy = 0;
	if(l == r) {
		tr[cur].val = a[l];//这一步好像没啥用？ 
		return cur;
	}
	int m = (l+r)>>1;
	tr[cur].l = build(l,m);
	tr[cur].r = build(m+1,r);
	pushup(cur,l,r);
	return cur;
}
int update(int pre,int pl,int pr,ll val,int l,int r) {
	int cur = ++tot;
	tr[cur] = tr[pre];
	if(pl <= l && pr >= r) {
		tr[cur].val += (r-l+1)*val;
		tr[cur].lazy += val;
		return cur;
	}
	int m = (l+r)>>1;
	if(pl <= m) tr[cur].l = update(tr[pre].l,pl,pr,val,l,m);
	if(pr >= m+1) tr[cur].r = update(tr[pre].r,pl,pr,val,m+1,r);
	pushup(cur,l,r);
	return cur;
}
ll query(int cur,int pl,int pr,ll laz,int l,int r) {
	if(pl <= l && pr >= r) return tr[cur].val + laz * (r-l+1);
	ll res = 0;
	laz += tr[cur].lazy;
	int m = (l+r)>>1;	
	if(pl <= m) res += query(tr[cur].l,pl,pr,laz,l,m);
	if(pr >= m+1) res += query(tr[cur].r,pl,pr,laz,m+1,r); 
	return res;  
}
int main()
{
	int n,m,l,r;
	ll d;
	char op[5];
	while(cin>>n>>m) {
		for(int i = 1; i<=n; i++) cin>>a[i];
		int T = 0,t; 
		tot=0;
		root[T] = build(1,n);
		while(m--) {
			scanf("%s",op);
			if(op[0] == 'C') {
				scanf("%d%d%lld",&l,&r,&d);
				T++;
				root[T] = update(root[T-1],l,r,d,1,n);//注意这里的序列是1~n就行了，而不是1~m！！！ 
			}
			else if(op[0] == 'Q') {
				scanf("%d%d",&l,&r);
				printf("%lld\n",query(root[T],l,r,0,1,n));
			}
			else if(op[0] == 'H') {
				scanf("%d%d%d",&l,&r,&t);
				printf("%lld\n",query(root[t],l,r,0,1,n));
			}
			else scanf("%d",&T);		
		}		
	}
 
	return 0 ;
}
/*
2 4
0 0
C 1 1 1
C 2 2 -1
Q 1 2
H 1 2 1
*/
```