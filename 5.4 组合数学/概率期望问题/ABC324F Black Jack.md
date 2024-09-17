### Problem Statement

You will play a game against a dealer. The game uses a $D$ \-sided die (dice) that shows an integer from $1$ to $D$ with equal probability, and two variables $x$ and $y$ initialized to $0$. The game proceeds as follows:

-   You may perform the following operation any number of times: roll the die and add the result to $x$. You can choose whether to continue rolling or not after each roll.
    
-   Then, the dealer will repeat the following operation as long as $y \lt L$: roll the die and add the result to $y$.
    
-   If $x \gt N$, you lose. Otherwise, you win if $y \gt N$ or $x \gt y$ and lose if neither is satisfied.
    

Determine the probability of your winning when you act in a way that maximizes the probability of winning.

## 题解
我们本题如果直接模拟过程，我们显然是不能计算得到答案的。于是，我们考虑寻找一些其他量来描述我们的比赛，显然，我们这里能看到的是用 $(x,y)$ 来表示我方为 $x$,对方为 $y$,并且我先手时的获胜概率。

但是，因为我们这里我们**庄家的策略是固定**的。所以，我们就可以采用我们下面的方法计算我们的概率：我们令 $f_{i}$ 表示庄家走到 $i$ 状态的概率为多少，那么我们起始 $f_{1}=0$,之后，我们的转移就有：$f_{i}-f_{i+D}+=\frac{f_{i}}{D}$,我们这样的更新要从我们的 $i=1\to i=L$ 一共更新 $n$ 次。

之后，我们考虑我们作为玩家时，我们的决策方法：我们的思路也是设 $g_{i}$ ，但是表示的内容不同，$g_{i}$ 表示我们作为玩家走到状态 i 时，我们**获胜的概率**是多少。

这里，我们就可以根据我们的决策来进行分类转移：如果我们决定在这个位置不选，那么我们就直接计算我们庄家获胜的概率，也就是 $f_{i}-f_{L+D}$ 中可以获胜的情况的概率和，如果我们选，那么我们就需要由我们的接下来的状态进行转移：即 $g(i)=\frac{g(i+1)+\dots+g(i+d)}{D}$。

```c++
#include <bits/stdc++.h>
using namespace std;

#define int long long
const int N = 4e5 + 5;

int n, l, d;
double g[N], dp[N], sum[N];

struct fenwick {
	double c[N][2];
	void mo(int x, double v) {
		x += 2;
		for (int i = x; i <= N - 5; i += i & -i) {
			c[i][0] += v;
			c[i][1] += x * v;
		}
	}
	void modify(int l, int r, double v) {
		mo(l, v);
		mo(r + 1, -v);
	}
	double get_sum(int op, int x) {
		x += 2;
		double res = 0.0;
		for (int i = x; i; i -= i & -i) res += c[i][op];
		return res;
	}
	double query(int l, int r) {
		double t1 = get_sum(0, l - 1) * 1.0 * (l + 2) - get_sum(1, l - 1);
		double t2 = get_sum(0, r) * (1.0 * r + 3) - get_sum(1, r);
		return t2 - t1;
	}
}tr;

double slove(int x) {
	if (x > n) return 0.0;
	double res = 1 - g[n];
	if (x >= 1) res += g[x - 1];
	return res;
}

signed main() {
	cin >> n >> l >> d;
	g[0] = 1.0; tr.modify(0, 0, 1.0);
	for (int i = 0; i <= N - 5; i++) {
		double t = tr.query(i, i); g[i] = t;
		if (i < l) {
			tr.modify(i + 1, i + d, t / d);
			g[i] = 0.0;
		}
	}
//	for (int i = 0; i <= 10; i++) cout << g[i] << ' ';
//	puts("");
	for (int i = 1; i <= N - 5; i++) g[i] += g[i - 1];
	for (int i = N - 5; i >= 0; i--) {
		if (i > n) dp[i] = 0.0;
		else dp[i] = max((sum[i + 1] - sum[i + d + 1]) / d, slove(i));
		sum[i] = sum[i + 1] + dp[i];
	}
	printf("%.10lf", dp[0]);
}
```