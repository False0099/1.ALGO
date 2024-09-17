# Gr-idian MST

## 题面翻译

$H \times W$ 的二维平面，$\forall 0\le i\le H, 0\le j\le W$ 有一个点。连接 $(i, j)$ 到 $(i + 1, j)$ 的边权为 $p_i$（$0\le j\le W$），连接 $(i, j)$ 到 $(i, j + 1)$ 的边权为 $q_j$。求这张 $(H + 1)\times (W + 1)$ 个点的图的最小生成树的边权和。$1\le H, W\le 10^5$，$1\le p_i,q_j\le 10^8$。

Translated by @YangTY

## 题目描述

[problemUrl]: https://atcoder.jp/contests/code-festival-2016-qualb/tasks/codefestival_2016_qualB_c

$ xy $平面上の$ 0\ ≦\ x\ ≦\ W,\ 0\ ≦\ y\ ≦\ H $をみたす領域にある$ x, y $ともに整数である点すべてに、ひとつずつ家があります。

$ x $座標が等しく$ y $座標の差が$ 1 $であるか、$ y $座標が等しく$ x $座標の差が$ 1 $であるような$ 2 $点の組のうち、両方の点に家が存在するような全てのものに対し、その$ 2 $点の間には舗装されていない道路があります。

座標$ (i, j) $と$ (i+1, j) $にある家の間の道路を舗装するのには$ j $の値にかかわらずコストが$ p_i $、 座標$ (i, j) $と$ (i, j+1) $にある家の間の道路を舗装するのには$ i $の値にかかわらずコストが$ q_j $かかります。

高橋君は、このうちいくつかの道路を舗装し、舗装された道路のみを通って任意の$ 2 $つの家の間を行き来できるようにしたいです。 かかるコストの総和の最小値を求めてください。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ W $ $ H $ $ p_0 $ : $ p_{W-1} $ $ q_0 $ : $ q_{H-1} $

## 输出格式

コストの総和の最小値を表す整数を出力せよ。

## 样例 #1

### 样例输入 #1

```
2 2
3
5
2
7
```

### 样例输出 #1

```
29
```

## 样例 #2

### 样例输入 #2

```
4 3
2
4
8
1
2
9
3
```

### 样例输出 #2

```
60
```

## 提示

### 制約

- $ 1\ ≦\ W, H\ ≦\ 10^5 $
- $ 1\ ≦\ p_i\ ≦\ 10^8 (0\ ≦\ i\ ≦\ W-1) $
- $ 1\ ≦\ q_j\ ≦\ 10^8 (0\ ≦\ j\ ≦\ H-1) $
- $ p_i (0\ ≦\ i\ ≦\ W-1) $は整数である
- $ q_j (0\ ≦\ j\ ≦\ H-1) $は整数である

### Sample Explanation 1

次の$ 8 $本の道路を舗装すればよいです。 - $ (0,0) $と$ (0,1) $にある家を結ぶ道路 - $ (0,1) $と$ (1,1) $にある家を結ぶ道路 - $ (0,2) $と$ (1,2) $にある家を結ぶ道路 - $ (1,0) $と$ (1,1) $にある家を結ぶ道路 - $ (1,0) $と$ (2,0) $にある家を結ぶ道路 - $ (1,1) $と$ (1,2) $にある家を結ぶ道路 - $ (1,2) $と$ (2,2) $にある家を結ぶ道路 - $ (2,0) $と$ (2,1) $にある家を結ぶ道路

## 题解
我们本题显然要求一个格点最小生成树，我们**暴力建图显然是不可取的**，我们要做的就十八我们的行和列当作一个整体，我们每一次，先将我们的所有边权进行排序，每一次排序后，我们再从我们的堆中选择一个权值最小的边，我们检查这一个边上对应的哪些可以连接，能连就尽可能的连接。

举例来说，我们的行需要连接的变数=**总列数-已经连接过的行数**。我们以此类推，直到我们一共连接了对应的变数。
```
```cpp
#include <bits/stdc++.h>
#define int long long
#define endl '\n'
int INF=0x3f3f3f3f3f3f3f3f;
using namespace std;
typedef pair<int,int> PII;
void init(){
    
}
void solve(){
    int h,w;
    cin>>h>>w;
    int count_row=0;
    int count_col=0;   
    vector<PII> edges;
    for(int i=0;i<h;i++){
        int u;
        cin>>u;
        edges.push_back({u,1});
//        cin>>edges[i].first;
  //      edges[i].second=1;
    } 
    for(int i=0;i<w;i++){
        int u;
        cin>>u;
        edges.push_back({u,2});
    }
    sort(begin(edges),end(edges));
    int ans=0;
    int a=h+1;
    int b=w+1;
    for(auto [val,type]:edges){
        if(type==1){
           if(a){
                --a;
                ans+=val*b;
           }
        }else if(type==2){
           if(b){
                --b;
                ans+=val*a;
           }
        }
    }
    cout<<ans<<endl;
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