# MOD - Power Modulo Inverted

## 题面翻译

求最小的$y$使得$k ≡ x^y (mod \ z)$

无解输出"No Solution"

$k,y,x\in[1,10^9]$

translated by yler

## 题目描述

Given 3 positive integers _x_, _y_ and _z_, you can find _k = x $ ^{y} $ %z_ easily, by fast power-modulo algorithm. Now your task is the inverse of this algorithm. Given 3 positive integers _x_, _z_ and _k_, find the smallest non-negative integer _y_, such that _k%z = x $ ^{y} $ %z_.

## 输入格式

About 600 test cases.

Each test case contains one line with 3 integers _x_, _z_ and _k_.(1<= _x_, _z_, _k_ <=10 $ ^{9} $ )

Input terminates by three zeroes.

## 输出格式

For each test case, output one line with the answer, or "No Solution"(without quotes) if such an integer doesn't exist.

## 样例 #1

### 样例输入 #1

```
5 58 33
2 4 3
0 0 0
```

### 样例输出 #1

```
9
No Solution
```

## 思路
经典exbsgs，直接套板子

## AC代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define INF 0x3f3f3f3f
#define For(i, j, k) for(int i = (j); i < (k); ++i)
#define Rep(i, j, k) for(int i = (j); i >= (k); --i)
#define Fo(i, j, k) for(int i = (j); i <= (k); ++i)
#define all(x) (x).begin(),(x).end()
#define allp(x,n) (x).begin()+(n),(x).end()
#define ms(x,y) memset(x,y,sizeof(x))
#define dbg(x) cerr<<__LINE__<<" | "<<#x<<" = "<<x<<"\n"
#define dbgl(i,x) cerr<<__LINE__<<" ["<<#i<<"]: "<<i<<" -> { "<<#x<<" = "<<x<<" }\n"
#define in(a,l,r)     for(int i=l;i<r;cin>>a[i],i++)
#define out(a,l,c)  for(int i=0;i<l;cout<<a[i]<<c,i++)
#define YES cout<<"YES"<<"\n"
#define NO  cout<<"NO"<<"\n"
#define Yes cout<<"Yes"<<"\n"
#define No  cout<<"No"<<"\n"

#include <ext/pb_ds/assoc_container.hpp> 
#include <ext/pb_ds/tree_policy.hpp> 
// #include<ext/pb_ds/hash_policy.hpp>
// #include<ext/pb_ds/trie_policy.hpp>
using namespace __gnu_pbds; 

template<int IDX, int MAX, typename... Args> struct PRINT_TUPLE {
    static void print(ostream &os, const tuple<Args...> &t) {os << get<IDX>(t) << (IDX + 1 == MAX ? "" : ",");PRINT_TUPLE<IDX + 1, MAX, Args...>::print(os, t);}
};
template<int MAX, typename... Args> struct PRINT_TUPLE<MAX, MAX, Args...> {
    static void print(ostream &os, const tuple<Args...> &t) {}
};
template<typename... Args> ostream &operator<<(ostream &os, const tuple<Args...> &t) {
    os << "[";PRINT_TUPLE<0, sizeof...(Args), Args...>::print(os, t);return os << "]";
}
template<class T1, class T2> ostream &operator<<(ostream &os, const pair<T1, T2> &p) {
    return os << '[' << p.first << "," << p.second << ']';
}
template<class T, class = decay_t<decltype(*begin(declval<T>()))>,class = enable_if_t<!is_same<T, string>::value>>ostream &operator<<(ostream &os, const T &c) {
    os << "[";for (auto it = c.begin(); it != c.end(); ++it) {if (it != prev(c.end())) {os << *it << ", ";} else {os << *it << "]";}}return os;
}
template <class T>ostream &operator<<(ostream &os, const stack<T> &S) {
    stack<T> s = S;os << "S[";while (s.size() > 1) {os << s.top() << ",";s.pop();}if (s.size()) {os << s.top();}os << ">";return os;
}
template <class T>ostream &operator<<(ostream &os, const queue<T> &S) {
    queue<T> s = S;os << "Q<";while (s.size() > 1) {os << s.front() << ",";s.pop();}if (s.size()) {os << s.front();}os << "]";return os;
}
template <class T>ostream &operator<<(ostream &os, const deque<T> &S) {
    deque<T> s = S;os << "[";while (s.size() > 1) {os << s.front() << ", ";s.pop_front();}if (s.size()) {os << s.front();}os << "]";return os;
}
template <class T>ostream &operator<<(ostream &os, const priority_queue<T> &S) {
    priority_queue<T> s = S;os << "[";while (s.size() > 1) {os << s.top() << ", ";s.pop();}if (s.size()) {os << s.top();}os << "]";return os;
}
template <class T>ostream &operator<<(ostream &os, const priority_queue<T, vector<T>, greater<T>> &S) { 
    priority_queue<T, vector<T>, greater<T>> s = S;os << "[";while (s.size() > 1) {os << s.top() << ", ";s.pop();}if (s.size()) {os << s.top();}os << "]";return os;
}

#define int long long
using ull = unsigned long long;                                                                              
using ll = long long;
using pii = pair<int,int>;
using psi = pair<string,int>;
constexpr ll MOD = 1e9+7;
//-------------------------------------------------------->>>>>>>>>>
namespace BSGS {
    ll a, b, p;
    map<ll, ll> f;
    inline ll gcd(ll a, ll b) { return b > 0 ? gcd(b, a % b) : a; }
    inline ll ps(ll n, ll k, int p) {
        ll r = 1;
        for (; k; k >>= 1) {
            if (k & 1) r = r * n % p;
            n = n * n % p;
        }
        return r;
    }
    void exgcd(ll a, ll b, ll &x, ll &y) {
        if (!b) {
            x = 1, y = 0;
        } else {
            exgcd(b, a % b, x, y);
            ll t = x;
            x = y;
            y = t - a / b * y;
        }
    }
    ll inv(ll a, ll b) {
        ll x, y;
        exgcd(a, b, x, y);
        return (x % b + b) % b;
    }
    ll bsgs(ll a, ll b, ll p) {
        f.clear();
        int m = ceil(sqrt(p));
        b %= p;
        for (int i = 1; i <= m; i++) {
            b = b * a % p;
            f[b] = i;
        }
        ll tmp = ps(a, m, p);
        b = 1;
        for (int i = 1; i <= m; i++) {
            b = b * tmp % p;
            if (f.count(b) > 0) return (i * m - f[b] + p) % p;
        }
        return -1;
    }
    ll exbsgs(ll a, ll b, ll p) { //a^x ≡ b(mod p)
        if (b == 1 || p == 1) return 0;
        ll g = gcd(a, p), k = 0, na = 1;
        while (g > 1) {
            if (b % g != 0) return -1;
            k++;
            b /= g;
            p /= g;
            na = na * (a / g) % p;
            if (na == b) return k;
            g = gcd(a, p);
        }
        ll f = bsgs(a, b * inv(na, p) % p, p);
        if (f == -1) return -1;
        return f + k;
    }
} 
using namespace BSGS;
inline void solve(int a,int p,int b){
    int res=exbsgs(a,b,p);
    if(res==-1){
        cout<<"No Solution\n";
    }else{
        cout<<res<<"\n";
    }
}

inline void prework(){}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);cout.tie(nullptr);
    cout<<fixed<<setprecision(12);
    prework();
    int T=1; 
    int a,p,b;
    cin>>a>>p>>b;
    while(a!=0&&p!=0&&b!=0){
        solve(a,p,b);
        cin>>a>>p>>b;
    }
    return 0;
}
```