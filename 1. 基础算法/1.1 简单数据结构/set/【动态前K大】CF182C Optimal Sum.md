# Optimal Sum

## 题面翻译

有一个长度为 $n$ 的数列 $a$，可以对它进行最多 $k$ 次操作，每次操作可以将一个数变为它的相反数，输出最后所有长度为 $len$ 的数列的和的绝对值的最大值（是子串和的最大值，而不是子串和的和的最大值）。

## 题目描述

And here goes another problem on arrays. You are given positive integer $ len $ and array $ a $ which consists of $ n $ integers $ a_{1} $ , $ a_{2} $ , ..., $ a_{n} $ . Let's introduce two characteristics for the given array.

- Let's consider an arbitrary interval of the array with length $ len $ , starting in position $ i $ . Value ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF182C/a67922122e1d38581ab8c091ae9897d972811ca1.png), is the modular sum on the chosen interval. In other words, the modular sum is the sum of integers on the chosen interval with length $ len $ , taken in its absolute value.
- Value ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF182C/93dd358f9082d67d4f803ced64f412bb80cdf4c2.png) is the optimal sum of the array. In other words, the optimal sum of an array is the maximum of all modular sums on various intervals of array with length $ len $ .

Your task is to calculate the optimal sum of the given array $ a $ . However, before you do the calculations, you are allowed to produce no more than $ k $ consecutive operations of the following form with this array: one operation means taking an arbitrary number from array $ a_{i} $ and multiply it by -1. In other words, no more than $ k $ times you are allowed to take an arbitrary number $ a_{i} $ from the array and replace it with $ -a_{i} $ . Each number of the array is allowed to choose an arbitrary number of times.

Your task is to calculate the maximum possible optimal sum of the array after at most $ k $ operations described above are completed.

## 输入格式

The first line contains two integers $ n $ , $ len $ ( $ 1<=len<=n<=10^{5} $ ) — the number of elements in the array and the length of the chosen subinterval of the array, correspondingly.

The second line contains a sequence consisting of $ n $ integers $ a_{1} $ , $ a_{2} $ , ..., $ a_{n} $ $ (|a_{i}|<=10^{9}) $ — the original array.

The third line contains a single integer $ k $ ( $ 0<=k<=n $ ) — the maximum allowed number of operations.

All numbers in lines are separated by a single space.

## 输出格式

In a single line print the maximum possible optimal sum after no more than $ k $ acceptable operations are fulfilled.

Please do not use the %lld specifier to read or write 64-bit integers in С++. It is preferred to use cin, cout streams or the %I 64 d specifier.

## 样例 #1

### 样例输入 #1

```
5 3
0 -2 3 -5 1
2
```

### 样例输出 #1

```
10
```

## 样例 #2

### 样例输入 #2

```
5 2
1 -3 -10 4 1
3
```

### 样例输出 #2

```
14
```

## 样例 #3

### 样例输入 #3

```
3 3
-2 -5 4
1
```

### 样例输出 #3

```
11
```

## 题解
我们本题显然的一个贪心是：把我们的所有的正数前 K 大都变成负数，然后把我们的所有的负数前 K 小都变成正数。因此，我们就需要维护我们的 **滑动窗口动态前 K 大**。这里，我们可以使用我们的 set，将我们的元素分成两类，一类是我们的要选择的东西，另一类是我们的其他元素。

我们维护的时候需要注意几个点：
1. 添加元素的时候，我们要注意，我们添加后注意我们的前 K 大是否已满，如果是，我们就不进行处理
2. 我们窗口滑动的时候，我们要看我们删去的哪一个元素属于什么类型，如果属于我们的前 K 大，那么我们就需要考虑**从我们的替补席找一个人上来**。反之，我们就直接删除就好。

```
#include <bits/stdc++.h>
#define int long long
#define endl '\n'
int INF=0x3f3f3f3f3f3f3f3f;
using namespace std;
typedef pair<int,int> PII;
void init(){
    
}
int len,n,k;
int calc(vector<int>& a){
        multiset<int> maxk_element;
        multiset<int> pools;
        int positive_sum=0;
        int tot_sum=0;
        int res=-INF;
        for(int i=0;i<len;i++){
            tot_sum+=a[i];
            if(maxk_element.size()<k&&a[i]>0){
                maxk_element.insert(a[i]);
                positive_sum+=a[i];
            }else if(maxk_element.size()==k&&a[i]>0){
                auto u=*(maxk_element.begin());
                if(a[i]>u){
                    pools.insert(u);
                    positive_sum-=u;
                    maxk_element.erase(maxk_element.find(u));
                    maxk_element.insert(a[i]);
                    positive_sum+=a[i];
                }else{
                    pools.insert(a[i]);
                }
            }
        }
        //cerr<<positive_sum<<" ";
        res=max(res,abs(tot_sum-2*positive_sum));
        for(int i=len,l=0;i<n;i++,l++){
            int prev=a[l];
            tot_sum-=a[l];
            //删除旧元素
            if(maxk_element.find(a[l])!=maxk_element.end()){
                maxk_element.erase(maxk_element.find(a[l]));
                positive_sum-=a[l];
                if(pools.size()!=0){
                    auto u=*(pools.rbegin());
                    pools.erase(pools.find(u));
                    positive_sum+=u;
                    maxk_element.insert(u);
                }
            }else if(pools.find(a[l])!=pools.end()){
                pools.erase(pools.find(a[l]));
            }
            //添加新元素
            int new_item=a[i];
            tot_sum+=a[i];
            if(maxk_element.size()<k&&a[i]>0){
                maxk_element.insert(a[i]);
                positive_sum+=a[i];
            }else if(maxk_element.size()==k&&a[i]>0){
                auto u=*(maxk_element.begin());
                if(a[i]>u){
                    pools.insert(u);
                    positive_sum-=u;
                    maxk_element.erase(maxk_element.find(u));
                    maxk_element.insert(a[i]);
                    positive_sum+=a[i];
                }else{
                    pools.insert(a[i]);
                }
            }
            //cerr<<positive_sum<<" ";
            res=max(res,abs(tot_sum-2*positive_sum));
        }
        //cerr<<endl;
        return res;
    };
void solve(){
    //int n,len;
    cin>>n>>len;
    vector<int> a(n);
    for(int i=0;i<n;i++){
        cin>>a[i];
    }
   //int k;
    cin>>k;
    if(k==0){
        int res=0;
        int tot_sum=0;
        for(int i=0;i<len;i++){
            tot_sum+=a[i];
        }
        res=abs(tot_sum);
        for(int i=len,l=0;i<n;i++,l++){
            tot_sum-=a[l];
            tot_sum+=a[i];
            res=max(res,abs(tot_sum));
        }
        cout<<res<<endl;
        return;
    }
    k=min(k,len);
    calc(a);
    int ans=calc(a);
    for(int i=0;i<n;i++){
        a[i]*=-1;
    }
    ans=max(ans,calc(a));
    cout<<ans<<endl;
}
signed main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int t;
    t=1;
 //   cin>>t;
    init();
    while(t--){
        solve();
    }
}
```