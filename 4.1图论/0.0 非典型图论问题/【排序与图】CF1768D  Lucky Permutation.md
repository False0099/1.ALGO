#逆序对 #交换 #建图
# Lucky Permutation

## 题面翻译

### 题目描述

给定整数 $n$ 和一个 $1\sim n$ 的排列 $p$。  
你可以对排列 $p$ 进行下列操作任意次：

- 选择整数 $i,j(1\leq i<j\leq n)$，然后交换 $p_i,p_j$ 的值。

你需要求出至少需要进行上述操作多少次才能使 $p$ 恰有一个逆序对。  
每个测试点包含 $t$ 组数据。

### 输入格式

第一行输入一个整数 $t(1\leq t\leq10^4)$ 表示数据组数，接下来对于每组数据：  
第一行输入一个整数 $n(2\leq n,\sum n\leq2\times10^5)$。  
接下来输入一行 $n$ 个整数 $p_1,p_2,\cdots,p_n(1\leq p_i\leq n)$，保证 $p$ 是一个 $1\sim n$ 的排列。

### 输出格式

对于每组数据：  
输出一行一个整数表示使 $p$ 恰有一个逆序对所需的最小操作次数。  
可以证明一定存在操作方案使得 $p$ 恰有一个逆序对。

## 题目描述

You are given a permutation $ ^\dagger $ $ p $ of length $ n $ .

In one operation, you can choose two indices $ 1 \le i < j \le n $ and swap $ p_i $ with $ p_j $ .

Find the minimum number of operations needed to have exactly one inversion $ ^\ddagger $ in the permutation.

 $ ^\dagger $ A permutation is an array consisting of $ n $ distinct integers from $ 1 $ to $ n $ in arbitrary order. For example, $ [2,3,1,5,4] $ is a permutation, but $ [1,2,2] $ is not a permutation ( $ 2 $ appears twice in the array), and $ [1,3,4] $ is also not a permutation ( $ n=3 $ but there is $ 4 $ in the array).

 $ ^\ddagger $ The number of inversions of a permutation $ p $ is the number of pairs of indices $ (i, j) $ such that $ 1 \le i < j \le n $ and $ p_i > p_j $ .

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases. The description of test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 2 \le n \le 2 \cdot 10^5 $ ).

The second line of each test case contains $ n $ integers $ p_1, p_2,\ldots, p_n $ ( $ 1 \le p_i \le n $ ). It is guaranteed that $ p $ is a permutation.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case output a single integer — the minimum number of operations needed to have exactly one inversion in the permutation. It can be proven that an answer always exists.

## 样例 #1

### 样例输入 #1

```
4
2
2 1
2
1 2
4
3 4 1 2
4
2 4 3 1
```

### 样例输出 #1

```
0
1
3
1
```

## 提示

In the first test case, the permutation already satisfies the condition.

In the second test case, you can perform the operation with $ (i, j)=(1,2) $ , after that the permutation will be $ [2,1] $ which has exactly one inversion.

In the third test case, it is not possible to satisfy the condition with less than $ 3 $ operations. However, if we perform $ 3 $ operations with $ (i, j) $ being $ (1,3) $ , $ (2,4) $ , and $ (3,4) $ in that order, the final permutation will be $ [1, 2, 4, 3] $ which has exactly one inversion.

In the fourth test case, you can perform the operation with $ (i, j)=(2,4) $ , after that the permutation will be $ [2,1,3,4] $ which has exactly one inversion.

## 题解
我们首先，可以发现，如果我们的一个序列的逆序数只有 1，那么他一定是由我们的排序完的序列，任选两个交换后，形成的一个结果。

于是，我们就可以考虑这样一种构造方法：先让我们的数字全部从我们的原来的顺序边惩我们的单调的顺序，这里，我们就可以通过我们的图论来解决。
我们的做法是从 $i\to p[i]$ 建图建图，我们能够得到若干个环，我们的答案就是我们的 $n-$ 环数。

于是，这里，我们就可以先枚举我们的最终状态的图是多少，然后再按照我们的对应关系去连边即可。最后我们的 $n-$ 环数就是我们的答案。

具体来说，假设我们的一个排列是 $[1,2,\dots k-1,k+1,k,k+2\dots]$,那么我们就把原来的从 $i\to k$ 连边，$j\to k+1$ 连边连边，修改为我们的 $i\to k+1$ 连边连边，$j\to k$ 连边。

```cpp
/*
    Name:
    Author: xiaruize
    Date:
*/
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ull unsigned long long
#define ALL(a) (a).begin(), (a).end()
#define pb push_back
#define mk make_pair
#define pii pair<int, int>
#define pis pair<int, string>
#define sec second
#define fir first
#define sz(a) int((a).size())
#define rep(i, x, y) for (int i = x; i <= y; i++)
#define repp(i, x, y) for (int i = x; i >= y; i--)
#define Yes cout << "Yes" << endl
#define YES cout << "YES" << endl
#define No cout << "No" << endl
#define NO cout << "NO" << endl
#define debug(x) cerr << #x << ": " << x << endl
#define double long double
const int INF = 0x3f3f3f3f;
const int MOD = 1000000007;
const int N = 2e5 + 10;

// bool st;
int t;
int n;
int a[N];
int vis[N];
// bool en;

void solve()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        vis[i] = false;
        cin >> a[i];
    }
    bool flag = false;
    int res = 0;
    for (int i = 1; i <= n; i++)
    {
        int x = i;
        if (!vis[x])
        {
            while (!vis[x])
            {
                res++;
                vis[x] = i;
                x = a[x];
            }
            res--;
        }
    }
    for (int i = 1; i < n; i++)
    {
        if (vis[i] == vis[i + 1])
        {
            flag = true;
            break;
        }
    }
    if (flag)
        res--;
    else
        res++;
    cout << res << endl;
}

signed main()
{
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    // cerr<<(&en-&st)/1024.0/1024.0<<endl;
    // auto t_1=chrono::high_resolution_clock::now();
    cin >> t;
    while (t--)
        solve();
    // auto t_2=chrono::high_resolution_clock::now();
    // cout <<". Elapsed (ms): " << chrono::duration_cast<chrono::milliseconds>(t_2 - t_1).count() << endl;
    return 0;
}
```