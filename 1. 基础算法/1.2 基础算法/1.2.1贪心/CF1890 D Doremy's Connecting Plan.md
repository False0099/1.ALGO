Doremy lives in a country consisting of $n$ cities numbered from $1$ to $n$, with $a_i$ people living in the $i$ \-th city. It can be modeled as an undirected graph with $n$ nodes.

Initially, there are no edges in the graph. Now Doremy wants to make the graph connected.

To do this, she can add an edge between $i$ and $j$ if

$$
\sum_{k \in S} a_k \ge i\cdot j \cdot c,
$$

where $S$ is the set of all the nodes that are currently in the same connected component of either $i$ or $j$, and $c$ is a given constant.

Can Doremy make the graph connected?

Two nodes $(i, j)$ are in the same connected component if there exists a path from $i$ to $j$. A graph is connected if all its nodes are in the same connected component.

**Input**

The input consists of multiple test cases. The first line contains a single integer $t$ ($1\le t\le 10^4$) — the number of test cases. The description of the test cases follows.

The first line contains two integers $n$, $c$ ($2\le n\le 2\cdot 10^5$, $1 \le c \le 10^6$) — the number of nodes and the constant.

The second line of each test case contains $ n $  integers $ a_1, a_2,\ldots, a_n $  ($0 \le a_i \le 10^{12}$) — the number of people living in the $i$ \-th city.

It is guaranteed that the sum of $n$ over all test cases does not exceed $2\cdot 10^5$.

**Output**

For each test case, print "YES" (without quotes), if it is possible to make the graph connected, and "NO" (without quotes) otherwise.

You can print letters in any case (upper or lower).

## 题解
我们本题可以首先修改一下我们的式子，因为我们本题**一定是用我们的位置 1 和我们的其他位置合并**，所以我们对其他位置，就按照我们的 $a[j]-j*c$ 从大到小进行我们的排序，然后再看我们能不能全部合并就行。 

```cpp
#include<bits/stdc++.h>
#define ll long long
#define il inline
using namespace std;
const int maxn=1000010;
il ll read(){
	ll x=0;
	char c=getchar();
	for(;!(c>='0'&&c<='9');c=getchar());
	for(;c>='0'&&c<='9';c=getchar())
		x=(x<<1)+(x<<3)+c-'0';
	return x;
}
struct node{
	ll x,id;
}a[maxn];
int T,n;
int C;
bool cmp(node a,node b){
	return a.id*C-a.x<b.id*C-b.x;
}
int main(){
	T=read();
	while(T--){
		n=read(),C=read();
		for(int i=1;i<=n;i++)
			a[i].x=read(),a[i].id=i;
		sort(a+2,a+1+n,cmp);
		ll A=a[1].x; bool fl=1;
		for(int i=2;i<=n;i++){
			if(A+a[i].x<a[i].id*C) fl=0;
			A+=a[i].x;
		}
		if(fl) printf("Yes\n");
		else printf("No\n");
	}
	return 0;
}
```