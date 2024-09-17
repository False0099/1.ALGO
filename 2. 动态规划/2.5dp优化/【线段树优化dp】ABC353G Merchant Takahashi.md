### Problem Statement

The Kingdom of AtCoder has $N$ towns: towns $1$, $2$, $\ldots$, $N$. To move from town $i$ to town $j$, you must pay a toll of $C \times |i-j|$ yen.

Takahashi, a merchant, is considering participating in zero or more of $M$ upcoming markets.

The $i$ \-th market $(1 \leq i \leq M)$ is described by the pair of integers $(T_i, P_i)$, where the market is held in town $T_i$ and he will earn $P_i$ yen if he participates.

For all $1 \leq i \lt M$, the $i$ \-th market ends before the $(i+1)$ \-th market begins. The time it takes for him to move is negligible.

He starts with $10^{10^{100}}$ yen and is initially in town $1$. Determine the maximum profit he can make by optimally choosing which markets to participate in and how to move.

Formally, let $10^{10^{100}} + X$ be his final amount of money if he maximizes the amount of money he has after the $M$ markets. Find $X$.

### Constraints

-   $1 \leq N \leq 2 \times 10^5$
-   $1 \leq C \leq 10^9$
-   $1 \leq M \leq 2 \times 10^5$
-   $1 \leq T_i \leq N$ $(1 \leq i \leq M)$
-   $1 \leq P_i \leq 10^{13}$ $(1 \leq i \leq M)$
-   All input values are integers.

### Input

The input is given from Standard Input in the following format:


$N$ $C$
$M$
$T_1$ $P_1$
$T_2$ $P_2$
$\vdots$
$T_M$ $P_M$


### Output

Print the answer.

## 题解
本题我们首先考虑暴力 dp，我们设 $dp[i]$ 表示我们以 $i$ 为最后一个事件时，我们的最大价值是多少，显然，我们可以存在下面的一个转移：
$$
dp[i]=max\{dp[j]+val[i]+c\times |pos[i]-pos[j]|\}
$$

这个时候，我们可以按照我们的绝对值来把我们的值进行分类讨论，**因为分类后有利于我们进行我们的优化**然后再去计算我们的答案，于是我们就有：
$$
dp[i]=max\{dp[j]+val[i]+c\times pos[i]-c\times pos[j]\}
$$

$$
dp[i]=max\{dp[j]-c\times pos[j]\}+c\times pos[i]+val[i]
$$

如果我们有 $pos[i]>pos[j]$

同理，如果我们满足 $pos[i]<pos[j]$,我们就有：
$$
dp[i]=max\{dp[j]+c\times pos[j]\}-c\times pos[i]+val[i]
$$

于是，我们可以考虑用我们的线段树来维护我们的最大值。但是，我们还有一个问题，**我们线段树的下标应该是多少**。经过权衡后，我们可以让我们的线段树的下标为我们的 $pos$,因为我们如果以 $j$ 为下标，那么我们处理 $pos[i]<pos[j]$ 时不好处理的。我们不妨**以值域为下表**。

那么，我们就有结果如下：
```
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e5+10;
int n,c;
struct Node
{
    int l, r;
    int max_;
}tr[N * 4][2];
int dp[N];
void pushup(int u,int idx)
{
    tr[u][idx].max_ = max(tr[u << 1][idx].max_ , tr[u << 1 | 1][idx].max_);
}

void build(int u, int l, int r,int idx)
{
    if (l == r) tr[u][idx] = {l, r, -0x3f3f3f3f3f3f3f};
    else
    {
        tr[u][idx] = {l, r};
        int mid = l + r >> 1;
        build(u << 1, l, mid,idx), build(u << 1 | 1, mid + 1, r,idx);
        pushup(u,idx);
    }
}

void modify(int u, int l, int r,int val,int idx)
{
    if (tr[u][idx].l >= l && tr[u][idx].r <= r){
    	tr[u][idx].max_=max(tr[u][idx].max_,val);
	}
    else
    {
        int mid = tr[u][idx].l + tr[u][idx].r >> 1;
        if (l <= mid) modify(u << 1, l, r, val, idx);
        if (r > mid) modify(u << 1 | 1, l, r, val, idx);
        pushup(u,idx);
    }
}

int query(int u, int l, int r,int idx)
{
    if (tr[u][idx].l >= l && tr[u][idx].r <= r) return tr[u][idx].max_;
    int mid = tr[u][idx].l + tr[u][idx].r >> 1;
    int ans = -0x3f3f3f3f3f3f3f;
    if (l <= mid) ans = query(u << 1, l, r,idx);
    if (r > mid) ans = max(ans ,query(u << 1 | 1, l, r,idx));
    return ans;
}

signed main()
{
    cin>>n>>c;
    int m;
    cin>>m;
    build(1,1,n+10,0);
    build(1,1,n+10,1);
    modify(1,1,1,c,0);//记录了我们的p[m]>[j] 
    modify(1,1,1,-c,1);//记录我们的p[m]<p[j] 
    for(int i=1;i<=m;i++){
 		int a,b;
		cin>>a>>b;
		int tmp1=query(1,1,a,0)+b-c*a;
		int tmp2=query(1,a+1,n,1)+b+c*a;
		dp[i]=max(tmp1,tmp2);
		modify(1,a,a,dp[i]+c*a,0);
		modify(1,a,a,dp[i]-c*a,1);   	
	}
	int ans=-0x3f3f3f3f3f3f3f;
	for(int i=1;i<=m;i++){
		ans=max(ans,dp[i]);
	}
	cout<<max(ans,0ll)<<endl;
}
```