# 知识点
  ## [[线段树]]
# 题目
 # [蓝桥杯 2022 省 A] 选数异或

## 题目描述

给定一个长度为 $n$ 的数列 $A_{1}, A_{2}, \cdots, A_{n}$ 和一个非负整数 $x$, 给定 $m$ 次查询, 每次询问能否从某个区间 $[l, r]$ 中选择两个数使得他们的异或等于 $x$ 。

## 输入格式

输入的第一行包含三个整数 $n, m, x$ 。

第二行包含 $n$ 个整数 $A_{1}, A_{2}, \cdots, A_{n}$。

接下来 $m$ 行，每行包含两个整数 $l_{i}, r_{i}$ 表示询问区间 $\left[l_{i}, r_{i}\right]$ 。

## 输出格式

对于每个询问, 如果该区间内存在两个数的异或为 $x$ 则输出 `yes`, 否则输出 `no`。

## 样例 #1

### 样例输入 #1

```
4 4 1
1 2 3 4
1 4
1 2
2 3
3 3
```

### 样例输出 #1

```
yes
no
yes
no
```

## 提示

**【样例说明】**

显然整个数列中只有 2,3 的异或为 1 。

**【评测用例规模与约定】**

对于 $20 \%$ 的评测用例, $1 \leq n, m \leq 100$;

对于 $40 \%$ 的评测用例, $1 \leq n, m \leq 1000$;

对于所有评测用例, $1 \leq n, m \leq 10^5,0 \leq x<2^{20}, 1 \leq l_{i} \leq r_{i} \leq n$ ， $0 \leq A_{i}<2^{20}$ 。

蓝桥杯 2022 省赛 A 组 D 题。

# 思路
因为我们已知 x 所以我们可以先预**处理出每一个数与 x 异或后的结果作为我们的真正的权值。**

之后，我们再创建一个last数组，表示要让我们**第i位异或后为结果为x的在第i位数前面的，最近的y所在的位置。**

**last 数组需要我们在构造线段树之前就取出来**

接下来，我们再用线段树**维护last数组的区间最大值**。如果区间的最大值是比L要大的，那么我们就输出是即可。

·
# AC 代码
```cpp
#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;
int n, q, x, loc[1919810];
namespace SegmentTree {
	int mx[400005];
	#define ls pos << 1
	#define rs pos << 1 | 1
	void build(int l, int r, int pos)
	{
		if (l == r)
		{
			int a;
			scanf("%d", &a);
			loc[a] = l, mx[pos] = loc[a ^ x];//维护异或上x后的值所在的最远距离	
			return;
		}
		int mid = (l + r) >> 1;
		build(l, mid, ls), build(mid + 1, r, rs);
		mx[pos] = max(mx[ls], mx[rs]);
	}
	int query(int l, int r, int pos, int L, int R)
	{
		if (L <= l && r <= R) return mx[pos];
		int mid = (l + r) >> 1, ans = 0;
		if (L <= mid) ans = max(ans, query(l, mid, ls, L, R));
		if (mid < R) ans = max(ans, query(mid + 1, r, rs, L, R));
		return ans;
	}
}; using namespace SegmentTree;

int main()
{
	scanf("%d%d%d", &n, &q, &x);
	build(1, n, 1);
	while (q--)
	{
		int l, r;
		scanf("%d%d", &l, &r);
		if (query(1, n, 1, l, r) >= l) puts("yes"); else puts("no");
	}
	return 0;
}
```
# 备注
