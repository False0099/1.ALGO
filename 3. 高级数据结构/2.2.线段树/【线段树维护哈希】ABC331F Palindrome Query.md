# [ABC 331 F] Palindrome Query

## 题面翻译

给定一个长度为 $n$ 的字符串，进行 $q$ 次操作。

操作分为两种：

1. $1\ x\ c$，表示将第 $x$ 个字符改为 $c$。

2. $2\ l\ r$，表示询问 $[l,r]$ 这个子串是否为回文串。

$n\leq10^6,\ q\leq10^5$。

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc331/tasks/abc331_f

英小文字からなる長さ $ N $ の文字列 $ S $ が与えられます。  
 以下で説明されるクエリを与えられる順に $ Q $ 個処理してください。  
 クエリは次の $ 2 $ 種類のいずれかです。

- `1 x c` : $ S $ の $ x $ 文字目を英小文字 $ c $ に変更する。
- `2 L R` : $ S $ の $ L $ 文字目から $ R $ 文字目までからなる部分文字列が回文であるならば `Yes` を、そうでないならば `No` を出力する。

## 输入格式

入力は以下の形式で標準入力から与えられる。ここで $ \text{query}_i $ は $ i $ 番目に処理するクエリである。

> $ N $ $ Q $ $ S $ $ \text{query}_1 $ $ \text{query}_2 $ $ \vdots $ $ \text{query}_Q $

各クエリは以下のいずれかの形式で与えられる。

> $ 1 $ $ x $ $ c $

> $ 2 $ $ L $ $ R $

## 输出格式

問題文の指示に従ってクエリへの答えを改行区切りで出力せよ。

## 样例 #1

### 样例输入 #1

```
7 8
abcbacb
2 1 5
2 4 7
2 2 2
1 5 c
2 1 5
2 4 7
1 4 c
2 3 6
```

### 样例输出 #1

```
Yes
No
Yes
No
Yes
Yes
```

## 提示

### 制約

- $ 1\ \leq\ N\ \leq\ 10^6 $
- $ 1\ \leq\ Q\ \leq\ 10^5 $
- $ S $ は英小文字からなる長さ $ N $ の文字列
- $ 1\ \leq\ x\ \leq\ N $
- $ c $ は英小文字
- $ 1\ \leq\ L\ \leq\ R\ \leq\ N $
- $ N,\ Q,\ x,\ L,\ R $ は整数
 
### Sample Explanation 1

はじめ、$ S\ = $ `abcbacb` です。 $ 1 $ 番目のクエリについて、$ S $ の $ 1 $ 文字目から $ 5 $ 文字目までからなる文字列は `abcba` で、これは回文です。よって `Yes` を出力します。 $ 2 $ 番目のクエリについて、$ S $ の $ 4 $ 文字目から $ 7 $ 文字目までからなる文字列は `bacb` で、これは回文ではありません。よって `No` を出力します。 $ 3 $ 番目のクエリについて、$ S $ の $ 2 $ 文字目から $ 2 $ 文字目までからなる文字列は `b` で、これは回文です。よって `Yes` を出力します。 $ 4 $ 番目のクエリについて、$ S $ の $ 5 $ 文字目を `c` に変更します。$ S $ は `abcbccb` になります。 $ 5 $ 番目のクエリについて、$ S $ の $ 1 $ 文字目から $ 5 $ 文字目までからなる文字列は `abcbc` で、これは回文ではありません。よって `No` を出力します。 $ 6 $ 番目のクエリについて、$ S $ の $ 4 $ 文字目から $ 7 $ 文字目までからなる文字列は `bccb` で、これは回文です。よって `Yes` を出力します。 $ 7 $ 番目のクエリについて、$ S $ の $ 4 $ 文字目を `c` に変更します。$ S $ は `abccccb` になります。 $ 8 $ 番目のクエリについて、$ S $ の $ 3 $ 文字目から $ 6 $ 文字目までからなる文字列は `cccc` で、これは回文です。よって `Yes` を出力します。

## 题解
我们本题可以考虑使用我们的线段树维护哈希的方法来同时维护一个正哈希和一个反哈希。
```cpp
#include <bits/stdc++.h>
#define int long long
#define endl '\n'
int INF=0x3f3f3f3f3f3f3f3f;
using namespace std;
typedef pair<int,int> PII;
int mod1=1e9+7;
const int N=1e6+10;
int pow1[N];
void init(){
    pow1[0]=1;
    for(int i=1;i<N;i++){
        pow1[i]=(pow1[i-1]*131)%mod1;
    }
}
string s;
class SegmentTree
{
public:
    struct Node
    {
        int l, r;
        int len;
        int hash_left;
        int hash_right;
    }tr[N << 2];
    Node merge(Node x, Node y)
    {
        if (x.l == -1) return y;
        if (y.l == -1) return x;
        Node z;
        z.l=min(x.l,y.l);
        z.r=max(x.r,y.r);
        z.len=(x.len+y.len);
        z.hash_left=(x.hash_left*pow1[y.len]%mod1+y.hash_left)%mod1;
        z.hash_right=(x.hash_right+y.hash_right*pow1[x.len]%mod1)%mod1;
        return z;
    }//这里需要改 
    void pushup(int u)
    {
        tr[u] = merge(tr[u << 1], tr[u << 1 | 1]);
    }
    void build(int u, int l, int r)
    {
        tr[u] = {l, r, 1,s[l]-'a'+1,s[l]-'a'+1};
        if (l == r) return;
        int mid = l + r >> 1;
        build(u << 1, l, mid);
        build(u << 1 | 1, mid + 1, r);
        pushup(u);
    }
    void update(int u, int p, int x)
    {
        if (tr[u].l == tr[u].r)
        {
            //这里需要改 
            tr[u].hash_left=x;
            tr[u].hash_right=x;
            return;
        }
        int mid = tr[u].l + tr[u].r >> 1;
        if (p <= mid) update(u << 1, p, x);
        else update(u << 1 | 1, p, x);
        pushup(u);
    }
    Node query(int u, int l, int r)
    {
        if (tr[u].l >= l and tr[u].r <= r) 
        {
            return tr[u];
        }
        int mid = tr[u].l + tr[u].r >> 1;
        Node ret;
        ret.l = -1;
        ret.hash_left=0;
        ret.hash_right=0;
        ret.len=0;
        if (l <= mid) ret = query(u << 1, l, r);
        if (r > mid) ret = merge(ret, query(u << 1 | 1, l, r));
        return ret;
    }
}t;
void solve(){
    int n,q;
    cin>>n>>q;
    //string s;
    cin>>s;
    s=" "+s;
    t.build(1,1,n);
    while(q--){
        int op;
        cin>>op;
        if(op==2){
            int l,r;
            cin>>l>>r;
            auto u=t.query(1,l,r);
            //cerr<<u.hash_left<<" "<<u.hash_right<<" "<<u.len<<endl;
            if(u.hash_left==u.hash_right){
                cout<<"Yes"<<endl;
            }else{
                cout<<"No"<<endl;
            }
        }else{
            int pos;
            cin>>pos;
            char c;
            cin>>c;
            t.update(1,pos,c-'a'+1);
        }
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