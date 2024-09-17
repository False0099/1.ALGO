# [ARC 134 D] Concatenate Subsequences

## 题面翻译

给定一个长度为 $2N$ 的正整数序列 $a$，你需要在前 $N$ 个数中删除若干个数（不能全删），如果删除了第 $i$ 个数，那么第 $i+N$ 个数也会被删除，求出在所有的删除方案中，最终留下的数列字典序最小的方案，输出最后留下的数列。

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc134/tasks/arc134_d

長さ $ 2 N $ の数列 $ a $ が与えられます。

すぬけ君が $ (1,2,\ \ldots,\ N) $ の**空でない**（連続するとは限らない）部分列 $ x=(x_1, x_2,\ldots, x_k) $ を用いて、数列を作ろうとしています。作られる数列は、$ a $ の $ x_1 $ 番目、$ x_2 $ 番目、$ \ldots $、$ x_k $ 番目、$ x_{1}+N $ 番目、$ \ldots $、$ x_{k}+N $ 番目の要素を抜き出してこの順で連結した数列です。

すぬけ君が作ることができる数列のうち、辞書順最小のものを求めてください。

 数列の辞書順とは？ 相異なる数列 $ S $ と数列 $ T $ の大小を判定するアルゴリズムを以下に説明します。

以下では $ S $ の $ i $ 番目の要素を $ S_i $ のように表します。また、 $ S $ が $ T $ より辞書順で小さい場合は $ S\ \lt\ T $ 、大きい場合は $ S\ \gt\ T $ と表します。

1. $ S $ と $ T $ のうち長さが短い方の数列の長さを $ L $ とします。$ i=1,2,\dots, L $ に対して $ S_i $ と $ T_i $ が一致するか調べます。
2. $ S_i\ \neq\ T_i $ である $ i $ が存在する場合、そのような $ i $ のうち最小のものを $ j $ とします。そして、$ S_j $ と $ T_j $ を比較して、 $ S_j $ が $ T_j $ より（数として）小さい場合は $ S\ \lt\ T $ 、大きい場合は $ S\ \gt\ T $ と決定して、アルゴリズムを終了します。
3. $ S_i\ \neq\ T_i $ である $ i $ が存在しない場合、 $ S $ と $ T $ の長さを比較して、$ S $ が $ T $ より短い場合は $ S\ \lt\ T $ 、長い場合は $ S\ \gt\ T $ と決定して、アルゴリズムを終了します。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ N $ $ a_{1} $ $ \cdots $ $ a_{2 N} $

## 输出格式

すぬけ君が作ることができる数列のうち、辞書順最小のものを出力せよ。

## 样例 #1

### 样例输入 #1

```
3
2 1 3 1 2 2
```

### 样例输出 #1

```
1 2
```

## 样例 #2

### 样例输入 #2

```
10
38 38 80 62 62 67 38 78 74 52 53 77 59 83 74 63 80 61 68 55
```

### 样例输出 #2

```
38 38 38 52 53 77 80 55
```

## 样例 #3

### 样例输入 #3

```
12
52 73 49 63 55 74 35 68 22 22 74 50 71 60 52 62 65 54 70 59 65 54 60 52
```

### 样例输出 #3

```
22 22 50 65 54 52
```

## 提示

### 制約

- 与えられる入力は全て整数
- $ 1\ \leq\ N\ \leq\ 10^5 $
- $ 1\ \leq\ a_i\ \leq\ 10^9 $

### Sample Explanation 1

\- $ x\ =\ (2) $ とします。 - このとき、作られる数列は $ (1,2) $ となり辞書順最小です。

## 题解
本题，我们考虑先预处理出我们的 $a$ 的**最长不下降子序列是多少**，这一个我们可以通过我们的单调栈来进行。

之后，我们将我们和 $a$ 对应的 $b$ 记录下来，我们记为 $a+b$ 我们考虑是否还有比 $a+b$ 还要小的子序列。

我们考虑分类讨论：
假设我们有下面的形式：
1. $a=[9,9,9,9,10];b=[3,5,1,3,11]$。那么我们就**只需要保留一对**，保留我们的 $a$ 和我们的 $b$ 中对应最小的即可
2. 如果我们的右侧都满足第一个要大一些，我们考虑如果哦我们有下面的形式 $a=[2,2,2,4,4,5,6],b=[4,<4,*,*,*,*,*]$。这个时候，我们可以**把 a 之后所有和 4 有关的都删除掉**。
3. 我们考虑下面的形式：$a=[2,2,2,4,4,5,6],b=[4,>6,*,*,*,*]$。
4. 因此，我们有下面的结论：![[Pasted image 20240720175110.png]]


```c++
#include <bits/stdc++.h>
#define int long long
int INF=0x3f3f3f3f3f;
using namespace std;
void solve(){
    int n;
    cin>>n;
    vector<int> a(n);
    vector<int> b(n);
    for(int i=0;i<n;i++){
        cin>>a[i];
    }
    for(int i=0;i<n;i++){
        cin>>b[i];
    }
    stack<int> stk;
    vector<int> a_;
    vector<int> b_;
    for(int i=0;i<n;i++){
        while(stk.size()&&a[i]<stk.top()){
            stk.pop();
            a_.pop_back();
            b_.pop_back();
        }
        stk.push(a[i]);
        a_.push_back(a[i]);
        b_.push_back(b[i]);
    }
    int min_=INF;
    for(int i=0;a_.size();i++){
        if(a_[i]==a_[0]){
            min_=min(min_,b_[i]);
        }else{
            break;
        }
    }
    if(min_<=a_[0]){
        cout<<a_[0]<<" "<<min_<<endl;
        return;
    }
    vector<int> resa;
    vector<int> resb;
    for(int i=0;i<a_.size();i++){
        if(a_[i]<b_[0]){
            resa.push_back(i);
        }
        if(a_[i]<=b_[0]){
            resb.push_back(i);
        }
        if(a_[i]>b_[0]){
            break;
        }
    }
    vector<int> ans_a;
    vector<int> ans_b;
    for(auto u:resa){
        ans_a.push_back(a_[u]);
    }
    for(auto u:resa){
        ans_a.push_back(b_[u]);
    }
    for(auto u:resb){
        ans_b.push_back(a_[u]);
    }
    for(auto u:resb){
        ans_b.push_back(b_[u]);
    }
    int type=0;
    for(int i=0;i<min(ans_a.size(),ans_b.size());i++){
       if(ans_a[i]<ans_b[i]){
            type=1;
            break;
       }
       if(ans_a[i]>ans_b[i]){
            type=2;
            break;
       }
    }
    if(type==0){
        if(ans_a.size()<ans_b.size()){
            type=1;
        }else{
            type=2;
        }
    }
    if(type==1){
        for(auto u:ans_a){
            cout<<u<<" ";
        }  
        cout<<endl;
    }
    if(type==2){
        for(auto u:ans_b){
            cout<<u<<" ";
        }  
        cout<<endl;
    }
}
signed main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int t;
 //   cin>>t;
    t=1;
    while(t--){
        solve();
    }
}
```
