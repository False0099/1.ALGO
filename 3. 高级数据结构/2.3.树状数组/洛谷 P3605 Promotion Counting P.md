# [USACO 17 JAN] Promotion Counting P

## 题目描述

奶牛们又一次试图创建一家创业公司，还是没有从过去的经验中吸取教训——牛是可怕的管理者！

为了方便，把奶牛从 $1\sim n$ 编号，把公司组织成一棵树，1 号奶牛作为总裁（这棵树的根节点）。除了总裁以外的每头奶牛都有一个单独的上司（它在树上的 “双亲结点”）。  

所有的第 $i$ 头牛都有一个不同的能力指数 $p_i$，描述了她对其工作的擅长程度。如果奶牛 $i$ 是奶牛 $j$ 的祖先节点，那么我们我们把奶牛 $j$ 叫做 $i$ 的下属。

不幸地是，奶牛们发现经常发生一个上司比她的一些下属能力低的情况，在这种情况下，上司应当考虑晋升她的一些下属。你的任务是帮助奶牛弄清楚这是什么时候发生的。简而言之，对于公司的中的每一头奶牛 $i$，请计算其下属 $j$ 的数量满足 $p_j > p_i$。

## 输入格式

输入的第一行包括一个整数 $n$。

接下来的 $n$ 行包括奶牛们的能力指数 $p_1,p_2 \dots p_n$。保证所有数互不相同。

接下来的 $n-1$ 行描述了奶牛 $2 \sim n$ 的上司的编号。再次提醒，1 号奶牛作为总裁，没有上司。

## 输出格式

输出包括 $n$ 行。输出的第 $i$ 行应当给出有多少奶牛 $i$ 的下属比奶牛 $i$ 能力高。

## 样例 #1

### 样例输入 #1

```
5
804289384
846930887
681692778
714636916
957747794
1
1
2
3
```

### 样例输出 #1

```
2
0
1
0
0
```

## 提示

对于 $100\%$ 的数据，$1\le n \le 10^5$，$1 \le p_i \le 10^9$。

## 题解
我们这一题，需要先构建出我们的关系树，然后再对我们的关系数构建一个 dfs 序，之后再在我们的 dfs 序上维护我们的树状数组，于是我们原来的问题都变成了一维求逆序对的问题。

只有后续遍历能保证在最后的 DFS 序中，一个节点的子孙都会在该节点的前面，因为我们对子孙进行查询，而子孙又是一段连续的区间。但是并不是所有在根节点之后的就都是他的子孙，我们子孙需要统计我们的字数大小，只有在这个大小内的才是我们的子树部分。

事实上还有一种解法，如果我们对节点和他的 DFS 序做了一一映射，即我们可以既通过节点本身得到他的 DFS 序位置，特可以根据 DFS 位置得到该处的节点，我们只要维护一个节点的上一个兄弟。


```cpp
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=1e5+10;
int a[MAXN],b[MAXN],ord[MAXN];
int n;
struct Cow{
	int p,ord,num;
	bool operator<(Cow& c2)const{
		return p<c2.p;
	}
}cow[MAXN];
struct Edge{
	int u,v;
}edge[MAXN];
int first[MAXN],next[MAXN],tot;
int past[MAXN],size[MAXN],tot2,m[MAXN];
int ans[MAXN];
int tree[MAXN];
void addedge(int u,int v){
	tot++;
	edge[tot].u = u;edge[tot].v = v;
	next[tot] = first[u];
	first[u] = tot;
}
int dfs(int u){
	size[u] = 1;
	for(int j=first[u];j;j=next[j]){
		int v=edge[j].v;
		size[u] += dfs(v);
	}
	past[++tot2] = u;
	m[u] = tot2; //映射 
	return size[u];
}
inline int lowbit(int x){
	return x & (-x);
}
inline void update(int x,int value){
	while(x<=n){
		tree[x] += value;
		x+=lowbit(x);
	}
}
inline int query(int x){
	int sum = 0;
	while(x>=1){
		sum += tree[x];
		x-=lowbit(x);
	}
	return sum;
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		b[i] = a[i];
	} 
	sort(b+1,b+1+n);
	for(int i=1;i<=n;i++){
		//离散化
		ord[i] = lower_bound(b+1,b+1+n,a[i])-b; 
	}
	for(int i=1;i<=n;i++){
		cow[i] = (Cow){a[i],ord[i],i};
	}
	//建树
	for(int i=2;i<=n;i++){
		int fa;
		cin>>fa;
		addedge(fa,i);
	} 
	//后序 + 统计子树大小 
	dfs(1);
	sort(cow+1,cow+1+n);//排序保证我们大小有序
	for(int i=n;i>=1;i--){//第一只出现的肯定是最大的
		int now = m[cow[i].num],s = size[cow[i].num]-1; //出现了就说明比自己抢
		//查找后序上[now-s,now)这一段的个数，出现了就比自己强
		ans[cow[i].num] = query(now)-query(now-s-1);
		//加入
		update(now,1);//把当前的奶牛的对应树编号++ 
	}
	for(int i=1;i<=n;i++){
		printf("%d\n",ans[i]);
	}
	return 0;
} 
```
```