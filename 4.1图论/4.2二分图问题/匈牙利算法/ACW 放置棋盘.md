# 知识点
  ## [[二分图]] [[二分图最大匹配]]
# 题目
 给定一个 N行 N列的棋盘，已知某些格子禁止放置。

求最多能往棋盘上放多少块的长度为 2、宽度为 1的骨牌，骨牌的边界与格线重合（骨牌占用两个格子），并且任意两张骨牌都不重叠。

# 输入格式
第一行包含两个整数 N和 t，其中 t为禁止放置的格子的数量。

接下来 t行每行包含两个整数 x和 y，表示位于第 x行第 y列的格子禁止放置，行列数从 1开始。

# 输出格式
输出一个整数，表示结果。

# 数据范围
1≤N≤100
,
0≤t≤100
# 输入样例 ：
8 0
# 输出样例 ：
32

# 思路
·这题的关键在于怎么构造一个图，以让我们可以正常计算
·把棋盘按1间隔染色 (横纵坐标值和为偶数染一种，奇数染另外一种），这样我们在每一个不同颜色之间的跳动都是可以认为是放进去了一个骨牌。之后我们的问题就可以转化为求二分图的最大匹配。
# AC 代码
```cpp
#include <cstring>
#include <iostream>
#include <algorithm>

#define x first
#define y second

using namespace std;

typedef pair<int, int> PII;

const int N = 110;

int n, m;
PII match[N][N];
bool g[N][N], st[N][N];
int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, 1, 0, -1};

bool find(int x, int y)
{
	//给定一个位置(x,y)，找他的四个方向
    for (int i = 0; i < 4; i ++ )
    {
        int a = x + dx[i], b = y + dy[i];
        if (a && a <= n && b && b <= n && !g[a][b] && !st[a][b])//如果这个方向合法而且没有被遍历过
        {
            st[a][b] = true;//标记已经被遍历过
            PII t = match[a][b];//找到这个点所对应的配对点
            if (t.x == -1 || find(t.x, t.y))//如果还没有配对，或者对应的配对点可以有新的配对
            {
                match[a][b] = {x, y};//我们直接配对
                return true;
            }
        }
    }

    return false;//没法配对我们就结束
}

int main()
{
    cin >> n >> m;

    while (m -- )
    {
        int x, y;
        cin >> x >> y;
        g[x][y] = true;//创建不可用点
    }

    memset(match, -1, sizeof match);

    int res = 0;
    for (int i = 1; i <= n; i ++ )
        for (int j = 1; j <= n; j ++ )
            if ((i + j) % 2 && !g[i][j])
            {
                memset(st, 0, sizeof st);
                if (find(i, j)) res ++ ;
            }

    cout << res << endl;

    return 0;
}


```
# 备注
