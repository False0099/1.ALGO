# [ABC 362 E] Count Arithmetic Subsequences

## 题面翻译

给你一个长度为 $n$ 的序列 $a$，对于 $k =1 \sim n$，求出 $a$ 中长度恰好为 $k$ 的等差子序列数量。子序列中的位置可以不连续。

$1 \le n \le 80,1 \le a_i \le 10^9$。

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc362/tasks/abc362_e

長さ $ N $ の数列 $ A=(A_1, A_2,\dots, A_N) $ が与えられます。各 $ k=1,2,\dots, N $ について、$ A $ の長さ $ k $ の（連続するとは限らない）部分列であって等差数列であるようなものの個数を $ 998244353 $ で割ったあまりを求めてください。ただし、$ 2 $ つの部分列が列として同じでも、取り出す位置が異なるならば区別するものとします。

部分列とは数列 $ A $ の部分列とは、$ A $ の要素を $ 0 $ 個以上選んで削除し、残った要素を元の順序を保って並べた数列のことを指します。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ N $ $ A_1 $ $ A_2 $ $ \dots $ $ A_N $

## 输出格式

$ k=1,2,\dots, N $ に対する答えを、この順に空白区切りで一行で出力せよ。

## 样例 #1

### 样例输入 #1

```
5
1 2 3 2 3
```

### 样例输出 #1

```
5 10 3 0 0
```

## 样例 #2

### 样例输入 #2

```
4
1 2 3 4
```

### 样例输出 #2

```
4 6 2 1
```

## 样例 #3

### 样例输入 #3

```
1
100
```

### 样例输出 #3

```
1
```

## 提示

### 制約

- $ 1\ \leq\ N\ \leq\ 80 $
- $ 1\ \leq\ A_i\ \leq\ 10^9 $
- 入力はすべて整数

### Sample Explanation 1

\- 長さ $ 1 $ の部分列は全部で $ 5 $ 個あり、これらはすべて長さ $ 1 $ の等差数列です。 - 長さ $ 2 $ の部分列は全部で $ 10 $ 個あり、これらはすべて長さ $ 2 $ の等差数列です。 - 長さ $ 3 $ の部分列であって等差数列であるものは、$ (A_1, A_2, A_3), (A_1, A_2, A_5), (A_1, A_4, A_5) $ の $ 3 $ つです。 - 長さ $ 4 $ 以上の部分列であって等差数列であるものは存在しません。


## 题解
本题我们有一种显然的 dp 方式，我们既然要求我们的 dp 最终的序列树，我们显然应该考虑能不能设置**以 i 结尾的**序列的方案有多少种之类的 dp 设置思路。

显然，对于本题来说，我们可以考虑设置我们的 $dp[i][j][k]$ 表示我们以 i 结尾，上一个选择的数字为 j，长度为 k 的对应的方案数有多少种。

我们转移的时候则暴力的枚举我们的上一个数位是多少，然后检查两者之间的公差是否满足要求即可。

```cpp
#include <bits/stdc++.h>
#define int long long
#define endl '\n'
int INF=0x3f3f3f3f3f3f3f3f;
using namespace std;
typedef pair<int,int> PII;
void init(){
    
}
const int N=100;
int mod=998244353;
int f[N][N][N];
int cnt[N];
//当前位置为i，上一个位置为j,总长度为len的总方案数
void solve(){
    int n;
    cin>>n;
    vector<int> a(n+1);   
    a[0]=INF;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    for(int i=1;i<=n;i++){
        f[i][i][1]=1;
      //  cnt[1]++;
    //    cnt[1]%=mod;
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<i;j++){
            f[i][j][2]=1;
//            cnt[2]++;
  //          cnt[2]%=mod;
        }
    }
    for(int k=1;k<=n;k++){
        for(int i=1;i<k;i++){
            for(int j=1;j<i;j++){
                if(a[k]-a[i]!=a[i]-a[j]){
                    continue;
                }
                for(int len=3;len<=n;len++){
                    f[k][i][len]=((f[i][j][len-1])+f[k][i][len])%mod;
                    //cnt[len]=(cnt[len]+f[k][i][len])%mod;
                }
            }
        }
    }
    for(int len=1;len<=n;len++){
        int res=0;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                res+=f[i][j][len];
                res%=mod;
            }
        }
        cout<<res<<endl;
    }
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