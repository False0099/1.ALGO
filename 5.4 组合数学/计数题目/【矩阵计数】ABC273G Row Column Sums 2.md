# [ABC 273 G] Row Column Sums 2

## 题面翻译

给定正整数 $N$ 和两个长为 $N$ 的序列 $R_i, C_i$，求有多少个 $N\times N$ 的矩阵满足以下条件:

- 所有元素是非负整数。
- 对于所有 $1\leq i\leq N$，第 $i$ 行上所有元素之和为 $R_i$。
- 对于所有 $1\leq i\leq N$，第 $i$ 列上所有元素之和为 $C_i$。

$C_i$ , $R_i$ 都是 $0$ 到 $2$ 之间的整数。

答案对 $998,244,353$ 取模。

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc273/tasks/abc273_g

非負整数を要素とする $ N $ 次正方行列であって、下記の $ 2 $ つの条件をともに満たすものの個数を $ 998244353 $ で割ったあまりを出力してください。

- すべての $ i\ =\ 1,\ 2,\ \ldots,\ N $ について、$ i $ 行目の要素の和は $ R_i $ である。
- すべての $ i\ =\ 1,\ 2,\ \ldots,\ N $ について、$ i $ 列目の要素の和は $ C_i $ である。

入力で与えられる $ R_i $ および $ C_i $ は $ 0 $ 以上 $ 2 $ 以下の整数であることに注意してください（制約参照）。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ N $ $ R_1 $ $ R_2 $ $ \ldots $ $ R_N $ $ C_1 $ $ C_2 $ $ \ldots $ $ C_N $

## 输出格式

答えを出力せよ。

## 样例 #1

### 样例输入 #1

```
3
1 1 1
0 1 2
```

### 样例输出 #1

```
3
```

## 样例 #2

### 样例输入 #2

```
3
1 1 1
2 2 2
```

### 样例输出 #2

```
0
```

## 样例 #3

### 样例输入 #3

```
18
2 0 1 2 0 1 1 2 1 1 2 0 1 2 2 1 0 0
1 1 0 1 1 1 1 1 1 1 1 1 2 1 1 0 2 2
```

### 样例输出 #3

```
968235177
```

## 提示

### 制約

- $ 1\ \leq\ N\ \leq\ 5000 $
- $ 0\ \leq\ R_i\ \leq\ 2 $
- $ 0\ \leq\ C_i\ \leq\ 2 $
- 入力はすべて整数

### Sample Explanation 1

条件を満たす行列は下記の $ 3 $ つです。 ``` 0 1 0 0 0 1 0 0 1 ``` ``` 0 0 1 0 1 0 0 0 1 ``` ``` 0 0 1 0 0 1 0 1 0 ```

### Sample Explanation 3

$ 998244353 $ で割ったあまりを出力することに注意してください。

## 题解
本题我们考虑我们的下面的方法：我们对于我们的矩阵计数，我们的思路一般有条件例如：**行的和为 xxx，且列的和为 xxx**。这个时候，我们就可以通过我们的 dp 来进行处理，我们每一次把我们的一个行看成一个整体，考虑**这一个行对于我们的列的改变是多少**。

首先第一点，我们的**具体哪些列是 2，哪些列是 1 是不重要的**，因此，我们可以考虑**只统计对应的数量**。

例如，我们在本题中，就可以设置下面的状态: $dp[i][j][k]$ 表示我们处理完前 $i$ 行，有 $j$ 个 1 列，$k$ 个 2 列的方案数，我们因为我们的每一个总和只能是 2，所以我们就可以考虑分类讨论，我们把我们的 2 放在哪里了：
对于 $R_i=1$,考虑要么将其补全一个 $j$,要么将其去补到 $k$ 使得减少一个 $k$ 并多一个 $j$。
$R_i=1:dp(i,j,k)\leftarrow dp(i-1,j+1,k)\times(j+1)+dp(i-1,j-1,k+1)\times(k+1)$ 对于 $R_i=2$,考虑可以补全两个 $j$,或补全一个 $k$,或将两个 $k$ 转化为两个 $j$,或补全一个 $j$ 并将一个 $k$ 转换为 $j$。
$$R_i=2:dp(i,j,k)\leftarrow dp(i-1,j+2,k)\times\binom{j+2}2+dp(i-1,j,k+1)\times(k+1)+dp(i-1,j-2,k+2)\times\binom{k+2}2+dp(i-1,j,k+1)\times(k+1)\times j$$

这是我们考虑**优化**，我们发现，我们的 $i$ 确定的时候，我们的 j 和我们的 k 之间存在有关系, 我们每一次转移，我们的**两个状态之间的差值都是一个定制**，并且我们还知道了**当前的总个数**，那么我们如果想要知道当前如果采用了 $j$ 个一级列，那么我们的二级列的个数就是显然易求的了：这个时候，我们就可以写出我们的代码和转移：

```cpp
#include <bits/stdc++.h>

#define int long long

int INF=0x3f3f3f3f3f;

using namespace std;

const int N=5050;

int mod=998244353;

int dp[N][N];

void solve(){

    int n;

    cin>>n;

    vector<int> r(n+1,0);

   // vector<int> pre_sum(n+1,0);

    int sum_r=0;

    for(int i=1;i<=n;i++){

        cin>>r[i];

        sum_r+=r[i];

    }

    vector<int> c(n+1,0);

    int sum_cnt1=0;

    int sum_tot=0;

    for(int i=1;i<=n;i++){

        cin>>c[i];

        sum_tot+=c[i];

        sum_cnt1+=(c[i]==1);

    }

    //cerr<<sum_r<<" "<<sum_tot<<endl;

    if(sum_r!=sum_tot){

        cout<<0<<endl;

        return;

    }

    dp[0][sum_cnt1]=1;

    for(int i=1;i<=n;i++){

        sum_tot-=r[i];

        for(int sing=0;sing<=n;sing++){

            if((sum_tot-sing)%2!=0){

                continue;

            }

            int plu=(sum_tot-sing)/2;

            if(plu<0){

                break;

            }

            switch (r[i])

            {

                case 0:{

                    dp[i][sing]=dp[i-1][sing];

                    break;

                }

                case 1:{

                    dp[i][sing]=(dp[i][sing]+dp[i-1][sing+1]*(sing+1)%mod)%mod;

                    if(sing-1>=0){

                        dp[i][sing]=(dp[i][sing]+dp[i-1][sing-1]*(plu+1)%mod)%mod;

                    }

                    break;

                }

                case 2:{

                    dp[i][sing]=(dp[i][sing]+dp[i-1][sing+2]*((sing+2)*(sing+1)/2%mod)%mod)%mod;//选取两个1

                    dp[i][sing]=(dp[i][sing]+dp[i-1][sing]*(plu+1)%mod);//完整消去一个2

                    dp[i][sing]=(dp[i][sing]+dp[i-1][sing]*(plu+1)*(sing)%mod)%mod;//一个2一个1

                    if(sing-2>=0){

                        dp[i][sing]=(dp[i][sing]+dp[i-1][sing-2]*((plu+1)*(plu+2)/2)%mod)%mod;//选取两个2

                    }

                    break;

                }

            }

        }

    }

    cout<<dp[n][0]<<endl;

}

signed main(){

    ios::sync_with_stdio(false),cin.tie(0);

    int t;

    //cin>>t;

    t=1;

    while(t--){

        solve();

    }

}
```