You are given a tree, consisting of $n$ vertices, numbered from $1$ to $n$. Every vertex is colored in some color, denoted by an integer from $1$ to $n$.

A simple path of the tree is called beautiful if:

-   it consists of at least $2$ vertices;
-   the first and the last vertices of the path have the same color;
-   no other vertex on the path has the same color as the first vertex.

Count the number of the beautiful simple paths of the tree. Note that paths are considered undirected (i. e. the path from $x$ to $y$ is the same as the path from $y$ to $x$).

## 输入：
**Input**

The first line contains a single integer $t$ ($1 \le t \le 10^4$) — the number of testcases.

The first line of each testcase contains a single integer $n$ ($2 \le n \le 2 \cdot 10^5$) — the number of vertices in the tree.

The second line contains $n$ integers $c_1, c_2, \dots, c_n$ ($1 \le c_i \le n$) — the color of each vertex.

The $i$ \-th of the next $n - 1$ lines contains two integers $v_i$ and $u_i$ ($1 \le v_i, u_i \le n$; $v_i \neq u_i$) — the $i$ \-th edge of the tree.

## 输出：
**Output**

For each testcase, print a single integer — the number of the beautiful simple paths of the tree.


The given edges form a valid tree. The sum of $n$ over all testcases doesn't exceed $2 \cdot 10^5$.

## 题解
我们本题的思路要求我们求出：树上除了两端颜色为 a，其他颜色都为 B 的片段有多少。

我们如果想要得到我们的信息，我们考虑固定一个点为头，考虑以这个头作为起点，我们能够获得的最大的距离是多少。我们于是需要维护下面两个信息：
1. 我们子节点的答案是多少
2. 我们的子结点中，满足末尾颜色和我们的中间所有点颜色都不相同的颜色个数，我们记作预备队。

于是，我们就可以按照下面的做法来统计：
我们用一个 $mp$ 统计我们当前节点的子树中符合要求的节点数有多少，当我们两个地方合并时，如果我们两个点的颜色相同，且不等于我们的根节点，我们直接乘法原理计算即可。

如果我们两个点的颜色相同，但是等于我们的根节点，我们只能使用加法进行计算，因为这种才是合法的。

最后，我们还要把我们的根节点对应的设置为 1.
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10;
int h[N],ne[N<<1],e[N<<1],idx;
int col[N];
map<int,int> cnt[N];
void add(int a,int b){
	e[idx]=b;
	ne[idx]=h[a];
	h[a]=idx++;
}
int ans=0;
void dfs(int u,int fa){
	for(int i=h[u];i!=-1;i=ne[i]){
		int v=e[i];
		if(v==fa){
			continue;
		}
		dfs(v,u);
		if(cnt[v].size()>cnt[u].size()){
			swap(cnt[v],cnt[u]);
		}
		for(auto it:cnt[v]){
			if(cnt[u].count(it.first)&&it.first!=col[u]){
				ans+=p.second*cnt[u][p.first];
				//如果当前点u集合中已经有这个颜色，并且这个颜色不和我们的当前点相同 
			}
			cnt[u][p.first]+=p.second;	
		}
		if(cnt[u].count(col[u])){
			ans+=cnt[u][col[u]];
		}
		c[u][col[u]]=1;
		
	}
	if(tmp){
		res++;
		st[u].clear();
	}
}
void solve(){
	int n;
	cin>>n;
	memset(h,-1,sizeof h);
	for(int i=1;i<=n;i++){
		cin>>col[i];
	}
	for(int i=0;i<n-1;i++){
		int a,b;
		cin>>a>>b;
		add(a,b);
		add(b,a);
	}
	dfs(1,-1);
	cout<<res<<endl;
}
int main(){
	int t;
	cin>>t;
	while(t--){
		solve();
	}
}
```