# Flexible String

## 题面翻译

您有一个字符串 $a$ 和一个字符串 $b$ 。这两个字符串的长度都是 $n$ 。字符串 $a$ 中最多有**个不同的字符 $10$ 。你还有一个集合 $Q$ 。最初，集合 $Q$ 是空的。您可以对字符串 $a$ 执行以下操作，次数不限：

- 选择一个索引 $i$ ( $1\leq i \leq n$ ) 和一个小写英文字母 $c$ 。将 $a_i$ 添加到集合 $Q$ 中，然后将 $a_i$ 替换为 $c$ 。

例如，将字符串 $a$ 设为" $\tt{abecca}$ "。我们可以进行以下操作：

- 在第一次操作中，如果选择 $i = 3$ 和 $c = \tt{x}$ ，字符 $a_3 = \tt{e}$ 将被添加到集合 $Q$ 中。因此，集合 $Q$ 将变为 $\{\tt{e}\}$ ，字符串 $a$ 将变为" $\tt{ab\underline{x}cca}$ "。
- 在第二次操作中，如果选择 $i = 6$ 和 $c = \tt{s}$ ，字符 $a_6 = \tt{a}$ 将添加到集合 $Q$ 中。因此，集合 $Q$ 将变为 $\{\tt{e}, \tt{a}\}$ ，字符串 $a$ 将变为" $\tt{abxcc\underline{s}}$ "。

你可以对 $a$ 进行任意数量的运算，但最终，集合 $Q$ 应该**最多包含 $k$ 个不同的字符**。在此限制条件下，我们必须最大化 $(l, r)$ ( $1\leq l\leq r \leq n$ )中 $a[l,r] = b[l,r]$ 的整数对数量。这里的 $s[l,r]$ 是指从索引 $l$ 开始（含）到索引 $r$ 结束（含）的字符串 $s$ 的子串。

数据范围：$1 \le t \le 10^4,1 \le n \le 10^5,0 \le k \le 10$。

## 题目描述

You have a string $a$ and a string $b$ . Both of the strings have length $n$ . There are at most $10$ different characters in the string $a$ . You also have a set $Q$ . Initially, the set $Q$ is empty. You can apply the following operation on the string $a$ any number of times:

- Choose an index $ i $ ( $ 1\leq i \leq n $ ) and a lowercase English letter $ c $ . Add $ a_i $ to the set $ Q $ and then replace $ a_i $ with $ c $ .

For example, Let the string $ a $ be " $ \tt{abecca} $ ". We can do the following operations:

- In the first operation, if you choose $ i = 3 $ and $ c = \tt{x} $ , the character $ a_3 = \tt{e} $ will be added to the set $ Q $ . So, the set $ Q $ will be $ \{\tt{e}\} $ , and the string $ a $ will be " $ \tt{ab\underline{x}cca} $ ".
- In the second operation, if you choose $ i = 6 $ and $ c = \tt{s} $ , the character $ a_6 = \tt{a} $ will be added to the set $ Q $ . So, the set $ Q $ will be $ \{\tt{e}, \tt{a}\} $ , and the string $ a $ will be " $ \tt{abxcc\underline{s}} $ ".

You can apply any number of operations on $ a $ , but in the end, the set $ Q $ should contain at most $ k $ different characters. Under this constraint, you have to maximize the number of integer pairs $ (l, r) $ ( $ 1\leq l\leq r \leq n $ ) such that $ a[l, r] = b[l, r] $ . Here, $ s[l, r] $ means the substring of string $ s $ starting at index $ l $ (inclusively) and ending at index $ r $ (inclusively).

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10^4 $ ). The description of the test cases follows.

The first line contains two integers $ n $ and $ k $ ( $ 1\leq n \leq 10^5 $ , $ 0\leq k\leq 10 $ ) — the length of the two strings and the limit on different characters in the set $ Q $ .

The second line contains the string $ a $ of length $ n $ . There is at most $ 10 $ different characters in the string $ a $ .

The last line contains the string $ b $ of length $ n $ .

Both of the strings $ a $ and $ b $ contain only lowercase English letters. The sum of $ n $ over all test cases doesn't exceed $ 10^5 $ .

## 输出格式

For each test case, print a single integer in a line, the maximum number of pairs $ (l, r) $ satisfying the constraints.

## 样例 #1

### 样例输入 #1

```
6
3 1
abc
abd
3 0
abc
abd
3 1
xbb
xcd
4 1
abcd
axcb
3 10
abc
abd
10 3
lkwhbahuqa
qoiujoncjb
```

### 样例输出 #1

```
6
3
6
6
6
11
```

## 提示

In the first case, we can select index $ i = 3 $ and replace it with character $ c = \tt{d} $ . All possible pairs $ (l, r) $ will be valid.

In the second case, we can't perform any operation. The $ 3 $ valid pairs $ (l, r) $ are:

1. $ a[1,1] = b[1,1] = $ " $ \tt{a} $ ",
2. $ a[1,2] = b[1,2] = $ " $ \tt{ab} $ ",
3. $ a[2,2] = b[2,2] = $ " $ \tt{b} $ ".

In the third case, we can choose index $ 2 $ and index $ 3 $ and replace them with the characters $ \tt{c} $ and $ \tt{d} $ respectively. The final set $ Q $ will be $ \{\tt{b}\} $ having size $ 1 $ that satisfies the value of $ k $ . All possible pairs $ (l, r) $ will be valid.

## 题解
我们因为我们的 k 较小，我们可以考虑暴力枚举我们修改哪些类，最多也就有 $2^{10}$ 种不同的方案，于是，我们可以考虑枚举我们的所有可行的方案，然后我们再去检查我们的这一个方案最后的答案是多少。

```cpp
#include <iostream>
#include <algorithm>
#include <bitset>
#include <vector>
#include <string>
using namespace std;
void solve()
{
    int n, k;
    cin >> n >> k;
    string a, b;
    cin >> a >> b;
    bitset<256> vis;
    vector<int> len(n+1);
    for (int i=0;i<n;++i)
        vis[a[i]] = 1;
    vector<char> q;//存储我们每个字符对应种类
    for (int i=vis._Find_first();i<256;i=vis._Find_next(i))
        q.push_back(i);
    long long ans = 0;
    for (int i=0;i<(1<<q.size());++i)
        if (__builtin_popcount(i) == k || (i == ((1 << q.size()) - 1) && k >= q.size()))
        {
            string c = a;
            for (int j=0;j<q.size();++j)
                if ((i>>j)&1)
                    for (int k=0;k<n;++k)
                        if (c[k] == q[j])
                            c[k] = b[k];//对我们的字符直接修改
            for (int i=0;i<n;++i)
                if (i == 0 || c[i] != b[i])
                    len[i] = c[i] == b[i];
                else len[i] = len[i-1] + 1;
            long long as = 0;
            for (int i=0;i<n;++i)
                as += len[i];
            ans = max(ans, as);
        }
    cout << ans << '\n';
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T;
    cin >> T;
    while (T--) solve();
    return 0;
}
```
```

```