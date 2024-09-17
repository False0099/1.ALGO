# How Does the Rook Move?

## 题目描述

You are given an $ n \times n $ chessboard where you and the computer take turns alternatingly to place white rooks &amp; black rooks on the board respectively. While placing rooks, you have to ensure that no two rooks attack each other. Two rooks attack each other if they share the same row or column regardless of color.

A valid move is placing a rook on a position ( $ r $ , $ c $ ) such that it doesn't attack any other rook.

You start first, and when you make a valid move in your turn, placing a white rook at position ( $ r $ , $ c $ ), the computer will mirror you and place a black rook at position ( $ c $ , $ r $ ) in its turn. If $ r = c $ , then the computer can't mirror your move, and skips its turn.

You have already played $ k $ moves with the computer (the computer tries to mirror these moves too), and you must continue playing the game until there are no valid moves remaining. How many different final configurations are possible when you continue the game after the $ k $ moves? It is guaranteed that the $ k $ moves and the implied computer moves are valid. Since the answer may be large, print it modulo $ 10^9+7 $ .

Two configurations are considered different if there exists a coordinate ( $ r $ , $ c $ ) which has a rook in one configuration, but not in the other or the color of the rook on the coordinate is different.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \leq t \leq 10^4 $ ) — the number of test cases.

The first line of each test case contains two integers $ n $ and $ k $ ( $ 1 \leq n \leq 3 \cdot 10^5 $ , $ 0 \leq k \leq n $ ) — the size of the chessboard and the number of moves you have already played respectively.

Each of the next $ k $ lines of the test case contains two integers $ r_i $ and $ c_i $ , denoting the $ i $ -th move you made.

It is guaranteed that the $ k $ moves and the implied computer moves are valid.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 3 \cdot 10^5 $ .

## 输出格式

For each test case, output a single integer on a new line — the total number of possible final configurations modulo $ 10^9+7 $ .

## 样例 #1

### 样例输入 #1

```
3
4 1
1 2
8 1
7 6
1000 4
4 4
952 343
222 333
90 91
```

### 样例输出 #1

```
3
331
671968183
```

## 提示

In the first test case, we have a $ 4 \times 4 $ grid and you've already played $ 1 $ move. After you and the computer play a turn, we have a white rook at ( $ 1 $ , $ 2 $ ), and a black rook at ( $ 2 $ , $ 1 $ ). There are three possible configurations from this state —

1. You place a white rook at ( $ 3 $ , $ 4 $ ) and the computer places a black rook at ( $ 4 $ , $ 3 $ ) as a response.
2. You place a white rook at ( $ 4 $ , $ 3 $ ) and the computer places a black rook at ( $ 3 $ , $ 4 $ ) as a response.
3. You place a white rook at ( $ 3 $ , $ 3 $ ) and then at ( $ 4 $ , $ 4 $ ), or the other way around. They both result in the same configuration.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1957C/3fef326707498dc73b2e0e06c6ca687024f0a080.png)

## 题解
我们本题的思路是：首先我们因为我们的规则，我们的一行只能存在一个，并且我们的每一列之间是不相同的，因此我们就可以把原问题转换为一个排列，也就是说，我们的可以构造出 $(i,a[i])$ 这样的对。

首先，我们先去处理我们的前 $k$ 次操作，我们每一次操作，我们都会有 $a[i]$ 和 $i$ 点都不能填新数字，这是因为我们的电脑操作规则，我们每一次先操作，我们的后面的那一个都要去镜像的操作。

我们发现，我们的答案和我们的具体位置无关，也就是说，我们的剩余位置是 $1,2,3$ 还是我们的 $2,3,4$ 是不重要的，只有我们的剩余的个数是最重要的，因为我们可以通过将我们的剩余位置重新排列来构造出我们的最终的结果。

现在我们的问题就变成了，给定你 $m\times m$ 的完全空白的矩形，问你有多少种本质不同的最终棋盘。首先，我们考虑递推，我们第一种思路就是让我们的当前元素直接放在对角线上，这个时候，我们就相当于直接降解了，于是我们就有：$f[i]+=f[i-1]$。

在之后，我们考虑一次性选择一对来进行我们的放置，这个时候，我们经过我们的**枚举**，我们可以找到我们这一种情况下的个数，应该是满足 $f[i]+=f[i-2]*(i-1)$。

于是我们就可以写出我们的总的递推式：$f[i]=f[i-1]+(i-1)f[i-2]$

```
```cpp
#include <bits/stdc++.h>
using namespace std;
#define X 1000000007
#define N 300005
long long fac[N], invfac[N], k, p;
long long cnt = 0, ans;

long long com(int a, int b) {
	return fac[a] * invfac[b] % X * invfac[a - b] % X;
}

long long qpow(long long a, long long n) {
	long long pp = 1;
	while (n) {
		if (n % 2)
			pp = (pp * a) % X;
		a = (a * a) % X;
		n /= 2;
	}
	return pp;
}

void solve() {
	int m;
	for (int i = 0; i <= p; i++) {
		if ((p - i) % 2)
			continue;
		m = (p - i) / 2;
		cnt = ((com(p, i) * com(2 * m, m)) % X * fac[m]) % X;
		ans += cnt;
	}
}

int main() {
	int n, t, r, c;
	fac[0] = 1;
	fac[1] = 1;
	for (int i = 2; i <= N; i++)
		fac[i] = (fac[i - 1] * i) % X; //计算组合数操作
	invfac[N] = qpow(fac[N], X - 2);
	for (int i = N - 1; i >= 0; i--)
		invfac[i] = (invfac[i + 1] * (i + 1)) % X;
	cin >> t;
	for (int i = 1; i <= t; i++) {
		cin >> n >> k;
		p = n;
		ans = 0;
		for (int j = 1; j <= k; j++) {
			cin >> r >> c;
			if (r == c)
				p--;
			else
				p -= 2;//删行
		}
		solve();
		cout << ans % X << endl;
	}
	return 0;
}
```
```