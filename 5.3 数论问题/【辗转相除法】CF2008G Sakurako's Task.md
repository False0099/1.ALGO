# Sakurako's Task

## 题目描述

Sakurako has prepared a task for you:

She gives you an array of $ n $ integers and allows you to choose $ i $ and $ j $ such that $ i \neq j $ and $ a_i \ge a_j $ , and then assign $ a_i = a_i - a_j $ or $ a_i = a_i + a_j $ . You can perform this operation any number of times for any $ i $ and $ j $ , as long as they satisfy the conditions.

Sakurako asks you what is the maximum possible value of $ mex_k $ $ ^{\text{∗}} $ of the array after any number of operations.

 $ ^{\text{∗}} $ $ mex_k $ is the $ k $ -th non-negative integer that is absent in the array. For example, $ mex_1 (\{1,2,3 \})=0 $ , since $ 0 $ is the first element that is not in the array, and $ mex_2 (\{0,2,4 \})=3 $ , since $ 3 $ is the second element that is not in the array.

## 输入格式

The first line contains a single integer $ t $ ( $ 1\le t\le 10^4 $ ) — the number of test cases.

The first line of each test case contains two integers $ n $ and $ k $ ( $ 1\le n\le 2\cdot 10^5,1\le k\le 10^9 $ ) — the number of elements in the array and the value $ k $ for $ mex_k $ .

The second line of each test case contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ 1\le a_i\le 10^9 $ ) — the elements of the array.

It is guaranteed that the sum of $ n $ across all test cases does not exceed $ 2\cdot 10^5 $ .

## 输出格式

For each test case, output the maximum $ mex_k $ that can be achieved through the operations.

## 样例 #1

### 样例输入 #1

```
6
1 3
3
2 10
1 1
3 1
1 2 3
3 2
1 2 4
4 5
2 2 2 16
4 5
2 2 2 3
```

### 样例输出 #1

```
2
11
3
4
8
8
```

## 题解
可以知道，我们最后如果希望我们的 mex 尽可能的大，我们最后的数组一定是构造成形如：
$$
0,gcd,2*gc\mathbf{d}\dots,(n-1)*gcd
$$

这样的，才能够最大化我们的 $mex_{k}$。于是，我们就可以通过我们的对应推式子来退出来我们的 $mex_{k}$ 是多少。我们的思路是，我们如果现在 $mex$ 在我们的 $(0,gcd)$ 之间，我们就可以通过使用 $gcd-1$ 个名额，然我们的 gcd 变成我们的 $gcd+1$。对于剩余的部分，我们则可以通过直接相加得到。

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
    int n,k;
    cin>>n>>k;
    vector<int> a(n+1);
    int gcd=0;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        gcd=__gcd(gcd,a[i]);
    }   
    if(n==1){
        if(a[1]<k){
            cout<<k<<endl;
        }else{
            cout<<k-1<<endl;
        }
        return;
    }
    if(n!=1){
        for(int i=1;i<=n;i++){
            a[i]=gcd*(i-1);
        }
    }
    // for(int i=1;i<=n;i++){
    //     cerr<<a[i]<<" ";
    // }
    // cerr<<endl;
    int mex=1;
    for(int i=2;i<=n;i++){
        if(gcd-1<k){
            k-=(gcd-1);
            mex=a[i];
        }else{
            mex=a[i-1]+k;
            k=0;
            break;
        }
    }
    //cerr<<mex<<endl;
    if(k){
        mex+=k;
    }
    cout<<mex<<endl;

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