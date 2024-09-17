# Willem, Chtholly and Seniorious

## 题面翻译

【题面】
请你写一种奇怪的数据结构，支持：
- $1$  $l$  $r$  $x$ ：将 $[l,r]$ 区间所有数加上 $x$ 
- $2$  $l$  $r$  $x$ ：将 $[l,r]$ 区间所有数改成 $x$ 
- $3$  $l$  $r$  $x$ ：输出将 $[l,r]$ 区间从小到大排序后的第 $x$ 个数是的多少 (即区间第 $x$ 小，数字大小相同算多次，保证 $1\leq$  $x$  $\leq$  $r-l+1$  )
- $4$  $l$  $r$  $x$  $y$ ：输出 $[l,r]$ 区间每个数字的 $x$ 次方的和模 $y$ 的值 (即 ($\sum^r_{i=l}a_i^x$ ) $\mod y$ )

【输入格式】
这道题目的输入格式比较特殊，需要选手通过 $seed$ 自己生成输入数据。
输入一行四个整数 $n,m,seed,v_{max}$ （$1\leq $  $n,m\leq 10^{5}$  , $0\leq seed \leq 10^{9}+7$  $, 1\leq vmax \leq 10^{9} $ ）
其中 $n$ 表示数列长度，$m$ 表示操作次数，后面两个用于生成输入数据。
数据生成的伪代码如下
![]( https://cdn.luogu.org/upload/pic/13887.png )

其中上面的 op 指题面中提到的四个操作。

【输出格式】
对于每个操作 3 和 4，输出一行仅一个数。

## 题目描述

— Willem...

— What's the matter?

— It seems that there's something wrong with Seniorious...

— I'll have a look...





![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF896C/98774bbeb6d46d43baff377283b5b8c924efc206.png)

Seniorious is made by linking special talismans in particular order.

After over 500 years, the carillon is now in bad condition, so Willem decides to examine it thoroughly.

Seniorious has $ n $ pieces of talisman. Willem puts them in a line, the $ i $ -th of which is an integer $ a_{i} $ .

In order to maintain it, Willem needs to perform $ m $ operations.

There are four types of operations:

- $ 1\ l\ r\ x $ : For each $ i $ such that $ l<=i<=r $ , assign $ a_{i}+x $ to $ a_{i} $ .
- $ 2\ l\ r\ x $ : For each $ i $ such that $ l<=i<=r $ , assign $ x $ to $ a_{i} $ .
- $ 3\ l\ r\ x $ : Print the $ x $ -th smallest number in the index range $ [l, r] $ , i.e. the element at the $ x $ -th position if all the elements $ a_{i} $ such that $ l<=i<=r $ are taken and sorted into an array of non-decreasing integers. It's guaranteed that $ 1<=x<=r-l+1 $ .
- $ 4\ l\ r\ x\ y $ : Print the sum of the $ x $ -th power of $ a_{i} $ such that $ l<=i<=r $ , modulo $ y $ , i.e. ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF896C/78509e8cef6ae4ac71093ef3596987ee9ded5b23.png).

## 输入格式

The only line contains four integers $ n, m, seed, v_{max} $ ( $ 1<=n, m<=10^{5}, 0<=seed<10^{9}+7,1<=vmax<=10^{9} $ ).

The initial values and operations are generated using following pseudo code:
```
def rnd():

    ret = seed
    seed = (seed * 7 + 13) mod 1000000007
    return ret

for i = 1 to n:

    a[i] = (rnd() mod vmax) + 1

for i = 1 to m:

    op = (rnd() mod 4) + 1
    l = (rnd() mod n) + 1
    r = (rnd() mod n) + 1

    if (l > r): 
         swap(l, r)

    if (op == 3):
        x = (rnd() mod (r - l + 1)) + 1
    else:
        x = (rnd() mod vmax) + 1

    if (op == 4):
        y = (rnd() mod vmax) + 1
```
Here $ op $ is the type of the operation mentioned in the legend.

## 输出格式

For each operation of types $ 3 $ or $ 4 $ , output a line containing the answer.

## 样例 #1

### 样例输入 #1

```
10 10 7 9
```

### 样例输出 #1

```
2
1
0
3
```

## 样例 #2

### 样例输入 #2

```
10 10 9 9
```

### 样例输出 #2

```
1
1
3
3
```

## 提示

In the first example, the initial array is $ {8,9,7,2,3,1,5,6,4,8} $ .

The operations are:

