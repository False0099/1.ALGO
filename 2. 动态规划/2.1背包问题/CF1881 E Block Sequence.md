Given a sequence of integers $a$ of length $n$.

A sequence is called beautiful if it has the form of a series of blocks, each starting with its length, i.e., first comes the length of the block, and then its elements. For example, the sequences \[$\color{red}{3},\ \color{red}{3},\ \color{red}{4},\ \color{red}{5},\ \color{green}{2},\ \color{green}{6},\ \color{green}{1}$ \] and \[$\color{red}{1},\ \color{red}{8},\ \color{green}{4},\ \color{green}{5},\ \color{green}{2},\ \color{green}{6},\ \color{green}{1}$ \] are beautiful (different blocks are colored differently), while \[$1$ \], \[$1,\ 4,\ 3$ \], \[$3,\ 2,\ 1$ \] are not.

**Input**

The first line of the input contains a single integer $t$ ($1 \le t \le 10^4$) — the number of test cases. Then follows the descriptions of the test cases.

The first line of each test case contains a single integer $n$ ($1 \le n \le 2 \cdot 10^5$) — the length of the sequence $a$.

The second line of each test case contains $n$ integers $a_1, a_2, \dots, a_n$ ($1 \le a_i \le 10^6$) — the elements of the sequence $a$.

It is guaranteed that the sum of the values of $n$ over all test cases does not exceed $2 \cdot 10^5$.

**Output**

For each test case, output a single number — the minimum number of deletions required to make the sequence $a$ beautiful.

In one operation, you can remove any element from the sequence. What is the minimum number of operations required to make the given sequence beautiful?

## 题解
我们这一题采用我们 dp 的思路，并且我们要从后往前更新，我们记 $dp[i]$,为我们选 i 位置为我们的目标点时，我们还需要往后删的数字的数量。于是我们的转移就可以写成 $dp[i]=min(dp[i+a[i]],dp[i])$,但是，我们还要记得分类：选或是不选，如果我们选那么 dp 如上图所示，如果我们**不选直接删除的话**，那么我们的 dp 就要变为 $dp[i]=min(dp[i],dp[i-1])+1$。

```cpp
// Problem: E. Block Sequence
// Contest: Codeforces - Codeforces Round 903 (Div. 3)
// URL: https://codeforces.com/contest/1881/problem/E
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

const int maxn = 200100;

int n, a[maxn], f[maxn];

void solve() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &a[i]);
	}
	f[n + 1] = 0;
	for (int i = n; i; --i) {
		f[i] = f[i + 1] + 1;
		if (i + a[i] <= n) {
			f[i] = min(f[i], f[i + a[i] + 1]);
		}
	}
	printf("%d\n", f[1]);
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