## 题目
Elena has a grid formed by $n$ horizontal lines and $m$ vertical lines. The horizontal lines are numbered by integers from $1$ to $n$ from top to bottom. The vertical lines are numbered by integers from $1$ to $m$ from left to right. For each $x$ and $y$ ($1 \leq x \leq n$, $1 \leq y \leq m$), the notation $(x, y)$ denotes the point at the intersection of the $x$ \-th horizontal line and $y$ \-th vertical line.

Two points $(x_1,y_1)$ and $(x_2,y_2)$ are adjacent if and only if $|x_1-x_2| + |y_1-y_2| = 1$.

![](https://espresso.codeforces.com/a930deff1273e6bdef85497667fad84a2fbc98be.png) The grid formed by $n=4$ horizontal lines and $m=5$ vertical lines.

Elena calls a sequence of points $p_1, p_2, \ldots, p_g$ of length $g$ a walk if and only if all the following conditions hold:

-   The first point $p_1$ in this sequence is $(1, 1)$.
-   The last point $p_g$ in this sequence is $(n, m)$.
-   For each $1 \le i \lt g$, the points $p_i$ and $p_{i+1}$ are adjacent.

Note that the walk may contain the same point more than once. In particular, it may contain point $(1, 1)$ or $(n, m)$ multiple times.

There are $n(m-1)+(n-1)m$ segments connecting the adjacent points in Elena's grid. Elena wants to color each of these segments in blue or red color so that there exists a walk $p_1, p_2, \ldots, p_{k+1}$ of length $k+1$ such that

-   out of $k$ segments connecting two consecutive points in this walk, no two consecutive segments have the same color (in other words, for each $1 \le i &lt; k$, the color of the segment between points $p_i$ and $p_{i+1}$ differs from the color of the segment between points $p_{i+1}$ and $p_{i+2}$).

Please find any such coloring or report that there is no such coloring.

## 输入
**Input**

Each test contains multiple test cases. The first line contains the number of test cases $t$ ($1 \leq t \leq 32$). The description of test cases follows.

The only line of each test case contains three integers $n$, $m$, and $k$ ($3 \leq n,m \leq 16$, $1 \leq k \leq 10^9$) — the dimensions of the grid and the number of segments in the walk Elena is looking for.

## 输出
**Output**

For each test case, output "NO" if it is not possible to color each of the $n(m-1)+(n-1)m$ segments in blue or red color, so that there exists a walk of length $k+1$ satisfying the condition from the statement.

Otherwise, output in the first line "YES", and then provide the required coloring.

In each of the first $n$ lines of coloring description, output $m-1$ space-separated characters. The $j$ \-th character in the $i$ \-th of these $n$ lines should denote the color of the segment between points $(i,j)$ and $(i,j+1)$. Here, use 'B' to denote the blue color and 'R' to denote the red color.

In each of the next $n-1$ lines of coloring description, output $m$ space-separated characters. The $j$ \-th character in the $i$ \-th of these $n-1$ lines should denote the color of the segment between points $(i,j)$ and $(i+1,j)$. Similarly, use 'B' to denote the blue color and 'R' to denote the red color.

You can output each letter in the answer in any case (upper or lower). For example, the strings "yEs", "yes", "Yes", and "YES" will be recognized as positive responses, and both 'R' and 'r' are valid notation of red.

## 题解
我们可以发现，我们如果到最后点的距离 $k$,是我们的 $k-mindist$ 如果上面的这一个数是一个奇数，那么我们一定不能到达我们的目的地，否则，我们可以通过在起点绕小圈（+2）弯，在末尾绕大圈（+4），来实现我们的最后的路径。![[Pasted image 20231120143635.png]]

```cpp
#include<bits/stdc++.h>
#define rep(i,x,y) for(int i=x; i<=y; ++i)
#define repd(i,x,y) for(int i=x; i>=y; --i)

using namespace std;
typedef long long LL;
const int N=20;
int n,m,k;
int ans1[N][N],ans2[N][N];

void solve()
{
	scanf("%d%d%d",&n,&m,&k);
	if(k<n-1+m-1 || (n-1+m-1-k)&1) return puts("NO"),void();
	ans1[n-1][m-1]=0;
	ans1[n][m-1]=0;
	ans2[n-1][m-1]=1;
	ans2[n-1][m]=1;
	int tp=1;
	repd(i,n-2,1) ans2[i][m]=tp,tp^=1;
	repd(i,m-1,1) ans1[1][i]=tp,tp^=1;
	tp=1;
	repd(i,m-2,1) ans1[n-1][i]=tp,tp^=1;
	repd(i,n-2,1) ans2[i][1]=tp,tp^=1;
	puts("YES");
	rep(i,1,n)
	{
		rep(j,1,m-1)
		{
			if(ans1[i][j]) putchar('R'); else putchar('B');
			putchar(' ');
		}
		puts("");
	}
	rep(i,1,n-1)
	{
		rep(j,1,m)
		{
			if(ans2[i][j]) putchar('R'); else putchar('B');
			putchar(' ');
		}
		puts("");
	}
}	

int main()
{
	int t;
	scanf("%d",&t);
	while(t--) solve();
	return 0;
}
```