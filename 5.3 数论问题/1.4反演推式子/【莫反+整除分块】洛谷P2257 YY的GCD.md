# YY 的 GCD

## 题目描述

神犇 YY 虐完数论后给傻× kAc 出了一题

给定 $N, M$，求 $1 \leq x \leq N$，$1 \leq y \leq M$ 且 $\gcd(x, y)$ 为质数的 $(x, y)$ 有多少对。

## 输入格式

第一行一个整数 $T$ 表述数据组数。

接下来 $T$ 行，每行两个正整数，$N, M$。

## 输出格式

$T$ 行，每行一个整数表示第 $i$ 组数据的结果。

## 样例 #1

### 样例输入 #1

```
2
10 10
100 100
```

### 样例输出 #1

```
30
2791
```

## 提示

$T = 10^4$，$N, M \leq 10^7$。

## 题解
$$\sum_{p\in\text{prime}}\sum_{i=1}^n\sum_{i=1}^m[\gcd(i,j)=p]$$
根据套路提出 $p$
$$\sum_{p\in\text{prime}}\sum_{i=1}^{\left\lfloor\frac np\right\rfloor}\sum_{i=1}^{\left\lfloor\frac mp\right\rfloor}[\gcd(i,j)=1]$$
替换 $\gcd$ 得到
$$\sum_{p\in\text{prime}}\sum_{i=1}^{\left\lfloor\frac np\right\rfloor}\sum_{i=1}^{\left\lfloor\frac mp\right\rfloor}\sum_{d|\gcd(i,j)}\mu(d)$$
枚举 $d$
$$\sum_{d=1}^{\left\lfloor\frac np\right\rfloor}\mu(d)\sum_{p\in\text{prime}}\sum_{i=1}^{\left\lfloor\frac np\right\rfloor\left\lfloor\frac mp\right\rfloor}[d\mid\gcd(i,j)]$$
由于 $x$ 以内 $d$ 的倍数有 $\left\lfloor\frac xd\right\rfloor$ 个
$$\sum_{p\in\text{prime}}\sum_{d=1}^{\left\lfloor\frac np\right\rfloor}\mu(d)\left\lfloor\frac n{pd}\right\rfloor\left\lfloor\frac m{pd}\right\rfloor $$


 考虑优化：令 $k=pd$,代入得
$$\sum_{p\in\text{prime}}\sum_{d=1}^{\left\lfloor\frac np\right\rfloor}\mu(\frac kp)\left\lfloor\frac nk\right\rfloor\left\lfloor\frac mk\right\rfloor $$
枚举 $k$
$$\sum_{k=1}^n\sum_{p\in\text{prime},p|k}\mu(\frac kp)\left\lfloor\frac nk\right\rfloor\left\lfloor\frac mk\right\rfloor $$


```cpp
#include <bits/stdc++.h>
#define int long long
#define endl '\n'
int INF=0x3f3f3f3f3f3f3f3f;
using namespace std;
typedef pair<int,int> PII;
const int N=1e7+10;
int miu[N];
int vis[N];
int sum_miu[N];
int cnt=0;
int pri[N];
void init(){
    miu[1]=1;
    for(int i=2;i<N;i++){
        if(vis[i]==0){
            miu[i]=-1;
            vis[i]=1;
            pri[++cnt]=i;
            //cerr<<"pri"<<i<<endl;
        }
        for(int j=1;j<=cnt&&i*pri[j]<N;j++){
            //cerr<<i<<" "<<j<<endl;
            //cerr<<pri[j]<<endl;
            vis[i*pri[j]]=1;
            if(i%pri[j]==0){
                miu[i*pri[j]]=0;
                break;
            }else{
                miu[i*pri[j]]=miu[i]*-1;
            }
        }
    }
    for(int i=1;i<=cnt;i++){
        for(int j=1;pri[i]*j<N;j++){
            sum_miu[j*pri[i]]+=miu[j];
        }
    }
    for(int i=1;i<N;i++){
        sum_miu[i]+=sum_miu[i-1];
    }
//    cerr<<"ok"<<endl;
}
void solve(){
    int n,m;
    cin>>n>>m;

    if(n>m){
        swap(n,m);
    }
    int ans=0;
    for(int l=1,r=0;l<=n;l=r+1){
        r=min(n/(n/l),m/(m/l));
        ans+=(sum_miu[r]-sum_miu[l-1])*(n/l)*(m/l);
    }
    cout<<ans<<endl;
}
signed main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int t;
    t=1;
    cin>>t;
    init();
    while(t--){
        solve();
    }
}
```