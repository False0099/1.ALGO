# [ABC 359 F] Tree Degree Optimization

## 题面翻译

有 $N$ 个结点，每个结点有权值 $A_1,A_2,\ldots,A_N$，把它们连成一棵树，设第 $i$ 个结点的度数为 $d_i$，则定义这棵树的权值为：  

$$\sum_{i=1}^N d_i^2\times A_i$$  

请找出所有可以构造出的树中权值最小的树，只需要输出这个最小权值。  

可以证明答案不超过 $2^{63}$。

+ $2\le N\le 2\times 10^5$  
+ $1\le A_i\le 10^9$

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc359/tasks/abc359_f

整数列 $ A=(A_1,\ldots, A_N) $ が与えられます。 $ N $ 頂点の木 $ T $ に対して、 $ f (T) $ を以下で定めます。

- $ T $ の頂点 $ i $ の次数を $ d_i $ とする。このとき、$ f (T)=\sum_{i=1}^N\ {d_i}^2\ A_i $ とする。
 
$ f (T) $ として考えられる最小値を求めてください。

なお、制約下において答えが $ 2^{63} $ 未満となることは保証されています。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ N $ $ A_1 $ $ A_2 $ $ \ldots $ $ A_N $

## 输出格式

答えを出力せよ。

## 样例 #1

### 样例输入 #1

```
4
3 2 5 2
```

### 样例输出 #1

```
24
```

## 样例 #2

### 样例输入 #2

```
3
4 3 2
```

### 样例输出 #2

```
15
```

## 样例 #3

### 样例输入 #3

```
7
10 5 10 2 10 13 15
```

### 样例输出 #3

```
128
```

## 提示

### 制約

- $ 2\leq\ N\leq\ 2\times\ 10^5 $
- $ 1\leq\ A_i\ \leq\ 10^9 $
- 入力される数値は全て整数
 
### Sample Explanation 1

頂点 $ 1 $ と頂点 $ 2 $ を結ぶ辺、頂点 $ 2 $ と頂点 $ 4 $ を結ぶ辺、頂点 $ 4 $ と頂点 $ 3 $ を結ぶ辺からなるような木 $ T $ を考えます。 このとき $ f (T)\ =\ 1^2\times\ 3\ +\ 2^2\times\ 2+1^2\times\ 5\ +2^2\times\ 2\ =\ 24 $ です。これが $ f (T) $ の最小値であることが証明できます。

## 题解
我们本题要求将我们的 n 个点连接，最后计算我们的贡献的那一坨的值是多少，我们显然可以通过我们的一个典型的套路，**将我们的边权转换为我们的点权**，然后再通过**固定选去所有点保证联通**，然后再贪心的选取 $n-2$ 个点保证最小。

这里，我们的选择的点保证最小，因为我们是存在随着我们的变化而变化，所以我们要用一个优先队列来进行存储，来取到我们的动态最小。

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
    int n;
    cin>>n;
    vector<int> a(n);
    for(int i=0;i<n;i++){
        cin>>a[i];
    } 
    //int ans=0;
    
    priority_queue<PII,vector<PII>,greater<PII>> heap;
    int ans=0;
    for(int i=0;i<n;i++){
        heap.push({a[i]*(2*1+1),i});
        ans+=a[i];
    }
    int k=n-2;

    while(k--){
        auto [val,i]=heap.top();
        ans+=val;
        heap.pop();
        int prev_d=(val/a[i]-1)/2;
        //cerr<<prev_d<<endl;
        prev_d++;
        heap.push({a[i]*(2*prev_d+1),i});
    }
    cout<<ans<<endl;
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