给定三个整数 $n, m, X$ 和两个非负整数数列 $x_{0···n-1},y_{0···m-1}$。然后从小到大依次枚举所有 $i ∈ \{0, 1, · · · , nm − 1\}$，每次把 $X$ 赋值为 $X,x_{\lfloor\frac{i}{m}\rfloor}, y_{i\bmod m}$ 三个数的中位数。枚举结束后输出最后 $X$ 的值作为答案。

## 输入
第一行三个整数 $n, m, X(1\leq n,m\leq 10^6,1\leq X\leq 10^9)$。  
  
第二行 $n$ 个非负整数，表示 $x_i(1\leq x_i\leq 10^9)$。  
第三行 $m$ 个非负整数，表示 $y_i(1\leq y_i\leq 10^9)$。

## 输出
一个整数表示答案。

## 题解
考虑三个数 X, A, B，考虑操作可以变成 $X=max(X,min(a,b)),X=min(X,max(a,b))$.那么我们考虑枚举 $i$,如果 $X\leq x_{i}$,我们的所有操作都等价于我们在固定 x 的情况下，和我们 y 数组的最小值、最大值进行一次直接比较。我们只需要 $o(n+m)$ 的模拟一遍即可。

```text
#include<iostream>
#include<cstring>
#include<queue>
#include<set>
#include<map>
#include<cmath>
#include<algorithm>

using namespace std;

#define itn int
typedef long long ll;
typedef pair<int, int> PII;
typedef pair<ll, int> PLI;
typedef pair<int, ll> PIL;
typedef pair<ll, ll> PLL;

#define x first
#define y second
#define sci(x) scanf("%d", &x)
#define scl(x) scanf("%lld", &x)
#define rep(i,a,b) for(int i=(a);i<=(b);i++)
#define lep(i,a,b) for(int i=(a);i>=(b);i--)
#define pri(x) printf("%d ", (x))
#define prl(x) printf("%lld ", (x))
#define pli(x) printf("%d\n", (x))
#define pll(x) printf("%lld\n", (x))
#define mem(a, x) memset(a, x, sizeof a)
#define mep(a, x) memcpy(a, x, sizeof x)
#define yes cout << "YES" << endl;
#define no cout << "NO" << endl;
//printf("case:%d %d\n", );

const int N = 1e6 + 10;
ll n, m, k, q, x;

ll a[N], f[N];
char s[N];

void solve() {
    cin >> n >> m >> x;
    rep(i, 1, n) scl(a[i]);
    ll mx = -1, mn = 1e9 + 10;
    rep(i, 1, m) scl(f[i]), mx = max(mx, f[i]), mn = min(mn, f[i]);

    rep(i, 1, n)
    {
        if (x >= a[i])
        {
            ll t1 = max(max(x, mn), a[i]), t2 = min(min(x, mn), a[i]);
            x = x + a[i] + mn - t1 - t2;
        }
        else
        {
            ll t1 = max(max(x, mx), a[i]), t2 = min(min(x, mx), a[i]);
            x = x + a[i] + mx - t1 - t2;
        }
    }

    cout << x << endl;
}

int main() {
    int T; T = 1;
    while (T--)
    {
        solve();
    }

    return 0;
}
```