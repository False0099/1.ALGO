## 题意
初始有 x 只羊 y 只狼，人要把羊运到河对岸，船最多运 p 只动物，当人不在的一岸的狼数量大于羊数量加 q，狼会吃羊。问最少运多少次可以把全部羊运到河对岸

## 题解
我们这一题关键在于我们 DP 状态的设置：我们人在哪一边，初始岸的狼的数量，达到这个状态的最少次数。由最少次数我们可以想到用 bfs 来转移。我们的转移如下：我们枚举每次运的动物数，枚举其中运多少只羊，离开的那一岸需要满足杨树为 0 或者杨树+q 大于狼数

```cpp
#include <cstring>
#include <array>
#include <queue>
#include <iostream>
using namespace std;
const int N = 103;
const int INF = 0x3f3f3f3f;
int d[2][N][N];
queue<array<int, 3>> qu;
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int x, y, p, q;
    cin >> x >> y >> p >> q;
    memset(d, 0x3f, sizeof(d));
    d[0][x][y] = 0;
    qu.push({0, x, y});
    while (!qu.empty())
    {
        auto [id, lx, ly] = qu.front();
        qu.pop();
        int rx = x - lx, ry = y - ly;
        for (int i = 0; i <= p; ++i)
        {
            for (int j = 0; j <= min(i, (id ? rx : lx)) && i - j <= (id ? ry : ly); ++j)
            {
                int shep = lx + (id ? j : -j), wolf = ly + (id ? i - j : j - i);
                int Oshep = rx + (id ? -j : j), Owolf = ry + (id ? j - i : i - j);
                if (id && (Oshep == 0 || Oshep + q >= Owolf) && d[id ^ 1][shep][wolf] > d[id][lx][ly] + 1)
                {
                    d[id ^ 1][shep][wolf] = d[id][lx][ly] + 1;
                    qu.push({id ^ 1, shep, wolf});
                }
                else if (!id && (shep == 0 || shep + q >= wolf) && d[id ^ 1][shep][wolf] > d[id][lx][ly] + 1)
                {
                    d[id ^ 1][shep][wolf] = d[id][lx][ly] + 1;
                    qu.push({id ^ 1, shep, wolf});
                }
            }
        }
    }
    int ans = INF;
    for (int i = 0; i <= y; ++i)
        ans = min(ans, d[1][0][i]);
    cout << (ans == INF ? -1 : ans);
    return 0;
}
```