# New Product

## 题目背景

**一个经商的神奇故事……**

(善意提醒：注意时限！）

## 题目描述

LiM 有一家手工糕点店，因为糕点既实惠又好吃，于是积累了 $P$ 个常客（$P$ 为质数）。

每次这家店出 New Product（新品）的时候，都会做很多个，这 $P$ 个人都会支持，支持方法是：

**每个人买的数量都相同，而且买的总数要尽量多。**

这家店共有 $B$ 个工人，一分钟可以生产已经生产的数量的 $A$ 倍。

（注：一开始有一个已制作的 New Product 作为制作样品）

而当制作完毕，抢购（只考虑常客）完后：

**为了考虑工人们，最后要剩下正好 $B$ 个。**

下面给出已知条件，请你帮 LiM 算算最少要工作多长时间吧！

## 输入格式

共 $T+1$ 行。

第一行一个数 $T$，表示共要出 $T$ 个 New Product。

第 $2 \sim T+1$ 行，每行三个数 $P$，$A$，$B$，意义如题。

## 输出格式

对于每个 New Product：

如果可以实现（有可能不行），输出最少工作的分钟数。

如果不行，输出 `Couldn't Produce!`。

## 样例 #1

### 样例输入 #1

```
1
5 2 3
```

### 样例输出 #1

```
3
```

## 样例 #2

### 样例输入 #2

```
1
2 2 2
```

### 样例输出 #2

```
Couldn't Produce!
```

## 提示

#### 样例 $1$ 解释：

有 $5$ 个常客，一分钟可以生产已生产的 $2$ 倍，有 $3$ 个工人。

则最小需要 $3$ 分钟（生产 $2^3=8$ 个）才能符合要求。

#### 样例 $2$ 解释：

有 $2$ 个常客，一分钟可以生产已生产的 $2$ 倍，有 $2$ 个工人。

因为不管是多长时间都会余下 $0$ 个，所以输出 `Couldn't Produce!`。


----------------------------------------------

说明：

LiM 不是工人哦！

对于每组 New Product，常客数量不同。

对于 $20\%$ 的数据，$T=1$，所有条件 $\leqslant 100$。

对于 $100\%$ 的数据，$T \leqslant 5000$，所有条件 $\leqslant 5 \times 10^4$。$P$ 为质数。

## 思路
题目可以转化为 $A^X \equiv B (mod P)$,用exbsgs即可

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
        a %= p,b %= p;
        if(b==0) return -1;
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
inline void solve(){
    int p,a,b;
    cin>>p>>a>>b;
    int res=exbsgs(a,b,p);
    if(res==-1){
        cout<<"Couldn't Produce!\n";
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
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}
```