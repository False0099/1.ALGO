# 知识点
  ## [[单源最短路问题]]
# 题目
 在 n 个人中，某些人的银行账号之间可以互相转账。

这些人之间转账的手续费各不相同。

给定这些人之间转账时需要从转账金额里扣除百分之几的手续费，请问 A 最少需要多少钱使得转账后 B 收到 100 元。

## 输入格式
第一行输入两个正整数 n, m，分别表示总人数和可以互相转账的人的对数。

以下 m 行每行输入三个正整数 x, y, z，表示标号为 x 的人和标号为 y 的人之间互相转账需要扣除 z% 的手续费 ( z<100 )。

最后一行输入两个正整数 A, B。

数据保证 A 与 B 之间可以直接或间接地转账。

## 输出格式
输出 A 使得 B 到账 100 元最少需要的总费用。

精确到小数点后 8 位。

## 数据范围
1≤n≤2000
,
M≤10^5
## 输入样例 ：
3 3
1 2 1
2 3 2
1 3 3
1 3
## 输出样例 ：
103.07153164

# 思路
·原本单源最短路中，每一次转移我们是加法，转成乘法以后，我们的最短路还是可以按照原来的思路去更新，实在不行，我们可以用 log 来把乘法变成加法。
·
·
# AC 代码
```cpp
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 2010;

int n, m, S, T;
double g[N][N];
double dist[N];
bool st[N];

void dijkstra()
{
    dist[S] = 1;
    for (int i = 1; i <= n; i ++ )
    {
        int t = -1;
        for (int j = 1; j <= n; j ++ )
            if (!st[j] && (t == -1 || dist[t] < dist[j]))
                t = j;
        st[t] = true;

        for (int j = 1; j <= n; j ++ )
            dist[j] = max(dist[j], dist[t] * g[t][j]);
    }
}

int main()
{
    scanf("%d%d", &n, &m);

    while (m -- )
    {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        double z = (100.0 - c) / 100;
        g[a][b] = g[b][a] = max(g[a][b], z);
    }

    cin >> S >> T;

    dijkstra();

    printf("%.8lf\n", 100 / dist[T]);

    return 0;
}
```
# 备注
