Consider a rooted tree consisting of �n vertices where the first vertex is the root.The �i-th vertex is endowed with the value ��vi​.

Now you are given a positive integer �k.An ordered pair of vertices (�,�)(x,y), indicating the �x-th and the �y-th vertices in the tree, is valid if it satisfies the following conditions:

- �≠�x=y;
- The �x-th vertex is not an ancestor of the �y-th one;
- The �y-th vertex is not an ancestor of the �x-th one;
- The length of the shortest path connection these two vertices is up to �k;
- Take the value of the lowest common ancestor of these two vertices, denoted by ��vz​. Then ��+��=2��vx​+vy​=2vz​.

Can you calculate the total number of valid pairs of vertices in this tree?

### Input

The first line contains two integers �n and � (1≤�,�≤105)k (1≤n,k≤105) which is described as above.

The second line contains �n integers, the �i-th of which is the value of the �i-th vertex ��vi​ (0≤��≤�0≤vi​≤n).

The third line contains �−1n−1 integers, the �i-th of which represents the index of the parent vertex of the (�+1)(i+1)-th vertex.

We guarantee that the given tree is indeed a tree.

### Output

Output the number of valid pairs of vertices in a line.

Two pairs (�1,�1)(x1​,y1​) and (�2,�2)(x2​,y2​) are regarded as the same if �1=�2x1​=x2​ and �1=�2y1​=y2​.

### Sample 1

|Inputcopy|Outputcopy|
|---|---|
|3 2<br>1 2 3<br>1 1|0|

  

### Sample 2

|Inputcopy|Outputcopy|
|---|---|
|3 1<br>2 1 3<br>1 1|0|

  

### Sample 3

|Inputcopy|Outputcopy|
|---|---|
|3 2<br>2 1 3<br>1 1|2|
## 题意
![[Pasted image 20240222174848.png]]

## 题解
我们考虑**枚举我们的 lca 节点**，然后我们再去枚举我们的各个子树当中的条件是否是满足条件的。

于是，我们就需要一种数据结构，能够统计我们子树中固定深度下，我们的各个权值有哪些。

这里，我们需要解决两个问题，
1. 怎么求我们的一定深度，
2. 怎么解决我们的权值匹配

考虑**暴力**法：我们枚举我们的根节点和我们的其中一个子节点，然后根据我们两个点之间的信息查找符合要求的节点。

但这里我们求的是 <=k, 考虑到这个问题类似于我们的一个主席树所能实现的问题。于是我们就可以通过我们的主席树来实现，我们以权值 $val[i]$ 为版本，每个版本内维护一个权值线段树，权值线段树维护我们**这一个权值在各个高度是否出现过**。


```cpp
void cal(int u, int lca){ //u是我们枚举的子节点，lca顾名思义 
	int tar = w[lca]*2 - w[u];//目标权值  
	int depl = dep[lca]+1;  //深度范围
	int depr = dep[lca]+(k-(dep[u]-dep[lca]));//深度范围  
	depr = min(depr, n);  
	if(depl <= depr && 0 <= tar && tar <= n) ans += query(depl,depr,1,n,root[tar]);  
	for(auto v:vc[u]) cal(v, lca);  
}
```

但是如果我们这么做，我们是会超时的，所以我们这里选择采用我们的启发式合并（树链剖分）来优化我们的合并过程

```cpp
#pragma GCC optimize(3)
#include <bits/stdc++.h>
#define debug(x) cout<<#x<<":"<<x<<endl;
#define dl(x) printf("%lld\n",x);
#define di(x) printf("%d\n",x);
#define _CRT_SECURE_NO_WARNINGS
#define pb push_back
#define mp make_pair
#define all(x) (x).begin(),(x).end()
#define fi first
#define se second
#define SZ(x) ((int)(x).size())
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> PII;
typedef vector<int> VI;
const int INF = 0x3f3f3f3f;
const int N = 1e5 + 50;
const ll mod = 1000000007;
const double eps = 1e-9;
const double PI = acos(-1);
template<typename T>inline void read(T &a) {
	char c = getchar(); T x = 0, f = 1; while (!isdigit(c)) {if (c == '-')f = -1; c = getchar();}
	while (isdigit(c)) {x = (x << 1) + (x << 3) + c - '0'; c = getchar();} a = f * x;
}
int gcd(int a, int b) {return (b > 0) ? gcd(b, a % b) : a;}
VI G[N];
int a[N],sz[N],son[N],dep[N];
int Son,idx;
ll ans;
int root[N];
int n,k;
struct Node{
	int l,r;
	int x;	 
}tr[N * 200];

void dfs(int u){
	sz[u] = 1;
	for(auto v:G[u]){
		dep[v] = dep[u] + 1;
		dfs(v);
		sz[u] += sz[v];
		if(sz[v] > sz[son[u]]) son[u] = v;
	}
}

int qeruy(int u,int l,int r,int L,int R){
	if(!u) return 0;
	if(l >= L && r <= R) return tr[u].x;
	int mid = (l + r) >> 1;
	int x = 0;
	if(L <= mid) x += qeruy(tr[u].l,l,mid,L,R);
	if(R > mid) x += qeruy(tr[u].r,mid + 1,r,L,R);
	return x; 
}

void modify(int &u,int l,int r,int p,int x){
	if(!u) u = ++idx;
	tr[u].x += x;
	if(l == r) return;
	int mid = (l + r) >> 1;
	if(p <= mid) modify(tr[u].l,l,mid,p,x);
	else modify(tr[u].r,mid + 1,r,p,x);
}

void run(int u,int td,int tv){
	int d = k + 2 * td - dep[u];
	d = min(d,n);
	int t = tv * 2 - a[u];
	if(d >= 1 && t >= 0 && t <= n) ans = (ans + 2ll * qeruy(root[t],1,n,1,d));
	for(auto v:G[u]) run(v,td,tv);
}

void add(int u,int x){
	modify(root[a[u]],1,n,dep[u],x);
	for(auto v:G[u]) add(v,x);
}

void dsu(int u){
	for(auto v:G[u]){
		if(v == son[u]) continue;
		dsu(v);
		add(v,-1);
	}
	if(son[u]) dsu(son[u]);
	for(auto v:G[u]){
		if(v == son[u]) continue;
		run(v,dep[u],a[u]);
		add(v,1);
	}	
	modify(root[a[u]],1,n,dep[u],1);

}	

int main() {
	read(n),read(k);
	dep[1] = 1;
	for(int i = 1;i <= n;i++) read(a[i]);
	for(int i = 2;i <= n;i++){
		int x;
		read(x);
		G[x].pb(i);
	}
	dfs(1);
	dsu(1);
	dl(ans);
	return 0;
}


```