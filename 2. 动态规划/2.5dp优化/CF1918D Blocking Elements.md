# Blocking Elements

## 题面翻译

给定一个长度为 $n$ 的序列 $A$，你需要划分这个序列。先任意选择若干个位置，假定你选择了 $m$ 个位置，这些位置分别为 $B_1,B_2...B_m$ ，这一次划分的代价为下面两个量中的最大值：

- $\sum\limits_{i=1}^{m}A_{B_{i}}$ .
- $\max\limits_{i=0}^{m}{\large{\sum\limits_{j=B_i+1}^{B_{i+1}-1}}{A_j}}$  。特别的，定义 $B_0=0,B_{m+1}=n+1$，同时，若 $B_i=B_i+1$ ，则在原式中 $\sum$ 一项的值你应当视为 0。

即为：你选择了若干位置，这些位置将原序列分隔成了若干段。代价是你选择的这些位置的元素和与每一段中所有的元素和的最大值。

给定 $n$ 与序列 $A$ ，求最小分隔代价。多测，$\sum n \le 1e5$ .

## 题目描述

You are given an array of numbers $ a_1, a_2, \ldots, a_n $ . Your task is to block some elements of the array in order to minimize its cost. Suppose you block the elements with indices $ 1 \leq b_1 < b_2 < \ldots < b_m \leq n $ . Then the cost of the array is calculated as the maximum of:

- the sum of the blocked elements, i.e., $ a_{b_1} + a_{b_2} + \ldots + a_{b_m} $ .
- The maximum sum of the segments into which the array is divided when the blocked elements are removed. That is, the maximum sum of the following ( $ m + 1 $ ) subarrays: \[ $ 1, b_1 − 1 $ \], \[ $ b_1 + 1, b_2 − 1 $ \], \[ $ \ldots $ \], \[ $ b_{m−1} + 1, b_m - 1 $ \], \[ $ b_m + 1, n $ \] (the sum of numbers in a subarray of the form \[ $ x, x − 1 $ \] is considered to be $ 0 $ ).

For example, if $ n = 6 $ , the original array is \[ $ 1, 4, 5, 3, 3, 2 $ \], and you block the elements at positions $ 2 $ and $ 5 $ , then the cost of the array will be the maximum of the sum of the blocked elements ( $ 4 + 3 = 7 $ ) and the sums of the subarrays ( $ 1 $ , $ 5 + 3 = 8 $ , $ 2 $ ), which is $ \max (7,1,8,2) = 8 $ .

You need to output the minimum cost of the array after blocking.

## 输入格式

The first line of the input contains a single integer $ t $ ( $ 1 \leq t \leq 30\, 000 $ ) — the number of queries.

Each test case consists of two lines. The first line contains an integer $ n $ ( $ 1 \leq n \leq 10^5 $ ) — the length of the array $ a $ . The second line contains $ n $ elements $ a_1, a_2, \ldots, a_n $ ( $ 1 \leq a_i \leq 10^9 $ ) — the array $ a $ .

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 10^5 $ .

## 输出格式

For each test case, output a single number — the minimum cost of blocking the array.

## 样例 #1

### 样例输入 #1

```
3
6
1 4 5 3 3 2
5
1 2 3 4 5
6
4 1 6 3 10 7
```

### 样例输出 #1

```
7
5
11
```

## 提示

The first test case matches with the array from the statement. To obtain a cost of $ 7 $ , you need to block the elements at positions $ 2 $ and $ 4 $ . In this case, the cost of the array is calculated as the maximum of:

- The sum of the blocked elements, which is $ a_2 + a_4 = 7 $ .
- the maximum sum of the segments into which the array is divided when the blocked elements are removed, i.e., the maximum of $ a_1 $ , $ a_3 $ , $ a_5 + a_6 = \max (1,5,5) = 5 $ .

So the cost is $ \max (7,5) = 7 $ .

In the second test case, you can block the elements at positions $ 1 $ and $ 4 $ .

In the third test case, to obtain the answer $ 11 $ , you can block the elements at positions $ 2 $ and $ 5 $ . There are other ways to get this answer, for example, blocking positions $ 4 $ and $ 6 $ .


## 题解
我们本题的要求是求我们把我们的一个数列划分为若干段，每一段的最大值不超过 k，且我们的删除值之和也不超过 k。这里，我们就可以通过我们的一个 dp 来进行，我们这里有两个要求，一个是我们的每一段区间和都不能超过我们的 k，另一个是我们的删除值之和也不能超过 k。这里，我们如果同时处理两个的话，我们是不好处理的，我们考虑把我们的每一段区间和不超过 k 作为我们的一个条件，于是我们的转移就有：
$dp[i]=min(dp[j])+a[i]$,其中，我们的 dp 表示我们的**删除值的和**。而我们的 j 的范围则可以通过我们的双指针，或者我们的双端队列来确定，

```cpp

void solve()
{
    int n;
    cin >> n;
    vector<ll> arr(n + 2), pre(n + 2);
    for (int i = 1; i <= n; ++i)
        cin >> arr[i], pre[i] = pre[i - 1] + arr[i];
    ll l = 1, r = 1e14, mid, ans = 1;
    function<bool(ll x)> check = [&](ll x)->bool
    {
        vector<ll> dp(n + 2);
        deque<ll> dq;
        dq.pb(0);
        for (int i = 1, j = 0; i <= n + 1; ++i)
        {
            while (pre[i - 1] - pre[j] > x)
                ++j;
            while (!dq.empty() && dq.front() < j)
                dq.pop_front();
            if (dq.empty())
                return false;
            dp[i] = dp[dq.front()] + arr[i];
            while(!dq.empty() && dp[dq.back()] >= dp[i])
                dq.pop_back();
            dq.pb(i);
        }
        return dp[n + 1] <= x;
    };
    while (l <= r)
    {
        mid = (l + r) / 2;
        if (check(mid))
        {
            ans = mid;
            r = mid - 1;
        }
        else
            l = mid + 1;
    }
    cout << ans << endl;
}
```
```