Cwbc 和 XHRlyb 生活在 s 市，这天他们打算一起出去旅游。

旅行地图上有 n 个城市，它们之间通过 n-1 条道路联通。

Cwbc 和 XHRlyb 第一天会在 s 市住宿，并游览与它距离不超过 1 的所有城市，之后的每天会选择一个城市住宿，然后游览与它距离不超过 1 的所有城市。

他们不想住在一个已经浏览过的城市，又想尽可能多的延长旅行时间。

XHRlyb 想知道她与 Cwbc 最多能度过多少天的时光呢？


聪明的你在仔细阅读题目后，一定可以顺利的解决这个问题！

## 输入：
第一行，两个正整数 n 和 s，表示城市个数和第一天住宿的城市 s。  
接下来 n-1 行，每行两个整数 x 和 y，表示城市 x 与城市 y 之间有一条双向道路。

## 输出：
第一行，一个非负整数表示答案。

## 题解
本题我们就是裸的求**树上最大独立集的题目**，我们 hi 姐通过我们的一个简单的 dfs 就秒了

```
#include <bits/stdc++.h>
#define endl '\n'
int INF=0x3f3f3f3f3f3f3f3f;
using namespace std;
typedef pair<int,int> PII;
void init(){
    
}
const int N=5e5+10;
int mod=998244353;
vector<int> edge[N];
int f[N][2];
void solve(){
    int n,s;
    cin>>n>>s;
//    vector<int> fa(n+1);
    for(int i=2;i<=n;i++){
        int u,v;
        cin>>u>>v;
        edge[u].push_back(v);
        edge[v].push_back(u);      
    }  
    function<void(int,int)> dfs=[&](int u,int fa){
        //f[u][0]=1;
        f[u][1]=1;
        for(auto v:edge[u]){
            if(v==fa){
                continue;
            }
            dfs(v,u);
            f[u][0]+=max(f[v][0],f[v][1]);
            f[u][1]+=f[v][0];
        }
    };
    dfs(s,0);
    cout<<f[s][1]<<endl;
}
signed main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int t;
    t=1;
//    cin>>t;
    init();
    while(t--){
        solve();
    }
}
```