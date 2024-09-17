# One-Dimensional Puzzle

## 题目描述

You have a one-dimensional puzzle, all the elements of which need to be put in one row, connecting with each other. All the puzzle elements are completely white and distinguishable from each other only if they have different shapes.

Each element has straight borders at the top and bottom, and on the left and right it has connections, each of which can be a protrusion or a recess. You cannot rotate the elements.

You can see that there are exactly $ 4 $ types of elements. Two elements can be connected if the right connection of the left element is opposite to the left connection of the right element.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1931G/ab3dee044a8e18206fe7c695b7a089bda5931d43.png) All possible types of elements. The puzzle contains $ c_1, c_2, c_3, c_4 $ elements of each type. The puzzle is considered complete if you have managed to combine all elements into one long chain. You want to know how many ways this can be done.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 2 \cdot 10^5 $ ) — the number of input test cases. The descriptions of the test cases follow.

The description of each test case contains $ 4 $ integers $ c_i $ ( $ 0 \le c_i \le 10^6 $ ) — the number of elements of each type, respectively.

It is guaranteed that the sum of $ c_i $ for all test cases does not exceed $ 4 \cdot 10^6 $ .

## 输出格式

For each test case, print one integer — the number of possible ways to solve the puzzle.

Two methods are considered different if there is $ i $ , such that the types of elements at the $ i $ position in these methods differ.

Since the answer can be very large, output it modulo $ 998244353 $ .

If it is impossible to solve the puzzle, print $ 0 $ .

## 样例 #1

### 样例输入 #1

```
11
1 1 1 1
1 2 5 10
4 6 100 200
900000 900000 900000 900000
0 0 0 0
0 0 566 239
1 0 0 0
100 0 100 0
0 0 0 4
5 5 0 2
5 4 0 5
```

### 样例输出 #1

```
4
66
0
794100779
1
0
1
0
1
36
126
```


## 题解
我们本题的第一步是要推导我们的性质，我们发现，我们最后我们的形态一定是形如：1 (......) 2 (......) 1 这样的，我们的 3，4 只能是作为我们的辅助去进行。**并且3 只能放在 1，2 之间，4 只能放在 21 之间，**。

于是，我们 1，2 的位置是固定的，那么我们的唯一问题就是我们的 3,4 要怎么去放。我们这里可以有：我们 1 和 2 之间可以放若干个 3，我们的 2 和 1 之间之间可以放若干个 4，我们的 1 前面可以放若干个 4，我们的 2 后面可以放若干个 3.

于是，我们的问题就变成了，在我们的 k 个空格内放 m 个相同的球，问我们的方案数是多少。于是我们就可以转换为我们的经典隔板法来计算。

```cpp
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx,popcnt,sse4,abm")
#include <bits/stdc++.h>
using namespace std;

#ifdef WAIMAI
#define debug(HEHE...) cout << "[" << #HEHE << "] : ", dout(HEHE)
void dout() {cout << '\n';}
template<typename T, typename...U>
void dout(T t, U...u) {cout << t << (sizeof...(u) ? ", " : ""), dout(u...);}
#else
#define debug(...) 7122
#endif

// #define int long long
#define ll long long
#define Waimai ios::sync_with_stdio(false), cin.tie(0)
#define FOR(x,a,b) for (int x = a, I = b; x <= I; x++)
#define pb emplace_back
#define F first
#define S second

const int MOD = 998244353;
const int SIZE = 2e6 + 5;

int cnt[5];
int pro[SIZE], inv[SIZE];

int power(int d, int up) {
    int re = 1;
    while (up) {
        if (up & 1) re = 1ll * re * d % MOD;
        d = 1ll * d * d % MOD;
        up >>= 1;
    }
    return re;
}
int C(int x, int y) {
    return x < y || y < 0 ? 0 : 1ll * pro[x] * inv[y] % MOD * inv[x - y] % MOD;
}

void init() {
    pro[0] = 1;
    FOR (i, 1, SIZE - 1) pro[i] = 1ll * pro[i - 1] * i % MOD;
    inv[SIZE - 1] = power(pro[SIZE - 1], MOD - 2);
    for (int i = SIZE - 1; i >= 1; i--) inv[i - 1] = 1ll * inv[i] * i % MOD;
}
int cal(int n, int m) {
    return 1ll * C(cnt[3] + n - 1, n - 1) * C(cnt[4] + m - 1, m - 1) % MOD;
}
void solve() {
    FOR (i, 1, 4) cin >> cnt[i];
    if (cnt[1] == 0 && cnt[2] == 0) {
        cout << (min(cnt[3], cnt[4]) ? 0 : 1) << '\n';
        return;
    }
    if (abs(cnt[1] - cnt[2]) > 1) {
        cout << "0\n";
        return;
    }
    if (abs(cnt[1] - cnt[2]) == 1) cout << cal(max(cnt[1], cnt[2]), max(cnt[1], cnt[2])) << '\n';
    else cout << (cal(cnt[1] + 1, cnt[1]) + cal(cnt[1], cnt[1] + 1)) % MOD << '\n';
}

int32_t main() {
    Waimai;
    init();
    int tt = 1;
    cin >> tt;
    while (tt--) solve();
}
```