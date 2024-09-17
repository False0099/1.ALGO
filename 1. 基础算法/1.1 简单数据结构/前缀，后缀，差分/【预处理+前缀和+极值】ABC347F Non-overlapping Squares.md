# [ABC 347 F] Non-overlapping Squares

## 题面翻译

给定一个 $N \times N$ 的矩阵，在里面选出三个不相交的 $M \times M$ 的矩阵使得矩阵中的数字和最大，求这个最大和。

$1 \leq N \leq 1000, 1 \leq M \leq N/2$。

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc347/tasks/abc347_f

$ N\times\ N $ のマス目があり、上から $ i $ 行目、左から $ j $ 列目 $ (1\leq\ i, j\leq\ N) $ のマスには整数 $ A\ _\ {i, j} $ が書かれています。

整数 $ M $ が与えられます。 $ M\times\ M $ のマス目を重ならないように $ 3 $ つ選ぶときの、選んだマス目に書かれている整数の総和としてありえる最大値を求めてください。

 問題の厳密な定義整数の $ 6 $ つ組 $ (i\ _\ 1, j\ _\ 1, i\ _\ 2, j\ _\ 2, i\ _\ 3, j\ _\ 3) $ が次の $ 3 $ つの条件を満たしているとき、**良い $ 6 $ つ組**ということにします。 - $ 1\leq\ i\ _\ k\leq\ N-M+1\ (k=1,2,3) $
- $ 1\leq\ j\ _\ k\leq\ N-M+1\ (k=1,2,3) $
- $ k\neq\ l\ (k, l\in\lbrace 1,2,3\rbrace) $ ならば、$ \lbrace (i, j)\mid\ i\ _\ k\leq\ i\lt\ i\ _\ k+M\wedge\ j\ _\ k\leq\ j\lt\ j\ _\ k+M\rbrace $ と $ \lbrace (i, j)\mid\ i\ _\ l\leq\ i\lt\ i\ _\ l+M\wedge\ j\ _\ l\leq\ j\lt\ j\ _\ l+M\rbrace $ に共通部分はない
 
 良い $ 6 $ つ組 $ (i\ _\ 1, j\ _\ 1, i\ _\ 2, j\ _\ 2, i\ _\ 3, j\ _\ 3) $ に対する値 $ \displaystyle\ \sum\ _\ {k=1}\ ^\ 3\sum\ _\ {i=i\ _\ k}\ ^\ {i\ _\ k+M-1}\sum\ _\ {j=j\ _\ k}\ ^\ {j\ _\ k+M-1}A\ _\ {i, j} $ の最大値を求めてください。 この問題の制約のもとで良い $ 6 $ つ組が存在することが示せます。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ N $ $ M $ $ A\ _\ {1,1} $ $ A\ _\ {1,2} $ $ \ldots $ $ A\ _\ {1, N} $ $ A\ _\ {2,1} $ $ A\ _\ {2,2} $ $ \ldots $ $ A\ _\ {2, N} $ $ \vdots $ $ \ \vdots $ $ \ddots $ $ \vdots $ $ A\ _\ {N, 1} $ $ A\ _\ {N, 2} $ $ \ldots $ $ A\ _\ {N, N} $

## 输出格式

答えを出力せよ。

## 样例 #1

### 样例输入 #1

```
7 3
3 1 4 1 5 9 2
6 5 3 5 8 9 7
9 3 2 3 8 4 6
2 6 4 3 3 8 3
2 7 9 5 0 2 8
8 4 1 9 7 1 6
9 3 9 9 3 7 5
```

### 样例输出 #1

```
154
```

## 样例 #2

### 样例输入 #2

```
7 1
3 1 4 1 5 9 2
6 5 3 5 8 9 7
9 3 2 3 8 4 6
2 6 4 3 3 8 3
2 7 9 5 0 2 8
8 4 1 9 7 1 6
9 3 9 9 3 7 5
```

### 样例输出 #2

```
27
```

## 样例 #3

### 样例输入 #3

```
16 4
74 16 58 32 97 52 43 51 40 58 13 24 65 11 63 29
98 75 40 77 15 50 83 85 35 46 38 37 56 38 63 55
95 42 10 70 53 40 25 10 70 32 33 19 52 79 74 58
33 91 53 11 65 63 78 77 81 46 81 63 11 82 55 62
39 95 92 69 77 89 14 84 53 78 71 81 66 39 96 29
74 26 60 55 89 35 32 64 17 26 74 92 84 33 59 82
23 69 10 95 94 14 58 58 97 95 62 58 72 55 71 43
93 77 27 87 74 72 91 37 53 80 51 71 37 35 97 46
81 88 26 79 78 30 53 68 83 28 59 28 74 55 20 86
93 13 25 19 53 53 17 24 69 14 67 81 10 19 69 90
88 83 62 92 22 31 27 34 67 48 42 32 68 14 96 87
44 69 25 48 68 42 53 82 44 42 96 31 13 56 68 83
63 87 24 75 16 70 63 99 95 10 63 26 56 12 77 49
94 83 69 95 48 41 40 97 45 61 26 38 83 91 44 31
43 69 54 64 20 60 17 15 62 25 58 50 59 63 88 70
72 95 21 28 41 14 77 22 64 78 33 55 67 51 78 40
```

