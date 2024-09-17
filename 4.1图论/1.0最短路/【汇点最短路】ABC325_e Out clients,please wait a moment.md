### Problem Statement

There are $N$ cities in a certain country.  
You will travel from your office in city $1$ to a destination in city $N$, via zero or more cities.  
Two types of transportation are available: company car and train. The time required to travel from city $i$ to city $j$ is as follows:

-   $D_{i,j} \times A$ minutes by company car, and
-   $D_{i,j} \times B + C$ minutes by train.

You can switch from company car to train, but not vice versa.  
You can do so without spending time, but only in a city.

What is the minimum time in minutes to travel from city $1$ to city $N$?

## 题解
我们首先本题不能被题目范围中的 N=1000 诈骗，因为写 floyd 是过不去的，我们这一题的正解应该是先求出每个点从 1 开车和从终点坐飞机去该点需要的距离最大和是，然后我们在比较我们中途转机所需的时间是多少，即可。

```cpp
#include<bits/stdc++.h>
#include<atcoder/all>
using namespace std;
using namespace atcoder;
#define ll long long
#define ld long double
#define rep(i, n) for(ll i = 0; i < n; i++)
#define rep2(i, a, b) for(ll i = a; i <= b; i++)
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define MAX(x) *max_element(all(x))
#define MIN(x) *min_element(all(x))
#define SZ(x) ((ll)(x).size())
#define eb emplace_back
#define fi first
#define se second
#define pll pair<ll, ll>
#define endl '\n'
void Yes(bool i = true){ cout << (i ? "Yes" : "No") <<  '\n';}
template<class T> using pq = priority_queue< T >;
template<class T> using pqg = priority_queue< T , vector< T >, greater< T >>;
template<class T> inline bool chmax(T& a, T b) { if (a < b) { a = b; return 1; } return 0; }
template<class T> inline bool chmin(T& a, T b) { if (a > b) { a = b; return 1; } return 0; }
template<class T>
T ceil_div(T a, T b) {
    if(b < 0) a = -a, b = -b;
    return (a >= 0 ? (a + b - 1) / b : a / b);
}
template<class T>
T floor_div(T a, T b) {
    if(b < 0) a = -a, b = -b;
    return (a >= 0 ? a / b : (a - b + 1) / b);
}
const int inf = 1001001001;
const ll INF = 1001001001001001001;
const double PI = acos(-1);
bool range(int y, int x, int h, int w){
  return (0 <= y && y < h && 0 <= x && x < w);
}
int dy[9] = {0, 1, 0, -1, 1, 1, -1, -1, 1};
int dx[9] = {1, 0, -1, 0, 1, -1, -1, 1, 1};
using mint = modint998244353;
const int MOD = 998244353;
//using mint = modint1000000007;
//const int MOD = 1000000007;

// multisetのeraseはfindしてからerase


signed main(){
  cout << fixed << setprecision(15);
  
  int n;
  ll a, b, c;
  cin >> n >> a >> b >> c;
  vector<vector<ll>> d(n, vector<ll>(n, INF));
  rep(i, n)rep(j, n){
    cin >> d[i][j];
  }
  
  vector<ll> d1(n, INF), d2(n, INF);
  pqg<pll> que;
  que.push({0, 0});
  d1[0] = 0;
  while(!que.empty()){
    auto[cost, v] = que.top();
    que.pop();
    if(cost != d1[v]) continue;
    rep(nv, n){
      ll ncost = cost + d[v][nv] * a;
      if(d1[nv] > ncost){
        d1[nv] = ncost;
        que.push({ncost, nv});
      }
    }
  }
  d2[n-1] = 0;
  que.push({0, n-1});
  while(!que.empty()){
    auto[cost, v] = que.top();
    que.pop();
    if(cost != d2[v]) continue;
    rep(nv, n){
      ll ncost = cost + d[v][nv] * b + c;
      if(d2[nv] > ncost){
        d2[nv] = ncost;
        que.push({ncost, nv});
      }
    }
  }
  ll ans = d1[n-1];
  rep(i, n) chmin(ans, d1[i] + d2[i]);
  
  cout << ans << endl;
  return 0;
  
}
```