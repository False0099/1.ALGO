### Problem Statement

**This problem has a similar setting to Problem G. Differences in the problem statement are indicated in red.**

There is a grid with $H$ rows and $W$ columns, where each cell is painted red or green.

Let $(i,j)$ denote the cell in the $i$ \-th row from the top and the $j$ \-th column from the left.

The color of cell $(i,j)$ is represented by the character $S_{i,j}$, where $S_{i,j} =$ `.` means cell $(i,j)$ is red, and $S_{i,j} =$ `#` means cell $(i,j)$ is green.

The **number of green connected components** in the grid is the number of connected components in the graph with the vertex set being the green cells and the edge set being the edges connecting two adjacent green cells. Here, two cells $(x,y)$ and $(x',y')$ are considered adjacent when $|x-x'| + |y-y'| = 1$.

Consider choosing one **red** cell uniformly at random and repainting it **green**. Print the expected value of the number of green connected components in the grid after repainting, modulo $998244353$.

What does "print the expected value modulo $998244353$" mean? It can be proved that the sought expected value is always rational. Furthermore, the constraints of this problem guarantee that if that value is expressed as $\frac{P}{Q}$ using two coprime integers $P$ and $Q$, there is exactly one integer $R$ such that $R \times Q \equiv P \pmod{998244353}$ and $0 \leq R &lt; 998244353$. Print this $R$.


### Constraints

-   $1 \leq H,W \leq 1000$
-   $S_{i,j} =$ `.` or $S_{i,j} =$ `#`.
-   There is at least one $(i,j)$ such that $S_{i,j} =$ `.`.


### Input

The input is given from Standard Input in the following format:


$H$ $W$
$S_{1,1}$$S_{1,2}$$\ldots$$S_{1,W}$
$S_{2,1}$$S_{2,2}$$\ldots$$S_{2,W}$
$\vdots$
$S_{H,1}$$S_{H,2}$$\ldots$$S_{H,W}$


## 题解
本体思路：通过我们的贡献发，计算我们每一个格子对于我们答案的贡献是多少。这里我们每一个格子对于我们答案的贡献：就是与这个格子相邻的不同种连通块的数量和-1. 之后，我们只需要按照我们的方法 dfs，计算贡献即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=1010;
char g[N][N];
set<int> st[N][N];//统计我们的这个点的相邻的颜色种类 
int dx[4]={0,1,0,-1};
int dy[4]={1,0,-1,0};
int idd[N][N];
const int MOD=998244353;
int qpow(int a,int b,int mod){
	int res=1;while(b){if(b&1){res=res*a%mod;}a=a*a%mod;b>>=1;}return res;
}
int inv(int x,int mod){return qpow(x,mod-2,mod);}
//求逆元，要求a与p互质


int n,m;
void dfs(int x,int y,int id){
	idd[x][y]=id;
	for(int i=0;i<4;i++){
		int xx=x+dx[i];
		int yy=y+dy[i];
		if(xx<0||xx>=n||yy<0||yy>=m){
			continue;
		}
		if(g[xx][yy]=='.'){
			st[xx][yy].insert(id);
			continue; 
		}
		if(g[xx][yy]=='#'&&idd[xx][yy]==0){
			dfs(xx,yy,id);
		}
	}
}
signed main(){
	//int n,m;
	cin>>n>>m;
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			cin>>g[i][j];
		}
	}
	int id=0;
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			if(g[i][j]=='#'&&idd[i][j]==0){
				dfs(i,j,++id);
			}
		}
	}
	int tot=0;
	int cnt=0;
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			if(g[i][j]=='.'){
				cnt++;
				tot+=id-(st[i][j].size()-1);
				tot%=MOD;	
			}
		}
	}
	
	cout<<(tot*inv(cnt,MOD))%MOD<<endl;
}
```