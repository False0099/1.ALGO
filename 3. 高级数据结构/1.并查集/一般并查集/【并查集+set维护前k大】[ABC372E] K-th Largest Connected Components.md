# [ABC372E] K-th Largest Connected Components

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc372/tasks/abc372_e

$ N $ 頂点 $ 0 $ 辺の無向グラフがあります。頂点には $ 1 $ から $ N $ の番号がつけられています。

$ Q $ 個のクエリが与えられるので、与えられた順に処理してください。各クエリは以下の $ 2 $ 種類のいずれかです。

- タイプ $ 1 $ : `1 u v` の形式で与えられる。頂点 $ u $ と頂点 $ v $ の間に辺を追加する。
- タイプ $ 2 $ : `2 v k` の形式で与えられる。頂点 $ v $ と連結な頂点の中で、$ k $ 番目に頂点番号が大きいものを出力する。ただし、頂点 $ v $ と連結な頂点が $ k $ 個未満のときは `-1` を出力する。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ N $ $ Q $ $ \mathrm{query}_1 $ $ \mathrm{query}_2 $ $ \vdots $ $ \mathrm{query}_Q $

ただし、$ \mathrm{query}_i $ は $ i $ 個目のクエリであり、以下のいずれかの形式で与えられる。

> $ 1 $ $ u $ $ v $

> $ 2 $ $ v $ $ k $

## 输出格式

タイプ $ 2 $ のクエリの個数を $ q $ として、$ q $ 行出力せよ。$ i $ 行目には $ i $ 個目のタイプ $ 2 $ に対するクエリの答えを出力せよ。

## 样例 #1

### 样例输入 #1

```
4 10
1 1 2
2 1 1
2 1 2
2 1 3
1 1 3
1 2 3
1 3 4
2 1 1
2 1 3
2 1 5
```

### 样例输出 #1

```
2
1
-1
4
2
-1
```

## 样例 #2

### 样例输入 #2

```
6 20
1 3 4
1 3 5
2 1 1
2 3 1
1 1 5
2 6 9
2 1 3
2 6 1
1 4 6
2 2 1
2 6 2
2 4 7
1 1 4
2 6 2
2 3 4
1 2 5
2 4 1
1 1 6
2 3 3
2 1 3
```

### 样例输出 #2

```
1
5
-1
3
6
2
5
-1
5
3
6
4
4
```

## 提示

### 制約

- $ 1\leq\ N,Q\leq\ 2\times\ 10^5 $
- タイプ $ 1 $ のクエリにおいて、$ 1\leq\ u\lt\ v\leq\ N $
- タイプ $ 2 $ のクエリにおいて、$ 1\leq\ v\leq\ N,\ 1\leq\ k\leq\ 10 $
- 入力は全て整数
 
### Sample Explanation 1

\- $ 1 $ 個目のクエリについて、頂点 $ 1 $ と頂点 $ 2 $ の間に辺が追加されます。 - $ 2 $ 個目のクエリについて、頂点 $ 1 $ と連結な頂点は $ 1,2 $ の $ 2 $ つです。この中で $ 1 $ 番目に大きい $ 2 $ を出力します。 - $ 3 $ 個目のクエリについて、頂点 $ 1 $ と連結な頂点は $ 1,2 $ の $ 2 $ つです。この中で $ 2 $ 番目に大きい $ 1 $ を出力します。 - $ 4 $ 個目のクエリについて、頂点 $ 1 $ と連結な頂点は $ 1,2 $ の $ 2 $ つです。$ 3 $ 個未満なので `-1` を出力します。 - $ 5 $ 個目のクエリについて、頂点 $ 1 $ と頂点 $ 3 $ の間に辺が追加されます。 - $ 6 $ 個目のクエリについて、頂点 $ 2 $ と頂点 $ 3 $ の間に辺が追加されます。 - $ 7 $ 個目のクエリについて、頂点 $ 3 $ と頂点 $ 4 $ の間に辺が追加されます。 - $ 8 $ 個目のクエリについて、頂点 $ 1 $ と連結な頂点は $ 1,2,3,4 $ の $ 4 $ つです。この中で $ 1 $ 番目に大きい $ 4 $ を出力します。 - $ 9 $ 個目のクエリについて、頂点 $ 1 $ と連結な頂点は $ 1,2,3,4 $ の $ 4 $ つです。この中で $ 3 $ 番目に大きい $ 2 $ を出力します。 - $ 10 $ 個目のクエリについて、頂点 $ 1 $ と連結な頂点は $ 1,2,3,4 $ の $ 4 $ つです。$ 5 $ 個未満なので `-1` を出力します。

## 思路
k最大只有10，所以直接在merge时维护即可，如果set[u]小于10直接添加，否则如果大于最小值，直接删除最小值并添加即可。

## AC代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define INF 0x3f3f3f3f3f3f3f3f
#define L(i, j, k, len) for(int i = (j); i < (k); i+=(len))
#define R(i, j, k, len) for(int i = (j); i > (k); i-=(len))
#define all(x) (x).begin(),(x).end()
#define allp(x,n) (x).begin()+(n),(x).end()
#define ms(x,y) memset(x,y,sizeof(x))
#define dbg(x) cerr<<__LINE__<<" | "<<#x<<" = "<<x<<"\n"
#define dbgl(i,x) cerr<<__LINE__<<" ["<<#i<<"]: "<<i<<" -> { "<<#x<<" = "<<x<<" }\n"
#define ok cerr<<"ok"<<"\n"
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
    int n,m;
    cin>>n>>m;
    vector<set<int>> st(n+1);
    auto add_st = [&](int u,int x){
        if(st[u].size()<10){
            st[u].insert(x);
        }else{
            if(*st[u].begin()<x){
                st[u].erase(st[u].begin());
                st[u].insert(x);
            }
        }
    };
    vector<int> p(n+1,0);
    iota(all(p),0);
    function<int(int)> find = [&](int x){
        if(x!=p[x]){
            p[x]=find(p[x]);
        }
        return p[x];
    };  
    auto merge = [&](int x,int y){
        x=find(x);
        y=find(y);
        if(x==y){
            return false;
        }
        for(auto &v:st[y]){
            add_st(x,v);
        }
        p[y]=x;
        return true;
    };
    for(int i=1;i<=n;i++){
        add_st(i,i);
    }
    for(int i=0;i<m;i++){
        int op;
        cin>>op;
        if(op==1){
            int u,v;
            cin>>u>>v;
            merge(u,v);
        }else{
            int u,k;
            cin>>u>>k;
            u = find(u);
            int temp=0;
            auto iter = st[u].rbegin();
            for(;iter!=st[u].rend();iter++){
                temp++;
                if(temp==k){
                    cout<<(*iter)<<"\n";
                    break;
                }
            }
            if(temp<k){
                cout<<-1<<"\n";
            }
        }
    }
}
inline void prework(){
    
}
signed main(){
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