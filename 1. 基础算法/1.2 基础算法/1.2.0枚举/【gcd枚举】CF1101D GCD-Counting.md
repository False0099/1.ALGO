# GCD Counting

## 题面翻译

题意简述

给出一棵树，树有点权，求树上的一条链满足：链上所有点的点权的 $gcd>1$ 且链上的点数最多．注意一个点也可以构成一条链．

输入数据

第一行一个正整数 $n(1 \leq n \leq 2 \times 10^5)$ 表示树的点数

接下来一行 $n$ 个正整数 $a_i(1 \leq a_i \leq 2 \times 10^5)$ 表示每个点的点权

接下来 $n-1$ 行每行两个正整数 $u,v(1 \leq u,v \leq n , u \neq v)$ 表示树上的一条边．

输出数据

输出一行一个整数，如果不存在这样的链输出 ```0```，否则输出最长的可能链长．

## 题目描述

You are given a tree consisting of $ n $ vertices. A number is written on each vertex; the number on vertex $ i $ is equal to $ a_i $ .

Let's denote the function $ g (x, y) $ as the greatest common divisor of the numbers written on the vertices belonging to the simple path from vertex $ x $ to vertex $ y $ (including these two vertices). Also let's denote $ dist (x, y) $ as the number of vertices on the simple path between vertices $ x $ and $ y $ , including the endpoints. $ dist (x, x) = 1 $ for every vertex $ x $ .

Your task is calculate the maximum value of $ dist (x, y) $ among such pairs of vertices that $ g (x, y) > 1 $ .

## 输入格式

The first line contains one integer $ n $ — the number of vertices $ (1 \le n \le 2 \cdot 10^5) $ .

The second line contains $ n $ integers $ a_1 $ , $ a_2 $ , ..., $ a_n $ $ (1 \le a_i \le 2 \cdot 10^5) $ — the numbers written on vertices.

Then $ n - 1 $ lines follow, each containing two integers $ x $ and $ y $ $ (1 \le x, y \le n, x \ne y) $ denoting an edge connecting vertex $ x $ with vertex $ y $ . It is guaranteed that these edges form a tree.

## 输出格式

If there is no pair of vertices $ x, y $ such that $ g (x, y) > 1 $ , print $ 0 $ . Otherwise print the maximum value of $ dist (x, y) $ among such pairs.

## 样例 #1

### 样例输入 #1

```
3
2 3 4
1 2
2 3
```

### 样例输出 #1

```
1
```

## 样例 #2

### 样例输入 #2

```
3
2 3 4
1 3
2 3
```

### 样例输出 #2

```
2
```

## 样例 #3

### 样例输入 #3

```
3
1 1 1
1 2
2 3
```

### 样例输出 #3

```
0
```

## 题解
本题，我们不难发现，因为我们要求我么的路径上的 gcd 大于 1 的，我们注意到我们的**gcd**可以暴力的枚举，因为我们的所有可能的 gcd 种类是 $\log a_{i}$ 级别的。于是，我们就可以通过我们的暴力树上合并的方式来进行。

具体来说，我们把我们的操作分为下面的两类：
第一类：我们把我们原来的路径和我们的子节点的路径合并，这里我们的时间复杂度是 $o(siz^2)$ 的，也就是我们的 $o(\log^2)$ 的，（也就是以我们的这个点为 lca 的路径）
第二类：用我们的子路径更新我们与根节点的路径。（也就是以我们的某一个点作为顶点的路径的 lca）

综上，我们可以写出我们的最终的代码如下所示：
```
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10;
int w[N],idx;
int e[N<<1],ne[N<<1],h[N];
void add(int a,int b){
	e[idx]=b;
	ne[idx]=h[a];
	h[a]=idx++;
}
int ans=0;
map<int,int> gcd_l[N];
void dfs(int u,int fa){
	map<int,int> rest;//表示以i为顶点的路径总数 
	rest[w[u]]=1;
	if(w[u]!=1){
		ans=max(ans,rest[w[u]]);
	}
	//ans=max(ans,rest[w[u]]);
	for(int i=h[u];i!=-1;i=ne[i]){
		int v=e[i];
		if(v==fa){
			continue;
		}
		dfs(v,u);
		for(auto uu:rest){
			for(auto vv:gcd_l[v]){
				int num1=uu.first;
				int num2=vv.first;
				int count1=uu.second;
				int count2=vv.second;
				if(__gcd(num1,num2)==1){
					continue;
				}else{
					ans=max(ans,count1+count2);
				}
			}
		}
		for(auto vv:gcd_l[v]){
			int num1=vv.first;
			int count1=vv.second;
			rest[__gcd(num1,w[u])]=max(rest[__gcd(num1,w[u])],count1+1);
		}
	}
	gcd_l[u]=rest; 
}
signed main(){
	ios::sync_with_stdio(false),cin.tie(0);
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>w[i];
	}
	memset(h,-1,sizeof h);
	for(int i=1;i<n;i++){
		int a,b;
		cin>>a>>b;
		add(a,b);
		add(b,a); 
	}
	dfs(1,0);
	if(ans==0){
		cout<<"0"<<endl;
	}else{
		cout<<ans<<endl;
	}
}
```