# [ABC 366 E] Manhattan Multifocal Ellipse

## 题面翻译

### 题目描述
二维平面上的 $N$ 个点 $(x_{1},y_{}1），(x_{2},y_{2})\ldots(x_{N},y_{N})$，和非负整数 $D$, $D$ 是给定的。
一组整数 $(x,y)$，若 x, y 满足：

$\sum_{i=1}^n(|x-x_{i}|,|y-y_{i}|) \le D$

输出满足的整数数量。
### 输入格式
输入 $N$，$D$。接下来 $N$ 行，每行两个整数，表示二维平面上的坐标。
### 输出格式
如题目描述

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc366/tasks/abc366_e

$ 2 $ 次元平面上の $ N $ 個の点 $ (x_1, y_1), (x_2, y_2),\dots, (x_N, y_N) $ と、非負整数 $ D $ が与えられます。

整数の組 $ (x, y) $ であって、 $ \displaystyle\ \sum_{i=1}^N\ (|x-x_i|+|y-y_i|)\ \leq\ D $ を満たすものの個数を求めてください。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ N $ $ D $ $ x_1 $ $ y_1 $ $ x_2 $ $ y_2 $ $ \vdots $ $ x_N $ $ y_N $

## 输出格式

答えを出力せよ。

## 样例 #1

### 样例输入 #1

```
2 3
0 0
1 0
```

### 样例输出 #1

```
8
```

## 样例 #2

### 样例输入 #2

```
2 0
0 0
2 0
```

### 样例输出 #2

```
0
```

## 样例 #3

### 样例输入 #3

```
6 100
9 -6
10 -1
2 10
-1 7
-7 5
-1 -4
```

### 样例输出 #3

```
419
```

## 提示

### 制約

- $ 1\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 0\ \leq\ D\ \leq\ 10^6 $
- $ -10^6\ \leq\ x_i,\ y_i\ \leq\ 10^6 $
- $ i\neq\ j $ ならば $ (x_i, y_i)\ \neq\ (x_j, y_j) $
- 入力はすべて整数
 
### Sample Explanation 1

下図は、サンプル $ 1 $ の入力と答えを可視化したものです。青い点が入力を表します。青い点と赤い点の合計 $ 8 $ 点が、問題文中の条件を満たす点です。 !\ [\](https://img.atcoder.jp/abc366/2b6d85ce3511e14c65dc80e052d62bca.png)

## 题解
 对上式进行变形：$$\sum_{i=1}^n|y-y_i|\leq D-\sum_{i=1}^n|x-x_i|$$
我们可以枚举所有的 $x$,带入上式右边，然后计算有多少个 $y$ 满足。

枚举 $x$ 的坐标的话，我们需要实现 $\Theta(1)$ 查询 $\sum_{i=1}^n|x-x_i|$。

思考 $x$ 坐标每往右移 1, 它对答案的影响会发生什么，什么会导致它发生变化。
这里先说结论，从点 $p$,到 $p+1$ 它对答案的变化是点 $p+1$ 右边有多少个 $x_i$,减去左边有多少个 $x_i$。更为形式化的，设之前的答案为 old，现在的答案 now，点 $p+1$ 的左边有 $l$ 个满足条件的 $x_i$ ,右边有 $r$ 个满足条件的，那么 $now=old-l+r$。

为什么这么做可以？
![[Pasted image 20240901214136.png]]
看图，其中黄色点是 $x_i$,蓝色点是 $p$,红色点是 $p+1$,蓝色线是 $p$ 所有 $x_i$ 到它的距离之和，也就是我
们要算的东西，红色点同理。
从图中我们可以直观的看到从点 $p$ 到 $p+1$,红点左侧的每条线段长度都比之前长了 1，右边的线段长度
都减少了 1。左边有两个点就减少 2，右边 3 个点就增加 3。
和我们的结论是一样的。




$$\begin{aligned}&\text{第一个问题已经解决了,我们还需要 }\Theta(1)\text{ 求出有多少个 }y\text{ 满足式子。}\\&\text{预处理所有的 }y\text{ 的值,用算 }x\text{ 的方法求出}\sum_{i=1}^n|y-y_i|\text{ 的值,放进一个桶里,然后进行前缀和,就行}\\&\text{了。}\\&\text{这里这道题也就讲完了。}\\&\text{最后总结一下算法流程:}\\&1.\text{ 预处理所有 }y\text{ 的可能值,放进桶里,前缀和。}\\&2.\text{ 用类似的法,校学 }x\text{ 的可能值,对每个 }x\text{ 算出有多少个 }y\text{ 满足条件。}\end{aligned}$$


```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 6e6 + 10;
int x[maxn], y[maxn];
int cnt[maxn], sum[maxn];
int mpx[maxn], mpy[maxn];
signed main()
{
    int n, d;
    cin >> n >> d;
    for (int i = 1; i <= n; i++)
    {
        cin >> x[i] >> y[i];
        mpx[x[i] + 2000000]++, mpy[y[i] + 2000000]++;
    }
    int now = 0, l = 0, r = n, ans = 0;
    for (int i = 1; i <= n; i++)
    {
        now += abs((-(2e6 + 1)) - y[i]);
    }
    for (int i = -2e6; i <= 2e6; i++)
    {
        now += l, now -= r;
        if (now <= d)
            cnt[now]++;
        l += mpy[i + 2000000], r -= mpy[i + 2000000];
    }
    for (int i = 0; i <= d; i++)
    {
        sum[i] = sum[i - 1] + cnt[i];
    }
    now = 0, l = 0, r = n;
    for (int i = 1; i <= n; i++)
    {
        now += abs(-(2e6 + 1) - x[i]);
    }
    for (int i = -2e6; i <= 2e6; i++)
    {
        now += l, now -= r;
        if (now <= d)
            ans += sum[d - now];
        l += mpx[i + 2000000], r -= mpx[i + 2000000];
    }
    cout << ans;
    return 0;
}
```