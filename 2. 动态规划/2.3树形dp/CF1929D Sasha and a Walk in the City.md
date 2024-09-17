Sasha wants to take a walk with his girlfriend in the city. The city consists of $n$ intersections, numbered from $1$ to $n$. Some of them are connected by roads, and from any intersection, there is exactly one simple path $^{\dagger}$ to any other intersection. In other words, the intersections and the roads between them form a tree.

Some of the intersections are considered dangerous. Since it is unsafe to walk alone in the city, Sasha does not want to visit three or more dangerous intersections during the walk.

Sasha calls a set of intersections good if the following condition is satisfied:

-   If in the city only the intersections contained in this set are dangerous, then any simple path in the city contains **no more than two** dangerous intersections.

However, Sasha does not know which intersections are dangerous, so he is interested in the number of different good sets of intersections in the city. Since this number can be very large, output it modulo $998\,244\,353$.

$^{\dagger}$ A simple path is a path that passes through each intersection at most once.

**Input**

Each test consists of multiple test cases. The first line contains a single integer $t$ ($1 \le t \le 10^4$) — the number of test cases. The description of the test cases follows.

The first line of each test case contains a single integer $n$ ($2 \le n \leq 3 \cdot 10^5$) — the number of intersections in the city.

The next $(n - 1)$ lines describe the roads. The $i$ \-th line contains two integers $u_i$ and $v_i$ ($1 \leq u_i, v_i \leq n$, $u_i \ne v_i$) — the numbers of the intersections connected by the $i$ \-th road.

It is guaranteed that these roads form a tree.

It is guaranteed that the sum of $n$ over all test cases does not exceed $3 \cdot 10^5$.

**Output**

For each test case, output a single integer — the number of good sets of intersections modulo $998\,244\,353$.


## 题解
我们本题考虑我们的树形 dp，同时思考我们的状态设计和转移，我们设 $dp[i][0,1,2]$ 表示我们以 i 为 lca，最多的一条链上有 `0/1/2` 个节点的方案数。

于是，我们可以根据我们子节点的状态再加上我们这一个位置的状态来转移我们的方程：
```cpp
dp[x][2]+=dp[son][1]+dp[son][2]
dp[x][1]*=dp[son][0]+dp[son][1]
dp[x][1]%=mod
```

于是，我们就可以通过我们的转移来得到我们的最终答案。

```cpp
#include<bits/stdc++.h>
#define pb push_back
#define x first
#define y second
#define pdd pair<double,double>
#define pii pair<int,int>
#define pll pair<LL,LL>
#define mp make_pair
#define LL long long
#define ULL unsigned long long
#define sqr(x) ((x)*(x))
#define pi acos(-1)
#define MEM(x) memset(x,0,sizeof(x))
#define MEMS(x) memset(x,-1,sizeof(x))
using namespace std;
#define plus Plus
const int mod=998244353;
LL dp[300005][3];
vector<int> v[300005];
void dfs(int x,int f){
    dp[x][0]=1;
    dp[x][1]=1;
    dp[x][2]=0;
    for(auto it:v[x]){
        if(it!=f){
            dfs(it,x);
            dp[x][2]+=dp[it][1]+dp[it][2];
            dp[x][1]*=dp[it][0]+dp[it][1];
            dp[x][1]%=mod;
        }
    }
}
void solve(int T){
    int n;
    scanf("%d",&n);
    for(int i = 1;i<=n;i++)v[i].clear();
    for(int i = 1;i<n;i++){
        int x,y;
        scanf("%d %d",&x,&y);
        v[x].pb(y);
        v[y].pb(x);
    }
    dfs(1,0);
    printf("%d\n",(dp[1][0]+dp[1][1]+dp[1][2])%mod);
}
int main(){
   
    int t=1;0000;
    scanf("%d",&t);
    for(int i = 1;i<=t;i++){
        solve(i);
    }
    return 0;
}
/*
*/
```