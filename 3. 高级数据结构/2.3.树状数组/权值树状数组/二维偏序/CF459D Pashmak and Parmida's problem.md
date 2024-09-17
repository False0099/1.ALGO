# Pashmak and Parmida's problem

## 题面翻译

- 给出长度为 $n(1\le n\le10^6)$ 的序列 $a(1\le a_i\le10^9)$。
- $f(i,j,x)$ 表示 $a_i\dots a_j$ 中 $x$ 的出现次数。
- 求有多少对 $i,j$ 满足 $f(1,i,a_i) > f(j,n,a_j)$ 且 $i < j$。

## 题目描述

Parmida is a clever girl and she wants to participate in Olympiads this year. Of course she wants her partner to be clever too (although he's not)! Parmida has prepared the following test problem for Pashmak.

There is a sequence $ a $ that consists of $ n $ integers $ a_{1}, a_{2},..., a_{n} $ . Let's denote $ f (l, r, x) $ the number of indices $ k $ such that: $ l<=k<=r $ and $ a_{k}=x $ . His task is to calculate the number of pairs of indicies $ i, j $ $ (1<=i&lt; j<=n) $ such that $ f (1, i, a_{i})&gt; f (j, n, a_{j}) $ .

Help Pashmak with the test.

## 输入格式

The first line of the input contains an integer $ n $ $ (1<=n<=10^{6}) $ . The second line contains $ n $ space-separated integers $ a_{1}, a_{2},..., a_{n} $ $ (1<=a_{i}<=10^{9}) $ .

## 输出格式

Print a single integer — the answer to the problem.

## 样例 #1

### 样例输入 #1

```
7
1 2 1 1 2 2 1
```

### 样例输出 #1

```
8
```

## 样例 #2

### 样例输入 #2

```
3
1 1 1
```

### 样例输出 #2

```
1
```

## 样例 #3

### 样例输入 #3

```
5
1 2 3 4 5
```

### 样例输出 #3

```
0
```


## 题解
![[Pasted image 20231105203251.png]]

```cpp
#include<bits/stdc++.h>
#define ll long long
#define rep(i, m, n) for (int i = m; i <= n; i++)
#define per(i, m, n) for (int i = m; i >= n; i--)
#define pb push_back
#define mp make_pair
#define all(v) v.begin(), v.end()
#define INF 0x3f3f3f3f
using namespace std;

const int maxn = 1e6 + 5;

int a[maxn], b[maxn], N, cnt[maxn], occurence[maxn][2], t[maxn];

// 1. Compression
// 2. Use prefix sum to find the number f
// 3. Use BIT

inline int lowbit(int x) {
    return x & (-x);
}

int sum(int x) {
    int ans = 0;
    while (x != 0) {
        ans += t[x];
        x -= lowbit(x);
    }
    return ans;
}

void update(int x, int k) {
    while (x <= N) {
        t[x] += k;
        x += lowbit(x);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> N;
    rep(i, 1, N) {
        cin >> a[i];
        b[i] = a[i];
    }
    sort(b + 1, b + N + 1);
    int len = unique(b + 1, b + N + 1) - b - 1;
    rep(i, 1, N) a[i] = lower_bound(b + 1, b + len + 1, a[i]) - b;
    ll ans = 0;
    rep(i, 1, N) {
        occurence[i][0] = ++cnt[a[i]];
    }
    memset(cnt, 0, sizeof cnt);
    per(i, N, 1) {
        occurence[i][1] = ++cnt[a[i]];
    }
    per(i, N, 1) {
        ans += sum(occurence[i][0] - 1);
        update(occurence[i][1], 1);
    }
    cout << ans << "\n";
    return 0;
}
```