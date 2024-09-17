After a day trip with his friend Dick, Harry noticed a strange pattern of tiny holes in the door of his SUV. The local American Tire store sells fiberglass patching material only in square sheets. What is the smallest patch that Harry needs to fix his door?

Assume that the holes are points on the integer lattice in the plane. Your job is to find the area of the smallest square that will cover all the holes.

## Input

The first line of input contains a single integer _T_ expressed in decimal with no leading zeroes, denoting the number of test cases to follow. The subsequent lines of input describe the test cases.

Each test case begins with a single line, containing a single integer _n_ expressed in decimal with no leading zeroes, the number of points to follow; each of the following _n_ lines contains two integers _x_ and _y_, both expressed in decimal with no leading zeroes, giving the coordinates of one of your points.

You are guaranteed that _T_ ≤ 30 and that no data set contains more than 30 points. All points in each data set will be no more than 500 units away from (0,0).

## Output

Print, on a single line with two decimal places of precision, the area of the smallest square containing all of your points.

## Sample

|Inputcopy|Outputcopy|
|---|---|
|2<br>4<br>-1 -1<br>1 -1<br>1 1<br>-1 1<br>4<br>10 1<br>10 -1<br>-10 1<br>-10 -1|4.00<br>242.00|


## 题解
本题要求我们对于给定的一些随机的点点，找到一个最小的能覆盖这 n 个点的矩形。

加入我们的正方形长宽都与坐标轴平行，那么我们只需要找到最左下角的那个点和最右上角的那个点即可。但是，我们还要考虑旋转的形况，我们考虑**旋转坐标轴**，即 $x'=x\cos a-y\sin a,y'=y\cos a-x\sin a$，这也就是我们旋转坐标轴的形况了。

那么现在，我们就等价于，对于每一个旋转角度 $\alpha$,求出在这个旋转角度下，我们的最大正方形矩形。并且对所有的最大正方形矩形，求出我们的 min。

我们的 n 个点，相当于我们的 n 个不同取值，我们每一个角度的函数就是这个不同取值的最大值减最小值。因此，我们有：

在这里，因为我们的参数至于我们的 $\alpha$ 有关，也就比较**类似于我们的二次函数最大值的最小值问题**。我们就可以采用我们类似于哪一题的做法。只需要把**题目中的二次函数替换为我们现在这里的新函数**。




```cpp
31 const double PI = acos(-1);
32 const double EPS = 1e-12;
33 double x[50], y[50];
34 int n;
35 
36 double calc(double a) {
37     double minx = 1e20, miny = 1e20, maxx = -1e20, maxy = -1e20;
38     rep(i, 0, n) {
39         double xx = x[i] * cos(a) - y[i] * sin(a);
40         double yy = x[i] * sin(a) + y[i] * cos(a);
41         minx = min(minx, xx);
42         maxx = max(maxx, xx);
43         miny = min(miny, yy);
44         maxy = max(maxy, yy);
45     }
46     return max(maxx - minx, maxy - miny);
47 }
48 
49 int main() {
50     int T;
51     cin >> T;
52     while (T--) {
53         cin >> n;
54         rep(i, 0, n) cin >> x[i] >> y[i];
55         double l = 0, r = PI, ans;
56         while (r - l > EPS) {//枚举我们的角度
57             double m = (l + r) / 2;
58             double mm = (m + r) / 2;
59             ans = calc(m);
60             if (ans <= calc(mm)) r = mm;
61             else l = m;
62         }
63         printf("%.2f\n", ans*ans);
64     }
65     return 0;
66 }
```