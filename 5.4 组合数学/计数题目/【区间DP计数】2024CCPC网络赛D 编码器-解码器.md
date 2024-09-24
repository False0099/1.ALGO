$\operatorname*{limpid}$ 和 S 酱在传输秘密信息，秘密信息可以看成一个数字 $x$ 。
S 酱决定将秘密信息 $x$ 编码成一个字符串 $S$。
而 $\operatorname*{limpid}$ 决定解密这个 $x$ 是多少。当他知道 $S$ 后，他会将其还原成真正的解码串 $S_n^{\prime}$ (其中，$n$ 为字符
串 $S$ 的长度，即 $|S|$), 具体的还原方式为：

$$S_i'=\begin{cases}S_{i-1}'+a_i+S_{i-1}'&\text{if}i>1\\a_1&\text{if}i=1\end{cases}$$

其中，$a_i$ 表示字符串 $S$ 第 $i$ 个位置上的字符 (从 1 开始编号), 加号表示拼接运算。
在知道真正的解码串之后，$\operatorname*{limpid}$ 会根据与 S 酱之前商定好的 $T$ 开始解密，其中 $x$ 为 $T$ 在 $S_n^\prime$ 中以子序列形式出现的次数。
如果你是 limpid ,告诉你 $S,T$ ,你能帮助他解密得到秘密信息 $x$ 吗。
由于答案可能很大，你只需要输出 $x$ 模 998 244 353 的值即可。

## Input
第一行输入两个字符串 S, T(1 ≤ |S|, |T| ≤ 100)。保证两个字符串仅包含小写字母。

## Output
输出一个整数表示 x 在模 998 244 353 意义下的值

## 题解
本题，我们对于我们的序列匹配，我们的一个思路是，进行我们的**贪心处理**，我们设我们的 $dp[i][l][r]$ 表示我们的第 $i$ 次操作后的字符串，匹配我们的原来的 $[l,r]$ 的方案数是多少。

显然，我们存在下面的转移：
$$
dp[i][l][r]+=2*dp[i-1][l][r];
$$

之后，我们可以根据我们的 $a[l]$ 是否和我们的对应位置匹配，再去对我们的 dp 状态转移进行详细的描述。

