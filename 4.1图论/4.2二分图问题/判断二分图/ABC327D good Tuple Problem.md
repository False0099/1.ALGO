# [ABC 327 D] Good Tuple Problem

## 题面翻译

我们称一对长度为 $ M $ 的序列 $ (S,\ T)\ =\ ((S_1,\ S_2,\ \dots,\ S_M),\ (T_1,\ T_2,\ \dots,\ T_M)) $ 为好序列对时，当且仅当 $ (S, T) $ 满足以下条件：

- $ S, T $ 均由正整数组成，且对于满足 $ 1 \le i \le M $ 的 $ i $ ，都有 $ 1 \le S_i, T_i \le N $
- 可以生成一个长度为 $ N $ 的序列 $ X $，保证 $ X_i \in \{0,1\} $

- 对于每个满足 $ 1 \le i \le M $ 的 $ i $，都有 $ X_{S_i} \ne X_{T_i} $

现在有一对长度为 $ M $ 的由正整数组成的序列 $ (A,\ B)\ =\ ((A_1,\ A_2,\ \dots,\ A_M),\ (B_1,\ B_2,\ \dots,\ B_M)) $，请问序列对 $ (A, B) $ 是否是好序列对？

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc327/tasks/abc327_d

$ N $ 以下の正整数からなる長さ $ M $ の数列の組 $ (S,\ T)\ =\ ((S_1,\ S_2,\ \dots,\ S_M),\ (T_1,\ T_2,\ \dots,\ T_M)) $ が **良い数列の組である** とは、$ (S,\ T) $ が次の条件を満たすことを言います。

- $ 0,1 $ からなる長さ $ N $ の数列 $ X\ =\ (X_1,\ X_2,\ \dots,\ X_N) $ であって次の条件を満たすものが存在する。
  - $ i=1,\ 2,\ \dots,\ M $ それぞれについて、$ X_{S_i}\ \neq\ X_{T_i} $ が成立する。
 
$ N $ 以下の正整数からなる長さ $ M $ の数列の組 $ (A,\ B)\ =\ ((A_1,\ A_2,\ \dots,\ A_M),\ (B_1,\ B_2,\ \dots,\ B_M)) $ が与えられます。$ (A,\ B) $ が良い数列の組である場合は `Yes` を、そうでない場合は `No` を出力してください。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ N $ $ M $ $ A_1 $ $ A_2 $ $ \dots $ $ A_M $ $ B_1 $ $ B_2 $ $ \dots $ $ B_M $

## 输出格式

$ (A,\ B) $ が良い数列の組である場合は `Yes` を、そうでない場合は `No` を出力せよ。

## 样例 #1

### 样例输入 #1

```
3 2
1 2
2 3
```

### 样例输出 #1

```
Yes
```

## 样例 #2

### 样例输入 #2

```
3 3
1 2 3
2 3 1
```

### 样例输出 #2

```
No
```

## 样例 #3

### 样例输入 #3

```
10 1
1
1
```

### 样例输出 #3

```
No
```

## 样例 #4

### 样例输入 #4

```
7 8
1 6 2 7 5 4 2 2
3 2 7 2 1 2 3 3
```

### 样例输出 #4

```
Yes
```

## 提示

### 制約

- $ 1\ \leq\ N,\ M\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ A_i,\ B_i\ \leq\ N $
- 入力される値は全て整数
 
### Sample Explanation 1

$ X=(0,1,0) $ とすると、$ X $ は $ 0,1 $ からなる長さ $ N $ の数列で、 $ X_{A_1}\ \neq\ X_{B_1} $ かつ $ X_{A_2}\ \neq\ X_{B_2} $ を満たします。 よって、$ (A, B) $ は良い数列の組としての条件を満たしています。

### Sample Explanation 2

条件を満たすような数列 $ X $ は存在しないので、$ (A,\ B) $ は良い数列の組ではありません。

## 题解
我们这一题连边连接的是两个不相同的部分，所以我们就可以用我们图能否二分来决定我们能否满足我们的条件，于是我们的问题就变成了我们的判断二分图。判断二分图的方法，我们可以用我们的染色法。

```cpp
// Problem: D - Good Tuple Problem
// Contest: AtCoder - HHKB Programming Contest 2023(AtCoder Beginner Contest 327)
// URL: https://atcoder.jp/contests/abc327/tasks/abc327_d
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>

using namespace std;

#define re			register
#define fi			first
#define se			second
#define il			inline
#define fup(x, l, r) for (re int x = (l), eNd = (r); x <= eNd; ++ x )
#define fdw(x, r, l) for (re int x = (r), eNd = (l); x >= eNd; -- x )

typedef pair<int, int> PII;
typedef long long LL;
typedef long double LD;

const int N = 1e6 + 10;
const int M = 2e6 + 10;
const int INF = 2e9, P = 998244353;
const double eps = 1e-6;

il int Max(int a, int b) { return a > b ? a : b; }
il int Min(int a, int b) { return a < b ? a : b; }
il int read() { re int x = 0; re bool f = true; re char c = getchar(); while (c < 48 || c > 57) { if (c == '-') f = false; c = getchar(); } while (c >= 48 && c <= 57) x = (x << 3) + (x << 1) + c - 48, c = getchar(); return f ? x : -x; }
il void write(int x) { if (x < 0) putchar('-'), x = -x; if (x > 9) write(x / 10); putchar(x % 10 + 48); }
il void wel(int x) { write(x), putchar('\n'); }
il void wsp(int x) { write(x), putchar(' '); }

int n, m;
int a[N], b[N];
int h[N], e[M], ne[M], idx;

void add(int a, int b)
{
	e[idx] = b, ne[idx] = h[a], h[a] = idx ++ ;
}

int col[N];

bool dfs(int u, int c)
{
	col[u] = c;
	for (int i = h[u]; ~i; i = ne[i])
	{
		int j = e[i];
		if (col[j] && col[j] == c) return false;
		if (!col[j])
		{
			if (!dfs(j, 3 - c)) return false;
		}
	}
	return true;
}

int main()
{
	memset(h, -1, sizeof h);
	n = read(), m = read();
	
	fup (i, 1, m) a[i] = read();
	fup (i, 1, m) b[i] = read();
	
	fup (i, 1, m) add(a[i], b[i]), add(b[i], a[i]);
	
	fup (i, 1, n)
	{
		if (!col[i] && !dfs(i, 1))
			return puts("No"), 0;
	}
	puts("Yes");
	
  return 0;
}

```