# Forest

## 题面翻译

给你一个有 $N$ 个顶点和 $M$ 个边的森林，每个点有一个值 $a_i$。在给定的森林中添加边 $(i,j)$，森林变得连通，此操作花费 $a_i+ a_j$ 美元，并且之后不能再选择点 $i$ 和 $j$。

第一行输入 $N$，$M$；第二行输入 $N$ 个数，表示 $a_i$；然后依次输入 $M$ 对数，表示这两个点联通。

找到连接森林所需的最低总成本，否则输出"Impossible"。

## 题目描述

[problemUrl]: https://atcoder.jp/contests/apc001/tasks/apc001_d

$ N $ 頂点 $ M $ 辺の森が与えられます。頂点には $ 0 $ から $ N-1 $ の番号がついています。辺は $ (x_i, y_i) $ の形で与えられます。これは頂点 $ x_i $ と $ y_i $ が辺でつながっていることを意味します。

各頂点 $ i $ には $ a_i $ という値が定まっています。 あなたは与えられた森に辺を追加して連結にしたいです。辺を追加するときには、まず異なる頂点二つを選択し( $ i $ , $ j $ とする)、 $ i $ と $ j $ の間に辺を張ります。 この時コストが $ a_i+a_j $ かかります。そしてこれ以降，頂点 $ i $ と $ j $ は永遠に選択できなくなります。

森を連結にする最小コストを求めてください。連結にするのが不可能な場合は `Impossible` と出力してください。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ N $ $ M $ $ a_0 $ $ a_1 $ $ .. $ $ a_{N-1} $ $ x_1 $ $ y_1 $ $ x_2 $ $ y_2 $ $ : $ $ x_M $ $ y_M $

## 输出格式

森を連結にする最小コストを出力せよ。ただし、不可能な場合は `Impossible` と出力せよ。

## 样例 #1

### 样例输入 #1

```
7 5
1 2 3 4 5 6 7
3 0
4 0
1 2
1 3
5 6
```

### 样例输出 #1

```
7
```

## 样例 #2

### 样例输入 #2

```
5 0
3 1 4 1 5
```

### 样例输出 #2

```
Impossible
```

## 样例 #3

### 样例输入 #3

```
1 0
5
```

### 样例输出 #3

```
0
```

## 提示

### 制約

- $ 1\ <\ =\ N\ <\ =\ 100,000 $
- $ 0\ <\ =\ M\ <\ =\ N-1 $
- $ 1\ <\ =\ a_i\ <\ =\ 10^9 $
- $ 0\ <\ =\ x_i, y_i\ <\ =\ N-1 $
- 与えられるグラフは森
- 入力は全て整数

### Sample Explanation 1

頂点 $ 0 $, $ 5 $ をつなぐとグラフが連結になり，この時かかるコストは $ 1\ +\ 6\ =\ 7 $ です。

### Sample Explanation 2

どのように辺を追加してもグラフを連結にすることはできません。

### Sample Explanation 3

最初からグラフは連結であるので，辺を追加する必要はありません。


## 题解
本题要求我们的每一个树联通时候的贪心值是多少，我们考虑**将我们的边贡献转换为我们的每一个点的贡献**，我们这个时候，我们就考虑**选哪些点**。这个时候，我们显然就有：如果我们选择了一个点，我们的单个点对于我们的答案的贡献可以写为：$a[i]$。

为了保证我们的树联通，我们应该选择的点数应该是：$n+m$ 个点，这个时候，我们首先在我们的每一个连通块中选择一个 $a[i]$ 最小的点，然后我们还剩下的点，就在我们的全局当中选取我们的所有点的最小值是多少即可。

```cpp
#include <bits/stdc++.h>
#define int long long
#define endl '\n'
int INF=0x3f3f3f3f3f3f3f3f;
using namespace std;
typedef pair<int,int> PII;
void init(){
    
}
const int N=1e5+10;
int fa[N];
int find(int u){
    if(u==fa[u]){
        return u;
    }else{
        return fa[u]=find(fa[u]);
    }
}
multiset<int> num_of_tree[N];
multiset<PII> min_of_all;
int tot=0;
void merge(int u,int v){
    int uu=find(u);
    int vv=find(v);
    if(uu==vv){
        return;
    }else{
        min_of_all.erase({*(num_of_tree[uu].begin()),uu});
        min_of_all.erase({*(num_of_tree[vv].begin()),vv});
        
        if(num_of_tree[uu].size()<num_of_tree[vv].size()){
            num_of_tree[uu].swap(num_of_tree[vv]);
        }
        for(auto v:num_of_tree[vv]){
            num_of_tree[uu].insert(v);
        }
        if(num_of_tree[uu].size()==0&&min_of_all.size()!=0){
            cout<<"Impossible"<<endl;
            exit(0);
        }
        min_of_all.insert({*(num_of_tree[uu].begin()),uu});
        num_of_tree[vv].clear();
        fa[vv]=uu;
    }
}
void solve(){
    int n,m;
    cin>>n>>m;
    vector<int> a(n+1);
    for(int i=0;i<n;i++){
        cin>>a[i];
        fa[i]=i;
        num_of_tree[i].insert(a[i]);
        min_of_all.insert({a[i],i});
    } 
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        merge(u,v);
    }
    int cnt_of_scc=0;
    int cnt_of_point=0;
    for(int i=0;i<n;i++){
        if(fa[i]==i){
            cnt_of_scc++;
            cnt_of_point+=num_of_tree[i].size();
        }
    }
    if(cnt_of_scc==1){
        cout<<0<<endl;
        return;
    }
    if(cnt_of_point<2*(cnt_of_scc-1)){
        cout<<"Impossible"<<endl;
        return;
    }
    multiset<int> num;
    int tot=2*(cnt_of_scc-1);
    int sum=0;
    for(int i=0;i<n;i++){
        if(fa[i]==i){
            int u=*(num_of_tree[i].begin());
            tot--;
            sum+=u;
            num_of_tree[i].erase(num_of_tree[i].begin());
            for(auto v:num_of_tree[i]){
                num.insert(v);
            }
        }
    }
    //cerr<<sum<<endl;
    while(tot){
        int u=*(num.begin());
        sum+=u;
        num.erase(num.begin());
        tot--;
    }
    cout<<sum<<endl;
}
signed main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int t;
    t=1;
 //   cin>>t;
    init();
    while(t--){
        solve();
    }
}
```