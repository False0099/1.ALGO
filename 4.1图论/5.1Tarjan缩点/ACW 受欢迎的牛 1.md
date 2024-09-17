# 知识点
  ## [[有向图的强连通分量求法]] [[Tarjan算法]]
# 题目
每一头牛的愿望就是变成一头最受欢迎的牛。

现在有 N头牛，编号从 1到 N，给你 M对整数 (A, B)，表示牛 A认为牛 B受欢迎。

这种关系是具有传递性的，如果 A认为 B受欢迎，B认为 C受欢迎，那么牛 A也认为牛 C受欢迎。

你的任务是求出有多少头牛被除自己之外的所有牛认为是受欢迎的。

# 输入格式
第一行两个数 N, M；

接下来 M行，每行两个数 A, B，意思是 A认为 B是受欢迎的（给出的信息有可能重复，即有可能出现多个 A, B）。

# 输出格式
输出被除自己之外的所有牛认为是受欢迎的牛的数量。

# 数据范围
$1≤N≤10^4$
$1≤M≤5×10^4$
# 输入样例 ：
3 3
1 2
2 1
2 3
# 输出样例 ：
1
# 样例解释
只有第三头牛被除自己之外的所有牛认为是受欢迎的。

# 思路
·我们题目相当于给定一个有向图，求**有多少个顶点是由任何顶点出发可以到达**
·定理 1：有向无环图中唯一出度为 0 的点，一定可以由任何点出发达到
·定理 2：有向无环图中所有入度不为 0 的点，一定可以有某个入度为 0 的点出发可达。

**我们的可达性，不会因为缩点而受影响，一个 scc 内的点一个可以相互抵达**，所以我们就可以把我们的**图进行 scc 缩点后，再按照有向无环图中的定理来判断即可**
# AC 代码
```cpp
#include <iostream>
#include <stack>
using namespace std;
void tarjan(int u){
	dfn[u]=low[u]=timesp++;
	stack <int> st;
	st.push(u);
	in_stack[u]=true;
	for(int i=h[u];i!=-1;i=ne[i]){
		int j=e[i];
		if(!dfn[j]){
			tarjan(j);
			low[u]=min(low[u],low[j]);
		}
		if(in_stack[j]){
			low[u]=min(low[u],dfn[j]);
		}
	}
	if(dfn[u]==low[u]){
		scc_cnt++;
		int y;
		do{
			y=st.top();
			st.pop();
			id[y]=scc_cnt;
			size[scc_cnt]++;
		}while(y!=u);
	}
}
int main(){
	cin>>n>>m;
	memset(h,-1,sizeof h);
	while(m--){
		int a,b;
		cin>>a>>b;
		add(a,b);
	}
	for(int i=1;i<=n;i++){
		if(!dfn[i]){
			tarjan(i);
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=h[i];j!=-1;j=ne[j]){
			int k=e[j];
			int a=id[i],b=id[k];
			if(a!=b) dout[a]++;//两个不是一个集合，那么a的出度就++
		}
	}//根据出度和入度来建新图
	int zeros=0,sum=0;
	//当一个强连通的出度为0,则该强连通分量中的所有点都被其他强连通分量的牛欢迎但假如存在两及以上个出度=0的牛(强连通分量) 则必然有一头牛(强连通分量)不被所有牛欢迎
	for(int i=1;i<=scc_cnt;i++){//遍历所有强连通块后直接拓扑排序
		if(!dout[i]){
			zeros++;//
			sum+=Size[i];
			if(zeros>1){
				sum=0;
				break;
			}
		}
	}
	cout<<sum;
}
```
# 备注
