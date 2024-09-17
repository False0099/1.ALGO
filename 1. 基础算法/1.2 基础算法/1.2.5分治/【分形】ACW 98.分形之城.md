城市的规划在城市建设中是个大问题。

不幸的是，很多城市在开始建设的时候并没有很好的规划，城市规模扩大之后规划不合理的问题就开始显现。

而这座名为 Fractal 的城市设想了这样的一个规划方案，如下图所示：

![city.png](/media/article/image/2019/01/07/19_1ac25efe11-city.png)

当城区规模扩大之后，Fractal 的解决方案是把和原来城区结构一样的区域按照图中的方式建设在城市周围，提升城市的等级。

对于任意等级的城市，我们把正方形街区从左上角开始按照道路标号。

虽然这个方案很烂，Fractal 规划部门的人员还是想知道，如果城市发展到了等级 $N$，编号为 $A$ 和 $B$ 的两个街区的直线距离是多少。

街区的距离指的是街区的中心点之间的距离，每个街区都是边长为 $10$ 米的正方形。

#### 输入格式

第一行输入正整数 $n$，表示测试数据的数目。

以下 $n$ 行，输入 $n$ 组测试数据，每组一行。

每组数据包括三个整数 $N, A, B$，表示城市等级以及两个街区的编号，整数之间用空格隔开。

#### 输出格式

一共输出 $n$ 行数据，每行对应一组测试数据的输出结果，结果四舍五入到整数。

#### 数据范围

$1 \le N \le 31$,  
$1 \le A,B \le 2^{2N}$,  
$1 \le n \le 1000$

#### 输入样例：

```
3 
1 1 2 
2 16 1 
3 4 33
```

#### 输出样例：

```
10 
30 
50
```


## 题解
我们本题可以发现如果我们以我们的原来形状作为我们的图形 1，那么我们的图形二就是我们把图形一向上旋转，不变，向下开头，不变来组合形成的。
之后，我们用一个超级大的图来存储我们的每一个图形，显然，要求出我们 n 级图的个数，那么我们就要先直到我们 n-1 级图的个数，那么我们就有 cnt=1<<2*(n-1)。n 级图中的任意一个数字的编号为 m，令块的编号为 cnk，那么数字 m 所在块的编号是：cnt=m/cnt.

```cpp
#include <iostream>
#include <cmath>
#define x first
#define y second
using namespace std;
typedef long long LL;
typedef pair<LL, LL> PLL;

PLL calc(LL n, LL m) {
    if(n == 0) return {0, 0};
    LL len = 1ll << (n - 1); // n - 1级图构成n级图平移时的单位长度
    LL cnt = 1ll << (n - 1) * 2; // n - 1级图中所含的元素个数
    LL cnk = m / cnt; // 在n级图中，编号为m的元素所属块的编号
    LL idx = m % cnt; // 在n级图中，编号为m的元素在所属块中的编号
    PLL pos = calc(n - 1, idx); // 在n级图中，编号为m的元素在所属块中的坐标
    LL x = pos.x, y = pos.y;
    // 根据n级图中某个块的编号和这个块中某个元素的坐标，确定n - 1级图的坐标变换
    // 注意：离散坐标系跟实数坐标系有些许差别，不考虑这些差别
    // 结果必然是抓耳挠腮。hh
    if(cnk == 0) return {y, x}; // 没有平移，虽是旋转，坐标关系容易确定
    if(cnk == 1) return {x, y + len}; // 单纯平移
    if(cnk == 2) return {x + len, y + len}; // 单纯平移
    if(cnk == 3) return {len * 2 - y - 1, len - x - 1}; // 旋转又平移
}

LL rounding(double a) {
    LL b;
    if(a > 0) b = (a * 2 + 1) / 2;
    else b = (a * 2 - 1) / 2;  
    return b;
}

int main() {
    int times;
    cin >> times;
    while(times--) {
        LL n, a, b;
        cin >> n >> a >> b;
        PLL pa = calc(n, a - 1);
        PLL pb = calc(n, b - 1);
        //double x = pa.x - pb.x, y = pa.y - pb.y;
        //printf("%.0lf\n", sqrt(x * x + y * y) * 10.00);
        LL x = pa.x - pb.x, y = pa.y - pb.y;
        double dist = sqrt(x * x + y * y);
        cout << rounding(dist) << endl;
    }
    return 0;
}


```
