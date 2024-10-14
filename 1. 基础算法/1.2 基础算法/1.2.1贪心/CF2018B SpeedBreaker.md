# Speedbreaker

## 题目描述

[Djjaner - Speedbreaker](https://soundcloud.com/luciano-ferrari-151560131/speedbreaker)


There are $ n $ cities in a row, numbered $ 1, 2, \ldots, n $ left to right.

- At time $ 1 $ , you conquer exactly one city, called the starting city.
- At time $ 2, 3, \ldots, n $ , you can choose a city adjacent to the ones conquered so far and conquer it.

You win if, for each $ i $ , you conquer city $ i $ at a time no later than $ a_i $ . A winning strategy may or may not exist, also depending on the starting city. How many starting cities allow you to win?

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10^4 $ ). The description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 1 \le n \le 2 \cdot 10^5 $ ) — the number of cities.

The second line of each test case contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le n $ ) — the deadlines for conquering the cities.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output a single integer: the number of starting cities that allow you to win.

## 样例 #1

### 样例输入 #1

```
3
6
6 3 3 3 5 5
6
5 6 4 1 4 5
9
8 6 4 2 1 3 5 7 9
```

### 样例输出 #1

```
3
0
1
```

## 提示

In the first test case, cities $ 2 $ , $ 3 $ , and $ 4 $ are good starting cities.

In the second test case, there are no good starting cities.

In the third test case, the only good starting city is city $ 5 $ .

## 题解
本题一个想法是，我们如果我们的一个数字的出现的最左端和我们的最右端之间的距离是大于这一个数本身的，那么我们就认为最后的答案为 0.

否则，我们可以知道，我们一个最后可选范围一定是我们的若干个区间相交形成了，我们对于一个 $i$,我们的对应的区间应该是我们的 $[i-a[i]+1,i+a[i]-1]$。于是，我们就可以转换为求区间交长度是多少来得到我们的最终的答案。
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
    vector<int> l(n+1);
    vector<int> r(n+1);
    vector<set<int>> pos(n+1);
    for(int i=1;i<=n;i++){
        int x;
        cin>>x;
        a[i]=x;
        pos[x].insert(i);
    }   
    int L=n;
    int R=1;
    for(int i=1;i<=n;i++){
        if(pos[i].size()){
            int ll=*(pos[i].begin());
            int rr=*(pos[i].rbegin());
            L=min(L,ll);
            R=max(R,rr);
            //xcerr<<i<<" "<<ll<<" "<<rr<<endl;
            if(R-L+1>i){
                cout<<0<<endl;
                return;
            }
        }
    }
    L=1,R=n;
    for(int i=1;i<=n;i++){
        L=max(L,i-a[i]+1);
        R=min(R,i+a[i]-1);
    }
    //cerr<<endl;
    //cerr<<L<<" "<<R<<endl;
    if(R-L+1<=0){
        cout<<0<<endl;
    }else{
        cout<<R-L+1<<endl;
    }
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