# LIS

## 题面翻译

- 给定一个长为 $n$ 的序列 $a_i$，求这个序列的最长单调上升子序列长度。
- $1 \le n \le 10^5 $。

## 题目描述

[problemUrl]: https://atcoder.jp/contests/chokudai_S001/tasks/chokudai_S001_h

数列 $ a $ から好きな整数を好きなだけ取り除き、単調増加な数列を作るとき、その数列の長さの最大値を求めなさい。

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
2
```

## 样例 #2

### 样例输入 #2

```
6
1 2 3 4 5 6
```

### 样例输出 #2

```
6
```

## 样例 #3

### 样例输入 #3

```
7
7 6 5 4 3 2 1
```

### 样例输出 #3

```
1
```

## 样例 #4

### 样例输入 #4

```
20
19 11 10 7 8 9 17 18 20 4 3 15 16 1 5 14 6 2 13 12
```

### 样例输出 #4

```
6
```

## 提示

### 制約

- $ 1\ \leq\ N\ \leq\ 100,000 $

## 题解：
典中典，我们直接树状数组优化求 LIS，值域就行了。

```cpp
// LUOGU_RID: 176400204
#include <bits/stdc++.h>
#define int long long
#define endl '\n'
int INF=0x3f3f3f3f3f3f3f3f;
using namespace std;
typedef pair<int,int> PII;
void init(){
    
}
template <typename T>
struct Fenwick {
    int n;
    vector<T> w;

    Fenwick(int n) {
        this->n = n;
        w.resize(n + 1);
    }
    void add(int x, T k) {
        for (; x <= n; x += x & -x) {
            w[x] = max(w[x],k);
        }
    }
    void add(int x, int y, T k) { // 区间修改
        add(x, k), add(y + 1, -k);
    }
    T ask_max(int x){
        auto ans=T();
        for (;x;x-=x&-x){
            ans=max(ans,w[x]);
        }
        return ans;
    }
    T ask(int x, int y) { // 区间查询(区间和)
        return ask(y) - ask(x - 1);
    }
    int kth(T k) { //查找第k大的值
        int ans = 0;
        for (int i = __lg(n); i >= 0; i--) {
            int val = ans + (1 << i);
            if (val < n && w[val] < k) {
                k -= w[val];
                ans = val;
            }
        }
        return ans + 1;
    }
};
struct skaljf
{
    vector<int> lsh;
    void push(int x){
        lsh.push_back(x);
    }
    void init(){
        sort(begin(lsh),end(lsh));
        lsh.erase(unique(begin(lsh),end(lsh)),end(lsh));
    }
    int get_rank(int x){
        return lower_bound(begin(lsh),end(lsh),x)-begin(lsh)+5;
    }
    int get_num(int k){
        return lsh[k];
    }
}discret;
const int N=2e5+10;
int f[N];
int g[N];
void solve(){
    int n;
    cin>>n;
    vector<int> a(n+1);
    Fenwick<int> w=Fenwick<int>(n+10);
    for(int i=1;i<=n;i++){
        cin>>a[i];
        discret.push(a[i]);
    }
    discret.init();
    for(int i=1;i<=n;i++){
        int u=discret.get_rank(a[i]);
        int maxx=w.ask_max(u-1);
        f[i]=maxx+1;
        w.add(u,f[i]);
    }
    discret.lsh.clear();

    for(int i=1;i<=n;i++){
        a[i]*=-1;
        discret.push(a[i]);
    }
    discret.init();
    Fenwick<int> w1=Fenwick<int> (n+10);
    for(int i=n;i>=1;i--){
        int u=discret.get_rank(a[i]);
        int maxx=w1.ask_max(u-1);
        //cerr<<i<<" "<<maxx<<endl;
        g[i]=maxx+1;
        w1.add(u,g[i]);
    }
    //cerr<<endl;
    vector<int> ans;
    vector<int> res(n+1);
    for(int i=1;i<=n;i++){
        res[i]=f[i]+g[i];
    }
    int maxx=*(max_element(begin(res)+1,end(res)));
    cout<<maxx-1<<endl;
    exit(0);
    for(int i=1;i<=n;i++){
    //    cerr<<f[i]<<" "<<g[i]<<endl;
        if(f[i]+g[i]==maxx){
            ans.push_back(i);
        }
    }
    cout<<ans.size()<<endl;
    for(auto u:ans){
        cout<<u<<" ";
    }
    cout<<endl;
}
signed main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int t;
    t=1;
   // cin>>t;
    init();
    while(t--){
        solve();
    }
}
```