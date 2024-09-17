# [ABC 231 E] Minimal payments

## 题面翻译

现有 $n$ 种硬币。

每个硬币的面额为 $A_1,A_2,\dots,A_n$。

保证对于 $\forall\ 1\le i\le n-1$，$A_{i+1}$ 是 $A_i$ 的**倍数**。

现在，你想买价值为 $x$ 元钱的物品。

求你用出的硬币个数和商家找回的硬币个数的总和的最小值是多少。

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc231/tasks/abc231_e

Atcoder 王国では $ A_1 $ 円, $ A_2 $ 円, $ \ldots $, $ A_N $ 円の $ N $ 種類の硬貨が使用されています。  
 ここで、$ 1=A_1\ <\ \ldots\ <\ A_N $ であり、全ての $ 1\leq\ i\ \leq\ N-1 $ に対し、$ A_{i+1} $ は $ A_i $ の倍数です。

硬貨のみを使って $ X $ 円を支払うとき、支払いに使う硬貨の枚数とお釣りでもらう硬貨の枚数の合計の最小値はいくつですか？

正確には、$ Y $ が $ X $ 以上の整数を自由に動く時、$ Y $ 円ちょうどを表すために必要な硬貨の枚数と、$ Y-X $ 円ちょうどを表すために必要な硬貨の枚数の和の最小値を求めてください。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ N $ $ X $ $ A_1 $ $ \ldots $ $ A_N $

## 输出格式

答えを出力せよ。

## 样例 #1

### 样例输入 #1

```
3 87
1 10 100
```

### 样例输出 #1

```
5
```

## 样例 #2

### 样例输入 #2

```
2 49
1 7
```

### 样例输出 #2

```
7
```

## 样例 #3

### 样例输入 #3

```
10 123456789012345678
1 100 10000 1000000 100000000 10000000000 1000000000000 100000000000000 10000000000000000 1000000000000000000
```

### 样例输出 #3

```
233
```

## 提示

### 制約

- 入力に含まれる値は全て整数である
- $ 1\ \leq\ N\ \leq\ 60 $
- $ 1=A_1\ <\ \ldots\ <\ A_N\ \leq\ 10^{18} $
- 全ての $ 1\leq\ i\ \leq\ N-1 $ で $ A_{i+1} $ は $ A_i $ の倍数である
- $ 1\leq\ X\ \leq\ 10^{18} $

### Sample Explanation 1

$ 100 $ 円硬貨 $ 1 $ 枚で支払いを行い、$ 10 $ 円硬貨 $ 1 $ 枚と $ 1 $ 円硬貨 $ 3 $ 枚をお釣りでもらうと、合計枚数は $ 5 $ 枚になります。

### Sample Explanation 2

$ 7 $ 円硬貨 $ 7 $ 枚で支払いを行うのが最適です。

## 题解
我们本体考虑假设我们现在有 $x$ 元的时候，我们的方案是什么，我们可以分为两种情况来讨论，一种是**用了一个大额的钱，用小额的找零**，另一种是不进行找零的操作。我们对于两种操作分别计算次数。

但是这样计算显然是有很大可能会超市的，因为我们的**值域范围回答道我们的 $1e9$**。但是，我们应该新的方法，我们可以采用**记忆化搜索**。

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
    int n,x;
    cin>>n>>x;
    vector<int> a(n+1);
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    map<PII,int> mp;
    auto dfs=[&](auto&& self,int n,int m){
        if(n==1){
            return m;
        }
        if(mp.count({n,m})){
            return mp[{n,m}];
        }
        int u=m%a[n];
        int v=(m/a[n]+1)*a[n]-m;
        int cnt1=m/a[n];
        int cnt2=(m/a[n]+1);
        int a=self(self,n-1,u)+cnt1;
        int b=self(self,n-1,v)+cnt2;
        mp[{n,m}]=min(a,b);
        return min(a,b);
    };
    cout<<dfs(dfs,n,x)<<endl;
}
signed main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int t;
    t=1;
   // cin>>t;
    init();
    while(t--){
        solve();
    }
}
```