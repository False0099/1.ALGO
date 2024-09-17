现在，平面上有两条轨道，AB 和 CD，轨道上可以坐车，从 A 到 B 的速度是 P，而从 C 到 D 的速度是 Q，不在 AB 或 CD 上就只有步行了，速度是 R。现在问从 A 到 D 的最短时间

## Input

The first line is the case number T.  
For each case, there are three lines.  
The first line, four integers, the coordinates of A and B: Ax Ay Bx By.  
The second line , four integers, the coordinates of C and D:Cx Cy Dx Dy.  
The third line, three integers, P Q R.  
0 <= Ax，Ay，Bx，By，Cx，Cy，Dx，Dy <=1000  
1 <=P，Q，R<=10

## Output

The minimum time to travel from A to D, round to two decimals.

## Sample Input

1
0 0 0 100
100 0 100 100
2 2 1

## Sample Output

136.60

## 题解
对于这样一题，我们满足任意一条路径，都可以划分从 A 到 AB 上某点 E，从 E 到 CD 上某一点 F，再从 F 到 D。在这个条件下，我们的时间就可以通过 $t=\frac{|AE|}{p}+\frac{|ER|}{r}+\frac{FD}{q}$ 计算出来。这里相当于我们的**二元函数求极值**，并且我们二元函数的变量之间存在约束关系，而且我们**可以列出我们的公式**，因此，我们只需要枚举两个变量的可能取值即可。这里我们可以**在一个的情况下枚举这个条件下的最优**。理论上我们可以通过我们的拉格朗日乘数法解决。但这里，我们采用的是我们的三分法求极值。

```cpp
#include <bits\stdc++.h>

using namespace std;
typedef long long ll;
double eps = 1e-6;


int p, q, r;
int ax, ay, bx, by, cx, cy, dx, dy;

double min(double x, double y) {
    return x < y ? x : y;
}


double findCD(double ABx, double ABy) {
    double lx = cx;
    double ly = cy;
    double rx = dx;
    double ry = dy;
    double mid1x, mid1y, mid2x, mid2y;
    double time1 = 0, time2 = 0;
    do {
        mid1x = lx + (rx - lx) / 3;
        mid1y = ly + (ry - ly) / 3;
        mid2x = lx + 2 * (rx - lx) / 3;
        mid2y = ly + 2 * (ry - ly) / 3;
        time1 = sqrt((dx - mid1x) * (dx - mid1x) + (dy - mid1y) * (dy - mid1y)) / q +
                sqrt((ABx - mid1x) * (ABx - mid1x) + (ABy - mid1y) * (ABy - mid1y)) / r;
        time2 = sqrt((dx - mid2x) * (dx - mid2x) + (dy - mid2y) * (dy - mid2y)) / q +
                sqrt((ABx - mid2x) * (ABx - mid2x) + (ABy - mid2y) * (ABy - mid2y)) / r;

        if (time1 < time2) {
            rx = mid2x;
            ry = mid2y;
        } else {
            lx = mid1x;
            ly = mid1y;
        }
    } while (abs(time1 - time2) > eps);
    return time1;
}

//三分AB
double findAB() {
    double lx = ax;
    double ly = ay;
    double rx = bx;
    double ry = by;
    double mid1x, mid1y, mid2x, mid2y;
    double time1 = 0, time2 = 0;
    do {
        mid1x = lx + (rx - lx) / 3;
        mid1y = ly + (ry - ly) / 3;
        mid2x = lx + 2 * (rx - lx) / 3;
        mid2y = ly + 2 * (ry - ly) / 3;
        //三分CD
        time1 = sqrt((ax - mid1x) * (ax - mid1x) + (ay - mid1y) * (ay - mid1y)) / p + findCD(mid1x, mid1y);
        time2 = sqrt((ax - mid2x) * (ax - mid2x) + (ay - mid2y) * (ay - mid2y)) / p + findCD(mid2x, mid2y);
        if (time1 < time2) {
            rx = mid2x;
            ry = mid2y;
        } else {
            lx = mid1x;
            ly = mid1y;
        }
    } while (abs(time1 - time2) > eps);
    return time1;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        cin >> ax >> ay >> bx >> by >> cx >> cy >> dx >> dy;
        cin >> p >> q >> r;
        printf("%.2lf\n", findAB());
    }
    return 0;
}


```