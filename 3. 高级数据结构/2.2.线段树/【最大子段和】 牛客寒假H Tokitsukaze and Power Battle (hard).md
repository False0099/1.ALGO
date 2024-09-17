**easy 与 hard 的唯一区别是** $a_i$ **与** $y$ **的范围。**  
  
有一块长长的铁，铁上写着 $n$ 个整数 $a_1, a_2, \ldots, a_n$。  
  
现在有 $q$ 次操作：  

-    $1$ $x$ $y$：把铁上第 $x$ 个数字 $a_x$ 修改为 $y$。
-    $2$ $l$ $r$: Tokitsukaze 将进行一场战斗。**假设**这块铁被截去前后，只剩下中间第 $l$ 个数字到第 $r$ 个数字这一段。Tokitsukaze 从中选择一段 $[i,j]$ ($l \leq i < j \leq r$)，再选择一个切断点 $x$ 将铁分成 $[i,x]$, $[x+1,j]$ 两段 ($i \leq x < j$)。Tokitsukaze 获得 $[i,x]$ 这一段，对手获得 $[x+1,j]$ 这一段。之后他们把获得的铁锻造成剑，剑的力量为铁上的数字之和。Tokitsukaze 想知道她锻造出的剑与对手的剑的力量的差值最大是多少。**注意：Tokitsukaze 与对手必须一人一段，不能全拿也不能全给对手。**

## 输入
第一行包含一个整数 $T$ ($1 \leq T \leq 2.5\cdot 10^5$)，表示 $T$ 组测试数据。  
  
对于每组测试数据：  
  
第一行包含两个整数 $n$, $q$ ($2 \leq n \leq 5\cdot 10^5$, $1 \leq q \leq 5\cdot 10^5$)，表示铁分为 $n$ 段，操作次数为 $q$。  
  
第二行包含 $n$ 个整数 $a_1, a_2, \ldots, a_n$ ($-10^9 \leq a_i \leq 10^9$)，表示铁上的数字。  
  
接下来 $q$ 行，每行三个整数按照以下格式：  

-    $1$ $x$ $y$ ($1 \leq x \leq n$; $-10^9 \leq y \leq 10^9$)
-    $2$ $l$ $r$ ($1 \leq l < r \leq n$)

  
保证 $\sum n$, $\sum q$ 都不超过 $5 \cdot 10^5$。

## 输出：
对于每个操作 $2$，输出一个整数，表示 Tokitsukaze 锻造出的剑与对手的剑最大力量差值。

## 示例：
```
2
10 4
3 2 3 -10 5 -1 8 -9 3 5
2 4 9
1 4 10
2 4 9
2 3 4
10 10
7 2 1 -9 8 6 -3 -7 -4 -1
1 10 -4
2 7 9
1 9 7
2 5 8
2 7 8
1 2 -9
2 2 10
1 9 -6
1 6 -9
2 6 7
```


```
21
31
-7
8
24
4
24
-6
```
## 题解
我们本题的一个关键性质在于：我们的左侧一定是给自己的，右侧的那一段一定是给对手的。

我们考虑我们之前存在的区间最大子段和来进行操作：

首先考虑答案的组成，按减号在哪段进行讨论：

1. 左边包含右端点的最大答案(减号在这整段中)-右边包含左端点的最小子段和（$\pm,-$ ）
    
2. 左边包含右端点的最大子段和+右边包含左端点的最大答案(减号在这整段中) $(+,\pm)$
    
3. 减号就是中间的减号：左边包含右端点的最大子段和-右边包含左端点的最小子段和 $(+,-)$
    

于是，我们就可以考虑维护我们上面提到的几个变量：
1. 包含右端点的最大答案
2. 包含左端点的最小子段和
3. 包含右端点的最大子段和
4. 包含左端点的最大答案
5. 答案

我们对每个节点的初始化按照下面的操作来进行：
```
tr[u].a=-114514;
tr[u].b=a[i];
tr[u].c=a[i];
tr[u].d=-114514;
```

