# Collapsing Strings

## 题面翻译

定义 $C(a,b)$ 如下，其中 $a,b$ 为两个字符串：

- 若 $a$ 为空，$C(a,b)=b$。

- 若 $b$ 为空，$C(a,b)=a$。

- 若 $a$ 的末尾和 $b$ 的开头一样，$C(a,b)=C(a_{1,|a|-1},b_{2,|b|})$。

- 否则，$C(a,b)=a+b$。

符号规定：

- $s_{l,r}$ 表示 $s$ 第 $l\sim r$ 位构成的字符串，从 $1$ 开始标号。

- $|s|$ 表示 $s$ 的长度。

现在，给定 $n$，$n$ 个字符串，第 $i$ 个记为 $s_i$。

求出 $\sum\limits^n_{i=1}\sum\limits^n_{j=1}C(s_i,s_j)$。

$1\le n\le10^6,1\le\sum |s_i|\le10^6$。

by [huangrenheluogu](https://www.luogu.com.cn/user/461359)

## 题目描述

You are given $ n $ strings $ s_1, s_2, \dots, s_n $ , consisting of lowercase Latin letters. Let $ |x| $ be the length of string $ x $ .

Let a collapse $ C (a, b) $ of two strings $ a $ and $ b $ be the following operation:

- If $ a $ is empty, $ C (a, b) = b $ ;
- If $ b $ is empty, $ C (a, b) = a $ ;
- If the last letter of $ a $ is equal to the first letter of $ b $ , then $ C (a, b) = C (a_{1,|a|-1}, b_{2,|b|}) $ , where $ s_{l, r} $ is the substring of $ s $ from the $ l $ -th letter to the $ r $ -th one;
- otherwise, $ C (a, b) = a + b $ , i. e. the concatenation of two strings.

Calculate $ \sum\limits_{i=1}^n \sum\limits_{j=1}^n |C (s_i, s_j)| $ .

## 输入格式

The first line contains a single integer $ n $ ( $ 1 \le n \le 10^6 $ ).

Each of the next $ n $ lines contains a string $ s_i $ ( $ 1 \le |s_i| \le 10^6 $ ), consisting of lowercase Latin letters.

The total length of the strings doesn't exceed $ 10^6 $ .

## 输出格式

Print a single integer — $ \sum\limits_{i=1}^n \sum\limits_{j=1}^n |C (s_i, s_j)| $ .

## 样例 #1

### 样例输入 #1

```
3
aba
ab
ba
```

### 样例输出 #1

```
20
```

## 样例 #2

### 样例输入 #2

```
5
abab
babx
xab
xba
bab
```

### 样例输出 #2

```
126
```

## 题解
我们把问题中的 C 函数转换为我们的 $C(a,b)=len(a)+len(b)-2*presuf(a,b)$,其中 $presuf$ 表示我们的公共的长度。

这里，我们需要一个转换：（一个完整的**最长公共前缀的贡献**，可以分割为若干个**公共前缀的贡献的和**，）
而众所周知，我们的最大公共前后缀长度，可以通过我们的 TRIE 树计算出来。具体来说，我们的 end 结点表示这个是不是我们的一个可能的前缀，我们每一次更新插入的时候，我们的 end[idx]都要++，然后我们再查询的时候，没访问到一个结点，我们就要减去对应的 `end[idx]`。

最后，我们的答案就是我们的：

```cpp
#include <iostream>
#include <string>

#define int long long

using namespace std;

int n;
string s[1000005];

struct trie {
    int son[26];
    int val;
} d[1000005];
int cnt = 0;
static inline void insert(const string &s) { // Trie 树模板
    int p = 0;
    for (auto ch : s) {
        if (!d[p].son[ch - 'a']) {
            d[p].son[ch - 'a'] = ++cnt;
        }
        p = d[p].son[ch - 'a'];
        ++d[p].val;
    }
}
static inline int query(const string &s) {
    int p = 0;
    int ret = 0;
    for (int i = s.size() - 1; i >= 0; --i) {
        char ch = s[i];
        if (!d[p].son[ch - 'a']) {
            break;
        }
        p = d[p].son[ch - 'a'];
        ret += d[p].val;
    }
    return ret * 2;
}

signed main() {
#ifndef ONLINE_JUDGE
    freopen("CF1902E.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n;
    int ans = 0;
    for (int i = 1; i <= n; ++i) {
        cin >> s[i];
        insert(s[i]);
        ans += (s[i].size() * n) << 1; // 假设没有重复的前后缀
    }
    for (int i = 1; i <= n; ++i) {
        ans -= query(s[i]); // 容斥 减掉重复答案
    }
    cout << ans << endl;
    return 0;
}
```