# Spiders

## 题目背景

请注意本题需要文件读写。

你的代码需要从 `input.txt` 中读入数据，并向 `output.txt` 输出。

## 题面翻译

Petya 有 $n$ 只玩具蜘蛛，每只玩具蜘蛛可以看作一棵无根树。节点大小忽略不计，边的长度为 1。

Petya 可以在两只蜘蛛中各选一个节点粘在一起，从而形成一只新蜘蛛。新的蜘蛛也是一棵树。

他希望把所有蜘蛛用上面的方式粘在一起，并让新形成的蜘蛛中最远的两个节点距离最大（即树的直径最大）。

如图，在样例 2 中，Petya 将第一只蜘蛛的 2 号点与第二只蜘蛛的 1 号点粘在一起，新得到的蜘蛛的直径被加粗标出。

### 输入格式

第一行一个正整数 $n(1\leq n\leq 100)$，代表蜘蛛的数量。

之后 $n$ 行，每行开头为一个正整数 $n_i(2\leq n_i\leq 100)$，代表第 $i$ 只蜘蛛的节点数；接下来 $n-1$ 对正整数，每一对代表某两点之间有边直接相连。

### 输出格式

一行一个正整数，代表新形成的蜘蛛中最远的两个节点距离的最大值（即树的直径的最大值）。

## 题目描述

One day mum asked Petya to sort his toys and get rid of some of them. Petya found a whole box of toy spiders. They were quite dear to him and the boy didn't want to throw them away. Petya conjured a cunning plan: he will glue all the spiders together and attach them to the ceiling. Besides, Petya knows that the lower the spiders will hang, the more mum is going to like it and then she won't throw his favourite toys away. Help Petya carry out the plan.

A spider consists of $ k $ beads tied together by $ k-1 $ threads. Each thread connects two different beads, at that any pair of beads that make up a spider is either directly connected by a thread, or is connected via some chain of threads and beads.

Petya may glue spiders together directly gluing their beads. The length of each thread equals 1. The sizes of the beads can be neglected. That's why we can consider that gluing spiders happens by identifying some of the beads (see the picture). Besides, the construction resulting from the gluing process should also represent a spider, that is, it should have the given features.

After Petya glues all spiders together, he measures the length of the resulting toy. The distance between a pair of beads is identified as the total length of the threads that connect these two beads. The length of the resulting construction is the largest distance between all pairs of beads. Petya wants to make the spider whose length is as much as possible.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF120F/8b664867db300110aac369f834bea9838c57bcef.png) ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF120F/4d2e6eef4b897e5c0e7f81891c6a05c68b56b178.png)The picture two shows two spiders from the second sample. We can glue to the bead number 2 of the first spider the bead number 1 of the second spider. The threads in the spiders that form the sequence of threads of maximum lengths are highlighted on the picture.

## 输入格式

The first input file line contains one integer $ n $ ( $ 1<=n<=100 $ ) — the number of spiders. Next $ n $ lines contain the descriptions of each spider: integer $ n_{i} $ ( $ 2<=n_{i}<=100 $ ) — the number of beads, then $ n_{i}-1 $ pairs of numbers denoting the numbers of the beads connected by threads. The beads that make up each spider are numbered from 1 to $ n_{i} $ .

## 输出格式

Print a single number — the length of the required construction.

## 样例 #1

### 样例输入 #1

```
1
3 1 2 2 3
```

### 样例输出 #1

```
2
```

## 样例 #2

### 样例输入 #2

```
2
3 1 2 1 3
4 1 2 2 3 2 4
```

### 样例输出 #2

```
4
```

## 样例 #3

### 样例输入 #3

```
2
5 1 2 2 3 3 4 3 5
7 3 4 1 2 2 4 4 6 2 7 6 5
```

### 样例输出 #3

```
7
```

## 思路
树直径性质，n棵树连接起来最长路是n棵树的直径和

## AC代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define INF 0x3f3f3f3f3f3f3f3f
#define L(i, j, k) for(int i = (j); i < (k); ++i)
#define R(i, j, k) for(int i = (j); i >= (k); --i)
#define _L(i, j, k) for(int i = (j); i <= (k); ++i)
#define all(x) (x).begin(),(x).end()
#define allp(x,n) (x).begin()+(n),(x).end()
#define ms(x,y) memset(x,y,sizeof(x))
#define dbg(x) cerr<<__LINE__<<" | "<<#x<<" = "<<x<<"\n"
#define dbgl(i,x) cerr<<__LINE__<<" ["<<#i<<"]: "<<i<<" -> { "<<#x<<" = "<<x<<" }\n"
#define in(a,l,r)   for(int i=l;i<r;cin>>a[i],i++)
#define bp cerr<<"breakpoint"<<"\n"
#define YES cout<<"YES"<<"\n"
#define NO  cout<<"NO"<<"\n"
#define Yes cout<<"Yes"<<"\n"
#define No  cout<<"No"<<"\n"

#ifdef KROWFEATHER
    #include<bits/KrowFeather.h>
#endif
#define int long long
using ull = unsigned long long;                                                                              
using ll = long long;
using pii = pair<int,int>;
using psi = pair<string,int>;
constexpr ll MOD = 1e9+7;
//-------------------------------------------------------->>>>>>>>>>

inline void solve(){
    int T;
    cin>>T;
    int tot=0;
    while(T--){
        int n;
        cin>>n;
        vector<vector<int>> g(n+1);
        L(i,0,n-1){
            int u,v;
            cin>>u>>v;
            g[u].push_back(v);
            g[v].push_back(u);
        }
        vector<int> dep(n+1,-1);
        int deepest = 0;
        function<void(int,int)> dfs = [&](int u,int fa){
            dep[u]=dep[fa]+1;
            if(dep[u]>dep[deepest]){
                deepest=u;
            }
            for(auto &v:g[u]){
                if(v!=fa){
                    dfs(v,u);
                }
            }
        };
        dfs(1,0);
        dfs(deepest,0);
        tot+=dep[deepest];
    }
    cout<<tot<<"\n";
}
inline void prework(){
    
}
signed main(){
    #ifndef KROWFEATHER
        freopen("input.txt","r",stdin);
        freopen("output.txt","w",stdout);
    #endif
    ios::sync_with_stdio(false);
    cin.tie(nullptr);cout.tie(nullptr);
    cout<<fixed<<setprecision(12);
    prework();
    int T=1; 
    // cin>>T;
    while(T--){
        solve();
    }
    return 0;
}
```