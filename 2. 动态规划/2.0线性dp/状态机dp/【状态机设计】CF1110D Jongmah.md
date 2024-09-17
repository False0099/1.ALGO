# Jongmah

## 题面翻译

你在玩一个叫做 Jongmah  的游戏，你手上有 $n$ 个麻将，每个麻将上有一个在 $1$ 到 $m$ 范围内的整数 $a_i$。

为了赢得游戏，你需要将这些麻将排列成一些三元组，每个三元组中的元素是相同的或者连续的。如 $7,7,7$ 和 $12,13,14$ 都是合法的。你只能使用手中的麻将，并且每个麻将只能使用一次。

请求出你最多可以形成多少个三元组。

数据范围：$1\le n,m\le 10^6$，$1\le a_i\le m$

## 题目描述

You are playing a game of Jongmah. You don't need to know the rules to solve this problem. You have $ n $ tiles in your hand. Each tile has an integer between $ 1 $ and $ m $ written on it.

To win the game, you will need to form some number of triples. Each triple consists of three tiles, such that the numbers written on the tiles are either all the same or consecutive. For example, $ 7, 7, 7 $ is a valid triple, and so is $ 12, 13, 14 $ , but $ 2,2,3 $ or $ 2,4,6 $ are not. You can only use the tiles in your hand to form triples. Each tile can be used in at most one triple.

To determine how close you are to the win, you want to know the maximum number of triples you can form from the tiles in your hand.

## 输入格式

The first line contains two integers integer $ n $ and $ m $ ( $ 1 \le n, m \le 10^6 $ ) — the number of tiles in your hand and the number of tiles types.

The second line contains integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le m $ ), where $ a_i $ denotes the number written on the $ i $ -th tile.

## 输出格式

Print one integer: the maximum number of triples you can form.

## 样例 #1

### 样例输入 #1

```
10 6
2 3 3 3 4 4 4 5 5 6
```

### 样例输出 #1

```
3
```

## 样例 #2

### 样例输入 #2

```
12 6
1 5 3 3 3 4 3 5 3 2 3 3
```

### 样例输出 #2

```
3
```

## 样例 #3

### 样例输入 #3

```
13 5
1 1 5 1 2 3 3 2 4 2 3 4 5
```

### 样例输出 #3

```
4
```

## 提示

In the first example, we have tiles $ 2, 3, 3, 3, 4, 4, 4, 5, 5, 6 $ . We can form three triples in the following way: $ 2, 3, 4 $ ; $ 3, 4, 5 $ ; $ 4, 5, 6 $ . Since there are only $ 10 $ tiles, there is no way we could form $ 4 $ triples, so the answer is $ 3 $ .

In the second example, we have tiles $ 1 $ , $ 2 $ , $ 3 $ ( $ 7 $ times), $ 4 $ , $ 5 $ ( $ 2 $ times). We can form $ 3 $ triples as follows: $ 1, 2, 3 $ ; $ 3, 3, 3 $ ; $ 3, 4, 5 $ . One can show that forming $ 4 $ triples is not possible.

## 题解
考虑到其实要组三元组跟数组的顺序没关系，只跟每个值的数目有关系，这时候为什么这个 m 也是1e6就一目了然了。我们应该把数值作为 dp 的状态
我们一个数有下面几种情况可能会被放在我们的三元组中：
1. (x, x+1, x+2)
2. (x-1, x, x+1)
3. (x-2, x-1, x)
4. (x, x, x)
然后我们就可以直接暴力的设我们的 $dp[i][t_{1}][t_{2}][t_{3}][t_{4}]$ 表示我们的当前状态，我们的转移就是我们的 $dp[i][t_{1}][t_{2}][t_{3}][t_{4}]=max(dp[i-1][t_{2}][t_{3}][m_{1}][m_{2}]+t_{3}+t_{4})$
,其中我们的 $m_{1},m_{2}$ 需要我们去自行枚举。于是我们考虑下面的优化：
1. 我们的 $t_{4}$ 是可以通过我们直接计算得出的，不需要我们另外开一个数组存储，因为我们的“顺子”一旦模 3 为 0，我们就可以直接转化为三个三联对，而不是用顺子表达，这样我们就可以省去一个维度
转移方程变为：
$dp[i][t_{1}][t_{2}][t_{3}]=max\left( dp[i-1][t_{2}][t_{3}][m_{1}]+t_{1}+\frac{cnt-t[1]-t[2]-t[3]}{3} \right)$

```cpp
#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e6 + 10;
int dp[maxn][3][3][3]; // dp[n][i][j][k]表示 n 在三元组中第一位的三元组有i个，在第二位的有j个，在第三位的有k个;
int cnt[maxn];

int main()
{
    int N, M;
    cin >> N >> M;
    for (int i = 1; i <= N; i++)
    {
        int x;
        cin >> x;
        cnt[x]++;
    }
    for (int n = 1; n <= M; n++)
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                for (int k = 0; k < 3; k++)
                {
                    if (cnt[n] < (i + j + k))
                        continue;
                    for (int m = 0; m < 3; m++)
                    {
                        dp[n][i][j][k] = max(dp[n][i][j][k], dp[n - 1][j][k][m] + i + (cnt[n] - i - j - k) / 3);
                    }
                }
            }
        }
    }
    int ans = 0;
    for (int i = 0; i < 3; i++)
        ans = max(ans, dp[M][0][0][i]);
    cout << ans << endl;
}
```


```c++
#include <cstdio>
#include <algorithm>
using namespace std;

int cnt[1000010];
int dp[1000010][3][3];
int n, m, temp;

void solve() {
    for (int i = 1; i <= m; ++i) {
        for (int c = 0; c < 3; ++c) {
            for (int b = 0; b < 3; ++b) {
                for (int a = 0; a < 3; ++a) {
                    if (a + b + c > cnt[i]) continue;
                    if (b + c > cnt[i + 1]) continue;
                    if (c > cnt[i + 2]) continue;
                    dp[i][c][b] = max(dp[i][c][b], dp[i - 1][b][a] + c + (cnt[i] - c - b - a) / 3);
                }
            }
        }
    }
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &temp);
        ++cnt[temp];
    }

    solve();

    printf("%d\n", dp[m][0][0]);
    return 0;
}
```
