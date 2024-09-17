### Problem Statement

In the country of AtCoder, there are $N$ stations: station $1$, station $2$, $\ldots$, station $N$.

You are given $M$ pieces of information about trains in the country. The $i$ \-th piece of information $(1\leq i\leq M)$ is represented by a tuple of six positive integers $(l _ i,d _ i,k _ i,c _ i,A _ i,B _ i)$, which corresponds to the following information:

-   For each $t=l _ i,l _ i+d _ i,l _ i+2d _ i,\ldots,l _ i+(k _ i-1)d _ i$, there is a train as follows:
    -   The train departs from station $A _ i$ at time $t$ and arrives at station $B _ i$ at time $t+c _ i$.

No trains exist other than those described by this information, and it is impossible to move from one station to another by any means other than by train.  
Also, assume that the time required for transfers is negligible.

Let $f(S)$ be the latest time at which one can arrive at station $N$ from station $S$.  
More precisely, $f(S)$ is defined as the maximum value of $t$ for which there is a sequence of tuples of four integers $\big((t _ i,c _ i,A _ i,B _ i)\big) _ {i=1,2,\ldots,k}$ that satisfies all of the following conditions:

-   $t\leq t _ 1$
-   $A _ 1=S,B _ k=N$
-   $B _ i=A _ {i+1}$ for all $1\leq i\lt k$,
-   For all $1\leq i\leq k$, there is a train that departs from station $A _ i$ at time $t _ i$ and arrives at station $B _ i$ at time $t _ i+c _ i$.
-   $t _ i+c _ i\leq t _ {i+1}$ for all $1\leq i\lt k$.

If no such $t$ exists, set $f(S)=-\infty$.

Find $f(1),f(2),\ldots,f(N-1)$.

### Constraints

-   $2\leq N\leq2\times10 ^ 5$
-   $1\leq M\leq2\times10 ^ 5$
-   $1\leq l _ i,d _ i,k _ i,c _ i\leq10 ^ 9\ (1\leq i\leq M)$
-   $1\leq A _ i,B _ i\leq N\ (1\leq i\leq M)$
-   $A _ i\neq B _ i\ (1\leq i\leq M)$
-   All input values are integers.

### Input

The input is given from Standard Input in the following format:

```
$N$ $M$
$l _ 1$ $d _ 1$ $k _ 1$ $c _ 1$ $A _ 1$ $B _ 1$
$l _ 2$ $d _ 2$ $k _ 2$ $c _ 2$ $A _ 2$ $B _ 2$
$\vdots$
$l _ M$ $d _ M$ $k _ M$ $c _ M$ $A _ M$ $B _ M$
```

### Output

Print $N-1$ lines. The $k$ \-th line should contain $f(k)$ if $f(k)\neq-\infty$, and `Unreachable` if $f(k)=-\infty$.


### Sample Input 1

```
6 7
10 5 10 3 1 3
13 5 10 2 3 4
15 5 10 7 4 6
3 10 2 4 2 5
7 10 2 3 5 6
5 3 18 2 2 3
6 3 20 4 2 1
```

### Sample Output 1

```
55
56
58
60
17
```

The following diagram shows the trains running in the country (information about arrival and departure times is omitted).

