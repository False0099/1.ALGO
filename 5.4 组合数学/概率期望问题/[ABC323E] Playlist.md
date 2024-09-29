# [ABC323E] Playlist

## 题面翻译

一个音乐软件的播放列表里面现在有 $n$ 首歌。第 $i$ 首的长度为 $t_i$ 秒。

一首歌播放完，另一首歌就会立马开始播放。一首歌一旦开始播放，我就会让它放完。

在 $0$ 时刻，我启动了随机播放，随机播放会在播放列表中等概率播放任意一首歌，且概率不受其他任何影响。

现在我想知道，在第 $(x+0.5)$ 时刻，第 $1$ 首歌正在被播放的概率。

Translate by 324350.

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc323/tasks/abc323_e

高橋君は $ N $ 曲からなるプレイリストを持っています。 曲 $ i $ $ (1\ \leq\ i\ \leq\ N) $ の長さは $ T_i $ 秒です。  
高橋君は時刻 $ 0 $ にプレイリストのランダム再生を開始しました。

ランダム再生では、$ N $ 曲の中から等確率で $ 1 $ つを選びその曲を最後まで再生することが繰り返されます。 ここで、曲の再生は休みなく行われ、$ 1 $ つの曲が終わったらすぐに次に選ばれた曲が始まります。 また、同じ曲が連続して選ばれる事もあります。

時刻 $ 0 $ から $ (X+0.5) $ 秒後に曲 $ 1 $ が再生されている確率を $ \text{mod}998244353 $ で求めてください。

確率 $ \text{mod\ }\ 998244353 $ の定義この問題で求める確率は必ず有理数になることが証明できます。 また、この問題の制約下では、求める確率を既約分数 $ \frac{y}{x} $ で表したときに $ x $ が $ 998244353 $ で割り切れないことが保証されます。

このとき $ xz\ \equiv\ y\ \pmod{998244353} $ を満たすような $ 0 $ 以上 $ 998244352 $ 以下の整数 $ z $ が一意に定まります。この $ z $ を答えてください。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ N $ $ X $ $ T_1 $ $ T_2 $ $ \ldots $ $ T_N $

## 输出格式

時刻 $ 0 $ から $ (X+0.5) $ 秒後にプレイリストの $ 1 $ 番目の曲が再生されている確率を $ \text{mod}998244353 $ で出力せよ。

## 样例 #1

### 样例输入 #1

```
3 6
3 5 6
```

### 样例输出 #1

```
369720131
```

## 样例 #2

### 样例输入 #2

```
5 0
1 2 1 2 1
```

### 样例输出 #2

```
598946612
```

## 样例 #3

### 样例输入 #3

```
5 10000
1 2 3 4 5
```

### 样例输出 #3

```
586965467
```

## 提示

### 制約

- $ 2\ \leq\ N\leq\ 10^3 $
- $ 0\ \leq\ X\leq\ 10^4 $
- $ 1\ \leq\ T_i\leq\ 10^4 $
- 入力はすべて整数

### Sample Explanation 1

時刻 $ 0 $ から $ 6.5 $ 秒後に曲 $ 1 $ が流れているパターンとしてあり得るのは、 - 曲 $ 1 $ $ \to $ 曲 $ 1 $ $ \to $ 曲 $ 1 $ - 曲 $ 2 $ $ \to $ 曲 $ 1 $ - 曲 $ 3 $ $ \to $ 曲 $ 1 $ の順で音楽が再生された場合であり、これらのいずれかが起こる確率は $ \frac{7}{27} $ となります。 $ 369720131\times\ 27\equiv\ 7\ \pmod{998244353} $ であるため、$ 369720131 $ を出力します。

### Sample Explanation 2

時刻 $ 0 $ から $ 0.5 $ 秒後には最初に再生された曲が再生されているため、求める確率は $ \frac{1}{5} $ となります。 同じ長さの異なる曲が存在することがあることに注意してください。

## 思路
动态规划，dp[0]=1,dp[i]=dp[i]+dp[i-t[j]]*inv

## AC代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define INF 0x3f3f3f3f3f3f3f3f
#define L(i, j, k, len) for(int i = (j); i < (k); i+=(len))
#define R(i, j, k, len) for(int i = (j); i > (k); i-=(len))
#define all(x) (x).begin(),(x).end()
#define allp(x,n) (x).begin()+(n),(x).end()
#define ms(x,y) memset(x,y,sizeof(x))
#define dbg(x) cerr<<__LINE__<<" | "<<#x<<" = "<<x<<"\n"
#define dbgl(i,x) cerr<<__LINE__<<" ["<<#i<<"]: "<<i<<" -> { "<<#x<<" = "<<x<<" }\n"
#define ok cerr<<"ok"<<"\n"
#define YES cout<<"YES"<<"\n"
#define NO  cout<<"NO"<<"\n"
#define Yes cout<<"Yes"<<"\n"
#define No  cout<<"No"<<"\n"

#ifdef KROWFEATHER
    #include<bits/KrowFeather.h>
#endif
#define int long long
using ull = unsigned long long;                                                                              
using ll = long long;
using pii = pair<int,int>;
using psi = pair<string,int>;
constexpr ll MOD = 1e9+7;
//-------------------------------------------------------->>>>>>>>>>
const int mod = 998244353;
int qpow(int a,int b){
    int res=1;while(b){if(b&1){res=res*a%mod;}a=a*a%mod;b>>=1;}return res;
}
int inv(int x){return qpow(x,mod-2);}
inline void solve(){
    int n,x;
    cin>>n>>x;
    vector<int> t(n+1,0);
    for(int i=1;i<=n;i++){
        cin>>t[i];
    }
    vector<int> dp(x+1,0);
    dp[0]=1;
    int INV = inv(n);
    for(int i=0;i<=x;i++){
        for(int j=1;j<=n;j++){
            if(t[j]<=i){
                dp[i]=(dp[i]+dp[i-t[j]]*INV%mod)%mod;
            }
        }
    }
    int ans=0;
    for(int i=max(0ll,x-t[1]+1);i<=x;i++){
        ans=(ans+dp[i])%mod;
    }
    cout<<ans*INV%mod<<"\n";
}
inline void prework(){
    
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);cout.tie(nullptr);
    cout<<fixed<<setprecision(12);
    prework();
    int T=1; 
    // cin>>T;
    while(T--){
        solve();
    }
    return 0;
}
```
