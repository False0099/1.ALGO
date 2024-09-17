苯 q 是一名强大的苯环，经常给阿宁带来每日一题，阿宁因为太蒻了，每次都能获得提升。

![](https://uploadfiles.nowcoder.com/images/20231219/0_1702976359562/59722717A62E238DE78489B79B251C96)  

  

现在苯 q 又来了一道每日一题：

给一个长度为 $n$ 的数组 $a$。一开始分数为 $0$。按照  $a_1,a_2,a_3,...,a_n$ 的顺序决定每一个数选或者不选。

每选够了 $6$ 个数时，假设分别是 $b_1,b_2,b_3,b_4,b_5,b_6$，那么可以获得 $((b_1-b_2)\times b_3-b_4)\times b_5 -b_6$ 分数。

问，最多获得多少分数？

## 输入：
第一行输入一个整数 $n$。  
第二行输入 $n$ 个整数 $a_i$。  
$1\leq n\leq 10^3$  
$-100 \leq a_i\leq 100$

## 输出：
输出一个整数，表示最多能获得的分数。


## 题解
我们本题考虑使用 dp，因为我们的权值可能为负数，所以我们要同时记录两个，一个是我们的最大值，一个是我们的最小值。

我们其实本题可以分割成两个部分，第一个部分是求我们的以 i 结尾的最大价值是多少，另一个是计算 $(i,j)$ 部分的最大价值。

其中第一个是我们要求的最终答案，我们的转移有：$ans[j]=max(ans[j],ans[i]+calc(i,j))$
其中，我们的 $calc(i,j)$ 可以通过我们的 $dp$ 来进行计算。


其中，我们对于我们的 $calc(i,j)$ 状态设计也相对来说比较直球，我么设 $dp[i][States]$ 表示表示我们 i 强制选强制选，进入到 j 状态状态时的最大价值，$pd[i][States]$ 表示我们 i 强制选，进入到 j 状态状态时的最小价值。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define lll __int128
const ll modd=998244353;
const ll inf=1e18;

inline ll qpow(ll a,ll b){
    ll res=1;
    while(b){
        if(b&1)res=res*a%modd;
        a=a*a%modd;b>>=1;
    }
    return res;
}
inline ll exgcd(ll a,ll b,ll &x,ll &y){
    if(b==0){
        x=1,y=0;
        return a;
    }
    ll d=exgcd(b,a%b,y,x);
    y-=a/b*x;
    return d;
}


ll n,a[1005],dp[1005][7],f[1005][7],mx[1005];
inline void qfl_zzz(){  
    cin>>n;
    for(ll i=1;i<=n;++i)cin>>a[i];
    for(ll i=1;i<=n;++i){
        memset(dp,-0x3f,sizeof(dp));
        memset(f,0x3f,sizeof(f));
        for(ll j=i;j<=n;++j){
            for(ll k=1;k<=6;++k){
                dp[j][k]=dp[j-1][k];
                f[j][k]=f[j-1][k];
            }
            dp[j][1]=max(dp[j][1],a[j]);
            f[j][1]=min(f[j][1],a[j]);
            for(ll k=2;k<=6;++k){
                if(k%2==0){
                    if(dp[j-1][k-1]>-1e18)dp[j][k]=max(dp[j][k],dp[j-1][k-1]-a[j]);
                    if(f[j-1][k-1]<1e18)f[j][k]=min(f[j][k],f[j-1][k-1]-a[j]);
                }
                else{
                    if(dp[j-1][k-1]>-1e18)dp[j][k]=max(dp[j][k],dp[j-1][k-1]*a[j]);
                    if(f[j-1][k-1]<1e18)f[j][k]=min(f[j][k],f[j-1][k-1]*a[j]);
                    if(f[j-1][k-1]<1e18)dp[j][k]=max(dp[j][k],f[j-1][k-1]*a[j]);
                    if(dp[j-1][k-1]>-1e18)f[j][k]=min(f[j][k],dp[j-1][k-1]*a[j]);
                }
            }
            mx[j]=max(mx[j],mx[i-1]+dp[j][6]);
        }
    }
    ll ans=0;
    for(ll i=1;i<=n;++i)ans=max(ans,mx[i]);
    cout<<ans;
}            
inline void pre_work(){

}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    
    cout<<setiosflags(ios::fixed)<<setprecision(10);

#ifdef LOCAL
    freopen("oo.in","r",stdin);
    freopen("oo.out","w",stdout);
#endif

    pre_work();

    int T=1;
    //cin>>T;
    while(T--)qfl_zzz();

    return 0;
}
```

