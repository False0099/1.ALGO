Bob is really interested in bipartite graph, and he needs help for this problem:

![](https://vj.csgrandeur.cn/8f510ff9982348240b85e2d1df8c5426?v=1666305101)

Bob has a bipartite graph which meets all the conditions below:

- The left part has �n (1≤�≤181≤n≤18) vertices, named �1,�2,⋯,��L1​,L2​,⋯,Ln​. And the right part also has �n vertices, named �1,�2,⋯,��R1​,R2​,⋯,Rn​.
- ��Li​ **never** connects with ��Rj​ when �>�i>j for all pairs of (�,�)(i,j) that 1≤�,�≤�1≤i,j≤n.
- For each vertex on the left part ��Li​ (1≤�≤�1≤i≤n), its degree ��Di​ is at most 33 and at least 11 (1≤��≤3)1≤Di​≤3).

Bob wants to select some edges from the graph such that the selected edges and their endpoints form a new graph. However, he should obey these rules:

- Some pairs of vertices can't appear in the new graph together. You are given an �×�n×n matrix �A, ��,�Ai,j​ is 11 if and only if ��Li​ and ��Lj​ can't appear in the new graph together.
- Bob must ensure that the selected edges cover all the right vertices. In other words, every right vertex should appear in the new graph.
- Every left vertex ��Li​ (1≤�≤�1≤i≤n) has a magic number ��Mi​ (1≤��≤1001≤Mi​≤100). If ��Li​ appears in the new graph, its cost is ����Mi​di​, where ��di​ is the degree of ��Li​ in the new graph, otherwise its cost is zero.

Now Bob wants to select edges satisfying the rules above with minimum total cost. Please write a program to help him find the minimum total cost, or determine it is impossible to get such a valid new graph.

### Input

There are several test cases in the input file. The first line contains one integer �T (1≤�≤101≤T≤10) --- number of the test cases. For each case:

The first line contains one integer �n (1≤�≤181≤n≤18) --- number of the left vertices.

The following �n lines are about the graph edges information with an �×�n×n matrix �G. The �i-th line contains a 01-string ��Gi​ and the �j-th character ��,�Gi,j​ is 11 if and only if ��Li​ and ��Rj​ are connected, otherwise ��,�Gi,j​ is 00. We guarantee that the degree of each left vertex ��Li​ is between 11 and 33. We also guarantee that ��,�Gi,j​ is always 00 when �>�i>j.

The following line is empty.

The following �n lines are about the constraints on left vertices with an �×�n×n matrix �A. The �i-th line contains a 01-string ��Ai​ and the �j-th character ��,�Ai,j​ is 11 if and only if ��Li​ and ��Lj​ can't be both in �S, which is the set of endpoints of the selected edges. We guarantee that ��,�Ai,i​ (1≤�≤�1≤i≤n) is 00 and ��,�=��,�Ai,j​=Aj,i​ (1≤�,�≤�1≤i,j≤n).

The following line is about magic numbers containing �n integers. The �i-th integer ��Mi​ (1≤��≤1001≤Mi​≤100) is the magic number of ��Li​.

### Output

For evey case print a single line containing an integer, the minimum total cost. If it is impossible to get such a valid new graph, just output `-1` instead.

### Sample 1

|Inputcopy|Outputcopy|
|---|---|
|2<br>4<br>1100<br>0110<br>0001<br>0001<br><br>0001<br>0001<br>0000<br>1100<br>3 4 4 5<br>4<br>1100<br>0110<br>0001<br>0001<br><br>0011<br>0001<br>1000<br>1100<br>3 4 4 5|17<br>-1|

  

In the first case:

![](https://res.jisuanke.com/img/upload/20191114/f7f7ad711042cdac7975f0fd708c2659eb124377.png)

We can choose edges (�1,�1),(�1,�2),(�2,�3),(�3,�4)(L1​,R1​),(L1​,R2​),(L2​,R3​),(L3​,R4​) such that �={�1,�2,�3}S={L1​,L2​,L3​}, satisfies the �A matrix's constraints. And the degrees are �1=2,�2=1,�3=1d1​=2,d2​=1,d3​=1, so the total cost =32+41+41+0=17=32+41+41+0=17.

In the second case, �3R3​ and �4R4​ can't be both covered at the same time, so there is no solution.

## 题意：
给你一个二分图，要求你重新连边，满足下面的要求：
1. 保留原图中的某些边，具体要求由矩阵给出
2. 最小化我们的花费，其中我们连边的花费为：$L_{i}^{D_{i}}$

## 题解
首先，对于本题来说，我们如果想要更新状态，我们的最好方法，还是得通过我们的状态压缩，我们设 $dp[i][S]$ 表示我们连接了我们右侧的 i 个点后，我们的状态为 S 的花费是多少。但是，我们还有一个问题，就是我们要怎么去计算我们的花费。这里，我们**需要用到我们的性质**：如果我们的左侧第 i 个被选，那么我们的右侧一定是唯一确定的。因此，我们想要计算的话，我们的度是可以确定的。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int inf=0x3f3f3f3f;
char str[20];
int g[20][20],A[20][20];
int w[20],tag[20],deg[20]; 
vector<int> go[20],con[20];
int ans=2e9;  
int cal(int x,int y) {
	if(!y) return 0; 
	int ans=1;
	for(int i=1;i<=y;++i) 
		ans=(ans*x);
	return ans; 
}
int n;  
void dfs(int cur,int A) {
	if(cur==n+1) { ans=min(ans,A);return; } 
	if(A>=ans) return;
	for(auto &v:go[cur]) {
		if(!tag[v]) {
			for(auto &x:con[v]) tag[x]++;
			deg[v]++;
			dfs(cur+1,A+cal(w[v],deg[v])-cal(w[v],deg[v]-1));
			deg[v]--;
			for(auto &x:con[v]) tag[x]--;
  		}
	}
}
void init() {
	memset(tag,0,sizeof(tag));
	memset(deg,0,sizeof(deg)); 
	for(int i=1;i<=n;i++) {
		go[i].clear();
		con[i].clear(); 
	}
}
int main() {
	int T;
	scanf("%d",&T);
	while(T--) {
		init(); 
		scanf("%d",&n);
		for(int i=1;i<=n;i++) {
			scanf("%s",str+1);
			for(int j=1;j<=n;j++)  {
				g[i][j]=str[j]-'0';
				if(g[i][j]) go[j].push_back(i); 	
			}	
		}
		for(int i=1;i<=n;i++) {
			scanf("%s",str+1);
			for(int j=1;j<=n;j++) {
				A[i][j]=str[j]-'0'; 
				if(A[i][j]) {
					con[i].push_back(j);
					con[j].push_back(i); 
				}
			}	
		}
		for(int i=1;i<=n;i++)
			scanf("%d",&w[i]); 
		bool ok=1; 
		for(int i=1;i<=n;i++) {
			if(!go[i].size()) {
				ok=0;
				break;
			}
		}
		if(!ok) puts("-1");
		else {
			ans=2e9; 
			dfs(1,0); 
			if(ans==2e9) puts("-1");
			else printf("%d\n",ans); 	
		}
	} 
	return 0;
}

```