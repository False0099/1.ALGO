Chaneka has an array $[a_1,a_2,\ldots,a_n]$. Initially, all elements are white. Chaneka will choose one or more different indices and colour the elements at those chosen indices black. Then, she will choose all white elements whose indices are multiples of the index of **at least one** black element and colour those elements green. After that, her score is the **maximum** value of $a_i$ out of all black and green elements.

There are $2^n-1$ ways for Chaneka to choose the black indices. Find the sum of scores for all possible ways Chaneka can choose the black indices. Since the answer can be very big, print the answer modulo $998\,244\,353$.

翻译：Chaneka 有一个数组 $[a_1,a_2,\ldots,a_n]$。最初，所有元素都是白色的。Chaneka 将选择一个或多个不同的下标，并将这些下表上的元素染成黑色。然后，她会选择所有下表是至少一个黑色元素下标倍数的白色元素，并将这些元素染成绿色。之后，她的得分就是所有黑色和绿色元素中 $a_i$ 的**最大**值。

Chaneka 有 $2^n-1$ 种方法来选择黑色下表。求 Chaneka 选择黑色下表的所有可能方式的得分之和。由
于答案可能很大，请打印答案的模数 $998\,244\,353$。

**Input**

The first line contains a single integer $n$ ($1 \leq n \leq 10^5$) — the size of array $a$.

The second line contains $n$ integers $a_1,a_2,a_3,\ldots,a_n$ ($0\leq a_i\leq10^5$).

**Output**

An integer representing the sum of scores for all possible ways Chaneka can choose the black indices, modulo $998\,244\,353$.

## 题解
注意读题：一个黑色选完后，所有的倍数都一定要选!

我们直接枚举方案是不现实的，我们考虑计算我们的贡献，即我们每一个位置作为答案是有多少种可能的选择方法。那么他对答案的贡献就是 $x*cnt$。我们以 $mx_{i}$ 表示将 i 位置染色后能够得到的最大值，显然我们有 $mx_{i}=max_{j\%i=0}^n a_{j}$,我们就可以预处理出来我们的 $mx_{i}$,


然后对于我们枚举到的一个值 x，他的最大方案数 $cnt$,我们按照我们 mx 数组种的元素和 x 的大小来进行分类
1. 如果是 mx 中大于 x 的值，我们直接跳过，因为去就崩
2. 如果我们等于 x 的值，我们至少要选一个，这样我们才能变成最大值，设有 $k$ 个等于 x，那么我们就有 $2^k-1$ 种方案。
3. 而对于 mx 数组中小于 x 的值，我们可以任意选择他们的对应位置，假设我们由 c 个，那么我们就有 $2^c$ 种方案。

因此，对于我们的值 x，它能够称为最大值的方案数就有 $cnt=(2^k-1)*(2^c)$ 种，那么他对答案的贡献也就可以计算出来。

其中，我们的 k 和 c 都可以通过我们将 mx 排序后二分得到。
**code**

```cpp
#include <bits/stdc++.h>
#define int long long
int n, m;
const int mod = 998244353;
struct point {
  int val, bf_idx, rank;
  bool operator<(const point& t) const {   return val < t.val; };
};
int qmi(int a, int b, int p = mod) {
  int res = 1 % p;
  while (b) {
    if (b & 1) res = res * a % p;
    a = a * a % p;
    b >>= 1;
  }
  return res;
}
using p = point;
void solve() {
  std::cin >> n;
  std::vector<int> a(n);
  for (auto& i : a) {
    std::cin >> i;
  }
  std::vector<p> now;
  std::vector<int> val(n + 1);//存储我们所有染色的初始选取位置后，我们能得到的最大是多少
  std::vector<int> arr(n + 1);
  for (int i = 1; i <= n; i++) {
    arr[i] = a[i - 1];
  }
  for (int i = 1; i <= n; i++) {
    for (int j = i; j <= n; j += i) {
      val[i] = std::max(val[i], arr[j]);//计算我们的mx_i
    }
  }
  for (int i = 0; i < n; i++) {
    now.push_back((point){val[i + 1], i, -1});
  }
  sort(begin(now), end(now));
  for (int i = 0; i < n; i++) {
    now[i].rank = i + 1;
  }
  sort(begin(now), end(now), [&](const point& a, const point& b) -> bool {
    return a.bf_idx < b.bf_idx;
  });
  int ans = 0;
  for (int i = 0; i < n; i++) {
    ans += qmi(2, now[i].rank - 1) * now[i].val;
    ans %= mod;
  }
  std::cout << ans << "\n";
}

signed main() {
  solve();
  return 0;
}
```