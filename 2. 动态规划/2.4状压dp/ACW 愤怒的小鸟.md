# 知识点
  ## [[状态压缩DP]] [[记忆化搜索]]
# 题目
 Kiana 最近沉迷于一款神奇的游戏无法自拔。简单来说，这款游戏是在一个平面上进行的。 

有一架弹弓位于 (0,0) 处，每次 Kiana 可以用它向第一象限发射一只红色的小鸟，小鸟们的飞行轨迹均为形如 y=ax 2+bx 的曲线，其中 a, b是 Kiana 指定的参数，且必须满足 a<0。

当小鸟落回地面（即 x轴）时，它就会瞬间消失。

在游戏的某个关卡里，平面的第一象限中有 n只绿色的小猪，其中第 i只小猪所在的坐标为 (xi, yi)。 

如果某只小鸟的飞行轨迹经过了 (xi, yi)，那么第 i只小猪就会被消灭掉，同时小鸟将会沿着原先的轨迹继续飞行； 

如果一只小鸟的飞行轨迹没有经过 (xi, yi)，那么这只小鸟飞行的全过程就不会对第 i只小猪产生任何影响。 

例如，若两只小猪分别位于 (1,3)和 (3,3)，Kiana 可以选择发射一只飞行轨迹为 y=−x^2+4 x 的小鸟，这样两只小猪就会被这只小鸟一起消灭。 

而这个游戏的目的，就是通过发射小鸟消灭所有的小猪。 

这款神奇游戏的每个关卡对 Kiana 来说都很难，所以 Kiana 还输入了一些神秘的指令，使得自己能更轻松地完成这个这个游戏。   

这些指令将在输入格式中详述。 

假设这款游戏一共有 T 个关卡，现在 Kiana 想知道，对于每一个关卡，至少需要发射多少只小鸟才能消灭所有的小猪。  

由于她不会算，所以希望由你告诉她。

注意: 本题除 NOIP 原数据外，还包含加强数据。

## 输入格式
第一行包含一个正整数 T，表示游戏的关卡总数。

下面依次输入这 T个关卡的信息。

每个关卡第一行包含两个非负整数 n, m，分别表示该关卡中的小猪数量和 Kiana 输入的神秘指令类型。

接下来的 n行中，第 i行包含两个正实数 (xi, yi)，表示第 i 只小猪坐标为 (xi, yi)，数据保证同一个关卡中不存在两只坐标完全相同的小猪。

如果 m=0，表示 Kiana 输入了一个没有任何作用的指令。

如果 m=1，则这个关卡将会满足：至多用 ⌈n/3+1⌉只小鸟即可消灭所有小猪。

如果 m=2，则这个关卡将会满足：一定存在一种最优解，其中有一只小鸟消灭了至少 ⌊n/3⌋只小猪。

保证 1≤n≤18，0≤m≤2，0<xi, yi<10，输入中的实数均保留到小数点后两位。

上文中，符号 ⌈c⌉ 和 ⌊c⌋ 分别表示对 c 向上取整和向下取整，例如 ：⌈2.1⌉=⌈2.9⌉=⌈3.0⌉=⌊3.0⌋=⌊3.1⌋=⌊3.9⌋=3。

## 输出格式
对每个关卡依次输出一行答案。

输出的每一行包含一个正整数，表示相应的关卡中，消灭所有小猪最少需要的小鸟数量。


# 思路
***我们先考虑构造出所有的抛物线，并处理出所有能没抛物线覆盖的点，那么我们 $path[i][j]储存的是经过i，j的所有抛物线所能到达的点的集合。$ 我们可以理解为 path 储存了抛物线所能经过的每一个点，而抛物线的确定方法又是由两点确定的。


# AC 代码
```cpp
#include <iostream>
#include <cstring>
#include <cmath>

#define x first
#define y second

using namespace std;

typedef pair<double, double> PDD;

const int N = 20, M = 1 << N;
const double eps = 1e-8;

int n, m;
PDD ver[N];
int path[N][N];
int f[M];//存储在M状态下的点被完全覆盖所需要的抛物线个数

int cmp_lf(double a, double b)  //浮点数比较
{
    if (fabs(a - b) < eps) return 0;
    if (a > b) return 1;
    return -1;
}
void init_path()    //预处理所有的抛物线
{
    memset(path, 0, sizeof path);
    for (int i = 0; i < n; ++ i)
    {
        path[i][i] = 1 << i;    //单独生成一条只经过(0,0)和(x,y)的抛物线
        for (int j = 0; j < n; ++ j)
        {
            double x1 = ver[i].x, y1 = ver[i].y;
            double x2 = ver[j].x, y2 = ver[j].y;
            if (!cmp_lf(x1, x2)) continue;  //单独一个点无法生成参数a,b的抛物线
            double a = (y1 / x1 - y2 / x2) / (x1 - x2);
            double b = (y1 / x1) - a * x1;
            if (cmp_lf(a, 0.0) >= 0) continue;  //a < 0
            //参数a,b的抛物线已生成，枚举他经过的所有点
            for (int k = 0; k < n; ++ k)
            {
                double x = ver[k].x, y = ver[k].y;
                if (!cmp_lf(y, a * x * x + b * x)) path[i][j] += 1 << k;
            }
        }
    }
}
//预处理所有抛物线
void solve()
{
    //input
    cin >> n >> m;
    for (int i = 0; i < n; ++ i) cin >> ver[i].x >> ver[i].y;
    //prework
    init_path();
    //dp
    memset(f, 0x3f, sizeof f);
    f[0] = 0;
    for (int cur_st = 0; cur_st + 1 < 1 << n; ++ cur_st)//枚举状态
    {
        int t = -1;
        for (int i = 0; i < n; ++ i)//枚举抛物线的一端，
            if (!(cur_st >> i & 1))//如果这个点是没有被覆盖过的
                t = i;//我们再去取这一个点
        for (int i = 0; i < n; ++ i)//枚举抛物线的另一端
        {
            int ne_st = path[t][i] | cur_st;//被抛物线覆盖后的状态变化。
            f[ne_st] = min(f[ne_st], f[cur_st] + 1);
        }
    }
    cout << f[(1 << n) - 1] << endl;
}
int main()
{
    int T = 1; cin >> T;
    while (T -- ) solve();
    return 0;
}

作者：一只野生彩色铅笔
链接：https://www.acwing.com/solution/content/58284/
来源：AcWing
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
```
# 备注
