# Nested Segments

## 题面翻译

在一条直线上有 $n$ 条线段，每条线段用 $(l,r)$ 表示，求每条线段包含多少条其他的线段。

## 题目描述

You are given $ n $ segments on a line. There are no ends of some segments that coincide. For each segment find the number of segments it contains.

## 输入格式

The first line contains a single integer $ n $ ( $ 1<=n<=2·10^{5} $ ) — the number of segments on a line.

Each of the next $ n $ lines contains two integers $ l_{i} $ and $ r_{i} $ ( $ -10^{9}<=l_{i}&lt; r_{i}<=10^{9} $ ) — the coordinates of the left and the right ends of the $ i $ -th segment. It is guaranteed that there are no ends of some segments that coincide.

## 输出格式

Print $ n $ lines. The $ j $ -th of them should contain the only integer $ a_{j} $ — the number of segments contained in the $ j $ -th segment.

## 样例 #1

### 样例输入 #1

```
4
1 8
2 3
4 7
5 6
```

### 样例输出 #1

```
3
0
1
0
```

## 样例 #2

### 样例输入 #2

```
3
3 4
1 5
2 6
```

### 样例输出 #2

```
0
1
1
```

## 题解
对于本题，我们如果两条线段满足相互包容关系，那么我们应该满足：$l_{i}<l_{j}\&r_{j}<r_{i}$。因此，我们可以通过我们的求解二位偏序的方法来求解有哪些元素来满足我们的答案。

```
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
            w[x] += k;
        }
    }
    void add(int x, int y, T k) { // 区间修改
        add(x, k), add(y + 1, -k);
    }
    T ask(int x) {  //单点查询
        auto ans = T();
        for (; x; x -= x & -x) {
            ans += w[x];
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
struct alkdsfj{
    vector<int> lsh;
    void push(int x){
        lsh.push_back(x);
    }
    void init(){
        sort(begin(lsh),end(lsh));
        lsh.erase(unique(begin(lsh),end(lsh)),end(lsh));
    }
    int get_rank(int x){
        return lower_bound(begin(lsh),end(lsh),x)-begin(lsh)+1;
    }
    int get_num(int x){
        return lsh[x-1];
    }
}disc;
struct node{
    int x;
    int y;
    int id;
};
void solve(){
    int n;
    cin>>n;
    vector<node> a(n);
    for(int i=0;i<n;i++){
        cin>>a[i].x>>a[i].y;
        a[i].id=i;
        disc.push(a[i].y);
    }
    sort(begin(a),end(a),[&](node a,node b){
        return a.x<b.x;
    });
    disc.init();
    Fenwick<int> t(n+1); 
    vector<int> ans(n+1,0);
    for(int i=n-1;i>=0;i--){
        int y=a[i].y;
        ans[a[i].id]=t.ask(disc.get_rank(y));
        //cerr<<a[i].x<<" "<<a[i].y<<" "<<t.ask(disc.get_rank(y))<<endl;
        t.add(disc.get_rank(y),1);
    }
    for(int i=0;i<n;i++){
        cout<<ans[i]<<endl;
    }
    cout<<endl;

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