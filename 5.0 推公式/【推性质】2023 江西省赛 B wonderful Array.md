## 题面
You are given a positive integer $k$ and $k$ positive integers $a_0, a_1, ... , a_{k-1}$.

Then three positive integers $n, m, x$ are given.

Let $b_0,b_1...b_n$ be the following sequence of $n$ numbers:

$b_i =\begin {cases} x, & i = 0\\ b_{i-1} + a_{(i-1) \mod k}, & 0&lt;i \le n\end {cases}$

Find the number of $i(0\le i\lt n)$ such that $(b_i \mod m) \le (b_{i+1} \mod m)$.


## 输入：
**Input**

The first line contains an integer $k$ $(1 \le k \le 10^6)$.

The second line contains $k$ integers $a_0, a_1, ... , a_{k-1}$ $(1 \le a_i \le 10^9)$.

The third line contains three integers $n,m,x$ $(1 \le n \le 10^9,1 \le m \le 10^9,1 \le x \le 10^9)$.

## 输出：
**Output**

Output a single integer, denoting the answer.

## 样例
3
2 4 3
4 7 5

2

## 题解
我们考虑我们问题的补集，如果有：$(b_{i} \text{ mod } m)>(b_{i+1} \text{ mod } m)$,那么我们显然有：
那么： $b_i/m<b_{i+1}/m$ 显然成立，并且 $b_i/m+1=b_{i+1}/m$。所以对于所有的 $b_i$ 都 $/=m$ ,得到的数字是连续的。于是我们只要求出最后一个数字就好了。然后用 $n$ 减去它就得到了答案。


```cpp
// #pragma GCC optimize(3,"Ofast","inline")

// #pragma GCC optimize(2)

#include <bits/stdc++.h>

using namespace std;

  

#define all(v) v.begin(), v.end()

#define point(n) fixed << setprecision(n)

#define lowbit(x) ((x) & (-x))

#define IOS                      \

    ios::sync_with_stdio(false); \

    cin.tie(0), cout.tie(0);

#define debug(a) cout << "=======" << a << "========" << endl;

#define endl '\n'

#define inf 0x3f3f3f3f

typedef long long ll;

typedef unsigned long long ull;

ll pow(ll a, ll b, ll mod)

{

    ll res = 1;

    while (b > 0)

    {

        a = a % mod;

        if (b & 1)

            res = res * a % mod;

        b = b >> 1;

        a = a * a % mod;

    }

    return res;

}

ll pow(ll a, ll b)

{

    ll res = 1;

    while (b > 0)

    {

        if (b & 1)

            res = res * a;

        b = b >> 1;

        a = a * a;

    }

    return res;

}

ll ceil(ll a, ll b)

{

    if (a % b == 0)

        return a / b;

    else

        return a / b + 1;

}

typedef pair<int, int> PII;

typedef pair<int, array<int, 2>> PIA;

const int N = 1e6 + 10, mod = 1e9 + 7;

ll n, m, k, x;

ll f[N];

ll sum = 0;

void solve()

{

}

int main()

{  

    IOS;

    cin >> k;

    for (int i = 1; i <= k; i++)

        cin >> f[i];

    cin >> n >> m >> x;

    for (int i = 1; i <= k; i++)

    {

        f[i] %= m;

        f[i] += f[i - 1];

    }

    sum = n / k * f[k] + f[n % k] + x % m;

    cout << (n - sum / m) << endl;

    return 0;

}
```