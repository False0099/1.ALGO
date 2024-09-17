As the title says, the construction team encountered some technical problems.When a thin rod of length L is heated n degrees, it expands to a new length L'=(1+n* C) * L, where C is the coefficient of heat expansion.  

When a thin rod is mounted on two solid walls and then heated, it expands and takes the shape of a circular segment, the original rod being the chord of the segment.  
  
Your task is to compute the distance by which the center of the rod is displaced.  

## Input

The input contains multiple lines. Each line of input contains three non-negative numbers: the initial lenth of the rod in millimeters, the temperature change in degrees and the coefficient of heat expansion of the material. Input data guarantee that no rod expands by more than one half of its original length. The last line of input contains three negative numbers and it should not be processed.

## Output

For each line of input, output one line with the displacement of the center of the rod in millimeters with 3 digits of precision.  

## Sample Input

1000 100 0.0001
15000 10 0.00006
10 0 0.001
-1 -1 -1

## Sample Output

61.329
225.020
0.000

## 题解
![[Pasted image 20230914215850.png]]
总而言之，这是一道我们的二分问题，

```cpp
#include <iostream>
#include <queue>
#include <algorithm>
#include <cstdio>
#include <cmath>
using namespace std;
const int enf = 0x3f3f3f;
const int maxn = 50000 + 5;
const double esp = 1e-5;
int minn = enf,maxx = 0;
int d[maxn];
int dis[maxn];
double l, n, c;
double x, r, s;
int main() {
    while(cin >> l >> n >> c) {
        if(l == -1 && n == -1 && c == -1) return 0;
        else {
            double start = 0;
            double right = 0.50 * l;
            s = (1 + n * c) * l;
            double mid;
            while(right - start > esp) {
                mid = (start + right) / 2;
                r = (4 * mid * mid + l * l) / (8 * mid);
                if(s > 2 * r * asin(l / (2 * r)) ) start = mid;
                else right = mid;
 
            }
 
            printf("%.3f\n",mid);
        }
    }
    
    return 0;
}
```