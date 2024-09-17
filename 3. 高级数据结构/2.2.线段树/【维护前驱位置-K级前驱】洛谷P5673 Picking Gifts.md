# 「SWTR-2」Picking Gifts

## 题目背景

$\mathrm{Sunny}$ 有个 $npy$ 叫做小 $\mathrm{b}$。

小 $\mathrm{b}$ 的生日就要到了，$\mathrm{Sunny}$ 想给她买一些礼物。

## 题目描述

商店里摆着琳琅满目的商品，每个商品都有：

- 编号，**从左到右**依次为 $1,2,\dots n$。

- 种类，分别为 $p_1,p_2,\dots p_n$。

- 价值，分别为 $v_1,v_2,\dots v_n$。

$\mathrm{Sunny}$ 想从中挑选一个区间，将这个区间里的所有礼物买下来送给小 $\mathrm{b}$。

小 $\mathrm{b}$ 会**从右往左**依次查看 $\mathrm{Sunny}$ 送给他的礼物，如果她看到同一种类的礼物出现了 $k$ 次，那么她就不会再去查看这种礼物（包括第 $k$ 个），当然，这些礼物也就失去了原本的价值。

现在，$\mathrm{Sunny}$ 给你了 $m$ 个区间，想让你求出在小 $\mathrm{b}$ 眼中，这个区间的价值。

具体的价值计算见样例。

## 输入格式

第一行由空格隔开的三个正整数 $n,m,k$。

第二行 $n$ 个由空格隔开的正整数，第 $i$ 个数代表 $p_i$。

第三行 $n$ 个由空格隔开的正整数，第 $i$ 个数代表 $v_i$。

接下来 $m$ 行，第 $i$ 行两个正整数 $l_i,r_i$，表示第 $i$ 次询问的区间。

## 输出格式

输出 $m$ 行，对于每一个询问，输出一行一个整数 $v$，为这个区间在小 $\mathrm{b}$ 眼中的价值。

## 样例 #1

### 样例输入 #1

```
6 11 3
1 1 1 2 1 3
7 3 8 9 6 5
1 1
1 2
1 3
1 4
1 5
1 6
2 6
3 6
4 6
5 6
6 6
```

### 样例输出 #1

```
7
10
11
20
23
28
28
28
20
11
5
```

## 提示

---

### 样例说明

$[1,1]:7$。

$[1,2]:3+7=10$。

$[1,3]:8+3=11$，因为编号为 $1$ 的礼物种类为 $1$，这是种类 $1$ 出现的第 $k(k=3)$ 次，所以她不会再看这种礼物（包括这个）。

$[1,4]:9+8+3=20$。

$[2,6]:5+6+9+8=28$。

$[3,6]:5+6+9+8=28$。

---

### 数据范围与约定

测试点 $1-4:n\leq 100,m\leq 100$。

测试点 $5-6:n\leq 5000,m\leq 5000$。

测试点 $7-10:n\leq 2\times 10^4,m\leq 10^4$。

测试点 $11-15:n\leq 2\times 10^5,m\leq 2\times 10^5$。

测试点 $16-20:n\leq 10^6,m\leq 5\times 10^5$。

对于测试点 $1,2,7,8,11,12,16,17$，有 $k=n$，其余测试点有 $2\leq k<n$。

对于所有测试点，有 $1\leq p_i\leq n,1\leq v_i\leq 2000,1\leq l \leq r \leq n$。

---

对于测试点 $1-10$，每个 $3$ 分。

对于测试点 $11-20$ 中 $k=n$ 的，每个 $4$ 分。

其余测试点每个 $9$ 分。

---

对于测试点 $1-6$，时间限制 $500ms$。

对于测试点 $7-15$，时间限制 $750ms$。

对于测试点 $16-20$，时间限制 $1.5s$。

对于所有测试点，空间限制 $128MB$。

---

当然了，SWTR-02 的出题人们是不可能有 girlfriends 的。

## 题解
本题，我们属于对于我们的之前的 HH 的相连的一个重要扩展，对于这一类问题，我们的线段树方法思路上都是**先离线我们的问题，按照我们的右端点排序**，对于我们的每一个右端点，维护一个**全局的线段树**，我们每一个右端点的问题都可以通过这一个全局的线段树进行处理。

例如，在本题中，我们的还需要**维护一个大小为 k 的队列，存储我们的每一种元素的对应的下表**，来保证**我们的超过 K 的元素都是没有贡献的**。因此，我们就可以采用我们的下面的代码来得到我们的最终的答案。

```cpp
#include <bits/stdc++.h>

#define int long long

#define endl '\n'

int INF=0x3f3f3f3f3f3f3f3f;

using namespace std;

typedef pair<int,int> PII;

const int N=1e6+10;

const int M=5e5+10;

int p[N];

int v[N];

struct node

{

    int l;

    int r;

    int id;

    int ans;

}q[M];

int cnt[N];

int last[N];

map<int,deque<int>> col;

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

    T ask(int x) {  //单点查询

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

void init(){

}

void solve(){

    int n,m,k;

    cin>>n>>m>>k;

    for(int i=1;i<=n;i++){

        cin>>p[i];

    }  

    for(int i=1;i<=n;i++){

        cin>>v[i];

    }

    for(int i=1;i<=m;i++){

        cin>>q[i].l>>q[i].r;

        q[i].id=i;

    }

    sort(q+1,q+1+m,[&](node a,node b){

        return a.r<b.r;

    });

    int r=1;

    Fenwick <int> tr(n+1);

    for(int i=1;i<=m;i++){

        while(r<=q[i].r){  

            col[p[r]].push_back(r);

            tr.add(r,v[r]);

            if(col[p[r]].size()>=k){

                int pos=col[p[r]].front();

                col[p[r]].pop_front();

                tr.add(pos,-v[pos]);

            }

            r++;

        }

        int l_=q[i].l;

        int r_=q[i].r;

        q[i].ans=tr.ask(l_,r_);

    }

    sort(q+1,q+1+m,[&](node a,node b){

        return a.id<b.id;

    });

    for(int i=1;i<=m;i++){

        cout<<q[i].ans<<endl;

    }

    cout<<endl;

  

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