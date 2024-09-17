农夫约翰的农场由 $N$ 块田地组成，每块地里都有一定数量的牛，其数量不会少于 $1$ 头，也不会超过 $2000$ 头。

约翰希望用围栏将一部分连续的田地围起来，并使得围起来的区域内每块地包含的牛的数量的平均值达到最大。

围起区域内至少需要包含 $F$ 块地，其中 $F$ 会在输入中给出。

在给定条件下，计算围起区域内每块地包含的牛的数量的平均值可能的最大值是多少。

#### 输入格式

第一行输入整数 $N$ 和 $F$，数据间用空格隔开。

接下来 $N$ 行，每行输入一个整数，第 $i+1$ 行输入的整数代表第 $i$ 片区域内包含的牛的数目。

#### 输出格式

输出一个整数，表示平均值的最大值乘以 $1000$ 再 **向下取整** 之后得到的结果。

#### 数据范围

$1 \le N \le 100000$  
$1 \le F \le N$

#### 输入样例：

```
10 6
6 
4
2
10
3
8
5
9
4
1
```

#### 输出样例：

```
6500
```


## 题解
我们本题采用二分，我们枚举我们的最大平均值 x，然后求我们原数组的最长的前缀和不为 0 的区间的长度。这一步我们可以通过我们的双指针来实现（其实是 0-1 分数规划的一种特殊情况）
```cpp
#include <cstdio>
#include <iostream>

const int N = 100005;
int cows[N]; double sum[N];

int n, m;

bool check(double avg) {
    for (int i = 1; i <= n; i++) {
        sum[i] = sum[i - 1] + cows[i] - avg;
    }

    double minv = 0;
    for (int i = 0, j = m; j <= n; j++, i++) {
        minv = std::min(minv, sum[i]);
        if(sum[j] - minv >= 0) return true;
    } return false;
}

int main() {
    scanf("%d %d", &n, &m);
    double l = 0, r = 0;
    for (int i = 1; i <= n; i++) {
        scanf("%d", &cows[i]);
        r = std::max(r, (double)cows[i]);
    }

    while(r - l > 1e-5) {
        double mid = (l + r) / 2;
        if(check(mid)) l = mid;
        else r = mid;
    } printf("%d\n", (int)(r * 1000));
    return 0; 
}

作者：Nicoppa
链接：https://www.acwing.com/solution/content/1148/
来源：AcWing
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
```
来源：AcWing
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。