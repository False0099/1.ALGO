# 知识点
  ## [[二分图]] [[二分图最大匹配]] [[最小点覆盖]]
# 题目
 有两台机器 A，B以及 K个任务。

机器 A有 N种不同的模式（模式 0∼N−1），机器 B有 M种不同的模式（模式 0∼M−1）。

两台机器最开始都处于模式 0。

每个任务既可以在 A上执行，也可以在 B上执行。

对于每个任务 i，给定两个整数 a[i]和 b[i]，表示如果该任务在 A上执行，需要设置模式为 a[i]，如果在 B上执行，需要模式为 b[i]。

任务可以以任意顺序被执行，但每台机器转换一次模式就要重启一次。

求怎样分配任务并合理安排顺序，能使机器重启次数最少。

# 输入格式
输入包含多组测试数据。

每组数据第一行包含三个整数 N, M, K。

接下来 K行，每行三个整数 i, a[i]和 b[i]，i为任务编号，从 0开始。

当输入一行为 0时，表示输入终止。

# 输出格式
每组数据输出一个整数，表示所需的机器最少重启次数，每个结果占一行。

# 数据范围
N, M<100, K<1000
# 输入样例 ：
5 5 10
0 1 1
1 1 2
2 1 3
3 1 4
4 2 1
5 2 2
6 2 3
7 2 4
8 3 3
9 4 3
0
# 输出样例 ：
3
# 思路
·这一题要求转换的最小次数，换个角度就是求每一个模式所能利用的最大次数。
·求每一个模式利用的最大次数也就是求最小覆盖点。而最小覆盖点就等于最大匹配边。
·最小点覆盖、最大独立集、最小路径点覆盖 (最小路径重复点覆盖)
  最大匹配数 = 最小点覆盖 = 总点数 - 最大独立集 = 总点数 - 最小路径覆盖
·最小点覆盖问题
	定义: 给我们一个图, 从中选出最少的点, 使得图中的每一条边至少有一个顶点被选，在这里，方案数就是我们的顶点。
# AC 代码
```cpp
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 110;

int n, m, k;
int match[N];
bool g[N][N], st[N];

bool find(int x)
{
    for(int i=0;i<m;i++)
    {
        if(!st[i] && g[x][i])
        {
            st[i] = true;
            if(match[i]==-1||find(match[i]))
            {
                match[i]=x;
                return true;
            }
        }
    }
    return false;
}

int main()
{
    while (cin >> n, n)
    {
        cin >> m >> k;
        memset(g, 0, sizeof g);
        memset(match, -1, sizeof match);

        while (k -- )
        {
            int t, a, b;
            cin >> t >> a >> b;
            if (!a || !b) continue;
            g[a][b] = true;//按照每一个任务去建图
        }

        int res = 0;
        for (int i = 0; i < n; i ++ )//算一个最大流
        {
            memset(st, 0, sizeof st);
            if (find(i)) res ++ ;
        }

        cout << res << endl;
    }

    return 0;
}


```
# 备注
