# [ABC 360 E] Random Swaps of Balls

## 题面翻译

有 $n$ 个球，其中有 $n-1$ 个白球和 $1$ 个黑球，最初黑球在最左边。每次操作等概率选取 $i$，再等概率选取 $j$，若 $i\ne j$ 则交换这两个球否则跳过这一条。进行 $k$ 次操作，设最终黑球落在左起第 $x$ 个，输出 $x$ 的期望值并对 $998244353$ 取模。

注意：$x$ **不一定**是整数。如果你不明白分数取模的含义，请参考 P 2613。

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc360/tasks/abc360_e

$ N\ -\ 1 $ 個の白いボールと $ 1 $ 個の黒いボールがあります。これらの $ N $ 個のボールが横一列に並んでおり、はじめ黒いボールが最も左にあります。

高橋くんは、これから以下の操作をちょうど $ K $ 回行います。

- $ 1 $ 以上 $ N $ 以下の整数を一様ランダムに選ぶ試行を $ 2 $ 回行う。選んだ整数をそれぞれ $ a,\ b $ とする。さらに、 $ a\ \neq\ b $ であれば左から $ a $ 番目のボールと $ b $ 番目のボールを交換する。
 
$ K $ 回の操作のあと黒いボールがある位置を左から $ x $ 番目とします。$ x $ の期待値を $ \text{mod}\ 998244353 $ で求めてください。

   期待値 $ \text{mod}\ 998244353 $ とは  求める期待値は必ず有理数になることが証明できます。 また、この問題の制約のもとでは、その値を既約分数 $ \frac{P}{Q} $ で表した時、$ Q\ \not\ \equiv\ 0\ \pmod{998244353} $ となることも証明できます。 よって、$ R\ \times\ Q\ \equiv\ P\ \pmod{998244353},\ 0\ \leq\ R\ &amp; lt\ 998244353 $ を満たす整数 $ R $ が一意に定まります。 この $ R $ を答えてください。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ N $ $ K $

## 输出格式

答えを $ 1 $ 行に出力せよ。

## 样例 #1

### 样例输入 #1

```
2 1
```

### 样例输出 #1

```
499122178
```

## 样例 #2

### 样例输入 #2

```
3 2
```

### 样例输出 #2

```
554580198
```

## 样例 #3

### 样例输入 #3

```
4 4
```

### 样例输出 #3

```
592707587
```

## 提示

### 制約

- $ 1\ \leq\ N\ \leq\ 998244352 $
- $ 1\ \leq\ K\ \leq\ 10^5 $
 
### Sample Explanation 1

$ 1 $ 回の操作が終わった後、黒いボールが左から $ 1 $ 番目にある確率、 $ 2 $ 番目にある確率はそれぞれ $ \displaystyle\ \frac{1}{2} $ です。よって期待値は $ \displaystyle\ \frac{3}{2} $ です。

## 题解
设每次选到的两个数为 $a,b$ ,黑球目前在 $x$。
·如果 $a\neq x$ 且 $b\neq x$,那么这轮操作就跟 $x$ 没有关系，$x$ 原地不动，概率为 $\frac{(n-1)^2}{n^2}$。
·如果 $a=b=x$,那么 $x$ 同样保持不动，概率为 $\frac1{n^2}$。
·如果 $a=x$ 或 $b=x$,那么 $x$ 等概率地换到除它以外的任何一个位置，每一位概率都为 $\frac2{n^2}$。
这时我们动用人类智慧：注意到前两种操作结果相同，于是你从第一种操作里随便拿一种情况分给第二
种，使第二种操作的概率变成 $\frac2{n^2}$,这样后面两种操作就可以合并起来了。变成，每次操作：
$\bullet$ $x$ 以 $\frac{(n-1)^2-1}{n^2}$ 的概率不受影响。
· $x$ 以 $\frac{2n}{n^2}$ 的概率随机分配到 $[1,n]$ 中任意一个位置，每个位置概率都为 $\frac2{n^2}$。
也就是说，只要 $x$ 在这个定义下 " 受到影响 ” 过一次 , 那么它的位置就会完全随机 , 不管受到几次影响都一 
样。这样 $x$ 的期望值就为 $\frac{n+1}{2}$。否则一次都没受影响就是 $x=1$。

即答案为 $(\frac{(n-1)^2-1}{n^2})^k+[1-(\frac{(n-1)^2-1}{n^2})^k]\cdot\frac{n+1}2$。

```cpp
#include <bits/stdc++.h>
#define int long long
#define endl '\n'
int INF=0x3f3f3f3f3f3f3f3f;
using namespace std;
typedef pair<int,int> PII;
void init(){
    
}
const int mod=998244353;
int qmi(int a,int b,int mod){
    int res=1;
    a%=mod;
    while ((b))
    {
        if(b&1){
            res=(res*a)%mod;
        }
        a=(a*a)%mod;
        b>>=1;
        /* code */
    }
    return res;
}
void solve(){
    int n,k;
    cin>>n>>k;
    int p1=((n-1)*(n-1)%mod-1+mod)%mod*qmi((n*n)%mod,mod-2,mod);
    cout<<(qmi(p1,k,mod)%mod+((1-qmi(p1,k,mod)%mod+mod)%mod*((n+1)%mod))%mod*qmi(2,mod-2,mod)+mod)%mod;
}
signed main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int t;
    t=1;
    //cin>>t;
    init();
    while(t--){
        solve();
    }
}
```