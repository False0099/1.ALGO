[t+pazolite, ginkiha, Hommarju - Paved Garden](https://soundcloud.com/fractalex-gd/ginkiha-paved-garden-little)

翻译：给你一个 n 个节点的树，问你要操作至少多少次，满足我们所有叶子节点到我们的根节点的距离相同。

You are given a tree with $n$ nodes, rooted at node $1$. In this problem, a leaf is a non-root node with degree $1$.

In one operation, you can remove a leaf and the edge adjacent to it (possibly, new leaves appear). What is the minimum number of operations that you have to perform to get a tree, also rooted at node $1$, where all the leaves are at the same distance from the root?

**Input**

Each test contains multiple test cases. The first line contains the number of test cases $t$ ($1 \le t \le 10^4$). The description of the test cases follows.

The first line of each test case contains a single integer $n$ ($3 \leq n \leq 5 \cdot 10^5$) — the number of nodes.

Each of the next $n-1$ lines contains two integers $u$, $v$ ($1 \leq u, v \leq n$, $u \neq v$), describing an edge that connects $u$ and $v$. It is guaranteed that the given edges form a tree.

It is guaranteed that the sum of $n$ over all test cases does not exceed $5 \cdot 10^5$.

**Output**

For each test case, output a single integer: the minimum number of operations needed to achieve your goal.

## 题解
我们本题显然有一个枚举方法，我们先枚举我们**当前需要我们的结点深度有多少**。然后我们考虑对于我们的每一个深度，我们怎么计算我们的对应的结果。

显然，我们的最后的对应的**深度比这个点还要大的点**是一定要删除的。另外还有其他要删除的吗？显然是有的，我们还需要删除一个点，满足**这一个点的子树最大深度没有达到我们的 d**，那么这一个子树上的所有的点都要对应的删除。

我们对于我们的信息 1 的统计是显然的，但是对于我们的信息二的统计，我们就会相对更加困难一点，我们不妨考虑把我们的满足下面条件的点都转喊道我们的每一个点上，而不是只在我们的根节点是。

于是，我们就可以完成本题。
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5e5+10;
vector<int> to[N];
int dep[N],fa[N],T,n,f[N],t1[N],t2[N];
void dfs1(int x)
{
	f[x]=dep[x]=dep[fa[x]]+1;
	for(int y:to[x])
		if(fa[x]!=y) fa[y]=x,dfs1(y),f[x]=max(f[x],f[y]);
	t1[dep[x]]++,t2[f[x]]++;
}
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&n);
		for(int i=1,x,y;i<n;i++)
		{
			scanf("%d%d",&x,&y);
			to[x].push_back(y),to[y].push_back(x);
		}
		dfs1(1);
		for(int i=1;i<=n;i++) t2[i]+=t2[i-1];
		for(int i=n;i;i--) t1[i]+=t1[i+1];
		int ans=n-2;
		for(int i=1;i<=n;i++) ans=min(ans,t1[i+1]+t2[i-1]);
		for(int i=1;i<=n;i++) t1[i]=t2[i]=fa[i]=dep[i]=0;
		for(int i=1;i<=n;i++) to[i].clear();
		printf("%d\n",ans);
	}
}
```