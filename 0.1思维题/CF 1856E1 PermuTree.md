# PermuTree (easy version)

## 题面翻译

**这是问题的简单版本，两个版本之间的唯一区别是 $n$ 的范围和时间限制的不同。**

给定一棵以 $1$ 为根的有根树，你需要给出一个 $1$ 到 $n$ 的排列 $a$，最大化二元组 $(u,v)$ 的数量，满足 $a_u < a_{\rm
{lca (u, v)}} < a_v$，输出这个最大值。

$2 \leq n \leq 5000$。

## 题目描述

This is the easy version of the problem. The differences between the two versions are the constraint on $ n $ and the time limit. You can make hacks only if both versions of the problem are solved.

You are given a tree with $ n $ vertices rooted at vertex $ 1 $ .

For some permutation $ ^\dagger $ $ a $ of length $ n $ , let $ f (a) $ be the number of pairs of vertices $ (u, v) $ such that $ a_u < a_{\operatorname{lca}(u, v)} < a_v $ . Here, $ \operatorname{lca}(u, v) $ denotes the [lowest common ancestor](https://en.wikipedia.org/wiki/Lowest_common_ancestor) of vertices $ u $ and $ v $ .

Find the maximum possible value of $ f (a) $ over all permutations $ a $ of length $ n $ .

 $ ^\dagger $ A permutation of length $ n $ is an array consisting of $ n $ distinct integers from $ 1 $ to $ n $ in arbitrary order. For example, $ [2,3,1,5,4] $ is a permutation, but $ [1,2,2] $ is not a permutation ( $ 2 $ appears twice in the array), and $ [1,3,4] $ is also not a permutation ( $ n=3 $ but there is $ 4 $ in the array).

## 输入格式

The first line contains a single integer $ n $ ( $ 2 \le n \le 5000 $ ).

The second line contains $ n - 1 $ integers $ p_2, p_3,\ldots, p_n $ ( $ 1 \le p_i < i $ ) indicating that there is an edge between vertices $ i $ and $ p_i $ .

## 输出格式

Output the maximum value of $ f (a) $ .

## 样例 #1

### 样例输入 #1

```
5
1 1 3 3
```

### 样例输出 #1

```
4
```

## 样例 #2

### 样例输入 #2

```
2
1
```

### 样例输出 #2

```
0
```

## 样例 #3

### 样例输入 #3

```
6
1 2 2 1 5
```

### 样例输出 #3

```
7
```

## 样例 #4

### 样例输入 #4

```
4
1 1 1
```

### 样例输出 #4

```
2
```

## 提示

The tree in the first test:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1856E1/b4446034dab04a6ae6c9b21c7c1f4229d9a4c572.png)One possible optimal permutation $ a $ is $ [2, 1, 4, 5, 3] $ with $ 4 $ suitable pairs of vertices:

- $ (2, 3) $ , since $ \operatorname{lca}(2, 3) = 1 $ and $ 1 < 2 < 4 $ ,
- $ (2, 4) $ , since $ \operatorname{lca}(2, 4) = 1 $ and $ 1 < 2 < 5 $ ,
- $ (2, 5) $ , since $ \operatorname{lca}(2, 5) = 1 $ and $ 1 < 2 < 3 $ ,
- $ (5, 4) $ , since $ \operatorname{lca}(5, 4) = 3 $ and $ 3 < 4 < 5 $ .

The tree in the third test:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1856E1/d99652a679d9214ec6283dd777f9d3b7f1434695.png)The tree in the fourth test:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1856E1/1b3604b93549da62e326378a176bbc03c4448da2.png)

## 题解
我们以我们的根节点作为我们的起点，我们看我们有几个儿子，对于某一个结点，我们可以使他的一部分子树全都小于他，另一个部分全都大于他，两类子树的节点个数和的乘积就是我们结点的贡献，因此我们可以用我们的 0-1 背包来解决。
```cpp
#include <bits/stdc++.h>
using namespace std;
#define rep(i,l,r) for(i=l;i<=r;++i)
#define req(i,r,l) for(i=r;i>=l;--i)
int t,n,i,j,k,l,r,ret,maxn,now,kk;long long ans;
const int N=5e4+5;
vector<int> e[N];
bool f[N];
int a[N],siz[N];
inline void dfs0(int u,int fa)
{
	siz[u]=1;
	if(e[u].empty())
	{
		siz[u]=1;return ;}
	for(auto nxt:e[u])
	{
		if(u==fa)continue;
		dfs0(nxt,u);
		siz[u]+=siz[nxt];
	}
	return ;
}
inline void dfs1(int u,int fa)
{
	f[0]=true;
	for(auto nxt:e[u])
	{
		if(u==fa)continue;
//		rep(j,0,siz[u])f[tot][j]=f[tot-1][j];
		req(j,siz[u],siz[nxt])
			f[j]|=f[j-siz[nxt]];
	}
//	printf("%d\n",u);
//	rep(i,1,n)printf("%d ",f[i]);
//	puts("");
	int bst=0;
	rep(i,1,siz[u])if(f[i])bst=max(bst,i*(siz[u]-1-i));
//	printf("%d %d %d\n",u,siz[u],bst);
	ans+=bst;
	memset(f,0,sizeof f);
	for(auto nxt:e[u])
	{
		if(u==fa)continue;
		dfs1(nxt,u);
	}
	return ;
}
int main()
{
	ans=0;int x;
	scanf("%d",&n);
	rep(i,2,n)
	{
		scanf("%d",&x);
		e[x].emplace_back(i);
	}
	dfs0(1,0);
	dfs1(1,0);
	printf("%lld\n",ans);
	return 0;
}
```