# [ABC 263 E] Sugoroku 3

## 题面翻译

### 题目描述
一共有 $N$ 个格子编号 $1$ 到 $N$。有一个人站在 $1$ 号格子。

对于 $\forall i \in [1,N-1]$ 号格子有一个 $A_i + 1$ 面的骰子，写有 $0$ 到 $A_i$ 这些数。如果 ta 掷到了 $k$，他将往前走 $k$ 格，走到 $i+k$ 号方格。

求走到 $N$ 号方格的期望次数。对 $998244353$ 取模。

### 输入格式
第一行一个正整数 $N$，第二行 $N-1$ 个正整数表示 $A_i$。
### 输出格式
如果期望次数为 $\frac{P}{Q}$，输入最小非负整数 $R$ 使得 $R\times Q \equiv P\pmod {998244353}$。
### 数据范围
$2\leq N\leq 2\times 10^5$

$\forall i \in [1,N-1],1\leq A_i\leq N-i$

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc263/tasks/abc263_e

マス $ 1 $ からマス $ N $ の $ N $ 個のマスがあります。はじめ、あなたはマス $ 1 $ にいます。

また、マス $ 1 $ からマス $ N-1 $ にはそれぞれサイコロが置いてあります。マス $ i $ のサイコロは $ 0 $ 以上 $ A_i $ 以下の整数を等確率にランダムで出します。(サイコロを振る操作は毎回独立です。)

あなたは、マス $ N $ に到達するまで、現在いるマスに置かれているサイコロを振り、出た目の数だけ進むことを繰り返します。厳密に言うと、マス $ X $ にいるときにサイコロで $ Y $ が出た場合はマス $ X+Y $ に移動します。

サイコロを振る回数の期待値 $ \bmod\ 998244353 $ を求めてください。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ N $ $ A_1 $ $ A_2 $ $ \dots $ $ A_{N-1} $

## 输出格式

答えを出力せよ。

## 样例 #1

### 样例输入 #1

```
3
1 1
```

### 样例输出 #1

```
4
```

## 样例 #2

### 样例输入 #2

```
5
3 1 2 1
```

### 样例输出 #2

```
332748122
```

## 提示

### 注記

求める期待値は必ず有理数となることが証明できます。またこの問題の制約下では、その値を互いに素な $ 2 $ つの整数 $ P $, $ Q $ を用いて $ \frac{P}{Q} $ と表したとき、$ R\ \times\ Q\ \equiv\ P\pmod{998244353} $ かつ $ 0\ \leq\ R\ \lt\ 998244353 $ を満たす整数 $ R $ がただ一つ存在することが証明できます。この $ R $ を求めてください。

### 制約

- $ 2\ \le\ N\ \le\ 2\ \times\ 10^5 $
- $ 1\ \le\ A_i\ \le\ N-i (1\ \le\ i\ \le\ N-1) $
- 入力は全て整数。

### Sample Explanation 1

求める期待値は $ 4 $ であるため、$ 4 $ を出力します。 マス $ N $ に到達するまでの流れとしては、以下のようなものが考えられます。 - マス $ 1 $ で $ 1 $ を出し、マス $ 2 $ に移動する。 - マス $ 2 $ で $ 0 $ を出し、移動しない。 - マス $ 2 $ で $ 1 $ を出し、マス $ 3 $ に移動する。 このようになる確率は $ \frac{1}{8} $ です。

## 题解
我们本题显然，我们没有复杂的状态，我们可以把我们的对应的状态设置为：$dp[i]$ 表示我们从 $i$ 出发，走到我们的终点，我们期望走过的步数是多少。

那么我们存在一个显然的转移 $dp[i]=\frac{dp[i+1]+\dots+dp[i+k]+dp[0]}{k+1}+1$

显然，我们用对应的后缀和优化 dp 极客。
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
    while(b){
        if(b&1){
            res=(res*a)%mod;
        }
        b>>=1;
        a=(a*a)%mod;
    }
    return res;
}
void solve(){
    int n;
    cin>>n;
    vector<int> a(n+1,0);
    vector<int> f(n+1,0);
    vector<int> suf(n+2,0);
    for(int i=1;i<=n-1;i++){
        cin>>a[i];
    }
    f[n]=1;
    suf[n]=1;
    for(int i=n-1;i>=1;i--){
        f[i]=((((suf[i+1]-suf[(i+a[i]+1)])%mod+mod)%mod+a[i]+1)%mod*qmi(a[i],mod-2,mod))%mod;
        suf[i]=(suf[i+1]+f[i])%mod;
    }
    cout<<f[1]-1<<endl;
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