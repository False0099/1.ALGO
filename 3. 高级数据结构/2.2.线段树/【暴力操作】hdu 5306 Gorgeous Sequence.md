## 题目描述
![[Pasted image 20230731150144.png]]

## 输入格式
多组测试数据，第一行 T 表示数据组数。  
对于每组数据，一行 n,m 表示长度和操作个数。  
接下来一行 n 个数代表序列的值。  
接下来 m 行每行一个操作。

	
## 输出格式
对于每一个询问输出一行表示答案。


## 样例 #1

### 样例输入 #1

```
1
5 5
1 2 3 4 5
1 1 5
2 1 5
0 3 5 3
1 1 5
2 1 5

```

### 样例输出 #1

```
5
15
3
12
```


## 题解
本题中的能看出明显模板的在于修改操作中 $a_{i}=min(a_{i},x)$，而且我们还要求最大值，这就**要求我们线段树中维护：最大值，次大值，区间和，区间和。**

区间修改我们可以这样分类，如果 $x$ 比区间所有数都大，相当于无事发生，如果**介于最大值和次大值之间，我们就直接把最大数变成我们的 $x$,区间和减去 $(x-a_{max})*cnt$**。否则我们就递推到下一个部分去求改。

剩下的区间求和和我们的区间最大也就很简单了。

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int w[N];
struct node{
	int l;
	int r;
	int max;
	int sec;
	int cnt;
	int lazy;
	int sum;
}tr[N<<2];
void pushup(int u){
	tr[u].max=max(tr[u<<1].max,tr[u<<1|1].max);
	tr[u].sum=tr[u<<1].sum+tr[u<<1|1].sum;
	if(tr[u<<1].max==tr[u<<1|1].max){
		tr[u].cnt=tr[u<<1].cnt+tr[u<<1|1].cnt;
		tr[u].sec=max(tr[u<<1].sec,tr[u<<1|1].sec);
	}else{
		tr[u].sec=max(tr[u<<1].sec,tr[u<<1|1].sec);
		tr[u].sec=max(tr[u].sec,min(tr[u<<1].max,tr[u<<1|1].max));
		tr[u].cnt=tr[u<<1].max>tr[u<<1|1].max?tr[u<<1].cnt:tr[u<<1|1].cnt;
	}
}
void addtag(int u,int x){
	if(x>=tr[u].max) return;
	tr[u].sum-=tr[u].cnt*(tr[u].max-x);
	tr[u].max=x;
}
void pushdown(int u){
	addtag(u<<1,tr[u].max);
	addtag(u<<1|1,tr[u].max);
}
void build(int u,int l,int r){
	tr[u].l=l;
	tr[u].r=r;
	if(l==r){
		tr[u].max=w[l];
		tr[u].sec=-1;//?
		tr[u].sum=w[l];
		tr[u].cnt=1;
		return;
	}
	int mid=l+r>>1;
	build(u<<1,l,mid);
	build(u<<1|1,mid+1,r);
	pushup(u); 
}
int query(int u,int l,int r){
	if(l<=tr[u].l&&tr[u].r<=r){
		return tr[u].sum;
	}
	pushdown(u);
	int mid=tr[u].l+tr[u].r>>1;
	int res=0;
	if(l<=mid){
		res+=query(u<<1,l,r);
	}	
	if(mid<r){
		res+=query(u<<1|1,l,r);
	}
	return res;
}
int querymax(int u,int l,int r){
	if(l<=tr[u].l&&tr[u].r<=r){
		return tr[u].max;
	}
	pushdown(u);
	int mid=tr[u].l+tr[u].r>>1;
	int res=-9999999;
	if(l<=mid){
		res=querymax(u<<1,l,r);
	}
	if(mid<r){
		res=max(res,querymax(u<<1|1,l,r));
	}
	return res;
}
void modify(int u,int l,int r,int d){
	if(d>=tr[u].max) return;
	if(tr[u].sec<d&&l<=tr[u].l&&tr[u].r<=r){
		addtag(u,d);
		return;
	}
	pushdown(u);
	long long mid=(tr[u].l+tr[u].r)>>1;
	if(l<=mid){
		modify(u<<1,l,r,d);
	}
	if(mid<r){
		modify(u<<1|1,l,r,d);
	}
	pushup(u);
}

int main(){
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>w[i];
	}
	build(1,1,n);
	while(m--){
		int q,l,r,x;
		cin>>q>>l>>r;
		if(q==0){
			cin>>x;
			modify(1,l,r,x);
		}
		if(q==1){
			cout<<querymax(1,l,r)<<endl;
		}
		if(q==2){
			cout<<query(1,l,r)<<endl; 
		}
	}
	return 0;
}
```