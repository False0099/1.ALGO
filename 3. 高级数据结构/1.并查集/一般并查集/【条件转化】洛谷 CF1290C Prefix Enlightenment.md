# Prefix Enlightenment

## 题面翻译

给定一个长度为 $n$ 的 01 串 $S$，和 $k$ 个 $S$ 的下标子集，且任意三个子集的交集为空集。一次操作可以选择一个子集，将子集中的下标对应的 $S_i$ 取反。令 $m_i$ 为让 $S_{1 \sim i} = 1$ 的最少操作次数，求出所有的 $m_i$，保证有方案。

$1 \leq n,k \leq 3 \times 10^5$。

## 题目描述

There are $ n $ lamps on a line, numbered from $ 1 $ to $ n $ . Each one has an initial state off ( $ 0 $ ) or on ( $ 1 $ ).

You're given $ k $ subsets $ A_1, \ldots, A_k $ of $ \{1, 2, \dots, n\} $ , such that the intersection of any three subsets is empty. In other words, for all $ 1 \le i_1 < i_2 < i_3 \le k $ , $ A_{i_1} \cap A_{i_2} \cap A_{i_3} = \varnothing $ .

In one operation, you can choose one of these $ k $ subsets and switch the state of all lamps in it. It is guaranteed that, with the given subsets, it's possible to make all lamps be simultaneously on using this type of operation.

Let $ m_i $ be the minimum number of operations you have to do in order to make the $ i $ first lamps be simultaneously on. Note that there is no condition upon the state of other lamps (between $ i+1 $ and $ n $ ), they can be either off or on.

You have to compute $ m_i $ for all $ 1 \le i \le n $ .

## 输入格式

The first line contains two integers $ n $ and $ k $ ( $ 1 \le n, k \le 3 \cdot 10^5 $ ).

The second line contains a binary string of length $ n $ , representing the initial state of each lamp (the lamp $ i $ is off if $ s_i = 0 $ , on if $ s_i = 1 $ ).

The description of each one of the $ k $ subsets follows, in the following format:

The first line of the description contains a single integer $ c $ ( $ 1 \le c \le n $ ) — the number of elements in the subset.

The second line of the description contains $ c $ distinct integers $ x_1, \ldots, x_c $ ( $ 1 \le x_i \le n $ ) — the elements of the subset.

It is guaranteed that:

- The intersection of any three subsets is empty;
- It's possible to make all lamps be simultaneously on using some operations.

## 输出格式

You must output $ n $ lines. The $ i $ -th line should contain a single integer $ m_i $ — the minimum number of operations required to make the lamps $ 1 $ to $ i $ be simultaneously on.

## 样例 #1

### 样例输入 #1

```
7 3
0011100
3
1 4 6
3
3 4 7
2
2 3
```

### 样例输出 #1

```
1
2
3
3
3
3
3
```

## 样例 #2

### 样例输入 #2

```
8 6
00110011
3
1 3 8
5
1 2 5 6 7
2
6 8
2
3 5
2
4 7
1
2
```

### 样例输出 #2

```
1
1
1
1
1
1
4
4
```

## 样例 #3

### 样例输入 #3

```
5 3
00011
3
1 2 3
1
4
3
3 4 5
```

### 样例输出 #3

```
1
1
1
1
1
```

## 样例 #4

### 样例输入 #4

```
19 5
1001001001100000110
2
2 3
2
5 6
2
8 9
5
12 13 14 15 16
1
19
```

### 样例输出 #4

```
0
1
1
1
2
2
2
3
3
3
3
4
4
4
4
4
4
4
5
```

## 提示

In the first example:

- For $ i = 1 $ , we can just apply one operation on $ A_1 $ , the final states will be $ 1010110 $ ;
- For $ i = 2 $ , we can apply operations on $ A_1 $ and $ A_3 $ , the final states will be $ 1100110 $ ;
- For $ i \ge 3 $ , we can apply operations on $ A_1 $ , $ A_2 $ and $ A_3 $ , the final states will be $ 1111111 $ .

In the second example:

- For $ i \le 6 $ , we can just apply one operation on $ A_2 $ , the final states will be $ 11111101 $ ;
- For $ i \ge 7 $ , we can apply operations on $ A_1, A_3, A_4, A_6 $ , the final states will be $ 11111111 $ .

## 题解
我们对于每一个开关，我们有两种操作，一种是开，一种是关，这是我们并查集的建立。
首先，我们贪心的，令**每一类操作只操作一次**，
考虑当中被两种操作所覆盖的区域，我们记被操作的区域上的数字为 $a$,我们的操作种类分别是 $i,j$，操作记为 1，不操作记为 0。
如果被操作区域的起始值为 1，那么我们 i 和 j 必须同时操作或同时不操作，才能保证最短，因此我们在 $i_{1}$ 和 $j_{1}$ ，$i_{0}$ 和 $j_{0}$ 连一条边。
如果被操作区域的起始值为 0，那么我们 i 和 j 必须一个操作一个不操作，因此我们在 $i_{1}$ 和 $j_{0}$, $i_{0}$ 和 $j_{1}$ 上连一条边。

考虑当中被一种操作覆盖的区域，如果该区域的初始值为 0，那么我们这个点的操作一定要选，如果该区域的初始值为 1，那么我们这个点的操作一定不能选。

```cpp
#include <bits/stdc++.h>
#define MAXN 100006
using namespace std;
typedef long long ll;
int N,M;
char s[MAXN];
int fa[MAXN],sz[MAXN];
int main(){
	cin>>N>>M;
	cin>>s+1;
	int n,j;
	for(int i=1;i<=m;i++){
		cin>>n;
		while(n--){
			cin>>j;
			adj[j].push_back(i);
		}
	}
	for(int i=1;i<=2*M;i++){
		if(adj[i].size()==1){//如果只被一个操作控制 
			x=adj[i][0];
			if(vis[x]) ans-=min(sz[findR(x)],sz[findR(x+M)]);
			if(s[i]=='0') sz[findR(x+M)]=inf;
			else sz[findR(x)]=inf;
			ans+=min(sz[findR(x)],sz[findR(x+M)]);
			vis[x]=1;
		}
		
		else if(adj[i].size()==2){
			x=adj[i][0],y=adj[i][1];
			if(chk(x,y)||chk(x,y+M)){
				continue;
			}
			if(vis[x]) ans-=min(sz[findR(x)],sz[findR(x+M)]);
			if(vis[y]) ans-=min(sz[findR(y)],sz[findR(y+M)]);
			if(s[i]=='1'){
				merge(x,y);
				merge(x+M,y+M);
			}else{
				merge(x,y+M);
				merge(x+M,y);
			}
			ans+=min(sz[findR(x)],sz[findR(x+M)]);
			vis[x]=vis[y]=1;
		}
		cout<<ans<<endl;
	}
}
 
```