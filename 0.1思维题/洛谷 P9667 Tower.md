# [ICPC 2022 Jinan R] Tower

## 题目描述

Prof. Pang built $n$ block towers with different heights. The $i$ -th tower has height $a_i$.

Prof. Shou doesn't like these towers because of their arbitrary heights. He decides to $\textbf{first remove exactly \textit{m} of them}$, and then perform some (or none) of the following operations: 

- Choose a tower and increase its height $a_i$ by $1$. 
- Choose a tower and decrease its height $a_i$ by $1$.
- Choose a tower and divide its height $a_i$ by $2$. If the new height is not an integer, it is rounded down. 

Prof. Shou can never choose a removed tower. If after an operation, the height of a tower will become $0$, that operation is not allowed. Under these constraints, Prof. Shou can perform an arbitrary number of operations in arbitrary order. 

Prof. Shou would like all the towers that are not removed to have the same heights. Please calculate the minimum number of operations to achieve this.

## 输入格式

The first line contains one integer $T~(1\le T \le 10)$, the number of test cases.

For each test case, the first line contains two integers $n, m~(1\le n\le 500, 0\le m <n)$, the number of towers, and the number of towers Prof. Shou should delete before performing the operations.

The next line contains $n$ integers $a_1,\ldots, a_n~(1\le a_i\le 10^9)$, the initial heights of the towers.

## 输出格式

For each test case, output the minimum number of operations in one line.

## 样例 #1

### 样例输入 #1

```
3
2 0
2 6
5 0
1 2 3 4 5
5 3
1 2 3 4 5
```

### 样例输出 #1

```
2
4
1
```


## 题解
首先，做这题需要我们先发现如下性质：
1. 我们如果要从大数变成小数，先除后加一定是更优的
2. 我们**最后要变成的那一个数，一定是我们某一个出现过的数字除以 2 后变成的**

于是，我们就可以考虑枚举我们最后能够形成的数字的结果是多少，然后我们再减去花费最大的 m 座塔即可。

```cpp
#include <bits/stdc++.h>

using namespace std;
#define LL long long

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t = 1;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        vector<int> a(n);
        set<int> s;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            int x = a[i];
            while (x) {
                s.insert(x);
                x >>= 1;
            }
        }
        LL ans = 9E18;
        for (int i : s) {
            auto get = [&](int x) {
                if (x - i <= 0) {
                    return i - x;
                }
                int res = 0;
                while (x / 2 >= i) {
                    x /= 2;
                    res++;
                }
                int tmp = res + x - i;
                if (x / 2 > 0) {
                    x /= 2;
                    return min(tmp, res + 1 + i - x);
                }
                else {
                    return tmp;
                }
            };
            vector<int> tmp;
            for (int i = 0; i < n; i++) {
                tmp.push_back(get(a[i]));
            }
            sort(tmp.begin(), tmp.end());
            LL res = 0;
            for (int i = 0; i < n - m; i++) {
                res += tmp[i];
            }
            ans = min(ans, res);
        }
        cout << ans << endl;
    }
    return 0;
}
```