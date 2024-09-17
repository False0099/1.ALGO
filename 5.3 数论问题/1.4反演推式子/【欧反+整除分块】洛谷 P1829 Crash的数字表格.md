给出 n，m，求出
$$
\sum_{i=1}^n \sum_{j=1}^m lcm(i,j)
$$

## 题解
 设 $n<m$,首先看要求的式子：

![](https://storage.simpletex.cn/view/fciUV77roBDQ7uN9HMkwMLcZ7WzilIID2)


套路 1：优先枚举 gcd
$$\sum_{d=1}^nd\sum_{i=1}^n\sum_{j=1}^m[gcd(i,j)==d]$$
套路 2：$gcd(i,j)=d$ 等价于 $gcd(i/d,j/d)=1$
$$\sum_{d=1}^nd\sum_{i=1}^{\lfloor\frac nd\rfloor}\sum_{j=1}^{\lfloor\frac md\rfloor}[gcd(i,j)==1]$$


套路 3：莫比乌斯函数的性质

若 n 不为 1，则 $\sum_d|n=1$,否则原式为0.
$$\sum_{d=1}^nd\sum_{i=1}^{\lfloor\frac nd\rfloor}\sum_{j=1}^{\lfloor\frac md\rfloor}\sum_{t|gcd(i,j)}\mu(t)$$
套路 4：优先枚举 $t($ 同时设 $sum(n)=\sum_i=1^ni=\frac{n(n+1)}2)$
$$\sum_{d=1}^nd\sum_{t=1}^{\lfloor\frac nd\rfloor}t^2\mu(t)sum(\lfloor\frac n{dt}\rfloor)sum(\lfloor\frac m{dt}\rfloor)$$
套路 5：设 $dt=T$,优先枚举 $sum(\lfloor\frac nT\rfloor)sum(\lfloor\frac mT\rfloor)$ (因为这一块可以数论分块根号时间内求，具体方法语言讲不清，看代码吧)
$$\sum_{T=1}^nsum(\lfloor\frac nT\rfloor)sum(\lfloor\frac mT\rfloor)T\sum_{d|T}d\mu(T)$$

之后，我么你局可以通过我们的整除分块解决我们的问题；
```cpp
#include<bits/stdc++.h>
#define N 10010000
#define int long long
using namespace std;
inline void read(int &x)
{
    x=0;
    static int p;p=1;
    static char c;c=getchar();
    while(!isdigit(c)){if(c=='-')p=-1;c=getchar();}
    while(isdigit(c)) {x=(x<<1)+(x<<3)+(c-48);c=getchar();}
    x*=p;
}
const long long mod=20101009;
int n,m;
bool vis[N];
int cnt,prim[N],mu[N];
long long sum[N];
void get_mu(int maxn)
{
    // mu[1]=1;
    // for(int i=2;i<=maxn;i++)
    // {
    //     if(!vis[i]){prim[++cnt]=i;mu[i]=-1;}
    //     for(int j=1;j<=cnt&&prim[j]*i<=maxn;j++)
    //     {
    //         vis[i*prim[j]]=1;
    //         if(i%prim[j]==0)break;
    //         else mu[i*prim[j]]=-mu[i];
    //     }
    // }
    mu[1]=1;
    for(int i=2;i<=maxn;i++){
        if(vis[i]==0){
            vis[i]=1;
            mu[i]=-1;
            prim[++cnt]=i;
        }
        //if(!vis[i]){prim[++cnt]=i;mu[i]=-1;}
        for(int j=1;j<=cnt&&prim[j]*i<=maxn;j++)
        {
            vis[i*prim[j]]=1;
            if(i%prim[j]==0)break;
            else mu[i*prim[j]]=-mu[i];
        }
    }
    for(int i=1;i<=maxn;i++)(sum[i]=sum[i-1]+1ll*mu[i]*1ll*i%mod*1ll*i%mod)%=mod;

    
    // for(int i=1;i<=maxn;i++){
    //     (sum[i]=(sum[i-1]+1ll*mu[i]*1ll*i%mod*1ll*i%mod)%mod)%=mod;
    // }

}
signed main()
{
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
    read(n);read(m);
    int max_rep=0;
    get_mu(max_rep=min(n,m));
    long long ans=0;
    long long inv2=(mod+1ll)/2ll;
    long long summ=0;
    for(int d=1;d<=max_rep;d++)
    {
        int maxx=n/d,maxy=m/d,minn=min(maxx,maxy);
        summ=0ll;
        for(int l=1,r;l<=minn;l=r+1ll)
        {
            r=min(maxx/(maxx/l),maxy/(maxy/l));
            (summ+=(sum[r]-sum[l-1])%mod*(((1ll+maxx/l)%mod*1ll*(maxx/l)%mod*inv2%mod)%mod)%mod*(((1ll+maxy/l)%mod*1ll*(maxy/l)%mod*inv2%mod)%mod)%mod)%=mod;
        }
        (ans+=summ*1ll*d)%=mod;
    }
    cout<<(ans%mod+mod)%mod<<endl;
    return 0;
}
```