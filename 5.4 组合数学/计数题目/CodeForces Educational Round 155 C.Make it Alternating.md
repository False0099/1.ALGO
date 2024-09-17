## 题目

You are given a binary string s. A binary string is a string consisting of characters 0 and/or 1.

You can perform the following operation on s any number of times (even zero):

- choose an integer i such that 1≤i≤|s|, then erase the character si.

You have to make s alternating, i. e. after you perform the operations, every two adjacent characters in s should be different.

Your goal is to calculate two values:

- the minimum number of operations required to make s alternating;
- the number of different shortest sequences of operations that make s alternating. Two sequences of operations are different if in at least one operation, the chosen integer i is different in these two sequences.

Input

The first line contains one integer t (1≤t≤104) — the number of test cases.

Each test case consists of one line containing the string s� (1≤|s|≤2⋅1051≤|�|≤2⋅105). The string s� consists of characters 0 and/or 1 only.

Additional constraint on the input:

- the total length of strings s over all test cases does not exceed 2⋅105.

Output

For each test case, print two integers: the minimum number of operations you have to perform, and the number of different shortest sequences of operations. Since the second number might be large, print its remainder modulo 998244353

## Example

input

Copy

3

10010

111

0101

output

Copy

1 2
2 6
0 1

## Note

In the first test case of the example, the shortest sequences of operations are:

- [2][2] (delete the 22-nd character);
- [3][3] (delete the 33-rd character).

In the second test case of the example, the shortest sequences of operations are:

- [2,1][2,1] (delete the 22-nd character, then delete the 11-st character);
- [2,2][2,2];
- [1,1][1,1];
- [1,2][1,2];
- [3,1][3,1];
- [3,2][3,2].

In the third test case of the example, the only shortest sequence of operations is [][] (empty sequence).

## 题解
我们这一题首先需要我们连续的 0/1 的个数不超过 1 个，否则我们就要删除，于是我们就可以统计我们连续 1/0 的长度。这样，我们就可以用我们的双指针来实现，

对于每一个长度为 n 的连续 0 或 1，我们可以用有 n 种不同的位置选择，来删除为我们最后仅有 1 个。于是，我们每一次统计出我们的 len 之后，我们在原先答案的基础上乘以一个 len 就可以了。

之后，我们对于 n 个删除位置的顺序，我们还要进行一个排序，这个排序的次数就是我们第一问中我们删除最小次数的阶乘次。代表我们一共有 $cnt!$ 种排列方式。
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

    int T;
    cin >> T;
    while(T--){
        string s;
        cin >> s;
        int mn = 0;
        mint ans = 1;
        for(int i = 0; i < s.size(); i++){
            int j = i;
            while(j + 1 < s.size() && s[j + 1] == s[j]) j++;
            int len = j - i + 1;
            mn += len - 1;
            ans *= len;
            i = j;
        }
        for(int i = 1; i <= mn; i++) ans *= i;
        cout << mn << ' ' << ans << '\n';
    }

}
```
```