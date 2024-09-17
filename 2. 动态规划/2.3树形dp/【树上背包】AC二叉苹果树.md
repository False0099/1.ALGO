# 知识点
  ## [[动态规划]] [[树形DP]]
# 题目
 有一棵二叉苹果树，如果树枝有分叉，一定是分两叉，即没有只有一个儿子的节点。

这棵树共 $N$ 个节点，编号为 $1$ 至 $N$ ，树根编号一定为 $1$。

我们用一根树枝两端连接的节点编号描述一根树枝的位置。

一棵苹果树的树枝太多了，需要剪枝。但是一些树枝上长有苹果，给定需要保留的树枝数量，求最多能留住多少苹果。

这里的保留是指最终与1号点连通。

#### 输入格式

第一行包含两个整数 $N$ 和 $Q$ ，分别表示树的节点数以及要保留的树枝数量。

接下来 $N−1$ 行描述树枝信息，每行三个整数，前两个是它连接的节点的编号，第三个数是这根树枝上苹果数量。

#### 输出格式

输出仅一行，表示最多能留住的苹果的数量。

#### 数据范围

$1≤Q<N≤1001$ .  
$N≠1$  
每根树枝上苹果不超过 $30000$ 个。

#### 输入样例：

```
5 2
1 3 1
1 4 10
2 3 20
3 5 20
```

#### 输出样例：

```
21
```

# 思路
·这一题就是典型的树上背包问题，而树上背包问题又可以被扩展为分组背包问题。
·我们从根节点开始，将总共的背包容量为 j，每一个子节点视为一个分组，现在要找一种取法，使得找到的所有子节点之和加起来是最大的，我们可以依此列出一个状态表示 $f[i][j],表示在以i为根节点的树上，总共容量为j的最大的价值$
·状态转移
$f[i][j]=max(f[i][j],f[i][j-k+1]+f[i.son][k]+w[i])$
$f[i][j-k+1]+f[i.son][k]+w[i]$   意思为给子节点 son 分配了 k 个任务，自己手上留着 j-k-1个任务等着分配给下一个研究生
# AC 代码
```cpp
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 110, M = N * 2;

int n, m;
int h[N], e[M], w[M], ne[M], idx;
int f[N][N];

void add(int a, int b, int c)
{
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++ ;
}

void dfs(int u, int father)
{
    for (int i = h[u]; ~i; i = ne[i])
    {
        if (e[i] == father) continue;
        dfs(e[i], u);
        for (int j = m; j; j -- )
            for (int k = 0; k + 1 <= j; k ++ )
                f[u][j] = max(f[u][j], f[u][j - k - 1] + f[e[i]][k] + w[i]);
    }
}

int main()
{
    cin >> n >> m;
    memset(h, -1, sizeof h);
    for (int i = 0; i < n - 1; i ++ )
    {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        add(a, b, c), add(b, a, c);
    }

    dfs(1, -1);

    printf("%d\n", f[1][m]);

    return 0;
}

作者：yxc
链接：https://www.acwing.com/activity/content/code/content/125602/
来源：AcWing
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
```
# 备注
