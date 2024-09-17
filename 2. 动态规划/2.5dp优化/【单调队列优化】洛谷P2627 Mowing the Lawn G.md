# [USACO 11 OPEN] Mowing the Lawn G

## 题目描述

在一年前赢得了小镇的最佳草坪比赛后，Farmer John 变得很懒，再也没有修剪过草坪。现在，新一轮的最佳草坪比赛又开始了，Farmer John 希望能够再次夺冠。

然而，Farmer John 的草坪非常脏乱，因此，Farmer John 只能够让他的奶牛来完成这项工作。Farmer John 有 $N$（$1\le N\le 10^5$）只排成一排的奶牛，编号为 $1\ldots N$。每只奶牛的效率是不同的，奶牛 $i$ 的效率为 $E_i$（$0\le E_i\le 10^9$）。

靠近的奶牛们很熟悉，因此，如果 Farmer John 安排超过 $K$ 只连续的奶牛，那么，这些奶牛就会罢工去开派对 :)。因此，现在 Farmer John 需要你的帮助，计算 FJ 可以得到的最大效率，并且该方案中没有连续的超过 $K$ 只奶牛。

## 输入格式

第一行：空格隔开的两个整数 $N$ 和 $K$。

第二到 $N+1$ 行：第 $i+1$ 行有一个整数 $E_i$。

## 输出格式

第一行：一个值，表示 Farmer John 可以得到的最大的效率值。

## 样例 #1

### 样例输入 #1

```
5 2
1
2
3
4
5
```

### 样例输出 #1

```
12
```

## 题解
本题是洛谷 P 2034 的双倍经验，
```
#include <bits/stdc++.h>

#define int long long

int INF=0x3f3f3f3f3f;

using namespace std;

int n,k;

const int N=1e5+10;

int f[N];

int e[N];

int s[N];

typedef pair<int,int> PII;

void solve(){

    cin>>n>>k;

    for(int i=1;i<=n;i++){

        cin>>e[i];

    }

    for(int i=1;i<=n;i++){

        s[i]=s[i-1]+e[i];

    }

    deque<PII> dq;

    dq.push_back({0,0});//为什么要加着一个？

    for(int r=1;r<=n;r++){

        int b=f[r-1]-s[r];

        while(dq.size()&&dq.front().first<r-k){

            dq.pop_front();

        }        

        while(dq.size()&&dq.back().second<b){

            dq.pop_back();

        }

        dq.push_back({r,b});

        f[r]=max(f[r],dq.front().second+s[r]);

    }

    cout<<f[n]<<endl;

}

signed main(){

    //ios::sync_with_stdio(false),cin.tie(0);

    int t;

    //cin>>t;

    t=1;

    while(t--){

        solve();

    }

}
```