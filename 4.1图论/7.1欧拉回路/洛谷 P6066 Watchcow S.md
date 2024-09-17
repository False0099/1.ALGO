# [USACO 05 JAN] Watchcow S

## 题目描述

Farmer John 有 $N$ 个农场（$2 \leq N \leq 10^4$），这些农场由 $M$ 条道路连接（$1 \leq M \leq 5 \times 10^4$）。不保证没有重边。

Bassie 从 $1$ 号农场开始巡逻，每条路必须从两个方向各走**恰好一遍**，最后回到 $1$ 号农场。

请输出一条满足上述要求的路径。

保证这样的路径存在。如果有多条路径，任意输出一条即可。

## 输入格式

第一行两个整数 $N,M$。

接下来 $M$ 行，每行两个整数 $u,v$，描述一条 $u$ 到 $v$ 的道路。

## 输出格式

输出经过的农场，一行一个。

## 样例 #1

### 样例输入 #1

```
4 5
1 2
1 4
2 3
2 4
3 4
```

### 样例输出 #1

```
1
2
3
4
2
1
4
3
2
4
1
```


## 题解
我们这一题可以用我们的欧拉回路法，因为所有的点都要经过一次，所以我们只需要删边即可。
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,u,v;
vector<int> ve[10002];
queue<int> ans;
//这里就是一个朴实无华的深搜，就只是用了欧拉回路的思路，反正他会回来，每次删边就行
void dfs(int f){
	int len=ve[f].size();
	for(int i=0;i<len;++i){
		int xn=ve[f][i];
		if(xn){
			//删边
			ve[f][i]=0;
			dfs(xn);
		}
	}
  	//ans是用来存最终的顺序的
	ans.push(f);
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;++i){
		scanf("%d%d",&u,&v);
  		//双向建边
		ve[u].push_back(v);
		ve[v].push_back(u);
	}
	//从1号点开始dfs
	dfs(1);		
  	//输出，每次输出都出队
	while(!ans.empty()) {
		printf("%d\n",ans.front());
		ans.pop();
	}
  	//朴实无华的结束
	return 0;
}
```