# 
## 题目描述
There is a square grid of size n×n. Some cells are colored in black, all others are colored in white. In one operation you can select some rectangle and color all its cells in white. It costs max(h,w) to color a rectangle of size h×w. You are to make all cells white for minimum total cost.

## 输入格式
The first line contains a single integer n (1≤n≤50) — the size of the square grid.

Each of the next n lines contains a string of length n, consisting of characters '.' and '#'. The j-th character of the i-th line is '#' if the cell with coordinates (i,j) is black, otherwise it is white.


## 输出格式
Print a single integer — the minimum total cost to paint all cells in white.


## 样例 #1

### 样例输入 #1

```
3
###
#.#
###

```

### 样例输出 #1

```
3

```

### 样例输入 #2

```
3
...
...
...


```

### 样例输出 #2

```
0
```
## 提示
本题是一个二维区间dp的例题
## 题解
我们设矩形左下角坐标为$(xi,yi)$,右上角坐标为$(xj,yj)$,我们设置状态$dp[x_{1}][y_{1}][x_{2}][y_{2}]$表示把这个区间涂成白色的最小代价。
这个区域分别按x轴或y轴分成两个矩形，遍历所有可能的分割，
x方向$dp[x_{1}][][x_{2}][]=min(dp[x_{1}][][x_{2}][],dp[x_{1}][][k][]+dp[k+1][][x_{2}][])$
y方向同理

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=55;
int dp[N][N][N][N];
char mp[N][N];
int main(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			cin>>mp[i][j]; 
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(mp[i][j]=='.') dp[i][j][i][j]=0;
			else dp[i][j][i][j]=1;
		}
	}
	for(int lenx=1;lenx<=n;lenx++){
		for(int leny=1;leny<=n;leny++){
			for(int x1=1;x1<=n-lenx+1;x1++){
				for(int y1=1;y1<=n-leny+1;y1++){
					int x2=x1+lenx-1;
					int y2=y1+leny-1;
					if(x1==x2&&y1==y2) continue;
					dp[x1][y1][x2][y2]=max(abs(x1-x2),abs(y1-y2))+1;
					for(int k=x1;k<=x2;k++){
						dp[x1][y1][x2][y2]=min(dp[x1][y1][x2][y2],dp[x1][y1][k][y2]+dp[k+1][y1][x2][y2]);
					}
					for(int k=y1;k<=y2;k++){
						dp[x1][y1][x2][y2]=min(dp[x1][y1][x2][y2],dp[x1][y1][x2][k]+dp[x1][k+1][x2][y2]);
					}
				}
			}
		} 
	}
	cout<<dp[1][1][n][n];
}
```