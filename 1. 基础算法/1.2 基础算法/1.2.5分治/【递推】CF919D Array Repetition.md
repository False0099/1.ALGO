## 题面
Jayden has an array $a$ which is initially empty. There are $n$ operations of two types he must perform in the given order.

1.  Jayden appends an integer $x$ ($1 \leq x \leq n$) to the end of array $a$.
2.  Jayden appends $x$ copies of array $a$ to the end of array $a$. In other words, array $a$ becomes $[a,\underbrace{a,\ldots,a}_{x}]$. It is guaranteed that he has done at least one operation of the first type before this.

Jayden has $q$ queries. For each query, you must tell him the $k$ \-th element of array $a$. The elements of the array are numbered from $1$.

**Input**

Each test consists of multiple test cases. The first line contains a single integer $t$ ($1 \leq t \leq 5000$) — the number of test cases. The description of the test cases follows.

The first line of each test case contains two integers $n$ and $q$ ($1 \leq n, q \leq 10^5$) — the number of operations and the number of queries.

The following $n$ lines describe the operations. Each line contains two integers $b$ and $x$ ($b \in \{1, 2\}$), where $b$ denotes the type of operation. If $b=1$, then $x$ ($1 \leq x \leq n$) is the integer Jayden appends to the end of the array. If $b=2$, then $x$ ($1 \leq x \leq 10^9$) is the number of copies Jayden appends to the end of the array.

The next line of each test case contains $q$ integers $k_1, k_2, \ldots, k_q$ ($1 \leq k_i \leq \min(10^{18}, c)$), which denote the queries, where $c$ is the size of the array after finishing all $n$ operations.

It is guaranteed that the sum of $n$ and the sum of $q$ over all test cases does not exceed $10^5$.

**Output**

For each test case, output $q$ integers — answers to Jayden's queries.

## 题解
我们本题思路就是我们的倍增操作的数量是有限的，我们最多操作 $\log10^{18}$ 后，我们的操作就是无效的了。所以我们可以存储我们的每一次操作，然后模拟即可解决我们的问题。
对于这一类存在**循环节**的问题，我们的思路是：**存储我们的每一个特殊位置所对应的字符**，然后再去存储我们的每一个**循环节**对应的是多少，我们每一次取模，都是按照我们的总长度，并且找到第一个比这个要小的数字作为我们的除数，然后我们再去进行取模操作。
```cpp
#include <bits/stdc++.h>
using namespace std;
#define all(a) a.begin(), a.end()
#define graph(G, n, m) vector<vector<int>> G(n); for (int i = 0; i < m; i++) { int x, y; cin >> x >> y; --x; --y; G[x].push_back(y); G[y].push_back(x); }
#define diGraph(G, n, m) vector<vector<int>> G(n); for (int i = 0; i < m; i++) { int x, y; cin >> x >> y; --x; --y; G[x].push_back(y); }
#define ansYesNo(Q) cout << (Q ? "Yes" : "No")  << '\n';
template <class T> istream& operator>>(istream& is, vector<T>& vec) { for (T& v : vec) is >> v; return is; }
template <class T> ostream& operator<<(ostream& os, const vector<T>& vec) { for (const T& v : vec) os << v << ' '; return os; }
void solve() {
  int T;
  cin >> T;
  while (T--) {
    int n, q;
    cin >> n >> q;
    long long c = 0;
    map<long long, int> mp;
    map<long long, long long> modMp;
    bool enough = 0;
    for (int i = 0; i < n; i++) {
      int op, x;
      cin >> op >> x;
      if (enough) continue;
      if (op == 1) {
        mp[c++] = x;
      } else {
        x++;
        // c*x >= 1e18; 时结束
        long long nc;
        if (c >= (1e18+x-1)/x) {
          nc = 1e18;
          enough = 1;
        } else {
          nc = c*x;
        }
        modMp[nc-1] = c;
        c = nc;
      }
    }
    vector<long long> queries(q);
    cin >> queries;
    for (long long x : queries) {
      --x;
      while (1) {
        if (mp.count(x)) {
          cout << mp[x] << ' ';
          break;
        }
        long long MOD = modMp.lower_bound(x)->second;
        x %= MOD;
      }
    }
    cout << '\n';
  }
}
int main () {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
#ifdef MY_CFG
  freopen("../input.txt", "r", stdin);
  int N; cin >> N; while(N--) // Represents the number of input boxes on a problem page (Codeforces/Atcoder)
#endif
    solve(), cout << endl;
  return 0;
}

```