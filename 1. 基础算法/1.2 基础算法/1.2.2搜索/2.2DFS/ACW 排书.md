# 知识点
  ## [[DFS]] [[A star 算法]]
# 题目
 ``给定 n 本书，编号为 1∼n。在初始状态下，书是任意排列的。在每一次操作中，可以抽取其中连续的一段，再把这段插入到其他某个位置。我们的目标状态是把书按照 1∼n 的顺序依次排列。求最少需要多少次操作。

# 输入格式
第一行包含整数 T，表示共有 T组测试数据。
每组数据包含两行，第一行为整数 n，表示书的数量。

第二行为 n个整数，表示 1∼n的一种任意排列。同行数之间用空格隔开。

# 输出格式
每组数据输出一个最少操作次数。如果最少操作次数大于或等于 5
次，则输出 5 or more。每个结果占一行。

# 数据范围
$1≤n≤15$

# 思路
·如果我们用暴力的列举，我们要列举可能的区间长度 i 从 1-26，依次区间移动的位置 l-i 种。这只是每一次的更改，而我们可以最多做 5 次次更改，所以时间复杂度会很高
·对于 dfs 的优化，我们可以采用 A * 算法来计算。
·A* 算法在于找到对应的一定会小于实际操作数的理想操作数 f
·对于这一题我们发现，对于每一次操作，最多只会把 3 个序列顺序发生更改，所以理想操作数 f 就是总共的错误数/3 下取整。
·我们还可以在原来的基础上采用迭代加深的框架，以此来减少我们的 dfs 次数。
# AC 代码
```cpp
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 15;

int n;
int q[N], w[5][N];

int f()
{
    int res = 0;
    for (int i = 0; i + 1 < n; i ++ )
        if (q[i + 1] != q[i] + 1)
            res ++ ;
    return (res + 2) / 3;
}//我们统计的f函数

bool check()//检查是否已经有序
{
    for (int i = 0; i < n; i ++ )
        if (q[i] != i + 1)
            return false;
    return true;
}

bool dfs(int depth, int max_depth)//计算需要的深度，采用迭代加深框架
{
    if (depth + f() > max_depth) return false;
    if (check()) return true;

    for (int l = 0; l < n; l ++ )
        for (int r = l; r < n; r ++ )
            for (int k = r + 1; k < n; k ++ )
            {
                memcpy(w[depth], q, sizeof q);//储存前一刻的状态
                int x, y;
                for (x = r + 1, y = l; x <= k; x ++, y ++ ) q[y] = w[depth][x];
                for (x = l; x <= r; x ++, y ++ ) q[y] = w[depth][x];
                if (dfs(depth + 1, max_depth)) return true;
                memcpy(q, w[depth], sizeof q);//回复现场
            }
    return false;
}

int main()
{
    int T;
    scanf("%d", &T);
    while (T -- )
    {
        scanf("%d", &n);
        for (int i = 0; i < n; i ++ ) scanf("%d", &q[i]);

        int depth = 0;
        while (depth < 5 && !dfs(0, depth)) depth ++ ;
        if (depth >= 5) puts("5 or more");
        else printf("%d\n", depth);
    }

    return 0;
}
```
# 备注
