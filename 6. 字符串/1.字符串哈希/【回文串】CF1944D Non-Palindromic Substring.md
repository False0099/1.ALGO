A string $t$ is said to be $k$ \-good if there exists at least one substring $^\dagger$ of length $k$ which is not a palindrome $^\ddagger$. Let $f(t)$ denote the sum of all values of $k$ such that the string $t$ is $k$ \-good.

You are given a string $s$ of length $n$. You will have to answer $q$ of the following queries:

-   Given $l$ and $r$ ($l \lt; r$), find the value of $f(s_ls_{l + 1}\ldots s_r)$.

$^\dagger$ A substring of a string $z$ is a contiguous segment of characters from $z$. For example, "$\mathtt{defor}$", "$\mathtt{code}$" and "$\mathtt{o}$" are all substrings of "$\mathtt{codeforces}$" while "$\mathtt{codes}$" and "$\mathtt{aaa}$" are not.

$^\ddagger$ A palindrome is a string that reads the same backwards as forwards. For example, the strings "$\texttt{z}$", "$\texttt{aa}$" and "$\texttt{tacocat}$" are palindromes while "$\texttt{codeforces}$" and "$\texttt{ab}$" are not.

**Input**

Each test contains multiple test cases. The first line contains a single integer $t$ ($1 \leq t \leq 2 \cdot 10^4$) — the number of test cases. The description of the test cases follows.

The first line of each test case contains two integers $n$ and $q$ ($2 \le n \le 2 \cdot 10^5, 1 \le q \le 2 \cdot 10^5$), the size of the string and the number of queries respectively.

The second line of each test case contains the string $s$. It is guaranteed the string $s$ only contains lowercase English characters.

The next $q$ lines each contain two integers, $l$ and $r$ ($1 \le l \lt; r \le n$).

It is guaranteed the sum of $n$ and the sum of $q$ both do not exceed $2 \cdot 10^5$.


**Output**

For each query, output $f(s_ls_{l + 1}\ldots s_r)$.

## 样例 ：
```
5
4 4
aaab
1 4
1 3
3 4
2 4
3 2
abc
1 3
1 2
5 4
pqpcc
1 5
4 5
1 3
2 4
2 1
aa
1 2
12 1
steponnopets
1 12
```

## 结果
```text
9
0
2
5
5
2
14
0
2
5
0
65
```

## 题解
首先，我们本题要求子串不存在 K 回文串，遇到这一类问题，我们的思路都是，先去推式子，用手去模拟几个样例。对于本题的要求，我们不妨正男则反，考虑判断字符串是否满足对于任意的长度为 $k$ 的字符串，都是一个回文串。
对于 $k=1$ 的情况，我们不需要思考。因为这是平凡的。

对于 $k=2$ 的情况，如果我们满足任意长度都是一个回文串，那么我们一定满足：我们的答案形如：$aaaaaa\dots aaa$,

对于 $k=3$ 的情况，我们的答案一定形如：$a.a.a.a.a\dots.a.a.a$ 其中我们的 `.` 表示我们任意相同字符。

对于 $k=4$ 的情况，我们的答案一定形如：$aaaaaaaaaa\dots$

对于我们的 $k=5$ 的情况，我们的答案一定形如：$a.a.a.a.a.a.a.a.a\dots a$

不难发现，我们本题可以按照我们的奇偶来讨论，如果我们的长度为奇数，并且我们的答案形如：$a.a.a.a.a.$,那么我们只用统计 $[1,len]$ 中的所有偶数加起来的答案是多少即可。如果我们的长度为偶数，并且我们的答案形如：$aaaaaa$,那么我们只用统计 $[1,len]$ 中的所有奇数加起来的答案是多少即可。

但是要注意，对于我们的 $k=len$ 的情况 ,我们还需要进行特判，判断我们整个串是否本身是一个回文串，如果是，那么我们就减掉我们当前的情况。

