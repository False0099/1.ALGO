# 知识点
  ## [[BFS]]
# 题目
 给定一个 N 行 M 列的 01 矩阵 A，$A[i][j]$ 与 $A[k][l]$ 之间的曼哈顿距离定义为：$Dist (A[i][j], A[k][l])=|i−k|+|j−l|$输出一个 N 行 M 列的整数矩阵 B，其中：$B[i][j]=min 1≤x≤N, 1≤y≤M, A[x][y]=1 dist (A[i][j], A[x][y])$
 # 输入格式
 第一行两个整数 N, M。接下来一个 N行 M列的 01矩阵，数字之间没有空格。

# 输出格式
一个 N行 M列的矩阵 B，相邻两个整数之间用一个空格隔开。

# 数据范围
$1≤N, M≤1000$
# 输入样例 ：
````
3 4
0001
0011
0110
````

# 输出样例 ：
````
3 2 1 0
2 1 0 0
1 0 0 1
````

# 思路
·我们在初始化的时候就先把 1 的点放入到队列中，然后再根据这个队列的变化来去找到离这些点最近的距离
·我们一般的思路是从头到尾按照类似于 floyd 的算法来计算每个点到每个商店的最大值
·而我们现在就反向来考虑，考虑先把 1 放进队列，或者说以 1 为源头开始bfs
# AC 代码
```cpp
#include <iostream>
using namespace std;
typedef pair<int,int> PII;
const int N=1010;
int dx[4]={0,1,0,-1};
int dy[4]={1,0,-1,0};
void  dfs(){
	queue<PII> q;
	q.push({1,1},{1,2}.....);
	while(!q.empty()){
		for(int i=0;i<4;i++){
			int x=t.first+dx[i];
			int y=t.second+dy[i];
			if(x<0||x>n||y<0||y>n||graph[x][y]==1||st[x][y]!=-1) continue;
			st[x][y]=st[t.first][t.second]+1;
		}
	}
}
```
# 备注
