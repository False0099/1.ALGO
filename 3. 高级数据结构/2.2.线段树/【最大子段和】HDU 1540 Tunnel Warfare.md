# 
## 题目描述
![[Pasted image 20230731151121.png]]

## 输入格式
输入包含多组测试数据。

每组数据第一行包含两个整数 n,m。

接下来 m 行，每行描述一个事件，格式如题面所述。


## 输出格式
每个询问输出一行回答。
## 样例 #1

### 样例输入 #1

```
7 9
D 3
D 6
D 5
Q 4
Q 5
R
Q 4
R
Q 4

```

### 样例输出 #1

```
1
0
2
4

```

## 题解
模型转换：
1. 摧毁了一个村庄：某一个点的值变为 0
2. 查询从某个点开始能到达的最长区间：我们从某个点开始最长的连续 1 的个数。
3. 修复了某个村庄：这一个点的值变为 1


本题是典型的求区间上的最大连通区间的问题，我们就可以通过维护一段区间内的**最长连续前缀，最长连续后缀**，来最后拼凑出来某个点所能到达的村庄总数（最长连续 1 的个数）
![[无标题 10.png]]
对于每一次查询，我们先把这个查询给进行一个分类


## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=50010;
struct node{
	int l,r;
	int pre,suf;
	int val;
	int max;
}tr[N<<2];
void pushup(int u){
	int lenl=tr[u<<1].r-tr[u<<1].l+1;
	int lenr=tr[u<<1|1].r-tr[u<<1|1].l+1;
	int len=tr[u].r-tr[u].l+1;
	tr[u].pre=tr[u<<1].pre;
	tr[u].suf=tr[u<<1|1].suf;
	if(tr[u<<1].pre==lenl){
		tr[u].pre=tr[u<<1].pre+tr[u<<1|1].pre;
	}
	if(tr[u<<1|1].suf==lenr){
		tr[u].suf=tr[u<<1].suf+tr[u<<1|1].suf;
	}
	tr[u].max=max(tr[u].pre,tr[u].suf);
	tr[u].max=max(tr[u].max,tr[u<<1].suf+tr[u<<1|1].pre);
}
void build(int u,int l,int r){
	tr[u].l=l,tr[u].r=r;
	if(l==r){
		tr[u].pre=1;
		tr[u].suf=1;
		tr[u].val=1;//1表示有 
		return;
	}
	int mid=l+r>>1;
	build(u<<1,l,mid);
	build(u<<1|1,mid+1,r);
	pushup(u);
}
void modify(int u,int x,int d){
	if(tr[u].l==tr[u].r){
		tr[u].pre=d;
		tr[u].val=d;
		tr[u].suf=d;
		return; 
	}
	int mid=tr[u].l+tr[u].r>>1;
	if(x<=mid){
		modify(u>>1,x,d);
	}
	if(x>mid){
		modify(u>>1|1,x,d);
	}
	pushup(u);
}
int query(int u,int x){
	if(tr[u].l==tr[u].r){
		return tr[u].val;
	}
	int mid=tr[u].l+tr[u].r>>1;
	if(x<=mid){
		//按照查询的点是否在我们的区间内来分类
		if(x+tr[u<<1].suf>mid) return tr[u<<1].suf+tr[u<<1|1].pre;
		else return query(u<<1,x);
	}
	else{
		//按照是否被我们的区间完全覆盖来分类
		if(mid+tr[u<<1|1].pre>=x) return tr[u<<1].suf+tr[u<<1|1].pre;
		else return query(u<<1|1,x);
	}
}
int main(){
	int n,m;
	cin>>n>>m;
	build(1,1,n);
	tot=0;
	while(m--){
		string op;
		cin>>op;
		if(op[0]=='Q'){
			cin>>x;
			cout<<query(1,x);
		}
		if(op[0]=='D'){
			cin>>x;
			history[++tot]=x;
			modify(1,x,0);
		}
		else{
			x=history[tot--];
			modify(1,x,1);
		}
	}
}
```

