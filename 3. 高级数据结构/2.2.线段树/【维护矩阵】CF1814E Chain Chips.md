# Chain Chips

## 题面翻译

在一条长度为 $n$ 的链上，有 $1\sim n$ 这 $n$ 个点，第 $i$ 条边连接着第 $i$ 个点到第 $i+1$ 个点，长度是 $w_i$ 。

在一开始，在第 $i$ 个点上都停着一辆车 $i$ 。现在，你需要通过这些道路，移动一些车辆，使得每一辆车都不停在它的初始位置上，同时每个位置最终也**仅有一辆车**，并且车的移动总距离尽可能小。

接下来会有 $m$ 组询问，每组询问会修改一条边的边权，你需要输出修改后的车的移动的最小距离。修改不独立，车并不会真的移动。

$n,m\leq 2\times 10^5$

## 题目描述

You are given an undirected graph consisting of $ n $ vertices and $ n-1 $ edges. The $ i $ -th edge has weight $ a_i $ ; it connects the vertices $ i $ and $ i+1 $ .

Initially, each vertex contains a chip. Each chip has an integer written on it; the integer written on the chip in the $ i $ -th vertex is $ i $ .

In one operation, you can choose a chip (if there are multiple chips in a single vertex, you may choose any one of them) and move it along one of the edges of the graph. The cost of this operation is equal to the weight of the edge.

The cost of the graph is the minimum cost of a sequence of such operations that meets the following condition:

- After all operations are performed, each vertex contains exactly one chip, and the integer on each chip is not equal to the index of the vertex where that chip is located.

You are given $ q $ queries of the form:

- $ k $ $ x $ — change the weight of the $ k $ -th edge (the one which connects the vertices $ k $ and $ k+1 $ ) to $ x $ .

After each query, print the cost of the graph. Note that you don't actually move any chips; when you compute the cost, the chips are on their initial positions.

## 输入格式

The first line contains one integer $ n $ ( $ 2 \le n \le 2 \cdot 10^5 $ ).

The second line contains $ n-1 $ integers $ a_1, a_2, \dots, a_{n-1} $ ( $ 1 \le a_i \le 10^9 $ ).

The third line contains one integer $ q $ ( $ 1 \le q \le 2 \cdot 10^5 $ ).

Then $ q $ lines follow. The $ i $ -th of them contains two integers $ k $ and $ x $ ( $ 1 \le k \le n-1 $ ; $ 1 \le x \le 10^9 $ ) for the $ i $ -th query.

## 输出格式

For each query, print one integer — the cost of the graph after the query is performed.

## 样例 #1

### 样例输入 #1

```
10
12 6 12 15 20 8 17 12 15
8
4 10
7 3
6 14
9 9
2 10
3 5
4 11
7 11
```

### 样例输出 #1

```
126
108
120
108
112
98
98
114
```

## 题解
本题我们考虑一个**没有修改的**弱化版本，这个时候，我们的一个显然的性质是，**如果我们的前面的已经是一个无序的**如果我们交换，我们一定是**只需要和我们的左边或者右边**交换一次极客。

这个时候，我们就可以通过我们的简单的 dp 来进行设计，我们设 $dp[i][0]$ 表示我们和我们的左侧项链，我们设我们的 $dp[i][1]$ 表示和我们的右侧相连。

这个时候我们显然存在下面的转移方程：
$$
\begin{align}
&dp[i][0]=min(dp[i-1][1],dp[i-1][0])+2*w[i] \\
&dp[i][1]=dp[i-1][0]
\end{align}
$$

我们通过观察不难发现，我们可以把我们的上面的式子进行转换：
$$
\begin{align}
&dp[i][0]=min(dp[i-1][1]+2*w[i],dp[i-1][0]+2*w[i]) \\
&dp[i][1]=min(dp[i-1][1]+INF,dp[i-1][0]+0)
\end{align}
$$

我们从中提取出我们的关键元素
$$\begin{bmatrix}\infty,2\times a_i\\0,2\times a_i\end{bmatrix}\times\begin{bmatrix}f_{i-1,0}\\f_{i-1,1}\end{bmatrix}=\begin{bmatrix}f_{i,0}\\f_{i,1}\end{bmatrix}$$

