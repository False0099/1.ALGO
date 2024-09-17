**easy 与 hard 的唯一区别是** $a_i$ **与** $y$ **的范围。**  
  
有一块长长的铁，铁上写着 $n$ 个整数 $a_1, a_2, \ldots, a_n$。  
  
现在有 $q$ 次操作：  

-    $1$ $x$ $y$：把铁上第 $x$ 个数字 $a_x$ 修改为 $y$。
-    $2$ $l$ $r$: Tokitsukaze 将进行一场战斗。**假设**这块铁被截去前后，只剩下中间第 $l$ 个数字到第 $r$ 个数字这一段。Tokitsukaze 从中选择一段 $[i,j]$ ($l \leq i < j \leq r$)，再选择一个切断点 $x$ 将铁分成 $[i,x]$, $[x+1,j]$ 两段 ($i \leq x < j$)。Tokitsukaze 获得 $[i,x]$ 这一段，对手获得 $[x+1,j]$ 这一段。之后他们把获得的铁锻造成剑，剑的力量为铁上的数字之和。Tokitsukaze 想知道她锻造出的剑与对手的剑的力量的差值最大是多少。**注意：Tokitsukaze 与对手必须一人一段，不能全拿也不能全给对手。**

## 输入
第一行包含一个整数 $T$ ($1 \leq T \leq 2.5\cdot 10^5$)，表示 $T$ 组测试数据。  
  
对于每组测试数据：  
  
第一行包含两个整数 $n$, $q$ ($2 \leq n \leq 5\cdot 10^5$, $1 \leq q \leq 5\cdot 10^5$)，表示铁分为 $n$ 段，操作次数为 $q$。  
  
第二行包含 $n$ 个整数 $a_1, a_2, \ldots, a_n$ ($0 \leq a_i \leq 10^9$)，表示铁上的数字。  
  
接下来 $q$ 行，每行三个整数按照以下格式：  

-    $1$ $x$ $y$ ($1 \leq x \leq n$; $0 \leq y \leq 10^9$)
-    $2$ $l$ $r$ ($1 \leq l < r \leq n$)

  
保证 $\sum n$, $\sum q$ 都不超过 $5 \cdot 10^5$。


## 输出
对于每个操作 $2$，输出一个整数，表示 Tokitsukaze 锻造出的剑与对手的剑最大力量差值。

## 示例：
输入
--

 2 10 4 3 2 3 10 5 1 8 9 3 5 2 4 9 1 9 100 2 4 9 2 3 4 10 10 7 2 1 9 8 6 3 7 4 1 1 10 4 2 7 9 1 9 7 2 5 8 2 7 8 1 2 9 2 2 10 1 9 6 1 6 9 2 6 7

```
2
10 4
3 2 3 10 5 1 8 9 3 5
2 4 9
1 9 100
2 4 9
2 3 4
10 10
7 2 1 9 8 6 3 7 4 1
1 10 4
2 7 9
1 9 7
2 5 8
2 7 8
1 2 9
2 2 10
1 9 6
1 6 9
2 6 7
```

输出

 30 15 -7 6 11 -4 46 6

说明：
第一组测试数据：  
  
当前铁上的数字为 $[3,2,3,10,5,1,8,9,3,5]$。  
  
第 $1$ 个操作选择 $[4,9]$ 这一段，Tokitsukaze 拿走 $[4,8]$，对手拿走 $[9,9]$，差值为 $(10+5+1+8+9)-(3)=30$；  
  
第 $2$ 个操作后，铁上的数字变为 $[3,2,3,10,5,1,8,9,100,5]$；  
  
第 $3$ 个操作选择 $[4,8]$ 这一段，Tokitsukaze 拿走 $[4,7]$，对手拿走 $[8,8]$，差值为 $(10+5+1+8)-(9)=15$；  
  
第 $4$ 个操作由于不能全拿或者全给对手，所以没得选，只能选择 $[3,4]$ 这一段，Tokitsukaze 只能拿走 $[3,3]$，对手拿走 $[4,4]$，差值为 $3-10=-7$。


