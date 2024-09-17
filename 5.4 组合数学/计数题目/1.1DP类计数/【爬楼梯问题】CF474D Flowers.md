# Flowers

## 题面翻译

给定正整数 $k$。称一个 $01$ 字符串是好的当且仅当其可以通过把**连续** $k$ 个 $1$ **全部改成** $0$ 来达到全为 $0$，例如 $k=2$ 时，`000`，`0110`，`110110` 是好的而 `010`，`101` 不是好的。

多次询问，每次给定 $l,r$，询问长度在 $[l,r]$ 内的 $01$ 字符串有多少个是好的。由于结果可能过大，答案对 $10^9+7$ 取模。

## 题目描述

We saw the little game Marmot made for Mole's lunch. Now it's Marmot's dinner time and, as we all know, Marmot eats flowers. At every dinner he eats some red and white flowers. Therefore a dinner can be represented as a sequence of several flowers, some of them white and some of them red.

But, for a dinner to be tasty, there is a rule: Marmot wants to eat white flowers only in groups of size $ k $ .

Now Marmot wonders in how many ways he can eat between $ a $ and $ b $ flowers. As the number of ways could be very large, print it modulo $ 1000000007 $ ( $ 10^{9}+7 $ ).

## 输入格式

We saw the little game Marmot made for Mole's lunch. Now it's Marmot's dinner time and, as we all know, Marmot eats flowers. At every dinner he eats some red and white flowers. Therefore a dinner can be represented as a sequence of several flowers, some of them white and some of them red.

But, for a dinner to be tasty, there is a rule: Marmot wants to eat white flowers only in groups of size $ k $ .

Now Marmot wonders in how many ways he can eat between $ a $ and $ b $ flowers. As the number of ways could be very large, print it modulo $ 1000000007 $ ( $ 10^{9}+7 $ ).

## 输出格式

We saw the little game Marmot made for Mole's lunch. Now it's Marmot's dinner time and, as we all know, Marmot eats flowers. At every dinner he eats some red and white flowers. Therefore a dinner can be represented as a sequence of several flowers, some of them white and some of them red.

But, for a dinner to be tasty, there is a rule: Marmot wants to eat white flowers only in groups of size $ k $ .

Now Marmot wonders in how many ways he can eat between $ a $ and $ b $ flowers. As the number of ways could be very large, print it modulo $ 1000000007 $ ( $ 10^{9}+7 $ ).

## 样例 #1

### 样例输入 #1

```
3 2
1 3
2 3
4 4
```

### 样例输出 #1

```
6
5
5
```

## 提示

- For $ K $ = $ 2 $ and length $ 1 $ Marmot can eat ( $ R $ ).
- For $ K $ = $ 2 $ and length $ 2 $ Marmot can eat ( $ RR $ ) and ( $ WW $ ).
- For $ K $ = $ 2 $ and length $ 3 $ Marmot can eat ( $ RRR $ ), ( $ RWW $ ) and ( $ WWR $ ).
- For $ K $ = $ 2 $ and length $ 4 $ Marmot can eat, for example, ( $ WWWW $ ) or ( $ RWWR $ ), but for example he can't eat ( $ WWWR $ ).

## 题解
我们注意到，我们每一次可以选择吃的方案，就等价于我们从起点开始，能够形成的 01 字符串的种类有多少种，并且保证我们 $1$ 只能作为我们的连续段出现。

于是，我们可以考虑设 $f[n]$ 表示我们长度为 $n$ 的总方案是多少，我们每一次在这个长度为 n 的段有两种操作方法，一种是选择长度为 1 的，另一种是直接选择长度为 $k$ 的，因此，我们就有：$f[i]=f[i-1]+f[i-k]$。**我们发现这一个思路类似于我们的爬台阶问题**。这是因为，我们**最后的颜色数是固定的，也就是说我们的颜色是唯一的**。换句话说，如果我们走的是 $f[i-1]$，那么就相当于**我们最后一个是白球**，如果我们走的是 $f[i-k]$，那么相当于我们**最后 k 个都是黑球**。

显然，我们有初始状态 $f[1]=1$。那么我们腰围我们的区间长度是多少，我们只需要进行前缀和后再相减即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define mod 1000000007 
#define maxn 100001
ll t,k,i;
ll f[maxn];
ll s[maxn];
int sum(int l,int r){
    return (s[r]-s[l-1]+mod)%mod;
}
int main(){
    cin>>t>>k;
    f[0]=s[0]=1;
    f[1]=1;
    for(i=1;i<=maxn;i++){
        if(i>=k) f[i]=(f[i-1]+f[i-k])%mod;
        else f[i]=f[i-1]%mod;
        s[i]=(s[i-1]+f[i])%mod;
    }
    while (t--)
    {
        int l,r;
        cin>>l>>r;
        cout<<(sum(l,r)+mod)%mod<<endl;
    }
    
    return 0;
}
```
