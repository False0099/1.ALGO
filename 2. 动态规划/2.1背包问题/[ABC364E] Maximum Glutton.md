# [ABC364E] Maximum Glutton

## 题面翻译

Takahashi 为 Snuke 准备了 $N$ 道菜。这些菜肴的编号从 $1$ 到 $N$，菜肴 $i$ 的**甜度**为 $A_i$，**咸度**为 $B_i$。

Takahashi 可以按照自己喜欢的顺序排列这些菜肴。Snuke 会按照排列顺序吃掉这些菜肴，但如果他吃过的菜肴的总甜度超过 $X$ 或总咸度超过 $Y$，他就不会再吃任何菜肴。

Takahashi 希望 Snuke 吃尽可能多的菜肴。求如果 Takahashi 把菜肴摆放得最合理，Snuke 最多吃的菜肴数。

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc364/tasks/abc364_e

高橋君はすぬけ君のために $ N $ 個の料理を作りました。 料理には $ 1 $ から $ N $ までの番号がつけられていて、料理 $ i $ の**甘さ**は $ A_i $、**しょっぱさ**は $ B_i $ です。

高橋君はこれらの料理を好きな順番で並べることができます。 すぬけ君は料理を並べられた順に食べていきますが、ある時点においてそれまでに食べた料理の甘さの合計が $ X $ を超えるかしょっぱさの合計が $ Y $ を超えた場合、それ以降の料理は食べません。

高橋君は、すぬけ君にできるだけ多くの料理を食べてほしいと思っています。 高橋君がうまく料理を並べたとき、すぬけ君が最大で何個の料理を食べることになるか求めてください。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ N $ $ X $ $ Y $ $ A_1 $ $ B_1 $ $ A_2 $ $ B_2 $ $ \vdots $ $ A_N $ $ B_N $

## 输出格式

答えを整数として出力せよ。

## 样例 #1

### 样例输入 #1

```
4 8 4
1 5
3 2
4 1
5 3
```

### 样例输出 #1

```
3
```

## 样例 #2

### 样例输入 #2

```
2 1 1
3 2
3 2
```

### 样例输出 #2

```
1
```

## 样例 #3

### 样例输入 #3

```
2 100 100
3 2
3 2
```

### 样例输出 #3

```
2
```

## 样例 #4

### 样例输入 #4

```
6 364 463
230 381
154 200
328 407
339 94
193 10
115 309
```

### 样例输出 #4

```
3
```

## 提示

### 制約

- $ 1\leq\ N\ \leq\ 80 $
- $ 1\leq\ A_i,B_i\ \leq\ 10000 $
- $ 1\leq\ X,Y\ \leq\ 10000 $
- 入力は全て整数

### Sample Explanation 1

高橋君が料理を $ 2,3,1,4 $ の順番で並べた場合のすぬけ君の行動を考えます。 - まず料理 $ 2 $ を食べる。ここまでに食べた料理の甘さの合計は $ 3 $、しょっぱさの合計は $ 2 $ である。 - 次に料理 $ 3 $ を食べる。ここまでに食べた料理の甘さの合計は $ 7 $、しょっぱさの合計は $ 3 $ である。 - 次に料理 $ 1 $ を食べる。ここまでに食べた料理の甘さの合計は $ 8 $、しょっぱさの合計は $ 8 $ である。 - しょっぱさの合計が $ Y=4 $ を超えたので、これ以降の料理は食べない。 よって、この並び方の場合すぬけ君は $ 3 $ 個の料理を食べることになります。 高橋君が料理をどのように並べてもすぬけ君が $ 4 $ つ全ての料理を食べることはないので、答えは $ 3 $ です。

## 思路
如果按照经典二维约数背包去做会超时，因为是N\*M\*M的，但是我们可以通过最小化咸度，通过找到第一个满足咸度小于y的下标来求解，这样可以变成N\*N\*M,dp[i][j][k],i表示到第i个食品，j是选j个，k是总甜度，求min咸度

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
// #define int long long
using ull = unsigned long long;                                                                              
using ll = long long;
using pii = pair<int,int>;
using psi = pair<string,int>;
constexpr ll MOD = 1e9+7;
//-------------------------------------------------------->>>>>>>>>>
const int N = 100;
const int M = 1e4+10;
int dp[N][N][M];
int a[N];
int b[N];
inline void solve(){
    int n,x,y;
    cin>>n>>x>>y;
    for(int i=1;i<=n;i++){
        cin>>a[i]>>b[i];
    }
    ms(dp,0x3f);
    for(int i=0;i<=n;i++){
        dp[i][0][0]=0;
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=i;j++){
            for(int k=0;k<=x;k++){
                if(a[i]<=k){
                    dp[i][j][k]=dp[i-1][j-1][k-a[i]]+b[i];
                }
                dp[i][j][k]=min(dp[i][j][k],dp[i-1][j][k]);
            }
        }
    }
    for(int i=n;i>=0;i--){
        for(int j=0;j<=x;j++){
            if(dp[n][i][j]<=y){
                cout<<min(i+1,n)<<"\n";
                return;
            }
        }
    }
    cout<<0<<"\n";
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