### Problem Statement

There is a grid with $N$ rows and $N$ columns. Let $(i,j)$ denote the square at the $i$ \-th row from the top and $j$ \-th column from the left.

Takahashi is initially at square $(1,1)$ with zero money.

When Takahashi is at square $(i,j)$, he can perform one of the following in one **action**:

-   Stay at the same square and increase his money by $P_{i,j}$.
-   Pay $R_{i,j}$ from his money and move to square $(i,j+1)$.
-   Pay $D_{i,j}$ from his money and move to square $(i+1,j)$.

He cannot make a move that would make his money negative or take him outside the grid.

If Takahashi acts optimally, how many actions does he need to reach square $(N,N)$?


### Constraints

-   $2 \leq N \leq 80$
-   $1 \leq P_{i,j} \leq 10^9$
-   $1 \leq R_{i,j},D_{i,j} \leq 10^9$
-   All input values are integers.

### Input

The input is given from Standard Input in the following format:


N
P_{1,1}$ $\ldots$ $P_{1,N}$
$\vdots$ 
$P_{N,1}$ $\ldots$ $P_{N,N}$
$R_{1,1}$ $\ldots$ $R_{1,N-1}$
$\vdots$
$R_{N,1}$ $\ldots$ $R_{N,N-1}$
$D_{1,1}$ $\ldots$ $D_{1,N}$
$\vdots$
$D_{N-1,1}$ $\ldots$ $D_{N-1,N}$


### Output

Print the answer.

### Sample Input 1

```
3
1 2 3
3 1 2
2 1 1
1 2
4 3
4 2
1 5 7
5 3 3
```

### Sample Output 1

```
8
```

![[Pasted image 20240310143629.png]]

It is possible to reach square $(3,3)$ in eight actions as follows:

-   Stay at square $(1,1)$ and increase money by $1$. His money is now $1$.
-   Pay $1$ money and move to square $(2,1)$. His money is now $0$.
-   Stay at square $(2,1)$ and increase money by $3$. His money is now $3$.
-   Stay at square $(2,1)$ and increase money by $3$. His money is now $6$.
-   Stay at square $(2,1)$ and increase money by $3$. His money is now $9$.
-   Pay $4$ money and move to square $(2,2)$. His money is now $5$.
-   Pay $3$ money and move to square $(3,2)$. His money is now $2$.
-   Pay $2$ money and move to square $(3,3)$. His money is now $0$.

## 题解
首先，因为本题中只能向下或者向右走，也就是说，我们的某个点一旦拿去更新其他点，他就一定不会再被更新，也就是说，我们的图是一个有向无环图。因此，我们可以采用我们的 dp 来设计。


于是，我们显然能够想到的一个 dp，就是 $dp[i][j][maxval]$ 来表示走到 $(i,j)$ 时，我们的最大价值是 $maxval$ 的最小时间是多少，然后我们这一个点的更新到下面的点，就需要：
1. 比较我们下一个点的赚钱数和我们当前点的赚钱数，并更新我们的 $dp[i][j][val]$
2. 我们根据我们的 $val$ 和我们剩余的钱来决定我们到这个点的转移所需时间是多少。（而我们剩余的钱因为是由我们的转移时间来计算的，所以满足可以同步转移）

不难发现，如果一个点不是我们从起始点出发的最大路径，那么我们这个状态就是不会被我们所更新的，那么他就不会出现在我们的对应 dp 数组当中。因此我们的更新是不会有重复的路径的。

但我们注意到，我们 `val` 的值域是我们的 $1e9$,暴力显然不可行，但我们注意到，我们的每一个 val 值都是对应一个点的，所以我们可以增加二维表示我们的当前最大值在哪个位置取到。

