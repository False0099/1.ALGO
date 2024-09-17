You are given an array $b_1, b_2, \ldots, b_n$.

An anonymous informant has told you that the array $b$ was obtained as follows: initially, there existed an array $a_1, a_2, \ldots, a_n$, after which the following two-component operation was performed $k$ times:

1.  A fixed point $^{\dagger}$ $x$ of the array $a$ was chosen.
2.  Then, the array $a$ was cyclically shifted to the left $^{\ddagger}$ exactly $x$ times.

As a result of $k$ such operations, the array $b_1, b_2, \ldots, b_n$ was obtained. You want to check if the words of the anonymous informant can be true or if they are guaranteed to be false.

$^{\dagger}$ A number $x$ is called a fixed point of the array $a_1, a_2, \ldots, a_n$ if $1 \leq x \leq n$ and $a_x = x$.

$^{\ddagger}$ A cyclic left shift of the array $a_1, a_2, \ldots, a_n$ is the array $a_2, \ldots, a_n, a_1$.

**Input**

Each test contains multiple test cases. The first line contains an integer $t$ ($1 \le t \le 10^4$) — the number of test cases. The description of the test cases follows.

The first line of each test case contains two integers $n, k$ ($1 \le n \le 2 \cdot 10^5$, $1 \le k \le 10^9$) — the length of the array $b$ and the number of operations performed.

The second line of each test case contains $n$ integers $b_1, b_2, \ldots, b_n$ ($1 \le b_i \le 10^9$) — the elements of the array $b$.

It is guaranteed that the sum of the values of $n$ for all test cases does not exceed $2 \cdot 10^5$.

**Output**

For each test case, output "Yes" if the words of the anonymous informant can be true, and "No" if they are guaranteed to be false.


## 题解
我们这一题的突破口在于我们循环左移的性质，对于每一个 $a[x]=x$，循环左移 x 次后，我们数列的最后一个元素，一定会变成我们的 x。于是**我们就可以通过我们的反推法，我们每一次来找我们的基数元素是多少，如果我们找到的基数元素范围不在 1-n, 说明无解**。

```cpp
#include <bits/stdc++.h>
 
using namespace std;
 
void solve() {
  int n, k;
  cin >> n >> k;
  vector<int> a(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  k = min(k, n);
  int last = n - 1;
  for (int _ = 0; _ < k; _++) {
    if (a[last] > n) {
      cout << "No\n";
      return;
    }
	last = last - a[last];
    while (last < 1) {
        last += n;
    }
    while (last > n) {
        last -= n;
    }
  }
  cout << "Yes\n";
}
 
signed main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int t;
  cin >> t;
  while (t--) {
    solve();
  }
}
```