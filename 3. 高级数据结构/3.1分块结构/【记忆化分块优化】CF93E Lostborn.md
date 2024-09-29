# Lostborn

## 题面翻译

#### 题目描述

小 Biu 最近喜欢上一款角色扮演游戏，游戏中的每一款武器有 $k$ 个参数 $a_{1},..., a_{k}$ ，并且根据游戏说明，这些参数两两互质。

游戏中的主角为英雄，英雄发起攻击时，造成的伤害不仅与武器有关，还与英雄的力量有关。如果英雄的力量为 $n$ ，那么一次攻击造成的伤害为区间 $[1,n]$ 中不能被武器参数整除的数的个数。

现在小 Biu 获得了一把新的武器装备，他想知道用某个英雄发起攻击时，造成的伤害值为多少。



#### 输入格式

第一行包含两个整数 $ n $ 和 $ k $ ( $ 1\le n\le 10^{13} $ , $ 1\le k\le 100 $ )，表示英雄的力量和装备的参数个数；

第二行包含 $ k $ 个整数 $ a_{i} $ ( $ 1\le a_{i}\le 1000 $ )，表示装备的每个参数，这些参数两两互质。



#### 输出格式

输出一个整数，表示造成的伤害值。

## 题目描述

Igor K. very much likes a multiplayer role playing game WineAge II. Who knows, perhaps, that might be the reason for his poor performance at the university. As any person who plays the game, he is interested in equipping his hero with as good weapon and outfit as possible.

One day, as he was reading the game's forum yet again, he discovered a very interesting fact. As it turns out, each weapon in the game is characterised with $ k $ different numbers: $ a_{1},..., a_{k} $ . They are called hit indicators and according to the game developers' plan they are pairwise coprime.

The damage that is inflicted during a hit depends not only on the weapon's characteristics, but also on the hero's strength parameter. Thus, if the hero's strength equals $ n $ , than the inflicted damage will be calculated as the number of numbers on the segment ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF93E/7c9ede55f73532a1d6ca7574887c95534e61c3ff.png), that aren't divisible by any hit indicator $ a_{i} $ .

Recently, having fulfilled another quest, Igor K. found a new Lostborn sword. He wants to know how much damage he will inflict upon his enemies if he uses it.

## 输入格式

The first line contains two integers: $ n $ and $ k $ ( $ 1<=n<=10^{13} $ , $ 1<=k<=100 $ ). They are the indicator of Igor K's hero's strength and the number of hit indicators.

The next line contains space-separated $ k $ integers $ a_{i} $ ( $ 1<=a_{i}<=1000 $ ). They are Lostborn sword's hit indicators. The given $ k $ numbers are pairwise coprime.

## 输出格式

Print the single number — the damage that will be inflicted by Igor K.'s hero when he uses his new weapon.

Please, do not use the %lld specificator to read or write 64-bit integers in C++. It is preferred to use the cin, cout streams or the %I 64 d specificator.

## 样例 #1

### 样例输入 #1

```
20 3
2 3 5
```

### 样例输出 #1

```
6
```

## 样例 #2

### 样例输入 #2

```
50 2
15 8
```

### 样例输出 #2

```
41
```

## 题解
首先，我们考虑熔池，也就是正难则反，我们要求**多少个数不能被一个数整除**，可以用 $n-$ 被至少一个数整除的数组。考虑使用我们的 $dp$,我们设 $dp[i][j]$ 表示我们前 $i$ 个数里总共有多少个，能被前 $j$ 个数至少整除一次。

我们不难发现，我们的 $dp[i][j]$ 存在下面的转移：
$dp[i][j]=\frac{i}{a[j]}+dp[i][j-1]-dp\left[ \frac{i}{a[j]} \right][j-1]$

我们转移的原理如下：
其中，$\lfloor n/a_k\rfloor$ 表示 $1\sim n$ 中能被 $a_k$ 整除的数的个数，$f(n,k-1)$ 表示 $1\sim n$ 中能被 $a_1\ldots a_{k-1}$ 整
除的数的个数。
显然这两个集合可能有交，即 $1\sim n$ 中既能被 $a_k$ 整除，又能被 $a_1\ldots a_{k-1}$ 中任意一个数整除的数。如果一个数 $x$ 是这两个集合的交，那么 $\frac x{a_k}$ 一定能被 $a_1\ldots a_{k-1}$ 中任意一个数整除。那么 $\frac x{a_k}$ 的数量为 $f(\lfloor n/a_k\rfloor,k-1)$。因为 $x$ 和 $\frac x{a_k}$ ——对应，所以 $x$ 的数量也是 $f(\lfloor n/a_k\rfloor,k-1)$。

但是，我们的上面的做法是 $o(nk)$ 的，我们考虑能否优化，注意到我们的 dp 转移式子中，我们的 $i$ 只会和我们的 $\frac{i}{a[j]}$ 相关，而显然，我们的 $\frac{i}{a[j]}$ 的值只会出现至多 $\sqrt{ n }$ 个，我们于是就可以通过我们的 map 来进行记忆化，而不是通过我们的数组记忆化。

但但但是，这样做会 TLE 在某一个点上，我们考虑**再度优化**，我们考虑**只对一定范围进行记忆化**，对于超过的部分，我们直接暴力跳，这样做我们就可以极限卡过这一题。

```cpp
#include <bits/stdc++.h>

#define int long long

#define endl '\n'

int INF=0x3f3f3f3f3f3f3f3f;

using namespace std;

typedef pair<int,int> PII;

void init(){

}

const int N=1e5+10;

const int K=110;

int ans[N][K];

int a[K];

int dfs(int n,int k){

    if(n==0){

        return 0;

    }

    if(k==1){

        return n/a[1];

    }

    if(n<N&&ans[n][k]!=-1){

        return ans[n][k];

    }

    int res=n/a[k]+dfs(n,k-1)-dfs(n/a[k],k-1);

//    ans[n][k]=n/a[k]+dfs(n,k-1)-dfs(n/a[k],k-1);

    if(n<N){

        ans[n][k]=res;

    }

    return res;

}

void solve(){

    int n,k;

    cin>>n>>k;

    memset(ans,-1,sizeof ans);

//    vector<int> a(k);

    for(int i=1;i<=k;i++){

        cin>>a[i];

    }

    sort(a+1,a+1+k);

    cout<<n-dfs(n,k)<<endl;

}

signed main(){

    ios::sync_with_stdio(false),cin.tie(0);

    int t;

    t=1;

 //   cin>>t;

    init();

    while(t--){

        solve();

    }

}
```
