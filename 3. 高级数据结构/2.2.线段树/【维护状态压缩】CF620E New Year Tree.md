# New Year Tree

## 题面翻译

- 给出一棵 $n$ 个节点的树，根节点为 $1$。每个节点上有一种颜色 $c_i$。$m$ 次操作。操作有两种：
	1. `1 u c`：将以 $u$ 为根的子树上的所有节点的颜色改为 $c$。
    2. `2 u`：询问以 $u$ 为根的子树上的所有节点的颜色数量。
- $1\le n,m\le 4\times 10^5$，$1\le c_i,c\le 60$。

## 题目描述

The New Year holidays are over, but Resha doesn't want to throw away the New Year tree. He invited his best friends Kerim and Gural to help him to redecorate the New Year tree.

The New Year tree is an undirected tree with $ n $ vertices and root in the vertex $ 1 $ .

You should process the queries of the two types:

1. Change the colours of all vertices in the subtree of the vertex $ v $ to the colour $ c $ .
2. Find the number of different colours in the subtree of the vertex $ v $ .

## 输入格式

The first line contains two integers $ n, m $ ( $ 1<=n, m<=4·10^{5} $ ) — the number of vertices in the tree and the number of the queries.

The second line contains $ n $ integers $ c_{i} $ ( $ 1<=c_{i}<=60 $ ) — the colour of the $ i $ -th vertex.

Each of the next $ n-1 $ lines contains two integers $ x_{j}, y_{j} $ ( $ 1<=x_{j}, y_{j}<=n $ ) — the vertices of the $ j $ -th edge. It is guaranteed that you are given correct undirected tree.

The last $ m $ lines contains the description of the queries. Each description starts with the integer $ t_{k} $ ( $ 1<=t_{k}<=2 $ ) — the type of the $ k $ -th query. For the queries of the first type then follows two integers $ v_{k}, c_{k} $ ( $ 1<=v_{k}<=n, 1<=c_{k}<=60 $ ) — the number of the vertex whose subtree will be recoloured with the colour $ c_{k} $ . For the queries of the second type then follows integer $ v_{k} $ ( $ 1<=v_{k}<=n $ ) — the number of the vertex for which subtree you should find the number of different colours.

## 输出格式

For each query of the second type print the integer $ a $ — the number of different colours in the subtree of the vertex given in the query.

Each of the numbers should be printed on a separate line in order of query appearing in the input.

## 样例 #1

### 样例输入 #1

```
7 10
1 1 1 1 1 1 1
1 2
1 3
1 4
3 5
3 6
3 7
1 3 2
2 1
1 4 3
2 1
1 2 5
2 1
1 6 4
2 1
2 2
2 3
```

### 样例输出 #1

```
2
3
4
5
1
2
```

## 样例 #2

### 样例输入 #2

```
23 30
1 2 2 6 5 3 2 1 1 1 2 4 5 3 4 4 3 3 3 3 3 4 6
1 2
1 3
1 4
2 5
2 6
3 7
3 8
4 9
4 10
4 11
6 12
6 13
7 14
7 15
7 16
8 17
8 18
10 19
10 20
10 21
11 22
11 23
2 1
2 5
2 6
2 7
2 8
2 9
2 10
2 11
2 4
1 12 1
1 13 1
1 14 1
1 15 1
1 16 1
1 17 1
1 18 1
1 19 1
1 20 1
1 21 1
1 22 1
1 23 1
2 1
2 5
2 6
2 7
2 8
2 9
2 10
2 11
2 4
```

### 样例输出 #2

```
6
1
3
3
2
1
2
3
5
5
1
2
2
1
1
1
2
3
```

## 题解
首先我们可以通过我们的 dfs 序序来快速的把我们的子树所有节点颜色都修改为 C。

之后，我们又可以通过我们的状态压缩来求出我们一个字数上的所有的颜色，两者加在一起就是我们的这一题。

