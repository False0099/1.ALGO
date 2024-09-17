Given an integer $r$, find the number of lattice points that have a Euclidean distance from $(0, 0)$ **greater than or equal to** $r$ but **strictly less** than $r+1$.

A lattice point is a point with integer coordinates. The Euclidean distance from $(0, 0)$ to the point $(x,y)$ is $\sqrt{x^2 + y^2}$.

**Input**

The first line contains a single integer $t$ ($1 \leq t \leq 1000$) — the number of test cases.

The only line of each test case contains a single integer $r$ ($1 \leq r \leq 10^5$).

The sum of $r$ over all test cases does not exceed $10^5$.

**Output**

For each test case, output a single integer — the number of lattice points that have an Euclidean distance $d$ from $(0, 0)$ such that $r \leq d \lt r+1$.

## 题解
本题，我们可以把我们的原来的条件转换为，求满足下面条件的 $(x,y)$,那么我们就有 $r^2\leq(x^2+y^2)\leq(r+1)^2-1$,我们考虑枚举我们的一个 $x$,然后再去求我们的另外的对应的 $y$ 的范围可以有多少个。

这个时候，我们的 $x$ 的范围显然是可以确定的，应该是我们的 $[0,r]$,那么这个时候，我们对应的 $y$ 的范围，在给定的 $x$ 的时候，应该也是唯一可以确定的，y 应该满足：$\sqrt{(r^2-x^2})\leq y\leq \sqrt{ (r+1)^2-1-x^2 }$

最后我们把我们算的的结果乘以四就是我们的最终答案。

```
```
#include <iostream>
using namespace std;
 
void solve()
{
    long long r;
    cin >> r;
    long long height = r;
    long long ans = 0;
    for(long long i = 0; i <= r; i++)
    {
        while(i*i+height*height >= (r+1)*(r+1))
        {
            height--;
        }
        long long cop = height;
        while(i*i+cop*cop >= r*r && cop > 0)
        {
            cop--;
            ans++;
        }
    }
    cout << ans*4 << endl;
}
 
int32_t main(){
    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
}
```
```