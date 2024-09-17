# [ABC 329 E] Stamp

## 题面翻译

#### 问题陈述

给你两个字符串：$S$ 由大写英文字母组成，长度为 $N$；$T$ 也由大写英文字母组成，长度为 $M\ (\leq N)$。

有一个长度为 $N$ 的字符串 $X$ 仅由字符 `#` 组成。请判断是否有可能通过执行以下任意次数的操作使 $X$ 与 $S$ 匹配：

- 在 $X$ 中选择连续的 $M$ 个字符，并用 $T$ 代替。

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc329/tasks/abc329_e

英大文字からなる長さ $ N $ の文字列 $ S $ と、英大文字からなる長さ $ M\ (\leq\ N) $ の文字列 $ T $ が与えられます。

`#` のみからなる長さ $ N $ の文字列 $ X $ があります。以下の操作を好きな回数行うことで、$ X $ を $ S $ に一致させることができるか判定してください。

- $ X $ の中から連続する $ M $ 文字を選び、$ T $ で置き換える。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ N $ $ M $ $ S $ $ T $

## 输出格式

$ X $ を $ S $ に一致させることができるならば `Yes` を、できないならば `No` を出力せよ。

## 样例 #1

### 样例输入 #1

```
7 3
ABCBABC
ABC
```

### 样例输出 #1

```
Yes
```

## 样例 #2

### 样例输入 #2

```
7 3
ABBCABC
ABC
```

### 样例输出 #2

```
No
```

## 样例 #3

### 样例输入 #3

```
12 2
XYXXYXXYYYXY
XY
```

### 样例输出 #3

```
Yes
```

## 提示

### 制約

- $ 1\ \leq\ N\ \leq\ 2\times\ 10^5 $
- $ 1\ \leq\ M\ \leq\ \min (N, $ $ 5$)
- $ S $ は英大文字からなる長さ $ N $ の文字列
- $ T $ は英大文字からなる長さ $ M $ の文字列

### Sample Explanation 1

以下、$ X $ の $ l $ 文字目から $ r $ 文字目までの部分を $ X[l:r] $ と表記します。 次のように操作を行うことで、$ X $ を $ S $ に一致させることができます。 1. $ X[3:5] $ を $ T $ で置き換える。$ X= $ `##ABC##` になる。 2. $ X[1:3] $ を $ T $ で置き換える。$ X= $ `ABCBC##` になる。 3. $ X[5:7] $ を $ T $ で置き換える。$ X= $ `ABCBABC` になる。

### Sample Explanation 2

どのように操作を行っても、$ X $ を $ S $ に一致させることはできません。

## 题解
我们遇到模拟很复杂的情况要往下面几个角度考虑：第一个是我们的枚举答案，第二个是进行我们的 dp，我们这里就是要用我们的 dp，我们的 $dp[i][j]$ 表示我们前 i 个元素都匹配 S，且第 $i$ 位匹配 $T$ 的第 $j$ 位的情况是否存在，我们最后的判断就是我们的 $dp[n][m]$
```cpp
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 2e5 + 10;

bool dp[N][7];

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    int T = 1;
    // cin >> T;
    while (T -- )
    {
        int n, m;
        cin >> n >> m;
        string s, t;
        cin >> s >> t;
        s = ">" + s;
        t = ">" + t;
        memset(dp, 0, sizeof dp);
        dp[0][0] = 1;
        for (int i = 1; i <= n; i ++ )
        {
            int ok = 0;
            for (int j = 1; j <= m; j ++ )
            {
                if (s[i] == t[j])
                    dp[i][j] |= dp[i - 1][j - 1];
                if (s[i] == t[j])
                    dp[i][j] |= dp[i - 1][m];
                ok |= dp[i][j];
                // cout << dp[i][j] << " \n"[j == m];
            }
            dp[i][0] = ok;  // 作为dp[i + 1][1]的转移依据
        }
        if (dp[n][m]) cout << "Yes\n";
        else cout << "No\n";
    }

    return 0;
}
```
```