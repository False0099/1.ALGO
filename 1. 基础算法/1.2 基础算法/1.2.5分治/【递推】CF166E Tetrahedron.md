# Tetrahedron

## 题面翻译

- 一只蚂蚁站在一个四面体的某个顶点上，求走过   $n$ 条棱后回到原顶点的方案总数。
- 答案对   $10 ^ 9 + 7$ 取模。
-  $\texttt{Data Range}: 1 \le n \le 10 ^ 7$。

## 题目描述

You are given a tetrahedron. Let's mark its vertices with letters $ A $ , $ B $ , $ C $ and $ D $ correspondingly.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF166E/40dcfda00eddce9e7e8701e13b2759e732ca40f3.png)An ant is standing in the vertex $ D $ of the tetrahedron. The ant is quite active and he wouldn't stay idle. At each moment of time he makes a step from one vertex to another one along some edge of the tetrahedron. The ant just can't stand on one place.

You do not have to do much to solve the problem: your task is to count the number of ways in which the ant can go from the initial vertex $ D $ to itself in exactly $ n $ steps. In other words, you are asked to find out the number of different cyclic paths with the length of $ n $ from vertex $ D $ to itself. As the number can be quite large, you should print it modulo $ 1000000007 $ ( $ 10^{9}+7 $ ).

## 输入格式

The first line contains the only integer $ n $ ( $ 1<=n<=10^{7} $ ) — the required length of the cyclic path.

## 输出格式

Print the only integer — the required number of ways modulo $ 1000000007 $ ( $ 10^{9}+7 $ ).

## 样例 #1

### 样例输入 #1

```
2
```

### 样例输出 #1

```
3
```

## 样例 #2

### 样例输入 #2

```
4
```

### 样例输出 #2

```
21
```

## 提示

The required paths in the first sample are:

- $ D-A-D $
- $ D-B-D $
- $ D-C-D $

## 题解
对于本题，我们可以考虑设计我们的状态如下：我们有 $dp[i][0]$ 表示我们走了 $i$ 步之后，还在我们的 `0` 点的方案数是多少，那么我们就有转移：$dp[i][0]=dp[i-1][1]+dp[i-1][2]+dp[i-1][3]$ 以此类推。最后我们只要输出我们的 $dp[n][0]$ 即可。

```cpp
#include <bits/stdc++.h>

int INF=0x3f3f3f3f3f;

using namespace std;

const int N=1e7+10;

const int mod=1e9+7;

int dp[N][4];

void solve(){

    int n;

    cin>>n;

    dp[0][0]=1;

    for(int i=1;i<=n;i++){

        dp[i][0]=((dp[i-1][1]+dp[i-1][2])%mod+dp[i-1][3])%mod;

        dp[i][1]=((dp[i-1][0]+dp[i-1][2])%mod+dp[i-1][3])%mod;

        dp[i][2]=((dp[i-1][0]+dp[i-1][1])%mod+dp[i-1][3])%mod;

        dp[i][3]=((dp[i-1][0]+dp[i-1][1])%mod+dp[i-1][2])%mod;

    }

    cout<<dp[n][0]<<endl;

}

signed main(){

    ios::sync_with_stdio(false),cin.tie(0);

    int t;

    t=1;

    while(t--){

        solve();

    }

}
```