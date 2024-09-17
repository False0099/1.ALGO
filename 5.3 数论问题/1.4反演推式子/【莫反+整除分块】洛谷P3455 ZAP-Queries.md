# [POI 2007] ZAP-Queries

## 题目描述

密码学家正在尝试破解一种叫 BSA 的密码。

他发现，在破解一条消息的同时，他还需要回答这样一种问题：

给出 $a,b,d$，求满足 $1 \leq x \leq a$，$1 \leq y \leq b$，且 $\gcd(x,y)=d$ 的二元组 $(x,y)$ 的数量。

因为要解决的问题实在太多了，他便过来寻求你的帮助。

## 输入格式

输入第一行一个整数 $n$，代表要回答的问题个数。

接下来 $n$ 行，每行三个整数 $a,b,d$。

## 输出格式

对于每组询问，输出一个整数代表答案。

## 样例 #1

### 样例输入 #1

```
2
4 5 2
6 4 3
```

### 样例输出 #1

```
3
2
```

## 提示

#### 数据规模与约定

对于全部的测试点，保证 $1 \leq n \leq 5 \times 10^4$，$1 \leq d \leq a,b \leq 5 \times 10^4$。

## 题解
$$
\begin{align}
原式&=\sum_{x=1}^{a}\sum_{y=1}^{b}[gcd(x,y)=d] \\
&=\sum_{x=1}^{a}\sum_{y=1}^{b}\left[ gcd\left( \frac{x}{d},\frac{y}{d}=1 \right) \right] \\
&=\sum_{x=1}^{a/d}\sum_{y=1}^{b/d}[gcd(x,y)=1] \\
&=\sum_{x=1}^{a/d}\sum_{y=1}^{b/d}\sum_{d|x}\mu(d) \\
&=\sum_{d=1}^{x}\sum_{x=1}^{a/d}[x整除d]\sum_{y=1}^{b/d}[y整除d]\mu(d) \\
&=\sum_{d=1}^{x}\mu(d)\left[ \frac{a}{kd} \right]\left[ \frac{b}{kd} \right]
\end{align}
$$

最后的式子，我们可以通过我们的**整数分块**在 $\sqrt{ n }$ 的时间复杂度内计算得到，于是我们的结果就是显然的。

```cpp
#include <bits/stdc++.h>
#define int long long
#define endl '\n'
int INF=0x3f3f3f3f3f3f3f3f;
using namespace std;
typedef pair<int,int> PII;
const int N=5e4+10;
bool vis[N];
int cnt=0;
int pri[N];
int phi[N];//phix
int mu[N];//miux
void init(){
    mu[1]=1;
    for(int i=2;i<N;i++){
        if(!vis[i]){
            vis[i]=1;
            pri[++cnt]=i;
            mu[i]=-1;
        }
        for(int j=1;j<=cnt&&i*pri[j]<N;j++){
            vis[i*pri[j]]=1;
            if(i%pri[j]){
                mu[i*pri[j]]=-mu[i];
                phi[pri[j]*i]=phi[i]*phi[pri[j]];
            }else{
                phi[pri[j]*i]=phi[i]*pri[pri[j]];
                mu[i*pri[j]]=0;
                break;
            }
        }
    }
    for(int i=1;i<N;i++){
        mu[i]=mu[i-1]+mu[i];
    }   
}
void solve(){
    int n,m,k;
    cin>>n>>m>>k;
    //cerr<<n<<m<<k<<endl;
    if(n>m){
        swap(n,m);
    }
    int ans=0;
    for(int l=1,r=0;l<=n;l=r+1){
        r=min(n/(n/l),m/(m/l));
        ans+=(n/l/k)*(m/l/k)*(mu[r]-mu[l-1]);
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