# [USACO 10 MAR] Barn Allocation G

## 题目描述

Farmer John recently opened up a new barn and is now accepting stall allocation requests from the cows since some of the stalls have a better view of the pastures.

The barn comprises N (1 <= N <= 100,000) stalls conveniently numbered 1.. N; stall i has capacity C\_i cows (1 <= C\_i <= 100,000). Cow i may request a contiguous interval of stalls (A\_i, B\_i) in which to roam (1 <= A\_i <= N; A\_i <= B\_i <= N), i.e., the cow would like to wander among all the stalls in the range A\_i..B\_i (and the stalls must always have the capacity for her to wander).

Given M (1 <= M <= 100,000) stall requests, determine the maximum number of them that can be satisfied without exceeding stall

Capacities.

 
农夫约翰最近开了一个新的牲口棚屋，并且现在接受来自奶牛的分配畜栏请求因为其中的一些畜栏有更好风景。

畜栏包括 N 个畜栏 (1 ≤ N ≤ 100,000)，方便起见，我们把它们编号为 1.. N，畜栏 i 能容纳 Ci 只牛 (1 ≤ Ci ≤ 100,000)，第 i 只牛需要连续编号畜栏（从 Ai 到 Bi）来漫步其中，

(1 ≤ Ai ≤ N; Ai ≤ Bi ≤ N)，换言之，这只牛想要在编号范围为 Ai.. Bi 的畜栏漫步（所有它想要畜栏必须实施为它空出位置来供它散步）

给出 M 个畜栏分配请求（1 ≤ M ≤ 100,000），回答最多能满足多少只牛的要求（不增加另外畜栏）

考虑以下例子：

```cpp
畜栏号:    1   2   3   4   5
           +---+---+---+---+---+
容纳空间:  | 1 | 3 | 2 | 1 | 3 |  
           +---+---+---+---+---+
Cow 1       XXXXXXXXXXX             (1, 3)
Cow 2           XXXXXXXXXXXXXXX     (2, 5)
Cow 3           XXXXXXX             (2, 3)
Cow 4                   XXXXXXX     (4, 5)
```
约翰显然不能满足所有的牛，因为畜栏 3，4 请求太多了

经过试验，我们发现，我们能满足牛 1，3，4 需要，所以这组数据答案为 3

## 输入格式

第一行包括两个以空格隔开的正整数：N, M

第二行到第 N+1 行：第 i+1 行包括一个整数：Ci

第 N+2 到第 N+M+1 行：第 i+N+1 包括两个整数 Ai、Bi

## 输出格式

仅一行：能满足的最大需要

## 样例 #1

### 样例输入 #1

```
5 4
1
3
2
1
3
1 3
2 5
2 3
4 5
```

### 样例输出 #1

```
3
```

## 提示

Source: USACO 2010 March Gold

Translator: @chrome 01

## 题解
我们这一题其实也算是我们区间调度的类型，原因在于，与一般的区间调度相比，我们的唯一区别是，原本的区间调度只能要求我们每一个区间只有 1 个，而现在，我们的区间 $i$ 可以有 $C_{i}$ 个，换句话说，**我们现在处理的就是一系列加权的区间调度问题**。
我们第一步仍然不变，仍然是按照我们的每个区间的末尾来进行我们的排序，然后我们每一次加入围栏，就相当于我们所有围栏的容量都--，**相当于我们的区间加**，然后我们对于下一个区间，我们就要进行我们的区间查询，如果我们的区间最小值>0, 那么我们就可以放，否则我们就不行
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 100005;
int n, m, a[N], ans;
int T[N << 2], minn[N << 2], lazy[N << 2];
struct node
{
	int l, r;
}nod[N];
bool cmp(node a, node b)
{
	if(a.r != b.r) return a.r < b.r;
	else return a.l < b.l;
}
void pushup(int cnt)
{
	minn[cnt] = min(minn[cnt << 1], minn[cnt << 1 | 1]);
}
void build(int cnt, int l, int r)
{
	if(l == r)
	{
		minn[cnt] = a[l];
		return;
	}
	int mid = l + r >> 1;
	build(cnt << 1, l, mid);
	build(cnt << 1 | 1, mid + 1, r);
	pushup(cnt);
}
void pushdown(int cnt, int l, int r)
{
	if(lazy[cnt])
	{
		minn[cnt << 1] += lazy[cnt];
		minn[cnt << 1 | 1] += lazy[cnt];
		lazy[cnt << 1] += lazy[cnt];
		lazy[cnt << 1 | 1] += lazy[cnt];

		lazy[cnt] = 0;
	}
}
void update(int cnt, int l, int r, int nl, int nr)
{
	if(l >= nl && r <= nr)
	{
		lazy[cnt] -= 1;
		minn[cnt] -= 1;
		return;
	}
	int mid = l + r >> 1;
	pushdown(cnt, l, r);
	if(mid >= nl) update(cnt << 1, l, mid, nl, nr);
	if(mid < nr) update(cnt << 1 | 1, mid + 1, r, nl, nr);
	pushup(cnt);
}
int qmin(int cnt, int l, int r, int nl, int nr)
{
	if(l >= nl && r <= nr) return minn[cnt];
	int mid = l + r >> 1;
	pushdown(cnt, l, r);
	int ans = 999999999;
	if(mid >= nl) ans = min(ans, qmin(cnt << 1, l, mid, nl, nr));
	if(mid < nr) ans = min(ans, qmin(cnt << 1 | 1, mid + 1, r, nl, nr));
	return ans;
}
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i ++) scanf("%d", &a[i]);
	build(1, 1, n);
	for(int i = 1; i <= m; i ++) scanf("%d%d", &nod[i].l, &nod[i].r);
	sort(nod + 1, nod + 1 + m, cmp);
	for(int i = 1; i <= m; i ++)
	{
		if(qmin(1, 1, n, nod[i].l, nod[i].r) > 0)
		{
			update(1, 1, n, nod[i].l, nod[i].r);
			ans ++;
		}
	}
	cout << ans;
}
```