## 题意
定义字符串 $S=S_0+\cdots+S_{n-1}$ 循环位移 $k$ 次为
$S(k)=S_{k\:\mathrm{mod~}n}+\cdots+S_{n-1}+S_{0}+\cdots+S_{(k-1)\:\mathrm{mod~}n}$.
定义 $[A]=\backslash$ set $A(k),k\in\mathbb{N}.$
给出 $T$ 组串 $A,B$,询问 $B$ 有多少个子串在 $[A]$ 中。
## 输入：
第一行一个 $T$ 表示输入组数。
接下来每行两个字符串，表示 $A$ 和 $B$,保证 $|A|\leq|B|$。保证 $\sum|B|\leq1048576$., 并且字符串均由大写字母组成。

## 输出
输出 $T$ 行，每行一个数表示答案。

## 题解
本题我们不难发现，我们循环移位可以转换为**倍长后取子串**，然后我们再去看我们的 B 中有多少个字串在我们的 A 的循环移位集合中。

这一点，我们可以先预处理出我们的 $A$ 的**所有循环移位的结果**，然后我们知道我们的**长度是固定的**。所以我们可以在我么的**B**中固定我们的一个断点，然后求以这个断点为**起点时，我们的对应子串是否出现过**。这个时候，我们的最终答案就可以显然求出来了。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define INF 0x3f3f3f3f3f3f3f3f
#define L(i, j, k) for (int i = (j); i < (k); ++i)
#define R(i, j, k) for (int i = (j); i >= (k); --i)
#define _L(i, j, k) for (int i = (j); i <= (k); ++i)
#define all(x) (x).begin(), (x).end()
#define allp(x, n) (x).begin() + (n), (x).end()
#define ms(x, y) memset(x, y, sizeof(x))
#define dbg(x) cerr << __LINE__ << " | " << #x << " = " << x << "\n"
#define dbgl(i, x) cerr << __LINE__ << " [" << #i << "]: " << i << " -> { " << #x << " = " << x << " }\n"
#define in(a, l, r) for (int i = l; i < r; cin >> a[i], i++)
#define bp cerr << "breakpoint" << "\n"
#define YES cout << "YES" << "\n"
#define NO cout << "NO" << "\n"
#define Yes cout << "Yes" << "\n"
#define No cout << "No" << "\n"

  

#ifdef KROWFEATHER

#include <bits/KrowFeather.h>

#endif

#define int long long

using ull = unsigned long long;

using ll = long long;

using pii = pair<int, int>;

using psi = pair<string, int>;

constexpr ll MOD = 1e9 + 7;

//-------------------------------------------------------->>>>>>>>>>

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

set<array<int,2>> st;

inline void solve(){

    string str, t;

    cin >> str >> t;

    Hashing hstr=(str+str);

    Hashing ht=(t);

    int len=str.size();

    for(int i=0;i<len;i++){

        auto u=hstr.query(i,i+len-1);

        st.insert(u);

    }

    int ans=0;

    for(int i=0;t[i+len-1];i++){

        auto u=ht.query(i,i+len-1);

        if(st.count(u)){

            ans++;

        }

    }

    cout<<ans<<endl;

}

inline void prework(){

}

signed main()

{

    ios::sync_with_stdio(false);

    cin.tie(nullptr);

    cout.tie(nullptr);

    cout << fixed << setprecision(12);

    prework();

    int T = 1;

    cin >> T;

    while (T--)

    {

        solve();

    }

    return 0;

}
```