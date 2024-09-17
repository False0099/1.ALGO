# 知识点
  ## [[树形DP]]
# 题目
 有一棵二叉苹果树，如果树枝有分叉，一定是分两叉，即没有只有一个儿子的节点。

这棵树共 N个节点，编号为 1至 N，树根编号一定为 1。

我们用一根树枝两端连接的节点编号描述一根树枝的位置。

一棵苹果树的树枝太多了，需要剪枝。但是一些树枝上长有苹果，给定需要保留的树枝数量，求最多能留住多少苹果。

这里的保留是指最终与 1 号点连通。

## 输入格式
第一行包含两个整数 N和 Q，分别表示树的节点数以及要保留的树枝数量。
接下来 N−1行描述树枝信息，每行三个整数，前两个是它连接的节点的编号，第三个数是这根树枝上苹果数量。

## 输出格式
输出仅一行，表示最多能留住的苹果的数量。

## 数据范围
1≤Q<N≤100
N≠1
每根树枝上苹果不超过 30000个。

## 输入样例 ：
5 2
1 3 1
1 4 10
2 3 20
3 5 20
## 输出样例 ：
21

# 思路
·这一题起源于我们原来的有以来的背包问题，但是我们这题是相对而言原本的价值被分配到了边上，而不是节点上。但是在确定树的跟节点后，边权与点权是可以相互转换的。我们还是选用体积分配方案，即给根节点的若干个节点分配体积，分配结束后我们再计算最大值。
·
·
# AC 代码
```cpp
#include <iostream>
#include <cstring>

using namespace std;

const int N = 110, M = N << 1;

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
        int ver = e[i];
        if (ver == father) continue;
        dfs(ver, u);
        for (int j = m; j >= 0; j -- )
            for (int k = 0; k <= j - 1; k ++ )  //枚举体积预留一条连向父节点的边
                f[u][j] = max(f[u][j], f[u][j - k - 1] + f[ver][k] + w[i]);
    }
}
int main()
{
    memset(h, -1, sizeof h);
    scanf("%d%d", &n, &m);
    for (int i = 1; i < n; i ++ )
    {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        add(a, b, c), add(b, a, c);
    }
    dfs(1, -1);
    printf("%d\n", f[1][m]);
    return 0;
}

作者：一只野生彩色铅笔
链接：https://www.acwing.com/solution/content/65600/
来源：AcWing
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
```
# 备注
