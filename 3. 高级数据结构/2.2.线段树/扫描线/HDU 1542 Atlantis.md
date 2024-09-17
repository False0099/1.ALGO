There are several ancient Greek texts that contain descriptions of the fabled island Atlantis. Some of these texts even include maps of parts of the island. But unfortunately, these maps describe different regions of Atlantis. Your friend Bill has to know the total area for which maps exist. You (unwisely) volunteered to write a program that calculates this quantity.  

Input

The input file consists of several test cases. Each test case starts with a line containing a single integer n (1<=n<=100) of available maps. The n following lines describe one map each. Each of these lines contains four numbers x1;y1;x2;y2 (0<=x1<x2<=100000;0<=y1<y2<=100000), not necessarily integers. The values (x1; y1) and (x2;y2) are the coordinates of the top-left resp. bottom-right corner of the mapped area.  
  
The input file is terminated by a line containing a single 0. Don’t process it.

Output

For each test case, your program should output one section. The first line of each section must be “Test case k”, where k is the number of the test case (starting with 1). The second one must be “Total explored area: a”, where a is the total explored area (i.e. the area of the union of all rectangles in this test case), printed exact to two digits to the right of the decimal point.  
  
Output a blank line after each test case.  

Sample

|Inputcopy|Outputcopy|
|---|---|
|2<br>10 10 20 20<br>15 15 25 25.5<br>0|Test case #1 <br>Total explored area: 180.00|

## 题解
我们给定 n 个矩形，求他们的并面积，我们这一题就需要用到我们的扫描线算法，类似于积分的思想。我们首先用扫描线按矩形的水平边分段，如上图。在同一段的面积一起计算，即同一种颜色。

我们从下往上扫描，对于每一段的高，即为两个相邻的水平边之间的垂直距离。而对于每一段的宽，就是多个矩形的实际覆盖距离，这一部分用线段树的区间覆盖来维护。

如果扫到的这条边是某条矩形的下边，则往区间插入这条线段。

如果扫到的这条边是某条举行的上边，则往区间删除这条线段。

就可以得到当前的那一段的实际覆盖距离。

将每一段小面积相加即为结果

![[无标题 11.png]]

其中我们的线段树维护我们从 0-最高位置哪些位置**出现过**，我们的每一次计算就是拿我们的**右边减左边再去乘上我们的长度**。我们如果遇到了右边界，我们就减去我们对应位置的长度

```cpp
#include <cstdio>
#include <cstring>
#include <vector>
#include <iostream>
#include <algorithm>
 
using namespace std;
const int maxn = 205;
 
#define lson(x) (x<<1)
#define rson(x) ((x<<1) | 1)
 
struct Node {
 
    int l, r, add;
    double s;
    void set (int l, int r, double s, int add) {
 
        this->l = l;
        this->r = r;
        this->s = s;
        this->add = add;
    }
}node[4 * maxn];
 
struct Line {
 
    double x, y1, y2;
    int flag;
    Line (double x, double y1, double y2, int flag) {
 
        this->x = x;
        this->y1 = y1;
        this->y2 = y2;
        this->flag = flag;
    }
 
    bool operator < (const Line &l) const {
 
        return x < l.x;   
    }
};
 
int n;
vector<Line> L;
vector<double> pos;
 
void pushup(int u) {
 
    if (node[u].add) 
        node[u].s = pos[node[u].r + 1] - pos[node[u].l];
    else if (node[u].l == node[u].r)
        node[u].s = 0;
    else
        node[u].s = node[lson(u)].s + node[rson(u)].s;
}
 
void build (int u, int l, int r) {
 
    node[u].set (l, r, 0, 0);
    if (l == r)
        return;
    int m = (l + r)>>1;
    build(lson(u), l, m);
    build(rson(u), m + 1, r);
}
 
void update (int u, int l, int r, int v) {
 
    if (node[u].l >= l && node[u].r <= r) {
        node[u].add += v;
        pushup(u);
        return;
    }
 
    int m = (node[u].l + node[u].r)>>1;
    if (l <= m)
        update (lson(u), l, r, v);
    if (r > m)
        update (rson(u), l, r, v);
    pushup(u);
}
 
void init () {
 
    pos.clear();
    L.clear();
    double x1, y1, x2, y2;
 
    for (int i = 0; i < n; i++) {
        scanf ("%lf%lf%lf%lf", &x1, &y1, &x2, &y2);
        pos.push_back(y1);
        pos.push_back(y2);
        L.push_back(Line(x1, y1, y2, 1));
        L.push_back(Line(x2, y1, y2, -1));
    }
 
    sort (pos.begin(), pos.end());
    sort (L.begin(), L.end());
    pos.erase(unique(pos.begin(), pos.end()), pos.end());
 
    build(1, 0, (int)pos.size() - 1);
}
 
double solve() {
 
    init();
    double ans = 0;
    for (int i = 0; i < (int)L.size() - 1; i++) {
 
        int l = lower_bound(pos.begin(), pos.end(), L[i].y1) - pos.begin();
        int r = lower_bound(pos.begin(), pos.end(), L[i].y2) - pos.begin();
        update (1, l, r - 1, L[i].flag);
//        printf ("%.2lf\n", node[1].s);
        ans += node[1].s * (L[i + 1].x - L[i].x);    
    }
    return ans;
}
 
int main () {
 
    int T = 0;
    double x1, y1, x2, y2;
    while (scanf ("%d", &n) && n) {
 
        printf ("Test case #%d\n", ++T);
        printf ("Total explored area: %.2lf\n\n", solve());
    }
    return 0;
}
```