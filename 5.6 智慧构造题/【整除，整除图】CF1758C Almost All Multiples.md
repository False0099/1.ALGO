#最小字典序 #排列  #整除
# Almost All Multiples

## 题面翻译

给定 $n$ 和 $x$，求一个 $1$ 到 $n$ 的字典序最小的排列 $\{ p_n \}$，满足 $p_1 = x, \ p_n = 1$，且对所有 $i \in [1, n)$ 有 $i \mid p_i$。

## 题目描述

Given two integers $ n $ and $ x $ , a permutation $ ^{\dagger} $ $ p $ of length $ n $ is called funny if $ p_i $ is a multiple of $ i $ for all $ 1 \leq i \leq n - 1 $ , $ p_n = 1 $ , and $ p_1 = x $ .

Find the lexicographically minimal $ ^{\ddagger} $ funny permutation, or report that no such permutation exists.

 $ ^{\dagger} $ A permutation of length $ n $ is an array consisting of each of the integers from $ 1 $ to $ n $ exactly once.

 $ ^{\ddagger} $ Let $ a $ and $ b $ be permutations of length $ n $ . Then $ a $ is lexicographically smaller than $ b $ if in the first position $ i $ where $ a $ and $ b $ differ, $ a_i < b_i $ . A permutation is lexicographically minimal if it is lexicographically smaller than all other permutations.

## 输入格式

The input consists of multiple test cases. The first line contains an integer $ t $ ( $ 1 \leq t \leq 10^4 $ ) — the number of test cases. The description of the test cases follows.

The only line of each test case contains two integers $ n $ and $ x $ ( $ 2 \leq n \leq 2 \cdot 10^5 $ ; $ 1 < x \leq n $ ).

The sum of $ n $ across all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, if the answer exists, output $ n $ distinct integers $ p_1, p_2, \dots, p_n $ ( $ 1 \leq p_i \leq n $ ) — the lexicographically minimal funny permutation $ p $ . Otherwise, output $ -1 $ .

## 样例 #1

### 样例输入 #1

```
3
3 3
4 2
5 4
```

### 样例输出 #1

```
3 2 1 
2 4 3 1 
-1
```

## 提示

In the first test case, the permutation $ [3,2,1] $ satisfies all the conditions: $ p_1=3 $ , $ p_3=1 $ , and:

- $ p_1=3 $ is a multiple of $ 1 $ .
- $ p_2=2 $ is a multiple of $ 2 $ .

In the second test case, the permutation $ [2,4,3,1] $ satisfies all the conditions: $ p_1=2 $ , $ p_4=1 $ , and:

- $ p_1=2 $ is a multiple of $ 1 $ .
- $ p_2=4 $ is a multiple of $ 2 $ .
- $ p_3=3 $ is a multiple of $ 3 $ .

We can show that these permutations are lexicographically minimal.

No such permutations exist in the third test case.

## 题解
我们显然可以发现，如果可以组成排列，那么我们的**n 一定要是 x 的倍数**，如果我们有 $n \text{ mod }x\neq 0$,那么我们一定无解，为什么呢？
如果我们有 $n \text{ mod } x=0$,那么我们就可以把我们的 $p_{x}=n$,然后再去构成我们的 $p_{i}=i$。我们这一种情况是 $100\%$ 可行的，但是不一定满足我们前面的字典序最小的条件。这个时候，我们应该怎么去考虑。
我们现在的思路就是，把我们所有可能整除的部分都连接起来连接成一个“整除图”，也就是我们可以把我们的 $i\to p[i]$ 连一条边。
但是，我们可能存在一个问题，如果我们完全只考虑贪心，我们还需要考虑我们的 $p_{x}=n$，这一点不一定是满足我们贪心要求的一个解。

我们的思路就是对于我们的这一个 $x$,再去找一个其他的它的倍数，然后再去依次考虑能不能交换这两个元素。如果可以的话，我们就贪心的交换即可。
```cpp
#include <bits/stdc++.h>
#define int long long
#define ld long double
#define ri register int
#define inf64 0x7f7f7f7f
#define endl '\n'
#define SeeFloat(x) fixed << setprecision(x)
using namespace std;
inline void solve() {
    int n, x; cin >> n >> x;
    if (n % x) {
        cout << "-1\n";
        return ;
    }
    vector<int> p(n + 1);
    p[1] = x, p[x] = n, p[n] = 1;
    for (int i = 2; i < n; i ++) {
        if (i != x)   p[i] = i;
    }
    for (int i = x + 1; i < n; i ++) {
        if (!(p[i] % x) && !(n % i)) {
            swap(p[i], p[x]);
            x = i;
        }
    }
    for (int i = 1; i <= n; i ++) {
        cout << p[i] << " \n"[i == n];
    }
}
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
    int T; cin >> T;
    while (T --)    solve();
	return 0;
}
```