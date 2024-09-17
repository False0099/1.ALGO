# Increasing Sequence with Fixed OR

## 题目描述
中文：给你一个数，要求你构造一个最长的数组，满足对于任意的元素，都有 $a[i]|a[i-1]=n$ 并且我们的 a 递增


You are given a positive integer $ n $ . Find the longest sequence of positive integers $ a=[a_1, a_2,\ldots, a_k] $ that satisfies the following conditions, and print the sequence:

- $ a_i\le n $ for all $ 1\le i\le k $ .
- $ a $ is strictly increasing. That is, $ a_i>a_{i-1} $ for all $ 2\le i\le k $ .
- $ a_i\,|\, a_{i-1}=n $ for all $ 2\le i\le k $ , where $ | $ denotes the [bitwise OR operation](https://en.wikipedia.org/wiki/Bitwise_operation#OR).

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 1000 $ ). Description of the test cases follows.

The only line of each test case contains one integer $ n $ ( $ 1\le n\le 10^{18} $ ).

It's guaranteed that the sum of lengths of the longest valid sequences does not exceed $ 5\cdot 10^5 $ .

## 输出格式

For each testcase, print two lines. In the first line, print the length of your constructed sequence, $ k $ . In the second line, print $ k $ positive integers, denoting the sequence. If there are multiple longest sequences, you can print any of them.

## 样例 #1

### 样例输入 #1

```
4
1
3
14
23
```

### 样例输出 #1

```
1
1
3
1 2 3
4
4 10 12 14
5
7 18 21 22 23
```

## 题解
我们不难发现，我们的最后的次数就是我们的**二进制中 1 的个数+1**，这个时候，我们就像，我们的构造是不是和我们的 lowbit 有关。我们发现是的，我们可以通过每一次**只消去我们的原本二进制位中的 1 个 1**来保证我们的**任意两个数或运算结果都是相同的**。
于是，我们就完成了本题的构造：
```
#include <bits/stdc++.h>

#define int long long

int INF=0x3f3f3f3f3f;

using namespace std;

void solve(){

    int num;

    cin>>num;

    int tmp=num;

    vector<int> ans;

    for(int i=60;i>=0;i--){

        int u=(num>>i)&1;

        if(u==1){

            ans.push_back(num^(1ll<<i));

        }

    }  

    ans.push_back(num);

    sort(ans.begin(),ans.end());

    if(ans[0]==0){

        cout<<ans.size()-1<<endl;

        for(auto u:ans){

            if(u==0){

                continue;

            }else{

                cout<<u<<" ";

            }

        }

        cout<<endl;

    }else{

         cout<<ans.size()<<endl;

            for(auto u:ans){

                cout<<u<<" ";

            }

            cout<<endl;

    }

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