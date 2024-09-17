# 知识点
  ## [[区间DP]]
# 题目
 将一个 8×8的棋盘进行如下分割：将原棋盘割下一块矩形棋盘并使剩下部分矩形，再将剩下的部分继续如此分割，这样割了 (n−1)次后，连同最后剩下的矩形棋盘共有 n块矩形棋盘。(每次切割都只能沿着棋盘格子的边进行)



原棋盘上每一格有一个分值，一块矩形棋盘的总分为其所含各格分值之和。

现在需要把棋盘按上述规则分割成 n块矩形棋盘，并使各矩形棋盘总分的均方差最小。

均方差 formula. Png ，其中平均值 lala. Png ，xi为第 i块矩形棋盘的总分。

请编程对给出的棋盘及 n，求出均方差的最小值。

## 输入格式
第 1行为一个整数 n。

第 2 行至第 9行每行为 8个小于 100 的非负整数，表示棋盘上相应格子的分值。每行相邻两数之间用一个空格分隔。

## 输出格式
输出最小均方差值（四舍五入精确到小数点后三位）。

## 数据范围
1<n<15
## 输入样例 ：
3
1 1 1 1 1 1 1 3
1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 0
1 1 1 1 1 1 0 3
## 输出样例 ：
1.633

# 思路
·首先，原来要求的标准差不方便我们进行转移，我们换成更听话的方差来进行转移，转移的过程中，我们不难发现，对于每一个大块，我们有两大类切法，第一类是竖着切，第二类是横着切。每一次切分都会把矩阵分为两部分如下图所示。
![[Pasted image 20230520165736.png]]
·
![[Pasted image 20230520165751.png]]
·划分完毕后，我们只需要分别求出每一个区域内的方差，然后再比较就可以了。
# AC 代码
```cpp
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>

using namespace std;

const int N = 16;
int n, m = 8;
int s[N][N];
double f[N][N][N][N][N];
double X;

double get(int x1, int y1, int x2, int y2)  //求该矩阵的 n\sigma^2
{
    double delta = s[x2][y2] - s[x1 - 1][y2] - s[x2][y1 - 1] + s[x1 - 1][y1 - 1];
    delta = delta - X;//标准差
    return delta * delta;
}
double dp(int k, int x1, int y1, int x2, int y2)
{
	
    if (f[k][x1][y1][x2][y2] >= 0) return f[k][x1][y1][x2][y2]; //记忆化搜索
    if (k == n) return f[k][x1][y1][x2][y2] = get(x1, y1, x2, y2);  //更新初始状态

    double t = 1e9; //初始化为无穷大
    for (int i = x1; i < x2; i ++ ) //横着切
    {
        t = min(t, dp(k + 1, x1, y1, i, y2) + get(i + 1, y1, x2, y2));
        t = min(t, dp(k + 1, i + 1, y1, x2, y2) + get(x1, y1, i, y2));
    }
    for (int i = y1; i < y2; i ++ ) //竖着切
    {
        t = min(t, dp(k + 1, x1, y1, x2, i) + get(x1, i + 1, x2, y2));
        t = min(t, dp(k + 1, x1, i + 1, x2, y2) + get(x1, y1, x2, i));
    }
    return f[k][x1][y1][x2][y2] = t;
}
int main()
{
    //读入
    scanf("%d", &n);
    for (int i = 1; i <= m; i ++ )
        for (int j = 1; j <= m; j ++ )
            scanf("%d", &s[i][j]);
    //预处理前缀和
    for (int i = 1; i <= m; i ++ )
        for (int j = 1; j <= m; j ++ )
            s[i][j] += s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1];
    //初始化所有状态
    memset(f, -1, sizeof f);
    //计算均值X拔
    X = (double) s[m][m] / n;
    //记忆化搜索
    printf("%.3lf\n", sqrt(dp(1, 1, 1, m, m) / n));
    return 0;
}

作者：一只野生彩色铅笔
链接：https://www.acwing.com/solution/content/62836/
来源：AcWing
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
```
# 备注
