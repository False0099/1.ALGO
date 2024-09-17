
You are given an array a of length n consisting of non-negative integers.

You have to calculate the value of $\sum_{l=1}^{n}\sum_{r=1}^{r-l+1} f(l,r)\times(r-l+1)$  where f(l,r)is $al⊕al+1⊕⋯⊕ar−1$ (the character ⊕ denotes bitwise XOR).

Since the answer can be very large, print it modulo 998244353.

Input

The first line contains one integer n (1≤n≤3⋅105) — the length of the array a.

The second line contains n integers a1,a2,…,an (0≤ai≤109)).

Output

Print the one integer — the value modulo 998244353.

Examples

input

Copy

3
1 3 2

output

Copy

12

input

Copy

4
39 68 31 80

output

Copy

1337

input

Copy

7
313539461 779847196 221612534 488613315 633203958 394620685 761188160

output

Copy

257421502

Note


## 题解
我们这一题采用我们按位计算贡献的方式 ,我们先将每个数拆位，于是我们的问题就转变为：
**给定一个 $[01]$ 串，对于所有包含奇数个 1 的区间，计算它们的总区间长度**

我们可以先考虑先**求这个 0-1 串的异或前缀和**，然后我们就可以发现，如果满足一个区间内包含有奇数个 1，那么我们这一段的异或和就一定是 1，那么现在就很好办了。我们现在考虑每一个位置的贡献，如果这个位置是 1，**那么我们只需要找到前面有多少个位 0 的片段，我们用我们的当前长度乘以我们的次数，算的我们的总共长度，我们减去这些片段的前缀长度之和**等价于我们做了 j 次总长度减去我们不符合条件的次数
![[}13YO1(0V}TZZ3]}@4U$XZS.jpg]]

```cpp
```cpp
#include<iostream>
#include<cstring>
#include<vector>
using namespace std;
using LL = long long;
template<const int T>
struct ModInt {
    const static int mod = T;
    int x;
    ModInt(int x = 0) : x(x % mod) {}
    ModInt(long long x) : x(int(x % mod)) {} 
    int val() { return x; }
    ModInt operator + (const ModInt &a) const { int x0 = x + a.x; return ModInt(x0 < mod ? x0 : x0 - mod); }
    ModInt operator - (const ModInt &a) const { int x0 = x - a.x; return ModInt(x0 < 0 ? x0 + mod : x0); }
    ModInt operator * (const ModInt &a) const { return ModInt(1LL * x * a.x % mod); }
    ModInt operator / (const ModInt &a) const { return *this * a.inv(); }
    bool operator == (const ModInt &a) const { return x == a.x; };
    bool operator != (const ModInt &a) const { return x != a.x; };
    void operator += (const ModInt &a) { x += a.x; if (x >= mod) x -= mod; }
    void operator -= (const ModInt &a) { x -= a.x; if (x < 0) x += mod; }
    void operator *= (const ModInt &a) { x = 1LL * x * a.x % mod; }
    void operator /= (const ModInt &a) { *this = *this / a; }
    friend ModInt operator + (int y, const ModInt &a){ int x0 = y + a.x; return ModInt(x0 < mod ? x0 : x0 - mod); }
    friend ModInt operator - (int y, const ModInt &a){ int x0 = y - a.x; return ModInt(x0 < 0 ? x0 + mod : x0); }
    friend ModInt operator * (int y, const ModInt &a){ return ModInt(1LL * y * a.x % mod);}
    friend ModInt operator / (int y, const ModInt &a){ return ModInt(y) / a;}
    friend ostream &operator<<(ostream &os, const ModInt &a) { return os << a.x;}
    friend istream &operator>>(istream &is, ModInt &t){return is >> t.x;}

    ModInt pow(int64_t n) const {
        ModInt res(1), mul(x);
        while(n){
            if (n & 1) res *= mul;
            mul *= mul;
            n >>= 1;
        }
        return res;
    }
    
    ModInt inv() const {
        int a = x, b = mod, u = 1, v = 0;
        while (b) {
            int t = a / b;
            a -= t * b; swap(a, b);
            u -= t * v; swap(u, v);
        }
        if (u < 0) u += mod;
        return u;
    }
    
};
using mint = ModInt<998244353>;

int main(){

    cin.tie(0);
    cout.tie(0);
    ios::sync_with_stdio(0);

    int n;
    cin >> n;
    vector<int> s(n + 1);
    for(int i = 1; i <= n; i++)
        cin >> s[i], s[i] ^= s[i - 1];
    mint ans = 0;
    for(int i = 0; i <= 30; i++){
        mint cnt[2] = {1, 0}, sum[2] = {0};
        for(int j = 1; j <= n; j++){
            int bit = (s[j] >> i & 1);
            ans += (j * cnt[bit ^ 1] - sum[bit ^ 1]) * (1 << i);
            cnt[bit] += 1;
            sum[bit] += j;
        }
    }
    cout << ans << '\n';

}
```
```