![](https://img.atcoder.jp/abc342/c3007f6fd6e6bffff5483312395e51f6.png)

Consider the latest time at which one can arrive at station $6$ from station $2$. As shown in the following diagram, one can arrive at station $6$ by departing from station $2$ at time $56$ and moving as station $2\rightarrow$ station $3\rightarrow$ station $4\rightarrow$ station $6$.

![](https://img.atcoder.jp/abc342/b6667844f8166458430c27bd93838a76.png)

It is impossible to depart from station $2$ after time $56$ and arrive at station $6$, so $f(2)=56$.

## 题意：
给定一个 N 个点 M 条有向边的图，要求我们从某个点出发到达我们重点的最晚出发时间是多少？

我们这一题需要下面的几个步骤：第一个步骤，把我们从多个点出发转变为从我们的终点出发求最长路。这一点可以画图来理解。
假设我们存在一个原图如下所示：
![[Pasted image 20240228191238.png]]

那么如果我们要求我们的 $a$ 点到我们的 e 点的最晚时间是多少？很显然，我们可以考虑不断地绕路，最后甚至可以不到达我们的 $e$ 点，这个点的结果就是 $\infty$,

这个结果我们可以通过我们的反图来解释：
![[Pasted image 20240228191449.png]]
我们从 E 出发到达 a 的最长路显然是能够被我们不断更新的。

然后，我们就基本确定了我们的方法，就是求我们的反图上的最长路。我们的更新方法就是：
```cpp
if(dist[u]+w[i]>dist[v]){
	dist[v]=dist[u]+w[i];
	p.push_back(dist[v],v);
}
```

然后麻烦的就变成了我们的给出的狗日的条件。我们要求每一个点的最晚出发时间要满足下面的条件：
1. 是在我们的火车发车范围内，也就是要大于我们的最小值，`dist[u]-c>=l`.
2. 只能是我们的某一个具体的火车发车时间，火车发车时间由一个等差数列给出。
对于我们的第一个，我们可以那我们求出来的 `dist[u]+w[i]` 和我们的对应取值进行比较，如果满足条件，我们才用来更新。
对于我们的第二个，我们可以在确定第一个条件满足的情况下，求出我们第一个比这个元素要大的数字是多少，这个位置对应的就是我们的答案。

细节点：
1. 我们更新的时候要用我们的 $dist[u]-c[i]$,这是因为我们的答案要满足：$dist[v]+c[i]\leq dist[u]$,这个条件是因为我们的最长路中 u 点是确定的，而我们的路程也是确定的。
2. 我们比较的时候是吧我们的 `dist_to_update` 和我们的 `k-1` 比较，而不是和我们的 `k` 比较，这是因为我们这里是我们的题目要求，

```cpp
#include <bits/stdc++.h> 
using namespace std;
const int N=2e5+10;
const int M=2e5+10;
#define int long long 
typedef pair<long long,long long> PLL;

int h[N],e[M<<1],ne[M<<1],l[M<<1],d[M<<1],k[M<<1],c[M<<1],dis[N],vis[N],idx;
void add(int a,int b,int ll,int dd,int kk,int cc){
	e[idx]=b;
	ne[idx]=h[a];
	l[idx]=ll;
	d[idx]=dd;
	k[idx]=kk;
	c[idx]=cc;
	h[a]=idx++;
}

signed main(){
	int n,m;
	memset(h,-1,sizeof h);
	cin>>n>>m;
	for(int i=0;i<m;i++){
		int l,d,k,c,a,b;
		cin>>l>>d>>k>>c>>a>>b;
		add(b,a,l,d,k,c);		
	}
	priority_queue<PLL> q;
	dis[n]=4e18+10;
	q.push({4e18+10,n});
	while(q.size()){
		auto u=q.top();
		q.pop();
		int pos=u.second;
		int val=u.first;
		for(int i=h[pos];i!=-1;i=ne[i]){
			int v=e[i];
			int ki=k[i];//最多有多少趟 
			int ci=c[i];//花费 
			int li=l[i];//起始位置 
			int di=d[i];//时间间隔
			
			
			//为什么是val-ci而不是val+ci 
			int dist_to_update=val-ci;
			if(dist_to_update<li){
				continue;
			}
			//为什么是k-1? 
			int k_update=min(ki-1,(dist_to_update-li)/di);
			dist_to_update=k_update*di+li;
			if(dist_to_update>dis[v]){
				dis[v]=dist_to_update;
				q.push({dis[v],v});
			} 
		} 
	}
	for(int i=1;i<n;i++){
		if(dis[i]==0){
			puts("Unreachable");
		}else{
			cout<<dis[i]<<endl;
		}
	}
}
```