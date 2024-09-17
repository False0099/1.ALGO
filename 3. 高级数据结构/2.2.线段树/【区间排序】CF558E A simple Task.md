# A Simple Task

## 题面翻译

题目大意： 给定一个长度不超过 10^5 的字符串（小写英文字母），和不超过 50000 个操作。

每个操作 L R K 表示给区间[L, R]的字符串排序，K=1 为升序，K=0 为降序。

最后输出最终的字符串。

## 题目描述

This task is very simple. Given a string $ S $ of length $ n $ and $ q $ queries each query is on the format $ i $ $ j $ $ k $ which means sort the substring consisting of the characters from $ i $ to $ j $ in non-decreasing order if $ k=1 $ or in non-increasing order if $ k=0 $ .

Output the final string after applying the queries.

## 输入格式

The first line will contain two integers $ n, q $ ( $ 1<=n<=10^{5} $ , $ 0<=q<=50000 $ ), the length of the string and the number of queries respectively.

Next line contains a string $ S $ itself. It contains only lowercase English letters.

Next $ q $ lines will contain three integers each $ i, j, k $ ( $ 1<=i<=j<=n $ , ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF558E/7c3e064c95015e1bd5569e78df83991726b5fb24.png)).

## 输出格式

Output one line, the string $ S $ after applying the queries.

## 样例 #1

### 样例输入 #1

```
10 5
abacdabcda
7 10 0
5 8 1
1 4 0
3 6 0
7 10 1
```

### 样例输出 #1

```
cbcaaaabdd
```

## 样例 #2

### 样例输入 #2

```
10 1
agjucbvdfk
1 10 1
```

### 样例输出 #2

```
abcdfgjkuv
```

## 提示

First sample test explanation:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF558E/39812d297b72578842edac4711612bcaf8f08f55.png)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF558E/6cf00260e704a305c81e1f57b87405efa2610fa7.png)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF558E/8d72452272093b12cc5f5081cf07220bba9298d5.png)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF558E/51ddb7e0620c1f3452d956f281c3537d11d07fb3.png)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF558E/47cfdfe8b8cb10e651ce3dbdd53d8f068aca3e79.png)

## 题解
因为我们的值域非常小，于是我们考虑使用我们对于每一个值域开一个线段树。
我们按照某一位是不是 x 来计算对应位置线段树的值是多少。我们可以首先得到 26 个序列，然后每一次区间排序，我们按照顺序把我们的字母填入对应的位置。然后，我们再去吧线段树上的对应位置赋值为 1，其余位置赋值为 0.

```cpp
#include <cstdio>

using namespace std;

const int sz = 7000010, maxn = 100010;

inline void read(int &x) {
	char ch = getchar();
	x = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') x = (x<<3)+(x<<1)+(ch&15), ch = getchar();	
}

struct stree{
	int ls, rs, val, laz;
}t[sz];
int root[30], tot = 1;

inline int newnode() {
	t[tot].ls = t[tot].rs = t[tot].val = 0; t[tot].laz = -1;
	return tot++;
}

inline void spread(int p, int ll, int lr) {
	if(!t[p].ls) t[p].ls = newnode();
	if(!t[p].rs) t[p].rs = newnode();
	if(t[p].laz == -1) return;
	t[t[p].ls].val = ll * t[p].laz; t[t[p].ls].laz = t[p].laz;
	t[t[p].rs].val = lr * t[p].laz; t[t[p].rs].laz = t[p].laz;
	t[p].laz = -1;
}

inline void change(int p, int lp, int rp, int l, int r, int v) {
	if(l <= lp && rp <= r) { t[p].val = (rp-lp+1) * v; t[p].laz = v; return; }
	int mid = (lp + rp) >> 1;
	spread(p, mid-lp+1, rp-mid);
	if(l <= mid) change(t[p].ls, lp, mid, l, r, v);
	if(r > mid) change(t[p].rs, mid+1, rp, l, r, v);
	t[p].val = t[t[p].ls].val + t[t[p].rs].val;
}

inline int query(int p, int lp, int rp, int l, int r) {
	if(l <= lp && rp <= r) return t[p].val;
	int mid = (lp + rp) >> 1;
	spread(p, mid-lp+1, rp-mid);
	int ans = 0;
	if(l <= mid) ans += query(t[p].ls, lp, mid, l, r);
	if(r > mid) ans += query(t[p].rs, mid+1, rp, l, r);
	return ans;
}

char s[maxn];

inline void putree(int p, int lp, int rp, char ch) {
	if(t[p].val == rp-lp+1)	{
		for(int i = lp; i <= rp; i++) s[i] = ch;
		return;	
	}
	if(lp == rp) return;
	int mid = (lp + rp) >> 1;
	spread(p, mid-lp+1, rp-mid);
	if(t[p].ls && t[t[p].ls].val) putree(t[p].ls, lp, mid, ch);
	if(t[p].rs && t[t[p].rs].val) putree(t[p].rs, mid+1, rp, ch);
}

int main() {
	int n, m, t, g, c;
	char ch;
	read(n); read(m);
	for(int i = 0; i < 26; i++) root[i] = newnode();
	for(int i = 1; i <= n; i++) {
		do{
			ch = getchar();
		}while(ch < 'a' || ch > 'z');
		change(root[ch-'a'], 1, n, i, i, 1);
	}
	while(m--) {
		read(t); read(g); read(c);
		int p = 0, tt;
		if(c == 1) {
			for(int i = 0; i < 26; i++) {
				tt = query(root[i], 1, n, t, g);
				if(!tt) continue;
				change(root[i], 1, n, t, g, 0);
				change(root[i], 1, n, t+p, t+p+tt-1, 1);
				p += tt;
			}
		} else {
			for(int i = 25; i > -1; --i) {
				tt = query(root[i], 1, n, t, g);
				if(!tt) continue;
				change(root[i], 1, n, t, g, 0);
				change(root[i], 1, n, t+p, t+p+tt-1, 1);
				p += tt;
			}
		}
	}
	for(int i = 0; i < 26; i++) 
		putree(root[i], 1, n, 'a'+i);
	for(int i = 1; i <= n; i++) putchar(s[i]);
	return 0;	
}
```