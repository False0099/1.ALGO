# 知识点
  ## [[FFT]] [[多项式除法]]
# 题目

## 题目描述

给定一个 $n$ 次多项式 $f(x)$ ，现在请你对于 $i \in [1,m]$ ，求出 $f(a_i)$ 。

## 输入格式

第一行两个正整数 $n,m$ 表示多项式的次数及你要求的点值的数量。

第二行 $n+1$ 个非负整数，由低到高地给出多项式的系数。

第三行 $m$ 个非负整数，表示 $a_i$ 。

## 输出格式

一共 $m$ 行，每行 $1$ 个非负整数。

第 $i$ 行的数字表示 $f(a_i)$ 。

答案对 $998244353$ 取模。

## 样例 #1

### 样例输入 #1

```
10 10
18 2 6 17 7 19 17 6 2 12 14
4 15 5 20 2 6 20 12 16 5
```

### 样例输出 #1

```
18147258
804760733
161737928
73381527
23750
973451550
73381527
525589927
842520242
161737928
```

## 提示

$n,m \in [1,64000]$，$a_i,[x^i]f(x) \in [0,998244352]$ 。

$[x^i]f(x)$ 表示 $f(x)$ 的 $i$ 次项系数。

# 思路
·首先我们先给出一个定理，对于一个多项式 $A(x)$,我们要求在多项式上的某两点的值 $A(x_{1}),A(x_{2})$,我们记 $\frac{A(X)}{X-X_{1}}$ 为 $A_{0}(x)$ ，那么我们有 $A(x_{2})=A_{0}(x_{2})$.对 $x_{1}$ 我们也有相对称的结论。
# AC 代码
```cpp

#include<cstdio>
#include<algorithm>
typedef long long LL;
const int md=998244353,N=262145;
//Poly begin
int rev[N],lim,g[20][N],M,vv;
inline void upd(int&a){a+=a>>31&md;}
inline int pow(int a,int b){
    int ret=1;
    for(;b;b>>=1,a=(LL)a*a%md)if(b&1)ret=(LL)ret*a%md;return ret;
}
inline void init(int n){
    int l=-1;
    for(lim=1;lim<n;lim<<=1)++l;M=l+1;
    for(int i=1;i<lim;++i)rev[i]=(rev[i>>1]>>1)|((i&1)<<l);vv=pow(lim,md-2);
}
void NTT(int*a,int f){
    for(int i=1;i<lim;++i)if(i<rev[i])std::swap(a[i],a[rev[i]]);
    for(int i=0;i<M;++i){
        const int*G=g[i],c=1<<i;
        for(int j=0;j<lim;j+=c<<1)
        for(int k=0;k<c;++k){
            const int x=a[j+k],y=a[j+k+c]*(LL)G[k]%md;
            upd(a[j+k]+=y-md),upd(a[j+k+c]=x-y);
        }
    }
    if(!f){
        for(int i=0;i<lim;++i)a[i]=(LL)a[i]*vv%md;
        std::reverse(a+1,a+lim);
    }
}
void INV(const int*a,int*B,int n){
    if(n==1){
        *B=pow(*a,md-2);
        return;
    }
    INV(a,B,n+1>>1);
    init(n<<1);
    static int A[N];
    for(int i=0;i<n;++i)A[i]=a[i];
    for(int i=n;i<lim;++i)A[i]=0;
    NTT(A,1),NTT(B,1);
    for(int i=0;i<lim;++i)B[i]=B[i]*(2-(LL)A[i]*B[i]%md+md)%md;
    NTT(B,0);
    for(int i=n;i<lim;++i)B[i]=0;
}
void REV(int*A,int n){std::reverse(A,A+n+1);}
void MOD(const int*a,const int*b,int*R,int n,int m){
    static int A[N],B[N],D[N];
    for(int i=0;i<n<<1;++i)D[i]=0;
    for(int i=0;i<=m;++i)B[i]=b[i];
    REV(B,m);
    for(int i=n-m+1;i<n<<1;++i)B[i]=0;
    INV(B,D,n-m+1);
    init(n-m+1<<1);
    for(int i=0;i<=n-m+1;++i)A[i]=a[n-i];
    for(int i=n-m+2;i<lim;++i)A[i]=0;
    NTT(A,1),NTT(D,1);
    for(int i=0;i<lim;++i)D[i]=(LL)D[i]*A[i]%md;
    NTT(D,0);
    REV(D,n-m);
    init(n+1<<1);
    for(int i=n-m+1;i<lim;++i)D[i]=0;
    for(int i=0;i<lim;++i)A[i]=B[i]=0;
    for(int i=0;i<=m;++i)B[i]=b[i];
    for(int i=0;i<=n;++i)A[i]=a[i];
    NTT(B,1),NTT(D,1);
    for(int i=0;i<lim;++i)B[i]=(LL)B[i]*D[i]%md;
    NTT(B,0);
    for(int i=0;i<m;++i)upd(R[i]=A[i]-B[i]);
}
//Poly end
int n,m,A[N],a[N],*P[N],len[N];
void solve(int l,int r,int o){
    if(l==r){
        len[o]=1;
        P[o]=new int[2];
        upd(P[o][0]=-a[l]),P[o][1]=1;
        return;
    }
    const int mid=l+r>>1,L=o<<1,R=L|1;
    solve(l,mid,L),solve(mid+1,r,R);
    len[o]=len[L]+len[R];
    P[o]=new int[len[o]+1];
    init(len[o]+1<<1);
    static int A[N],B[N];
    for(int i=len[L];~i;--i)A[i]=P[L][i];
    for(int i=len[L]+1;i<lim;++i)A[i]=0;
    for(int i=len[R];~i;--i)B[i]=P[R][i];
    for(int i=len[R]+1;i<lim;++i)B[i]=0;
    NTT(A,1),NTT(B,1);
    for(int i=0;i<lim;++i)A[i]=(LL)A[i]*B[i]%md;
    NTT(A,0);
    for(int i=len[o];~i;--i)P[o][i]=A[i];
}
void solve(int l,int r,int o,const int*A){
    if(l==r){printf("%d\n",*A);return;}
    const int mid=l+r>>1,L=o<<1,R=L|1;
    int B[len[o]+2<<1];
    MOD(A,P[L],B,len[o]-1,len[L]);
    solve(l,mid,L,B);
    MOD(A,P[R],B,len[o]-1,len[R]);
    solve(mid+1,r,R,B);
}
int main(){
    for(int i=0;i<19;++i){
        int*G=g[i];
        G[0]=1;
        const int gi=G[1]=pow(3,(md-1)/(1<<i+1));
        for(int j=2;j<1<<i;++j)G[j]=(LL)G[j-1]*gi%md;
    }
    scanf("%d%d",&n,&m);if(!m)return 0;
    for(int i=0;i<=n;++i)scanf("%d",A+i);
    for(int i=1;i<=m;++i)scanf("%d",a+i);
    solve(1,m,1);
    if(n>=m)MOD(A,P[1],A,n,m);
    solve(1,m,1,A);
    return 0;
}
```

# 备注
