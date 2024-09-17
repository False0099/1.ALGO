# [ABC 347 E] Set Add Query

## 题面翻译

### 题目翻译

给定一个长度为 $N$ 的序列 $A =(A_1,A_2,\dots,A_N)$，所有元素都初始化为 $0$。再者，给定一个初始化为空集的集合 $S$。

顺序执行以下操作 $Q$ 次，然后输出 $Q$ 次操作后序列 $A$ 的每个元素的值。第 $i$ 次操作按照以下格式进行：

- 给定一个整数 $x_i$。如果 $x_i$ 在集合 $S$ 中出现过，将 $x_i$ 从 $S$ 中移除。否则，加入 $x_i$，然后对于每个 $j =1,2,\dots,N$ 且 $j \in S$，将 $A_j$ 加上 $|S|$。

在这，$|S|$ 表示为 $S$ 的元素数量。比如，如果 $S=\{3,4,7\}$，则 $|S| =3$。

### 数据保证

- $1 \le N \le 2 \times 10^5$
- $1 \le x_i \le N$
- 所有输入均为整数

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc347/tasks/abc347_e

全ての要素が $ 0 $ で初期化された長さ $ N $ の整数列 $ A=(A_1, A_2,\ldots, A_N) $ があります。また、集合 $ S $ があります。はじめ $ S $ は空です。

以下の $ Q $ 個のクエリを順に行います。$ Q $ 個のクエリを全て処理した後の数列 $ A $ の各要素の値を求めてください。 $ i $ 番目のクエリは以下の形式です。

- 整数 $ x_i $ が与えられる。整数 $ x_i $ が $ S $ に含まれる場合、$ S $ から $ x_i $ を削除する。そうでない場合、$ S $ に $ x_i $ を追加する。次に、$ j=1,2,\ldots, N $ について、$ j\in\ S $ ならば $ A_j $ に $ |S| $ を加算する。

なお、$ |S| $ は集合 $ S $ の要素数を意味します。例えば $ S=\lbrace\ 3,4,7\rbrace $ のとき、$ |S|=3 $ です。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ N $ $ Q $ $ x_1 $ $ x_2 $ $ \ldots $ $ x_Q $

## 输出格式

クエリを全て処理した後の数列 $ A $ を以下の形式で出力せよ。

> $ A_1 $ $ A_2 $ $ \ldots $ $ A_N $

## 样例 #1

### 样例输入 #1

```
3 4
1 3 3 2
```

### 样例输出 #1

```
6 2 2
```

## 样例 #2

### 样例输入 #2

```
4 6
1 2 3 2 4 2
```

### 样例输出 #2

```
15 9 12 7
```

## 提示

### 制約

- $ 1\leq\ N, Q\leq\ 2\times 10^5 $
- $ 1\leq\ x_i\leq\ N $
- 入力される数値は全て整数

### Sample Explanation 1

$ 1 $ 番目のクエリでは、$ S $ に $ 1 $ を追加し、$ S=\lbrace\ 1\rbrace $ となります。その後、$ A_1 $ に $ |S|=1 $ を加算します。$ A=(1,0,0) $ となります。 $ 2 $ 番目のクエリでは、$ S $ に $ 3 $ を追加し、$ S=\lbrace\ 1,3\rbrace $ となります。その後、$ A_1, A_3 $ に $ |S|=2 $ を加算します。$ A=(3,0,2) $ となります。 $ 3 $ 番目のクエリでは、$ S $ から $ 3 $ を削除し、$ S=\lbrace\ 1\rbrace $ となります。その後、$ A_1 $ に $ |S|=1 $ を加算します。$ A=(4,0,2) $ となります。 $ 4 $ 番目のクエリでは、$ S $ に $ 2 $ を追加し、$ S=\lbrace\ 1,2\rbrace $ となります。その後、$ A_1, A_2 $ に $ |S|=2 $ を加算します。$ A=(6,2,2) $ となります。最終的に、$ A=(6,2,2) $ となります。


## 题解
本题，我们的一个简单的思路就是通过计算我们的每一个下表会被添加多少次，我们一个下表如果有贡献，当且仅当我们的下表在我们的集合中出现过，于是我们可以维护**每一个下标的进入时间和退出时间**，两者的时间差就是我们最后添加的大小。

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
    int n,q;
    cin>>n>>q;
    vector<int> a(n+2);
    vector<int> size_of_time(q+1,0);
    vector<int> sum_of_time(q+1,0);
    vector<int> start_time(n+1);
    set<int> st;
    for(int i=1;i<=q;i++){
        int id;
        cin>>id;
        if(st.count(id)){
            st.erase(id);
            int sz=st.size();
            //cerr<<id<<" "<<i<<" "<<start_time[id]<<endl;
            size_of_time[i]=size_of_time[i-1]-1;
            a[id]+=(sum_of_time[i-1]-sum_of_time[start_time[id]-1]);
            sum_of_time[i]=sum_of_time[i-1]+size_of_time[i];
            start_time[id]=-1;
        }else{
            st.insert(id);
            int sz=st.size();
            size_of_time[i]=size_of_time[i-1]+1;
            sum_of_time[i]=sum_of_time[i-1]+size_of_time[i];
            start_time[id]=i;
        }
    }
    for(int i=1;i<=q;i++){
//        cerr<<size_of_time[i]<<" "<<sum_of_time[i]<<endl;
    }
    for(auto id:st){
        //cerr<<id<<" "<<q<<" "<<start_time[id]<<endl;
        a[id]+=(sum_of_time[q]-sum_of_time[start_time[id]-1]);
    }
    for(int i=1;i<=n;i++){
       // a[i]=a[i]+a[i-1];
        cout<<a[i]<<" ";
    }
    cout<<endl;
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