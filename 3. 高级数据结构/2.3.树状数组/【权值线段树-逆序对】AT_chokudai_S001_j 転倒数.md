    # 転倒数

## 题面翻译

输入序列a，进行冒泡排序。 输出总共进行多少次交换。

感谢@MoMaek 提供的翻译

## 题目描述

[problemUrl]: https://atcoder.jp/contests/chokudai_S001/tasks/chokudai_S001_j

数列 $ a $ をバブルソートした時、スワップが何回発生するかを出力しなさい。

## 输入格式

## 输出格式

## 样例 #1

### 样例输入 #1

```
5
3 1 5 4 2
```

### 样例输出 #1

```
5
```

## 样例 #2

### 样例输入 #2

```
6
1 2 3 4 5 6
```

### 样例输出 #2

```
0
```

## 样例 #3

### 样例输入 #3

```
7
7 6 5 4 3 2 1
```

### 样例输出 #3

```
21
```

## 样例 #4

### 样例输入 #4

```
20
19 11 10 7 8 9 17 18 20 4 3 15 16 1 5 14 6 2 13 12
```

### 样例输出 #4

```
114
```

## 提示

### 制約

- $ 1\ \leq\ N\ \leq\ 100,000 $

## 思路
就是求逆序对个数

## AC代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define INF 0x3f3f3f3f3f3f3f3f
#define L(i, j, k) for(int i = (j); i < (k); ++i)
#define R(i, j, k) for(int i = (j); i >= (k); --i)
#define _L(i, j, k) for(int i = (j); i <= (k); ++i)
#define all(x) (x).begin(),(x).end()
#define allp(x,n) (x).begin()+(n),(x).end()
#define ms(x,y) memset(x,y,sizeof(x))
#define dbg(x) cerr<<__LINE__<<" | "<<#x<<" = "<<x<<"\n"
#define dbgl(i,x) cerr<<__LINE__<<" ["<<#i<<"]: "<<i<<" -> { "<<#x<<" = "<<x<<" }\n"
#define in(a,l,r)   for(int i=l;i<r;cin>>a[i],i++)
#define bp cerr<<"breakpoint"<<"\n"
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
template <typename T>
struct Fenwick {
    int n;
    vector<T> w;

    Fenwick() {}
    void add(int x, T k) {
        for (; x <= n; x += x & -x) {
            w[x] += k;
        }
    }
    T ask(int x) {
        T ans = 0;
        for (; x; x -= x & -x) {
            ans += w[x];
        }
        return ans;
    }
    T ask(int x, int y) {
        return ask(y) - ask(x - 1);
    }
    T get(auto val) { // 获取逆序对数量
        this->n = val.size() - 1; // 注意 n 不能 +1
        w.resize(n + 1);

        vector<pair<int, int>> alls;
        for (int i = 1; i <= n; i++) {
            alls.emplace_back(val[i], i);
        }
        sort(alls.begin(), alls.end()); 

        T ans = 0;
        for (auto [val, idx] : alls) {
            ans += ask(idx + 1, n);
            add(idx, 1);
        }
        return ans;
    }
};
inline void solve(){
    int n;
    cin>>n;
    Fenwick<int> fen;
    vector<int> a(n+1,0);
    L(i,1,n+1){
        cin>>a[i];
    }
    cout<<fen.get(a)<<"\n";
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