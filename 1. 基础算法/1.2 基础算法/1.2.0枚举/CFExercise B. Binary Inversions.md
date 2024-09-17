You are given a binary array $^{\dagger}$ of length $n$. You are allowed to perform one operation on it **at most once**. In an operation, you can choose any element and flip it: turn a $0$ into a $1$ or vice-versa.

What is the maximum number of inversions $^{\ddagger}$ the array can have after performing **at most one** operation?

$^\dagger$ A binary array is an array that contains only zeroes and ones.

$^\ddagger$ The number of inversions in an array is the number of pairs of indices $i,j$ such that $i&lt;j$ and $a_i &gt; a_j$.

**Input**

The input consists of multiple test cases. The first line contains an integer $t$ ($1 \leq t \leq 10^4$) — the number of test cases. The description of the test cases follows.

The first line of each test case contains an integer $n$ ($1 \leq n \leq 2\cdot10^5$) — the length of the array.

The following line contains $n$ space-separated positive integers $a_1$, $a_2$,..., $a_n$ ($0 \leq a_i \leq 1$) — the elements of the array.

It is guaranteed that the sum of $n$ over all test cases does not exceed $2\cdot10^5$.

**Output**

For each test case, output a single integer  — the maximum number of inversions the array can have after performing **at most one** operation.


## 题解
通过本题，我们可以学到**对于 $01$ 串和逆序对相关的时候，我们应该进行简单的分类讨论**，因为 $01$ 串的类别数量一般都是 $2$ 种，或者两两组合成 $4$ 种，在上一场的 $D$ 题中，我们也将 $01$ 串划分为了 $4$ 种，经过分析又变为两类。

首先思考一下在 $01$ 串中如何计算逆序对，其实要比一般的数组中计算要简单得多，对于每一位数字，我们都将其当做 $j$，然后往左边去找有多少 $i$ 满足条件可以构成逆序对，那么也就是说：

如果$a_j=1$，它左边肯定没有比它大的，对结果贡献为$0$；

如果$a_j=0$，它左边满足条件的$i$的数量就是其左侧的$1$的数量，对结果贡献为$\sum_{k=1}^{j-1}[a_k==1]$。

  

现在来考虑反转操作，如果将$a_j$反转：

  

如果$a_j=1=>0$，那么它将损失$\sum_{k=j+1}^{n}[a_k==0]$的贡献，并产生$\sum_{k=1}^{j-1}[a_k==1]$的贡献。

如果$a_j=0=>1$，那么对于左边它将损失$\sum_{k=1}^{j-1}[a_k==1]$的贡献，并产生$\sum_{k=j+1}^{n}[a_k==0]$的贡献。

  

这个$\sum_{k=1}^{j-1}[a_k==1]$和$\sum_{k=j+1}^{n}[a_k==0]$直接用两个数组来存储即可，$f1_i$表示$i$左侧的$1$的个数，$f2_i$表示$i$右侧的$0$的个数，这个很容易处理。

```cpp

#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int N = 2e5 + 9;

int a[N], f1[N], f2[N];

  

void solve()

{

    int n;cin >> n;

    for(int i = 1;i <= n; ++ i)cin >> a[i];

    f1[0] = 0;

    for(int i = 1;i <= n; ++ i)f1[i] = f1[i - 1] + (a[i] == 1);

    f2[n + 1] = 0;

    for(int i = n;i >= 1; -- i)f2[i] = f2[i + 1] + (a[i] == 0);

    ll ans = 0;

    for(int i = 1;i <= n; ++ i)if(a[i] == 0)ans += f1[i - 1];

    ll sum = ans;

    for(int i = 1;i <= n; ++ i)

    {

        if(a[i])ans = max(ans, sum - f2[i + 1] + f1[i - 1]);

        else ans = max(ans, sum - f1[i - 1] + f2[i + 1]);

    }

    cout << ans << '\n';

}

  

int main()

{

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);

    int _;cin >> _;

    while(_ --)solve();

    return 0;

}

```

  

### 思路2

  

在思路1的基础上继续分析，对于：

  

* $0 \to 1$，为了使得损失最小，需要让“左边的$1$”尽可能少，于是要靠左，为了使得收益最大，需要让“右边的$0$”尽可能多，于是也靠左，于是最左侧的$0 \to 1$是最优的。

  

* $1 \to 0$，为了使得损失最小，需要让“右边的$0$”尽可能少，于是要靠右，为了使得收益最大，需要让“左边的$1$”尽可能多，于是也靠右，于是最右侧的$1 \to 0$是最优的。

暴力计算三种情况（不修改，改最左侧的0，改最右侧的1）即可。

  

### 代码2

  

```cpp

#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int N = 2e5 + 9;

ll a[N];

  

ll f(ll a[], int n)

{

    ll res = 0, c1 = 0;

    for(int i = 1;i <= n; ++ i)

    {

        if(a[i])c1 ++;

        else res += c1;

    }

    return res;

}

  

void solve()

{

    int n; cin >> n;

    int c1 = 0;

    ll ans = 0;

    for(int i = 1; i <= n; ++ i) {

        cin >> a[i];

        if(a[i] == 1)c1++;

        else ans += c1;

    }

    for(int i = 1; i <= n; ++ i)

    {

        if(a[i] == 0)

        {

            a[i] = 1;

            ans = max(ans, f(a, n));

            a[i] = 0;

            break;

        }

    }

  

    for(int i = n; i >= 1; -- i)

    {

        if(a[i] == 1)

        {

            a[i] = 0;

            ans = max(ans, f(a, n));

            a[i] = 1;

            break;

        }

    }

    cout << ans << "\n";

}

  

int main()

{

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);

    int _;cin >> _;

    while(_ --)solve();

    return 0;

}

```

