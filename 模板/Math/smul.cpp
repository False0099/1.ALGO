using ll = long long;
//龟速乘a 和 b 为因数 mod为模数
ll smul(ll a,ll b,ll mod){
	ll res = 0;
	while (b){
		if (b & 1) res = (res + a) % mod;
		a = (a + a) % mod;
		b >>= 1;
	}
	return res%mod;
}