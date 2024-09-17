### Problem Statement

There is a weighted simple directed graph with $N$ vertices and $M$ edges. The vertices are numbered $1$ to $N$, and the $i$ \-th edge has a weight of $W_i$ and extends from vertex $U_i$ to vertex $V_i$. The weights can be negative, but the graph does not contain negative cycles.

Determine whether there is a walk that visits each vertex at least once. If such a walk exists, find the minimum total weight of the edges traversed. If the same edge is traversed multiple times, the weight of that edge is added for each traversal.

Here, "a walk that visits each vertex at least once" is a sequence of vertices $v_1,v_2,\dots,v_k$ that satisfies both of the following conditions:

-   For every $i$ $(1\leq i\leq k-1)$, there is an edge extending from vertex $v_i$ to vertex $v_{i+1}$.
-   For every $j\ (1\leq j\leq N)$, there is $i$ $(1\leq i\leq k)$ such that $v_i=j$.

### Constraints

-   $2\leq N \leq 20$
-   $1\leq M \leq N(N-1)$
-   $1\leq U_i,V_i \leq N$
-   $U_i \neq V_i$
-   $(U_i,V_i) \neq (U_j,V_j)$ for $i\neq j$
-   $-10^6\leq W_i \leq 10^6$
-   The given graph does not contain negative cycles.
-   All input values are integers.

### Input

The input is given from Standard Input in the following format:

```
$N$ $M$
$U_1$ $V_1$ $W_1$
$U_2$ $V_2$ $W_2$
$\vdots$
$U_M$ $V_M$ $W_M$
```


### Output

If there is a walk that visits each vertex at least once, print the minimum total weight of the edges traversed. Otherwise, print `No`.


### Sample Input 1

```
3 4
1 2 5
2 1 -3
2 3 -4
3 1 100
```

### Sample Output 1

```
\-2
```

By following the vertices in the order $2\rightarrow 1\rightarrow 2\rightarrow 3$, you can visit all vertices at least once, and the total weight of the edges traversed is $(-3)+5+(-4)=-2$. This is the minimum.

## 题解
我们这一题要求我们一个经过所有边，并且我们的权值最小的一个方案是多少，我们于是可以考虑用我们的 floyd+ 状压来解决这一类最短路径长度不定的情况。

这个时候，我们需要先通过我们的 floyd 求出求出我们任意两点之间的最短路。

之后，我们对于我们的状态进行一个设置。假设我们最终停在了我们的 k 点，我们之前经过的点的状态为 S，那么我们的状态转移就可以写成我们的
```cpp
//#pragma GCC optimize(2)
//#pragma GCC optimize(3,"Ofast","inline")
//#include <bits\stdc++.h>
#include <iostream>
#include <bitset>
#include <chrono>
#include <cstring>
#include <algorithm>
#include <string>
#include <cmath>
#include <iomanip>
#include <stdio.h>
#include <cstdio>
#include <ctime>
#include <set>
#include <queue>
#include <map>
#include <stack>
#include <random>
#include <cctype>
#include <unordered_map>
#include <unordered_set>
using namespace std;
#define bs bitset
#define lg log10
#define re register
#define db double
#define ld long double
#define ll long long
#define lll __int128
#define ull unsigned long long
#define nth nth_element
#define lb lower_bound
#define ub upper_bound
#define _div stable_partition
#define _merge inplace_merge
#define point(x) setiosflags(ios::fixed)<<setprecision(x)
#define writen(x) write(x),printf("\n")
#define writet(x) write(x),printf(" ")
//const ull MOD = 212370440130137957ll;
const ll MOD = 1e9 + 7;
int test = 1;
//读入输出优化
namespace Fio {
    inline string sread() {
        string s=" ";char e=getchar();
        while(e==' '||e=='\n')e=getchar();
        while(e!=' '&&e!='\n')s+=e,e=getchar();
        return s;
    }
    inline void swrite(string s){
        for(char e:s)putchar(e);
        printf("\n");
    }
    inline ll read() {
        ll x=0,y=1;char c=getchar();
        while(!isdigit(c)){if(c=='-')y=-1;c=getchar();}
        while(isdigit(c)){x=(x<<3)+(x<<1)+(c^48);c=getchar();}
        return x*=y;
    }
    inline void write(ll x) {
        if(x<0)x=-x,putchar('-');ll sta[35],top=0;
        do sta[top++]=x%10,x/=10;while(x);
        while(top)putchar(sta[--top]+'0');
    }
}using namespace Fio;
const ll modd=1e9+7;
const ll inv2=499122177;
const ll inv6=166374059;
const db eps=0.0001;
//mt19937_64 gen(chrono::steady_clock::now().time_since_epoch().count());
//uniform_int_distribution<ll> rd(1,1e18);
//inline ll rnd(){return rd(gen);}

inline ll qpow(ll a,ll b){
    ll res=1;
    while(b){
        if(b&1)res=res*a%modd;
        a=a*a%modd,b>>=1;
    }
    return res;
}
inline ll gcd(ll a,ll b){
    if(b==0)return a;
    return gcd(b,a%b);
}
inline ll lcm(ll a,ll b){
    return a/gcd(a,b)*b;
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


ll n,m,d[25][25],dp[1<<20][25];
inline void qfl_zzz(){  
    n=read(),m=read();
    memset(d,0x3f,sizeof(d));
    for(ll i=1;i<=m;++i){
        ll u=read(),v=read();
        d[u][v]=read();
    }
    for(ll k=1;k<=n;++k)
        for(ll i=1;i<=n;++i)
            for(ll j=1;j<=n;++j)
                d[i][j]=min(d[i][j],d[i][k]+d[k][j]);
    memset(dp,0x3f,sizeof(dp));
    for(ll i=1;i<=n;++i)dp[1<<(i-1)][i]=0;
    for(ll s=0;s<(1<<n);++s)
        for(ll i=1;i<=n;++i){
            if(!((s>>(i-1))&1))continue;
            for(ll j=1;j<=n;++j){
                if(i==j||!((s>>(j-1))&1))continue;
                dp[s][i]=min(dp[s][i],dp[s-(1<<(i-1))][j]+d[j][i]);
            }
        }
    ll ans=1e18;
    for(ll i=1;i<=n;++i)ans=min(ans,dp[(1<<n)-1][i]);
    if(ans>=1e18){
        printf("No\n");
        return;
    }
    writen(ans);
} 
inline void pre_work(){

}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    srand(time(NULL));
    //freopen("uuiu.txt","r",stdin);
    //test=read(); 
    //cin>>test;
    pre_work();
    for(ll i=1;i<=test;++i){
        //printf("Case #%lld: ",i);
        qfl_zzz();
    }
    //system("pause");
    return 0;
}   
```