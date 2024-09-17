# [SDOI 2012] Longge 的问题

## 题目背景

Longge 的数学成绩非常好，并且他非常乐于挑战高难度的数学问题。

## 题目描述

现在问题来了：给定一个整数 $n$，你需要求出 $\sum\limits_{i=1}^n \gcd(i, n)$，其中 $\gcd(i, n)$ 表示 $i$ 和 $n$ 的最大公因数。

## 输入格式

输入只有一行一个整数，表示 $n$。

## 输出格式

输出一行一个整数表示答案。

## 样例 #1

### 样例输入 #1

```
6
```

### 样例输出 #1

```
15
```

## 提示

#### 数据规模与约定

- 对于 $60\% $ 的数据，保证 $n\leq 2^{16}$。
- 对于 $100\% $ 的数据，保证 $1\leq n< 2^{32}$。

## 题解
本题是一个典题，我们首先可以转换我们的式子：

$$
\begin{align}
原式=\sum_{i=1}^{n} gcd(i,n) \\
=\sum_{d|n}d*\phi\left( \frac{i}{d} \right) \\

\end{align}
$$

而对于我们的上面的式子，我们就可以直接通过我们的**欧拉函数定义来暴力求解**，这是因为我们的因子个数不会超过我们的 $d$。

```cpp
#include <bits/stdc++.h>

#define int long long

#define endl '\n'

int INF=0x3f3f3f3f3f3f3f3f;

using namespace std;

typedef pair<int,int> PII;

const int N=1e5+10;

int phi[N];

bool not_prime[N];

  

void solve(){

    int n;

    cin>>n;

    auto phi=[&](int n){

        int res=n;

        for(int i=2;i*i<=n;i++){

            if(n%i==0){

                res=res/i*(i-1);

                while(n%i==0){

                    n/=i;

                }

            }

        }

        if(n>1){

            res=res/n*(n-1);

        }

        return res;

    };

    int ans=0;

    for(int i=1;i*i<=n;i++){

        if(n%i==0){

            ans+=phi(n/i)*i;

            if(i*i!=n){

                ans+=phi(i)*(n/i);

            }

        }

    }

    cout<<ans<<endl;

}

signed main(){

    ios::sync_with_stdio(false),cin.tie(0);

    int t;

    t=1;

 //   cin>>t;

   // init();

    while(t--){

        solve();

    }

}
```
