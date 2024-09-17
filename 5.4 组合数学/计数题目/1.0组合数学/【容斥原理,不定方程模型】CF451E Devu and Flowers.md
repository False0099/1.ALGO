# Devu and Flowers

## 题面翻译

Devu 有 $n$ 个花瓶，第 $i$ 个花瓶里有 $f_i$ 朵花。他现在要选择 $s$ 朵花。

你需要求出有多少种方案。两种方案不同当且仅当两种方案中至少有一个花瓶选择花的数量不同。

答案对 $10^9+7$ 取模。

$1\le n\le 20,0\le f_i\le 10^{12},0\le s\le 10^{14}$

## 题目描述

Devu wants to decorate his garden with flowers. He has purchased $ n $ boxes, where the $ i $ -th box contains $ f_{i} $ flowers. All flowers in a single box are of the same color (hence they are indistinguishable). Also, no two boxes have flowers of the same color.

Now Devu wants to select exactly $ s $ flowers from the boxes to decorate his garden. Devu would like to know, in how many different ways can he select the flowers from each box? Since this number may be very large, he asks you to find the number modulo $ (10^{9}+7) $ .

Devu considers two ways different if there is at least one box from which different number of flowers are selected in these two ways.

## 输入格式

The first line of input contains two space-separated integers $ n $ and $ s $ ( $ 1<=n<=20 $ , $ 0<=s<=10^{14} $ ).

The second line contains $ n $ space-separated integers $ f_{1}, f_{2},...\ f_{n} $ ( $ 0<=f_{i}<=10^{12} $ ).

## 输出格式

Output a single integer — the number of ways in which Devu can select the flowers modulo $ (10^{9}+7) $ .

## 样例 #1

### 样例输入 #1

```
2 3
1 3
```

### 样例输出 #1

```
2
```

## 样例 #2

### 样例输入 #2

```
2 4
2 2
```

### 样例输出 #2

```
1
```

## 样例 #3

### 样例输入 #3

```
3 5
1 3 2
```

### 样例输出 #3

```
3
```

## 提示

Sample 1. There are two ways of selecting $ 3 $ flowers: $ {1,2} $ and $ {0,3} $ .

Sample 2. There is only one way of selecting $ 4 $ flowers: $ {2,2} $ .

Sample 3. There are three ways of selecting $ 5 $ flowers: $ {1,2,2} $ , $ {0,3,2} $ , and $ {1,3,1} $ .

## 题解
我们本题可以可以通过我们的一个转换，转换为我们求不定方程的对应解是什么。这里，我们就有：
$x_{1}+\dots+x_{n}=s$,并且我们的限制条件有：$0\leq x_{i}\leq f_{i}$ 因此，我们就转换为了我们的典型模型。
我们的方法是：计算我们的每一个
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;

const int ll p=1000000007;

int k;
ll r,n[25],inv[25];

ll pow(ll a,ll b,ll p){
    ll ans=1;
    while(b){
        if (b%2) ans=(ans*a)%p;
        b/=2;
        a=(a*a)%p;
    }
    return ans;
}

void get_inv(ll n,ll p){
    inv[1]=1;
    for (ll i=2;i<=n;i++){
        inv[i]=inv[p%i]*(p-p/i)%p;
    }
}

int C(ll y,ll x){
    if (y<0||x<0||y<x) return 0;
    y%=p;
    if (y==0 || x==0) return 1;
    ll ans=1;
    for (int i=0;i<x;i++){
        ans=1ll*ans*(y-i)%p;
    }
    for (int i=1;i<=x;i++){
        ans=1ll*ans*inv[i]%p;
    }
    return ans;
}

int main(){
    get_inv(20,p);
    scanf("%d%lld",&k,&r);
    ll ans=C(k+r-1,k-1);
    for (int i=1;i<=k;i++){
        scanf("%lld",&n[i]);
    }
    
    for (int x=1;x<1<<k;x++){//有k种限制条件
        ll t=k+r,num=0;
        for (int i=0;i<k;i++){
            if (x>>i & 1) num++,t-=n[i+1];//我们计算第k种和前面的同时生效我们的方案数
        }
        t-=num+1;
        if (num%2==1) ans=(ans-C(t,k-1))%p;
        else ans=(ans+C(t,k-1))%p;
    }
    printf("%lld",(ans+p)%p);
    return 0;
}
```