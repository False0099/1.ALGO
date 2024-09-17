# [AGC 008 D] K-th K

## 题面翻译

给你一个长度为 $N$ 的整数序列 $X$，请判断是否存在一个满足下列条件的整数序列 $a$，如果存在，请构造一种方案。

条件如下：

1. $a$ 的长度为 $N^2$，并且满足数字 $1,2, \cdots, N$ 都各出现恰好 $N$ 次。

2. 对于 $1 \le i \le N$，数字 $i$ 在 $a$ 中第 $i$ 次出现的位置是 $X_i$。

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc008/tasks/agc008_d

長さ $ N $ の数列 $ x $ が与えられます。次の条件をすべて満たす数列 $ a $ が存在するか判定し、存在するならば $ a $ を $ 1 $ つ構成してください。

- $ a $ は長さ $ N^2 $ であり、整数 $ 1 $, $ 2 $, $ ... $, $ N $ をそれぞれちょうど $ N $ 個ずつ含む。
- 各 $ 1\ <\ =\ i\ <\ =\ N $ について、$ a $ に含まれる整数 $ i $ のうち左から $ i $ 番目に位置するものは、$ a $ 全体では左から $ x_i $ 番目に位置する。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ N $ $ x_1 $ $ x_2 $ $ ... $ $ x_N $

## 输出格式

条件をすべて満たす数列 $ a $ が存在しないならば、`No` を出力せよ。存在するならば、$ 1 $ 行目に `Yes` を出力し、$ 2 $ 行目に $ a $ を空白区切りで出力せよ。

## 样例 #1

### 样例输入 #1

```
3
1 5 9
```

### 样例输出 #1

```
Yes
1 1 1 2 2 2 3 3 3
```

## 样例 #2

### 样例输入 #2

```
2
4 1
```

### 样例输出 #2

```
No
```

## 提示

### 制約

- $ 1\ <\ =\ N\ <\ =\ 500 $
- $ 1\ <\ =\ x_i\ <\ =\ N^2 $
- $ x_i $ はすべて相異なる。

### Sample Explanation 1

たとえば、$ a $ に含まれる整数 $ 2 $ のうち左から $ 2 $ 番目に位置するものは、$ a $ 全体では左から $ 5 $ 番目に位置しています。整数 $ 1 $, $ 3 $ についても同様に条件が成り立っています。

## 题解
本题我们采用一个**贪心策略**，我们首先让我们每一个数先**占据这一个数必须有的位置**，然后我们直到这个是前面应该由多少个 $i$,那么我们就**尽可能靠前的安排这些数字**，然后对于我们的后面还有多少个数字也是确定的，我们也是尽可能的靠后的安排这些数字，这样，我们就可以通过我们的**贪心**来判断是否可行，如果可行，我们就输出答案，否则我们就认为不可行。
```cpp
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
    vector<PII> limits(n);
    for(int i=0;i<n;i++){
        cin>>limits[i].first;
        limits[i].second=i+1;
    } 
    sort(begin(limits),end(limits));
    vector<int> ans(n*n+10,0);
    map<int,int> cnt;
   // reverse(begin(limits),end(limits));
    for(auto [pos,num]:limits){
        ans[pos]=num;
        cnt[num]++;
    }
    for(auto [pos,num]:limits){
        int cnt_before=num;
        //ans[pos]=num;
        //cnt[num]++;
        //cerr<<cnt_before<<endl;
        for(int j=1;j<=pos-1;j++){
            if(cnt[num]==cnt_before){
                //cerr<<cnt_before<<" "<<cnt[num]<<endl;
                break;
            }
            if(ans[j]==0){
                ans[j]=num;
                cnt[num]++;
                //cerr<<num<<" "<<cnt[num]<<<<" "<<cnt_before<<" "<<endl;
//                cerr<<j<<endl;
            }
        }
        if(cnt[num]!=cnt_before){
            cout<<"No"<<endl;
//            break;
            return;
        }
    }
    reverse(begin(limits),end(limits));
    for(auto [pos,num]:limits){
//        int cnt_after=n-pos;
        for(int j=n*n;j>=pos+1;j--){
            if(cnt[num]==n){
                break;
            }
            if(ans[j]==0){
                ans[j]=num;
                cnt[num]++;
            }
        }
        if(cnt[num]!=n){
            cout<<"No"<<endl;
            return;
        }
    }
    cout<<"Yes"<<endl;
    for(int i=1;i<=n*n;i++){
        cout<<ans[i]<<" ";
    }
    cout<<endl;
}
signed main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int t;
    t=1;
 //   cin>>t;
    init();
    while(t--){
        solve();
    }
}
```