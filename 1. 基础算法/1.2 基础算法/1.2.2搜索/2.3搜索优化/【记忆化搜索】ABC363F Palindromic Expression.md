# [ABC 363 F] Palindromic Expression

## 题面翻译

给定一个整数 $n$ ，构造出符合下面要求的字符串：

+ 只包含字符 `1` 到 `9` 和 `*` 。

+ 是一个回文字符串。

+ 作为表达式求值后的结果等于 $n$ 。

如果存在这样的字符串，可以输出任意一个；如果不存在这样的字符串，输出 `-1` 。

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc363/tasks/abc363_f

整数 $ N $ が与えられます。次の条件を全て満たす文字列 $ S $ としてあり得るものを $ 1 $ 個出力してください。そのような文字列が存在しなければ `-1` を出力してください。

- $ S $ は `1`, `2`, `3`, `4`, `5`, `6`, `7`, `8`, `9` および `*` (乗算記号) からなる長さ $ 1 $ 以上 $ 1000 $ 以下の文字列である。
- $ S $ は回文である。
- $ S $ の先頭の文字は数字である。
- $ S $ を式として評価した値が $ N $ と一致する。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ N $

## 输出格式

問題文の条件を満たす文字列が存在する場合はその文字列を、そうでない場合は `-1` を出力せよ。

## 样例 #1

### 样例输入 #1

```
363
```

### 样例输出 #1

```
11*3*11
```

## 样例 #2

### 样例输入 #2

```
101
```

### 样例输出 #2

```
-1
```

## 样例 #3

### 样例输入 #3

```
3154625100
```

### 样例输出 #3

```
2*57*184481*75*2
```

## 提示

### 制約

- $ 1\ \leq\ N\ \leq\ 10^{12} $
- $ N $ は整数
 
### Sample Explanation 1

$ S\ = $ `11\*3\*11` は問題文の条件を満たします。他に条件を満たす文字列として $ S= $ `363` があります。

### Sample Explanation 2

$ S $ は `0` を含んではいけない点に注意してください。


## 题解
本题的思路是，枚举我们的 n 的所有可能的因子，然后看删除我们的这一个因子和我们的对应的回文因子后，我们的对应的元素是否是会问的，如果是，我们输出答案，否则我们输出-1. 注意我们**判断回文的时候可以通过一个技巧来进行**。就是判断我们的当数字是否等于**反转后我们的数字**。

```cpp
#include <bits/stdc++.h>
#define int long long
#define endl '\n'
int INF=0x3f3f3f3f3f3f3f3f;
using namespace std;
typedef pair<int,int> PII;
void init(){
    
}
bool nozero(int x){
    if(x==0){
        return 0;
    }
    while(x){
        if(x%10==0){
            return 0;
        }
        x/=10;
    }
    return 1;
}
int rev(int x){
    int ans=0;
    while(x){
        ans=ans*10+x%10;
        x/=10;
    }
    return ans;
}
string dfs(int n){
    if(nozero(n)&&n==rev(n)){
        return to_string(n);
    }
    for(int x=2;x*x<=n;x++){
        if(n%x==0&&nozero(x)==1){
            int y=rev(x);
            if(n%(x*y)!=0){
                continue;
            }
            string ret=dfs(n/x/y);
            if(n/x%y==0&&ret.size()){
                return to_string(x)+"*"+ret+"*"+to_string(y);
            }
        }
    }
    return "";
}
void solve(){
    int n;
    cin>>n;
    string s=dfs(n);
    if(s.size()==0){
        cout<<-1<<endl;
    }else{
        cout<<s<<endl;
    }   
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