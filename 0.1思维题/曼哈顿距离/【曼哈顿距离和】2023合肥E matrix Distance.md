Mr. Ham has a matrix of size $ n \times m $  , where each cell is filled with a color value $c_{i,j}$. Mr. Ham is interested in the relationships between cells of the same color and wants to calculate the sum of Manhattan distances between all pairs of cells with the same color.

The Manhattan distance between two cells $ (x_1, y_1) $  and $ (x_2, y_2) $  is given by $ d_M = \left|x_1 - x_2\right| + \left|y_1 - y_2\right| $  .

Formally, please compute:

$$
\text{Total Sum} = \sum_C \sum_{(x_i, y_i) \in S_C} \sum_{(x_j, y_j)\in S_C} \left|x_i-x_j\right|+\left|y_i-y_j\right|
$$

Here, $C$ denotes the set of all distinct colors. $ S_C $  denotes the set of coordinates $(x, y)$  with the color value equal to the specified color $C$.

**Input**

The first line contains two integers $ n $  and $ m $  (1 $\leq n, m \leq 1000$), representing the number of rows and columns in the matrix.

The following contains n lines. Each line $i$ contains $m$ space-separated integers $c_{i,j}$ ($1 \leq c_{i,j} \leq 10^9$), representing the color values in the matrix.

**Output**

Output a single integer, the sum of Manhattan distances for all pairs of cells with the same color.

## 样例：
```
2 2
1 1
2 2
```

```
4
```

```
4 4
1 3 2 4
2 1 2 3
1 3 3 2
3 2 1 4
```

```
152
```

## 题解
我们本题的思路是，因为我们的曼哈顿距离在我们固定我们的点的情况下，我们的 $x$ 和我们的 $y$ 对我们的贡献是分离的。于是，我们就可以把我们的 $x$ 和 $y$ 按照偶们的每一种颜色分别取存储我们的答案。然后我们对于某一个 $vector$ 中的第 $i$ 个数，它的贡献就等于：
$\sum_{j<i}(vec_{i}-vec_{j})+\sum_{j>i}(vec_{j}-vec_{i})$。而我们的这一个式子，我们很容易在枚举我们 $i$ 的过程中维护。

```cpp
#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using vi = vector<int>;
#define all(x) begin(x), end(x)

ll getSum(vector<ll>& arr){
    sort(all(arr));
    ll out = 0;
    ll sum = 0;
    ll num = 0;
    for(ll x : arr){
        sum += x;
        ++num;

        out += num*x - sum;
    }
    return out;
}

void solve() {
    int R, C;
    cin >> R >> C;

    map<int, vector<pair<int, int>>> cols;
    for(int r = 0; r < R; ++r){
        for(int c = 0; c < C; ++c){
            int col;
            cin >> col;
            cols[col].emplace_back(r, c);
        }
    }

    ll out = 0;
    for(auto [col, pts] : cols){
        vector<ll> xs, ys;
        for(auto [x, y] : pts){
            xs.push_back(x);
            ys.push_back(y);
        }
        out += getSum(xs) + getSum(ys);
    }

    cout << out * 2 << "\n";
}

int main(void) {
    ios::sync_with_stdio(false), cin.tie(0), cin.exceptions(cin.failbit);

    solve();
    return 0;
}
```