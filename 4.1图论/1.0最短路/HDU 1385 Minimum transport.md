## 题目描述
一个国家有 n 座城市，每个城市之间可能有一条公路或没有。现在有一些货物要从一座城市运输到另一座城市。交通费用由两部分组成：

1、在公路上的运输成本

2、固定的税收，每经过一座城市需要上缴一定的费用，费用可能不同，源城市和目标城市不用交。

现在请你编写一个程序计算出最短路径和花费。

## 输入格式
本题有多组数据。

每组数据的第一行是一个数字 n，表示有 n 座城市，n=0 表示数据结束。

然后是一个n×n 行，用来表示任意两座城市之间公路的花销，−1 代表没有公路。

然后是一行 n 个数字，表示从每座城市中转时的固定税收。

接下来若干行，每行 22 个数 c,d 表示询问从 c 到 d 的最短路径。以 −1 结尾。


## 输出格式
```
From c to d :
Path: c-->c1-->......-->ck-->d
Total cost : ......
......

From e to f :
Path: e-->e1-->......-->ek-->f
Total cost : ......
```

	
## 样例 #1

### 样例输入 #1

```
5
0 3 22 -1 4
3 0 5 -1 -1
22 5 0 9 20
-1 -1 9 0 4
4 -1 20 4 0
5 17 8 3 1
1 3
3 5
2 4
-1 -1
0

```

### 样例输出 #1

```
From 1 to 3 :
Path: 1-->5-->4-->3
Total cost : 21

From 3 to 5 :
Path: 3-->4-->5
Total cost : 16

From 2 to 4 :
Path: 2-->1-->5-->4
Total cost : 17

```


## 题解
本题是要求我们输出所有最短路和他们的具体路径，我们可以采用floyd算法，用一个path数组来定义我们的路径，$path[i][j]$表示我们起点为$i$终点为$j$，的最短路径，从i出发的下一个点为j，然后找下一个点我们就可以用$path[u][j]=v$等，直到最后到达j

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=505;
const int INF=0x3f3f3f3f;
int n,map[N][N],tax[N],path[N][N];
void init(){
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			cin>>map[i][j];
			if(map[i][j]==-1) map[i][j]=INF;
			path[i][j]=j;
		}
	}
	for(int i=1;i<=n;i++){
		cin>>tax[i];
	}
}
void floyd(){
	for(int k=1;k<=n;k++){
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				int len=map[i][k]+map[k][j]+tax[k];
				if(map[i][j]>len){
					map[i][j]=len;
					path[i][j]=path[i][k];
				}else if(len==map[i][j]&&path[i][j]>path[i][k]){
					path[i][j]=path[i][k]; 
				}
		
			}
		}
	}
}
void output(){
	int s,t;
	while(cin>>s>>t){
		if(s==-1&&t==-1) break;
		cout<<s<<t;
		cout<<s;
		int k=s;
		while(k!=t){
			cout<<path[k][t];
			k=path[k][t];
		}
		puts("");
	}
}
int main(){
	input();
	floyd();
	output();
}
```