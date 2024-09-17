There is a one-dimensional grid of length $n$. The $i$ \-th cell of the grid contains a character $s_i$, which is either '<' or '\>'.

When a pinball is placed on one of the cells, it moves according to the following rules:

-   If the pinball is on the $i$ \-th cell and $s_i$ is '<', the pinball moves one cell to the left in the next second. If $s_i$ is '\>', it moves one cell to the right.
-   After the pinball has moved, the character $s_i$ is inverted (i. e. if $s_i$ used to be '<', it becomes '\>', and vice versa).
-   The pinball stops moving when it leaves the grid: either from the left border or from the right one.

You need to answer $n$ **independent** queries. In the $i$ \-th query, a pinball will be placed on the $i$ \-th cell. Note that we always place a pinball on the initial grid.

For each query, calculate how many seconds it takes the pinball to leave the grid. It can be shown that the pinball will always leave the grid within a finite number of steps.

**Input**

Each test contains multiple test cases. The first line contains the number of test cases $t$ ($1 \le t \le 10^5$). The description of the test cases follows.

The first line of each test case contains an integer $n$ ($1 \le n \le 5 \cdot 10^5$).

The second line of each test case contains a string $s_1s_2 \ldots s_{n}$ of length $n$ consisting of characters '<' and '\>'.

It is guaranteed that the sum of $n$ over all test cases does not exceed $5 \cdot 10^5$.

**Output**

For each test case, for each $i$ ($1 \le i \le n$) output the answer if a pinball is initially placed on the $i$ \-th cell.

## 题意：
我们本题的思路是：通过我们的位置相关信息来直接求出我们的过程，首先我们可以观察到，假设我们是向左走的。那么我们的格式如下所示：
1. 向左移动走到第一个 $>$,然后再去向右走移动到第一个 $<$,如此循环，直到我们左边没有 $<$。

这个时候，如果我们暴力的计算我们的这个位置，那么我们铁定为 $TLE$,我们考虑从贡献和预处理两个方面来计算。

不妨设当前点左侧有 $x$ 个>位置分别为 $l_1,l_2,\ldots,l_x$,那么我们需要在右侧找到 $x$ 个<位置分别为 $r_{1},r_{2},\ldots r_{x}.$
 然后路径就是 $i\to l_x\to r_1\to l_{x-1}\to r_2.$

然后如果我们化简一下我们的式子，就能得到，我们的答案是：$2(\sum r_{i}-l_{j})+i$

对于我们从右边出去的情况，我们就只要把我们的原串翻转一次即可。

```cpp
```cpp
#include<iostream>
#include<cstring>
#include<vector>
using namespace std;
using LL = long long;

int main(){

    cin.tie(0);
    cout.tie(0);
    ios::sync_with_stdio(0);

    const LL INF = 1e18;
    int T;
    cin >> T;
    while(T--){
        int n;
        cin >> n;
        string s;
        cin >> s;

        auto solve = [&](){
            vector<LL> ans(n, INF);
            int cnt1 = 0, cnt2 = 0;
            LL s1 = 0, s2 = 0;
            if (s[0] == '<'){
                cnt2 += 1;
                s2 += 0;
            }
            int last = -1;
            for(int i = 0, j = 0; i < n; i++){
                if (s[i] == '>'){
                    cnt1 += 1;
                    s1 += i;
                    if (last == -1) last = i;
                }
                if (s[i] == '<'){
                    cnt2 -= 1;
                    s2 -= i;
                }
                while(cnt1 > cnt2 && j < n){
                    ++j;
                    if (s[j] == '<'){
                        cnt2 += 1;
                        s2 += j;
                    }
                }
                if (cnt1 > cnt2) break;
                if (last == -1) ans[i] = i + 1;
                else ans[i] = 2 * s2 - 2 * s1 + i + 1;
            }
            return ans;
        };

        auto ans1 = solve();
        reverse(s.begin(), s.end());
        for(auto &c : s){
            if (c == '<') c = '>';
            else c = '<';
        }
        auto ans2 = solve();
        for(int i = 0; i < n; i++){
            cout << min(ans1[i], ans2[n - 1 - i]) << ' ';
        }
        cout << '\n';
    }

}
```
```


