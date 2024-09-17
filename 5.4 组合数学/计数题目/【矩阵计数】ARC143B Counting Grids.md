# [ARC 143 B] Counting Grids

## 题面翻译

统计将 $1 \sim N^2$ 共 $N^2$ 个整数填入 $N \times N$ 的棋盘并满足对于每个格子均满足以下**至少一个条件**的方案数，对 $998244353$ 取模：

- 该格子不是所处的列的最大值
- 该格子不是所处的行的最小值

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc143/tasks/arc143_b

$ N\ \times\ N $ のマス目の各マスに $ 1 $ から $ N^2 $ までの整数を $ 1 $ つずつ書き込む方法であって， どのマスも以下の条件のうち少なくとも一方を満たすようなものの個数を $ 998244353 $ で割ったあまりを求めてください．

- そのマスに書かれている数より大きい数が書かれているマスが同じ列に存在する．
- そのマスに書かれている数より小さい数が書かれているマスが同じ行に存在する．

## 输入格式

入力は以下の形式で標準入力から与えられる．

> $ N $

## 输出格式

答えを出力せよ．

## 样例 #1

### 样例输入 #1

```
2
```

### 样例输出 #1

```
8
```

## 样例 #2

### 样例输入 #2

```
5
```

### 样例输出 #2

```
704332752
```

## 样例 #3

### 样例输入 #3

```
100
```

### 样例输出 #3

```
927703658
```

## 提示

### 制約

- $ 1\ \leq\ N\ \leq\ 500 $

### Sample Explanation 1

例えば，以下のような書き込み方は条件を満たします． ``` 13 42 ``` この場合，左上のマスは左下のマスに書かれている数より小さい数が書かれているので， $ 1 $ つ目の条件を満たします．ただし，$ 2 $ つ目の条件は満たしません．

## 题解
本题考虑正男则反，**不难看出**，我们如果一个各自不满足当且仅当有**唯一的一个数**同时是行和列的最大数。于是我们就可以考虑我们的反向方案数有多少。

首席按，我们的全排列的方案数为 $(N^2)!$,考虑怎么计算我们不满足条件的个数有多少，设不满足任何条件的数为 $i$,考虑到 $i$ 是所在列中最大的数，且是所在行中最小的数，故所在行的填法为 $A_{n^2-i}^{n-1}$,所在列的填法为 $A_{i-1}^{n-1}$,其他的地方随便填，一定满足条件，填法为 $(n-1)^2!$, 再考虑 $i$ 的位置，故得出不合法的方案数的计算式为：
$$
n^2\times(n-1)^2!\times\sum_{i=n}^{n^2-n+1}A_{n^2-i}^{n-1}A_{i-1}^{n-1}
$$

```cpp
#include <iostream>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <cstdio>

using namespace std;
const int N=250100,V=250000,mod=998244353;
#define int long long

int fac[N],inv[N];
int n,ans;

int q_pow(int a,int b){
    int res=1;
    while(b){
        if(b&1) res=res*a%mod;
        a=a*a%mod;
        b>>=1;
    }
    return res;
}

int A(int n,int m){
    if(n<m) return 0;
    return fac[n]*inv[n-m]%mod;
}

signed main(){
    scanf("%lld",&n);
    int n2=n*n;
    fac[0]=1;
    for(int i=1;i<=n2;i++) fac[i]=fac[i-1]*i%mod;
    inv[n2]=q_pow(fac[n2],mod-2);
    for(int i=n2;i>=1;i--) inv[i-1]=inv[i]*i%mod;
    for(int i=n;i<=n2-n+1;i++) 
        ans=(ans+A(n2-i,n-1)*A(i-1,n-1)%mod)%mod;
    ans=(ans*fac[(n-1)*(n-1)]%mod)*n2%mod;
    ans=(fac[n*n]-ans+mod)%mod;
    cout<<ans<<'\n';
    return 0;
}

```