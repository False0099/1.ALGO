# [SCOI 2013] 数数

## 题目描述

Fish 是一条生活在海里的鱼，有一天他很无聊，就开始数数玩。他数数玩的具体规则是：

1. 确定数数的进制 B

2. 确定一个数数的区间[L, R]

3. 对于[L, R] 间的每一个数，把该数视为一个字符串，列出该字符串的每一个（连续的）子串对应的 B 进制数的值。

4. 对所有列出的数求和。现在 Fish 数了一遍数，但是不确定自己的结果是否正确了。由于[L, R] 较大，他没有多余精力去验证是否正确，你能写一个程序来帮他验证吗？

## 输入格式

输入包含三行。

第一行仅有一个数 B，表示数数的进制。

第二行有 N +1 个数，第一个数为 N，表示数 L 在 B 进制下的长度为 N，接下里的 N 个数从高位到低位的表示数 L 的具体每一位。

第三行有 M+ 1 个数，第一个数为 M，表示数 R 在 B 进制下的长度为 M，接下里的 M 个数从高位到低位的表示数 R 的具体每一位。

## 输出格式

输出仅一行，即按照 Fish 数数规则的结果，结果用 10 进制表示，由于该数可能很大，输出该数模上 20130427 的模数。

数据中有 $r<l$ 的情况，输出的是 $-ans[r+1,l-1]\bmod 20130427$

## 样例 #1

### 样例输入 #1

```
10
3 1 0 3
3 1 0 3
```

### 样例输出 #1

```
120
```

## 提示

【样例解释】

[103, 103] 之间仅有数 103，该数的所有子串包括 1, 10, 103, 0, 03, 3，其和为 120。

【数据范围与约定】

20% 数据，0 <= L <= R <= 10^5。

50% 数据，2 <= B <= 1000，1 <= N, M <= 1000。

100% 数据，2 <= B <= 10^5，1 <= N, M <= 10^5。


## 题解
看到这一题，我们就可以考虑我们的数位 dp，我们给定的数位 B，就相，我们就可以考虑我们每添加一个位，对于我们的那个答案的贡献是多少？这一点，我们要分类别来看：我们把我们的贡献就可以用我们的 $S[n]=\sum_{i=1}^n B_{i-1}$

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long LL;

const int P = 20130427;
const int maxn = 2e5 + 5;

int B, n, m, l[maxn], r[maxn], sum[maxn], a[maxn], len, sa[maxn], mi[maxn];
pair<int, int> f[maxn][2], em;

inline int read() {
	char ch = getchar(); int u = 0, f = 1;
	while(!isdigit(ch)) {if(ch == '-') f = -1; ch = getchar();}
	while(isdigit(ch))  {u = u * 10 + ch - 48; ch = getchar();} return u * f;
}

inline int pls(int x, int y) {x += y; return x >= P ? x - P : (x < 0 ? x + P : x);}
inline int mul(int x, int y) {LL rnt = 1ll * x * y; return rnt >= P ? rnt % P : rnt;}
inline int mul(int a, int b, int c) {return mul(a, mul(b, c));}
inline int pls(int a, int b, int c) {return pls(a, pls(b, c));}

inline int check(int *s, int n, int rnt = 0) {
	for(register int i = 1; i <= n; i++)
		rnt = pls(rnt, mul(i, s[i], sum[n - i + 1]));
	return rnt;
}

inline pair<int, int> dfs(int pos, bool lim, bool lead) {
	if(pos > len) return em;
	pair<int, int> &rnt = f[pos][lead], tmp;
	int Lim = lim ? a[pos] : (B - 1), S, l, r, i;
	bool is;
	if(!lim && rnt.first != -1) return rnt;
	rnt.first = rnt.second = 0;
	/*-------------------- i = 0 -----------------------*/
	i = 0;
	is = !lead || i != 0;
	S = (lim && (i == Lim)) ? (sa[pos + 1] + 1) : mi[len - pos + 1];
	tmp = dfs(pos + 1, lim && (i == Lim), lead && (i == 0));
	rnt.first = pls(rnt.first, tmp.first, is * tmp.second);
	rnt.first = pls(rnt.first, mul(i, sum[len - pos + 1], S));
	rnt.second = pls(rnt.second, tmp.second, mul(i, sum[len - pos + 1], S));
	/*-------------------- i > 0 -----------------------*/
	if(Lim > 1) {
		i = 1;
		is = !lead || i != 0;
		S = (lim && (i == Lim)) ? (sa[pos + 1] + 1) : mi[len - pos + 1];
		tmp = dfs(pos + 1, lim && (i == Lim), lead && (i == 0));
		l = i; r = Lim - 1;
		LL Len = r - l + 1;
		rnt.first = pls(rnt.first, mul(pls(tmp.first, tmp.second * is), Len));
		rnt.second = pls(rnt.second, mul(tmp.second, Len));
		Len = (l + r) * Len / 2;
		Len %= P; Len = mul(Len, S, sum[len - pos + 1]);
		rnt.first = pls(rnt.first, Len);
		rnt.second = pls(rnt.second, Len);
	}
	/*------------------- i = Lim ----------------------*/
	if(Lim > 0) {
		i = Lim;
		is = !lead || i != 0;
		S = (lim && (i == Lim)) ? (sa[pos + 1] + 1) : mi[len - pos + 1];
		tmp = dfs(pos + 1, lim && (i == Lim), lead && (i == 0));
		rnt.first = pls(rnt.first, tmp.first, is * tmp.second);
		rnt.first = pls(rnt.first, mul(i, sum[len - pos + 1], S));
		rnt.second = pls(rnt.second, tmp.second, mul(i, sum[len - pos + 1], S));
	} return rnt;
}

inline pair<int, int> calc(int *s, int n) {
	memset(f, 255, sizeof(f));
	memset(sa, 0, sizeof(sa));
	len = n;
	for(register int i = 1; i <= n; i++) a[i] = s[i];
	for(register int i = n; i >= 1; i--)
		sa[i] = pls(sa[i + 1], mul(mi[n - i + 1], a[i]));
	return dfs(1, 1, 1);
}

int main() {
	B = read(); n = read();
	for(register int i = 1; i <= n; i++) l[i] = read();
	m = read();
	for(register int i = 1; i <= m; i++) r[i] = read();
	//if(cmp(l, r, n, m) > 0) {cout << 0; return 0;}
	mi[1] = sum[1] = 1;
	for(register int i = 2; i < maxn; i++) mi[i] = mul(mi[i - 1], B);
	for(register int i = 2; i < maxn; i++) sum[i] = pls(mi[i], sum[i - 1]);
	cout << pls(calc(r, m).first, check(l, n) - calc(l, n).first);
	return 0;
}
/*
100801110

d[maxn]

L, pos, a[pos]
d[L - pos + 2] -= a[pos] * pos
d[1] += a[pos] * pos

ans

103
1 0 0 -1
1 0 0 -1
10 -9 0 -1
10 1 1
1 10 100 1000
1 11 111 1111
O(n)

1 10 100 1000
1103
1111 + 222 + 0 + 12
0000 + 111 + 0 + 09
-> 各个位上数的和
1103


*/
```