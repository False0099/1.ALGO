# Equal XOR Segments

## 题面翻译

我们称一个数列 $x_1, x_2, \cdots, x_m$ 有意思，当且仅当它可以被分成 $k > 1$ 个部分，使得每个部分的异或和都相等。

现在给定一个长度为 $n$ 的数列 $a$，$q$ 次询问 $a$ 的子段 $a_l, a_{l + 1}, \cdots, a_r$ 是不是有意思。

## 题目描述

Let us call an array $ x_1,\dots, x_m $ interesting if it is possible to divide the array into $ k>1 $ parts so that [bitwise XOR](http://tiny.cc/xor_wiki_eng) of values from each part are equal.

More formally, you must split array $ x $ into $ k $ consecutive segments, each element of $ x $ must belong to exactly $ 1 $ segment. Let $ y_1,\dots, y_k $ be the XOR of elements from each part respectively. Then $ y_1=y_2=\dots=y_k $ must be fulfilled.

For example, if $ x = [1, 1, 2, 3, 0] $ , you can split it as follows: $ [\color{blue}1], [\color{green}1], [\color{red}2, \color{red}3, \color{red}0] $ . Indeed $ \color{blue}1=\color{green}1=\color{red}2 \oplus \color{red}3\oplus \color{red}0 $ .

You are given an array $ a_1,\dots, a_n $ . Your task is to answer $ q $ queries:

- For fixed $ l $ , $ r $ , determine whether the subarray $ a_l, a_{l+1},\dots, a_r $ is interesting.

## 输入格式

The first line contains a single integer $ t $ ( $ 1\le t\le 10^4 $ ) — the number of test cases.

The first line of each test case contains two integers $ n $ and $ q $ ( $ 2 \le n \le 2 \cdot 10^5 $ , $ 1 \le q \le 2 \cdot 10^5 $ ) — the number of elements in the array and the number of queries respectively.

The next line contains $ n $ integers $ a_1,\dots, a_n $ ( $ 0 \le a_i < 2^{30} $ ) — elements of the array.

Each of the next $ q $ lines contains two integers $ l $ and $ r $ ( $ 1 \le l < r \le n $ ) describing the query.

It is guaranteed that the sum of $ n $ over all testcases does not exceed $ 2 \cdot 10^5 $ .

It is guaranteed that the sum of $ q $ over all testcases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each query, output "YES" if the subarray is interesting and "NO" otherwise.

You can output "Yes" and "No" in any case (for example, the strings "yES", "yes", and "Yes" will be recognized as correct answers).

## 样例 #1

### 样例输入 #1

```
4
5 5
1 1 2 3 0
1 5
2 4
3 5
1 3
3 4
5 5
1 2 3 4 5
1 5
2 4
3 5
1 3
2 3
7 4
12 9 10 9 10 11 9
1 5
1 7
2 6
2 7
11 4
0 0 1 0 0 1 0 1 1 0 1
1 2
2 5
6 9
7 11
```

### 样例输出 #1

```
YES
YES
NO
NO
NO

YES
NO
NO
YES
NO

NO
NO
NO
NO

YES
NO
YES
YES
```

## 提示

Explanation for the first test case:

The first query is described in the statement.

In the second query, we should divide $ [1,2,3] $ . A possible division is $ [1,2],[3] $ , since $ 1\oplus 2=3 $ .

It can be shown that for queries $ 3,4,5 $ , the subarrays are not interesting.

## 题解
我们本题显然，因为我们没限制分成多少段，显然是分的越少越好实现。

**首先，我们注意到，如果我们这一个区间的异或和为 0，那么我们一定可以实现**

其次，如果我们最后分的区间和不为**0**，那么我们就要分成至少**3**段，我们每一段的异或和都是我们的最后的答案。那么我们根据上面的性质，就可以通过我们的二分来求解我们的答案

**注意边界条件**，

```
#include <bits/stdc++.h>
#ifdef DEBUG
#include "debug.hpp"
#else
#define debug(...) (void)0
#endif
using namespace std;
using i64 = int64_t;
using u64 = uint64_t;
using f64 = double_t;
using i128 = __int128_t;
constexpr i64 mod = 998244353;
i64 power(i64 a, i64 r, i64 res = 1) {
  for (; r; r >>= 1, a = a * a % mod)
    if (r & 1) res = res * a % mod;
  return res;
}
int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cout << fixed << setprecision(20);
  int t;
  cin >> t;
  for (int ti = 0; ti < t; ti += 1) {
    int n, q;
    cin >> n >> q;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i += 1) {
      cin >> a[i];
      a[i] ^= a[i - 1];
    }
    map<int, vector<int>> pos;
    for (int i = 0; i <= n; i += 1) pos[a[i]].push_back(i);
    for (int qi = 0, l, r; qi < q; qi += 1) {
      cin >> l >> r;
      int mr = *prev(ranges::upper_bound(pos[a[l - 1]], r));
      int ml = *ranges::lower_bound(pos[a[r]], l - 1);
      cout << (ml < mr ? "YES" : "NO") << "\n";
    }
    cout << "\n";
  }
}
```