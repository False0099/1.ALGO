## 题目描述
直角坐标系中，一个机器人从任意点出发进行N次移动，每次向右移动dx，向上移动dy，最后会围成一个封闭图形，求该图形的内部和边上共有多少格点（横纵坐标都为整数的点），以及该图形的面积

## 输入格式
第一行times，其后有times组数据，每组数据第一行正整数N，其后N行，每行两个整数dx,dy


## 输出格式
每组数据在两行中输出，第一行字符串  
Scenario A:  
其中A代表数据序数，从1开始，第二行两个整数和一个保留一位小数的浮点数，分别代表内部和边上的格点数，以及图形面积，两组输出间有一个空行


## 样例 #1

### 样例输入 #1

```
2  
4  
1 0  
0 1  
-1 0  
0 -1  
7  
5 0  
1 3  
-2 2  
-1 0  
0 -3  
-3 1  
0 -3
```

### 样例输出 #1

```
Scenario #1:  
0 4 1.0
```

## 题解
这是一道pick定理的模版题，pick定理即在一个平面直角坐标系内，如果一个多边形的顶点都是格点，多边形的面积等于边界上的个点数的一般加上内部格点数再减去1，即$s=\frac{j}{2}+k-1$。


边界上的点，我们可以通过前面计算线段上的格点数量为模板进行计算，总的面积s我们可以用计算几何的方法计算，内部格点的数量，我们可以用pick定理计算。
## 代码
```cpp
#include<cstdio>
#include<cmath>
#pragma warning(disable:4996)
struct point { int x, y; };
const unsigned nmax = 101;
unsigned t, n; point p[nmax]; int dx, dy, A, E;
template<class _Ty> _Ty gcd(const _Ty& a, const _Ty& b) { return b == 0 ? a : gcd(b, a % b); }//a, b > 0
inline int area_2x(const point& a, const point& b) { return a.x * b.y - a.y * b.x; }
int main() {
	scanf("%u", &t);
	for (unsigned h = 1; h <= t; ++h) {
		scanf("%u", &n); E = 0; A = 0;
		for (unsigned i = 1; i <= n; ++i) {
			scanf("%d%d", &dx, &dy); p[i].x = p[i - 1].x + dx; p[i].y = p[i - 1].y + dy;
			E += gcd(abs(dx), abs(dy)); A += area_2x(p[i - 1], p[i]);
		}
		printf("Scenario #%u:\n%d %d %.1lf\n\n", h, (A - E + 2) / 2, E, A * 0.5);
	}
	return 0;
}

```