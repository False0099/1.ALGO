#01背包 #特殊限制 #复杂过程 #方案
# 题目
一天，小智和皮卡丘来到了小精灵狩猎场，里面有很多珍贵的野生宠物小精灵。

小智也想收服其中的一些小精灵。

然而，野生的小精灵并不那么容易被收服。

对于每一个野生小精灵而言，小智可能需要使用很多个精灵球才能收服它，而在收服过程中，野生小精灵也会对皮卡丘造成一定的伤害（从而减少皮卡丘的体力）。

当皮卡丘的体力小于等于 0 时，小智就必须结束狩猎（因为他需要给皮卡丘疗伤），而使得皮卡丘体力小于等于 0 的野生小精灵也不会被小智收服。

当小智的精灵球用完时，狩猎也宣告结束。

我们假设小智遇到野生小精灵时有两个选择：收服它，或者离开它。

如果小智选择了收服，那么一定会扔出能够收服该小精灵的精灵球，而皮卡丘也一定会受到相应的伤害；如果选择离开它，那么小智不会损失精灵球，皮卡丘也不会损失体力。

小智的目标有两个：主要目标是收服尽可能多的野生小精灵；如果可以收服的小精灵数量一样，小智希望皮卡丘受到的伤害越小（剩余体力越大），因为他们还要继续冒险。

现在已知小智的精灵球数量和皮卡丘的初始体力，已知每一个小精灵需要的用于收服的精灵球数目和它在被收服过程中会对皮卡丘造成的伤害数目。

请问，小智该如何选择收服哪些小精灵以达到他的目标呢？

## 输入格式
输入数据的第一行包含三个整数：N，M，K，分别代表小智的精灵球数量、皮卡丘初始的体力值、野生小精灵的数量。

之后的 K 行，每一行代表一个野生小精灵，包括两个整数：收服该小精灵需要的精灵球的数量，以及收服过程中对皮卡丘造成的伤害。

## 输出格式
输出为一行，包含两个整数：C，R，分别表示最多收服 C 个小精灵，以及收服 C 个小精灵时皮卡丘的剩余体力值最多为 R。

## 数据范围
0<N≤1000
,
0<M≤500
,
0<K≤100
## 输入样例 1：
10 100 5
7 10
2 40
2 50
1 20
4 20
## 输出样例 1：
3 30
## 输入样例 2：
10 100 5
8 110
12 10
20 10
5 200
1 110
## 输出样例2 ：
0 100

# 思路
***首先，由于先前的决策不会影响我们的后面的决策，我们认为这一题是可以使用动态规划算法的。

**此次，我们观察这一题的条件，我们能发现，当中有两个约束条件，一个是我们的精灵球总数，一个是我们的皮卡丘的血量，这时我们就要开一个二维背包去解决我们的问题。最后我们需要输出精灵的数量，以及我们最后剩余的体力值的最大值。

*注意到，我们这一题中，精灵的数目和体力值是等价值的，所以我们即可以以体力，精灵球算费用，精灵数位价值。也可以以体力、精灵数位费用，精灵球数位价值。

# AC 代码
```cpp
#include <cstdio>
#include <iostream>
#include <cstring>
using namespace std;
const int N = 1005, M = 505, S = 105;
int n, m, K, w[S], v[S], f[N][M];
int main() {
    memset(f, 0xcf, sizeof f);
    scanf("%d%d%d", &n, &m, &K);
    for(int i = 1; i <= K; i++)
        scanf("%d%d", w + i, v + i);

    f[0][0] = 0;
    for(int i = 1; i <= K; i++) {
        for(int j = n; j >= w[i]; j--) 
            for(int k = m; k >= v[i]; k--)
                f[j][k] = max(f[j][k], f[j - w[i]][k - v[i]] + 1);
    }
    int res = -1, t;
    for(int j = 0; j <= n; j++) {
        for(int k = 0; k < m; k++) {
            if(f[j][k] > res || (res == f[j][k] && k < t)) {
                res = f[j][k], t = k;
            }
        }
    }
    printf("%d %d\n", res, m - t);
    return 0;
}
```
# 备注
