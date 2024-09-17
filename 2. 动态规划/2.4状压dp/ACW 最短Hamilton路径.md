# 
## 题目描述
给定一张 n个点的带权无向图，点从 0∼n−1 标号，求起点 0 到终点 n−1的最短 Hamilton 路径。

Hamilton 路径的定义是从 0 到 n−1 不重不漏地经过每个点恰好一次。

## 输入格式
![[Pasted image 20230802185310.png]]


## 输出格式

输出一个整数，表示最短 Hamilton 路径的长度。

## 样例 #1

### 样例输入 #1

```
5
0 2 4 5 1
2 0 6 5 3
4 6 0 8 3
5 5 8 0 5
1 3 3 5 0
```

### 样例输出 #1

```
18
```

## 提示

![[Pasted image 20230802185327.png]]

## 题解
我们可以按照状态压缩的思路求解最短 Hamilton 问题，首先定义 dp 状态 $dp[S][j]$ 表示集合 S 内的最短 halmiton 路径，且以 j 为重点。然后根据 DP 的思路，让 S 从最小的子集逐渐扩展到全图，$dp[S][j]=min(dp[S-j][k],dist(k,j)) k\to S-j$


## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,dp[1<<20][21];
int dist[20][21];
int main(){
	memset(dp,0x3f,sizeof dp);
	cin>>n;
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			cin>>dist[i][j];
		}
	}
	dp[1][0]=0;
	for(int s=1;s<(1<<n);s++){
		for(int j=0;j<n;j++){
			if((s>>j)&1){
				for(int k=0;k<n;k++){
					if(s^(1<<j)>>k&1){
						dp[s][j]=min(dp[s][j],dp[s^(1<<j)][k]+dist[k][j]);
					}
				}
			}
		}
	}
	cout<<dp[(1<<n)-1][n-1];
	return 0;
}
```