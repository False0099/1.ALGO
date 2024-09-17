#mex #树状数组 #set #STL库 
### Problem Statement

You are given a sequence $A=(A_1,A_2,\dots,A_N)$ of length $N$.  
Respond to the following $Q$ queries in the order they are given.

The $k$ \-th query is given in the following format:

```
$i_k$ $x_k$
```

-   First, change $A_{i_k}$ to $x_k$. This change will carry over to subsequent queries.
-   Then, print the $\rm{mex}$ of $A$.
    -   The $\rm{mex}$ of $A$ is the smallest non-negative integer not contained in $A$.

### Constraints

-   All input values are integers.
-   $1 \le N,Q \le 2 \times 10^5$
-   $0 \le A_i \le 10^9$
-   $1 \le i_k \le N$
-   $0 \le x_k \le 10^9$

### Input

Input is given from Standard Input in the following format:

```
$N$ $Q$
$A_1$ $A_2$ $\dots$ $A_N$
$i_1$ $x_1$
$i_2$ $x_2$
$\vdots$
$i_Q$ $x_Q$
```

### Sample Input 1

```
8 5
2 0 2 2 1 1 2 5
4 3
4 4
6 3
8 1000000000
2 1
```

## 题解
我们这一题需要我们维护整个数组的 mex，我们可以仿照我们的分块思路，对我们的结果进行维护，也可以采用我们的树状数组方法，先计算我们的出现的种类，最后再去每一次以 $\log n$ 来计算我们的数组 $mex$,

或者我们也可以采用我们的 STL 来进行我们的计算
```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#ifdef LOCAL
#include "debug.h"
#else
#define debug(...) 2137
#endif

const int N = 200200;
int n, q;
int a[N];
set<int> s;//维护我们的mex是多少
map<int, int> cnt;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> n >> q;
  for (int i = 0; i <= n; i++) {
    s.insert(i);
  }
  for (int i = 0; i < n; i++) {
    cin >> a[i];
    cnt[a[i]]++;
    s.erase(a[i]);
  }
  while (q--) {
    int i, x;
    cin >> i >> x;
    i--;
    if (--cnt[a[i]] == 0) {
      s.insert(a[i]);
    }
    a[i] = x;
    if (++cnt[a[i]] == 1) {
      s.erase(a[i]);
    }
    cout << *s.begin() << '\n';
  }
}

```