而判断是否为回文串的方法，就是把我们的原来的串进行一个反转后，再进行一次哈希, 相当于做一遍倒着来的哈希，之后我们再去找我们的对应位置是否是相等的，注意这里我们的对应位置需要变更，例如我们在原串中的位置是 $l,r$,那么我们再新的字符串中的位置就应该去判断 $n-1-r,n-1-l$。`abccdeedcc`，`ccdeedccba`

综上，我们需要统计如下：
1. 我们某个区间是是完全由同一种字母构成，是的话，我们的偶数不用算了
2. 我们的某个区间是否是由两种字母间隔构成，（两种字母可以相同），是的话，我们的奇数可以不用算了
3. 我们的某个区间是否本身是回文串，是的话，我们的自己可以不用算了。

```cpp
#include <bits/stdc++.h>

using namespace std;
#define IOS ios::sync_with_stdio(false),cin.tie(nullptr),cout.tie(nullptr);
#define int long long


std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

struct StringHash {
    static array<int, N> mod;
    static array<int, N> base;
    vector<array<int, N>> p, h;

    StringHash() = default;

    StringHash(const string &s) {
        int n = s.size();
        p.resize(n);
        h.resize(n);
        fill(p[0].begin(), p[0].end(), 1);
        fill(h[0].begin(), h[0].end(), 1);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < N; j++) {
                p[i][j] = 1ll * (i == 0 ? 1ll : p[i - 1][j]) * base[j] % mod[j];
                h[i][j] = (1ll * (i == 0 ? 0ll : h[i - 1][j]) * base[j] + s[i]) % mod[j];
            }
    }

    array<int, N> query(int l, int r) {
        assert(r >= l - 1);
        array<int, N> ans{};
        if (l > r) return {0, 0};
        for (int i = 0; i < N; i++) {
            ans[i] = (h[r][i] - 1ll * (l == 0 ? 0ll : h[l - 1][i]) * (r - l + 1 == 0 ? 1ll : p[r - l][i]) % mod[i] +
                      mod[i]) % mod[i];
        }
        return ans;
    }
};

constexpr int HN = 2;
template<>
array<int, 2> StringHash<HN>::mod =
        {findPrime(rng() % 900000000 + 100000000),
         findPrime(rng() % 900000000 + 100000000)};
template<>
array<int, 2> StringHash<HN>::base{13331, 131};
using Hashing = StringHash<HN>;

void solve() {
    int n, q;
    cin >> n >> q;
    string s;
    cin >> s;
    Hashing h1(s);//正着求哈希 
    reverse(s.begin(), s.end());
    Hashing h2(s);//反着求哈希 
    reverse(s.begin(), s.end());
    vector e(n, vector(26, 0ll));//统计我们每一个位置的前缀数字个数 
    vector dp(n, 0ll);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 26; j++) {
            e[i][j] = e[(int) max(i - 1, 0ll)][j] + (int) (s[i] == (char) ('a' + j));
        }
    }
    for (int i = 0; i < n; i++) {
        dp[i] = (i == 0ll ? 0ll : dp[i - 1]) + (i >= 2 && s[i] == s[i - 2]);
    }

    auto is_palindromic = [&](int l1, int r1, int l2, int r2) {
        return h1.query(l1, r1) == h2.query(l2, r2);
    };
    while (q--) {
        int l, r;
        cin >> l >> r;
        l--;
        r--;
        int len = r - l + 1;
        int res = len * (len + 1) / 2 - 1 - is_palindromic(l, r, n - 1 - r, n - 1 - l) * len;
        if (len >= 4) {
            int len1 = len;
            if (dp[r] - dp[l + 1] == r - (l + 1)) {
                if (len1 & 1ll)len1 -= 1;
                res -= len1 * len1 / 4 - 1;
            }
        }
        for (int i = 0; i < 26; i++) {
            if (e[r][i] - (l == 0ll ? 0ll : e[l - 1][i]) == len) {
                res = 0ll;
            }
        }
        cout << res << endl;
    }
}

signed main() {
    IOS
    int t;
    cin >> t;
    while (t--)solve();
    return 0;
}
```
