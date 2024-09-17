# Moscow Gorillas

## 题面翻译

对于给出的两个长度为 $n$ 的排列 $p$ 和 $q$ ，请你算出有多少对 $l$ 和 $r$ ( $1 \le l \le r \le n$ ) ，满足 $\operatorname{MEX}([p_l, p_{l+1}, \ldots, p_r])=\operatorname{MEX}([q_l, q_{l+1}, \ldots, q_r])$。

其中，一段序列的 $\operatorname{MEX}$ 值表示 **没有在该序列中出现的最小正整数**。

## 题目描述

In winter, the inhabitants of the Moscow Zoo are very bored, in particular, it concerns gorillas. You decided to entertain them and brought a permutation $ p $ of length $ n $ to the zoo.

A permutation of length $ n $ is an array consisting of $ n $ distinct integers from $ 1 $ to $ n $ in any order. For example, $ [2,3,1,5,4] $ is a permutation, but $ [1,2,2] $ is not a permutation ( $ 2 $ occurs twice in the array) and $ [1,3,4] $ is also not a permutation ( $ n=3 $ , but $ 4 $ is present in the array).

The gorillas had their own permutation $ q $ of length $ n $ . They suggested that you count the number of pairs of integers $ l, r $ ( $ 1 \le l \le r \le n $ ) such that $ \operatorname{MEX}([p_l, p_{l+1}, \ldots, p_r])=\operatorname{MEX}([q_l, q_{l+1}, \ldots, q_r]) $ .

The $ \operatorname{MEX} $ of the sequence is the minimum integer positive number missing from this sequence. For example, $ \operatorname{MEX}([1, 3]) = 2 $ , $ \operatorname{MEX}([5]) = 1 $ , $ \operatorname{MEX}([3, 1, 2, 6]) = 4 $ .

You do not want to risk your health, so you will not dare to refuse the gorillas.

## 输入格式

The first line contains a single integer $n$ ( $1 \le n \le 2 \cdot 10^5$ ) — the permutations length.

The second line contains $n$ integers $p_1, p_2, \ldots, p_n$ ( $1 \le p_i \le n$ ) — the elements of the permutation $p$ .

The third line contains $ n $ integers $ q_1, q_2, \ldots, q_n $ ( $ 1 \le q_i \le n $ ) — the elements of the permutation $ q $ .

## 输出格式

Print a single integer — the number of suitable pairs $ l $ and $ r $ .

## 样例 #1

### 样例输入 #1

```
3
1 3 2
2 1 3
```

### 样例输出 #1

```
2
```

## 样例 #2

### 样例输入 #2

```
7
7 3 6 2 1 5 4
6 7 2 5 3 1 4
```

### 样例输出 #2

```
16
```

## 样例 #3

### 样例输入 #3

```
6
1 2 3 4 5 6
6 5 4 3 2 1
```

### 样例输出 #3

```
11
```

## 提示

In the first example, two segments are correct – $ [1, 3] $ with $ \operatorname{MEX} $ equal to $ 4 $ in both arrays and $ [3, 3] $ with $ \operatorname{MEX} $ equal to $ 1 $ in both of arrays.

In the second example, for example, the segment $ [1, 4] $ is correct, and the segment $ [6, 7] $ isn't correct, because $ \operatorname{MEX}(5, 4) \neq \operatorname{MEX}(1, 4) $ .

## 题解
首先，我们先给出排列中每个数出现的位置 $s[i],t[i]$,作为我们的预备数组，首先，我们特殊考虑我们的 `MEX=1` 的情况，因为这种情况下我们没有前驱，假设我们两个出现的位置分别为 $s[1],t[1]$ 这个时候，我们只需要不选到 $1$ 就行，所以我们的答案就是不包含 $1$ 的所有区间数，这里我们的计算区间数的方程和代码如下所示：
```cpp
int k1 = s[1], k2 = t[1];
if (k1 > k2) swap(k1, k2);
if (1 <= k1 - 1) {
    ans += k1 * (k1 - 1) / 2;
}
if (k2 + 1 <= n) {
    ans += (n - k2 + 1) * (n - k2) / 2;
}
if (k1 < k2) {
    ans += (k2 - k1 - 1) * (k2 - k1) / 2;
}
```

之后，我们考虑对于每一个 $MEX=m$，应该怎么求出我们的答案。首先根据我们的性质，我们的 $1-m-1$ 应该全都出现过至少一次。并且我们的 $m$ 一定不能出现，除此之外没有限制。

因此，我们就可以对于单个数列，求出我们的 $min$ 表示我们的 $1-\{ m-1 \}$ 中最靠左的位置是什么，然后再去求出我们的 $max$ 表示我们的 $1-\{ m-1 \}$ 中出现的最靠右的位置是什么。然后我们每一次就去判断，我们的 $m$ 出现的位置是不是在这个范围当中。如果是的话，我们就直接输出 0。

否则，我们按照我们的 $min,max$ 与我们的 $k$ 关系进行分类，如果我们的 $max\leq k$,那么我们可以选择的范围就是我们的 $1,k-1$,
如果我们的 $min\geq k$,那么我们可以选择的范围就是我们的 $k+1,n$。

根据上述所说，我们每一次更新，并且取我们两个数组的交集，就能得到我们的最终答案。
![[Pasted image 20240323143425.png]]



```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

const int maxn = 2e5 + 1;

int n, ans;
int p[maxn];
int q[maxn];
int s[maxn];
int t[maxn];

signed main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> p[i];
        s[p[i]] = i;
    }for (int i = 1; i <= n; i++) {
        cin >> q[i];
        t[q[i]] = i;
    }
    int k1 = s[1], k2 = t[1];
    if (k1 > k2) swap(k1, k2);
    if (1 <= k1 - 1) {
        ans += k1 * (k1 - 1) / 2;
    }
    if (k2 + 1 <= n) {
        ans += (n - k2 + 1) * (n - k2) / 2;
    }
    if (k1 < k2) {
        ans += (k2 - k1 - 1) * (k2 - k1) / 2;
    }
    int l = k1, r = k2;
    for (int m = 2; m <= n; m++) {//枚举mex
        k1 = s[m], k2 = t[m];
        if (k1 > k2) swap(k1, k2);
        if (l <= k1 && k1 <= r || l <= k2 && k2 <= r) {
            
        l = min(l, k1);
        r = max(r, k2);
            continue;
        }
        if (k1 < l && k2 < l) {
            ans += (n - r + 1) * (l - k2);
        }
        if (k1 > r && k2 > r) {
            ans += (k1 - r) * l;
        }
        if (k1 < l && k2 > r) {
            ans += (l - k1) * (k2 - r);
        }
        l = min(l, k1);
        r = max(r, k2);
    }
    cout << ans+1;
    return 0;
}
```
