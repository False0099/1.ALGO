### Problem Statement

省流：给你 N 个物品，做无线背包，对于一个物品，如果你选了 k 个，那你最后只能得到 $k*v-k*k$ 的价值。


There are $N$ types of items. The $i$ \-th type of item has a weight of $w_i$ and a value of $v_i$. Each type has $10^{10}$ items available.

Takahashi is going to choose some items and put them into a bag with capacity $W$. He wants to maximize the value of the selected items while avoiding choosing too many items of the same type. Hence, he defines the **happiness** of choosing $k_i$ items of type $i$ as $k_i v_i - k_i^2$. He wants to choose items to maximize the total happiness over all types while keeping the total weight at most $W$. Calculate the maximum total happiness he can achieve.

### Constraints

-   $1 \leq N \leq 3000$
-   $1 \leq W \leq 3000$
-   $1 \leq w_i \leq W$
-   $1 \leq v_i \leq 10^9$
-   All input values are integers.

### Input

The input is given from Standard Input in the following format:

```
$N$ $W$
$w_1$ $v_1$
$w_2$ $v_2$
$\vdots$
$w_N$ $v_N$
```


## 题解
首先，我们考虑最为朴素的方程：
$f[i][j]=\max(f[i-1][j-k*w[i]]+k*v[i]-k*k)$

我们首先考虑怎么对于我们的一个**多重背包进行变形**，假设我们的一般的多重背包 $f[i][j]=\max(f[i-1][j-k*w[i]]+k*v[i])$ 那么有一个中所周至的事实是：我们跑上面的式子，等价于对于我们的下面的式子，**连续跑 K 次**：$f[i][j]=\max(f[i-1][j-w[i]]+v[i])$,

其中，我们的 $v[i]$ 的来源是因为我们的 $v[i]=(k+1)\times v[i]-k*v[i]$。

同时，我们不难发现，对于本题，我们**也可以进行同样的变形**，我们就有对上面的式子进行暴力跑等价于对下面的式子跑了 $k$ 次，
$f[i][j]=\max(f[i-1][j-w[i]]+(k+1)*v[i]-k*v[i]+(k+1)*(k+1)-k*k)$
$f[i][j]=\max(f[i-1][j-w[i]]+v[i]-2*k+1)$

那么，我们对于上面的式子，我们其实**没有优化我们的时间复杂度**，我们现在考虑一些其他的问题，我们可以**枚举我们的 $w[i]$,**, 根据我们的调和级数，我们总共的 $k$ 对应最多有 $\frac{j}{/w[i]}$ 个物品，这个时候，我们再去枚举我们的 $j$。也许就能跑通我们的式子？

这个时候，我们的大致的思路是：
$f[j]=f[j-w]+v(w,k)-2*k+1$。但是，我们注意到一个问题，我们的**w->v**不是一个一对一的映射，也就是说，我们的一个 $w$ 可能会对应多个**不同的 v**，那么我们这个时候可以考虑将我们的对应的映射设置为 $f(w)=v$,也就是我们在**选择了单个代价为 w，总共使用了 k 个，我们的最终最大受益**，这个显然我们可以通过一个单调队列来进行同台的处理。
```cpp
#include <bits/stdc++.h>

#define int long long

#define fi first

#define se second

  

using namespace std;

  

const int N = 3e3 + 10;

  

int n, m;

priority_queue<int> heap[N];

int dp[N];

  

signed main() {

    cin.tie(0);

    cout.tie(0);

    ios::sync_with_stdio(0);

  

    cin >> n >> m;

    for (int i = 1; i <= n; i ++) {

        int w, v;

        cin >> w >> v, heap[w].push(v - 1);

    }

    for (int i = 1; i <= m; i ++)

        for (int j = 1; j <= m / i && heap[i].size(); j ++) {

            int v = heap[i].top();

            heap[i].pop();

            for (int k = m; k >= i; k --) dp[k] = max(dp[k], dp[k - i] + v);

            heap[i].push(v - 2);

        }

    cout << *max_element(dp + 1, dp + 1 + m) << endl;

  

    return 0;

}
```