```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;




//---------------求dfs序---------------// 
int tot=0;//记录序号的变量 
int pos[400040];//时间戳所对应的点 id->编号 
int in[400040];//入点时间戳 
int out[400040];//出点时间戳 
struct edge{
	int to,next;
}e[800080];//存储树结构 
int eid=0;//存储树结构 
int head[400040];//存储树结构 
void insert(int u,int v){
	eid++;
	e[eid].to=v;
	e[eid].next=head[u];
	head[u]=eid;
}//加边函数 
void dfs(int x,int fa){//用dfs序将树形结构转为线性结构 
	tot++;
	in[x]=tot;
	pos[tot]=x;
	for(int i=head[x];i+1;i=e[i].next){
		int k=e[i].to;
		if(k==fa)continue;
		dfs(k,x);
	}
	out[x]=tot;//其实我们out记录的是该子树中dfs序最大结点的dfs序，所以tot不加一 
	return;
} 


//------------------线段树----------------// 


struct tree{
	long long sum;
	long long tag;//记录要修改为哪个颜色 
	int l,r;
}t[1600040];
int c[400040];

void pushup(int rt){
	t[rt].sum=t[rt<<1].sum|t[rt<<1|1].sum;
	return;
}
void pushdown(int rt){
	if(t[rt].tag!=0){//或运算不像区间和，这里0是影响答案的 
		t[rt<<1].sum=t[rt].tag;
		t[rt<<1].tag=t[rt].tag;
		t[rt<<1|1].sum=t[rt].tag;
		t[rt<<1|1].tag=t[rt].tag;
		t[rt].tag=0;
	}	
	return;
}
void build(int rt,int l,int r){
	t[rt].l=l;
	t[rt].r=r;
	if(l==r){
		t[rt].sum=(long long)1<<(c[pos[l]]);//
		t[rt].tag=0;
		return;
	}
	int mid=(l+r)>>1;
	build(rt<<1,l,mid);
	build(rt<<1|1,mid+1,r);
	pushup(rt);
	return;
}
void modify(int rt,int l,int r,int p){//将dfs序从l到r这一区间的颜色改为p  注意状压 
	if(t[rt].l>=l&&t[rt].r<=r){
		t[rt].sum=(long long)1<<p;//
		t[rt].tag=(long long)1<<p;//
		return ;
	}
	int mid=(t[rt].l+t[rt].r)>>1;
	pushdown(rt);
	if(l<=mid)modify(rt<<1,l,r,p);
	if(r>mid)modify(rt<<1|1,l,r,p);
	pushup(rt);
	return;
}
long long query(int rt,int l,int r){//查询dfs序从l到r的颜色个数 
	if(t[rt].l>=l&&t[rt].r<=r){
		return t[rt].sum;
	}
	pushdown(rt);
	int mid=(t[rt].l+t[rt].r)>>1;
	long long rec=0;
	if(l<=mid)rec|=query(rt<<1,l,r);
	if(r>mid)rec|=query(rt<<1|1,l,r);
	pushup(rt);
	return rec;
}
// 
int n,m;
long long lowbit(long long x){
	return x&(-x);
}
int main(){
	memset(head,-1,sizeof(head));
	n=read();
	m=read();
	for(int i=1;i<=n;i++){
		c[i]=read();
	}
	for(int i=1;i<n;i++){
		int x,y;
		x=read();
		y=read();
		insert(x,y);
		insert(y,x);
	}
	dfs(1,0);
	build(1,1,n);
	for(int i=1;i<=m;i++){
		int a;
		a=read();
		if(a==1){
			int x,y;
			x=read();
			y=read();
			modify(1,in[x],out[x],y);
			//cout<<query(1,in[x],in[x])<<endl;
		}
		else{
			int x;
			x=read();
			long long num=query(1,in[x],out[x]);
			int ans=0;
			//cout<<num<<endl;
			for(long long j=num;j>0;j-=lowbit(j))ans++;
			cout<<ans<<endl;
		}
	}
	return 0;
}
```