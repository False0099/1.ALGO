#include <bits/stdc++.h>

using namespace std;
#define IOS ios::sync_with_stdio(false),cin.tie(nullptr),cout.tie(nullptr);
#define int long long


std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

bool isprime(int n) {
    if (n <= 1) return false;
    for (int i = 2; i * i <= n; i++)
        if (n % i == 0)
            return false;
    return true;
}

int findPrime(int n) {
    while (!isprime(n))
        n++;
    return n;
}

template<int N>
struct StringHash {
    static array<int, N> mod;
    static array<int, N> base;
    vector<array<int, N>> p, h;

    StringHash() = default;

    StringHash(const string &s) {
        int n = s.size();
        p.resize(n);
        h.resize(n);
        fill(p[0].begin(), p[0].end(), 1);
        fill(h[0].begin(), h[0].end(), 1);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < N; j++) {
                p[i][j] = 1ll * (i == 0 ? 1ll : p[i - 1][j]) * base[j] % mod[j];
                h[i][j] = (1ll * (i == 0 ? 0ll : h[i - 1][j]) * base[j] + s[i]) % mod[j];
            }
    }

    array<int, N> query(int l, int r) {
        assert(r >= l - 1);
        array<int, N> ans{};
        if (l > r) return {0, 0};
        for (int i = 0; i < N; i++) {
            ans[i] = (h[r][i] - 1ll * (l == 0 ? 0ll : h[l - 1][i]) * (r - l + 1 == 0 ? 1ll : p[r - l][i]) % mod[i] +
                      mod[i]) % mod[i];
        }
        return ans;
    }
};

constexpr int HN = 2;
template<>
array<int, 2> StringHash<HN>::mod =
        {findPrime(rng() % 900000000 + 100000000),
         findPrime(rng() % 900000000 + 100000000)};
template<>
array<int, 2> StringHash<HN>::base{13331, 131};
using Hashing = StringHash<HN>;

void solve() {
    int n,m;
    cin>>n>>m;
    string a;
    string b;
    cin>>a>>b;
    if(n>m){
        swap(n,m);
        swap(a,b);
    }
    Hashing ha=(a);//a的正向哈希
    reverse(a.begin(),a.end());
    Hashing ah=(a);//a的反向哈希
    //reverse(a.begin(),a.end());
    
    Hashing hb=(b);//b的正向哈希
    reverse(b.begin(),b.end());
    Hashing bh=(b);//b的反向哈希
    //reverse(b.begin(),b.end());
    auto is_palindromic_a = [&](int l1, int r1, int l2, int r2) {
        return ha.query(l1, r1) == ah.query(l2, r2);
    };
     auto is_palindromic_b = [&](int l1, int r1, int l2, int r2) {
        return hb.query(l1, r1) == bh.query(l2, r2);
    };
    vector<int> p;
    int lenprev=0;
    for(int i=0;i<n;i++){
        if(ha.query(0,i)==bh.query(0,i)){
            if(is_palindromic_a(0, i, n-1-i, n-1)&&is_palindromic_b(m-1-i, m-1, 0, i)){
                p.push_back(i+1);
            }
        }
    }//判断我们的正向字符串
    stack<int> q;
    int lensuf=0;
    for(int i=0;i<n;i++){
        if(ha.query(n-i-1,n-1)==hb.query(0,i)){
            if(is_palindromic_a(n-i-1,n-1,0,i)&&is_palindromic_b(0,i,m-1-i,m-1)){
                q.push(i+1);
				//lensuf=i+1;
            }
        }
    }//判断我们的逆向字符串
    int ans=-1;
    for(auto x:p){
    	while(q.size()&&q.top()+x>min(n,m)) q.pop();
    	if(q.size()==0) break;
    	ans=max(ans,2*(x+q.top()));
	}
	cout<<ans<<"\n";
	return;
}

signed main() {
    IOS
    int t;
    t=1;
    while (t--)solve();
    return 0;
}