于是，我们的 dp 就可以表示成如下所示：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=83;
#define int long long
int p[N][N];
int r[N][N];
int d[N][N];
long long dist[N][N][N][N];
int g[N][N][N][N];
signed main(){
	int n;
	cin>>n;
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			cin>>p[i][j];
		}
	}
	
	for(int i=0;i<n;i++){
		for(int j=0;j<n-1;j++){
			cin>>r[i][j];
		}
	}
	
	for(int i=0;i<n-1;i++){
		for(int j=0;j<n;j++){
			cin>>d[i][j];
		}
	}
	memset(g,0,sizeof g);
	memset(dist,0x3f3f3f3f3f3f,sizeof dist);
	dist[0][0][0][0]=0;
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			for(int x=0;x<=i;x++){
				for(int y=0;y<=j;y++){
					//由(i,j,x,y)->(i+1,j,x,y)
					if(i+1<n){
						int val_pre=dist[i][j][x][y];//上一个点的时间 
						int last_pre=g[i][j][x][y];//上一个点剩下的东西 
						int max_prev=p[x][y];//上一个点的最大值 
						int val_to_update=val_pre+1;//这一个点我们要采用的更新时间 
						int last_to_update=0;//这一个点剩下的权值是多少 
						int x_to_update=x;
						int y_to_update=y;
						if(max_prev<p[i+1][j]){
							x_to_update=i+1;
							y_to_update=j;
						}
						if(last_pre>=d[i][j]){
							last_to_update=last_pre-d[i][j];
							if(val_to_update<dist[i+1][j][x_to_update][y_to_update]||(val_to_update==dist[i+1][j][x_to_update][y_to_update]&&last_to_update>g[i+1][j][x_to_update][y_to_update])){
								dist[i+1][j][x_to_update][y_to_update]=val_to_update;
								g[i+1][j][x_to_update][y_to_update]=last_to_update;
							} 
						}else{
							val_to_update+=(d[i][j]-last_pre+max_prev-1)/max_prev;
							last_to_update=(d[i][j]-last_pre+max_prev-1)/max_prev*p[x][y]+last_pre-d[i][j];
							if(val_to_update<dist[i+1][j][x_to_update][y_to_update]||(val_to_update==dist[i+1][j][x_to_update][y_to_update]&&last_to_update>g[i+1][j][x_to_update][y_to_update])){
								dist[i+1][j][x_to_update][y_to_update]=val_to_update;
								g[i+1][j][x_to_update][y_to_update]=last_to_update;
							} 
						}
					} 
					if(j+1<n){
						int val_pre=dist[i][j][x][y];//上一个点的时间 
						int last_pre=g[i][j][x][y];//上一个点剩下的东西 
						int max_prev=p[x][y];//上一个点的最大值 
						int val_to_update=val_pre+1;//这一个点我们要采用的更新时间 
						int last_to_update=0;//这一个点剩下的权值是多少 
						int x_to_update=x;
						int y_to_update=y;
						if(max_prev<p[i][j+1]){
							x_to_update=i;
							y_to_update=j+1;
						}
						if(last_pre>=r[i][j]){
							last_to_update=last_pre-r[i][j];
							if(val_to_update<dist[i][j+1][x_to_update][y_to_update]||(val_to_update==dist[i][j+1][x_to_update][y_to_update]&&last_to_update>g[i][j+1][x_to_update][y_to_update])){
								dist[i][j+1][x_to_update][y_to_update]=val_to_update;
								g[i][j+1][x_to_update][y_to_update]=last_to_update;
							} 
						}else{
							val_to_update+=(r[i][j]-last_pre+max_prev-1)/max_prev;
							last_to_update=(r[i][j]-last_pre+max_prev-1)/max_prev*p[x][y]+last_pre-r[i][j];
							if(val_to_update<dist[i][j+1][x_to_update][y_to_update]||(val_to_update==dist[i][j+1][x_to_update][y_to_update]&&last_to_update>g[i][j+1][x_to_update][y_to_update])){
								dist[i][j+1][x_to_update][y_to_update]=val_to_update;
								g[i][j+1][x_to_update][y_to_update]=last_to_update;
							} 
						}
					} 
			}
		}
	}
}
	long long ans=0x3f3f3f3f3f3f;
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			ans=min(ans,dist[n-1][n-1][i][j]);
		}
	}
	cout<<ans<<endl;
}
```