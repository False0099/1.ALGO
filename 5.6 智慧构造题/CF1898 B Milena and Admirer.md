#最少操作次数 #非递增数列 #拆分操作 #答案形态已知 
Milena has received an array of integers $a_1, a_2, \ldots, a_n$ of length $n$ from a secret admirer. She thinks that making it non-decreasing should help her identify the secret admirer.

She can use the following operation to make this array non-decreasing:

-   Select an element $a_i$ of array $a$ and an integer $x$ such that $1 \le x  a_i$. Then, replace $a_i$ by two elements $x$ and $a_i - x$ in array $a$. New elements ($x$ and $a_i - x$) are placed in the array $a$ in this order instead of $a_i$.
    
    More formally, let $a_1, a_2, \ldots, a_i, \ldots, a_k$ be an array $a$ before the operation. After the operation, it becomes equal to $a_1, a_2, \ldots, a_{i-1}, x, a_i - x, a_{i+1}, \ldots, a_k$. Note that the length of $a$ increases by $1$ on each operation.
    

Milena can perform this operation multiple times (possibly zero). She wants you to determine the minimum number of times she should perform this operation to make array $a$ non-decreasing.

An array $x_1, x_2, \ldots, x_k$ of length $k$ is called non-decreasing if $x_i \le x_{i+1}$ for all $1 \le i &lt; k$.

## 输入
**Input**

Each test contains multiple test cases. The first line contains the number of test cases $t$ ($1 \leq t \leq 10\,000$). The description of test cases follows.

The first line of each test case contains a single integer $n$ ($1\leq n\leq 2\cdot 10^5$) — the length of the array $a$.

The second line of each test case contains $n$ integers $a_1, a_2, \ldots, a_n$ ($1\leq a_i\leq 10^9$) – the array $a$.

It is guaranteed that the sum of $n$ over all test cases does not exceed $2\cdot 10^5$.

## 输出
**Output**

For each test case, output one integer — the minimum number of operations required to make the array non-decreasing.

It can be shown that it is always possible to make the array $a$ non-decreasing in the finite number of operations.

## 题解
这一题我们从我们的结果出发，我么能发现，我们的结果最好的情况就是形如 111222 这样的，相同数字出现的次数越多越好。
我们本题首先考虑一种能全部变成我们结果的方法，就是我们先把所有的数
我们将从右到左遍历数组。然后，如提示部分所述，我们将拆分当前的 $a_i$ 并创建几乎相等的部分。例如，将 $5$ 拆分为三部分，就形成了子数组 $[1,2,2]$ 。将 $8$ 拆分为四部分，形成子数组 $[2,2,2,2]$ 。注意，子数组必须排序。由于我们希望尽可能少地进行拆分，因此最右端点的值应尽可能高（只要低于或等于拆分后 $a_{i+1}$ 的最左端点即可，如果存在的话）。

当我们遍历数组时，只需将**当前的 $a_i$ 设置为拆分的最左端点**（当前最小值）即可。这将有助于计算 $a_{i-1}$ 的最优拆分。对于当前的 $a_i$ ，我们希望找到最小的 $k$ ，从而将 $a_{i-1}$ 分割成 $k$ 部分，使得最右端点小于或等于 $a_i$ 。更具体地说，我们希望 $\lceil \frac{a_{i-1}}{k} \rceil \leq a_i$ 成立。然后，我们将 $a_{i-1}$ 设为 $\lfloor \frac{a_{i-1}}{k} \rfloor$ ，继续我们的算法。找到所需的 $k$ 的最简单方法是应用下面的公式：

$k=\lceil \frac{a_{i-1}}{a_i} \rceil$

答案就是所有 $k-1$ 的和。

```cpp
#include<bits/stdc++.h>

#define i64 long long
#define ull unsigned long long
#define pii pair<int,int>
#define pll pair<i64,i64>

using namespace std;

const i64 mod=1e9+7;

void solve()
{
    int n;cin>>n;
    vector<i64>a(n+1,0);
    for(int i=1;i<=n;i++) cin>>a[i];
    i64 ans=0;
    for(int i=n-1;i>=1;i--)
    {
        if(a[i]<=a[i+1]) continue;

        if(a[i]%a[i+1]==0)
        {
            ans+=(a[i]/a[i+1]-1);
            a[i]=a[i+1];
        }
        else
        {
            i64 h=a[i]/a[i+1]+1;
            ans+=h-1;
            i64 now=a[i]/h;
            a[i]=now;
        }
    }
    cout<<ans<<"\n";
}

int main()
{
	ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    cout<<fixed<<setprecision(20);
    
    int t;cin>>t;
    while(t--)
    {
        solve();
    }
    return 0;    
}
```