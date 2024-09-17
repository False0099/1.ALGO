# Trust Nobody

## 题面翻译

**题目描述**

有由 $n$ 个人组成的群体，其中的一部分人被称为“说谎者”，总是说谎话，另一部分人总是说真话。对于 $1\leq i \leq n$ ，第 $i$ 个人说：“在我们中间至少有 $l_i$ 个人说谎话。”写一个程序判断人们所说的是矛盾的，还是可能存在的。如果是可能存在的，输出群体中说谎者的数量，如果有多种可能，输出其中任意一种即可。

**输入格式**

第一行一个整数 $t(1 \leq t \leq 1000)$ ，代表测试数据的组数。

对于每一组测试数据：
第一行一个整数 $n(1 \leq n \leq 100)$ ，代表群体中的人数。

第二行共 $n$ 个数，以空格隔开，对于 $1\leq i \leq n$，第 $i$ 个数代表 $l_i$ 。

数据保证 $\displaystyle\sum n \leq 10^4$。

**输出格式**

对于每一组测试数据，输出一个整数。如果人们所说的是矛盾的，输出 $-1$ ,否则，输出群体中说谎者的数量，如果有多种可能，输出其中任意一种即可。

## 题目描述

There is a group of $ n $ people. Some of them might be liars, who always tell lies. Other people always tell the truth. The $ i $ -th person says "There are at least $ l_i $ liars amongst us". Determine if what people are saying is contradictory, or if it is possible. If it is possible, output the number of liars in the group. If there are multiple possible answers, output any one of them.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \leq t \leq 1000 $ ) — the number of test cases.

The first line of each test case contains a single integer $ n $ ( $ 1 \leq n \leq 100 $ ).

The second line of each test case contains $ n $ integers $ l_i $ ( $ 0 \leq l_i \leq n $ ) — the number said by the $ i $ -th person.

It's guaranteed that the sum of all $ n $ does not exceed $ 10^4 $ .

## 输出格式

For each test case output a single integer. If what people are saying is contradictory, output $ -1 $ . Otherwise, output the number of liars in the group. If there are multiple possible answers, output any one of them.

## 样例 #1

### 样例输入 #1

```
7
2
1 2
2
2 2
2
0 0
1
1
1
0
5
5 5 3 3 5
6
5 3 6 6 3 5
```

### 样例输出 #1

```
1
-1
0
-1
0
3
4
```

## 提示

In the first example, the only possible answer is that the second person is a liar, so the answer is $ 1 $ liar.

In the second example, it can be proven that we can't choose the liars so that all the requirements are satisfied.

In the third example, everybody tells the truth, so the answer is $ 0 $ liars.

## 题解
我们本题采用正难则反的思想，我们考虑**枚举我们有多少个骗子，然后验证我们的猜想是否正确**。

```cpp
#include <bits/stdc++.h>

using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> l(n);
    for (auto &i : l) {
        cin >> i;
    }
    for (int cnt_liars = 0; cnt_liars <= n; ++cnt_liars) {
        int actual = 0;
        for (auto i : l) {
            if (!(cnt_liars >= i)) {
                ++actual;
            }
        }
        if (actual == cnt_liars) {
            cout << cnt_liars << '\n';
            return;
        }
    }
    cout << "-1\n";
}

signed main() {
    int t;
    cin >> t;
    while (t--) solve();
    return 0;
}
```