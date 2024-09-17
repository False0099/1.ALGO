# Rudolf and Snowflakes (hard version)

## 题面翻译

询问 $T$ 次：是否存在一个满 $k$（$k\ge 2$） 叉树节点数恰好为 $n$，且深度至少为 $2$。

## 题目描述

This is the hard version of the problem. The only difference is that in this version $ n \le 10^{18} $ .

One winter morning, Rudolf was looking thoughtfully out the window, watching the falling snowflakes. He quickly noticed a certain symmetry in the configuration of the snowflakes. And like a true mathematician, Rudolf came up with a mathematical model of a snowflake.

He defined a snowflake as an undirected graph constructed according to the following rules:

- Initially, the graph has only one vertex.
- Then, more vertices are added to the graph. The initial vertex is connected by edges to $ k $ new vertices ( $ k > 1 $ ).
- Each vertex that is connected to only one other vertex is connected by edges to $ k $ more new vertices. This step should be done at least once.

The smallest possible snowflake for $ k = 4 $ is shown in the figure.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1846E2/2fc3f5caf761ddee75c017a3deae10ee696f63d1.png)After some mathematical research, Rudolf realized that such snowflakes may not have any number of vertices. Help Rudolf check whether a snowflake with $ n $ vertices can exist.

## 输入格式

The first line of the input contains an integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

Then follow the descriptions of the test cases.

The first line of each test case contains an integer $ n $ ( $ 1 \le n \le 10^{18} $ ) — the number of vertices for which it is necessary to check the existence of a snowflake.

## 输出格式

Output $ t $ lines, each of which is the answer to the corresponding test case — "YES" if there exists such $ k > 1 $ that a snowflake with the given number of vertices can be constructed; "NO" otherwise.

## 样例 #1

### 样例输入 #1

```
9
1
2
3
6
13
15
255
10101
1000000000000000000
```

### 样例输出 #1

```
NO
NO
NO
NO
YES
YES
YES
YES
NO
```

## 题解
首先，我们本题要求我们的等差数列求和是否可以构成我们的 $n$,我们枚举我们的 k 显然是不现实的，我们考虑枚举我们的 $height$，可以知道，当我们的 $height$ 的范围最多只能到我们的 $32$,因为我们我们最后一旦超过 $height$,我们于是可以考虑枚举我们的 $height$,然后再去计算我们的对应 $k$ 是否存在，显然，我们的 $k$ 是可以通过我们的二分法去计算的。

```c++
#include <bits/stdc++.h>
using namespace std;

#define int __int128
const int N = 2e5 + 5;

int t, n;

int read() {
	char c = ' ';
	int f = 1, x = 0;
	while (c <  '0' || c > '9') {
		if (c == '-') f = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9') {
		x = x * 10 + c - '0';
		c = getchar();
	}
	return x * f;
}

int check(int x, int p) {
	__int128 ans = 0, kk = 1; // 这里会爆 long long，须开__int128
	for (int i = 1; i <= p + 1; i++) {
		ans += kk;
		kk *= x;
		if (ans > n) return 1; // 二分结果大于n
	}
	if (ans == n) return 2; // 二分结果等于n
	else return 0; // 二分结果小于n
}

signed main() {
	t = read();
	while (t--) {
		n = read();
		int flg = 0;
		for (int i = 2; i <= 63; i++) {
			int l = 2, r = 1e9;
			while (l < r) {
				int mid = (l + r) >> 1;
				int t = check(mid, i);
				if (t == 1 || t == 2) r = mid; // 如果二分结果大于等于n，调整右端点
				else l = mid + 1; // 否则调整左端点
			}
			if (check(l, i) == 2) { // 最后需要检查答案是否恰好为n
				flg = 1;
				break;
			}
		}
		if (flg) puts("Yes");
		else puts("No");
	}
}
```