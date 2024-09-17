# 知识点
  ## [[有向图的强连通分量求法]] [[Tarjan算法]]
# 题目
 一些学校连接在一个计算机网络上，学校之间存在软件支援协议，每个学校都应支援的学校名单（学校 A支援学校 B，并不表示学校 B一定要支援学校 A）。

当某校获得一个新软件时，无论是直接获得还是通过网络获得，该校都应立即将这个软件通过网络传送给它应支援的学校。

因此，一个新软件若想让所有学校都能使用，只需将其提供给一些学校即可。

现在请问最少需要将一个新软件直接提供给多少个学校，才能使软件能够通过网络被传送到所有学校？

最少需要添加几条新的支援关系，使得将一个新软件提供给任何一个学校，其他所有学校就都可以通过网络获得该软件？

# 输入格式
第 1行包含整数 N，表示学校数量。

第 2.. N+1行，每行包含一个或多个整数，第 i+1行表示学校 i应该支援的学校名单，每行最后都有一个 0表示名单结束（只有一个 0即表示该学校没有需要支援的学校）。

# 输出格式
输出两个问题的结果，每个结果占一行。

# 数据范围
2≤N≤100
# 输入样例：
5
2 4 3 0
4 5 0
0
0
1 0
# 输出样例：
1
2

# 思路
·对于第一问我们观察到求发给多少个学校，其实就是求这个图里有多少个强连通分量。这个我们完全可以用 tarjan 算法算出后直接求图里的每一个分量。
·对于第二问，我们也可以观察到这个问题实际上就是求使得图变得联通的结果，我们可据此来得到，最后要添加的边数就是缩点后的图的入度和出度的最大值。
·
# AC 代码
```cpp
#include <iostream>
#include <stack>
using namespace std;
stack<int> st;
void tarjan(int u){
	dfn[u]=low[u]=timestamp++;
	st.push(u);
	in_stk[u]=true;
	for(int i=h[u];i!=-1;i=ne[i]){
		int j=e[i];
		if(!dfn[j]){
			tarjan(j);
			low[u]=min(low[u],low[j]);
		}else if(in_stk[j]){
			low[u]=min(low[u],dfn[j]);
		}
	}
	if(dfn[u]==low[u]){
		++scc_cnt;
		int y;
		do{
			y=st.top();
			st.pop();
			in_stk[y]=false;
			Size[scc_cnt]++;
			id[y]=scc_cnt;
		}while(y!=u);
	}
}
int main(){
	cin>>n;
	memset(h,-1,sizeof h);
	for(int i=1;i<=n;i++){
		int t;
		while(cin>>t,t){
			add(i,t);
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=h[i];j!=-1;j=ne[j]){
			int k=e[j];
			int a=id[i],b=id[k];
			if(a!=b){
				dout[a]++;
				din[b]++;
			}
		}
	}
	int a=0,b=0;
	for(int i=1;i<=scc_cnt;i++){
		if(!din[i]) a++;
		if(!dout[i]) b++; 
	}
	cout<<a;
	if(scc_cnt==1) cout<<"0";
	else cout<<max(a,b);
}
```
# 备注
