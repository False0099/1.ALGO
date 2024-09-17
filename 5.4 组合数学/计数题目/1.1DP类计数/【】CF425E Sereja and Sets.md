# Sereja and Sets

## 题面翻译

### 题目描述
对于一个有 $m$ 条线段的集合 $S$ 来说，定义函数 $f(S)$ 为你最多可以从这个集合中选择多少线段使得他们都不相交。端点重合也算相交。线段的右端点都小于等于 $n$。

对于给定的 $n,k$，求出有多少个满足条件的 $S$ 满足 $f(S)=k$。

### 输入格式
输入仅一行，$n,k$。$(1\le n\le 500,\ \ 0\le k\le 500)$。
### 输出格式
输出一行一个正整数，表示答案。对 $10^9+7$ 取模。

## 题目描述

Let's assume that set $ S $ consists of $ m $ distinct intervals $ [l_{1}, r_{1}] $ , $ [l_{2}, r_{2}] $ , $ ... $ , $ [l_{m}, r_{m}] $ ( $ 1<=l_{i}<=r_{i}<=n $ ; $ l_{i}, r_{i} $ are integers).

Let's assume that $ f (S) $ is the maximum number of intervals that you can choose from the set $ S $ , such that every two of them do not intersect. We assume that two intervals, $ [l_{1}, r_{1}] $ and $ [l_{2}, r_{2}] $ , intersect if there is an integer $ x $ , which meets two inequalities: $ l_{1}<=x<=r_{1} $ and $ l_{2}<=x<=r_{2} $ .

Sereja wonders, how many sets $ S $ are there, such that $ f (S)=k $ ? Count this number modulo $ 1000000007 $ $ (10^{9}+7) $ .

## 输入格式

The first line contains integers $ n $ , $ k $ $ (1<=n<=500; 0<=k<=500) $ .

## 输出格式

In a single line, print the answer to the problem modulo $ 1000000007 $ $ (10^{9}+7) $ .

## 样例 #1

### 样例输入 #1

```
3 1
```

### 样例输出 #1

```
23
```

## 样例 #2

### 样例输入 #2

```
3 2
```

### 样例输出 #2

```
32
```

## 样例 #3

### 样例输入 #3

```
2 0
```

### 样例输出 #3

```
1
```

## 样例 #4

### 样例输入 #4

```
2 2
```

### 样例输出 #4

```
2
```

## 题解
我们本题的思路是：怎么设计我们的 dp 状态，我们注意到，如果我们采用**暴力 DFS**的话，我们最后**check**的时候，可以使用贪心的做法，将我们的线段按照我们的左端点排序，排序后，如果我们的 $k$ 有增加，一定要满足 k 是一个最大值。

这里，我们就可以设我们的 $dp[i][j]$ 表示我们当前的界限是 $i$ 点，并且我们的答案为 $j$ 的总方案数是多少。这个时候，显然我们就存在下面的转移：
我们枚举下一个右端点 $k$ 进行转移。
对于 $i<l\leq r=k$ 的线段有 $k-i$ 条，其至少有一条线段存在，则贡献为 $2^{k-i}-1$。
$i<l<r=k$ 的线段都不能存在；因为，如果存在，就会在前面更新。
$i<l\leq k<r$ 的线段有 $(n-k)\times(k-i)$ 条，其存在不存在无所谓 (因为要选最多的，必然不会
选), 贡献为 $2^(n-k)\times(k-i)$。

则转移方程：
$$f_{k,j+1}=f_{i,j}\times(2^{k-i}-1)\times2^{(n-k)\times(k-i)}$$

```
#include <bits/stdc++.h>
#define int long long
#define endl '\n'
int INF=0x3f3f3f3f3f3f3f3f;
using namespace std;
typedef pair<int,int> PII;
void init(){
    
}
const int N=550;
const int K=550;
const int mod=1e9+7;
int qmi(int a,int b){
    int res=1;
    while(b){
        if(b&1){
            res=(res*a)%mod;
        }
        a=(a*a)%mod;
        b>>=1;
    }
    return res;
}
int f[N][K];
const int M=1e6+10;
int pow2[M];
void solve(){
    int n,k;
    cin>>n>>k; 
    pow2[0]=1;
    for(int i=1;i<=M;i++){
        pow2[i]=(pow2[i-1]*2)%mod;
    }
    f[0][0]=1;
    for(int i=0;i<=n;i++){
        for(int j=0;j<=i;j++){
            for(int k=i+1;k<=n;k++){
                f[k][j+1]=(f[k][j+1]+f[i][j]*(pow2[k-i]-1)%mod*pow2[(n-k)*(k-i)]%mod)%mod;
            }
        }
    }
    int ans=0;
    for(int i=k;i<=n;i++){
        ans=(ans+f[i][k])%mod;
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