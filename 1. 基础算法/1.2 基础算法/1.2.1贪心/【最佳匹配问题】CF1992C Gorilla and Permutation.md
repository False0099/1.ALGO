# Gorilla and Permutation

## 题目描述

Gorilla and Noobish\_Monk found three numbers $ n $ , $ m $ , and $ k $ ( $ m < k $ ). They decided to construct a permutation $ ^{\dagger} $ of length $ n $ .

For the permutation, Noobish\_Monk came up with the following function: $ g (i) $ is the sum of all the numbers in the permutation on a prefix of length $ i $ that are not greater than $ m $ . Similarly, Gorilla came up with the function $ f $ , where $ f (i) $ is the sum of all the numbers in the permutation on a prefix of length $ i $ that are not less than $ k $ . A prefix of length $ i $ is a subarray consisting of the first $ i $ elements of the original array.

For example, if $ n = 5 $ , $ m = 2 $ , $ k = 5 $ , and the permutation is $ [5, 3, 4, 1, 2] $ , then:

- $ f (1) = 5 $ , because $ 5 \ge 5 $ ; $ g (1) = 0 $ , because $ 5 > 2 $ ;
- $ f (2) = 5 $ , because $ 3 < 5 $ ; $ g(2) = 0 $ , because $ 3 > 2 $ ;
- $ f (3) = 5 $ , because $ 4 < 5 $ ; $ g(3) = 0 $ , because $ 4 > 2 $ ;
- $ f (4) = 5 $ , because $ 1 < 5 $ ; $ g (4) = 1 $ , because $ 1 \le 2 $ ;
- $ f (5) = 5 $ , because $ 2 < 5 $ ; $ g (5) = 1 + 2 = 3 $ , because $ 2 \le 2 $ .

Help them find a permutation for which the value of $ \left (\sum_{i=1}^n f (i) - \sum_{i=1}^n g (i)\right) $ is maximized.

 $ ^{\dagger} $ A permutation of length $ n $ is an array consisting of $ n $ distinct integers from $ 1 $ to $ n $ in any order. For example, $ [2,3,1,5,4] $ is a permutation, but $ [1,2,2] $ is not a permutation (as $ 2 $ appears twice in the array) and $ [1,3,4] $ is also not a permutation (as $ n=3 $ , but $ 4 $ appears in the array).

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

The only line of each case contains three integers $ n $ , $ m $ , $ k $ ( $ 2\le n \le 10^5 $ ; $ 1 \le m < k \le n $ ) — the size of the permutation to be constructed and two integers.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output the permutation — a set of numbers that satisfies the conditions of the problem. If there are multiple solutions, output any of them.

## 样例 #1

### 样例输入 #1

```
3
5 2 5
3 1 3
10 3 8
```

### 样例输出 #1

```
5 3 4 1 2
3 2 1
10 9 8 4 7 5 6 1 2 3
```

## 提示

In the first example, $ \left (\sum_{i=1}^n f (i) - \sum_{i=1}^n g (i)\right) = 5 \cdot 5 - (0 \cdot 3 + 1 + 3) = 25 - 4 = 21 $

## 题解
本题，我们考虑可以通过我们的一个贪心步骤来进行：
第一步：我们希望尽可能的最大化我们的 $g[i]$,同时我们希望尽可能的最小化我们的 $f[i]$。于是，我们可以考虑我们能否做到，我们发现是可以的，我们最好的方法就是把我们的前 $(n,k)$ 都放在我们的最前面，剩下的我们按照 $(m+1,k)$ 放在我们的后面，最后的剩余元素，我们随便放即可。
```cpp
#include <bits/stdc++.h>
#define int long long
int INF=0x3f3f3f3f3f;
using namespace std;
void solve(){
    int n,m,k;
    cin>>n>>m>>k;
    vector<int> ans;
    for(int i=n;i>=k;i--){
        //ans.push_back(i);
        cout<<i<<" ";
    }
    for(int i=m+1;i<k;i++){
        cout<<i<<" ";
    }
    for(int i=1;i<=m;i++){
        cout<<i<<" ";
    }
    cout<<endl;
}
signed main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int t;
    cin>>t;
    while(t--){
        solve();
    }
}
```