# Bits

## 题面翻译

```
- $n$组询问，每次给出一个区间$l, r$，你需要输出在这个区间内二进制表示中1的个数最多的数

- 如有多个答案，输出最小的那个

- $(n \leq10^4, 0\leq l, r \leq10^{18})$

```
### 效果
- $n$ 组询问，每次给出一个区间 $l, r$，你需要输出在这个区间内二进制表示中 1 的个数最多的数

- 如有多个答案，输出最小的那个

- $(n \leq10^4, 0\leq l, r \leq10^{18})$

## 题目描述

Let's denote as ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF484A/b30c9ebcde0f9929e0344fbd7e7dae947e957ee2.png) the number of bits set ('1' bits) in the binary representation of the non-negative integer $ x $ .

You are given multiple queries consisting of pairs of integers $ l $ and $ r $ . For each query, find the $ x $ , such that $ l<=x<=r $ , and ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF484A/b30c9ebcde0f9929e0344fbd7e7dae947e957ee2.png) is maximum possible. If there are multiple such numbers find the smallest of them.

## 输入格式

Let's denote as ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF484A/b30c9ebcde0f9929e0344fbd7e7dae947e957ee2.png) the number of bits set ('1' bits) in the binary representation of the non-negative integer $ x $ .

You are given multiple queries consisting of pairs of integers $ l $ and $ r $ . For each query, find the $ x $ , such that $ l<=x<=r $ , and ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF484A/b30c9ebcde0f9929e0344fbd7e7dae947e957ee2.png) is maximum possible. If there are multiple such numbers find the smallest of them.

## 输出格式

For each query print the answer in a separate line.

## 样例 #1

### 样例输入 #1

```
3
1 2
2 4
1 10
```

### 样例输出 #1

```
1
3
7
```

## 提示

Let's denote as ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF484A/b30c9ebcde0f9929e0344fbd7e7dae947e957ee2.png) the number of bits set ('1' bits) in the binary representation of the non-negative integer $ x $ .

You are given multiple queries consisting of pairs of integers $ l $ and $ r $ . For each query, find the $ x $ , such that $ l<=x<=r $ , and ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF484A/b30c9ebcde0f9929e0344fbd7e7dae947e957ee2.png) is maximum possible. If there are multiple such numbers find the smallest of them.

## 题解
本题我们显然考虑拆位，我们考虑固定我们的右端点，考虑我们的 $[0,r]$ 中 1 最多的数有多少个，然后我们再去从我们的对应的数字里面考虑是否满足 $\geq l$ 的限制条件，如果满足，我们才能去对我们的答案做贡献，否则我们不做贡献。

或者我们考虑下面的一种思路，从最低位开始（二进制），每次尝试将 l 的当前位变为 1。如果变为 1 后会大于右边界 r，则终止循环，输出当前的 l。
```cpp
#include <bits/stdc++.h>
#define int long long
#define endl '\n'
int INF=0x3f3f3f3f3f3f3f3f;
using namespace std;
typedef pair<int,int> PII;
void init(){
    
}
int calc(int u){
    int res=0;
    while(u){
        u-=(u&(-u));
        res++;
    }
    return res;
}
void solve(){
    int a,b;
    cin>>a>>b;
    int ans=0;
    int num=b;
    ans=max(calc(b),ans);
    for(int i=63;i>=0;i--){
        int u=(b>>i)&1;
        if(u==1){
            int t=(1ll<<i)-1;
            int tmp=b-(1ll<<i);
            tmp|=t;
            if(tmp>=a){
                if(calc(tmp)>ans){
                    ans=calc(tmp);
                    num=tmp;
                }else if(calc(tmp)==ans){
                    num=min(num,tmp);
                }
                //ans=max(ans,calc(tmp));
            }
            //cerr<<ans<<endl;
        }
    }
    //cerr<<calc(3)<<endl;
    cout<<num<<endl;
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