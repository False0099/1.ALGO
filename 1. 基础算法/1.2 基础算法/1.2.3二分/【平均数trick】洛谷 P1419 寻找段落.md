# 寻找段落

## 题目描述

给定一个长度为 $n$ 的序列 $a$，定义 $a_i$ 为第 $i$ 个元素的价值。现在需要找出序列中最有价值的“段落”。段落的定义是长度在 $[S, T]$ 之间的连续序列。最有价值段落是指平均值最大的段落。

**段落的平均值** 等于 **段落总价值** 除以 **段落长度**。

## 输入格式

第一行一个整数 $n$，表示序列长度。

第二行两个整数 $S$ 和 $T$，表示段落长度的范围，在 $[S, T]$ 之间。

第三行到第 $n+2$ 行，每行一个整数表示每个元素的价值指数。

## 输出格式

一个实数，保留 $3$ 位小数，表示最优段落的平均值。

## 样例 #1

### 样例输入 #1

```
3
2 2
3
-1
2
```

### 样例输出 #1

```
1.000
```

## 提示

【数据范围】

对于 $30\%$ 的数据有 $n \le 1000$。

对于 $100\%$ 的数据有 $1 \le n \le 100000$，$1 \le S \le T \le n$，$-{10}^4 \le a_i \le {10}^4$。

【题目来源】

Tinylic 改编

## 题解
我们这一题理论上是属于我们的 0-1 分数规划问题，我们可以令我们分子的权重变为 1 就可以证明我们的说法. 因此，我们现在对于我们的问题只需要这样操作：
1. 我们枚举我们的答案s
2. 对于我们的每一个答案 s，我们计算变换后的数组 $a[i]-s$ 中，是否存在一段连续和是大于 0 的，如果有，那么我们就返回 true，否则，我们就返回 false

```cpp
#include <iostream>
#include <cstdio>
#include <cstdlib>
#define maxn 100010

using namespace std;

int n, s, t, i;
double l, r, mid, ans;
double a[maxn];
int b[maxn];
double sum[maxn];
int q[maxn];

bool check(double x) {
    int i, l = 1, r = 0;
    for (i = 1; i <= n; i++)
        a[i] = (double)b[i] - x;
    sum[0] = 0;
    for (i = 1; i <= n; i++)
        sum[i] = sum[i - 1] + a[i];
    for (i = 1; i <= n; i++) {
        if (i >= s) {
            while (r >= l && sum[i - s] < sum[q[r]])    r--;
            q[++r] = i - s;
        }
        if (l <= r && q[l] < i - t) l++;
        if (l <= r && sum[i] - sum[q[l]] >= 0) return true;
    }
    return false;
}

int main() {

    scanf("%d", &n);
    scanf("%d%d", &s, &t);
    for (i = 1; i <= n; i++)
        scanf("%d", &b[i]);
    ans = l = -10000; r = 10000;
    while (r - l > 1e-5) {
        mid = (l + r) / 2;
        if (check(mid))
            ans = l = mid;
        else r = mid;
    }

    printf("%.3lf\n", ans);
    return 0;
}
```