### 样例输出 #3

```
3295
```

## 提示

### 制約

- $ 2\leq\ N\leq\ 1000 $
- $ 1\leq\ M\leq\ N/2 $
- $ 0\leq\ A\ _\ {i, j}\leq 10\ ^\ 9 $
- 入力はすべて整数
 
### Sample Explanation 1

与えられたグリッドから、以下の図のように $ 3\times 3 $ のマス目を $ 3 $ つ選ぶと（これは $ (i\ _\ 1, j\ _\ 1, i\ _\ 2, j\ _\ 2, i\ _\ 3, j\ _\ 3)=(1,5,2,1,5,2) $ とすることに対応します）、選んだマス目に書かれている数の合計は $ 154 $ となります。 ![](https://img.atcoder.jp/abc347/f24ee82455befb7c9af500437f79cde8.png) 問題文の条件を満たす選び方であって選んだマス目に書かれている数の合計が $ 155 $ 以上であるものは存在しないため、$ 154 $ を出力してください。

### Sample Explanation 2

以下のように選ぶのが最適です。 ![](https://img.atcoder.jp/abc347/d380b6de908ba5259451d798e7851be3.png)

### Sample Explanation 3

以下のように選ぶのが最適です。 ![](https://img.atcoder.jp/abc347/592c9536ace6712dd7532131b8da15be.png)

## 题解
本题是我们的洛谷 P 3625 的双倍经验，我们只需要修改我们对应的输入输出即可得到我们的答案。

```cpp
#include <bits/stdc++.h>
#define int long long
#define endl '\n'
int INF=0x3f3f3f3f3f3f3f3f;
using namespace std;
typedef pair<int,int> PII;
void init(){
    
}
const int N=1109;
int a[N][N];
int s[N][N];
int s_m[N][N];
int pref[N][N];
int suf[N][N];
int row[N];//横向最大值
int between_row[N][N];
int rev_row[N];//倒着的横向最大值
int col[N];//纵向最大值
int rev_col[N];
int between_col[N][N];
int _0_0[N][N];//西北角
int _0_n[N][N];//东北角
int _n_0[N][N];//西南角
int _n_n[N][N];//东南角
int n;
void print(){
    cerr<<"debug"<<endl;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cerr<<a[i][j]<<" ";
        }
        cerr<<endl;
    }
}
void solve(){
    int m;
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cin>>a[i][j];
        }
    }   
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            s[i][j]=s[i-1][j]+s[i][j-1]+a[i][j]-s[i-1][j-1];
        }
    }
   
    //print(s);
    auto calc=[&](int x1,int y1,int x2,int y2){
        //cerr<<x1<<" "<<y1<<" "<<x2<<" "<<y2<<endl;
        //exit(0);
        //cerr<<s[x2][y2]<<" "<<s[x2][y1-1]<<" "<<s[x1-1][y2]<<" "<<s[x1-1][x2-1]<<endl;
        return s[x2][y2]-s[x2][y1-1]-s[x1-1][y2]+s[x1-1][y1-1];
    };
    for(int i=1;i<=n;i++){
        if(i-m+1<1){
            continue;
        }
        for(int j=1;j<=n;j++){
            if(j-m+1<1){
                continue;
            }
            s_m[i][j]=calc(i-m+1,j-m+1,i,j);
        }
    }
    // cerr<<"debug"<<endl;
    // for(int i=1;i<=n;i++){
    //     for(int j=1;j<=n;j++){
    //         cerr<<s_m[i][j]<<" ";
    //     }
    //     cerr<<endl;
    // }
    // cerr<<"debug"<<endl;
    // for(int i=1;i<=n;i++){
    //     for(int j=1;j<=n;j++){
    //         cerr<<s[i][j]<<" ";
    //     }
    //     cerr<<endl;
    // }
    //计算横向的最大值
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            row[i]=max(row[i],s_m[i][j]);
        }
        //row[i]=max(row[i],row[i-1]);
    }
    // cerr<<"debug"<<endl;
    // for(int i=1;i<=n;i++){
    //     cerr<<row[i]<<" ";
    // }
    // cerr<<endl;
    for(int i=1;i<=n;i++){
        between_row[i][i+m-1]=row[i+m-1];

//        between_row[i][i]=row[i];
        for(int j=i+m;j<=n;j++){
            between_row[i][j]=max(between_row[i][j-1],row[j]);
        }
    }
    // cerr<<"debug"<<endl;
    // for(int i=1;i<=n;i++){
    //     for(int j=1;j<=n;j++){
    //         cerr<<between_row[i][j]<<" ";
    //     }
    //     cerr<<endl;
    // }

    for(int i=n-m+1;i>=1;i--){
        rev_row[i]=max(row[i+m-1],rev_row[i+1]);
    }

    for(int i=1;i<=n;i++){
        row[i]=max(row[i],row[i-1]);
    }
    //计算纵向的最大值
    
    for(int j=1;j<=n;j++){
        for(int i=1;i<=n;i++){
            col[j]=max(col[j],s_m[i][j]);
        }
    }
    // cerr<<"debug"<<endl;
    // for(int i=1;i<=n;i++){
    //     cerr<<col[i]<<" "<<endl;
    // }
    // exit(0);
    for(int i=1;i<=n;i++){
        //between_col[i][i]=col[i];
        between_col[i][i+m-1]=col[i+m-1];
        for(int j=i+m;j<=n;j++){
            between_col[i][j]=max(between_col[i][j-1],col[j]);
        }
    }
    // cerr<<"debug"<<endl;
    // for(int i=1;i<=n;i++){
    //     for(int j=1;j<=n;j++){
    //         cerr<<between_col[i][j]<<" ";
    //     }
    //     cerr<<endl;
    // }
    for(int i=n-m+1;i>=1;i--){
        rev_col[i]=max(col[i+m-1],rev_col[i+1]);
    }
    for(int j=1;j<=n;j++){
        col[j]=max(col[j],col[j-1]);
    }
    //计算四个角的最大值：
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(i-m+1>=1&&j-m+1>=1){
                _0_0[i][j]=max({_0_0[i-1][j],_0_0[i][j-1],calc(i-m+1,j-m+1,i,j)});
            }
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=n;j>=1;j--){
            if(i-m+1>=1&&j+m-1<=n){
                _0_n[i][j]=max({_0_n[i][j+1],_0_n[i-1][j],calc(i-m+1,j,i,j+m-1)});
            }
        }
    }
    for(int i=n;i>=1;i--){
        for(int j=1;j<=n;j++){
            if(i+m-1<=n&&j-m+1>=1){
                _n_0[i][j]=max({_n_0[i+1][j],_n_0[i][j-1],calc(min(i+m-1,i),min(j-m+1,j),max(i+m-1,i),max(j-m+1,j))});
            }
        }
    }
    for(int i=n;i>=1;i--){
        for(int j=n;j>=1;j--){
            if(i+m-1<=n&&j+m-1<=n){
                _n_n[i][j]=max({_n_n[i+1][j],_n_n[i][j+1],calc(i,j,i+m-1,j+m-1)});
            }
        }
    }
    int res=0;
    //case1:
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            res=max(res,row[i]+_n_0[i+1][j]+_n_n[i+1][j+1]);
            // if(res==170){
            //     cerr<<i<<" "<<j<<" "<<1<<endl;
            //     cerr<<i<<" "<<i+1<<" "<<j<<" "<<i+1<<" "<<j+1<<endl;
            //     cerr<<row[i]<<" "<<_n_0[i+1][j]<<" "<<_n_n[i+1][j+1]<<endl;
            //     exit(0);
            // }
            //cerr<<res<<" "<<"row[i]+_n_0[i+1][j]+_n_n[i+1][j+1]"<<i<<" "<<j<<endl;
            res=max(res,rev_row[i+1]+_0_0[i][j]+_0_n[i][j+1]);
            //cerr<<res<<" "<<"rev_row[i+1]+_0_0[i][j]+_0_n[i][j+1]"<<i<<" "<<j<<endl;
            //  if(res==170){
            //     cerr<<i<<" "<<j<<" "<<2<<endl;
            //     exit(0);
            // }
            res=max(res,col[j]+_0_n[i][j+1]+_n_n[i+1][j+1]);
            //cerr<<res<<" "<<"col[j]+_0_n[i][j+1]+_n_n[i+1][j+1]"<<i<<" "<<j<<endl;
            // if(res==170){
            //     cerr<<i<<" "<<j<<" "<<3<<endl;
            //     exit(0);
            // }
            res=max(res,rev_col[j+1]+_0_0[i][j]+_n_0[i+1][j]);
            // if(res==170){
            //     cerr<<i<<" "<<j<<" "<<4<<endl;
            //     exit(0);
            // }
            //cerr<<res<<" "<<"rev_col[j+1]+_0_0[i][j]+_n_0[i+1][j] "<<i<<" "<<j<<endl;
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=i+1;j<=n;j++){
            //cerr<<res<<endl;
            res=max(res,row[i-1]+between_row[i][j]+rev_row[j+1]);
            // if(res==162){
            //     cerr<<i<<" "<<j<<" "<<"row";
            //     cerr<<row[i-1]<<" "<<between_row[i][j]<<" "<<rev_row[j+1]<<endl;
            //     exit(0);
            // }
            res=max(res,col[i-1]+between_col[i][j]+rev_col[j+1]);
        }
    }
    cout<<res<<endl;
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