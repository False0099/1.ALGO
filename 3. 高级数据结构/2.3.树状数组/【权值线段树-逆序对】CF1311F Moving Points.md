# Moving Points

## 题面翻译

### 题目描述

在数轴 $OX$ 上有 $n$ 个点。第 $i$ 个点最初在坐标 $x_i$，并且有一个速度 $v_i$。没有两个点的坐标是相同的。所有的的都安装不变的速度移动，第 $i$ 个点在 $t$ 时刻的坐标为 $x_i + t \cdot v_i$ （$t$ 可能不是整数）。

对于两个点 $i$ 和 $j$，设 $d(i,j)$ 为 $i$ 和 $j$ 在任意时刻下的可能的最小距离（时刻可能不是整数）。如果 $i$ 和 $j$ 在某一时刻重合，那么 $d(i,j)=0$。

你的任务是计算出下面这个式子的值（对于任意两个点的最小距离之和）：
$$
\sum_{1\leq i < j \leq n}d(i,j)
$$

### 输入格式

第一行是一个整数 $n\ (2\leq n \leq 2\times 10^5)$，表示点的个数。

第二行包含 $n$ 个整数 $x_1,x_2,\dots,x_n\ (1\leq x_i \leq 10^8)$，$x_i$ 表示第 $i$ 个点的初始坐标。数据保证没有重复的 $x_i$。

第三行包含 $n$ 个整数 $v_1,v_2,\dots,v_n\ (-10^8 \leq v_i \leq 10^8)$，$v_i$ 表示第 $i$ 个点的初始速度。

### 输出格式

输出一个整数，表示任意两个点的最小距离之和，即
$$
\sum_{1\leq i < j \leq n}d(i,j)
$$

## 题目描述

There are $ n $ points on a coordinate axis $ OX $ . The $ i $ -th point is located at the integer point $ x_i $ and has a speed $ v_i $ . It is guaranteed that no two points occupy the same coordinate. All $ n $ points move with the constant speed, the coordinate of the $ i $ -th point at the moment $ t $ ( $ t $ can be non-integer) is calculated as $ x_i + t \cdot v_i $ .

Consider two points $ i $ and $ j $ . Let $ d (i, j) $ be the minimum possible distance between these two points over any possible moments of time (even non-integer). It means that if two points $ i $ and $ j $ coincide at some moment, the value $ d (i, j) $ will be $ 0 $ .

Your task is to calculate the value $ \sum\limits_{1 \le i < j \le n} $ $ d (i, j) $ (the sum of minimum distances over all pairs of points).

## 输入格式

The first line of the input contains one integer $ n $ ( $ 2 \le n \le 2 \cdot 10^5 $ ) — the number of points.

The second line of the input contains $ n $ integers $ x_1, x_2, \dots, x_n $ ( $ 1 \le x_i \le 10^8 $ ), where $ x_i $ is the initial coordinate of the $ i $ -th point. It is guaranteed that all $ x_i $ are distinct.

The third line of the input contains $ n $ integers $ v_1, v_2, \dots, v_n $ ( $ -10^8 \le v_i \le 10^8 $ ), where $ v_i $ is the speed of the $ i $ -th point.

## 输出格式

Print one integer — the value $ \sum\limits_{1 \le i < j \le n} $ $ d (i, j) $ (the sum of minimum distances over all pairs of points).

## 样例 #1

### 样例输入 #1

```
3
1 3 2
-100 2 3
```

### 样例输出 #1

```
3
```

## 样例 #2

### 样例输入 #2

```
5
2 1 4 3 5
2 2 2 3 4
```

### 样例输出 #2

```
19
```

## 样例 #3

### 样例输入 #3

```
2
2 1
-3 0
```

### 样例输出 #3

```
0
```

## 题解
本题考虑对于某一个点，我们因为我们的 $t$ 可以是实数，因此，我们的最近近距离只有两种可能：
1. 两者之间的距离为 0
2. 两者之间的距离为初始距离

对于我们的第二种情况，我们显然需要满足两个条件：$v_{i}<v_{j},x_{i}<x_{j}$。于是，我们就可以转换为求我们的二位偏序+权值树状数组即可。

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
struct akldsjf{
    vector<int> lsh;
    void push(int x){
        lsh.push_back(x);
    }
    void init(){
        sort(begin(lsh),end(lsh));
        lsh.erase(unique(begin(lsh),end(lsh)));
    }
    int get_rank(int x){
        return lower_bound(begin(lsh),end(lsh),x)-begin(lsh)+1;
    }
    int get_num(int x){
        return lsh[x-1];
    }
    void clear(){
        lsh.clear();
    }
}discret;
void solve(){
    int n;
    cin>>n;
    vector<PII> a(n+1);
    for(int i=1;i<=n;i++){
        cin>>a[i].first;
    } 
    for(int i=1;i<=n;i++){
        cin>>a[i].second;
        discret.push(a[i].second);
    }
    discret.init();  
    sort(begin(a),end(a));
    Fenwick<int> tr1(n+1);
    Fenwick<int> tr2(n+1);
    int ans=0;
    for(int i=1;i<=n;i++){
        int u=a[i].second;
        int sum_divide=tr1.ask(discret.get_rank(u));
        int sum_cnt=tr2.ask(discret.get_rank(u));
        if(sum_cnt==0){
            ans+=0;
        }else{
            ans+=sum_cnt*a[i].first-sum_divide;
        }
        //cerr<<ans<<endl;
        tr1.add(discret.get_rank(u),a[i].first);
        tr2.add(discret.get_rank(u),1);
    }
    cout<<ans<<endl;
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