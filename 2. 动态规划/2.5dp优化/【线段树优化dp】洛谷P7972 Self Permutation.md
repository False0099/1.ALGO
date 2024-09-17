# [KSN 2021] Self Permutation

## 题目描述

给定一个长度为 $N$ 的排列 $a_i$，你可以执行若干次操作：

* 选择两个相邻的数，删除它们中较大的那个。

问最后可能得到序列的数量，答案对 $10^9+7$ 取模。

注意如果两个数中间所有的数被删除了，它们会变成相邻的。

## 输入格式

第一行输入一个正整数 $N$。

第二行输入 $N$ 个正整数 $a_i$。

## 输出格式

输出一个整数代表答案。

## 样例 #1

### 样例输入 #1

```
3
2 3 1
```

### 样例输出 #1

```
3
```

## 样例 #2

### 样例输入 #2

```
4
2 1 4 3
```

### 样例输出 #2

```
6
```

## 提示

**【样例解释】**

对于第一组样例，以下为所有可能得到的序列：

- $[2,3,1]$
- $[\bold2,\bold3,1]\to[2,1]$
- $[\bold2,\bold3,1]→[\bold2,\bold1]→[1]$

对于第二组样例，以下为所有可能得到的序列：

- $[2,1,4,3]$
- $[\bold2,\bold1, 4, 3]\to[1, 4, 3]$
- $[\bold2,\bold1, 4, 3]\to[1,\bold4,\bold3]\to[1, 3]$
- $[\bold2,\bold1, 4, 3]\to[1,\bold4,\bold3]\to[\bold1,\bold3]\to[1]$
- $[2, 1,\bold4,\bold3]\to[2, 1, 3]$
- $[2, 1,\bold4,\bold3]\to[2,\bold1,\bold3]\to[2, 1]$

**【数据范围】**

**本题采用捆绑测试。**

- Subtask 1（8 points）：只存在一组数据，满足 $N=6$，$A=[2,5,1,3,4,6]$。
- Subtask 2（20 points）：$N\leq 200$。
- Subtask 3（13 points）：$N\leq 2000$，$A_i=i$。
- Subtask 4（9 points）：$A_i=i$。
- Subtask 5（23 points）：$N\leq 2000$。
- Subtask 6（27 points）：无特殊限制。

对于所有数据，$N\leq 3\times 10^5$，保证输入的 $a_i$ 能构成一个排列。

## 题解
本题是一个典型的**子序列相关问题**，我们的一般的 dp 设置思路都是**以 i 记为的子数列如何如何**。我们这一题也不例外，我们设我们的 $dp[i]$ 表示我们以 $i$ 结尾的子数列我们的总方案数有是多少。

考虑到我们**转移情况**，注意到，我们如果可以转移，当且仅当我们有 $min(a[j],a[i])<min(a[j+1],\dots a[i-1])$。对于这一种**涉及到区间的式子**，我们不妨**预处理出**我们的内容，比如我们可以预处理出我们以我们的 $a[j]$ 我们**向左向右能够延伸出的最大距离是多少**。这一点类似于我们的之前的 gcd 问题，可以通过我们的单调栈来进行处理。

那么，之后, 我们显然有我们的 $dp[i]$ 可以由 $dp[j]$ 转移过来，当且仅当我们的**这两个点对应的线段之间有交点**。而我们的两个线段之间有交点，可以被认为是同时满足下面两个条件：
$l[i]<r[j]\&\&r[i]>l[j]$。而又因为我们的 $l[i]$ 一定能够满足，因此我们只需要关注我们的后面的条件。而我们也因此，可以**根据我们的约束条件来进行我们的优化**。显然，我们对于上面的可以进行一个整体的优化。

最后我们就可以把我们的转移谢晨一个**树状数组的求和问题**，并且还有我们的**单点修改**。

```cpp
#include <bits/stdc++.h>

#define int long long

#define endl '\n'

int INF=0x3f3f3f3f3f;

const int mod=1e9+7;

using namespace std;

typedef pair<int,int> PII;

void init(){

}

const int N=3e5+10;

int f[N];

int l[N];

int r[N];

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

            ans = (ans+w[x])%mod;

        }

        return ans;

    }

    T ask(int x, int y) { // 区间查询(区间和)

        return (ask(y)%mod - ask(x - 1)%mod+mod)%mod;

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

void solve(){

   int n;

   cin>>n;

   vector<int>a(n+1);

    for(int i=1;i<=n;i++){

        cin>>a[i];

    }

    stack<int> stk;

    for(int i=1;i<=n;i++){

        while (stk.size()&&a[stk.top()]>=a[i])

        {

            stk.pop();

        }

        if(stk.size()){

            l[i]=stk.top()+1;

        }else{

            l[i]=1;

        }

        stk.push(i);

    }

    // for(int i=1;i<=n;i++){

    //     cerr<<l[i]<<" ";

    // }

    // cerr<<endl;

    while(stk.size()){

        stk.pop();

    }

    for(int i=n;i>=1;i--){

        while(stk.size()&&a[stk.top()]>=a[i]){

            stk.pop();

        }

        if(stk.size()){

            r[i]=stk.top()-1;

        }else{

            r[i]=n;

        }

        stk.push(i);

    }

    // for(int i=1;i<=n;i++){

    //     cerr<<r[i]<<" ";

    // }

    // cerr<<endl;

    Fenwick <int> tr(n+10);

    tr.add(1,1);

    for(int i=1;i<=n;i++){

        int l_=l[i];

        int _r=r[i];

        f[i]=(f[i]+tr.ask(l_,n+1)%mod)%mod;

        tr.add(_r,f[i]);

    }

    int mn=INF;

    int cnt=0;

    // for(int i=1;i<=n;i++){

    //     cerr<<f[i]<<" ";

    // }

    // cerr<<endl;

    for(int i=n;i>=1;i--){

        mn=min(mn,a[i]);

        //cerr<<(mn == a[i] ? 1 : 0) * f[i]<<endl;

        cnt=(cnt+(mn == a[i] ? 1 : 0) * f[i])%mod;

    }

    cout<<cnt<<endl;

}

signed main(){

    ios::sync_with_stdio(false),cin.tie(0);

    int t;

    t=1;

 //   cin>>t;

    init();

    while(t--){

        solve();

    }

}
```

