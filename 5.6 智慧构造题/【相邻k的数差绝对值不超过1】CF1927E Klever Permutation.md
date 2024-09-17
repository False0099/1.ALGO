## 题意
You are given two integers $n$ and $k$ ($k \le n$), where $k$ is even.

A permutation of length $n$ is an array consisting of $n$ distinct integers from $1$ to $n$ in any order. For example, $[2,3,1,5,4]$ is a permutation, but $[1,2,2]$ is not a permutation (as $2$ appears twice in the array) and $[0,1,2]$ is also not a permutation (as $n=3$, but $3$ is not present in the array).

Your task is to construct a $k$ \-level permutation of length $n$.

A permutation is called $k$ \-level if, among all the sums of continuous segments of length $k$ (of which there are exactly $n - k + 1$), any two sums differ by no more than $1$.

More formally, to determine if the permutation $p$ is $k$ \-level, first construct an array $s$ of length $n - k + 1$, where $s_i=\sum_{j=i}^{i+k-1} p_j$, i.e., the $i$ \-th element is equal to the sum of $p_i, p_{i+1}, \dots, p_{i+k-1}$.

A permutation is called $k$ \-level if $\max(s) - \min(s) \le 1$.

Find **any** $k$ \-level permutation of length $n$.

## 输入：
**Input**

The first line of the input contains a single integer $t$ ($1 \le t \le 10^4$) — the number of test cases. This is followed by the description of the test cases.

The first and only line of each test case contains two integers $n$ and $k$ ($2 \le k \le n \le 2 \cdot 10^5$, $k$ is even), where $n$ is the length of the desired permutation.

It is guaranteed that the sum of $n$ for all test cases does not exceed $2 \cdot 10^5$.

## 输出：
**Output**

For each test case, output **any** $k$ \-level permutation of length $n$.

It is guaranteed that such a permutation always exists given the constraints.


## 题解
我首先，口胡一下可以发现每一对**相邻的模 k 同余的**位置的值的差不超过 1。然后就写了个每次跳着填数的代码，样例都过不去。
发现这样只能保证两个相邻的段的差不超过 1, 不能保证所有的段都满足，只能尝试调整构造方法：对于模 $k$ 余奇数的位置，正着填过去；对于模 $k$ 余偶数的位置，反着填。容易证明这是对的 (但是如果是考场的话主要靠冂胡)。


```cpp
#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n, k;
    std::cin >> n >> k;
    
    std::vector<int> a(n);
    int cur = 0;
    for (int x = 0; x < k; x++) {
        if (x % 2 == 0) {
            for (int i = x; i < n; i += k) {
                a[i] = ++cur;
            }
        } else {
            for (int i = (n - 1) - (n - 1 - x) % k; i >= 0; i -= k) {
                a[i] = ++cur;
            }
        }
    }
    
    for (int i = 0; i < n; i++) {
        std::cout << a[i] << " \n"[i == n - 1];
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int t;
    std::cin >> t;
    
    while (t--) {
        solve();
    }
    
    return 0;
}
```