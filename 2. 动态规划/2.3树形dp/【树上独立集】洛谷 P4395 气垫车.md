# [BOI 2003] Gem 气垫车

## 题目描述

给出一棵树，要求你为树上的结点标上权值，权值可以是任意的正整数 

唯一的限制条件是相临的两个结点不能标上相同的权值，要求一种方案，使得整棵树的总价值最小。

## 输入格式

先给出一个数字 N, 代表树上有 N 个点, N<=10000 

下面 N-1 行, 代表两个点相连

## 输出格式

最小的总权值

## 样例 #1

### 样例输入 #1

```
10 
7 5 
1 2 
1 7 
8 9 
4 1 
9 7 
5 6 
10 2 
9 3
```

### 样例输出 #1

```
14
```

## 提示

本题已经添加数据，但考虑到题目年代较为久远（毕竟是 2003 年的 BOI 了）以及洛谷神速评测姬，将此题时限修改为 500 ms。


## 题解
注意：这一题不能采用我们的 0-1 染色法，我们有反例：10 1 2 1 3 1 4 1 5 1 6 2 7 2 8 2 9 2 10。

我们这一题可以采用我们的树形 dp，因为我们要上我们的总价值最小，我们可以枚举我们每一个点的权值是多少，然后再去转移子节点不为这个权值即可。我们设 $dp[i][0]$,为我们把根节点染为 i 时，我们子树的最大值。之后，我们再用一个转移，求出我们子节点为 k 时，我们获得的最小是多少，然后再转移即可。
$dp[i][j]+=min(dp[son][\neq j])$
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int head[N],ver[N],net[N],tot;
int n,f[N][20],ans=0x3f3f3f3f;
void add(int a,int b){
	net[++tot]=head[a];
	head[a]=tot;
	ver[tot]=b;
}
void dfs(int x,int fa){
	for(int i=1;i<=15;i++){
		f[x][i]=i;//初始化 
	}
	for(int i=head[x];i;i=net[i]){
		int v=ver[i];
		if(v==fa)continue;
		dfs(v,x);
		for(int j=1;j<=15;j++){
			int minn=0x3f3f3f3f;
			for(int k=1;k<=15;k++){//找最小值，并且不与当前值相同 
				if(j!=k)minn=min(minn,f[v][k]);
			}
			f[x][j]+=minn;
		}
	}
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<n;i++){
		int a,b;
		scanf("%d%d",&a,&b);
		add(a,b);
		add(b,a);
	}
	dfs(1,0);
	for(int i=1;i<=15;i++){
		ans=min(ans,f[1][i]);//找最小值 
	}
	printf("%d",ans);
	return 0;
}
```