# Catching Cheaters

## 题面翻译

给我们两个字符串，让我们从中选出两个字串，算出它们的最大公共子序列长度。然后将它乘$ 4 $在减去两个字串的长度。问你这个数最大是多少。

## 题目描述

You are given two strings $ A $ and $ B $ representing essays of two students who are suspected cheaters. For any two strings $ C $ , $ D $ we define their similarity score $ S (C, D) $ as $ 4\cdot LCS (C, D) - |C| - |D| $ , where $ LCS (C, D) $ denotes the length of the Longest Common Subsequence of strings $ C $ and $ D $ .

You believe that only some part of the essays could have been copied, therefore you're interested in their substrings.

Calculate the maximal similarity score over all pairs of substrings. More formally, output maximal $ S (C, D) $ over all pairs $ (C, D) $ , where $ C $ is some substring of $ A $ , and $ D $ is some substring of $ B $ .

If $ X $ is a string, $ |X| $ denotes its length.

A string $ a $ is a substring of a string $ b $ if $ a $ can be obtained from $ b $ by deletion of several (possibly, zero or all) characters from the beginning and several (possibly, zero or all) characters from the end.

A string $ a $ is a subsequence of a string $ b $ if $ a $ can be obtained from $ b $ by deletion of several (possibly, zero or all) characters.

Pay attention to the difference between the substring and subsequence, as they both appear in the problem statement.

You may wish to read the [Wikipedia page about the Longest Common Subsequence problem](https://en.wikipedia.org/wiki/Longest_common_subsequence_problem).

## 输入格式

The first line contains two positive integers $ n $ and $ m $ ( $ 1 \leq n, m \leq 5000 $ ) — lengths of the two strings $ A $ and $ B $ .

The second line contains a string consisting of $ n $ lowercase Latin letters — string $ A $ .

The third line contains a string consisting of $ m $ lowercase Latin letters — string $ B $ .

## 输出格式

Output maximal $ S (C, D) $ over all pairs $ (C, D) $ , where $ C $ is some substring of $ A $ , and $ D $ is some substring of $ B $ .

## 样例 #1

### 样例输入 #1

```
4 5
abba
babab
```

### 样例输出 #1

```
5
```

## 样例 #2

### 样例输入 #2

```
8 10
bbbbabab
bbbabaaaaa
```

### 样例输出 #2

```
12
```

## 样例 #3

### 样例输入 #3

```
7 7
uiibwws
qhtkxcn
```

### 样例输出 #3

```
0
```

## 提示

For the first case:

Abb from the first string and abab from the second string have LCS equal to abb.

The result is $ S (abb, abab) = (4 \cdot |abb| $ ) - $ |abb| $ - $ |abab| $ = $ 4 \cdot 3 - 3 - 4 = 5 $ .

## 题解
本题，可以通过 DP 来解决，我们设 $dp[i][j]$ 表示我们的第一个字符串的前 $i$ 个字符和我们的第二个字符串的后 $i$ 个字符匹配，我们最终答案的最大值是多少。显然，1 如果我们的 $s[i]=t[j]$，那么我们的 $dp[i][j]=dp[i-1][j-1]+2$,否则我们 $dp[i][j]=\max(dp[i-1][j],dp[i][j-1])-1$。

```
#include <bits/stdc++.h>
#define int long long
#define endl '\n'
int INF=0x3f3f3f3f3f3f3f3f;
using namespace std;
typedef pair<int,int> PII;
void init(){
    
}
const int N=5050;
int dp[N][N];
void solve(){
    int n,m;
    cin>>n>>m;
    string s,t;
    cin>>s>>t;
   // memset(dp,-INF,sizeof dp);
    dp[0][0]=0;
    int res=0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            dp[i][j]=max(0ll,max(dp[i-1][j],dp[i][j-1])-1);
            if(s[i-1]==t[j-1]){
                dp[i][j]=max(dp[i][j],dp[i-1][j-1]+2);
            }
            res=max(res,dp[i][j]);
        }
    }
    cout<<res<<endl;
}
signed main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int t;
    t=1;
    //cin>>t;
    init();
    while(t--){
        solve();
    }
}
```