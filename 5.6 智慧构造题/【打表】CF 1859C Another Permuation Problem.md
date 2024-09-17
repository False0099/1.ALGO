#贪心 #排列 #特殊函数最大 #打表 #枚举
# Another Permutation Problem

## 题面翻译

给定 $n \ (\leqslant 250)$，求一个 $1$ 到 $n$ 的排列 $\{ p_n \}$ 使 $\sum_{i=1}^n p_i \cdot i - \max_{j=1}^n\{ p_j \cdot j \}$ 最大，输出最大值。

## 题目描述

Andrey is just starting to come up with problems, and it's difficult for him. That's why he came up with a strange problem about permutations $ ^{\dagger} $ and asks you to solve it. Can you do it?

Let's call the cost of a permutation $ p $ of length $ n $ the value of the expression:

  $(\sum_{i = 1}^{n} p_i \cdot i) - (\max_{j = 1}^{n} p_j \cdot j)$ . Find the maximum cost among all permutations of length $ n $ .

 $ ^{\dagger} $ A permutation of length $ n $ is an array consisting of $ n $ distinct integers from $ 1 $ to $ n $ in arbitrary order. For example, $ [2,3,1,5,4] $ is a permutation, but $ [1,2,2] $ is not a permutation ( $ 2 $ appears twice in the array), and $ [1,3,4] $ is also not a permutation ( $ n=3 $ but there is $ 4 $ in the array).

## 输入格式

Each test consists of multiple test cases. The first line contains a single integer $ t $ ( $ 1 \le t \le 30 $ ) — the number of test cases. The description of the test cases follows.

The only line of each test case contains a single integer $ n $ ( $ 2 \le n \le 250 $ ) — the length of the permutation.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 500 $ .

## 输出格式

For each test case, output a single integer — the maximum cost among all permutations of length $ n $ .

## 样例 #1

### 样例输入 #1

```
5
2
4
3
10
20
```

### 样例输出 #1

```
2
17
7
303
2529
```

## 提示

In the first test case, the permutation with the maximum cost is $ [2, 1] $ . The cost is equal to $ 2 \cdot 1 + 1 \cdot 2 - \max (2 \cdot 1, 1 \cdot 2)= 2 + 2 - 2 = 2 $ .

In the second test case, the permutation with the maximum cost is $ [1, 2, 4, 3] $ . The cost is equal to $ 1 \cdot 1 + 2 \cdot 2 + 4 \cdot 3 + 3 \cdot 4 - 4 \cdot 3 = 17 $ .

## 题解
我们这一题第一眼看上去题意很好懂，但是我们不好象，而且这一题打表比较方便，所以我们考虑先打表找规律。
```cpp

void solve(int n) {
  vector<int> a(n);
  int mx = -1;
  _rep(i, 0, n) a[i] = i + 1;
  do {
    auto calc = [&]() {
      int cnt = 0, mx = 0;
      _rep (i, 0, n) cnt += a[i] * (i + 1);
      _rep (i, 0, n) mx = max(a[i] * (i + 1), mx);
      return cnt - mx;
    };
    int k = calc();
    if (k > mx) {
      mx = k;
    }
  } while (next_permutation(a.begin(), a.end()));
  _rep(i, 0, n) a[i] = i + 1;
  do {
    auto calc = [&]() {
      int cnt = 0, mx = 0;
      _rep (i, 0, n) cnt += a[i] * (i + 1);
      _rep (i, 0, n) mx = max(a[i] * (i + 1), mx);
      return cnt - mx;
    };
    int k = calc();
    if (k == mx) {
      for (auto i : a) cout << i << ' ';
      cout << '\n';
    }
  } while (next_permutation(a.begin(), a.end()));
  
  cout << '\n';
}

```
之后我们就能发现，如果一个是答案，那么我们的答案数列一定是我们的某个前缀保持不表，反转我们的后缀。我们于是可以枚举我们的 j，作为我们反转位置的起点，在这个位置之前，我们采用正序，在这个位置之后，我们采用倒序。于是，我们就可以用暴力枚举 k 后暴力计算我们的答案。

```cpp
void solve() {
  int n; cin >> n;
  rep (i, 1, n) {
    a[i] = i;
  }
  int ans = 0;
  auto calc = [&]() {
    int cnt = 0, mx = 0;
    rep (i, 1, n) cnt += a[i] * i;
    rep (i, 1, n) mx = max(a[i] * i, mx);
    return cnt - mx;
  };
  rep (i, 1, n) {
    reverse(a + i, a + n + 1);
    ans = max(calc(), ans);
    reverse(a + i, a + n + 1);
  }
  cout << ans << '\n';
}
```