# [ARC 066 E] Addition and Subtraction Hard

## 题面翻译

给你一个只包含'+'、'-'、正整数的式子，你需要在式子中添加一些括号，使运算结果最大，输出最大的结果。

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc066/tasks/arc066_c

joisinoお姉ちゃんは、$ N $ 項から成る式、$ A_1 $ $ op_1 $ $ A_2 $ $ ... $ $ op_{N-1} $ $ A_N $ を持っています。 ここで、$ A_i $ は整数で、$ op_i $ は、`+` または `-` の記号です。 Joisinoお姉ちゃんは大きい数が好きなので、括弧を好きな数だけ( $ 0 $ 個でもよい)挿入することで、計算の順番を変え、式の値を最大化したいです。開き括弧は数の直前、閉じ括弧は数の直後にのみ、挿入することが許されます。同じ場所に挿入する括弧の個数に制限はありません。 あなたの仕事は、式に括弧をいくつか挿入した際に、式の値としてありうるものの最大値を求めるプログラムを作ることです。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ N $ $ A_1 $ $ op_1 $ $ A_2 $ $ ... $ $ op_{N-1} $ $ A_N $

## 输出格式

括弧をいくつか挿入してできる式の値としてありうるものの最大値を出力せよ。

## 样例 #1

### 样例输入 #1

```
3
5 - 1 - 3
```

### 样例输出 #1

```
7
```

## 样例 #2

### 样例输入 #2

```
5
1 - 2 + 3 - 4 + 5
```

### 样例输出 #2

```
5
```

## 样例 #3

### 样例输入 #3

```
5
1 - 20 - 13 + 14 - 5
```

### 样例输出 #3

```
13
```

## 提示

### 制約

- $ 1≦N≦10^5 $
- $ 1≦A_i≦10^9 $
- $ op_i $ は、`+` または `-` の記号である。

### Sample Explanation 1

$ 5\ -\ (1\ -\ 3)\ =\ 7 $ となり、これが最大なので、$ 7 $ を出力します。

### Sample Explanation 2

$ 1\ -\ (2\ +\ 3\ -\ 4)\ +\ 5\ =\ 5 $ となり、これが最大なので、$ 5 $ を出力します。

### Sample Explanation 3

$ 1\ -\ (20\ -\ (13\ +\ 14)\ -\ 5)\ =\ 13 $ となり、これが最大なので、$ 13 $ を出力します。


## 题解：
本题的关键是找到下面的性质：在 + 号后面套括号显然是没有意义的，所以括号只在 - 号后面。
考虑在一个 - 号后面套括号以后，里面原来贡献为负的贡献变为正了，原来贡献为正的贡献变为负了 (第一个数的贡献
仍为负)。
那么，我们考虑括号后面第一个由 + 号连接的连通块。这个连通块的贡献无论如何都是负。然后后面所有的数的贡献，我们都可以让它为正：如果是负号，则其本身就会被纠正为正的；如果是 + 号连通块，则连通块前面必然有一个 - 号，那么给这个连通块加上括号之后，这个连通块的贡献就会再次反转，变为正。
所以我们只需要枚举外层括号的左端点的位置，然后用前后缀和计算即可。

```
#include <bits/stdc++.h>

#define int long long

#define endl '\n'

int INF=0x3f3f3f3f3f3f3f3f;

using namespace std;

typedef pair<int,int> PII;

void init(){

}

void solve(){

    int n;

    cin>>n;

    vector<int> a(n+1);

    vector<int> b(n+1);

    b[1]=0;

    int k=0;

    vector<int> s(n+1,0);

    vector<int> ss(n+1,0);

    for(int i=1;i<=n;i++){

        if(i!=1){

            char c=getchar();

            while(c!='+'&&c!='-'){

                c=getchar();

            }

            if(c=='-'){

                b[i]=1;

                k++;

            }

        }

        int num;

        cin>>num;

        if(b[i]==1){

            num=-num;

        }

        s[i]=s[i-1]+num;

        ss[i]=ss[i-1]+abs(num);

    }

    //cerr<<"ok"<<endl;

    int lst=n+1;

    for(int i=1;i<=n;i++){

        if(b[i]==1){

            lst=i;

            break;

        }

    }

    if(lst==n+1||k==1){

        cout<<s[n]<<endl;

        return;

    }

    int ans=s[n];

    for(int i=lst+1;i<=n;i++){

        if(b[i]==1){

            ans=max(ans,s[lst-1]-(ss[i-1]-ss[lst-1])+ss[n]-ss[i-1]);

            lst=i;

        }

    }

    cout<<ans<<endl;

    return;

}

signed main(){

//    ios::sync_with_stdio(false),cin.tie(0);

    int t;

    t=1;

 //   cin>>t;

    init();

    while(t--){

        solve();

    }

}
```