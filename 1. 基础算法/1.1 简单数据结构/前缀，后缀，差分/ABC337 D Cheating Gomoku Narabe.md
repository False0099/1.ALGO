### Problem Statement

There is a grid with $H$ rows and $W$ columns. Let $(i, j)$ denote the cell at the $i$ \-th row from the top and the $j$ \-th column from the left.

Each cell contains one of the characters `o`, `x`, and `.`. The characters written in each cell are represented by $H$ strings $S_1, S_2, \ldots, S_H$ of length $W$; the character written in cell $(i, j)$ is the $j$ \-th character of the string $S_i$.

For this grid, you may repeat the following operation any number of times, possibly zero:

-   Choose one cell with the character `.` and change the character in that cell to `o`.

Determine if it is possible to have a sequence of $K$ horizontally or vertically consecutive cells with `o` written in all cells (in other words, satisfy **at least one** of the following two conditions). If it is possible, print the minimum number of operations required to achieve this.

-   There is an integer pair $(i, j)$ satisfying $1 \leq i \leq H$ and $1 \leq j \leq W-K+1$ such that the characters in cells $(i, j), (i, j+1), \ldots, (i, j+K-1)$ are all `o`.
-   There is an integer pair $(i, j)$ satisfying $1 \leq i \leq H-K+1$ and $1 \leq j \leq W$ such that the characters in cells $(i, j), (i+1, j), \ldots, (i+K-1, j)$ are all `o`.

## 题解
我们这一题如果直接去做的话，不太方便我们进行计算，我们考虑把我们的问题进行转化，我们转化为在每一行和每一列上的问题。
我们在每一列上，就可以转化为求：我们的一个长度为 k 的的区间。要求
1. 我们这个区间内不能有 `x`
2. 我们这个区间内的 o 代价为 0，`.` 代价为 1
3. 要求我们的代价最小的一个区间

于是，我们就可以对于我们的每一行每一列都去维护一个前缀和，然后，我们每一次就可以 $o(1)$ 的查询我们的每一个区间。最后我们的时间复杂度就是我们的 $o(n)$

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn = 3e+5+100;
int n,m,K,ans=1e9;
int sum[maxn];
vector<char> a[maxn];
main(){
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin>>n>>m>>K;
	for(int i=1;i<=n;++i){
		a[i].resize(m+1);
		for(int j=1;j<=m;++j){
			cin>>a[i][j];
		}
	}
	for(int i=1;i<=n;++i){
		for(int j=1,la=0;j<=m;++j){
			if(a[i][j]=='.') sum[j]=sum[j-1]+1;
			else sum[j]=sum[j-1];
			if(a[i][j]=='x') la=j;
			if(la<=j-K) ans=min(ans,sum[j]-sum[j-K]);
		}
	}
	for(int j=1;j<=m;++j){
		for(int i=1,la=0;i<=n;++i){
			if(a[i][j]=='.') sum[i]=sum[i-1]+1;
			else sum[i]=sum[i-1];
			if(a[i][j]=='x') la=i;
			if(la<=i-K) ans=min(ans,sum[i]-sum[i-K]);
		}
	}
	if(ans==1e9) ans=-1;
	cout<<ans;
}
```