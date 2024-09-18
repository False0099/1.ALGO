using ll = long long;
ll qpow(ll a, ll n, ll mod){
	ll res = 1;
	while (n){
		if (n & 1) res = res * a % mod;
		a = a * a % mod;
		n >>= 1;
	}
	return res%mod;
}

const int mod = 1e9+7;
int qpow(int a,int b){
    int res=1;while(b){if(b&1){res=res*a%mod;}a=a*a%mod;b>>=1;}return res;
}
int inv(int x){return qpow(x,mod-2);}