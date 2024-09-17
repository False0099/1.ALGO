# PermuTree (easy version)

## 题面翻译

**这是问题的简单版本，两个版本之间的唯一区别是 $n$ 的范围和时间限制的不同。**

给定一棵以 $1$ 为根的有根树，你需要给出一个 $1$ 到 $n$ 的排列 $a$，最大化二元组 $(u,v)$ 的数量，满足 $a_u < a_{rm{lca (u, v)}} < a_v$，输出这个最大值。

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
我们考虑计算每一个节点作为我们的 $lca$ 时对我们的答案的贡献是多少。在这里，我们如果一个节点是我们的 lca，那么我们的答案就是：我们的比他小的子节点数 * 比他大的子节点数。

我们以我们的根节点作为我们的起点，我们看我们有几个儿子，对于某一个结点，我们可以使他的一部分子树全都小于他，另一个部分全都大于他，两类子树的节点个数和的乘积就是我们结点的贡献。


而在我们的和一定的情况下，我们一定是两者之差越小，我们的答案越好，这个问题就转变为：在给定我们的某一个子树可以分成若干个
因此我们可以用我们的 0-1 背包来解决。
```cpp
```cpp
#include <bits/stdc++.h>

using namespace std;
const long long N = 5e3+16,MOD = 1e9+7,INF = 1e18;
typedef long long LL;
map<LL,int> mp;
int dx[5]={0,0,1,0,-1},dy[5]={0,1,0,-1,0};
LL n,m,ans;

vector<int> g[N];
LL s[N];  // 存每个子树的节点个数

void dfs(int v,int p){
	vector<LL> a;  // 储存节点v的每个子树的节点个数
	s[v] = 1;
	
	for (auto u : g[v]){
		if (u==p)
			continue;
		dfs(u,v);
		s[v]+=s[u];  // 添加节点个数
		
		a.push_back(s[u]);
	}
	// 预处理
	vector<bool> dp(N);
	dp[0] = 1;
	LL sum = 0;
	for (auto x: a){  // 处理a里能构成的所有数
		sum += x;
		for (int j=N-x-1;j>=0;j--){
			if (dp[j])
				dp[j+x] = 1;
		}
	}
	
	//将当前节点作为最近公共祖先
	//将子节点分成两堆 找对答案贡献最大的即可 
	LL add = 0;
	for (int i=0;i<sum;i++){
		if (dp[i])
			add = max(add,i*(sum-i));
	}
	ans += add;
	dp.clear();
    a.clear();
}


void solve(){
	cin >> n;
	for (int i=2,x;i<=n;i++){
		cin >> x;
		g[x].push_back(i);
	}
    dfs(1,-1);
    cout << ans << '\n';
}

int main (){
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
//	cout<<fixed<<setprecision(12);
//	freopen("D:\\study\\test.txt","r",stdin);
	int _ = 1;
//	cin >> _;
	while (_--){
		solve();
	}
	return 0;
}
```
```