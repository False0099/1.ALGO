# [USACO 13 NOV] No Change G

## 题目描述

Farmer John is at the market to purchase supplies for his farm.  He has in his pocket K coins (1 <= K <= 16), each with value in the range 1.. 100,000,000.  FJ would like to make a sequence of N purchases (1 <= N <= 100,000), where the ith purchase costs c (i) units of money (1 <= c (i) <= 10,000).  As he makes this sequence of purchases, he can periodically stop and pay, with a single coin, for all the purchases made since his last payment (of course, the single coin he uses must be large enough to pay for all of these).  Unfortunately, the vendors at the market are completely out of change, so whenever FJ uses a coin that is larger than the amount of money he owes, he sadly receives no changes in return!

Please compute the maximum amount of money FJ can end up with after making his N purchases in sequence.  Output -1 if it is impossible for FJ to make all of his purchases.

约翰到商场购物，他的钱包里有 K (1 <= K <= 16)个硬币，面值的范围是 1.. 100,000,000。

约翰想按顺序买 N 个物品 (1 <= N <= 100,000)，第 i 个物品需要花费 c (i)块钱，(1 <= c (i) <= 10,000)。

在依次进行的购买 N 个物品的过程中，约翰可以随时停下来付款，每次付款只用一个硬币，支付购买的内容是从上一次支付后开始到现在的这些所有物品（前提是该硬币足以支付这些物品的费用）。不幸的是，商场的收银机坏了，如果约翰支付的硬币面值大于所需的费用，他不会得到任何找零。

请计算出在购买完 N 个物品后，约翰最多剩下多少钱。如果无法完成购买，输出-1

## 输入格式

\* Line 1: Two integers, K and N.

\* Lines 2.. 1+K: Each line contains the amount of money of one of FJ's coins.

\* Lines 2+K..1+N+K: These N lines contain the costs of FJ's intended purchases.

## 输出格式

\* Line 1: The maximum amount of money FJ can end up with, or -1 if FJ cannot complete all of his purchases.

## 样例 #1

### 样例输入 #1

```
3 6 
12 
15 
10 
6 
3 
3 
2 
3 
7
```

### 样例输出 #1

```
12
```

## 提示

FJ has 3 coins of values 12, 15, and 10.  He must make purchases in sequence of value 6, 3, 3, 2, 3, and 7.


FJ spends his 10-unit coin on the first two purchases, then the 15-unit coin on the remaining purchases.  This leaves him with the 12-unit coin.

## 题解
本题我们思考能不能正着做，正着设置我们的 DP 状态，我们发现这一个好像不太方便。这个时候，我们可以考虑下面的几种方法：
1. 转换为贡献
2. 转换为检验问题
在本题中，我们选择了转换为检验问题，我们考虑枚举我们的硬币使用情况 S，我们对于每一种 S，求出这一种 S 的情况下，能够购买前多少个物品，如果我们有 $f[S]=n$,那么这一个状态就是我们需要的合法状态之一。

之后，我们考虑怎么对于我们的一个 $S\to S\oplus(1\ll j)$ 来进行处理，显然我们现在应该有一个贪心的解法：我们尽可能多的买，直到我们买不起。

```cpp
#include <bits/stdc++.h>
#define int long long
#define endl '\n'
int INF=0x3f3f3f3f3f3f3f3f;
using namespace std;
typedef pair<int,int> PII;
void init(){
    
}
const int N=1e5+10;
const int S=(1ll<<17);
int dp[S];
int sum[N];
int c[N];
void solve(){
    int k,n;
    cin>>k>>n;
    vector<int> coins(k);
    for(int i=0;i<k;i++){
        cin>>coins[i];
//        coins.push_back(u);
    }
//    vector<int> c(n+1,0);
  //  vector<int> sum(n+1,0);
    for(int i=1;i<=n;i++){
        cin>>c[i];
        sum[i]=sum[i-1]+c[i];
    }
    dp[0]=0;
    for(int i=0;i<(1ll<<k);i++){
        for(int j=0;j<k;j++){
            if((i>>j)&1==1){
                int states_before=(i^(1<<j));
                int pre_pos=dp[states_before];
                int l=1,r=n;
                auto check=[&](int mid){
                    if(sum[mid]-sum[pre_pos]<=coins[j]){
                        return true;
                    }else{
                        return false;
                    }
                };
                while(l<r){
                    int mid=l+r>>1;
                  //  cerr<<mid<<endl;
                    if(check(mid)){
                        l=mid+1;
                    }else{
                        r=mid;
                    }
                    //cerr<<l<<" "<<r<<endl;
                }
                //cout<<i<<" "<<check(5)<<endl;
                int k=l-1;
                if(l<=n&&check(l)){
                    k=l;
                }
                //cerr<<states_before<<" "<<i<<" "<<k<<" "<<endl;
                dp[i]=max(dp[i],k);
            }
        }
    }
    // for(int i=0;i<(1ll<<k);i++){
    //     cerr<<dp[i]<<endl;
    // }
    int res=-INF;
    for(int i=0;i<(1ll<<k);i++){
        if(dp[i]>=n){
            int tmp=0;
            for(int j=0;j<k;j++){
                if(((i>>j)&1)!=1){
                    tmp+=coins[j];   
                }
            }
            res=max(res,tmp);
        }
    }
    if(res==-INF){
        cout<<-1<<endl;
    }else{
        cout<<res<<endl;
    }
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