Manhattan consists of n parallel horizontal streets (numbered from 1 to n) and n parallel vertical streets (also numbered from 1 to n). The streets are perfectly straight, and the horizontal streets are perpendicular to the vertical streets, as shown in the diagram below.

![wieze-fig.png](https://images.ptausercontent.com/d2a42d8a-1e50-4e38-a222-f6f613bafe2e.png)

A television station has decided to cover all events happening on the streets of Manhattan. A person standing at the intersection of horizontal street i and vertical street j can see what is happening at all intersections of these two streets with the others. For each intersection, a price has been set for finding a vlogger who is willing to work there (and transmit meaningless news shaking public opinion from both streets they can see). It turned out that for some intersections, this price is negative (some vloggers are willing to pay their employer for publicity). The television station is wondering how to control all intersections and minimize the total fees for vloggers.

### Input

The first line of the input contains an integer T (1≤T≤20), denoting the number of test cases.

For each testcase:

The first line of the input contains a positive integer n (1≤n≤500). In the next n lines, there is a description of each horizontal street. The description of one horizontal street contains n numbers separated by single spaces, which are the rental prices for vloggers at the intersections of that street.

It is guaranteed that all prices are in the range $[−106,106]$.

### Output

For each test case, you should print a single integer, denoting the minimum price that the television station must pay to guarantee coverage of all intersections.

Specially, paying a negative price is preferred over a non-negative price.

### Sample Input

```in
2
4
8 4 2 9
7 1 8 3
8 1 4 3
3 2 8 7
4
-8 -4 -2 -9
-7 -1 -8 -3
-8 -1 -4 -3
-3 -2 -8 -7
```

### Sample Output

```out
6
-78
```

## 题解
我们这一题的思路很简单，先把我们的负数点找到，全选，然后再去找我们的剩下方案里可以选的，再把能选的给选上。最后我们就能得到我们的答案。

**坑点：
1. 记得要 memset 我们的 vis 数组
2. 记得要重置先找负数再去计算我们的最小值，否则就是错误的


```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 510;
//const int mod = 998244353;

int n, m;
int x, y;
int a[maxn][maxn];
bool row[maxn], col[maxn];

void solve() {
    scanf("%d", &n);
    ll left = 0;
    for (int i = 1; i <= n; ++i) {
        row[i] = col[i] = 0;
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            scanf("%d", &a[i][j]); 
            if (a[i][j] < 0) {
                left += a[i][j];
                row[i] = col[j] = 1;
            }
        }
    }
    ll res = 0, ans;
    int mn;
    for (int i = 1; i <= n; ++i) {
        if (row[i]) {
            continue;
        }
        mn = 1e6+1; 
        for (int j = 1; j <= n; ++j) {
            mn = min(mn, a[i][j]);
        }
        if (mn < 0) {
            continue;
        }
        res += mn;
    }
    ans = res;
    res = 0;
    for (int i = 1; i <= n; ++i) {
        if (col[i]) {
            continue;
        }
        mn = 1e6+1; 
        for (int j = 1; j <= n; ++j) {
            mn = min(mn, a[j][i]);
        }
        if (mn < 0) {
            continue;
        }
        res += mn;
    }
    ans = min(ans, res) + left;

    printf("%lld\n", ans);
}
int main(){
    int t;
    cin>>t;
    while(t--){
        solve();
    }
}
```

**坑点 1：必须要先选负数，然后才能去判断最小
坑点 2：在我们最后判断最小的时候，如果有负数，那么我们就直接跳过这一个，这个可能是我们程序的问题。
坑点 3：在我们范围内声明 bool 数组时要先 memset。