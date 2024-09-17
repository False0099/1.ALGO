# [USACO 12 OPEN] Balanced Cow Subsets G

## 题面翻译

我们定义一个奶牛集合 $S$ 是平衡的，当且仅当满足以下两个条件：

- $S$ 非空。
- $S$ 可以被**划分**成两个集合 $A,B$，满足 $A$ 里的奶牛产奶量之和等于 $B$ 里的奶牛产奶量之和。划分的含义是，$A\cup B=S$ 且 $A\cap B=\varnothing$。

现在给定大小为 $n$ 的奶牛集合 $S$，询问它有多少个子集是平衡的。请注意，奶牛之间是互不相同的，但是它们的产奶量可能出现相同。

### 输入格式

第一行一个整数 $n$，表示奶牛的数目。

第 $2$ 至 $n+1$ 行，每行一个数 $a_i$，表示每头奶牛的产奶量。

### 输出格式

输出一个数表示方案总数。

### 样例解释

共存在三种方案。集合 $\{1,2,3\}$ 可以划分为 $\{1,2\}$ 与 $\{3\}$；集合 $\{1,3,4\}$ 可以划分为 $\{1,3\}$ 与 $\{4\}$；集合 $\{1,2,3,4\}$ 可以划分为 $\{1,4\}$ 与 $\{2,3\}$，共 $3$ 种子集。

### 数据范围及约定

对于全部数据，保证 $1\le n\le 20$，$1\le a_i\le 10^8$。

## 题目描述

Farmer John's owns N cows (2 <= N <= 20), where cow i produces M (i) units of milk each day (1 <= M (i) <= 100,000,000).  FJ wants to streamline the process of milking his cows every day, so he installs a brand new milking machine in his barn.  Unfortunately, the machine turns out to be far too sensitive: it only works properly if the cows on the left side of the barn have the exact same total milk output as the cows on the right side of the barn!

Let us call a subset of cows "balanced" if it can be partitioned into two groups having equal milk output.  Since only a balanced subset of cows can make the milking machine work, FJ wonders how many subsets of his N cows are balanced.  Please help him compute this quantity.

## 输入格式

\* Line 1: The integer N.

\* Lines 2.. 1+N: Line i+1 contains M (i).

## 输出格式

\* Line 1: The number of balanced subsets of cows.

## 样例 #1

### 样例输入 #1

```
4 
1 
2 
3 
4
```

### 样例输出 #1

```
3
```

## 提示

There are 4 cows, with milk outputs 1, 2, 3, and 4.


There are three balanced subsets: the subset {1,2,3}, which can be partitioned into {1,2} and {3}, the subset {1,3,4}, which can be partitioned into {1,3} and {4}, and the subset {1,2,3,4} which can be partitioned into {1,4} and {2,3}.

## 题解
我们这一题要求，我们划分出多少个集合，使得我们划分后两个集合的大小是相等的。

这种关于子集的问题，我们显然可以通过 dfs 枚举所有选或不选的方案，然后再根据到最后是我们的划分是否相等来判断。对于我们的每个位置，我们有下面几种操作：
1. 添加到大集合，并且选到我们的相反的结合中
2. 添加到大集合，并且选到我们目前的集合
3. 不添加到大集合
```cpp
void dfs(int pos,int sum){
	if(pos==n){
		if(sum==0){
			cnt++;
		}
		return;
	}
	dfs(pos+1,sum+a[i]);
	dfs(pos+1,sum-a[i]);
	dfs(pos+1,sum);
}
```

但是这样我们的时间复杂度会超时，无法接受，我们于是考虑把 n 头奶牛分成两半，前一半中在第一组中放的数和为 a，在第二组中放的数为 b，后一半中，我们在第一组中放的数和为 c, 在第二组中我们放的数为 d。那么，我们就必须有 $a+c=b+d$,由于我们需要对每一半分开处理，所以考虑将同一半的放在一起，即 $a-b=d-c$,因此，我们只需要维护在每一半中和为 $a-b$ 的方案有多少种，然后再进行组合即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,N,a[21],ans[2000001],s,tot;
vector<int> p[2000001];
map<int,int> b;//因为可能有负数，所以用map更加稳妥
void dfs1(int x,int sum,int now){//对前一半搜索，x表示到了第几个，sum表示a-b的值，now表示状压，取了那些数
	if(x>N){
		if(b[sum]==0) b[sum]=++tot;//离散化
		p[b[sum]].push_back(now);//放入方案
		return;
	}
	dfs1(x+1,sum+a[x],now|(1<<(x-1)));  //三种情况讨论
    dfs1(x+1,sum-a[x],now|(1<<(x-1)));  
    dfs1(x+1,sum,now);
} 
void dfs2(int x,int sum,int now){//对后一半搜索，同上
	if(x>n){ 
		int t=b[sum];
		if(t!=0)  for(int i=0;i<p[t].size();i++)  ans[p[t][i]|now]=1;//对于每一种可能的组合，将值赋为1，注意，题目中要求的方案数为取数的方案数而不是分数的方案数，因此不是+1而是=1
		return;
	}
	dfs2(x+1,sum+a[x],now|(1<<(x-1)));  
    dfs2(x+1,sum-a[x],now|(1<<(x-1)));  
    dfs2(x+1,sum,now);
} 
int main(){
	scanf("%d",&n); N=n/2;
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	dfs1(1,0,0);
	dfs2(N+1,0,0);
	for(int i=1;i<=(1<<n);i++)s+=ans[i];
	printf("%d",s);
} 
```