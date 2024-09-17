> 按位或运算：处理两个长度相同的二进制数，两个相应的二进位中只要有一个为 1，该位的结果值为 1。例如 5 or 3 = 7
> 
> ```
>         0101（十进制 5）
>      OR 0011（十进制 3）
>       = 0111（十进制 7）
> ```
> —— 引用自位运算——维基百科

小姐姐想要一种数据结构，支持如下操作：

对于一个整数数组：    

1\. 给定 L 和 R，输出\[L, R\]中元素的和

2\. 给定 L，R 和 X，将\[L, R\]中每个元素与 X 进行按位或运算

3\. 数组索引从 1 开始

按位或在 C\\C++、Java、Python 中为'|'运算符

## 输入：
第一行为两个整数 n 和 m，表示数组元素个数和操作的次数

第二行有 n 个整数，第 i 个表示数组 array 中第 i 个元素的值 array\[i\]

接下来 m 行，每行只有两种可能：

1\. SUM L R

表示对\[L, R\]的元素求和并输出

2\. OR L R X

表示对\[L, R\]的每一个元素与 X 进行按位或运算，L、R 为 base 1 的数字序号

数据满足：

$1 \leq n,m \leq 200000$  

$1\leq array_i, X \leq 1000000$  

$1 \leq L,R \leq n$

## 输出：
对于每个 SUM 操作，在一行内输出该操作的结果。

## 示例：
```
5 3
1 2 3 4 5
SUM 1 4
OR 2 5 10
SUM 1 4
```

```
10
36
```

## 题解
对于我们的 J 题，我们的思路是：对于我们的每一个二进制位，都去维护每一个线段树，然后我们对于我们的一个区间，我们的或就相当于我们的区间赋值。然后我们如果要查询我们的区间和，我们就直接去转换即可。

具体到我们的实现，我们就是对于每一个接单维护一个 sum 数组，维护我们对应的位数和
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define INF 0x3f3f3f3f3f3f3f3f
constexpr int mod = 1e9 + 7;
constexpr int N = 2e5 + 9;


int a[N];
#define kl k<<1
#define kr k<<1|1
struct node {
	int l, r;
	int flag, sum[20];
	int mid() {
		return l + r >> 1;
	};
};
node tr[N << 2];
void pushup(int k) {
	for (int i = 0; i < 20; i++) {
		tr[k].sum[i] = tr[kl].sum[i] + tr[kr].sum[i];
	}
}
void pushdown(int k) {
	if (!tr[k].flag) return ;
	int mid = tr[k].mid();
	for (int i = 0; i < 20; i++) {
		if (tr[k].flag >> i & 1) {
			tr[kl].sum[i] = mid - tr[k].l + 1;
			tr[kr].sum[i] = tr[k].r - mid;
		}
	}
	tr[kl].flag |= tr[k].flag;
	tr[kr].flag |= tr[k].flag;
	tr[k].flag = 0;
}
void build(int k, int l, int r) {
	tr[k] = {l, r};
	if (l == r) {
		for (int i = 0; i < 20; i++) {
			tr[k].sum[i] = a[l] >> i & 1;
		}
		return ;
	}
	int mid = tr[k].mid();
	build(kl, l, mid);
	build(kr, mid + 1, r);
	pushup(k);
}
void modify(int k, int l, int r, int val) {
	if (l <= tr[k].l && tr[k].r <= r) {
		for (int i = 0; i < 20; i++) {
			if (val >> i & 1) {
				tr[k].sum[i] = tr[k].r - tr[k].l + 1;
			}
		}
		tr[k].flag |= val;
		return ;
	}
	pushdown(k);
	int mid = tr[k].mid();
	if (l <= mid) modify(kl, l, r, val);
	if (r > mid) modify(kr, l, r, val);
	pushup(k);
}
int query(int k, int l, int r) {
	if (l <= tr[k].l && tr[k].r <= r) {
		int ans = 0;
		for (int i = 0; i < 20; i++) {
			ans += tr[k].sum[i] << i;
		}
		return ans;
	}
	pushdown(k);
	int mid = tr[k].mid();
	int ans = 0;
	if (l <= mid) ans += query(kl, l, r);
	if (r > mid) ans += query(kr, l, r);
	return ans;
}
void solve() {
	int n, m;
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
	}
	build(1, 1, n);
	while (m--) {
		string op;
		cin >> op;
		int l, r, val;
		if (op == "SUM") {
			cin >> l >> r;
			cout << query(1, l, r) << "\n";
		} else {
			cin >> l >> r >> val;
			modify(1, l, r, val);
		}
	}
}


constexpr bool test = 0;
signed main() {
	cin.tie(0)->ios::sync_with_stdio(false);
	cout << fixed << setprecision(20);
	int T = 1;
	if (test) cin >> T;
	for (int i = 1; i <= T; i++) solve();
	return 0;
}
```