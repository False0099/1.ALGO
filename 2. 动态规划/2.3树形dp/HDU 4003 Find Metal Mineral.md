Humans have discovered a kind of new metal mineral on Mars which are distributed in point‐like with paths connecting each of them which formed a tree. Now Humans launches k robots on Mars to collect them, and due to the unknown reasons, the landing site S of all robots is identified in advanced, in other word, all robot should start their job at point S. Each robot can return to Earth anywhere, and of course they cannot go back to Mars. We have research the information of all paths on Mars, including its two endpoints x, y and energy cost w. To reduce the total energy cost, we should make a optimal plan which cost minimal energy cost.

  
给一棵n个节点的树, 节点编号为1~n, 每条边都有一个花费值.  
有k个机器人从S点出发, 问让机器人遍历所有边,最少花费值多少?

Input

There are multiple cases in the input.  
In each case:  
The first line specifies three integers N, S, K specifying the numbers of metal mineral, landing site and the number of robots.  
The next n‐1 lines will give three integers x, y, w in each line specifying there is a path connected point x and y which should cost w.  
1<=N<=10000, 1<=S<=N, 1<=k<=10, 1<=x, y<=N, 1<=w<=10000.

Output

For each cases output one line with the minimal energy cost.

Sample Input

3 1 1
1 2 1
1 3 1
3 1 2
1 2 1
1 3 1

Sample Output

3
2

## 题解
设 $f[i,j]$ 表示**以 i 为根的子树**全部遍历后**有 j 个机器人没有回来**的最小花费。（因为我们发现最后机器人都不回来才会最优）

特别的，$f[i,0]$ 表示机器人全部回到了 i 点且子树全部遍历了，我们可以发现**只派一个机器人去遍历然后回来**是最优的。所以 f $[i,0]=∑_{j \in son_{i}}f[j,0]+2∗w$

对于 $f[i,j]$，我们可以理解为把 j 个不回来的机器人分配给每一个儿子，从所有的分配情况里面找到最小的。（树形背包）

$f[i,j]=min_{v \in son_{i},1<k\leq j} f[i][j],f[i,j-k]+f[v,k]+k*w$


因为必须要遍历一遍，枚举 k 之前先要 $f[i,j]+=f[v,0]$，保证 $f[i,j]$ 至少遍历了子树。

显然，答案是 $f[s][K]$。
```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read() {
	int x=0,f=1; char ch=getchar();
	while(ch<'0' || ch>'9') { if(ch=='-') f=-1; ch=getchar(); }
	while(ch>='0'&&ch<='9') { x=(x<<3)+(x<<1)+(ch^48); ch=getchar(); }
	return x * f;
}
const int N = 10007;
int n,rt,K,cnt;
int head[N];
int f[N][11];
struct Edge {
	int next,to,w;
}edge[N<<1];
inline void add(int u,int v,int w) {
	edge[++cnt] = (Edge)<%head[u],v,w%>;
	head[u] = cnt;
}
void Dfs1(int u,int fa) {
	for(int i=head[u];i;i=edge[i].next) {
		int v = edge[i].to, w = edge[i].w;
		if(v == fa) continue;
		Dfs1(v,u);
		for(int j=K;j>=1;--j) {
			f[u][j] += f[v][0] + 2*w;
			for(int k=1;k<=j;++k)
				f[u][j] = min(f[u][j], f[u][j-k]+f[v][k]+k*w);
		}
		f[u][0] += f[v][0] + 2*w;
	}
}
void work() {
	cnt = 0;
	memset(f, 0, sizeof(f));
	memset(head, 0, sizeof(head));
	rt = read(), K = read();
	for(int i=1,u,v,w;i<n;++i) {
		u = read(), v = read(), w = read();
		add(u,v,w), add(v,u,w);
	}
	Dfs1(rt,0);
	printf("%d\n",f[rt][K]);
}
int main()
{
	while(~scanf("%d",&n))
		work();
	return 0;
}
/*
3 1 1
1 2 1
1 3 1
3 1 2
1 2 1
1 3 1

3
2
*/

```



  
 

## Hint

In the first case: 1->2->1->3 the cost is 3;
In the second case: 1->2; 1->3 the cost is 2;

