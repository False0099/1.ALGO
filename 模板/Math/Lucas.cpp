#include<bits/stdc++.h>
using namespace std;
using ll = long long;
//lucas
struct Lucas{
    ll mod; 
    ll qpow(ll a,ll b){
        ll s=1;
        while(b){
            if(b&1) s=s*a%mod;
            a=a*a%mod;
            b>>=1;
        }       
        return s;
    }
    ll A(ll n,ll m){
        if(m>n) return 0;
        ll a=1;
        for(ll i=n-m+1;i<=n;++i){
            a=a*i%mod;
        }
        return a%mod;
    }
    ll C(ll n,ll m){
        if(m>n) return 0;
        ll a=1,b=1;
        for(ll i=n-m+1;i<=n;++i)
            a=a*i%mod;
        for(ll i=2;i<=m;++i)
            b=b*i%mod;
        return a*qpow(b,mod-2)%mod;
    }
    ll query(ll n,ll m){
        if(!m) return 1;
        else return (C(n%mod,m%mod)*query(n/mod,m/mod))%mod;
    } 
    Lucas(ll mod):mod(mod){}
};