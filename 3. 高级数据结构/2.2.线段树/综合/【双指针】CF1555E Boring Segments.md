# Boring Segments

## 题面翻译

在一个 $[1,m]$ 的数轴上有 n 条线段，第 i 条覆盖了 $[l_i,r_i]$ 的区间，权值为 $w_i$ ，你的任务是从这些线段中选出若干条首尾相接线段覆盖整个数轴，使得这些线段权值极差最小化，输出这个极差

首尾相接的定义是，假设你有机会从同一条线段覆盖的任意两个点中移动，如果你可以从位置 1 出发，经过一些线段到达位置 m ，就称为这些线段首尾相接

## 题目描述

You are given $ n $ segments on a number line, numbered from $ 1 $ to $ n $ . The $ i $ -th segments covers all integer points from $ l_i $ to $ r_i $ and has a value $ w_i $ .

You are asked to select a subset of these segments (possibly, all of them). Once the subset is selected, it's possible to travel between two integer points if there exists a selected segment that covers both of them. A subset is good if it's possible to reach point $ m $ starting from point $ 1 $ in arbitrary number of moves.

The cost of the subset is the difference between the maximum and the minimum values of segments in it. Find the minimum cost of a good subset.

In every test there exists at least one good subset.

## 输入格式

The first line contains two integers $ n $ and $ m $ ( $ 1 \le n \le 3 \cdot 10^5 $ ; $ 2 \le m \le 10^6 $ ) — the number of segments and the number of integer points.

Each of the next $ n $ lines contains three integers $ l_i $ , $ r_i $ and $ w_i $ ( $ 1 \le l_i < r_i \le m $ ; $ 1 \le w_i \le 10^6 $ ) — the description of the $ i $ -th segment.

In every test there exists at least one good subset.

## 输出格式

Print a single integer — the minimum cost of a good subset.

## 样例 #1

### 样例输入 #1

```
5 12
1 5 5
3 4 10
4 10 6
11 12 5
10 12 3
```

### 样例输出 #1

```
3
```

## 样例 #2

### 样例输入 #2

```
1 10
1 10 23
```

### 样例输出 #2

```
0
```


## 题解
我们本题因为我们要最小化我们的极差，我们首先就可以先对我们的线段进行一个排序，然后我们再把每一个线段都加进去，然后我们每一次贪心的 check，如果我们把我们的端点删除能否满足条件，如果能我们就删，否则我们就不删。

```cpp
```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
inline int read(){
	int x=0; char c=getchar();
	while(!isdigit(c)) c=getchar();
	while(isdigit(c)) x=x*10+(c^'0'),c=getchar();
	return x;
}
const int maxn=3e5+10;
const int maxm=1e6+10;
struct Node{
	int l,r,dat,tag;
}tr[maxm*4];
inline void pushup(int x){
	tr[x].dat=min(tr[x<<1].dat,tr[x<<1|1].dat);
}
inline void pushdown(int x){
	if(tr[x].tag){
		tr[x<<1].dat+=tr[x].tag,tr[x<<1].tag+=tr[x].tag;
		tr[x<<1|1].dat+=tr[x].tag,tr[x<<1|1].tag+=tr[x].tag;
		tr[x].tag=0;
	}
}
void build(int x,int l,int r){
	tr[x].l=l,tr[x].r=r,tr[x].dat=tr[x].tag=0;
	if(l==r) return;
	int mid=l+r>>1;
	build(x<<1,l,mid),build(x<<1|1,mid+1,r); 
}
void modify(int x,int l,int r,int v){
	if(l<=tr[x].l&&r>=tr[x].r){
		tr[x].dat+=v,tr[x].tag+=v;
		return;
	}
	pushdown(x);
	int mid=tr[x].l+tr[x].r>>1;
	if(l<=mid) modify(x<<1,l,r,v);
	if(r>mid) modify(x<<1|1,l,r,v);
	pushup(x);
}
int n,m;
struct Segment{
	int l,r,w;
	bool operator<(const Segment &x)const{
		return w<x.w;
	}
}s[maxn];
int main(){
	n=read(),m=read();
	for(int i=1;i<=n;i++) s[i].l=read(),s[i].r=read()-1,s[i].w=read();
	sort(s+1,s+n+1);
	build(1,1,m-1);
	int ans=0x3f3f3f3f;
	for(int l=1,r=0;l<=n;l++){
		while(!tr[1].dat){
			if(++r>n){
				printf("%d\n",ans);
				return 0;
			}
			modify(1,s[r].l,s[r].r,1);
		}
		ans=min(ans,s[r].w-s[l].w);
		modify(1,s[l].l,s[l].r,-1);
	}
	printf("%d\n",ans);
	return 0;
}
```
```