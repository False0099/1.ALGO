const int mod = 1e9+7;
const int N = 1e6+100;
int fac[N+2],invfac[N+2];
int qpow(int a,int b){
    int res=1;while(b){if(b&1){res=res*a%mod;}a=a*a%mod;b>>=1;}return res;
}
int inv(int x){return qpow(x,mod-2);}
void init(int n){
    fac[0] = 1;for (int i = 1; i <= n; ++i) fac[i] = fac[i - 1] * i % mod;
    invfac[n] = inv(fac[n]);for (int i = n - 1; i >= 0; --i) invfac[i] = (invfac[i + 1] * (i + 1)) % mod;    
}
int C(int n,int m){
    if (n < m || m < 0) return 0;return fac[n]*invfac[m]%mod*invfac[n-m]%mod;
}
int A(int n,int m){
    if (n < m || m < 0) return 0;return fac[n]*invfac[n-m]%mod;
}

// int D[N+2]
//错排：D[i]=(i-1)*(D[i-1]+D[i-2]) D[0]=1,D[1]=0,D[2]=1,D[3]=2;