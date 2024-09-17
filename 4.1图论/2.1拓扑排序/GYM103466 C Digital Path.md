Zhe the bully, is condemned by all kinds of evil, like bullying those who are weaker. His teammates have been mistreated for a long time. Finally, they decided not to put up with their buddy any more and flee to Digital Village, with the bully in hot pursuit. Due to difficult terrain and a considerable amount of Digital Paths staggered, they can't be easily arrested.

Getting familiar with the terrain as soon as possible is important for these innocents to escape the threat of bullying. All they need now is to count the number of Digital Paths in Digital Village.

To simplify the problem, Digital Village is abstracted into a grid with $n$ rows and $m$ columns filled by integers. A Digital Path is a continuous walk in the grid satisfying the following conditions:

-   adjacent boxes in the walk share a common edge;
-   the walk is maximal, which cannot be extended;
-   the walk contains at least four boxes;
-   going from one end to the other, the increment of values for any two adjacent boxes is exactly one.

Here we have some examples.

![](https://espresso.codeforces.com/61b9f3c337e39662f63f69753db0ca5e62caaa3f.png)

Figure 1: An invalid path.

The path in Figure 1 is invalid because its length is less than $4$.

![](https://espresso.codeforces.com/d65a2c4c76a65173a1f9f8f0fcca6a29120ff23e.png)

Figure 2: An invalid path.

The path in Figure 2 is invalid because it is not continuous.

![](https://espresso.codeforces.com/b912f7a35b696a3bbf4bd951f37559ceef4a6136.png)

Figure 3: An invalid path.

The path in Figure 3 is invalid because it can be extended further.

![](https://espresso.codeforces.com/1cbd0a4c2c6ad3224680bb2f7979a0b05f2962d2.png)

Figure 4: An invalid path.

The path in Figure 4 is also invalid because values in the path are not strictly increased by one.

![](https://espresso.codeforces.com/17bf4b83509eb71ead197bce7c49bb880a0bf253.png)

Figure 5: All valid paths.

Digital Paths may partially overlap. In Figure 5, there are $4$ Digital Paths marked by different colours.

**Input**

The first line contains two positive integers $n$ and $m~(1\le n,m\le 1\,000)$ describing the size of the grid.

Each of the next $n$ lines contains $m$ integers, the $j$ \-th of which, denoted by $a_{i,j}~(-10^7\le a_{i,j}\le 10^7)$, represents the value of the box in the $i$ \-th row and the $j$ \-th column.

**Output**

Output the number of Digital Paths modulo $(10^9+7)$.

## 样例 ：

```cpp
3 5
1 2 3 8 7
-1 -1 4 5 6
1 2 3 8 7

```

```
4
```

## 题解
我们本题首先考虑，如果我们走到一个点，有没有可能回到原来的点，答案是不可能的。

于是，我们如果对我们的路径建图，那么我们的结果一定是一个拓扑图，于是我们可以通过我们的拓扑排序上 DP 的思路来进行我们的计算，我们设 $dp[i][k]$ 表示我们走到图上的 i 点，长为 k 的符合要求的路径是多少。

我们的转移就如下所示：
$$\left.dp[i][k]=\left\{\begin{array}{l}dp[i][k]+dp[j][k-1],k<4\\dp[i][k]+dp[j][k-1]+dp[j][k],k=4\end{array}\right.\right.$$

之后，我们只需要在拓扑序上进行即可。

```cpp
#include <iostream>
#include <cstring>
#include <queue>

using namespace std;

const int N = 1010, MOD = 1e9 + 7, W = 1000010;
int n, m;
int idx, h[W], e[W * 2], ne[W * 2], in[W], dp[W][5];
int a[N][N];
int dx[] = {-1, 0, 1, 0}, dy[] = {0, -1, 0, 1};
int ans = 0;

void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}

void top_sort()
{
    queue<int> q;
    for (int i = 0; i < n * m; i++)
    {
        if (in[i] == 0)
        {
            q.push(i);
            dp[i][1] = 1;
        }
    }
    while (q.size())
    {
        int t = q.front();
        q.pop();
        bool flag = true;
        for (int i = h[t]; i != -1; i = ne[i])
        {
            int u = e[i];
            dp[u][2] = (dp[u][2] + dp[t][1]) % MOD;
            dp[u][3] = (dp[u][3] + dp[t][2]) % MOD;
            dp[u][4] = (dp[u][4] + dp[t][3] + dp[t][4]) % MOD;
            in[u]--;
            if (in[u] == 0)
                q.push(u);
            flag = false;
        }
        if (flag)
            ans = (ans + dp[t][4]) % MOD;
    }
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &a[i][j]);
    memset(h, -1, sizeof h);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            for (int k = 0; k < 4; k++)
            {
                int x = i + dx[k], y = j + dy[k];
                if (x >= 0 && x < n && y >= 0 && y < m && a[i][j] + 1 == a[x][y])
                {
                    add(i * m + j, x * m + y);
                    in[x * m + y]++;
                }
            }
        }
    }
    top_sort();
    printf("%d", ans);
    return 0;
}
```