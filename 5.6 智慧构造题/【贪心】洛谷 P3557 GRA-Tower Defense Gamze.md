# [POI 2013] GRA-Tower Defense Game

## 题目描述

Bytie is playing the computer game Tower Defense.

His aim is to construct guard towers, so that they protect all of his domain.

There are multiple towns in Bytie's domain, some of which are linked by  bidirectional roads.

If Bytie erects a guard tower in a city, then the tower protects its city and  all the cities directly linked with it by roads.

Just as Bytie was pondering over the placement of guard towers in his domain,  his elder sister Bytea entered the room.  She glanced at the map displayed on  the screen, and after a moment exclaimed:

"Oi, what is there to think about, clearly $k$ towers suffice!".

Angered by his sister spoiling the fun, Bytie showed his sister the door,  and began wondering what to do next.

Pride will not let him construct more than $k$ towers.

He has an up his sleeve though:

He can research a technology that will allow him to construct improved guard towers.

An improved guard tower protects not only the town it was erected in and its  immediate neighbors but also the towns that are further away.

Formally, an improved guard tower built in the town $u$ protects the town $v$ if either of the following holds:

- $u=v$;

- there is a direct road from $u$ to $v$;

- or there is such a town $w$ that there are direct roads from $u$ to $w$ and from $w$ to $v$.

Of course, Bytie still strives to erect at most $k$ towers,  but he has no qualms about making these the improved guard towers.

有一个 n 个点 m 条边的图，每条边距离是 1，已知用 k 个攻击距离为 1 的塔可以打到整个地图，让构造一个方案使得用小于等于 k 个攻击距离为 2的塔打到整个地图

## 输入格式

In the first line of the standard input, there are three integers,  $n$, $m$, and $k$ ($2\le n\le 500\ 000$,  $0\le m\le 1\ 000\ 000$, $1\le k\le n$), separated by single spaces,  that specify, respectively, the number of towns and roads in Bytie's domain,  and the number $k$ given by Bytea.

The towns in Bytie's domain are numbered from 1 to $n$.

Next, $m$ lines describing the roads follow.

Each of those lines holds two integers, $a_i$ and $b_i$ ($1\le a_i,b_i\le n$, $a_i\ne b_i$), indicating that the towns no. $a_i$ and $b_i$ are directly linked by a bidirectional road. Each pair of towns is linked by at most a single road.

## 输出格式

Your program is to print two lines, describing the placement of improved  guard towers in Bytie's domain, to the standard output.

The first line is to hold an integer $r$ ($1\le r\le k$), the number of  improved guard towers that Bytie should construct.

The second line is to specify the placement of these by providing $r$ pairwise disjoint integers that are the numbers of town where the improved  guard towers are to be built.

The town numbers can be given in an arbitrary order.

If more than one solution exists, any solution can be printed.

Let us remind that any placement of no more than $k$ improved towers will do  - you need not minimize their number.

You may assume that Bytea was correct, i.e., that the whole domain of Bytie  can indeed be protected by $k$ plain (not improved) guard towers. Thus a solution always exists.

## 样例 #1

### 样例输入 #1

```
9 8 3
1 2
2 3
3 4
1 4
3 5
4 6
7 8
8 9
```

### 样例输出 #1

```
3
1 5 7
```

## 提示

有一个 n 个点 m 条边的图，每条边距离是 1，已知用 k 个攻击距离为 1 的塔可以打到整个地图，让构造一个方案使得用小于等于 k 个攻击距离为 2的塔打到整个地图

## 题解
因为我们本题存在特殊性质，所以我们可以考虑下面的构造法：任意选择一个点，作为我们的起点，然后直接在这个地点放一个守卫，之后，我们再在没有放守卫的地方选择一个放守卫，以此类推，直到我们所有点都被覆盖，这样我们构造出来的一定是合法的。

我们可以感性理解如下：

```cpp
#include<bits/stdc++.h>
#define il inline
using namespace std;
typedef long long ll;
il int read(){
	int ans=0,flag=1;
	char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')flag=-1;ch=getchar();}
	while(isdigit(ch))ans=(ans<<3)+(ans<<1)+(ch^48),ch=getchar();
	return ans*flag;
}
const int N=5e5+7,M=1e6+7;
struct edge{
	int to,nxt;
}e[M<<1];
int head[N];
int cnt;
int n,m,k;

void add_edge(int u,int v){
	e[++cnt].to=v;
	e[cnt].nxt=head[u];
	head[u]=cnt;
}

int tot;
int ans[N];
bool vis[N];

void dfs(int now,int stp){
	//printf("(%d,%d)\n",now,stp);
	vis[now]=1;
	if(stp==2)return;
	for(int i=head[now];i;i=e[i].nxt){
		dfs(e[i].to,stp+1);
	}
}

int main(){
	n=read(),m=read(),k=read();
	for(int i=1;i<=m;i++){
		int u=read(),v=read();
		add_edge(u,v);
		add_edge(v,u);
	}
	//for(int i=1;i<=2*m;i++){
	//	printf("%d %d\n",e[i].to,e[i].nxt);
	//}
	for(int i=1;i<=n;i++){
		if(!vis[i]){
			ans[++tot]=i;
			dfs(i,0);
		}
	}
	printf("%d\n",tot);
	for(int i=1;i<=tot;i++){
		printf("%d ",ans[i]);
	}
	return 0;
}
```