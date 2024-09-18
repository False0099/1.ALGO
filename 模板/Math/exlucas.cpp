struct exlucas{
    using ll = long long;
    int p;
    exlucas(int p):p(p){}
    ll cnt,pr[1010],al[1010];
    void exgcd(ll a,ll b,ll &x,ll &y){
        if (!b) return (void)(x=1,y=0);
        exgcd(b,a%b,x,y);
        ll tmp=x;x=y;y=tmp-a/b*y;
    }
    ll inv(ll a,ll p){
        ll x,y;
        exgcd(a,p,x,y);
        return (x+p)%p;
    }
    ll qpow(ll a,ll b,ll p){
        ll t=1;
        a%=p;
        for(;b;b>>=1){
            if(b&1) t=t*a%p;
            a=a*a%p;
        }
        return t;
    }
    ll fac(ll n,ll p,ll ppa){
        if (n==0) return 1;
        ll cir=1,rem=1;
        for (ll i=1;i<=ppa;i++) if(i%p) cir=cir*i%ppa;
        cir=qpow(cir,n/ppa,ppa);
        for(ll i=ppa*(n/ppa);i<=n;i++) if(i%p) rem=rem*(i%ppa)%ppa;
        return fac(n/p,p,ppa)*cir%ppa*rem%ppa;
    }
    ll sum_fac(ll n,ll p){
        return n<p?0:sum_fac(n/p,p)+(n/p);
    }
    ll C(ll n,ll m,ll p,ll ppa){
        ll fz=fac(n,p,ppa),fm1=inv(fac(m,p,ppa),ppa),fm2=inv(fac(n-m,p,ppa),ppa);
        ll mi=qpow(p,sum_fac(n,p)-sum_fac(m,p)-sum_fac(n-m,p),ppa);
        return fz*fm1%ppa*fm2%ppa*mi%ppa;
    }
    void split(ll n,ll m){
        ll P=p;
        for(ll i=2;i*i<=p;i++){
            if(!(P%i)){
                ll ppa=1;
                while(!(P%i)) ppa*=i,P/=i;
                pr[++cnt]=ppa;
                al[cnt]=C(n,m,i,ppa);
            }
        }
        if(P!=1) pr[++cnt]=P,al[cnt]=C(n,m,P,P);
    }
    ll crt(){
        ll ans=0;
        for(ll i=1;i<=cnt;i++){
            ll M=p/pr[i],T=inv(M,pr[i]);
            ans=(ans+al[i]*M%p*T%p)%p;
        }
        return ans;
    }
    ll work(ll n,ll m){
        split(n,m);
        return crt();
    }
};