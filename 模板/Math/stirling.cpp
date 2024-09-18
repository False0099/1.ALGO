//stirling
template<typename T>
struct stirling{
    #define maxn 105
    T s[maxn][maxn]={0};
    void init(){
        int i,j;
        for(i=0;i<maxn;i++){
            s[i][0]=1;s[i][i]=1;
        }
        for(i=2;i<maxn;i++){
            for(j=1;j<i;j++){
                s[i][j]=s[i-1][j-1]+s[i-1][j]*(j+1);
            }
        }
    }
    inline T query(int n,int k){
        return s[n-1][k-1];
    }
    inline T fac(int i){
        if(i==1){
            return 1;
        }else{
            return i*fac(i-1);
        }
    }
    stirling(){
        init();
    }
    #undef maxn
};


const int mod = 1e9+7;
const int N = 1e6+100;
int fac[N+2],invfac[N+2];
int qpow(int a,int b,int mod){
    int res=1;while(b){if(b&1){res=res*a%mod;}a=a*a%mod;b>>=1;}return res;
}
int inv(int x){return qpow(x,mod-2,mod);}
void init(int n){
    fac[0] = 1;for (int i = 1; i <= n; ++i) fac[i] = fac[i - 1] * i % mod;
    invfac[n] = inv(fac[n]);for (int i = n - 1; i >= 0; --i) invfac[i] = (invfac[i + 1] * (i + 1)) % mod;    
}
int C(int n,int m){
    if (n < m || m < 0) return 0;return fac[n]*invfac[m]%mod*invfac[n-m]%mod;
}
int S(int n,int k){
    int ans=0;
    for(int i=0;i<=k;i++){
        ans=(ans+mod)%mod;
        ans=(ans+(i%2?-1:1)*C(k,i)%mod*qpow(k-i,n,mod)%mod)%mod;
    }  
    ans=ans*invfac[k]%mod;
    return ans;
}