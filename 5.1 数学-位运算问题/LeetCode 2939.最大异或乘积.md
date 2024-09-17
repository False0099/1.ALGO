给你三个整数 `a` ，`b` 和 `n` ，请你返回 `(a XOR x) * (b XOR x)` 的 **最大值** 且 `x` 需要满足 `0 <= x < 2n`。

由于答案可能会很大，返回它对 `109 + 7` **取余** 后的结果。

**注意**，`XOR` 是按位异或操作。

**示例 1：**

**输入：**a = 12, b = 5, n = 4
**输出：**98
**解释：**当 x = 2 时，(a XOR x) = 14 且 (b XOR x) = 7 。所以，(a XOR x) * (b XOR x) = 98 。
98 是所有满足 0 <= x < 2n 中 (a XOR x) * (b XOR x) 的最大值。

**示例 2：**

**输入：**a = 6, b = 7 , n = 5
**输出：**930
**解释：**当 x = 25 时，(a XOR x) = 31 且 (b XOR x) = 30 。所以，(a XOR x) * (b XOR x) = 930 。
930 是所有满足 0 <= x < 2n 中 (a XOR x) * (b XOR x) 的最大值。

**示例 3：**

**输入：**a = 1, b = 6, n = 3
**输出：**12
**解释：** 当 x = 5 时，(a XOR x) = 4 且 (b XOR x) = 3 。所以，(a XOR x) * (b XOR x) = 12 。
12 是所有满足 0 <= x < 2n 中 (a XOR x) * (b XOR x) 的最大值。

**提示：**

- `0 <= a, b < 250`
- `0 <= n <= 50`

## 题解
我们这一题可以考虑用我们的贪心法去构造，对于我们 $bit$ 位大于 n 的部分，我们没法修改，我们直接保留，假设我们的 A 的二进制表示为 $000111$,我们的 $B$ 的二进制表示为 $111000$,那么我们对于两个不同位，我们考虑把出现的第一个位置存储到 f，后边的其他位置累加到 s，**目的是使两者的差值 $f-s$ 最小化。因为和相同时，差越小，乘积越大**

```cpp
class Solution {
public:
#define ll long long
    int maximumXorProduct(long long a, long long b, int n) {
        ll x = 0, f = 0, s = 0;
        int mod = 1e9 + 7;
        ll p1 = a & (~((1LL << n) - 1));
        ll p2 = b & (~((1LL << n) - 1));
        x = min(p1, p2);
        if (p1 != p2) { // bit位大于等于n的部分，存在差异
            f = max(p1, p2) - x;
        }
        for (int i = n - 1; i >= 0; --i) {
            ll h1 = a & (1LL << i), h2 = b & (1LL << i);
            if (h1 && h2) { // 两者都为1
                x += h1;
            } else if (h1 || h2) { // 两者只存在一个为1
                if (!f) {
                    f = h1 + h2;
                } else {
                    s += h1 + h2;
                }
            } else { // 两者都为0
                x += (1LL << i);

            }
        }
        ll a1 = x + f, b1 = x + s;
        printf("(%lld, %lld)\n", a1, b1);
        return (a1 % mod) * (b1 % mod) % mod;
    }
};
```