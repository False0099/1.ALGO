# 知识点
  ## [[动态规划]]
# 题目
![[Pasted image 20230526230017.png]]

# 思路
·我们设置一个变量 $f_{i,j,k}$ 表示我们运行到第 i 个位置时，有 j 个位置相同，此时的哈希值为k。我们可以写出转移方程
$f_{i,j,k}=f_{i-1,j-[c=s[i]],(j-(c-'a'-a)*b^i)+p}$
·![[Pasted image 20230526230601.png]]
·其实这给了我们一个启示，对于一个 dp 问题，我们不妨先从最暴力的搜索出发，研究一下每一个后状态是不是都能有一个或几个前状态通过一定的运算表示出来。
·dp 中变量的选择，题目中有什么限制，我们就拿什么作为我们的变量，比如说这一题里面，我们要求哈希值、相等数、序列位置相同。所以我们就可以拿这三个来设置我们的变量。而因为这一题问的是是否存在可行方案，存在可转移的条件，所以我们理所当然的可以用 dp 去计算。
·dp 式子的转移，我们可以先写一个正向转移，然后再反推一个反向状态。或者直接考虑后台可以分为多少个子类。
# AC 代码
```cpp
#include <bits/stdc++.h>
#define ios std::ios::sync_with_stdio(false); std::cin.tie(0);
#define inf 0x3f3f3f3f3f3f3f3f
#define int long long
#define pii pair<int, int>
#define vi vector<int>
#define vpii vector<pii>
#define endl '\n'
#define fi first
#define se second
using namespace std;

const int N = 0, M = 0, mod = 998244353; 

bool f[55][55][1010];
int B[55], g[55][55][1010];

int has(string s, int b, int mod) {
    int ans = 0, cnt = s.size();
    B[cnt] = 1;
    while (cnt--) {
        ans = (ans + (s[cnt] - 'a' + 1) * B[cnt + 1] + mod) % mod;
        B[cnt] = B[cnt + 1] * b % mod;
    }
    return ans;
}

void solve() {
    int n, b, p, k;
    string s;
    cin >> n >> b >> p >> k >> s;
    int P = has(s, b, p);
    // cout << P << endl;
    // for (int i = 1; i <= n; i++) cout << B[i] <<' ';
    // cout << endl;
    for (int i = 0; i <= n; i++)
    for (int j = 0; j <= k; j++)
        memset(f[i][j], 0, sizeof f[i][j]);
    f[0][0][0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int d = 0; d <= min(i, k); d++) {
            for (int w = 0; w < p; w++) {
                if (!f[i - 1][d][w]) continue;
                for (int c = 1; c <= 26; c++) {
                    int v = (w + B[i] * c % p + p) % p;
                    // cout << B[i] << endl;
                    int j = d + (c + 'a' - 1 == s[i - 1]);
                    // cout << j << endl;
                    f[i][j][v] = 1;
                    g[i][j][v] = c;
                    // cout << i <<' ' << v << endl;
                    // cout << i << ' ' << j << ' ' << v << ' ' << w << endl;
                }
            }
        }
    }
    if (f[n][k][P] == 0) {
        cout << -1 << endl;
        return;
    }
    string ans;
    for (int i = n; i; i--) {
        int w = g[i][k][P];
        ans += w + 'a' - 1;
        if (ans.back() == s[i - 1])
            k--;
        P = (P - B[i] * w % p + p) % p;
    }
    reverse(ans.begin(), ans.end());
    cout << ans << endl;
}
//63506449813
signed main() {
    int T;
    cin >> T;
    while (T--)
        solve();
    return 0;
}

```
# 备注
