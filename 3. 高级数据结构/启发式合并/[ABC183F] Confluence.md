# [ABC183F] Confluence

## 题面翻译

$N$ 个学生，学生 $i$ 属于班级 $C_i$，学生们会组成一个个集合（不一定同班）。

初始每位学生所属集合只包含自己，有 $Q$ 次操作：

`1 a b` 合并 $a$ 和 $b$ 所在的集合（在同一集合里则什么也不发生）。

`2 x y` 问 $x$ 所在的集合里有多少 $y$ 班的学生。

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc183/tasks/abc183_f

$ N $ 人の生徒が登校しようとしています。生徒 $ i $ はクラス $ C_i $ に属しています。

各生徒はそれぞれの家から出発したあと、他の生徒と合流を繰り返しながら学校へ向かいます。一度合流した生徒が分かれることはありません。

$ Q $ 個のクエリが与えられるので、順番に処理してください。クエリには $ 2 $ 種類あり、入力形式とクエリの内容は以下の通りです。

- `1 a b` : 生徒 $ a $ を含む集団と、生徒 $ b $ を含む集団が合流する (既に合流しているときは何も起こらない)
- `2 x y` : クエリの時点で既に生徒 $ x $ と合流している生徒(生徒 $ x $ を含む)のうち、クラス $ y $ に属している生徒の数を求める

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ N $ $ Q $ $ C_1 $ $ \ldots $ $ C_N $ $ Query_1 $ $ \vdots $ $ Query_Q $

## 输出格式

`2 x y` のクエリに対する答えを、$ 1 $ 行に $ 1 $ つずつ、順に出力せよ。

## 样例 #1

### 样例输入 #1

```
5 5
1 2 3 2 1
1 1 2
1 2 5
2 1 1
1 3 4
2 3 4
```

### 样例输出 #1

```
2
0
```

## 样例 #2

### 样例输入 #2

```
5 4
2 2 2 2 2
1 1 2
1 1 3
1 2 3
2 2 2
```

### 样例输出 #2

```
3
```

## 样例 #3

### 样例输入 #3

```
12 9
1 2 3 1 2 3 1 2 3 1 2 3
1 1 2
1 3 4
1 5 6
1 7 8
2 2 1
1 9 10
2 5 6
1 4 8
2 6 1
```

### 样例输出 #3

```
1
0
0
```

## 提示

### 制約

- $ 1\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ Q\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ C_i,a,b,x,y\ \leq\ N $
- `1 a b` のクエリにおいて、$ a\ \neq\ b $
- 入力はすべて整数

### Sample Explanation 1

$ 3 $ 番目のクエリの時点で、生徒 $ 1 $ は、生徒 $ 2,5 $ と合流しています。生徒 $ 1,2,5 $ のうちクラス $ 1 $ に属する生徒は $ 2 $ 人です。 $ 5 $ 番目のクエリの時点で、生徒 $ 3 $ は、生徒 $ 4 $ と合流しています。生徒 $ 3,4 $ のうちクラス $ 4 $ に属する生徒は $ 0 $ 人です。

### Sample Explanation 2

すでに同じ集団に属している生徒に対して、`1 a b` のクエリが与えられることもあります。

## 思路
把元素少的集合合并到元素多的集合，这样 for 的时候就可以减少复杂度

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
const int N = 2e5+10;
map<int,int> mp[N];
inline void solve(){
    int n,q;
    cin>>n>>q;
    vector<int> a(n+1,0);
    map<int,int> cla;
    L(i,1,n+1){
        cin>>a[i];
        mp[i][a[i]]++;
    }
    vector<int> p(N+2,0);
    iota(all(p),0);
    function<int(int)> find = [&](int x){
        if(x!=p[x]){
            p[x]=find(p[x]);
        }
        return p[x];
    };
    auto merge=[&](int a,int b){
        a=find(a);
        b=find(b);
        if(a==b) return false;
        if(mp[b].size()>mp[a].size()){
            swap(a,b);
        }
        p[b]=a;
        for(auto &[v,w]:mp[b]){
            mp[a][v]+=w;
        }
        return true;
    };
    L(i,0,q){
        int op;
        cin>>op;
        if(op==1){
            int a,b;
            cin>>a>>b;
            merge(a,b);
        }else{
            int x,y;
            cin>>x>>y;
            cout<<mp[find(x)][y]<<"\n";
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