# [eJOI 2020 Day 1] Fountain

## 题目描述

大家都知道喷泉吧？现在有一个喷泉由 $N$ 个圆盘组成，从上到下以此编号为 $1 \sim N$，第 $i$ 个喷泉的直径为 $D_i$，容量为 $C_i$，当一个圆盘里的水大于了这个圆盘的容量，那么水就会溢出往下流，直到流入半径大于这个圆盘的圆盘里。如果下面没有满足要求的圆盘，水就会流到喷泉下的水池里。

现在给定 $Q$ 组询问，每一组询问这么描述：

- 向第 $R_i$ 个圆盘里倒入 $V_i$ 的水，求水最后会流到哪一个圆盘停止。

如果最终流入了水池里，那么输出 $0$。

**注意，每个询问互不影响。**

## 输入格式

第一行两个整数 $N,Q$ 代表圆盘数和询问数。      
接下来 $N$ 行每行两个整数 $D_i,C_i$ 代表一个圆盘。       
接下来 $Q$ 行每行两个整数 $R_i,V_i$ 代表一个询问。

## 输出格式

$Q$ 行每行一个整数代表询问的答案。

## 样例 #1

### 样例输入 #1

```
6 5
4 10
6 8
3 5
4 14
10 9
4 20
1 25
6 30
5 8
3 13
2 8
```

### 样例输出 #1

```
5
0
5
4
2
```

## 提示

#### 样例 1 解释

前两个询问的解释如下图所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/64e7acuq.png)

因为每个询问互不影响，对于第三个询问，第 $5$ 个圆盘里的水不会溢出。

#### 数据规模与约定

**本题采用捆绑测试。**

- Subtask 1（30 pts）：$N \le 1000$，$Q \le 2000$。
- Subtask 2（30 pts）：$D_i$ 为严格单调递增序列。
- Subtask 3（40 pts）：无特殊限制。

对于 $100\%$ 的数据：

- $2 \le N \le 10^5$。
- $1 \le Q \le 2 \times 10^5$。
- $1 \le C_i \le 1000$。
- $1 \le D_i,V_i \le 10^9$。
- $ 1\le R_i \le N$。

#### 说明

翻译自 [eJOI 2020 Day1 A Fountain](https://ejoi2020.ge/static/assets/Day1/Problems/Fountain.pdf)。

## 题解
本题，我们的一个显然的思路，就是求出**下一个我们能够到达的盘子是哪一个**。这一步可以通过我们的单调栈处理。然后，我们在计算，我们如果线稿到达下一个盘子，我们需要的最低水量是多少。之后，我们就可以进行一个简单的倍增出里解决即可。

```
```cpp
#include <bits/stdc++.h>
#define int long long
#define endl '\n'
int INF=0x3f3f3f3f3f;
using namespace std;
typedef pair<int,int> PII;
const int N=1e5+10;
int last[N];
int dep[N];
int f[N][30];
int g[N][30];
PII a[N];
vector<int> edge[N];
void init(){
    
}
void dfs(int u,int fa){
    dep[u]=dep[fa]+1;
    f[u][0]=fa;
    g[u][0]=a[fa].second;
    for(int k=1;(1ll<<k)<=dep[u];k++){
        f[u][k]=f[f[u][k-1]][k-1];
        g[u][k]=g[f[u][k-1]][k-1]+g[u][k-1];
    }
    for(auto v:edge[u]){
        if(v==fa){
            continue;
        }
        dfs(v,u);
    }
}
void solve(){
    int n,m;
    cin>>n>>m;
    //vector<PII> a(n);
    for(int i=1;i<=n;i++){
        int d,c;
        cin>>d>>c;
        a[i].first=d;
        a[i].second=c;
    }
    a[n+1]={INF,INF};
    stack<int> stk;
    for(int i=n;i>=1;i--){
        while(stk.size()&&a[stk.top()].first<=a[i].first){
            stk.pop();
        }
        if(stk.size()){
            last[i]=stk.top();
        }else{
            last[i]=n+1;
        }
        stk.push(i);
    }
    for(int i=1;i<=n;i++){
        edge[i].push_back(last[i]);
        edge[last[i]].push_back(i);
    }
    dfs(n+1,0);

    for(int i=1;i<=m;i++){
        int r,v;
        cin>>r>>v;
        if(a[r].second>=v){
            cout<<r<<endl;
            continue;
        }
        v-=a[r].second;
        int x=r;
        int ans=0;
        for(int i=20;i>=0;i--){
            if(g[x][i]<=v&&(1ll<<i<=dep[x])){
                v-=g[x][i];
                x=f[x][i];
            }
            if(v==0){
                ans=x;
            }
        }
        if(ans==0){
            ans=f[x][0];
        }
        if(ans==n+1){
            cout<<0<<endl;
        }else{
            cout<<ans<<endl;
        }
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
```

