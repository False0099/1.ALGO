# [ABC 178 E] Dist Max

## 题面翻译

给定平面上 $N$ 个点，求出所有点对间的最大曼哈顿距离。

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc178/tasks/abc178_e

二次元平面上に $ N $ 個の点があり、$ i $ 番目の点の座標は $ (x_i, y_i) $ です。同じ座標に複数の点があることもあります。異なる二点間のマンハッタン距離として考えられる最大の値はいくつでしょうか。

ただし、二点 $ (x_i, y_i) $ と $ (x_j, y_j) $ のマンハッタン距離は $ |x_i-x_j|+|y_i-y_j| $ のことをいいます。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ N $ $ x_1 $ $ y_1 $ $ x_2 $ $ y_2 $ $ : $ $ x_N $ $ y_N $

## 输出格式

答えを出力せよ。

## 样例 #1

### 样例输入 #1

```
3
1 1
2 4
3 2
```

### 样例输出 #1

```
4
```

## 样例 #2

### 样例输入 #2

```
2
1 1
1 1
```

### 样例输出 #2

```
0
```

## 提示

### 制約

- $ 2\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ x_i, y_i\ \leq\ 10^9 $
- 入力はすべて整数

### Sample Explanation 1

$ 1 $ 番目の点と $ 2 $ 番目の点のマンハッタン距離は $ |1-2|+|1-4|=4 $ で、これが最大です。

## 题解
**注意：我们下面的思路只适用于我们的哈密顿距离，如果我们是一般距离，我们需要采用我们的旋转卡壳方法来计算**。

我们要求我们的最大曼哈顿距离，首先我们**有一个结论**，我们整个图上的最大哈密顿距离就是我们所有点中的最大 $(x+y)$,和最小 $(x+y)$ 的差，或者是我们的所有点中的最大 $(x-y)$ 和最小 $(x-y)$ 的差。
具体证明如下：

不妨将坐标系顺时针旋转 45 度。那么原来在 $(x,y)$ 位置的点来到了 $(x+y,x-y)$。令 $x+y=$ $p,x-y=q$。
 那么曼哈顿距离就变成了 $\max(|p_1-p_2|,|q_1-q_2|)$。

$$
\max\{|x_{i}-x_{j}|+|y_{i}-y_{j}|\}=\max(\max\{p_{i}\}-\min\{p_{i}\},\max\{q_{i}\}-\min\{q_{i}\})。
$$

那么我们求出 $\operatorname*{max}\{p_{i}\},\operatorname*{min}\{p_{i}\},\operatorname*{max}\{q_{i}\},\operatorname*{min}\{q_{i}\}$。最后答案就出来了。

```cpp
#include <bits/stdc++.h>

using namespace std;

int n, x, y, maxx = INT_MIN, minx = INT_MAX, maxy = INT_MIN, miny = INT_MAX;

int main() {
    for (cin >> n; n; n--) {
        cin >> x >> y;
        int p = x + y, q = x - y;
        maxx = max(maxx, p), maxy = max(maxy, q);
        minx = min(minx, p), miny = min(miny, q);
    }
    cout << max(maxx - minx, maxy - miny) << '\n';
    return 0;
}
```