## 题解
我们这一题的关键在于利用我们的题目本身的性质：
因为我们有：我们的数字是非负的，所以我们就可以有下面的贪心思路：
我们每一次左端点 i 都固定为我们的 l，然后我们找到一个右端点，满足我们的条件。

而我们的右端点可以通过我们的一个公式来计算，我们考虑把我们的公式进行计算：
$$\begin{aligned}
&ه\:bit_{i}=\sum_{j=1}^{i}a_{j} \\
&\sum_{i=L}^{y-1}a_i-a_y \\
&=\sum_{i=L}^ya_i-2\cdot a_y \\
&=\sum_{i=1}^ya_i-\sum_{i=1}^{L-1}a_i-2\cdot a_y \\
&=bit_y-bit_{L-1}-2\cdot a_y
\end{aligned}$$
我们发现，我们这里，我们需要维护我们的一个 $sum[y]-2a_{y}$ 的最大值，然后我们的 $bit_{L-1}$ 就可以通过我们的一个单点查询得到我们的答案。

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
		type mx,sum;
		void init()
		{
			mx=-LLINF;
			sum=0;
		}
	}t[MAX<<2];
	int n,ql,qr,qop;
	type a[MAX],bit[MAX],tag[MAX<<2],qv;
	node merge(node x,node y)
	{
		node res;
		res.sum=x.sum+y.sum;
		res.mx=max(x.mx,y.mx);
		return res;
	}
	void pushup(int id){t[id]=merge(t[ls],t[rs]);}
	void pushdown(int l,int r,int id)
	{
		if(!tag[id]) return;
		t[ls].mx+=tag[id];
		t[rs].mx+=tag[id];
		tag[ls]+=tag[id];
		tag[rs]+=tag[id];
		tag[id]=0;
	}
	void build(int l,int r,int id)
	{
		tag[id]=0;
		t[id].init();
		if(l==r)
		{
			t[id].mx=bit[l]-2*a[l];
			t[id].sum=a[l];
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
			if(qop==1) t[id].sum=qv;
			else
			{
				t[id].mx+=qv;
				tag[id]+=qv;
			}
			return;
		}
		pushdown(l,r,id);
		int mid=(l+r)>>1;
		if(ql<=mid) update(l,mid,ls);
		if(qr>mid) update(mid+1,r,rs);
		pushup(id);
	}
	node query(int l,int r,int id)
	{
		if(l>=ql&&r<=qr) return t[id];
		pushdown(l,r,id);
		int mid=(l+r)>>1;
		if(qr<=mid) return query(l,mid,ls);
		if(ql>mid) return query(mid+1,r,rs);
		return merge(query(l,mid,ls),query(mid+1,r,rs));
	}
	void build(int _n){n=_n;build(1,n,1);}
	void upd(int l,int r,type v,int op)
	{
		ql=l;
		qr=r;
		qv=v;
		qop=op;
		update(1,n,1);
	}
	type ask_max(int l,int r)
	{
		ql=l;
		qr=r;
		return query(1,n,1).mx;
	}
	type ask_sum(int l,int r)
	{
		if(l>r) return type(0);
		ql=l;
		qr=r;
		return query(1,n,1).sum;
	}
	#undef type
	#undef ls
	#undef rs
}tr;
ll a[MAX];
int main()
{
	int T,n,q,i,op,x,y;
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&n,&q);
		tr.bit[0]=0;
		for(i=1;i<=n;i++)
		{
			scanf("%lld",&a[i]);
			tr.a[i]=a[i];
			tr.bit[i]=tr.bit[i-1]+a[i];
		}
		tr.build(n);
		while(q--)
		{
			scanf("%d%d%d",&op,&x,&y);
			if(op==1)
			{
				tr.upd(x,x,2*a[x]-2*y,2);
				tr.upd(x,n,y-a[x],2);
				a[x]=y;
				tr.upd(x,x,a[x],1);
			}
			else printf("%lld\n",tr.ask_max(x+1,y)-tr.ask_sum(1,x-1));
		}
	}
	return 0;
}

```