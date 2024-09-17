
## 题目描述
判断组合数$\binom{n}{r}$的奇偶性。

## 提示
当卢卡斯定理里p=2时的特殊情况，背就完事了

## 代码
```cpp
#include<bits/stdc++.h>
#define N 100010
using namespace std;
typedef long long ll;
ll a[N];
int p;
ll pow(ll y,int z,int p){
    y%=p;ll ans=1;
    for(int i=z;i;i>>=1,y=y*y%p)if(i&1)ans=ans*y%p;
    return ans;
}
ll C(ll n,ll m){
    if(m>n)return 0;
    return ((a[n]*pow(a[m],p-2,p))%p*pow(a[n-m],p-2,p)%p);
}
ll Lucas(ll n,ll m){
    if(!m)return 1;
    return C(n%p,m%p)*Lucas(n/p,m/p)%p;
}
inline int read(){
    int f=1,x=0;char ch;
    do{ch=getchar();if(ch=='-')f=-1;}while(ch<'0'||ch>'9');
    do{x=x*10+ch-'0';ch=getchar();}while(ch>='0'&&ch<='9');
    return f*x;
}
int main(){
    int T=read();
    while(T--){
        int n=read(),m=read();p=read();
        a[0]=1;
        for(int i=1;i<=p;i++)a[i]=(a[i-1]*i)%p;
        cout<<Lucas(n+m,n)<<endl;
    }
}

```