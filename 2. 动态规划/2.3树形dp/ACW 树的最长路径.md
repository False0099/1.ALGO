# 知识点
  ## [[树形DP]]
# 题目
 给定一棵树，树中包含 n个结点（编号 1~n）和 n−1
 条无向边，每条边都有一个权值。现在请你找到树中的一条最长路径。换句话说，要找到一条路径，使得使得路径两端的点的距离最远。
 注意：路径中可以只包含一个点。

## 输入格式
第一行包含整数 n。

接下来 n−1 行，每行包含三个整数 ai, bi, ci，表示点 ai
 和 bi 之间存在一条权值为 ci 的边。
 
## 输出格式
输出一个整数，表示树的最长路径的长度。

## 数据范围
1≤n≤10000
,
1≤ai, bi≤n
,
−105≤ci≤105
## 输入样例 ：
6
5 1 6
1 4 5
6 3 9
2 6 8
6 1 7
## 输出样例 ：
22

# 思路
·如果我们是求单纯的最长的 2没有权重的，我们可以用下面的思路，先找到一个节点最远的一个节点，记作 A，再从 A 出发，找到离 A 最远的第二个点 B，AB 两者的连线就是一个直径。
·但现在有了权重，我们就不能那么简单粗暴的求了，我们需要求出每一个点上的最长路和次长路，最后在每一个节点上的最长路就是最长路+次长路。
·
# AC 代码
```cpp
#include <iostream>
using namespace std;
int h[N],ne[N],e[N],idx,w[N];
void add(int a,int b,int c){
	e[idx]=b;
	w[idx]=c;
	ne[idx]=a;
	h[a]=idx++;
}
int dfs(int u,int father){
	int dist=0;
	int d1=0,d2=0;
	for(int i=h[u];i!=-1;i=ne[i]){
		int j=e[i];
		if(j==father){
			continue;
		}
		int d=dfs(j,u);
		dist=max(dist,d+w[i]);
		if(d>=d1) d2=d1,d1=d;
		else if(d>=d2) d2=d;
	}
	ans=max(ans,d1+d2);
	return dist;
}
```
# 备注
