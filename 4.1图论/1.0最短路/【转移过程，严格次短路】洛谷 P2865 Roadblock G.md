# [USACO 06 NOV] Roadblocks G

## 题面翻译

贝茜把家搬到了一个小农场，但她常常回到 FJ 的农场去拜访她的朋友。贝茜很喜欢路边的风景，不想那么快地结束她的旅途，于是她每次回农场，都会选择第二短的路径，而不象我们所习惯的那样，选择最短路。  
贝茜所在的乡村有 $R(1\le R \le 10^5)$ 条双向道路，每条路都联结了所有的 $N(1\le N\le 5000)$ 个农场中的某两个。贝茜居住在农场 $1$，她的朋友们居住在农场 $N$（即贝茜每次旅行的目的地）。  
贝茜选择的第二短的路径中，可以包含任何一条在最短路中出现的道路，并且，一条路可以重复走多次。当然咯，第二短路的长度必须严格大于最短路（可能有多条）的长度，但它的长度必须不大于所有除最短路外的路径的长度。

## 题目描述

Bessie has moved to a small farm and sometimes enjoys returning to visit one of her best friends. She does not want to get to her old home too quickly, because she likes the scenery along the way. She has decided to take the second-shortest rather than the shortest path. She knows there must be some second-shortest path.

The countryside consists of R (1 ≤ R ≤ 100,000) bidirectional roads, each linking two of the N (1 ≤ N ≤ 5000) intersections, conveniently numbered 1..N. Bessie starts at intersection 1, and her friend (the destination) is at intersection N.

The second-shortest path may share roads with any of the shortest paths, and it may backtrack i.e., use the same road or intersection more than once. The second-shortest path is the shortest path whose length is longer than the shortest path (s) (i.e., if two or more shortest paths exist, the second-shortest path is the one whose length is longer than those but no longer than any other path).

## 输入格式

Line 1: Two space-separated integers: N and R


Lines 2.. R+1: Each line contains three space-separated integers: A, B, and D that describe a road that connects intersections A and B and has length D (1 ≤ D ≤ 5000)

## 输出格式

Line 1: The length of the second shortest path between node 1 and node N

## 样例 #1

### 样例输入 #1

```
4 4
1 2 100
2 4 200
2 3 250
3 4 100
```

### 样例输出 #1

```
450
```

## 提示

Two routes: 1 -> 2 -> 4 (length 100+200=300) and 1 -> 2 -> 3 -> 4 (length 100+250+100=450)


## 题解
我们本题要求我们求第二短路，我们就可以考虑按照我们求第 K 短路，令我们的 K=2 即可。或者因为我们边数较少，我们可以直接维护我们的最短和次短值。

```cpp
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
#include <stack>
#include <queue> 
using namespace std;
struct ahah{
	int nxt,to,dis;
}edge[200010];
int n,m;
int head[5010],tot;
void add(int x,int y,int z)
{
	edge[++tot].nxt=head[x],edge[tot].to=y,edge[tot].dis=z,head[x]=tot;
}
int d[5010][2];
bool vis[5010];
queue <int> que;
int read()
{
	int sum=0,fg=1; char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')fg=-1;c=getchar();}
	while(c>='0'&&c<='9'){sum=sum*10+c-'0';c=getchar();}
	return sum*fg;
}
void spfa(int s)
{
	memset(d,0x7f,sizeof(d));
	que.push(s);vis[s]=1;
	d[s][0]=0;
	while(!que.empty())
	{
		int u=que.front();
		vis[u]=0;que.pop() ;
		for(int i=head[u];i;i=edge[i].nxt)
		{
			int v=edge[i].to;
			if(d[v][0]>d[u][0]+edge[i].dis)
			{
				d[v][1]=d[v][0];
				d[v][0]=d[u][0]+edge[i].dis;
				if(!vis[v])vis[v]=1,que.push(v);
			}
			if(d[v][1]>d[u][0]+edge[i].dis&&d[u][0]+edge[i].dis>d[v][0])
			{
				d[v][1]=d[u][0]+edge[i].dis;
				if(!vis[v])vis[v]=1,que.push(v);
			}
			if(d[v][1]>d[u][1]+edge[i].dis)
			{
				d[v][1]=d[u][1]+edge[i].dis;
				if(!vis[v])vis[v]=1,que.push(v);
			}
		}
	} 
}
int main()
{
	int x,y,z;
	n=read();m=read();
	for(int i=1;i<=m;i++)
	{
		x=read(),y=read(),z=read();
		add(x,y,z);add(y,x,z);
	}
	spfa(n);
	printf("%d",d[1][1]);
}
```

```cpp
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
#include <stack>
#include <queue> 
using namespace std;
struct ahah{
	int nxt,to,dis;
}edge[200010];
int n,m;
int head[5010],tot;
void add(int x,int y,int z)
{
	edge[++tot].nxt=head[x],edge[tot].to=y,edge[tot].dis=z,head[x]=tot;
}
int d[5010][2];
bool vis[5010];
queue <int> que;
int read()
{
	int sum=0,fg=1; char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')fg=-1;c=getchar();}
	while(c>='0'&&c<='9'){sum=sum*10+c-'0';c=getchar();}
	return sum*fg;
}
void spfa(int s)
{
	memset(d,0x7f,sizeof(d));
	que.push(s);vis[s]=1;
	d[s][0]=0;
	while(!que.empty())
	{
		int u=que.front();
		vis[u]=0;que.pop() ;
		for(int i=head[u];i;i=edge[i].nxt)
		{
			int v=edge[i].to;
			if(d[v][0]>d[u][0]+edge[i].dis)
			{
				d[v][1]=d[v][0];
				d[v][0]=d[u][0]+edge[i].dis;
				if(!vis[v])vis[v]=1,que.push(v);
			}
			if(d[v][1]>d[u][0]+edge[i].dis&&d[u][0]+edge[i].dis>d[v][0])
			{
				d[v][1]=d[u][0]+edge[i].dis;
				if(!vis[v])vis[v]=1,que.push(v);
			}
			if(d[v][1]>d[u][1]+edge[i].dis)
			{
				d[v][1]=d[u][1]+edge[i].dis;
				if(!vis[v])vis[v]=1,que.push(v);
			}
		}
	} 
}
int main()
{
	int x,y,z;
	n=read();m=read();
	for(int i=1;i<=m;i++)
	{
		x=read(),y=read(),z=read();
		add(x,y,z);add(y,x,z);
	}
	spfa(n);
	printf("%d",d[1][1]);
}
```