# A Growing Tree

## 题面翻译

$T$ 组数据

给定一棵树，初始只含一个节点，编号为 $1$ ，初始权值为 $0$ ，设树的大小为 $sz$ 。

$q$ 次操作：
	
- $1\ \ x$ ，在 $s$ 下挂一个节点，编号为 $sz+1$ ，初始权值为 $0$ 。
    
- $2\ \ x\ v$ ，将当前 $x$ 子树中节点的权值加上 $v$ 。
    
求所有操作完成后每个节点的点权。

$1\le T\le 10^4$ , $1 \le\sum q\le 5\times 10^5$

## 题目描述

You are given a rooted tree with the root at vertex $ 1 $ , initially consisting of a single vertex. Each vertex has a numerical value, initially set to $ 0 $ . There are also $ q $ queries of two types:

- The first type: add a child vertex with the number $ sz + 1 $ to vertex $ v $ , where $ sz $ is the current size of the tree. The numerical value of the new vertex will be $ 0 $ .
- The second type: add $ x $ to the numerical values of all vertices in the subtree of vertex $ v $ .

After all queries, output the numerical value of all of the vertices in the final tree.

## 输入格式

The first line contains a single integer $ T $ ( $ 1 \leq T \leq 10^4 $ ) — the number of test cases. The descriptions of the test cases follow.

The first line of each test case contains a single integer $ q $ ( $ 1 \leq q \leq 5 \cdot 10^5 $ ) — the number of queries.

The following $ q $ lines can fall into two cases:

- The first type of query: The $ i $ -th line contains two integers $ t_i $ ( $ t_i = 1 $ ), $ v_i $ . You need to add a child with the number $ sz + 1 $ to vertex $ v_i $ , where $ sz $ is the current size of the tree. It is guaranteed that $ 1 \leq v_i \leq sz $ .
- The second type of query: The $ i $ -th line contains three integers $ t_i $ ( $ t_i = 2 $ ), $ v_i $ , $ x_i $ ( $ -10^9 \leq x_i \leq 10^9 $ ). You need to add $ x_i $ to all numerical values of vertices in the subtree of $ v_i $ . It is guaranteed that $ 1 \leq v_i \leq sz $ , where $ sz $ is the current size of the tree.

It is guaranteed that the sum of $ q $ across all test cases does not exceed $ 5 \cdot 10^5 $ .

## 输出格式

For each test case, output the numerical value of each vertex of the final tree after all queries have been performed.

## 样例 #1

### 样例输入 #1

```
3
9
2 1 3
1 1
2 2 1
1 1
2 3 2
1 3
2 1 4
1 3
2 3 2
5
2 1 1
1 1
2 1 -1
1 1
2 1 1
5
1 1
1 1
2 1 1
2 1 3
2 2 10
```

### 样例输出 #1

```
7 5 8 6 2 
1 0 1 
4 14 4
```

## 提示

In the first case, the final tree with the assigned numerical values will look like this:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1891F/450cfb88a93df41b0d4048df05e79ddc23a1fc76.png) The final tree with the assigned numerical values

## 题解
我们考虑到我们如果正着计算的话会非常的麻烦，于是我们考虑能否倒序计算，发现是可以的，原因有二：
第一点：我们最后的询问只有一个，并不是对于每一个点都进行询问，当然，我们每一次操作完后再去进行一个询问也是可以的，我们只需要把我们的询问离线即可。

第二点：我们的单点的权值并不受我们的时间的影响，也就是我们的权值是一个与操作顺序无关的变量。

于是，我们就可以先按照我们的最后结构见一棵树，然后我们每一次子树加就直接加上我们的子树即可，我们之后每一次如果想要删除掉我们的某一个结点，那么我们就直接计算出这一个节点的权值即可，然后后续不在考虑这一个节点的全职即可。

**注意，本题我们要求的是子树上的加减，于是我们需要通过我们的 dfn 序来进行子树加减操作**。

剩下的区间加，单点求和，我们只需要通过我们的线段树即可。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+2;
int T,n,m,k,a[N],f[N],g[N],t[N],u[N],v[N];
vector<int>e[N];
void add(int x,int y){for(;x<=n;x+=(x&-x))a[x]+=y;}
void add(int l,int r,int c){add(l,c),add(r+1,-c);}
int qry(int x,int s=0){for(;x;x-=(x&-x))s+=a[x];return s;}
void dfs(int x){
	f[x]=g[x]=++k;
	for(int i:e[x])
		dfs(i),g[x]=max(g[x],g[i]);
}
void solve(){
	for(int i=1;i<=n;i++)
		e[i].clear(),a[i]=0;
	scanf("%lld",&m),n=1,k=0;
	for(int i=1;i<=m;i++){
		scanf("%lld%lld",t+i,u+i);
		if(t[i]>1)scanf("%lld",v+i);
		else e[u[i]].push_back(++n),u[i]=n;
	}
	dfs(1);
	for(int i=1;i<=m;i++)
		add(f[u[i]],g[u[i]],t[i]<2?-qry(f[u[i]]):v[i]);
	for(int i=1;i<=n;i++)printf("%lld ",qry(f[i]));
	printf("\n");
}
signed main(){
	scanf("%lld",&T);
	while(T--)solve();
	return 0;
}
```