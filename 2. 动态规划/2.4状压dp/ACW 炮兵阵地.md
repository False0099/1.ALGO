# 知识点
  ## [[状态压缩DP]]
# 题目
 司令部的将军们打算在 N×M
 的网格地图上部署他们的炮兵部队。

一个 N×M的地图由 N行 M列组成，地图的每一格可能是山地（用 H 表示），也可能是平原（用 P 表示），如下图。

在每一格平原地形上最多可以布置一支炮兵部队（山地上不能够部署炮兵部队）；一支炮兵部队在地图上的攻击范围如图中黑色区域所示：

![[Pasted image 20230520113508.png]]

如果在地图中的灰色所标识的平原上部署一支炮兵部队，则图中的黑色的网格表示它能够攻击到的区域：沿横向左右各两格，沿纵向上下各两格。

图上其它白色网格均攻击不到。

从图上可见炮兵的攻击范围不受地形的影响。

现在，将军们规划如何部署炮兵部队，在防止误伤的前提下（保证任何两支炮兵部队之间不能互相攻击，即任何一支炮兵部队都不在其他支炮兵部队的攻击范围内），在整个地图区域内最多能够摆放多少我军的炮兵部队。

## 输入格式
第一行包含两个由空格分割开的正整数，分别表示 N和 M；

接下来的 N 行，每一行含有连续的 M 个字符 (P 或者 H)，中间没有空格。按顺序表示地图中每一行的数据。

## 输出格式
仅一行，包含一个整数 K，表示最多能摆放的炮兵部队的数量。

## 数据范围
N≤100, M≤10
## 输入样例 ：
5 4
PHPP
PPHH
PPPP
PHPP
PHHP
## 输出样例 ：
6

# 思路
***对于二层以上的状态压缩，我们要想办法找到限制条件，所以很显然，我们可以直接用两个维度来表示我们的限制条件即 
$f[i][j][k],表示在前i行已经摆完，且前一行状态为j，前两行状态为j时的所有可能的方案$

# AC 代码
```cpp
#include <iostream>
#include <vector>

using namespace std;

const int N = 110, M = 1 << 10;
int n, m;
int g[N], cnt[M];
int f[2][M][M];//使用滚动数组
vector<int> state;
vector<int> head[M];

bool check(int st)
{
    return !(st & st >> 1 || st & st >> 2);//判断合法
}
int count(int st)
{
    int res = 0;
    while (st) res += st & 1, st >>= 1;
    return res;
}
int main()
{
    //input
    cin >> n >> m;
    for (int i = 1, j = 0; i <= n; ++ i, j = 0)
        for (char c; j < m && cin >> c; ++ j)   //纯属为了压行,没有其他意思w
            g[i] += (c == 'H') << j;
    //找出所有合法状态
    for (int st = 0; st < 1 << m; ++ st)
        if (check(st))
            state.push_back(st), cnt[st] = count(st);
    //找出所有合法状态的合法转移
    for (int cur_st: state)
        for (int pre_st: state)
            if (!(cur_st & pre_st))
                head[cur_st].push_back(pre_st);
    //dp
    for (int i = 1; i <= n; ++ i)
        for (int st: state)
            if (!(g[i] & st))
                for (int p1: head[st])
                    for (int p2: head[p1])
                        if (!(st & p2))
                            f[i&1][st][p1] = max(f[i&1][st][p1], f[i-1&1][p1][p2] + cnt[st]);
    //Enumerate the final state
    int res = 0;
    for (int st: state)
        for (int pre: head[st])
            res = max(res, f[n&1][st][pre]);
    //output
    cout << res << endl;
    return 0;
}
```
# 备注
