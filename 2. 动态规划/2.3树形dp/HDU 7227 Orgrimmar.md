  *"In my memory, the last time such a tragic farewell to a respected Horde leader was at the top of Thunder Bluff. That day, Mother Earth was crying for him too. "*  
  
    *"This time, it is the Shadow of the Horde who has left us. At this moment, the entire Horde is whispering affectionately for him. "*  
  
    *"Son of Sen'jin, leader of the Darkspear tribe, Warchief of the Horde - Vol'jin."*  
  
    *Born in the cunning and vicious troll race, he spent his life explaining to the world what loyalty and faith are.*  
  
  
  
A dissociation set of an undirected graph is a set of vertices such that if we keep only the edges between these vertices, each vertex in the set is connected to at most one edge.  
  
The size of a dissociation set is defined by the size of the set of vertices.  
  
The maximal dissociation set of the graph is defined by the dissociation set of the graph with the maximum size.  
  
Sylvanas has a connected undirected graph that has �n vertex and �−1n−1 edges, and she wants to find the size of the maximal dissociation set of the graph.  
  
But since she just became the warchief of the Horde, she is too busy to solve the problem.  
  
Please help her to do so.

Input

The input consists of multiple test cases.  
  
The first line contains one integer � (1≤�≤10)T (1≤T≤10) denoting the number of test cases.  
  
The following are �T test cases.  
  
For each test case, the first line contains one integer � (�≤500000)n (n≤500000), which is the number of vertices.  
  
The following �−1n−1 lines each contains two integers �x and �y denoting an edge between x and y.  
  
It is guaranteed that the graph is connected.

Output

For each test case, output one line containing one integer indicating the answer.  
  
  
Notes:  
In this problem, you may need more stack space to pass this problem.  
We suggest you to add the following code into your main function if you use C++.  
  
```  
int main() {  
int size(512<<20); // 512M  
__asm__ ( "movq %0, %%rsp\n"::"r"((char*)malloc(size)+size));  
// YOUR CODE  
...  
exit(0);  
}  
  
```  
  
And if you use the code above please DON'T forget to add ����(0);exit(0); in the end of your main function, otherwise your code may get RE.  
  
  

Sample

|Inputcopy|Outputcopy|
|---|---|
|2<br>5<br>1 2<br>2 3<br>3 4<br>4 5<br>10<br>1 2<br>2 4<br>3 2<br>5 3<br>6 4<br>7 5<br>8 3<br>9 8<br>10 7|4<br>7|

## 题解
题意：给定一棵树，要求选择部分点构成一个**最大**集合，使得这个集合中所有点的度小于等于 1。**找到这个集合的大小是多少**。

思路：我们定义三个 $dp$ 数组 , `f` 表示选择子树的根作为集合中的点，`g` 表示不选择子树的根作为集合中的点，`h` 表示子树根和他的儿子都不在集合中，

```cpp
struct dp{
	int choose;
	int notchoose;
}dp[N];
dp[i].choose=d[son[i]]
```

```cpp
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int,int>
#define pll pair<long long,long long>
#define pb push_back
#define sz size
#define IOS ios::sync_with_stdio(0), cin.tie(0),cout.tie(0)
const ll inf=1ll<<60;
const int mod=998244353;
const int N=500010;
int n,ans,g[N],f[N],h[N];
vector<int> e[N];
void dfs(int par, int u){
	for(auto v:e[u]) if(v!=par){
		dfs(u,v);
		g[u]+=max(f[v],g[v]);
		h[u]+=g[v];
	}
	f[u]=max(f[u],h[u]+1);
	for(auto v:e[u]) if(v!=par){
		f[u]=max(f[u],h[v]+h[u]-g[v]+2);
	}
}
void solve()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		e[i].clear();
		f[i]=g[i]=h[i]=0;
	}
	for(int i=1;i<n;i++){
		int u,v;
		scanf("%d%d",&u,&v);
		e[u].pb(v);
		e[v].pb(u);
	}
	dfs(0,1);
	printf("%d\n",max(f[1],g[1]));
}
signed main(){
	int size(512<<20);  // 512M
        __asm__ ( "movq %0, %%rsp\n"::"r"((char*)malloc(size)+size));
	int _test=1,_tot=0;
	scanf("%d",&_test);getchar();
	while(_test--){
		solve();
	}
    exit(0);
}
```
```