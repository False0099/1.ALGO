# [USACO 13 OPEN] Fuel Economy S

## 题目描述

Farmer John has decided to take a cross-country vacation. Not wanting his cows to feel left out, however, he has decided to rent a large truck and to bring the cows with him as well!

The truck has a large tank that can hold up to G units of fuel (1 <= G <= 1,000,000).  Unfortunately, it gets very poor mileage: it consumes one unit of fuel for every unit of distance traveled, and FJ has a total of D units of distance to travel along his route (1 <= D <= 1,000,000,000).

Since FJ knows he will probably need to stop to refill his tank several times along his trip, he makes a list of all the N fuel stations along his route (1 <= N <= 50,000).  For each station i, he records its distance X\_i from the start of the route (0 <= X\_i <= D), as well as the price Y\_i per unit of fuel it sells (1 <= Y\_i <= 1,000,000).

Given this information, and the fact that FJ starts his journey with exactly B units of fuel (0 <= B <= D), please determine the minimum amount of money FJ will need to pay for fuel in order to reach his destination. If it is impossible for him to reach the destination, please output -1. Note that the answer to this problem may not fit into a standard 32-bit integer.


Farmer John 决定去一次跨国旅游度假。为了不让他的奶牛们感到被抛弃，他决定租一辆大卡车来带他的奶牛们一起旅行。


这辆卡车有一个很大的油箱，可以装下 $G$ 个单位的油（$1 \le G \le {10}^6$），不幸的是，卡车的耗油量也很大，卡车每运动一个单位的距离，就要消耗一个单位的油。Farmer John 要在他的旅程中走 $D$ 个单位的距离。（$1 \le D \le {10}^9$）


因为 FJ 直到他可能要几次在旅途中停下，给油箱加油，所以他把在旅途沿路上的 $N$ 个加油站的记录做成了表格。对于第 $i$ 个加油站，他记录了加油站与起点的距离 $X_i$（$0 \le X_i \le D$），以及加油站中每单位油的价格 $Y_i$（$1 \le Y_i \le {10}^6$）。

已知以上所给的信息，以及 FJ 在路途开始时拥有的燃油的数量 $B$（$0 \le B \le D$），请计算出 FJ 到达目的地时花费的油费用的最小值。如果 FJ 无法到达旅途的终点，那么请输出 `-1`。本题的答案可能无法使用 32 位整数储存。

## 输入格式

第一行： 四个整数：$N, G, B, D$

接下来 $N$ 行：每一行都有两个整数 $X_i$ 与 $Y_i$，意义如上所述

## 输出格式

一个整数，如果 FJ 无法到达旅途的终点，那么输出 `-1`，否则输出 FJ 到达目的地时花费的油费用的最小值。

## 样例 #1

### 样例输入 #1

```
4 10 3 17
2 40
9 15
5 7
10 12
```

### 样例输出 #1

```
174
```

## 提示

样例解释：FJ 先移动 $2$ 个单位，然后停下购买 $2$ 个单位的油（要花费 $40 \times 2$）。然后一直前进到距离起点 $5$ 个单位的地方，此时油箱为空。这时向油箱里加满油（要花费 $7 \times 10$）。再向前走 $5$ 个单位，加 $2$ 个单位的油（花费 $12 \times 2$）。最后一直走到终点。此时总花费是 $174$。

## 题解
我们本题也是我们的进化论贪心的典型题目，我们的思路是：**先满足要求，再考虑最优**，我们考虑怎么样能够满足我们的要求，显然我们到一个站就加满我们的油就能**满足我们的要求**，之后我们再看怎么能够**到达最优状态**。

我们如果希望能够到达最优状态，我们首先可以做下面的优化：
1. 我们到终点站时，剩下的空余的油可以全部都丢弃
2. 我们到达一个站，我们就把我们的原本更贵的油换成更便宜的油，并且能换就全部换
3. 我们在路上，尽可能的使用更便宜的油

综上，我们就已经完成了我们的**最优化**，我们最后只需要计算我们的答案即可。
```
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e6+10;
struct node{
    int dist;
    int val;
    bool operator < (node a){
        return dist<a.dist;
    }
}station[N];
struct oil{
    int num;
    int val;
};
int n,g,b,d;
signed main(){
    cin>>n>>g>>b>>d;
    for(int i=1;i<=n;i++){
        cin>>station[i].dist>>station[i].val;
    }
    sort(station+1,station+1+n);
    deque<oil> q;
    q.push_back({b,0});
    int val=0;
    for(int i=1;i<=n;i++){
        int oil_now;
        if(i==1){
            oil_now=b;
        }else{
            oil_now=g;
        }
        int dist_now=station[i].dist-station[i-1].dist;
        while(q.size()&&dist_now>0){
            if(dist_now>=q.front().num){
                dist_now-=q.front().num;

                oil_now-=q.front().num;

                q.pop_front();

            }else{

                q.front().num-=dist_now;

                oil_now-=dist_now;

                dist_now=0;

            }

        }

        if(dist_now){

            cout<<-1<<endl;

            return 0;

        }
        while(q.size()&&q.back().val>station[i].val){
            val-=(q.back().val)*q.back().num;
            oil_now-=q.back().num;
            q.pop_back();
        }
        q.push_back({g-oil_now,station[i].val});
        val+=(g-oil_now)*station[i].val;
    }
    int dist_now=d-station[n].dist;
    while(q.size()&&dist_now!=0){
        if(dist_now>=q.front().num){
            dist_now-=q.front().num;
            q.pop_front();
        }else{
            q.front().num-=dist_now;
            dist_now=0;
        }
    }
    if(dist_now){
        cout<<"-1"<<endl;
        return 0;
    }
    while(q.size()){
        int nums=q.back().num;
        int vall=q.back().val;
        val-=vall*nums;
        q.pop_back();
    }
    cout<<val<<endl;
}
```