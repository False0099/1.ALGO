# Expected diameter of a tree

## 题面翻译

给一片森林，$q$ 个询问，每个询问两个点，问将这两个点所在的集合连接起来组成的新集合，它的最远两点的距离的期望值是多少。

## 题目描述

Pasha is a good student and one of MoJaK's best friends. He always have a problem to think about. Today they had a talk about the following problem.

We have a forest (acyclic undirected graph) with $ n $ vertices and $ m $ edges. There are $ q $ queries we should answer. In each query two vertices $ v $ and $ u $ are given. Let $ V $ be the set of vertices in the connected component of the graph that contains $ v $ , and $ U $ be the set of vertices in the connected component of the graph that contains $ u $ . Let's add an edge between some vertex ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF804D/8ef01bdc02f37e886781700f62479c92154da008.png) and some vertex in ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF804D/0479fe8afb5e9211cdac4c2d711ca0b8e2ad6e82.png) and compute the value $ d $ of the resulting component. If the resulting component is a tree, the value $ d $ is the diameter of the component, and it is equal to -1 otherwise. What is the expected value of $ d $ , if we choose vertices $ a $ and $ b $ from the sets uniformly at random?

Can you help Pasha to solve this problem?

The diameter of the component is the maximum distance among some pair of vertices in the component. The distance between two vertices is the minimum number of edges on some path between the two vertices.

Note that queries don't add edges to the initial forest.

## 输入格式

The first line contains three integers $ n $ , $ m $ and $ q $ ( $ 1<=n, m, q<=10^{5} $ ) — the number of vertices, the number of edges in the graph and the number of queries.

Each of the next $ m $ lines contains two integers $ u_{i} $ and $ v_{i} $ ( $ 1<=u_{i}, v_{i}<=n $ ), that means there is an edge between vertices $ u_{i} $ and $ v_{i} $ .

It is guaranteed that the given graph is a forest.

Each of the next $ q $ lines contains two integers $ u_{i} $ and $ v_{i} $ ( $ 1<=u_{i}, v_{i}<=n $ ) — the vertices given in the $ i $ -th query.

## 输出格式

For each query print the expected value of $ d $ as described in the problem statement.

Your answer will be considered correct if its absolute or relative error does not exceed $ 10^{-6} $ . Let's assume that your answer is $ a $ , and the jury's answer is $ b $ . The checker program will consider your answer correct, if ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF804D/259203790d90e969d73ec841bd0673c1e8e7d69a.png).

## 样例 #1

### 样例输入 #1

```
3 1 2
1 3
3 1
2 3
```

### 样例输出 #1

```
-1
2.0000000000
```

## 样例 #2

### 样例输入 #2

```
5 2 3
2 4
4 3
4 2
4 1
2 5
```

### 样例输出 #2

```
-1
2.6666666667
2.6666666667
```

## 提示

In the first example the vertices $ 1 $ and $ 3 $ are in the same component, so the answer for the first query is -1. For the second query there are two options to add the edge: one option is to add the edge $ 1-2 $ , the other one is $ 2-3 $ . In both ways the resulting diameter is $ 2 $ , so the answer is $ 2 $ .

In the second example the answer for the first query is obviously -1. The answer for the second query is the average of three cases: for added edges $ 1-2 $ or $ 1-3 $ the diameter is $ 3 $ , and for added edge $ 1-4 $ the diameter is $ 2 $ . Thus, the answer is ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF804D/80f05d9f9a5abbad800eeb11e2f309500aaccabe.png).


## 题解
我们这一题要求我们连边后的直径期望，我们可以先求出总共可能的连边方式，一共有 $sizx\times sizy$ 中可能的情况。

对于我们的直径总长度，我们可以考虑进行一个换根 dp，先预处理出来对于每棵树来说，我们某个节点能够到达的最远距离，那么我们再 $(a,b)$ 之间连边后形成的最大直径就是 max $(d_{x},d_{y},mx_{a}+mx_{b}+1)$ 这里的关键是快速的求出我们的 $mx_{a}+mx_{b}+1$ 产生的贡献。

一种朴素的思路是对于小树 x 的每个点 s，我们二分查找在对应的大树 y 上满足条件的 mxb, 那么我们在 mxb 之后的就都不行，之前的就都行。完事儿我们再去看下一个点。

```cpp
/*
わんわん……わんだほーいっ☆
Wonderhoy!
*/
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef double DB;
char buf[1<<21],*p1=buf,*p2=buf;
#define getchar() (p1==p2 && (p2=(p1=buf)+fread(buf,1,1<<18,stdin),p1==p2)?EOF:*p1++)
LL read()
{
	LL x=0;
	char c=getchar();
	while(c<'0' || c>'9')	c=getchar();
	while(c>='0' && c<='9')	x=(x<<1)+(x<<3)+(c^'0'),c=getchar();
	return x;
}
vector<LL> G[100005];
LL n,m,q;
LL col[100005],cnt;
void colit(LL u,LL f,vector<LL> &Seq)
{
	Seq.push_back(u);
	col[u]=cnt;
	for(LL v:G[u])
	{
		if(v==f)	continue;
		colit(v,u,Seq);
	}
}
vector<LL> Seq[100005];
LL dis[100005],p[100005];
void dfs1(LL u,LL f)
{
	for(LL v:G[u])
	{
		if(v==f)	continue;
		dis[v]=dis[u]+1;
		dfs1(v,u);
	}
}
typedef pair<LL,LL> P;
#define mp make_pair
map<P,DB> M;
int main(){
	n=read(),m=read(),q=read();
	for(LL i=1;i<=m;++i)
	{
		LL u=read(),v=read();
		G[u].push_back(v);
		G[v].push_back(u);
	}
	for(LL i=1;i<=n;++i)
	{
		if(col[i])	continue;
		++cnt;
		colit(i,0,Seq[cnt]);
		dis[i]=0;
		dfs1(i,0);
		LL u=0;
		for(LL v:Seq[cnt])	if(dis[v]>dis[u])	u=v;
		dis[u]=0;
		dfs1(u,0);
		LL v=0;
		for(LL a:Seq[cnt])	if(dis[a]>dis[v])	v=a;
		for(LL a:Seq[cnt])	p[a]=dis[a];
		dis[v]=0;
		dfs1(v,0);
		for(LL a:Seq[cnt])	p[a]=max(p[a],dis[a]);
		sort(Seq[cnt].begin(),Seq[cnt].end(),[&](LL x,LL y){return p[x]<p[y];});
	}
	while(q-->0)
	{
		LL u=read(),v=read();
		u=col[u],v=col[v];
		if(u==v)
		{
			puts("-1");
			continue;
		}
		if(Seq[u].size()>Seq[v].size())	swap(u,v);
		if(M[mp(u,v)])
		{
			printf("%.10f\n",M[mp(u,v)]);
			continue;
		}
		LL ans=0,suf=0;
		LL pos=LL(Seq[v].size());
		LL dmax=max(p[Seq[u].back()],p[Seq[v].back()]);
		for(LL i=0;i<LL(Seq[u].size());++i)
		{
			LL c=p[Seq[u][i]];
			while(pos>=1 && p[Seq[u][i]]+p[Seq[v][pos-1]]+1>=dmax)	--pos,suf+=p[Seq[v][pos]];
			ans+=pos*dmax;
			ans+=suf;
			ans+=(c+1)*(LL(Seq[v].size())-pos);
		}
		printf("%.10f\n",M[mp(u,v)]=DB(ans)/DB(LL(Seq[u].size())*LL(Seq[v].size())));
	}
	return 0;
}