Pushup 函数：
```cpp
tr[u].a=tr[u<<1].c+tr[u<<1|1].d
tr[u].a=tr[u<<1].a-tr[u<<1|1].b;
tr[u].a=tr[u<<1].
tr[u].b=tr[u<<1].b+(tr[u<<1|1].b)?
tr[u].c=tr[u<<1|1].c+(tr[u<<1].c)?
tr[u].d=tr[u<<1].c+(tr[u<<1|1].b)?
```

之后，我们就可以通过线段树来进行 $o(\log n)$ 的单词查询

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll LLINF=0x3f3f3f3f3f3f3f3fLL;
const int MAX=5e5+10;
struct Segment_Tree
{
	#define type ll
	#define ls (id<<1)
	#define rs (id<<1|1)
	struct node
	{
		type sum,rmx,lmn,lans,rans,segans,ans;
		void init()
		{
			rmx=lans=rans=segans=ans=-LLINF;
			lmn=LLINF;
			sum=0;
		}
	}t[MAX<<2],null_node;
	int n,ql,qr;
	type a[MAX],qv;
	node merge_node(node x,node y)
	{
		node res;
		res.sum=x.sum+y.sum;
		res.rmx=max(y.rmx,x.rmx+y.sum);
		res.lmn=min(x.lmn,x.sum+y.lmn);
		res.lans=max({x.lans,x.sum+y.lans,x.sum-y.lmn,x.segans-y.lmn});
		res.rans=max({y.rans,x.rans-y.sum,x.rmx-y.sum,x.rmx+y.segans});
		res.segans=max({x.segans-y.sum,x.sum+y.segans,x.sum-y.sum});
		res.ans=max({x.ans,y.ans,x.rmx-y.lmn,x.rans-y.lmn,x.rmx+y.lans});
		return res;
	}
	void pushup(int id){t[id]=merge_node(t[ls],t[rs]);}
	void build(int l,int r,int id)
	{
		t[id].init();
		if(l==r)
		{
			t[id]={a[l],a[l],a[l],-LLINF,-LLINF,-LLINF,-LLINF};
			return;
		}
		int mid=(l+r)>>1;
		build(l,mid,ls);
		build(mid+1,r,rs);
		pushup(id);
	}
	void update(int l,int r,int id)
	{
		if(l>=ql&&r<=qr)
		{
			t[id]={qv,qv,qv,-LLINF,-LLINF,-LLINF,-LLINF};
			return;
		}
		int mid=(l+r)>>1;
		if(ql<=mid) update(l,mid,ls);
		if(qr>mid) update(mid+1,r,rs);
		pushup(id);
	}
	node query(int l,int r,int id)
	{
		if(l>=ql&&r<=qr) return t[id];
		int mid=(l+r)>>1;
		if(qr<=mid) return query(l,mid,ls);
		if(ql>mid) return query(mid+1,r,rs);
		return merge_node(query(l,mid,ls),query(mid+1,r,rs));
	}
	void build(int _n)
	{
		n=_n;
		build(1,n,1);
		null_node.init();
	}
	void upd(int l,int r,type v)
	{
		if(l>r) return;
		ql=l;
		qr=r;
		qv=v;
		update(1,n,1);
	}
	type ask(int l,int r)
	{
		if(l>r) return null_node.ans;
		ql=l;
		qr=r;
		return query(1,n,1).ans;
	}
	#undef type
	#undef ls
	#undef rs
}tr;
int main()
{
	int T,n,q,i,op,x,y;
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&n,&q);
		for(i=1;i<=n;i++) scanf("%lld",&tr.a[i]);
		tr.build(n);
		while(q--)
		{
			scanf("%d%d%d",&op,&x,&y);
			if(op==1) tr.upd(x,x,y);
			else printf("%lld\n",tr.ask(x,y));
		}
	}
	return 0;
}
/*
2
10 1
7 0 6 6 8 2 -6 3 -9 1
2 2 10
20 1
2 -4 10 5 9 -1 2 1 -9 7 -9 -5 4 4 -1 -3 0 -5 7 -10
2 3 12
*/
```