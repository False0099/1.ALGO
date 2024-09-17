# 知识点
  ## [[动态规划]] [[树形DP]] [[状态机]]
# 题目
 鲍勃喜欢玩电脑游戏，特别是战略游戏，但有时他找不到解决问题的方法，这让他很伤心。现在他有以下问题。他必须保护一座中世纪城市，这条城市的道路构成了一棵树。每个节点上的士兵可以观察到所有和这个点相连的边。他必须在节点上放置最少数量的士兵，以便他们可以*观察到所有的边*。你能帮助他吗？
#### 输入格式
输入包含多组测试数据，每组测试数据用以描述一棵树。

对于每组测试数据，第一行包含整数 $N$，表示树的节点数目。

接下来 $N$  行，每行按如下方法描述一个节点。

节点编号：(子节点数目) 子节点 子节点 …

节点编号从 $0$ 到 $N−1$ ，每个节点的子节点数量均不超过 $10$，每个边在输入数据中只出现一次。

#### 输出格式

对于每组测试数据，输出一个占据一行的结果，表示最少需要的士兵数。

#### 数据范围

$0<N≤1500$ ,  
一个测试点所有 $N$  相加之和不超过 $300650$。
# 思路
·本题与没有上司的舞会是一道相反的问题，都是同时需要用到树形 dp 和状态机的一道题目
· $f[i][j]表示以i为根节点，并且不选择第i点的情况下所能花费的最少代价$ 我们根据在某一点是否安排士兵来决定该点是 0 或者是 1 
·所以我们就能得出状态转移方程 $f[i][0]=\left( \sum  f[i.son][1]\right),f[i][1]=min\left( \sum min(f[i.son][0],f[i.son][1])\right)$
·意为如果我们选择了 i 点要在这一点不放士兵，那么就一定要在下面的子节点就一定要全选，否则就会有边看不见。如果在 i 点放了，那么下面的节点就可以选择防或是不放。
# AC 代码
```cpp
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 1510;

int n;
int h[N], e[N], ne[N], idx;
int f[N][2];
bool st[N];

void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++ ;
}

void dfs(int u)
{
    f[u][0] = 0, f[u][1] = 1;
    for (int i = h[u]; ~i; i = ne[i])
    {
        int j = e[i];
        dfs(j);
        f[u][0] += f[j][1];
        f[u][1] += min(f[j][0], f[j][1]);
    }
}

int main()
{
    while (cin >> n)
    {
        memset(h, -1, sizeof h);
        idx = 0;

        memset(st, 0, sizeof st);
        for (int i = 0; i < n; i ++ )
        {
            int id, cnt;
            scanf("%d:(%d)", &id, &cnt);
            while (cnt -- )
            {
                int ver;
                cin >> ver;
                add(id, ver);
                st[ver] = true;
            }
        }

        int root = 0;
        while (st[root]) root ++ ;
        dfs(root);

        printf("%d\n", min(f[root][0], f[root][1]));
    }

    return 0;
}

作者：yxc
链接：https://www.acwing.com/activity/content/code/content/125601/
来源：AcWing
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
```
# 备注
