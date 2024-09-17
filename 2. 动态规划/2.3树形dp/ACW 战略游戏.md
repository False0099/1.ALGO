# 知识点
  ## [[]]
# 题目
 鲍勃喜欢玩电脑游戏，特别是战略游戏，但有时他找不到解决问题的方法，这让他很伤心。

现在他有以下问题。

他必须保护一座中世纪城市，这条城市的道路构成了一棵树。

每个节点上的士兵可以观察到所有和这个点相连的边。

他必须在节点上放置最少数量的士兵，以便他们可以观察到所有的边。

你能帮助他吗？

例如，下面的树：



只需要放置 1 名士兵（在节点 1 处），就可观察到所有的边。

## 输入格式
输入包含多组测试数据，每组测试数据用以描述一棵树。

对于每组测试数据，第一行包含整数 N，表示树的节点数目。

接下来 N 行，每行按如下方法描述一个节点。

节点编号：(子节点数目) 子节点子节点 …

节点编号从 0 到 N−1，每个节点的子节点数量均不超过 10，每个边在输入数据中只出现一次。

## 输出格式
对于每组测试数据，输出一个占据一行的结果，表示最少需要的士兵数。

## 数据范围
0<N≤1500
,
一个测试点所有 N 相加之和不超过 300650。

## 输入样例 ：
4
0: (1) 1
1: (2) 2 3
2: (0)
3: (0)
5
3: (3) 1 4 2
1: (1) 0
2: (0)
0: (0)
4: (0)
## 输出样例 ：
1
2

# 思路
·我们看到这一题，首先会想到这是一道树上 dp 的题目，而且这还是一道树上状态机的题目，类似于没有上司的舞会，我们可以建立状态函数 $f[i][j]$ 表示第以 i 为根节点的字数被点亮的或是没有被点亮的，我们的转移方程也可以转换为
![[Pasted image 20230520224509.png]]
·
·
# AC 代码
```cpp
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 1510;

int n;
int h[N], e[N], ne[N], idx;
int f[N][2];
bool not_root[N];

void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++ ;
}
void dfs(int u)
{
    f[u][0] = 0, f[u][1] = 1;  //initialize
    for (int i = h[u]; ~i; i = ne[i])
    {
        int j = e[i];
        dfs(j);
        f[u][0] += f[j][1];//对边必须放
        f[u][1] += min(f[j][0], f[j][1]);//对边可放可不放
    }
}
int main()
{
    while (~scanf("%d", &n))
    {
        memset(h, -1, sizeof h); idx = 0;
        memset(not_root, 0, sizeof not_root);
        for (int i = 0; i < n; i ++ )
        {
            int a, b, siz;
            scanf("%d:(%d) ", &a, &siz);
            while (siz -- )
            {
                scanf("%d", &b);
                add(a, b);
                not_root[b] = true;
            }
        }
        int root = 0;
        while (not_root[root]) root ++ ;
        dfs(root);
        printf("%d\n", min(f[root][0], f[root][1]));
    }
    return 0;
}
```
# 备注
