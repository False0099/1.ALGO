## Description

一道好题应该有一个简洁的题面。

有一个长度为 n，初始全为 0 的序列 a，另有一个长度为 n 的序列 b，你希望将 a 变成 b，你可以执行如下两种操作：

1 x：将 a 中所有值为 x 的数 +1。

2 x：将 a 中下标为 x 的数 +1。

你不需要最小化操作次数，但只能使用最多 20000 次操作。

## Input

第一行一个正整数 n（1≤n≤1000）。

第二行 n 个非负整数 b1,⋯, bn（0≤bi≤n）描述序列 b。

## Output

第一行一个整数 k 表示操作次数，你需要保证 0≤k≤20000。

之后 k 行每行两个整数 1 x 或 2 x，表示一次操作。对于 1 x 类型的操作，你需要保证 0≤x≤n，对于 2 x 类型的操作，你需要保证 1≤x≤n。

## Sample

#### #0

#### **Input**

Copy

4
2 4 3 1

#### **Output**

Copy

7
1 0
2 1
2 2
2 3
2 2
1 3
2 3

## Hint

## 题解
我们这一题如果考虑我们的暴力做法的话是不能冲过去的，我们于是需要我们借助我们的分治来优化我们的操作。我们每一次处理我们一半的元素，并且我们按照下面的方法来构造；
1. 我们每一次让所有数都等于我们的最左边的那一个数
2. 我们完成之后，将我们的数组分两半，一半

这一种想法其实来源于我们的朴素想法：我们把我们的数组排序后，每一次都先构成我们的最小的元素，然后再对剩下的位置构造我们的不是最小的元素。

本题的递归只是优化了我们的一个构造过程，而没有在根本上改变我们的构造方法。

```cpp
```cpp
#include "bits/stdc++.h"

#define range(a) begin(a), end(a)

using namespace std;
using i64 = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> a(n);
    vector<vector<int>> p(1001);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        p[a[i]].push_back(i);
    }

    sort(range(a));
    a.erase(unique(range(a)), a.end());
    int N = a.size();

    vector<pair<int, int>> ans;

    function<void(int, int, int)> dfs = [&](int l, int r, int val) {
        if (val != a[l]) {
            for (int i = l; i < r; i++) {
                for (auto &j : p[a[i]]) {
                    ans.push_back({2, j + 1});
                }
            }
            for (int i = val + 1; i < a[l]; i++) {
                ans.push_back({1, i});
            }
        }//让我们的区间都大于等于我们的$a[l]$      
        if (r == l + 1) {
            return;
        }
        int m = (l + r) >> 1;
        dfs(m, r, a[l]);
        dfs(l, m, a[l]);
    };

    dfs(0, N, 0);

    cout << ans.size() << '\n';
    for (auto &[o, j] : ans) {
        cout << o << ' ' << j << '\n';
    }

    return 0;
}
```


