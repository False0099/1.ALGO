# New Year's Problem

## 题面翻译

### 题目描述
Vlad 有 $n$ 个朋友，每个朋友需要且仅需要 $1$ 个礼物。有 $m$ 家礼物商店，如果在第 $i$ 个商店中为朋友 $j$ 买礼物，朋友 $j$ 将获得 $p_{ij}$ 的快乐值。

由于时间紧迫， Vlad 最多只会在 $n-1$ 家不同的商店中买礼物。请你使每位朋友能获得的快乐值中的最小值最大。
### 输入格式
第一行一个整数 $t$，表示有 $t$ 组测试数据。

每组测试数据之间有一个空行。对于每组测试数据，第一行两个整数 $m$ 和 $n$。接下来 $m$ 行，每行 $n$ 个整数，其中第 $i$ 行的第 $j$ 个数表示 $p_{ij}$。

保证 $t\leq10^4$，$p_{ij}\leq10^9$，$n\geq2$，且所有测试数据中 $n\cdot m$ 的和不超过 $10^5$。
### 输出格式
输出 $t$ 行，每行包含对应测试数据的答案，即 Vlad 的朋友中最小快乐值的最大值。

## 题目描述

Vlad has $ n $ friends, for each of whom he wants to buy one gift for the New Year.

There are $ m $ shops in the city, in each of which he can buy a gift for any of his friends. If the $ j $ -th friend ( $ 1 \le j \le n $ ) receives a gift bought in the shop with the number $ i $ ( $ 1 \le i \le m $ ), then the friend receives $ p_{ij} $ units of joy. The rectangular table $ p_{ij} $ is given in the input.

Vlad has time to visit at most $ n-1 $ shops (where $ n $ is the number of friends). He chooses which shops he will visit and for which friends he will buy gifts in each of them.

Let the $ j $ -th friend receive $ a_j $ units of joy from Vlad's gift. Let's find the value $ \alpha=\min\{a_1, a_2, \dots, a_n\} $ . Vlad's goal is to buy gifts so that the value of $ \alpha $ is as large as possible. In other words, Vlad wants to maximize the minimum of the joys of his friends.

For example, let $ m = 2 $ , $ n = 2 $ . Let the joy from the gifts that we can buy in the first shop: $ p_{11} = 1 $ , $ p_{12}=2 $ , in the second shop: $ p_{21} = 3 $ , $ p_{22}=4 $ .

Then it is enough for Vlad to go only to the second shop and buy a gift for the first friend, bringing joy $ 3 $ , and for the second — bringing joy $ 4 $ . In this case, the value $ \alpha $ will be equal to $ \min\{3, 4\} = 3 $

Help Vlad choose gifts for his friends so that the value of $ \alpha $ is as high as possible. Please note that each friend must receive one gift. Vlad can visit at most $ n-1 $ shops (where $ n $ is the number of friends). In the shop, he can buy any number of gifts.

## 输入格式

The first line of the input contains an integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases in the input.

An empty line is written before each test case. Then there is a line containing integers $ m $ and $ n $ ( $ 2 \le n $ , $ 2 \le n \cdot m \le 10^5 $ ) separated by a space — the number of shops and the number of friends, where $ n \cdot m $ is the product of $ n $ and $ m $ .

Then $ m $ lines follow, each containing $ n $ numbers. The number in the $ i $ -th row of the $ j $ -th column $ p_{ij} $ ( $ 1 \le p_{ij} \le 10^9 $ ) is the joy of the product intended for friend number $ j $ in shop number $ i $ .

It is guaranteed that the sum of the values $ n \cdot m $ over all test cases in the test does not exceed $ 10^5 $ .

## 输出格式

Print $ t $ lines, each line must contain the answer to the corresponding test case — the maximum possible value of $ \alpha $ , where $ \alpha $ is the minimum of the joys from a gift for all of Vlad's friends.

## 样例 #1

### 样例输入 #1

```
5

2 2
1 2
3 4

4 3
1 3 1
3 1 1
1 2 2
1 1 3

2 3
5 3 4
2 5 1

4 2
7 9
8 1
9 6
10 8

2 4
6 5 2 1
7 9 7 2
```

### 样例输出 #1

```
3
2
4
8
2
```

## 题解
我们这一题发现了关键词最小值最大，我们考虑使用二分枚举我们的答案。然后我们的问题就变成了怎么去检查所有可能的情况。

这里，我们不能满足条件的情况，可以分为我们的下面两种情况：
情况一：我们有一个人在哪里都买不到他所需要的礼物
情况二：我们没有一个商店可以满足两个或以上的人。

其余的情况就一定是可以满足的。

```cpp
#include<bits/stdc++.h>
#define lhr long long
using namespace std;
lhr t,n,m,a[200005],b,l=0,r=1000000000;
bool check(int x){
    for(int i=1;i<=n;++i){
        int f=1;
        for(int j=1;j<=m;++j)
            if(a[(j-1)*n+i]>=x) f=0;
        if(f) return 0;
    }
    for(int i=1;i<=m;++i){
        int cnt=0;
        for(int j=1;j<=n;++j)
            if(a[(i-1)*n+j]>=x) cnt++;
        if(cnt>=2) return 2;
    }
    return 0;
}
int main(){
    cin>>t;
    while(t--){
        cin>>m>>n;
        for(int i=1;i<=m;++i)
            for(int j=1;j<=n;++j) cin>>a[(i-1)*n+j];
        l=0,r=1000000000;
        while(l<r){
            int mid=(l+r)/2;
            if(check(mid+1)) l=mid+1;
            else r=mid;
        }
        cout<<l<<endl;
    }
    return 0;
}
```