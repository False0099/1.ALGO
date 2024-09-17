# [ABC 366 F] Maximum Composition

## 题面翻译

现在有 $N$ 个线性函数 $f_1,\dots,f_N$。函数 $f_i(x)=A_ix+B_i$。

找到一个长度为 $K$ 的序列 $p=(p_1,\dots,p_k)$，序列元素为 $K$ 个大小在 $[1,N]$ 的**不同整数**。

输出 $f_{p_1}(f_{p_2}(\dots f_{p_k}(1)\dots))$ 可能的最大值。

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc366/tasks/abc366_f

$ N $ 個の一次関数 $ f_1, f_2,\ldots, f_N $ が与えられます。$ f_i (x)=A_i\ x+B_i $ です。

$ 1 $ 以上 $ N $ 以下の**相異なる** $ K $ 個の整数からなる長さ $ K $ の数列 $ p=(p_1, p_2,\ \ldots\ p_K) $ について、$ f_{p_1}(f_{p_2}(\ldots\ f_{p_K}(1)\ldots\ )) $ としてありえる最大値を求めてください。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ N $ $ K $ $ A_1 $ $ B_1 $ $ A_2 $ $ B_2 $ $ \vdots $ $ A_N $ $ B_N $

## 输出格式

答えを整数として出力せよ。

## 样例 #1

### 样例输入 #1

```
3 2
2 3
1 5
4 2
```

### 样例输出 #1

```
26
```

## 样例 #2

### 样例输入 #2

```
10 3
48 40
34 22
24 37
45 40
48 31
49 44
45 40
44 6
35 22
39 28
```

### 样例输出 #2

```
216223
```

## 提示

### 制約

- $ 1\ \leq\ N\ \leq\ 2\ \times\ 10^{5} $
- $ 1\ \leq\ K\ \leq\ \text{min}(N, 10) $
- $ 1\ \leq\ A_i, B_i\ \leq\ 50 $ $ (1\ \leq\ i\ \leq\ N) $
- 入力はすべて整数

### Sample Explanation 1

ありえるすべての $ p $ とそれに対応する $ f_{p_1}(f_{p_2}(1)) $ の値は以下の通りです。 - $ p=\ (\ 1,2\ ) $ : $ f_1 (f_2 (1))=15 $ - $ p=\ (\ 1,3\ ) $ : $ f_1 (f_3 (1))=15 $ - $ p=\ (\ 2,1\ ) $ : $ f_2 (f_1 (1))=10 $ - $ p=\ (\ 2,3\ ) $ : $ f_2 (f_3 (1))=11 $ - $ p=\ (\ 3,1\ ) $ : $ f_3 (f_1 (1))=22 $ - $ p=\ (\ 3,2\ ) $ : $ f_3 (f_2 (1))=26 $ よって、 $ 26 $ と出力します。

## 题解
假设现在已经选出了序列 $p$,考虑怎么放 (放外层还是内层)答案更优。

钦定 $i<j$,则有两种放法：$f_i(f_j(x))$ 和 $f_j(f_i(x))$。

把 $A,B$ 代入：$A_iA_jx+A_iB_j+B_i$ 和 $A_iA_jx+A_jB_i+B_j$。发现其实只有后两项不同，我们钦定

排序后越前面的放在越里层，所以我们可以定下排序规则为：
$$A_iB_j+B_i<A_jB_i+B_j$$
移项一下：
$$\frac{A_i-1}{B_i}<\frac{A_j-1}{B_j}$$
现在取序列 $p$ 是直接取后 $k$ 个就可以了吗？

不对。因为以上排序规则只是解决了怎么放的问题，都是在已经选好了 $p$ 的前提假设下。那怎么取呢？考
虑 DP 即可。
经典二维 DP: $f_{i,j}$ 表示当前第 $i$ 个，已选 $j$ 个的最大可能答案。转移就是选与不选，由于我们的排序规则
是想越前面的放里层，所以直接从前往后转移就好了，不用倒着转移。

```
#include <bits/stdc++.h>
#define int long long
#define endl '\n'
int INF=0x3f3f3f3f3f3f3f3f;
using namespace std;
typedef pair<int,int> PII;
void init(){
    
}

void solve(){
    int n,k;
    cin>>n>>k;
    vector<PII> line(n);
    int res=1;
    for(int i=0;i<n;i++){
        cin>>line[i].first>>line[i].second;
    }
    sort(line.begin(),line.end(),[&](PII a,PII b){
        return a.second*(b.first-1)>(a.first-1)*b.second;
    });
    int f[n+1][k+1];
    for(int i=0;i<=n;i++){
        for(int j=0;j<=k;j++){
            f[i][j]=0;
        }
    }
    f[0][0]=1;
    for(int i=0;i<n;i++){
        for(int j=0;j<=k;j++){
            if(f[i][j]){
                f[i+1][j]=max(f[i+1][j],f[i][j]);
                if(j+1<=k){
                    f[i+1][j+1]=max(f[i+1][j+1],f[i][j]*line[i].first+line[i].second);
                }
            }
        }
    }
    cout<<f[n][k]<<endl;
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