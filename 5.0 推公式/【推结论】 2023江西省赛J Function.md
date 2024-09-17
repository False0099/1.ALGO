You are given a positive integer $n$ and $n$ quadratic functions with quadratic coefficients equal to $1$. The $i$ \-th function takes the form $y=(x-i)^2+b_i$ .

Then, you are given a positive integer $m$ , representing the total number of operations.

There are two types of operations. The first type is to add a quadratic function with a quadratic coefficient of $1$, taking the form $y=(x-a)^2+b$ . The second type is query operation, and you should print the minimum function value for all quadratic functions at $x=a$.

Specifically, for each operation, you will be given the type of the operation first. If the type is $0$, it represents the first type of operation. If the type is $1$, it represents the second type of operation. For the first type of operation, you will be given two positive integers $a$ and $b$. For the second type of operation, you wil be given one positive integer $a$.

**Input**

The first line contains a positive integer $n$ $(1 \le n \le 10^5)$, representing the initial number of functions.

The second line contains $n$ positive integers $b_1, b_2, ... , b_{n}$ $(1 \le b_i \le n)$, and the $i$ \-th function is $y=(x-i)^2+b_i$.

The third line contains a positive integer $m$ $(1 \le m \le 10^5)$, representing the total number of operations.

Next $m$ lines, each line contains either "$0$ $a$ $b$" $(1 \le a, b\le n)$ or "$1$ $a$" $(1 \le a \le n )$, denoting an operation.

**Output**

Print $q$ lines where the $i$ \-th line contains one integer — the answer for the $i$ \-th query operation.

## 题解
查询 $x=\alpha$ 时函数的最小值，容易发现可能为最小值的函数只可能在左右根号的范围内
 那么只要在左右根号的范围内枚举所有函数，找出最优的即可。
 时间复杂度：$\mathcal{O}(\mathfrak{n}\sqrt{\mathfrak{n}})$

```cpp
// #pragma GCC optimize(3,"Ofast","inline")
// #pragma GCC optimize(2)
#include <bits/stdc++.h>
using namespace std;

#define all(v) v.begin(), v.end()
#define point(n) fixed << setprecision(n)
#define lowbit(x) ((x) & (-x))
#define IOS                      \
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
int n, m, k;
int f[N];

void solve()
{
}
int main()
{
    IOS;
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> f[i];
    cin >> m;
    while (m--)
    {
        int a, b, c;
        cin >> c;
        if (c == 0)
        {
            cin >> a >> b;
            f[a] = min(f[a], b);
        }
        else
        {
            cin >> a;
            int ans = f[a];
            for (int i = 1; a + i <= n && i * i < f[a]; i++)
            {
                ans = min(ans, i * i + f[a + i]);
            }
            for (int i = 1; a - i >= 1 && i * i < f[a]; i++)
            {
                ans = min(ans, i * i + f[a - i]);
            }
            cout << ans << endl;
        }
    }

    return 0;
}
```