我们于是，我们就可以把我们的原本的 DP 操作，变成一个矩阵乘法。那么我们最后就可以通过线段树维护矩阵的方法动态维护我们的矩阵极客。
```
#include <bits/stdc++.h>
#define int long long
#define endl '\n'
int INF=0x3f3f3f3f3f3f3f3f;
using namespace std;
typedef pair<int,int> PII;
const int N=2e5+10;
int w[N];
struct Matrix{
	int m[4][4];

	void clear(){
		for(int i=0;i<4;i++){
			for(int j=0;j<4;j++)
				m[i][j]=0;
		}
	}

	void init(){
		for(int i=0;i<4;i++)
			m[i][i]=1;
	}

	void print(){
		for(int i=1;i<=2;i++){
			for(int j=1;j<=2;j++)
				printf("i=%I64d,j=%I64d,m=%I64d\n",i,j,m[i][j]);
		}
	}

	bool empty(){
		if(m[1][1]!=1) return 0;
		if(m[1][2]!=0) return 0;
		if(m[2][1]!=0) return 0;
		if(m[2][2]!=1) return 0;
		return 1;
	}

	Matrix operator*(const Matrix &y) const {
		Matrix z; z.clear();
        for(int i=1;i<=2;i++){
            for(int j=1;j<=2;j++){
                z.m[i][j]=INF;
            }
        }
		for(int i=1;i<=2;i++){
			for(int k=1;k<=2;k++){
				for(int j=1;j<=2;j++)
					z.m[i][j]=min(z.m[i][j],m[i][k]+y.m[k][j]);
			}
		}
		return z;
	}

	friend Matrix operator+(Matrix a,Matrix b){
		Matrix c;c.clear();
		for(int i=1;i<=2;i++){
			for(int j=1;j<=2;j++)
				c.m[i][j]=(a.m[i][j]+b.m[i][j]);
		}
		return c;
	}

};
struct SegmentTree
{
    struct Node
    {
        int l, r;
        Matrix sum;
    }tr[N << 2];
    Node merge(Node x, Node y)
    {
        if (x.l == -1) return y;
        if (y.l == -1) return x;
        Node z;
        z.l=min(x.l,y.l);
        z.r=max(x.r,y.r);
        z.sum=(x.sum*y.sum);
        return z;
    }//这里需要改 
    void pushup(int u)
    {
        tr[u] = merge(tr[u << 1], tr[u << 1 | 1]);
    }
    void build(int u, int l, int r)
    {
        Matrix a;
        tr[u] = {l, r};
        if (l == r){
            a.m[2][2]=2*w[l];
            a.m[1][2]=2*w[l];
            a.m[1][1]=INF;
            a.m[2][1]=0;
            tr[u].sum=a;
            return;
        } 
        int mid = l + r >> 1;
        build(u << 1, l, mid);
        build(u << 1 | 1, mid + 1, r);
        pushup(u);
    }
    void update(int u, int p, int x)
    {
        if (tr[u].l == tr[u].r)
        {
            //这里需要改 
            tr[u].sum.m[2][2]=2*x;
            tr[u].sum.m[1][2]=2*x;
            return;
        }
        int mid = tr[u].l + tr[u].r >> 1;
        if (p <= mid) update(u << 1, p, x);
        else update(u << 1 | 1, p, x);
        pushup(u);
    }
    Node query(int u, int l, int r)
    {
        if (tr[u].l >= l and tr[u].r <= r) 
        {
            return tr[u];
        }
        int mid = tr[u].l + tr[u].r >> 1;
        Node ret;
        ret.l = -1;
        if (l <= mid) ret = query(u << 1, l, r);
        if (r > mid) ret = merge(ret, query(u << 1 | 1, l, r));
        return ret;
    }
    void debug(int u){
        cerr<<tr[u].l<<" "<<tr[u].r<<" "<<tr[u].sum.m[1][1]<<" "<<tr[u].sum.m[1][2]<<" "<<tr[u].sum.m[2][1]<<" "<<tr[u].sum.m[2][2]<<endl;
        if(tr[u].l==tr[u].r){
            return;
        }
        debug(u<<1);
        debug(u<<1|1);
    }
}t;
void init(){
    
}
void solve(){
    int n;
    cin>>n;
    n--;
    for(int i=1;i<=n;i++){
        cin>>w[i];
    }
    t.build(1,1,n);
    int q;
    cin>>q;
    while(q--){
        int x,y;
        cin>>x>>y;
        t.update(1,x,y);
        auto u=t.query(1,1,n);
        cout<<(u.sum.m[1][2])<<endl;
    }
   
}
signed main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int t;
    t=1;
    //cin>>t;
    init();
    while(t--){
        solve();
    }
}
```

