# Diverse Garland

## 题面翻译

## 题目描述:
给一串字符，只有 `R` 和 `G` 和 `B`。问如果要让相邻 $2$ 个字符都不同，最少要改几个?
## 输入格式：
第一行：字符串的长度 $n$。$(1\leq n\leq2*10^5)$

第二行：$n$ 个字符，是给的字符串。
## 输出格式：
第一行：最少要改动几个字符。

第二行：改后的字符串。（注：有 $spj$）

## 题目描述

You have a garland consisting of $ n $ lamps. Each lamp is colored red, green or blue. The color of the $ i $ -th lamp is $ s_i $ ('R', 'G' and 'B' — colors of lamps in the garland).

You have to recolor some lamps in this garland (recoloring a lamp means changing its initial color to another) in such a way that the obtained garland is diverse.

A garland is called diverse if any two adjacent (consecutive) lamps (i. e. such lamps that the distance between their positions is $ 1 $ ) have distinct colors.

In other words, if the obtained garland is $ t $ then for each $ i $ from $ 1 $ to $ n-1 $ the condition $ t_i \ne t_{i + 1} $ should be satisfied.

Among all ways to recolor the initial garland to make it diverse you have to choose one with the minimum number of recolored lamps. If there are multiple optimal solutions, print any of them.

## 输入格式

The first line of the input contains one integer $ n $ ( $ 1 \le n \le 2 \cdot 10^5 $ ) — the number of lamps.

The second line of the input contains the string $ s $ consisting of $ n $ characters 'R', 'G' and 'B' — colors of lamps in the garland.

## 输出格式

In the first line of the output print one integer $ r $ — the minimum number of recolors needed to obtain a diverse garland from the given one.

In the second line of the output print one string $ t $ of length $ n $ — a diverse garland obtained from the initial one with minimum number of recolors. If there are multiple optimal solutions, print any of them.

## 样例 #1

### 样例输入 #1

```
9
RBGRRBRGG
```

### 样例输出 #1

```
2
RBGRGBRGR
```

## 样例 #2

### 样例输入 #2

```
8
BBBGBRRR
```

### 样例输出 #2

```
2
BRBGBRGR
```

## 样例 #3

### 样例输入 #3

```
13
BBRRRRGGGGGRR
```

### 样例输出 #3

```
6
BGRBRBGBGBGRG
```

## 题解
我们这一题首先可以通过我们的一个 dp 来进行，我们设我们的 $f[i][color]$ 为我们让我们的第 i 位颜色为 `color` ,并且我们的前面 i 个都已经满足的方案情况有多少个。

于是，我们的转移方程就可以写作:
$$\mathrm{cost(i,R)}\:=\:min(\:cost(i-1,G),\:cost(i-1,B)\:)\:+\:\begin{cases}0,s[i]=R\\1,s[i]\neq\mathbb{R}\end{cases}$$

现在，我们的问题就变成了我们的方案输出：
利用我们的一个 dp 可以反推状态，我们可以直接通过我们最后最终的状态来反推我们的结果
```cpp
#include <bits/stdc++.h>
#define rep(i,a,b) for(ll i=a;i<=b;i++)
using namespace std;
typedef long long ll;
ll n,c[200005],dp[200005][3];
string s;
 
int main(){
    while(cin>>n){
        cin>>s;
        rep(i,0,n-1)c[i]=s[i]=='R'?0:s[i]=='G'?1:2;
        dp[0][0]=dp[0][1]=dp[0][2]=1;
        dp[0][c[0]]=0;
        rep(i,1,n-1){
            dp[i][0]=min(dp[i-1][1],dp[i-1][2])+(c[i]!=0);
            dp[i][1]=min(dp[i-1][0],dp[i-1][2])+(c[i]!=1);
            dp[i][2]=min(dp[i-1][0],dp[i-1][1])+(c[i]!=2);
        }
        ll ans=min(min(dp[n-1][0],dp[n-1][1]),dp[n-1][2]);
        cout<<ans<<endl;
        ll col=-1;
        for(ll i=n-1;i>=0;i--){
            rep(j,0,2){
                if(j==col)continue;
                if(dp[i][j]==ans){
                    s[i]=(j==0?'R':j==1?'G':'B');
                    ans-=(c[i]!=j);
                    col=j;
                    break;
                }
            }
        }
        cout<<s<<endl;
    }
    return 0;
}
```