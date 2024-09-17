# XOR Tree

## 题面翻译

你有一棵无根树，点数为 $n$，每个点有个点权 $a_u$，定义一条路径 $P(u,v)$ 的权值为经过的**所有点的点权的异或和**。定义一棵树是合法的，当且仅当树上所有**简单路径**（只经过每个点一次的路径）的的权值都不为 $0$。

你可以对权值进行修改，可以改成**任意正整数**，问最少修改多少次才能让这棵树合法。

输出最小修改次数。

$n\leq 2\times 10^5,a_i\leq 2^{30}$

## 题目描述

You are given a tree consisting of $ n $ vertices. A number is written on each vertex; the number on vertex $ i $ is equal to $ a_i $ .

Recall that a simple path is a path that visits each vertex at most once. Let the weight of the path be the bitwise XOR of the values written on vertices it consists of. Let's say that a tree is good if no simple path has weight $ 0 $ .

You can apply the following operation any number of times (possibly, zero): select a vertex of the tree and replace the value written on it with an arbitrary positive integer. What is the minimum number of times you have to apply this operation in order to make the tree good?

## 输入格式

The first line contains one integer $ n $ ( $ 1 \le n \le 2 \cdot 10^5 $ ) — the number of vertices.

The second line contains $ n $ integers $ a_1 $ , $ a_2 $ , ..., $ a_n $ ( $ 1 \le a_i < 2^{30} $ ) — the numbers written on vertices.

Then $ n - 1 $ lines follow, each containing two integers $ x $ and $ y $ ( $ 1 \le x, y \le n; x \ne y $ ) denoting an edge connecting vertex $ x $ with vertex $ y $ . It is guaranteed that these edges form a tree.

## 输出格式

Print a single integer — the minimum number of times you have to apply the operation in order to make the tree good.

## 样例 #1

### 样例输入 #1

```
6
3 2 1 3 2 1
4 5
3 4
1 4
2 1
6 1
```

### 样例输出 #1

```
2
```

## 样例 #2

### 样例输入 #2

```
4
2 1 1 1
1 2
1 3
1 4
```

### 样例输出 #2

```
0
```

## 样例 #3

### 样例输入 #3

```
5
2 2 2 2 2
1 2
2 3
3 4
4 5
```

### 样例输出 #3

```
2
```

## 提示

In the first example, it is enough to replace the value on the vertex $ 1 $ with $ 13 $ , and the value on the vertex $ 4 $ with $ 42 $ .


## 题解
首先，我们本题有一个性质：如果我们有一条非法路径，我们想要修改的最少，**一定是在我们的路径 $lca$ 上修改**，能让我们的次数最少，因此，我们只需要找到所有非法路径和对应的 $lca$ 即可。这一点，我们可以考虑反向思考，我们原来是要求我们的边，**我们可以考虑找到我们的每一个点，然后判断一下这个点是否需要我们修改**，这一点我们可以通过枚举我们的左右子树路径上的异或和放到一个 set 中，统计我们每一个子树中的 set 值，如果发现了非法路径，我们直接答案++，清除我们的所有边。否则，我们就把小集合并入大集合。
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10;
int h[N],ne[N<<1],e[N<<1],idx;
int a[N],dist[N];
set<int> st[N];
void add(int a,int b){
	e[idx]=b;
	ne[idx]=h[a];
	h[a]=idx++;
}
int res=0;
void dfs(int u,int fa){
	st[u].insert(dist[u]);
	bool tmp=0;
	for(int i=h[u];i!=-1;i=ne[i]){
		int v=e[i];
		if(v==fa){
			continue;
		}
		dist[v]=dist[u]^a[v];
		dfs(v,u);
		if(st[v].size()>st[u].size()){
			swap(st[v],st[u]);
		}
		for(int it:st[v]){
			if(st[u].count(a[u]^it)){
				tmp=1;		
			}
		}
		for(int it:st[v]){
			st[u].insert(it);
		}
	}
	if(tmp){
		res++;
		st[u].clear();
	}
}
signed main(){
	int n;
	cin>>n;
	memset(h,-1,sizeof h);
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=0;i<n-1;i++){
		int a,b;
		cin>>a>>b;
		add(a,b);
		add(b,a);
	}
	dist[1]=a[1];
	dfs(1,-1);
	cout<<res<<endl;
}
```


