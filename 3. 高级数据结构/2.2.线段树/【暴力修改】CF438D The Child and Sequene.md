# The Child and Sequence

## 题面翻译

### 题目描述

有一个长度为 $n$ 的数列 $\{a_n\}$ 和 $m$ 次操作，操作内容如下：

1. 格式为 `1 l r`，表示求 $\sum \limits _{i=l}^{r} a_i$ 的值并输出。
2. 格式为 `2 l r x`，表示对区间 $[l,r]$ 内每个数取模，模数为 $x$。
3. 格式为 `3 k x`，表示将 $a_k$ 修改为 $x$。

$1 \le n,m \le 10^5$，$1\le l,r,k,x \le 10^9$。

### 输入格式

第一行两个正整数 $n,m$，分别表示数列长度和操作次数。

第二行给出长为 $n$ 的数列 $\{a_n\}$。

接下来 $m$ 行，每行表示一次操作。

### 输出格式

对于每个操作 $1$，输出答案，每行一个整数。答案可能大于 $2^{31}-1$。

## 题目描述

At the children's day, the child came to Picks's house, and messed his house up. Picks was angry at him. A lot of important things were lost, in particular the favorite sequence of Picks.

Fortunately, Picks remembers how to repair the sequence. Initially he should create an integer array $ a[1], a[2],..., a[n] $ . Then he should perform a sequence of $ m $ operations. An operation can be one of the following:

1. Print operation $ l, r $ . Picks should write down the value of ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF438D/876beae330acc049f49836f16bfed34538663977.png).
2. Modulo operation $ l, r, x $ . Picks should perform assignment $ a[i]=a[i] mod x $ for each $ i $ $ (l<=i<=r) $ .
3. Set operation $ k, x $ . Picks should set the value of $ a[k] $ to $ x $ (in other words perform an assignment $ a[k]=x $ ).

Can you help Picks to perform the whole sequence of operations?

## 输入格式

The first line of input contains two integer: $ n, m $ $ (1<=n, m<=10^{5}) $ . The second line contains $ n $ integers, separated by space: $ a[1], a[2],..., a[n] (1<=a[i]<=10^{9}) $ — initial value of array elements.

Each of the next $ m $ lines begins with a number $ type $ ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF438D/30ecae3e73b4644470ddff9dcee5b218291a621f.png).

- If $ type=1 $ , there will be two integers more in the line: $ l, r (1<=l<=r<=n) $ , which correspond the operation 1.
- If $ type=2 $ , there will be three integers more in the line: $ l, r, x (1<=l<=r<=n; 1<=x<=10^{9}) $ , which correspond the operation 2.
- If $ type=3 $ , there will be two integers more in the line: $ k, x (1<=k<=n; 1<=x<=10^{9}) $ , which correspond the operation 3.

## 输出格式

For each operation 1, please print a line containing the answer. Notice that the answer may exceed the 32-bit integer.

## 样例 #1

### 样例输入 #1

```
5 5
1 2 3 4 5
2 3 5 4
3 3 5
1 2 5
2 1 3 3
1 1 3
```

### 样例输出 #1

```
8
5
```

## 样例 #2

### 样例输入 #2

```
10 10
6 9 6 7 6 1 10 10 9 5
1 3 9
2 7 10 9
2 5 10 8
1 4 7
3 3 7
2 7 9 9
1 2 4
1 6 6
1 5 9
3 1 10
```

### 样例输出 #2

```
49
15
23
1
9
```

## 提示

Consider the first testcase:

- At first, $ a={1,2,3,4,5} $ .
- After operation $ 1 $ , $ a={1,2,3,0,1} $ .
- After operation $ 2 $ , $ a={1,2,5,0,1} $ .
- At operation $ 3 $ , $ 2+5+0+1=8 $ .
- After operation $ 4 $ , $ a={1,2,2,0,1} $ .
- At operation $ 5 $ , $ 1+2+2=5 $ .

## 题解
我们这一题的难点就在于我们的区间取模我们这一个操作不具有可加性，但是我们有下面一个性质：$x \text{ mod p}< \frac{x}{2}$,所以我们取模最多也就取模 $\log x$ 次，我们不妨记录我们的**区间最大值**，如果我们的区间最大值 $<p$，我们就直接返回，这一题其实类似于我们的花神游历各国，都是因为我们的修改操作不能传递下去，所以我们就要利用我们修改存在的性质，来加速我们的修改操作。

```cpp
#include<bits/stdc++.h>
#define MAXN 100005
#define reg register
#define inl inline
#define int long long
using namespace std;
int n,q,a[MAXN];
struct SegmentTree
{
	int t[MAXN<<2],maxn[MAXN<<2];
	inl void PushUp(reg int rt)
	{
		t[rt]=t[rt<<1]+t[rt<<1|1];
		maxn[rt]=max(maxn[rt<<1],maxn[rt<<1|1]);
	}
	void Build(reg int rt,reg int l,reg int r)
	{
		if(l==r)
		{
			t[rt]=maxn[rt]=a[l];
			return;
		}
		reg int mid=l+r>>1;
		Build(rt<<1,l,mid);
		Build(rt<<1|1,mid+1,r);
		PushUp(rt);
	}
	void ModifyMod(reg int rt,reg int l,reg int r,reg int tl,reg int tr,reg int p)
	{
		if(maxn[rt]<p) return;
		if(l==r)
		{
			t[rt]%=p;
			maxn[rt]%=p;
			return;
		}
		reg int mid=l+r>>1;
		if(tl<=mid) ModifyMod(rt<<1,l,mid,tl,tr,p);
		if(tr>mid) ModifyMod(rt<<1|1,mid+1,r,tl,tr,p);
		PushUp(rt);
	}
	void Modify(reg int rt,reg int l,reg int r,reg int pos,reg int val)
	{
		if(l==r)
		{
			t[rt]=maxn[rt]=val;
			return;
		}
		reg int mid=l+r>>1;
		if(pos<=mid) Modify(rt<<1,l,mid,pos,val);
		else Modify(rt<<1|1,mid+1,r,pos,val);
		PushUp(rt);
	}
	int Query(reg int rt,reg int l,reg int r,reg int tl,reg int tr)
	{
		if(tl<=l && r<=tr) return t[rt];
		reg int mid=l+r>>1,res=0;
		if(tl<=mid) res+=Query(rt<<1,l,mid,tl,tr);
		if(tr>mid) res+=Query(rt<<1|1,mid+1,r,tl,tr);
		return res;
	}
}T;
signed main()
{
	scanf("%lld %lld",&n,&q);
	for(reg int i=1;i<=n;i++) scanf("%lld",&a[i]);
	T.Build(1,1,n);
	while(q--)
	{
		reg int opt,x,y,z;
		scanf("%lld %lld %lld",&opt,&x,&y);
		if(opt==1) printf("%lld\n",T.Query(1,1,n,x,y));
		else if(opt==2)
		{
			scanf("%lld",&z);
			T.ModifyMod(1,1,n,x,y,z);
		}
		else T.Modify(1,1,n,x,y);
	}
	return 0;
}
```