```
#include <bits/stdc++.h>
#define int long long
#define endl '\n'
int INF=0x3f3f3f3f3f3f3f3f;
using namespace std;
typedef pair<int,int> PII;
using ll = long long;

// 快速幂
template <typename T>
constexpr T power(T x, ll p)
{
    T res = 1;
    while (p)
    {
        if (p & 1)
            res *= x;
        x *= x, p >>= 1;
    }
    return res;
}
// 取模类
template <typename T, T P>
struct ModInt
{
    T x;
    constexpr ModInt() : x() {}
    constexpr ModInt(ll x) : x(norm(x % getMod())) {}
    constexpr T val() const { return x; }

    static T Mod;
    constexpr static T getMod()
    {
        if (P > 0)
            return P;
        else
            return Mod;
    }
    constexpr static void setMod(T Mod_)
    {
        Mod = Mod_;
    }
    constexpr T norm(T x) const
    {
        if (x < 0)
            x += getMod();
        if (x >= getMod())
            x -= getMod();
        return x;
    }

    static constexpr int mul(int a, int b, int mod)
    {
        return 1ll * a * b % mod;
    }
    // static constexpr ll mul(ll a, ll b, ll mod)
    // {
    //     ll res = a * b - ll(1.l * a * b / mod) * mod;
    //     res %= mod;
    //     if (res < 0)
    //         res += mod;
    //     return res;
    // }

    explicit constexpr operator T() const
    {
        return x;
    }
    constexpr ModInt operator-() const
    {
        return norm(getMod() - x);
    }
    constexpr ModInt inv() const
    {
        assert(x != 0);
        return power(*this, getMod() - 2);
    }

    constexpr ModInt &operator+=(ModInt rhs) &
    {
        x = norm(x + rhs.x);
        return *this;
    }
    constexpr ModInt &operator-=(ModInt rhs) &
    {
        x = norm(x - rhs.x);
        return *this;
    }
    constexpr ModInt &operator*=(ModInt rhs) &
    {
        x = mul(x, rhs.x, getMod());
        return *this;
    }
    constexpr ModInt &operator/=(ModInt rhs) &
    {
        return *this *= rhs.inv();
    }
    friend constexpr ModInt operator+(ModInt lhs, ModInt rhs)
    {
        return lhs += rhs;
    }
    friend constexpr ModInt operator-(ModInt lhs, ModInt rhs)
    {
        return lhs -= rhs;
    }
    friend constexpr ModInt operator*(ModInt lhs, ModInt rhs)
    {
        return lhs *= rhs;
    }
    friend constexpr ModInt operator/(ModInt lhs, ModInt rhs)
    {
        return lhs /= rhs;
    }

    friend constexpr bool operator==(ModInt lhs, ModInt rhs)
    {
        return lhs.val() == rhs.val();
    }
    friend constexpr bool operator!=(ModInt lhs, ModInt rhs)
    {
        return lhs.val() != rhs.val();
    }
    friend constexpr bool operator<(ModInt lhs, ModInt rhs)
    {
        return lhs.val() < rhs.val();
    }
    friend constexpr bool operator<=(ModInt lhs, ModInt rhs)
    {
        return lhs.val() <= rhs.val();
    }
    friend constexpr bool operator>(ModInt lhs, ModInt rhs)
    {
        return lhs.val() > rhs.val();
    }
    friend constexpr bool operator>=(ModInt lhs, ModInt rhs)
    {
        return lhs.val() >= rhs.val();
    }

    friend constexpr std::istream &operator>>(std::istream &is, ModInt &in)
    {
        ll v;
        is >> v;
        in = ModInt(v);
        return is;
    }
    friend constexpr std::ostream &operator<<(std::ostream &os, const ModInt &out)
    {
        return os << out.val();
    }
};

constexpr int P = 998244353;
using mint = ModInt<int, P>;


void init(){
    
}
const int N=110;
mint dp[N][N][N];
void solve(){
    string s;
    string t;
    cin>>s>>t;
    int n=s.length();
    int m=t.length();
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            dp[i][j][j]=(s[i]==t[j]);
        }
    }
    for(int i=1;i<n;i++){
        for(int len=1;len<=m;len++){
            for(int l=0;l+len-1<m;l++){
                int r=l+len-1;
                dp[i][l][r]+=2*dp[i-1][l][r];
                for(int x=l;x+1<=r;x++){
                    dp[i][l][r]+=dp[i-1][l][x]*dp[i-1][x+1][r];
                    //cerr<<i<<" "<<l<<" "<<r<<"+ "<<dp[i-1][l][x]*dp[i-1][x+1][r]<<endl;
                    //dp[i][l][r]+=dp[i-1][l][x]*dp[i-1][x+1][r];
                }
                for(int x=l;x<r;x++){
                    if(s[i]==t[x]){
                        dp[i][l][r]+=dp[i-1][l][x-1]*dp[i-1][x+1][r];
                       // cerr<<i<<" "<<l<<" "<<r<<" + "<<l<<" "<<x-1<<""<<dp[i-1][l][x-1]*dp[i-1][x+1][r]<<endl;
                    }
                }
                if(s[i]==t[r]){
                    dp[i][l][r]+=dp[i-1][l][r-1];
                    //cerr<<i<<" "<<l<<" "<<r<<"+ "<<dp[i-1][l][r-1]<<endl;

                }
                if(s[i]==t[l]){
                    dp[i][l][r]+=dp[i-1][l+1][r];
                    //cerr<<i<<" "<<l<<" "<<r<<"+ "<<dp[i-1][l+1][r]<<endl;
                }
            }
        }
    }
    // for(int i=0;i<n;i++){
    //     for(int j=0;j<m;j++){
    //         for(int k=0;k<m;k++){
    //             cerr<<dp[i][j][k]<<" ";
    //         }
    //         cerr<<endl;
    //     }
    //     cerr<<endl;
    // }
    cout<<dp[n-1][0][m-1]<<endl;
}
signed main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int t;
    t=1;
    //cin>>t;
    init();
    while(t--){
        solve();
    }
}
```