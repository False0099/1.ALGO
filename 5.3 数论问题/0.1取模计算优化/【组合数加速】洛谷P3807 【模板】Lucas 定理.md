# 【模板】卢卡斯定理/Lucas 定理

## 题目背景

这是一道模板题。

## 题目描述

给定整数 $n, m, p$ 的值，求出 $C_{n + m}^n \bmod p$ 的值。

输入数据保证 $p$ 为质数。

注: $C$ 表示组合数。

## 输入格式

**本题有多组数据**。

第一行一个整数 $T$，表示数据组数。

对于每组数据: 

一行，三个整数 $n, m, p$。

## 输出格式

对于每组数据，输出一行，一个整数，表示所求的值。

## 样例 #1

### 样例输入 #1

```
2
1 2 5
2 1 5
```

### 样例输出 #1

```
3
3
```

## 提示

对于 $100\%$ 的数据，$1 \leq n, m, p \leq 10^5$，$1 \leq T \leq 10$。

## 题解
本题我们试对于我们的卢卡斯定理的一个应用，我们对于我们的 lucas 公式，我们存在下面的递推：$lucas(n,m)=lucas\left( \frac{n}{p},m/p \right)*c(n\%p,m\%p)$。

我们于是就可以写出我们的下面的代码，我们需要注意下面的绩点：
1. 固定我们的 0 的逆元为 1

```
#include <bits/stdc++.h>

#define int long long

#define endl '\n'

int INF=0x3f3f3f3f3f3f3f3f;

using namespace std;

typedef pair<int,int> PII;

void init(){

}

const int N=1e6+10;

int fac[N];

int invfac[N];

int p;

int qmi(int a,int b){

    a%=p;

    int res=1;

    while(b){

        if(b&1){

            res=res*a%p;

        }

        b>>=1;

        a=(a*a)%p;

    }

    return res;

}

int c(int n,int m){

    if(m>n){

        return 0;

    }

    return ((fac[n]*invfac[n-m])%p)*invfac[m]%p;

}

int lucas(int n,int m){

    if(!m){

        cerr<<n<<" "<<m<<endl;

        return 1;

    }

    int u=lucas(n/p,m/p);

    int v=c(n%p,m%p);

    cerr<<n<<" "<<m<<" "<<u<<" "<<v<<endl;

//    cerr<<lucas(n/p,m/p)<<" "<<c(n%p,m%p)<<endl;

    return (u*v)%p;

}

void solve(){

    int n,m;

    cin>>n>>m>>p;

    fac[0]=1;

    for(int i=1;i<=p;i++){

        fac[i]=(fac[i-1]*i)%p;

    }

    invfac[0]=1;

    invfac[p-1]=qmi(p-1,p-2);

//    cerr<<invfac[p-1]<<endl;

    for(int i=p-2;i>=1;i--){

        invfac[i]=(invfac[i+1]*(i+1))%p;

//        cerr<<invfac[i]<<" ";

    }

    cout<<lucas(n+m,n)<<endl;

  

}

signed main(){

    ios::sync_with_stdio(false),cin.tie(0);

    int t;

    t=1;

    cin>>t;

//    init();

    while(t--){

        solve();

    }

}
```