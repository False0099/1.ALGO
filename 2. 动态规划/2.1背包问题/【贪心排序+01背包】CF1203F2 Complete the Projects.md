# Complete the Projects (hard version)

## 题面翻译

![](https://cdn.luogu.org/upload/pic/72121.png)

## 题目描述

The only difference between easy and hard versions is that you should complete all the projects in easy version but this is not necessary in hard version.

Polycarp is a very famous freelancer. His current rating is $ r $ units.

Some very rich customers asked him to complete some projects for their companies. To complete the $ i $ -th project, Polycarp needs to have at least $ a_i $ units of rating; after he completes this project, his rating will change by $ b_i $ (his rating will increase or decrease by $ b_i $ ) ( $ b_i $ can be positive or negative). Polycarp's rating should not fall below zero because then people won't trust such a low rated freelancer.

Polycarp can choose the order in which he completes projects. Furthermore, he can even skip some projects altogether.

To gain more experience (and money, of course) Polycarp wants to choose the subset of projects having maximum possible size and the order in which he will complete them, so he has enough rating before starting each project, and has non-negative rating after completing each project.

Your task is to calculate the maximum possible size of such subset of projects.

## 输入格式

The first line of the input contains two integers $ n $ and $ r $ ( $ 1 \le n \le 100, 1 \le r \le 30000 $ ) — the number of projects and the initial rating of Polycarp, respectively.

The next $ n $ lines contain projects, one per line. The $ i $ -th project is represented as a pair of integers $ a_i $ and $ b_i $ ( $ 1 \le a_i \le 30000 $ , $ -300 \le b_i \le 300 $ ) — the rating required to complete the $ i $ -th project and the rating change after the project completion.

## 输出格式

Print one integer — the size of the maximum possible subset (possibly, empty) of projects Polycarp can choose.

## 样例 #1

### 样例输入 #1

```
3 4
4 6
10 -2
8 -1
```

### 样例输出 #1

```
3
```

## 样例 #2

### 样例输入 #2

```
5 20
45 -6
34 -15
10 34
1 27
40 -45
```

### 样例输出 #2

```
5
```

## 样例 #3

### 样例输入 #3

```
3 2
300 -300
1 299
1 123
```

### 样例输出 #3

```
3
```

## 题解
**注意到，我们的顺序会影响到我们的背包的计算，于是我们就需要考虑贪心的排序**。


首先，我们由我们的贪心不等式可以得到，我们一定是首先完成我们的正向的任务，做到不能做的时候，再去考虑我们的负贡献的任务。

对于我们的负贡献的任务，我们考虑使用 dp 来进行处理，我们用 $dp[i][j]$ 表示我们前 i 个里面选了 j 个需要的是多少，我们这个时候，显然我们存在转移 $dp[i][j]=dp[i-1][j-w]+v$。于是我们就完成了本题：

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, r, cnt, ans, cnt1, cnt2, dp[105][60005];
struct node {
    int x, y;
}a[105], b[105];
bool cmp(node x, node y) {
    return x.x < y.x;
}
bool cmp2(node x, node y) {
    return x.x + x.y > y.x + y.y;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> r;
    for(int i = 1, x, y; i <= n; i++) {
        cin >> x >> y;
        if(y < 0)
            b[++cnt2] = (node){x, y};
        else
            a[++cnt1] = (node){x, y};
    }
    sort(a + 1, a + cnt1 + 1, cmp), sort(b + 1, b + cnt2 + 1, cmp2);
    for(int i = 1; i <= cnt1; i++)
        if(r >= a[i].x)
            r += a[i].y, cnt++;
        else
            break;
    for(int i = 1; i <= cnt2; i++)
        if(r >= max(b[i].x, abs(b[i].y))) {
            dp[i][r + b[i].y] = 1, ans = max(ans, 1);
            for(int j = i - 1; j; j--)
                for(int k = max(b[i].x, abs(b[i].y)); k < 60001; k++)
                    if(dp[j][k])
                        dp[i][k + b[i].y] = max(dp[i][k + b[i].y], dp[j][k] + 1), ans = max(ans, dp[i][k + b[i].y]);
        }
    cout << cnt + ans;
    return 0;
}
```