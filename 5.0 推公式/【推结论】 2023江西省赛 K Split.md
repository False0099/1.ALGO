You are given a positive integer $n$ and a non-increasing sequence $a_i$ of length $n$ , satisfying $\forall i \in [1,n-1],a_i \ge a_{i+1}$.

Then, you are given a positive integer $m$, which represents the total number of operations.

There are two types of operations. The first type gives an integer $x$ satisfying $1&lt;x&lt;n$ and changes $a_x$ to $a_{x-1}+a_{x+1}-a_x$.

The second type is query operation and gives an integer $k$ . Assuming the sequence is divided into $k$ segments, and the length of each segment must be at least $1$. The value of a segment is defined as the difference between the maximum element and the minimum element of the segment. You should print the mininum sum of the values of the $k$ segments for all possible ways to divide the sequence into $k$ segments.

Specifically, for each operation, you will be given the type of the operation first. If it is $0$, it means the first type of operation, and if it is $1$, it means the second type of operation. For the first type of operation, you will then be given a positive integer $x$. For the second type of operation, you will then be given a positive integer $k$.

**Input**

The first line contains a positive integer $n$ $(3 \le n \le 10^6 )$, representing the length of the sequence.

The second line contains $n$ positive integers $a_1, a_2, ... , a_{n}$ $(1 \le a_i \le 10^9 )$.

The third line contains a positive integer $m$ $(1 \le m \le 10^6)$, representing the total number of operations.

Next $m$ lines, each line containing either "$0$ $x$" $(1 &lt; x &lt; n)$ or "$1$ $k$" $(1 \le k \le n )$, denoting an operation.


**Output**

Print $q$ lines where the $i$ \-th line contains one integer — the answer for the $i$ \-th query operation.

## 样例
```
5
30 20 18 13 2
3
1 2
0 3
1 3

```

```
17
7

```

## 题解
我们本题的思路是：限制考虑我们的询问操作，我们容易发现，如果在 $i,i+1$ 之间切开，$a[i]$ 是前一段的最小值，$a[i+1]$ 是后一段的最大值，那么对答案的共线就是 $a[i+1]-a[i]$，于是我们就可以通过把我们的差分数组排序后再去取前 $k-1$ 小即可。

而我们的修改，其实只不过是交换了我们的左右两个间隔，对于我们的答案没有影响，于是我们就可以直接看 k 说话了。

```cpp
// created on Lucian Xu's Laptop

#include <bits/stdc++.h>

// using namespace std;

typedef unsigned int UI;
typedef unsigned long long ULL;
typedef long long LL;
typedef unsigned long long ULL;
typedef __int128 i128;
typedef std::pair<int, int> PII;
typedef std::pair<int, LL> PIL;
typedef std::pair<LL, int> PLI;
typedef std::pair<LL, LL> PLL;
typedef std::vector<int> vi;
typedef std::vector<vi> vvi;
typedef std::vector<LL> vl;
typedef std::vector<vl> vvl;
typedef std::vector<PII> vpi;

#define typet typename T
#define typeu typename U
#define types typename... Ts
#define tempt template <typet>
#define tempu template <typeu>
#define temps template <types>
#define tandu template <typet, typeu>

#define ff first
#define ss second
#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()

#ifdef LOCAL
#include "debug.h"
#else
#define debug(...) \
    do {           \
    } while (false)
#endif

constexpr int mod = 998244353;
constexpr int inv2 = (mod + 1) / 2;
constexpr int inf = 0x3f3f3f3f;
constexpr LL INF = 1e18;
constexpr double pi = 3.141592653589793;
constexpr double eps = 1e-6;

constexpr int lowbit(int x) { return x & -x; }
constexpr int add(int x, int y) { return x + y < mod ? x + y : x - mod + y; }
constexpr int sub(int x, int y) { return x < y ? mod + x - y : x - y; }
constexpr int mul(LL x, int y) { return x * y % mod; }
constexpr void Add(int& x, int y) { x = add(x, y); }
constexpr void Sub(int& x, int y) { x = sub(x, y); }
constexpr void Mul(int& x, int y) { x = mul(x, y); }
constexpr int pow(int x, int y, int z = 1) {
    for (; y; y /= 2) {
        if (y & 1) Mul(z, x);
        Mul(x, x);
    }
    return z;
}
temps constexpr int add(Ts... x) {
    int y = 0;
    (..., Add(y, x));
    return y;
}
temps constexpr int mul(Ts... x) {
    int y = 1;
    (..., Mul(y, x));
    return y;
}

tandu bool Max(T& x, const U& y) { return x < y ? x = y, true : false; }
tandu bool Min(T& x, const U& y) { return x > y ? x = y, true : false; }

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);

    int t = 1;
    // std::cin >> t;
    while (t--) {
        int n, q;
        std::cin >> n;
        vi a(n + 1), b;
        for (int i = 1; i <= n; i++) {
            std::cin >> a[i];
            if (i > 1) b.push_back(a[i - 1] - a[i]);
        }
        std::sort(rall(b));
        for (int i = 1; i < (int) b.size(); i++) {
            b[i] += b[i - 1];
        }
        reverse(all(b));
        b.push_back(0);
        reverse(all(b));
        int maxx = a[1] - a[n];
        std::cin >> q;
        while (q--) {
            int op, x;
            std::cin >> op >> x;
            if (op == 1) {
                std::cout << maxx - b[x - 1] << '\n';
            } else {
            }
        }
    }
    return 0;
}

```