实验室里原先有一台电脑(编号为1)，最近 CC 中了彩票，又为实验室购置了 N-1台电脑，编号为2到 N。每台电脑都用网线连接到一台先前安装的电脑上。但是 CC 担心网速太慢，他希望知道第 i 台电脑到其他电脑的最大网线长度，但是可怜的 CC 在不久前刚刚遭受了 JC，请你帮帮他。  

![](https://s1.ax1x.com/2020/03/25/8XylFS.png)

  
  
提示: 样例输入对应这个图，从这个图中你可以看出，距离1号电脑最远的电脑是4号电脑，他们之间的距离是3。 4号电脑与5号电脑都是距离2号电脑最远的点，故其答案是2。5号电脑距离3号电脑最远，故对于3号电脑来说它的答案是3。同样的我们可以计算出4号电脑和5号电脑的答案是4.

输入格式

输入文件包含多组测试数据。对于每组测试数据，第一行一个整数N (N<=10000)，接下来有N-1行，每一行两个数，对于第i行的两个数，它们表示与i号电脑连接的电脑编号以及它们之间网线的长度。网线的总长度不会超过10^9，每个数之间用一个空格隔开。

输出格式

对于每组测试数据输出N行，第i行表示i号电脑的答案 (1<=i<=N).

样例输入

5
1 1
2 1
3 1
1 1

样例输出

3
2
3
4
4


## 题解
我们本题的要求是每个点到其他点的距离最长是多少，我们采用树形 dp：我们设我们到 i 点为根节点的最大距离为 $f[i]$,那么我们可以进行的 $f[i]=max(f[son])+1$。即可得到我们的答案。

当然，我们也可以用我们的换根思路，我们先任选一个作为我们的根节点，然后我们设 $g[i]$ 为我们更新后 i 到所有点的最大值, $gsec[i]$ 为我们更新后从 i 到所有点的次大值，显然我们有 $g[root]=f[root]$,然后，我们再进行一次 dfs，这一次，我们  

```cpp
#include<iostream>
#include<cstring>
#include<vector>
using namespace std;
typedef pair<int,int> PII; 
const int N = 10010;
vector<PII> g[N];
int d1[N],d2[N],df[N],dn[N];
int n;
void dfs_d(int u,int fa)
{
	for(auto &it:g[u])
	{
		int j=it.first,w=it.second;
		if(j==fa) continue;
		dfs_d(j,u);
		if(d1[u]<=d1[j]+w) d2[u]=d1[u],d1[u]=d1[j]+w,dn[u]=j;
		else if(d2[u]<d1[j]+w) d2[u]=d1[j]+w;
	}
}
void dfs_f(int u,int fa)
{
	for(auto &it:g[u])
	{
		int j=it.first,w=it.second;
		if(j==fa) continue;
		if(dn[u]==j) df[j]=max(df[u],d2[u])+w;
		else df[j]=max(df[u],d1[u])+w;
		dfs_f(j,u);
	}
}
int main()
{
	while(cin>>n)
	{
		memset(d1,0,sizeof d1);
		memset(d2,0,sizeof d2);
		memset(df,0,sizeof df);
		memset(dn,0,sizeof dn);
		for(int i=1;i<=n;i++) g[i].clear();
		for(int i=2;i<=n;i++)
		{
			int b,c;cin>>b>>c;
			g[i].push_back({b,c});
			g[b].push_back({i,c});
		}
		dfs_d(1,-1);
		dfs_f(1,-1);
		for(int i=1;i<=n;i++)
			cout<<max(d1[i],df[i])<<endl;
	}
	return 0;
}

```