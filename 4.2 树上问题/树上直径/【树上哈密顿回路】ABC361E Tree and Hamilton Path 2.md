### Problem Statement

In the nation of AtCoder, there are $N$ cities numbered $1$ to $N$ and $N-1$ roads numbered $1$ to $N-1$.

Road $i$ connects cities $A_i$ and $B_i$ bidirectionally, and its length is $C_i$. Any pair of cities can be reached from each other by traveling through some roads.

Find the minimum travel distance required to start from a city and visit all cities at least once using the roads.

翻译：给你一颗树，要你求出树上的最小哈密顿回路。

### Constraints

-   $2 \leq N \leq 2\times 10^5$
-   $1 \leq A_i, B_i \leq N$
-   $1 \leq C_i \leq 10^9$
-   All input values are integers.
-   Any pair of cities can be reached from each other by traveling through some roads.

### Input

The input is given from Standard Input in the following format:


$N$
$A_1$ $B_1$ $C_1$
$\vdots$
$A_{N-1}$ $B_{N-1}$ $C_{N-1}$


## 题解
我们本体要求我们的**树上哈密顿回路**，我们发现，我们的**树上哈密顿回路**。我们考虑将我们的原问题变为一个简化的问题，加入我们**之后还需要回到我们的源点**，那么在这个时候，我们的结果很好计算，就是沃恩的两倍边长和。但是，因为我们不需要回到我们的起点，所以我们可以考虑**记我们的终点为 e**, 那么我们就可以少走一段从我们的终点返回我们的起点的路径，我们把这个长度记作**s**, 我们很明显可以知道**ans+s=2 e**, 于是，我们就只需要最大化我们的 $s$ 就可以知道我们的 ans 最小是多少。
```
#include <bits/stdc++.h>

#define int long long

int INF=0x3f3f3f3f3f;

using namespace std;

const int N=2e5+10;

int dist[N];

int h[N],e[N<<1],ne[N<<1],w[N<<1],idx;

int tmp;

void add(int a,int b,int c){

    e[idx]=b;

    w[idx]=c;

    ne[idx]=h[a];

    h[a]=idx++;

}

void dfs1(int u,int fa){

    for(int i=h[u];i!=-1;i=ne[i]){

        int v=e[i];

        if(v==fa){

            continue;

        }

        dist[v]=dist[u]+w[i];

        if(dist[v]>dist[tmp]){

            tmp=v;

        }

        dfs1(v,u);

    }

}

void solve(){

   int n;  

   cin>>n;

   int ans=0;

   memset(h,-1,sizeof h);

   for(int i=0;i<n-1;i++){

        int a,b,c;

        cin>>a>>b>>c;

        ans+=2*c;

        add(a,b,c);

        add(b,a,c);

   }

   dfs1(1,0);

   int side1=tmp;

   memset(dist,0,sizeof dist);

   dfs1(side1,0);

   int side2=tmp;

   cout<<ans-dist[side2];

}

signed main(){

    ios::sync_with_stdio(false),cin.tie(0);

    int t;

//    cin>>t;

    t=1;

    while(t--){

        solve();

    }

}
```