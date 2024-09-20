int mod=1e9+7;
struct Matrix {
	ll s[105][105];
    ll n;
	Matrix(ll n):n(n){
		memset(s, 0, sizeof(s));
	}
	inline void unit() {
		for (ll i = 1; i <= n; i++)
			s[i][i] = 1;
	}
    Matrix operator* (const Matrix &b) const{
        Matrix c(n);
        for (ll i = 1; i <= n; i++) {
            for (ll j = 1; j <= n; j++) {
                for (ll k = 1; k <= n; k++) {
                    c.s[i][j] = (c.s[i][j] + s[i][k] * b.s[k][j]) % mod;
                }
            }
        }
        return c;
    }
    Matrix operator *= (const Matrix &b){
        *this = *this*b;
        return *this;
    }
    Matrix operator ^(ll b){
        Matrix tmp(n);
        tmp.unit();
        while (b) {
            if (b&1)
                tmp*=*this;
            *this*=*this;
            b >>= 1;
        }
        return tmp;
    }
    friend Matrix qpow(Matrix a,Matrix b,ll time){
        while(time){
            if(time&1) a=a*b;
            b=b*b;
            time>>=1;
        }
        return a;
    }
    Matrix operator ^=(ll b){
        *this=*this^b;
        return *this;
    }
    ll* operator[](ll index) {
        return s[index];
    }
};