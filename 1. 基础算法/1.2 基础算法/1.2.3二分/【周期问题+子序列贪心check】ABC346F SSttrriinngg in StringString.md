# [ABC 346 F] SSttrriinngg in StringString

## 题面翻译

对于一个字符串 $X$ 和一个非负整数 $k$，定义 $f(X, k)$ 表示将 $X$ 重复 $k$ 次得到的字符串，$g(X, k)$ 表示将 $X$ 的每个字符重复 $k$ 次得到的字符串。例如当 $X = \texttt{abc}$ 时，$f(X, 2) = \texttt{abcabc}, g(X, 3) = \texttt{aaabbbccc}$。特别的，当 $k = 0$ 时，$f(X, k), g(X, k)$ 为空串。

给定两个字符串 $S, T$ 和一个正整数 $n$。求最大的非负整数 $k$ 满足 $g(T, k)$ 是 $f(S, n)$ 的子序列。

$1 \le n \le 10^{12}$，$1 \le |S|, |T| \le 10^5$。

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc346/tasks/abc346_f

長さ $ n $ の文字列 $ X $ に対して、$ X $ を $ k $ 回繰り返して得られる文字列を $ f (X, k) $ と表記し、$ X $ の $ 1 $ 文字目、$ 2 $ 文字目、$ \dots $、$ n $ 文字目を $ k $ 回ずつこの順に繰り返して得られる文字列を $ g (X, k) $ と表記します。例えば、$ X= $ `abc` のとき、$ f (X, 2)= $ `abcabc`、$ g (X, 3)= $ `aaabbbccc` です。 また、任意の文字列 $ X $ に対して、$ f (X, 0) $ と $ g (X, 0) $ は共に空文字列です。

正整数 $ N $ および文字列 $ S, T $ が与えられます。 $ g (T, k) $ が $ f (S, N) $ の（連続とは限らない）部分列であるような最大の非負整数 $ k $ を求めてください。 なお、定義より、$ g (T, 0) $ は常に $ f (S, N) $ の部分列であることに注意してください。

部分列とは文字列 $ X $ の（連続とは限らない）部分列とは、$ X $ から $ 0 $ 個以上の文字を取り除いた後、残りの文字を元の順序で連結して得られる文字列のことをいいます。例えば、`ac`、`atcoder`、` `（空文字列）などはどれも `atcoder` の部分列ですが、`ta` は `atcoder` の部分列ではありません。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ N $ $ S $ $ T $

## 输出格式

$ g (T, k) $ が $ f (S, N) $ の（連続とは限らない）部分列であるような最大の非負整数 $ k $ を出力せよ。

## 样例 #1

### 样例输入 #1

```
3
abc
ab
```

### 样例输出 #1

```
2
```

## 样例 #2

### 样例输入 #2

```
3
abc
arc
```

### 样例输出 #2

```
0
```

## 样例 #3

### 样例输入 #3

```
1000000000000
kzazkakxkk
azakxk
```

### 样例输出 #3

```
344827586207
```

## 提示

### 制約

- $ N $ は整数
- $ 1\leq\ N\leq\ 10^{12} $
- $ S,\ T $ は英小文字からなる長さ $ 1 $ 以上 $ 10^5 $ 以下の文字列

### Sample Explanation 1

$ f (S, 3)= $ `abcabcabc` です。 $ g (T, 2)= $ `aabb` は $ f (S, 3) $ の部分列ですが、$ g (T, 3)= $ `aaabbb` は $ f (S, 3) $ の部分列ではないので、$ 2 $ を出力します。

## 题解
本题我们的一个简单的思路是，通过**二分我们的答案**，然后 check，如果我们重复了 x 次之后，我们是不是重复 n 次就可以达到？

这里，我们的 check 是**比较 border**的，我们有很多要讨论的边界条件，这里因为涉及到我们的周期性问题，对于这一类问题，我们从下面的几个角度入手：
1. 我们的一个周期能够给我们的答案贡献多少次
2. 我们的余数，我们应该怎么去处理我们的结果？

这里，我们的第一个部分是简单的，假设我们一个字符串中有 $k$ 个 a 字符，那么我们的一个周期就可以**提供给我们的 k 个字符**。

接下来就是我们的第二个问题，我们假设现在剩余了 $x$ 个字母，我们要怎么在我们的字符串中继续处理？显然，如果我么现在剩余了 x 个字符，我们会去找到我们的从 0 开始往后的第 $x$ 个对应字符的位置，这个位置+1，就是我们需要的结果。

**注意到，我们的这一个位置会影响到我们的后来的数字**，于是我们考虑计算这一个位置对于我们的后来数字的影响，即可得到我们的最终结果。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

#define int ll

const int N = 1e5 + 5, K = 26;

char s[N], t[N]; int n, sn, st;
int pos[N][K], suf[N][K], pre[N][K];
int cnt[26];

bool chk(int k)
{
    int p = 1, q = 1;
    for(int i = 1; i <= st; i ++)
    {
        int c=t[i]-'a';
        if(cnt[c]==0){
            return false;
        }
        int k0=k;
        int T=cnt[c];
        if(k0>T){//这里为什么不能等于？
            p+=(k0-1)/T;
            //为什么是k0-1，因为是下取整，对于剩下的单独的周期，我们单独处理
            k0 = k0 - (k0 - 1) / cnt[c] * cnt[c];
        }
        if(k0>suf[q][c]){//看能否把我们的后缀跳完，能跳玩我们就跳完，进入下一个位置
            k0-=suf[q][c];
            p++;
            q=1;
        }
        q=pos[pre[q-1][c]+k0][c]+1;
        if(q > sn) q = 1, p ++;
    }
//    cerr<<p<<endl;
    if(q == 1) p --;
    return p <= n;
}

signed main()
{
    ios::sync_with_stdio(0);cin.tie(0);
    cin >> n >> s + 1 >> t + 1;
    sn = strlen(s + 1);
    st = strlen(t + 1);
    for(int i = sn; i >= 1; i --)
    {
        cnt[s[i] - 'a'] ++;
        for(int j = 0; j < K; j ++) suf[i][j] = cnt[j];
    }
    memset(cnt, 0, sizeof cnt);
    for(int i = 1; i <= sn; i ++)
    {
        cnt[s[i] - 'a'] ++;
        pos[cnt[s[i] - 'a']][s[i] - 'a'] = i;
        for(int j = 0; j < K; j ++) pre[i][j] = cnt[j];
    }
    int l = 0, r = n * sn / st;
    while(l < r)
    {
        int mid = l + r + 1 >> 1;
        if(chk(mid)) l = mid;
        else r = mid - 1;
    }
    chk(2);
//    cerr<<chk(l)<<endl;
    cout << l;

    return 0;
}
```