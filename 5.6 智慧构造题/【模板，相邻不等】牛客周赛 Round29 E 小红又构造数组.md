## 题意
小红希望你构造一个数组，满足以下三个条件：  
1\. 数组的元素都是素数。  
2\. 数组所有元素相乘恰好等于 $x$。  
3\. 数组任意相邻两个元素不等。

## 输入
一个正整数 $x$。  
$1\leq x \leq 10^{13}$

## 输出
如果无解，直接输出 -1 即可。  
如果有解，第一行输入一个正整数 $n$，代表数组的大小。第二行输入 $n$ 个正整数 $a_i$，代表数组的元素。  

有多解时输出任意合法解都可以。

## 题解
我们这一题首先，我们可以通过简单的统计我们的每一个素数是多少，来确定我们的元素是多少。这里，我们可以通过我们的简单的因式分解来解决我们每一个因子的次数是多少。

之后，我们的问题就变成了，给定你一系列数字，要求你构造一个数列，使得我们任意相邻的两个元素都不相等，问我们构造方案是多少？

这里，我们需要先判断我们是不是可以构造来判断。假设我们有一个数字他出现的次数，已经超过了我们剩余所有数字出现的次数+1. 那么那么我们就认为我们的这一个是不可能构造的，我们直接输出-1 即可。

然后，对于我们的构造，我们采用下面的思路：
第一步：我们从我们的多元集合中选取一个最大的和一个最小的，然后我们每一次操作，就是把我们的一个最大值和我们的一个次大值给打印出来。
第二步：我们每一次打印之后，我们就可以把我们的新的更新后的再放回去即可。
```cpp
// #define LOCAL
#define _USE_MATH_DEFINES
#include <array>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <vector>
#include <queue>
#include <stack>
#include <list>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <complex>
#include <cmath>
#include <numeric>
#include <bitset>
#include <functional>
#include <random>
#include <ctime>

using namespace std;

template <typename A, typename B>
ostream& operator <<(ostream& out, const pair<A, B>& a) {
  out << "(" << a.first << "," << a.second << ")";
  return out;
}
template <typename T, size_t N>
ostream& operator <<(ostream& out, const array<T, N>& a) {
  out << "["; bool first = true;
  for (auto& v : a) { out << (first ? "" : ", "); out << v; first = 0;} out << "]";
  return out;
}
template <typename T>
ostream& operator <<(ostream& out, const vector<T>& a) {
  out << "["; bool first = true;
  for (auto v : a) { out << (first ? "" : ", "); out << v; first = 0;} out << "]";
  return out;
}
template <typename T, class Cmp>
ostream& operator <<(ostream& out, const set<T, Cmp>& a) {
  out << "{"; bool first = true;
  for (auto& v : a) { out << (first ? "" : ", "); out << v; first = 0;} out << "}";
  return out;
}
template <typename T, class Cmp>
ostream& operator <<(ostream& out, const multiset<T, Cmp>& a) {
  out << "{"; bool first = true;
  for (auto& v : a) { out << (first ? "" : ", "); out << v; first = 0;} out << "}";
  return out;
}
template <typename U, typename T, class Cmp>
ostream& operator <<(ostream& out, const map<U, T, Cmp>& a) {
  out << "{"; bool first = true;
  for (auto& p : a) { out << (first ? "" : ", "); out << p.first << ":" << p.second; first = 0;} out << "}";
  return out;
}
#ifdef LOCAL
#define trace(...) __f(#__VA_ARGS__, __VA_ARGS__)
#else
#define trace(...) 42
#endif
template <typename Arg1>
void __f(const char* name, Arg1&& arg1){
  cerr << name << ": " << arg1 << endl;
}
template <typename Arg1, typename... Args>
void __f(const char* names, Arg1&& arg1, Args&&... args){
  const char* comma = strchr(names + 1, ',');
  cerr.write(names, comma - names) << ": " << arg1 << " |";
  __f(comma + 1, args...);
}

template <class T> auto vect(const T& v, int n) { return vector<T>(n, v); }
template <class T, class... D> auto vect(const T& v, int n, D... m) {
  return vector<decltype(vect(v, m...))>(n, vect(v, m...));
}

using int64 = long long;
using int128 = __int128_t;
using ii = pair<int64, int64>;
#define SZ(x) (int)((x).size())
template <typename T> static constexpr T inf = numeric_limits<T>::max() / 2;
const int MOD = 1e9 + 7;
// const int MOD = 998244353;
mt19937_64 mrand(random_device{}());
int64 rnd(int64 x) { return mrand() % x; }
constexpr inline int lg2(int64 x) { return x == 0 ? -1 : sizeof(int64) * 8 - 1 - __builtin_clzll(x); }
constexpr inline int64 p2ceil(int64 x) { return 1LL << (lg2(x - 1) + 1); }
template <class T> void out(const vector<T>& a) { for (int i = 0; i < SZ(a); ++i) cout << a[i] << " \n"[i + 1 == SZ(a)]; }
template <class T> bool ckmin(T& a, const T& b) { return b < a ? a = b, 1 : 0; }
template <class T> bool ckmax(T& a, const T& b) { return a < b ? a = b, 1 : 0; }
template <class T> void dedup(vector<T>& v) { sort(v.begin(), v.end()); v.erase(unique(v.begin(), v.end()), v.end()); }
inline void add_mod(int& x, int y) { x += y; if (x >= MOD) x -= MOD; }
inline void sub_mod(int& x, int y) { x += MOD - y; if (x >= MOD) x -= MOD; }
inline int mod(int x) { return x >= MOD ? x - MOD : x; }

struct fast_ios {
  fast_ios() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(10);
  };
} fast_ios_;

const int N = 4e6 + 10;
bool flag[N];
vector<int> prime;
int minp[N];

void prime_gen(int n) {
  fill(flag, flag + n, false);
  for (int i = 2; i < n; ++i) {
    if (!flag[i]) {
      prime.push_back(i);
      minp[i] = i;
    }
    for (int j = 0, k; j < SZ(prime) && (k = prime[j] * i) < n; ++j) {
      flag[k] = true;
      if (i % prime[j]) {
        minp[k] = prime[j];
      } else {
        minp[k] = minp[i];
        break;
      }
    }
  }
  trace(SZ(prime));
}

int main() {
  // prime_gen(N);
  int64 n;
  cin >> n;
  if (n == 1) {
    cout << -1 << '\n';
    return 0;
  }
  map<int64, int64> cnt;
  for (int64 p = 2; p * p <= n; ++p) {
    if (n % p == 0) {
      while (n % p == 0) {
        cnt[p]++;
        n /= p;
      }
    }
  }
  if (n > 1) cnt[n]++;
  priority_queue<ii> pq;
  int64 sum = 0;
  for (auto& [k, v] : cnt) pq.push({v, k}), sum += v;
  if (pq.top().first * 2 - 1 > sum) {
    cout << -1 << '\n';
  } else {
    vector<int64> ret;
    while (!pq.empty()) {
      if (pq.size() >= 2) {
        auto [x1, y1] = pq.top();
        pq.pop();
        auto [x2, y2] = pq.top();
        pq.pop();
        ret.push_back(y1);
        ret.push_back(y2);
        if (x1 - 1 > 0) pq.push({x1 - 1, y1});
        if (x2 - 1 > 0) pq.push({x2 - 1, y2});
      } else {
        auto [x, y] = pq.top();
        pq.pop();
        ret.push_back(y);
      }
    }
    cout << SZ(ret) << '\n';
    out(ret);
  }
  return 0;
}

```
