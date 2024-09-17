# [ABC 350 F] Transpose

## 题面翻译

字符串 $S$ 含有大小写英文字母和 `(`、`)`，保证括号完全匹配。执行下列操作，直到无法继续执行为止：

- 选定一对 $1\le l<r\le |S|$ 使得 $s_l$ 为 `(`，$s_r$ 为 `)`，且 $S_{l+1}\ldots, S_{r-1}$ 都是英文字母。
- 令字符串 $T$ 为 $\overline{S_{r-1}S_{r-2}\ldots S_{l+1}}$，其中 $\overline s$ 为字符串 $s$ 所有字符大小写反转的结果。
- 删除 $S_{l,\ldots, r}$，然后在删除操作的位置插入字符串 $T$。

你可以参考样例以更清晰地理解这个过程。

所有操作结束后，你需要输出最终字符串。

由题目管理 @ [yummy](https://www.luogu.com.cn/user/101694) 翻译。

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc350/tasks/abc350_f

英大小文字と `(` 、 `)` からなる文字列 $ S=S_1\ S_2\ S_3\ \dots\ S_{|S|} $ が与えられます。  
 文字列 $ S $ 中の括弧は、対応が取れています。

次の操作を、操作ができなくなるまで繰り返します。

- まず、以下の条件を全て満たす整数組 $ (l, r) $ をひとつ選択する。
  - $ l\ <\ r $
  - $ S_l\ = $ `(`
  - $ S_r\ = $ `)`
  - $ S_{l+1}, S_{l+2},\dots, S_{r-1} $ は全て英大文字または英小文字である
- $ T=\overline{S_{r-1}S_{r-2}\ \dots\ S_{l+1}} $ とする。
  - 但し、 $ \overline{x} $ は $ x $ の大文字と小文字を反転させた文字列を指す。
- その後、 $ S $ の $ l $ 文字目から $ r $ 文字目までを削除し、削除した位置に $ T $ を挿入する。
 
詳細は入出力例を参照してください。

上記の操作を使って全ての `(` と `)` を除去することができ、最終的な文字列は操作の方法や順序によらないことが証明できます。  
 このとき、最終的な文字列を求めてください。

  「 $ S $ 中の括弧の対応が取れている」とは? まず、正しい括弧列を次の通り定義します。 - 正しい括弧列とは、以下のいずれかの条件を満たす文字列です。
- 空文字列
- ある正しい括弧列 $ A $ が存在して、 `(`, $ A $, `)` をこの順に連結した文字列
- ある空でない正しい括弧列 $ A, B $ が存在して、 $ A, B $ をこの順に連結した文字列
 
 
 $ S $ 中の括弧の対応が取れているとは、 $ S $ 中の `(` と `)` を順序を保って抜き出した時、それが正しい括弧列となることを指す。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ S $

## 输出格式

答えを出力せよ。

## 样例 #1

### 样例输入 #1

```
((A)y)x
```

### 样例输出 #1

```
YAx
```

## 样例 #2

### 样例输入 #2

```
((XYZ)n(X(y)Z))
```

### 样例输出 #2

```
XYZNXYZ
```

## 样例 #3

### 样例输入 #3

```
(((()))(()))(())
```

### 样例输出 #3

```

```

## 样例 #4

### 样例输入 #4

```
dF(qT(plC())NnnfR(GsdccC))PO()KjsiI((ysA)eWW)ve
```

### 样例输出 #4

```
dFGsdccCrFNNnplCtQPOKjsiIwwEysAve
```

## 提示

### 制約

- $ 1\ \le\ |S|\ \le\ 5\ \times\ 10^5 $
- $ S $ は英大小文字と `(` 、 `)` からなる
- $ S $ 中の括弧は対応が取れている
 
### Sample Explanation 1

$ S= $ `((A)y)x` に対して操作を行います。 - $ l=2, r=4 $ を選択します。このとき削除される文字列は `(A)` で、代わりに `a` が挿入されます。 - この操作の結果、 $ S= $ `(ay)x` となります。 - $ l=1, r=4 $ を選択します。このとき削除される文字列は `(ay)` で、代わりに `YA` が挿入されます。 - この操作の結果、 $ S= $ `YAx` となります。括弧を除去した結果、文字列は `YAx` となったので、これを出力してください。

### Sample Explanation 2

$ S= $ `((XYZ)n(X(y)Z))` に対して操作を行います。 - $ l=10, r=12 $ を選択します。このとき削除される文字列は `(y)` で、代わりに `Y` が挿入されます。 - この操作の結果、 $ S= $ `((XYZ)n(XYZ))` となります。 - $ l=2, r=6 $ を選択します。このとき削除される文字列は `(XYZ)` で、代わりに `zyx` が挿入されます。 - この操作の結果、 $ S= $ `(zyxn(XYZ))` となります。 - $ l=6, r=10 $ を選択します。このとき削除される文字列は `(XYZ)` で、代わりに `zyx` が挿入されます。 - この操作の結果、 $ S= $ `(zyxnzyx)` となります。 - $ l=1, r=9 $ を選択します。このとき削除される文字列は `(zyxnzyx)` で、代わりに `XYZNXYZ` が挿入されます。 - この操作の結果、 $ S= $ `XYZNXYZ` となります。括弧を除去した結果、文字列は `XYZNXYZ` となったので、これを出力してください。

### Sample Explanation 3

操作結果が空文字列になる場合もあります。


## 题解
我们本题是关于我们的**括号+反转**的一个典型的题目，我们可以采用递归的方法来思考本题。

首先，我们预处理出我们的这个字符串的**每一个括号对应的匹配位置**，之后，我们采用 dfs 递归的方法解决，我们用 $dfs(l,r)$ 表示我们现在处理我们的 $l,r$ 字符串最后的结果是什么。同时，我们还需要记录我们的右括号对应的匹配位置。

我们就有下面的方法：

$$
dfs(l,r)=
\begin{align}\{
&dfs(match[l]+1)+dfs(l+1,match[l])(s[i]=='(') \\
&s[i]+dfs(l+1,r)(other)
\end{align}\}
$$

```cpp
#include <bits/stdc++.h>
#define int long long
#define endl '\n'
int INF=0x3f3f3f3f3f3f3f3f;
using namespace std;
typedef pair<int,int> PII;
void init(){
    
}
string s;
const int N=5e5+10;
int r_pos[N];
int l_pos[N];
char trans(char s){
    if(s<='z'&&s>='a'){
        return s-'a'+'A';
    }
    if(s<='Z'&&s>='A'){
        return s-'A'+'a';
    }
}
void print(int l,int r,int reverse){
    //cerr<<l<<" "<<r<<endl;
    if(reverse==0){
        for(int i=l;i<=r;i++){
            if(s[i]=='('){
                print(i+1,r_pos[i]-1,1);
                i=r_pos[i];
            }else{
                cout<<s[i];
            }
        }
    }else{
        for(int i=r;i>=l;i--){
            if(s[i]==')'){
                print(l_pos[i]+1,i-1,0);
                i=l_pos[i];
            }else{
                cout<<trans(s[i]);
            }
        }
    }
}
void solve(){
    cin>>s;
    int n=s.length();
    stack<int> stk;
    for(int i=0;s[i];i++){
        if(s[i]=='('){
            stk.push(i);
        }
        if(s[i]==')'){
            auto u=stk.top();
            stk.pop();
            r_pos[u]=i;
            l_pos[i]=u;
        }
    }
    print(0,n-1,0);
}
signed main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int t;
    t=1;
//    cin>>t;
    init();
    while(t--){
        solve();
    }
}
```