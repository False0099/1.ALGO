Kristina has a matrix of size $n$ by $n$, filled with lowercase Latin letters. The value of $n$ is **even**.

She wants to change some characters so that her matrix becomes a perfect square. A matrix is called a perfect square if it remains unchanged when rotated $90^\circ$ clockwise **once**.

Here is an example of rotating a matrix by $90^\circ$:

![](https://espresso.codeforces.com/f31ca811677514ff724a6af677d2e4a129b8fcfb.png)

In one operation, Kristina can choose any cell and replace its value with the next character in the alphabet. If the character is equal to "z", its value **does not change**.

Find the **minimum** number of operations required to make the matrix a perfect square.

For example, if the $4$ by $4$ matrix looks like this:

$$
\matrix{ a & b & b & a \cr b & c & \textbf{b} & b \cr b & c & c & b\cr a & b & b & a \cr }
$$

then it is enough to apply $1$ operation to the letter **b**, highlighted in bold.

**Input**

The first line of the input contains a single integer $t$ ($1 \le t \le 10^2$) — the number of test cases.

Then follows the description of each test case.

The first line of each test case contains a single **even** integer $n$ ($2 \le n \le 10^3$) — the number of rows and columns in the matrix.

Then follows $n$ lines, each containing exactly $n$ lowercase Latin letters.

It is guaranteed that the sum of $n$ over all test cases does not exceed $10^3$.

## 题解
我们本题只需要搞清楚我们旋转 90 度时，我们都对应着那些点，设我们的初始坐标为 $x,y$,那么我们有：旋转一次后，我们的答案为: $(i,j),(j,n-i+1),(n-i+1,j),(n-j+1,i)$,我们每一次的花费，就是这四个坐标里的最大值，加上我们与这个坐标的差值。

```cpp
// Problem: C. Perfect Square
// Contest: Codeforces - Codeforces Round 903 (Div. 3)
// URL: https://codeforces.com/contest/1881/problem/C
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
#define pb emplace_back
#define fst first
#define scd second
#define mkp make_pair
#define mems(a, x) memset((a), (x), sizeof(a))

using namespace std;
typedef long long ll;
typedef double db;
typedef unsigned long long ull;
typedef long double ldb;
typedef pair<ll, ll> pii;

const int maxn = 1010;

int n;
bool vis[maxn][maxn];
char s[maxn][maxn];

void solve() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%s", s[i] + 1);
		for (int j = 1; j <= n; ++j) {
			vis[i][j] = 0;
		}
	}
	int ans = 0;
	for (int i = 1; i <= n / 2; ++i) {
		for (int j = 1; j <= n / 2; ++j) {
			char mx = max({s[i][j], s[j][n - i + 1], s[n - i + 1][n - j + 1], s[n - j + 1][i]});
			ans += mx - s[i][j];
			ans += mx - s[j][n - i + 1];
			ans += mx - s[n - i + 1][n - j + 1];
			ans += mx - s[n - j + 1][i];
		}
	}
	printf("%d\n", ans);
}

int main() {
	int T = 1;
	scanf("%d", &T);
	while (T--) {
		solve();
	}
	return 0;
}

```