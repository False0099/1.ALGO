# Balancing Weapons

## 题面翻译

有 $n$ 把枪，第 $i$ 把枪的攻击力是 $p_i = f_i \cdot d_i$。你需要调整 $d_i$ 使得 $ \max\limits_{1 \le i \le n}{p_i} - \min\limits_{1 \le i \le n}{p_i} \le k $，要保证 $d_i > 0$，求最少调整几把枪的 $d_i$ 可以满足条件。

## 题目描述

You've got a job in a game studio that developed an online shooter, and your first big task is to help to balance weapons. The game has $ n $ weapons: the $ i $ -th gun has an integer fire rate $ f_i $ and an integer damage per bullet $ d_i $ . The $ i $ -th gun's total firepower is equal to $ p_i = f_i \cdot d_i $ .

You have to modify the values $ d_i $ of some guns in such a way that the new values $ d_i $ will still be integers, and the firepower of all guns will become balanced. Given an integer $ k $ , the guns are said to be balanced if $ \max\limits_{1 \le i \le n}{p_i} - \min\limits_{1 \le i \le n}{p_i} \le k $ .

Since gamers that play your game don't like big changes, you need to change the values $ d_i $ for the minimum possible number of guns. What is the minimum number of guns for which you have to change these values to make the guns balanced?

Note that the new values $ d_i $ must be integers greater than $ 0 $ .

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 1000 $ ) — the number of test cases.

The first line of each test case contains two integers $ n $ and $ k $ ( $ 2 \le n \le 3000 $ ; $ 0 \le k \le 1500 $ ) — the number of guns to balance, and the maximum allowed gap between the most and the least powerful weapons.

The second line contains $ n $ integers $ f_1, f_2, \dots, f_n $ ( $ 1 \le f_i \le 2000 $ ), where $ f_i $ is the fire rate of the $ i $ -th gun.

The third line contains $ n $ integers $ d_1, d_2, \dots, d_n $ ( $ 1 \le d_i \le 10^9 $ ), where $ d_i $ is the damage per bullet of the $ i $ -th gun.

It's guaranteed that the sum of $ n $ over all test cases doesn't exceed $ 3000 $ .

## 输出格式

For each test case, print the minimum number of guns which damage $ d_i $ you have to change in order to make the guns balanced.

Note that the new values $ d_i $ must be integers greater than $ 0 $ .

## 样例 #1

### 样例输入 #1

```
5
4 2
6 3 13 7
1 2 1 2
3 2
100 101 102
100 99 98
5 0
1 12 4 4 3
12 1 3 3 4
2 50
1000 10
1000000000 1
3 5
1 19 11
49 4 72
```

### 样例输出 #1

```
2
3
0
1
2
```

## 提示

In the first test case, you can set $ d_1 = 2 $ and $ d_2 = 4 $ . You'll get an array $ d = [2, 4, 1, 2] $ , and the values of firepower will be $ p = [12, 12, 13, 14] $ . The guns are balanced, since $ 14 - 12 \le 2 $ .

In the second test case, you have to change the value $ d_i $ for all three guns. For example, you can set $ d = [5151, 5100, 5050] $ .

In the third test case, all guns are already balanced, so you don't have to change anything.

## 题解
首先，本题支持我们在我们的 $o(n^2)$ 附近的算法，我们就可以考虑**通过枚举来降低我们的复杂度**。
通过观察，我们可以发现，我们的最终的答案，一定是形如 $a[i]$ 不变，然后其他的元素**尽可能的靠近 $a[i]$,**。于是，我们可以**枚举我们的 $a[i]$**，

枚举我们的 $a[i]$ 之后，我们剩余的元素就有三种选择：
1. 保持不变
2. 变成第一个比 $a[i]$ 小的数字
3. 变成第一个比 $a[i]$ 大的数字

我们总共也就一共有 $3*n$ 个元素，之后，我们对这 $3n$ 个元素**按照我们的 val**进行排序，然后**通过双指针找到相差不超过 K**的区间都有哪些，然后分别统计这些区间内有哪些是本来就不需要进行处理的元素。

之后，我们再去进行我们的比大小处理即可。

```
#include <bits/stdc++.h>
#define int long long
#define endl '\n'
int INF=0x3f3f3f3f3f3f3f3f;
using namespace std;
typedef pair<int,int> PII;
void init(){
    
}
struct node{
    int f;
    int d;
    int tot;
};

struct node2{
    int val;
    int id;
    int add;
};
void solve(){
    int n,k;
    cin>>n>>k;
    vector<node> weapons(n+1);
  //  vector<int> f(n+1);
    //vector<int> d(n+1);
    for(int i=1;i<=n;i++){
        cin>>weapons[i].f;
    }
    for(int i=1;i<=n;i++){
        cin>>weapons[i].d;
        weapons[i].tot=weapons[i].f*weapons[i].d;
    }
    // sort(begin(weapons)+1,end(weapons),[&](node a,node b){
    //     return a.tot<b.tot;
    // });
    int ans=n;
    for(int i=1;i<=n;i++){
        vector<node2> lst;
        //weapons[i]保持不变
        for(int j=1;j<=n;j++){
            int tmp=weapons[i].tot/weapons[j].f*weapons[j].f;
            lst.push_back({weapons[j].tot,j,1});//保持不变
            if(tmp>0){
                lst.push_back({tmp,j,0});
            }
            lst.push_back({tmp+weapons[j].f,j,0});
        }
        sort(begin(lst),end(lst),[&](node2 a,node2 b){
            return a.val<b.val;
        });
//        vector<int> unchanged(n+1);
        vector<int> types(n+1,0);
        int tot=n;
        int sz=0;
        auto add=[&](int id,int val){
            tot-=val;
            if(types[id]==0){
                sz++;
            }
            types[id]++;
        };
        auto del=[&](int id,int val){
            tot+=val;
            if(types[id]==1){
                sz--;
            }
            types[id]--;
        };
        for(int i=0,j=0;i<lst.size();i++){
            while(j<lst.size()&&lst[j].val-lst[i].val<=k){
                add(lst[j].id,lst[j].add);
                j++;
            }
            if(sz==n){
                ans=min(ans,tot);
//                cerr<<i<<" "<<j<<sz<<endl;
//                cerr<<ans<<" "<<tot<<endl;
                //exit(0);
            }
            del(lst[i].id,lst[i].add);
        }
        //cerr<<ans<<endl;
    }
    cout<<ans<<endl;


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