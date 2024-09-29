"Why, master," quoth Little John, taking the bags and weighing them in his hand, "here is the chink of gold."

The folk hero Robin Hood has been troubling Sheriff of Nottingham greatly. Sheriff knows that Robin Hood is about to attack his camps and he wants to be prepared.

Sheriff of Nottingham built the camps with strategy in mind and thus there are exactly $n$ camps numbered from $1$ to $n$ and $n-1$ trails, each connecting two camps. Any camp can be reached from any other camp. Each camp $i$ has initially $a_i$ gold.

As it is now, all camps would be destroyed by Robin. Sheriff can strengthen a camp by subtracting exactly $c$ gold from **each of its neighboring camps** and use it to build better defenses for that camp. Strengthening a camp **doesn't change** its gold, only its neighbors' gold. A camp can have negative gold.

After Robin Hood's attack, all camps that have been strengthened survive the attack, all others are destroyed.

What's the maximum gold Sheriff can keep in his surviving camps after Robin Hood's attack if he strengthens his camps optimally?

Camp $a$ is neighboring camp $b$ if and only if there exists a trail connecting $a$ and $b$. Only strengthened camps count towards the answer, as others are destroyed.

**Input**

The first line contains a single integer $t$ ($1 \le t \le 10^4$) — the number of test cases.

Each test case begins with two integers $n$, $c$ ($1 \le n \le 2\cdot10^5, 1 \le c \le 10^9$) — the number of camps and the gold taken from each neighboring camp for strengthening.

The second line of each test case contains $n$ integers $a_1,a_2,\dots,a_n$ ($-10^9 \le a_i \le 10^9$) — the initial gold of each camp.

Then follow $n-1$ lines, each with integers $u$, $v$ ($1 \le u, v \le n$, $u \ne v$) — meaning that there is a trail between $u$ and $v$.

The sum of $n$ over all test cases doesn't exceed $2\cdot10^5$.

It is guaranteed that any camp is reachable from any other camp.


**Output**

Output a single integer, the maximum gold Sheriff of Nottingham can keep in his surviving camps after Robin Hood's attack.

## 题解
本题，我们可以把我们的问题转换为一个树形背包问题，我们从**哪些选哪些不选来考虑我们的对应的问题**, 但是注意到，我们的这一个点**可能会影响到我们的父节点**，也就是说我们可能会存在后效性，这个时候，我们要怎么处理呢？

我们注意到，我们消除后效性的方法，是从我们的顶点开始，如果我们选择了这一个点，我们就让我们的对应的子节点的对应的获得的内容-k，然后再把这一个加进来作为我们的答案。

这样，我们就可以设置我们的 $dp[i][0]$ 表示我们不选择这一个点时，我们的子节点的最大值是多少，我们的 $dp[i][1]$ 表示我们选择这一个点的时候，我们的子节点的最大值是多少。我们的对应的转移方程就很好谢了：

```
#include <bits/stdc++.h>
#define int long long
#define endl '\n'
int INF=0x3f3f3f3f3f3f3f3f;
using namespace std;
typedef pair<int,int> PII;
void init(){
    
}
const int N=2e5+10;
vector<int> edge[N];
int f[N][2];
void solve(){
    int n,c;
    cin>>n>>c;
    vector<int> a(n+1);
    for(int i=1;i<=n;i++){
        cin>>a[i];
        edge[i].clear();
        f[i][0]=0;
        f[i][1]=0;
    }   
    for(int i=1;i<=n-1;i++){
        int u,v;
        cin>>u>>v;
        edge[u].push_back(v);
        edge[v].push_back(u);
    }
    function<void(int,int)> dfs=[&](int u,int fa){
        //cerr<u<<" "<<fa<<endl;
        f[u][0]=0;
        f[u][1]=a[u];
        for(auto v:edge[u]){
            if(v==fa){
                continue;
            }
            dfs(v,u);
            f[u][0]+=max(f[v][1],f[v][0]);
            f[u][1]+=max(f[v][0],f[v][1]-2*c);
        }
    };
    dfs(1,0);
    cout<<max(f[1][0],f[1][1])<<endl;
}
signed main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int t;
    t=1;
    cin>>t;
    init();
    while(t--){
        solve();
    }
}
```