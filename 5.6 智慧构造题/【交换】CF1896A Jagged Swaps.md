You are given a permutation $^\dagger$ $a$ of size $n$. You can do the following operation

-   Select an index $i$ from $2$ to $n - 1$ such that $a_{i - 1}\lt; a_i$ and $a_i \gt; a_{i+1}$. Swap $a_i$ and $a_{i+1}$.

Determine whether it is possible to sort the permutation after a finite number of operations.

$^\dagger$ A permutation is an array consisting of $n$ distinct integers from $1$ to $n$ in arbitrary order. For example, $[2,3,1,5,4]$ is a permutation, but $[1,2,2]$ is not a permutation ($2$ appears twice in the array) and $[1,3,4]$ is also not a permutation ($n=3$ but there is $4$ in the array).

**Input**

Each test contains multiple test cases. The first line contains the number of test cases $t$ ($1 \le t \le 5000$). Description of the test cases follows.

The first line of each test case contains a single integer $n$ ($3 \le n \le 10$) — the size of the permutation.

The second line of each test case contains $n$ integers $a_1, a_2, \ldots, a_n$ ($1 \le a_i \le n$) — the elements of permutation $a$.

**Output**

For each test case, print "YES" if it is possible to sort the permutation, and "NO" otherwise.

You may print each letter in any case (for example, "YES", "Yes", "yes", "yEs" will all be recognized as positive answer).

## 题解
我们这一题
如果我们的开头是 1我们采用这样的构造方法：
1. 我们每一次找到一个最大值，把他放到我们的最右端

如果我们的开头不是 1，我们直接输出无解。
```cpp
#include <bits/stdc++.h>
using namespace std;

#define debug(x) cerr << #x << ": " << x << '\n';
#define bd cerr << "----------------------" << el;
#define el '\n'
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define lop(i, a, b) for (int i = (a); i < (b); i++)
#define dwn(i, a, b) for (int i = (a); i >= (b); i--)
#define cmax(a, b) a = max(a, b)
#define cmin(a, b) a = min(a, b)
#define x first
#define y second
#define db double

typedef long long LL;
typedef pair<int, int> PII;

constexpr int N = 1e5 + 10, md = 1e9 + 7;
constexpr int INF = 0x3f3f3f3f;

int n, m;

void no()
{
    cout << "NO" << el;
}

void yes()
{
    cout << "YES" << el;
}
int a[N];
void solve()
{
    cin >> n;
    rep(i, 1, n)
    {
        cin >> a[i];
    }
    if(a[1] != 1)
    {
        no();
    }
    else {
        yes();
    }

}

int main()
{
    cin.tie(0)->sync_with_stdio(false);
    cout.tie(0);
    int T = 1;
    cin >> T;
    while (T--)
        solve();
}
```