- $ 2\ 6\ 7\ 9 $
- $ 1\ 3\ 10\ 8 $
- $ 4\ 4\ 6\ 2\ 4 $
- $ 1\ 4\ 5\ 8 $
- $ 2\ 1\ 7\ 1 $
- $ 4\ 7\ 9\ 4\ 4 $
- $ 1\ 2\ 7\ 9 $
- $ 4\ 5\ 8\ 1\ 1 $
- $ 2\ 5\ 7\ 5 $
- $ 4\ 3\ 10\ 8\ 5 $

## 题解


## 一、什么是珂朵莉树

珂朵莉树，又称Old Driver Tree(ODT)。是一种基于`std::set`的暴力数据结构。B站上有UESTC的[讲解视频](https://www.bilibili.com/video/av21651173)。

## 二、什么时候用珂朵莉树

关键操作：推平一段区间 (**区间赋值**），使一整段区间内的东西变得一样。保证**数据随机**。



## 三、珂朵莉树的初始化

这道题里，这样定义珂朵莉树的节点：

```
struct node
{
	int l,r;
	mutable LL v;
	node(int L, int R=-1, LL V=0):l(L), r(R), v(V) {}
	bool operator<(const node& o) const
	{
		return l < o.l;
	}
};
```

这样的一个节点表示$[l,r]$内的所有数都是v。需要注意的是`mutable`，意为易变的，不定的。它对`v`的修饰，使得我们可以在`add`操作中修改`v`的值。没有它的修饰会在`add`函数里导致CE。

我们把节点存在`set`里。

```
set<node> s;
```

像CF896C这道题就这样初始化。

```
cin>>n>>m>>seed>>vmax;
for (int i=1; i<=n; ++i)
{
	a[i] = (rnd() % vmax) + 1;
	s.insert(node(i,i,a[i]));
}
```

初始化完了？初始化完了。

## 四、珂朵莉树的核心操作：split

`split(pos)`操作是指将原来含有pos位置的节点分成两部分：$[l,pos−1]$和$[pos,r]$。

看这个操作的代码：

```
#define IT set<node>::iterator
IT split(int pos)
{
	IT it = s.lower_bound(node(pos));
	if (it != s.end() && it->l == pos) return it;
	--it;
	int L = it->l, R = it->r;
	LL V = it->v;
	s.erase(it);
	s.insert(node(L, pos-1, V));
	return s.insert(node(pos, R, V)).first;
}
```

一行一行来看。

```
#define IT set<node>::iterator
```

宏定义没什么好说的，记住NOI系列赛事不能用`auto`。`auto`一时爽，评测火葬场。

```
IT it = s.lower_bound(node(pos));
```

找到首个l不小于pos的节点。

```
if (it != s.end() && it->l == pos)
	return it;
```

如果无需`split`，直接返回。

```
--it;
```

否则pos一定在前一个区间中。

```
int L = it->l, R = it->r;
```

$[L,R]$就是要被分割的区间。

```
LL V = it->v;
```

取出这个节点的值。

```
s.erase(it);
```

删除原节点。

```
s.insert(node(L, pos-1, V));
```

插入前半段。

```
return s.insert(node(pos, R, V)).first;
```

插入后半段，返回后半段的迭代器。这里利用了`pair<iterator,bool> insert (const value_type& val)`的返回值。

## 五、珂朵莉树的推平操作：assign

要是只有`split`还不得复杂度爆炸？我们需要`assign`操作迅速减小`set`的规模。

```
void assign(int l, int r, LL val=0)
{
	IT itl = split(l),itr = split(r+1);
	s.erase(itl, itr);
	s.insert(node(l, r, val));
}
```

一些萌新可能没有见过`erase`的这种用法，你们应该学习一个。C++98中`void erase (iterator first, iterator last)`可删除$[first,last)$区间。这里就是把$[l,r+1)$内的部分推成一段。

珂朵莉树的复杂度是由`ass`♂`ign`保证的。由于数据随机，有1441​的操作为`assign`。`set`的大小快速下降，最终趋于logn，使得这种看似暴力无比的数据结构复杂度接近�mlogn。

## 六、其他操作：一个比一个暴力

区间加：

```
void add(int l, int r, LL val=1)
{
	IT itl = split(l),itr = split(r+1);
	for (; itl != itr; ++itl) itl->v += val;
}
```

分裂出来挨个加一下就行。

区间第k小：

```
LL rank(int l, int r, int k)
{
	vector<pair<LL, int> > vp;
	IT itl = split(l),itr = split(r+1);
	vp.clear();
	for (; itl != itr; ++itl)
		vp.push_back(pair<LL,int>(itl->v, itl->r - itl->l + 1));
	sort(vp.begin(), vp.end());
	for (vector<pair<LL,int> >::iterator it=vp.begin();it!=vp.end();++it)
	{
		k -= it->second;
		if (k <= 0) return it->first;
	}
	return -1LL;
}
```

暴力取出排序就好了，反正也没有多少段。

```
LL sum(int l, int r, int ex, int mod)
{
	IT itl = split(l),itr = split(r+1);
	LL res = 0;
	for (; itl != itr; ++itl)
		res = (res + (LL)(itl->r - itl->l + 1) * pow(itl->v, LL(ex), LL(mod))) % mod;
	return res;
}
```

暴力遍历，快速幂，然后加起来。

那么，这道题就可做了。而且我们交了一发，发现这玩意跑得完全不像暴力，最慢的点是500多ms。


```
#include<cstdio>
#include<set>
#include<vector>
#include<utility>
#include<algorithm>
#define IT set<node>::iterator

using std::set;
using std::vector;
using std::pair;

typedef long long LL;
const int MOD7 = 1e9 + 7;
const int MOD9 = 1e9 + 9;
const int imax_n = 1e5 + 7;

LL pow(LL a, LL b, LL mod)
{
	LL res = 1;
	LL ans = a % mod;
	while (b)
	{
		if (b&1) res = res * ans % mod;
		ans = ans * ans % mod;
		b>>=1;
	}
	return res;
}

struct node
{
	int l,r;
	mutable LL v;
	node(int L, int R=-1, LL V=0):l(L), r(R), v(V) {}
	bool operator<(const node& o) const
	{
		return l < o.l;
	}
};

set<node> s;

IT split(int pos)
{
	IT it = s.lower_bound(node(pos));
	if (it != s.end() && it->l == pos) return it;
	--it;
	int L = it->l, R = it->r;
	LL V = it->v;
	s.erase(it);
	s.insert(node(L, pos-1, V));
	return s.insert(node(pos, R, V)).first;
}

void add(int l, int r, LL val=1)
{
	IT itl = split(l),itr = split(r+1);
	for (; itl != itr; ++itl) itl->v += val;
}

void assign_val(int l, int r, LL val=0)
{
	IT itl = split(l),itr = split(r+1);
	s.erase(itl, itr);
	s.insert(node(l, r, val));
}

LL rank(int l, int r, int k)
{
	vector<pair<LL, int> > vp;
	IT itl = split(l),itr = split(r+1);
	vp.clear();
	for (; itl != itr; ++itl)
		vp.push_back(pair<LL,int>(itl->v, itl->r - itl->l + 1));
	std::sort(vp.begin(), vp.end());
	for (vector<pair<LL,int> >::iterator it=vp.begin();it!=vp.end();++it)
	{
		k -= it->second;
		if (k <= 0) return it->first;
	}
	return -1LL;
}

LL sum(int l, int r, int ex, int mod)
{
	IT itl = split(l),itr = split(r+1);
	LL res = 0;
	for (; itl != itr; ++itl)
		res = (res + (LL)(itl->r - itl->l + 1) * pow(itl->v, LL(ex), LL(mod))) % mod;
	return res;
}

int n, m;
LL seed, vmax;

LL rnd()
{
	LL ret = seed;
	seed = (seed * 7 + 13) % MOD7;
	return ret;
}

LL a[imax_n];

int main()
{
	scanf("%d %d %lld %lld",&n,&m,&seed,&vmax);
	for (int i=1; i<=n; ++i)
	{
		a[i] = (rnd() % vmax) + 1;
		s.insert(node(i,i,a[i]));
	}
	s.insert(node(n+1, n+1, 0));
	int lines = 0;
	for (int i =1; i <= m; ++i)
	{
		int op = int(rnd() % 4) + 1;
		int l = int(rnd() % n) + 1;
		int r = int(rnd() % n) + 1;
		if (l > r)
			std::swap(l,r);
		int x, y;
		if (op == 3)
			x = int(rnd() % (r-l+1)) + 1;
		else
			x = int(rnd() % vmax) +1;
		if (op == 4)
			y = int(rnd() % vmax) + 1;
		if (op == 1)
			add(l, r, LL(x));
		else if (op == 2)
			assign_val(l, r, LL(x));
		else if (op == 3)
			printf("%lld\n",rank(l, r, x));
		else
			printf("%lld\n",sum(l, r, x, y));
	}
	return 0;
}
```

