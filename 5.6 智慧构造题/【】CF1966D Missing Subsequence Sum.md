You are given two integers $n$ and $k$. Find a sequence $a$ of non-negative integers of size at most $25$ such that the following conditions hold.

-   There is no subsequence of $a$ with a sum of $k$.
-   For all $1 \le v \le n$ where $v \ne k$, there is a subsequence of $a$ with a sum of $v$.

A sequence $b$ is a subsequence of $a$ if $b$ can be obtained from $a$ by the deletion of several (possibly, zero or all) elements, without changing the order of the remaining elements. For example, $[5, 2, 3]$ is a subsequence of $[1, 5, 7, 8, 2, 4, 3]$.

It can be shown that under the given constraints, a solution always exists.

**Input**

The first line of the input contains a single integer $t$ ($1 \le t \le 1000$) — the number of test cases. The description of the test cases follows.

Each test case consists of a single line containing two integers $n$ and $k$ ($2 \le n \le 10^6$, $1 \le k \le n$) — the parameters described above.

It is guaranteed that the sum of $n$ over all test cases does not exceed $10^7$.

**Output**

The first line of output for each test case should contain a single integer $m$ ($1 \le m \le 25$) — the size of your chosen sequence.

The second line of output for each test case should contain $m$ integers $a_i$ ($0 \le a_i \le 10^9$) — the elements of your chosen sequence.

If there are multiple solutions, print any.

## 题解
我们本题首先，要求我们构造一个序列，并且我们的这一个序列中的能够构造我们的 1-n 中的所有元素，但是不能构造出我们的 $k$。求一个具体的方案。

对于我们的上面的我们不妨**放宽我们的条件**，让我们的 $n$ 等于我们的最大值。那么这个时候，我们就可以通过构造我们的直接的元素，来实现我们的结果。

这个时候，我们想到我们可以通过**二进制构造**，我们假设我们的 $k$ 对应的第一个**比 k 还要小的数字**是 m，那么我们就可以首先通过我们的朴素构造构造出 $(1,2^{m}-1)$ 中的所有数字，那么之后，我们还需要构造出我们的 $(2^{m},(k))$ 内的所有数，这个时候，我们因为我们一定可以任意的排列组合我们的 $(1,2^{m}-1)$，那么这个时候，我们只需要能够构造出我们的**上界**即可，所以我们添加一个 $k-2^m$。

接下来，我们还需要构造出我们的 $(k+1,\inf)$ 中的所有数字，在这个时候，我们的第一思路肯定是先去构造出我们的对应的 $2^p$。**但是**，我们注意到，我们此时并不能构造出我们的 $k+1$,于是，我们需要把我们的 $k+1$ 添加进去，**另外**，因为我们 $k$ 是无法构造的，导致我们的 $2^p+k$ 也是无法构造的，于是，我们还需要把这一个数字单独加进去，就能完成所有的构造。

```
#include<iostream>
using namespace std;
void solve()
{
	int n, k;
	cin >> n >> k;
	int p = 0;
	while ((1 << (p + 1)) <= k)p++;
	cout << 22 << '\n';
	for (int i = 0; i < 20; i++)
	{
		if (i != p)cout << (1 << i) << " ";
	}
	cout << (k - (1 << p)) << " " << k + 1 << " " << (k + 1 + (1 << p));
}
int main()
{
	ios::sync_with_stdio(0), cin.tie(0);
	int t;
	cin >> t;
	while (t--)
	{
		solve();
		cout << endl;
	}
	return 0;
}

```