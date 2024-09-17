# [HAOI 2011] Problem b

## 题目描述

对于给出的 $n$ 个询问，每次求有多少个数对 $(x,y)$，满足 $a \le x \le b$，$c \le y \le d$，且 $\gcd(x,y) = k$，$\gcd(x,y)$ 函数为 $x$ 和 $y$ 的最大公约数。

## 输入格式

第一行一个整数 $n$，接下来 $n$ 行每行五个整数，分别表示 $a,b,c,d,k$。

## 输出格式

共 $n$ 行，每行一个整数表示满足要求的数对 $(x,y)$ 的个数。

## 样例 #1

### 样例输入 #1

```
2
2 5 1 5 1
1 5 1 5 2
```

### 样例输出 #1

```
14
3
```

## 提示

对于 $100\%$ 的数据满足：$1 \le n,k \le 5 \times 10^4$，$1 \le a \le b \le 5 \times 10^4$，$1 \le c \le d \le 5 \times 10^4$。


## 题解
我们发现，对于本体而言，我们如果要直接求我们的范围，我们是**不太方便**，但是也有办法。我们可以转换为我们的前缀和计算，我们设我们的 $f(a,b)$ 表示计算我们的 $\sum_{x=1}^{a}\sum_{y=1}^{b}$
的结果，那么我们的最终询问就等于我们的 $f(a,b)-f(a-1,b)-f(a,b-1)+f(a-1,b-1)$。

```cpp
#include <bits/stdc++.h>
#define int long long
#define endl '\n'
int INF=0x3f3f3f3f3f3f3f3f;
using namespace std;
typedef pair<int,int> PII;
const int N=5e4+10;
int miu[N];
bool vis[N];
int cnt;
int pri[N];
void init(){
    miu[1]=1;
    for(int i=2;i<N;i++){
        if(vis[i]==0){
            miu[i]=-1;
            pri[++cnt]=i;
            vis[i]=1;
        }
        for(int j=1;j<=cnt&&i*pri[j]<N;j++){
            vis[i*pri[j]]=1;
            if(i%pri[j]==0){
                miu[i*pri[j]]=0;
                break;
            }else{
                miu[i*pri[j]]=miu[i]*-1;
            }
        }
    }
    for(int i=1;i<N;i++){
        miu[i]=miu[i]+miu[i-1];
    }
}
void solve(){
    int a,b,c,d,k;
    cin>>a>>b>>c>>d>>k;
    auto f=[&](int n,int m){
        n/=k;
        m/=k;
        if(n>m){
            swap(n,m);
        }
        int l,r;
        int res=0;
        for(int l=1;l<=n;l=r+1){
            r=min(n/(n/l),m/(m/l));
            res=res+1ll*(n/l)*(m/l)*(miu[r]-miu[l-1]);
        }
        return res;
    };
    cout<<f(b,d)-f(a-1,d)-f(b,c-1)+f(a-1,c-1)<<endl;
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