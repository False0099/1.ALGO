# Bomb

## 题面翻译

### 题目描述

你有两个长度为 $n$ 的数组 $a$ 和 $b$。最初，你的分数是 $0$。每一次操作中，你可以选择一个 $a_i$ 加到你的分数上。然后 $a_i$ 将会更新为 $\max(0,a_i-b_i)$。

现在你只能执行 $k$ 次操作。那么你能得到的最大分数是多少？

### 输入格式

#### 本题每个测试点包含多组数据

每个测试数据的第一行输入 $t(1 \le t \le 1000)$ 表示数据组数。

每组数据的第一行包含两个整数 $n(1 \le n \le 2 \cdot 10^5)$ 和 $k(1 \le k \le 10^9)$。分别表示两个数组的长度以及操作次数。

接下来的 $2$ 行，分别输入数组 $a$ 和 $b(1 \le a_i,b_i \le 10^9)$。

保证每个测试数据中 $n$ 的总和不超过 $2 \cdot 10^5$。

### 输出格式

共 $t$ 行，第 $i$ 行表示第 $i$ 组数据执行 $k$ 次操作后分数的最大值。

## 题目描述

Sparkle gives you two arrays $ a $ and $ b $ of length $ n $ . Initially, your score is $ 0 $ . In one operation, you can choose an integer $ i $ and add $ a_i $ to your score. Then, you must set $ a_i $ = $ \max (0, a_i - b_i) $ .

You only have time to perform $ k $ operations before Sparkle sets off a nuclear bomb! What is the maximum score you can acquire after $ k $ operations?

## 输入格式

The first line contains $ t $ ( $ 1 \leq t \leq 1000 $ ) — the number of test cases.

The first line of each test case contains $ n $ and $ k $ ( $ 1 \leq n \leq 2 \cdot 10^5, 1 \leq k \leq 10^9 $ ) — the length of the arrays and the number of operations you can perform.

The following line contains $ n $ integers $ a_1, a_2, ... A_n $ ( $ 1 \leq a_i \leq 10^9 $ ).

The following line contains $ n $ integers $ b_1, b_2, ... B_n $ ( $ 1 \leq b_i \leq 10^9 $ ).

It is guaranteed that the sum of $ n $ for all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output an integer, the maximum score you can acquire after $ k $ operations.

## 样例 #1

### 样例输入 #1

```
5
3 4
5 6 7
2 3 4
5 9
32 52 68 64 14
18 14 53 24 8
5 1000
1 2 3 4 5
5 4 3 2 1
1 1000000
1000000
1
10 6
3 3 5 10 6 8 6 8 7 7
6 1 7 4 1 1 8 9 3 1
```

### 样例输出 #1

```
21
349
27
500000500000
47
```

## 题解
本题我们的一个显然的方法是贪心，我们每一次都选择答案最大的哪一个，但是这里我们采用这一个显然是不太行的，我们于是考虑**枚举我们的第 K 大值是多少**，我们这个时候，我们发现，我们如果知道了第 K 大值是多少，我们的**正确答案就能通过我们的计算 $o(1)$ 的计算出来**。

这个时候，我们就有下面的答案：
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
    int n,k;
    cin>>n>>k;
    vector<int> a(n);
    for(int i=0;i<n;i++){
        cin>>a[i];
    }   
    vector<int> b(n);
    for(int i=0;i<n;i++){
        cin>>b[i];
    }
    int l=0,r=INF;
    auto check=[&](int mid){
        int cnt=0;
        for(int i=0;i<n;i++){
            if(a[i]>mid){
                cnt+=(a[i]-mid-1)/b[i]+1;
            }
        }
        return cnt<=k;
    };
    while (l<r)
    {
        int mid=l+r>>1;
        if(check(mid)){
            r=mid;
        }else{
            l=mid+1;
        }
        /* code */
    }
    auto calc=[&](int x){
        int res=0;
        int tot=0;
        for(int i=0;i<n;i++){
            if(a[i]<x){
                continue;
            }
            int cnt=(a[i]-x)/b[i]+1;
            res+=cnt*(a[i])-(cnt*(cnt-1)/2)*b[i];
            tot+=cnt;
        }
        if(tot>k){
            res-=(tot-k)*x;
        }
        return res;
    };
    cout<<calc(l)<<endl;
    
}
signed main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int t;
    t=1;
    cin>>t;
    init();
    while(t--){
        solve();
    }
}
```