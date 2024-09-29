# Wish I Knew How to Sort

## 题面翻译

给定一个长度为 $n$ 的 01 序列 $a$ 和一种操作，你需要用这种操作将序列从小到大排序。

操作如下：

- 等概率随机选取两个位置 $i,j\ (i<j)$，若 $a_i>a_j$，则交换 $a_i,a_j$。

**注意**：当 $a_i\le a_j$ 时，交换失败，也算作一次操作。

请你求出操作被执行的 **期望次数**。对 998244353 取模。$1\le n\le2\times 10^5,\ a_i\in \{0,1\}$。

## 题目描述

You are given a binary array $ a $ (all elements of the array are $ 0 $ or $ 1 $ ) of length $ n $ . You wish to sort this array, but unfortunately, your algorithms teacher forgot to teach you sorting algorithms. You perform the following operations until $ a $ is sorted:

1. Choose two random indices $ i $ and $ j $ such that $ i < j $ . Indices are chosen equally probable among all pairs of indices $ (i, j) $ such that $ 1 \le i < j \le n $ .
2. If $ a_i > a_j $ , then swap elements $ a_i $ and $ a_j $ .

What is the [expected number](https://en.wikipedia.org/wiki/Expected_value) of such operations you will perform before the array becomes sorted?

It can be shown that the answer can be expressed as an irreducible fraction $ \frac{p}{q} $ , where $ p $ and $ q $ are integers and $ q \not \equiv 0 \pmod{998\, 244\, 353} $ . Output the integer equal to $ p \cdot q^{-1} \bmod 998\, 244\, 353 $ . In other words, output such an integer $ x $ that $ 0 \le x < 998\, 244\, 353 $ and $ x \cdot q \equiv p \pmod{998\, 244\, 353} $ .

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10^5 $ ). Description of the test cases follows.

The first line of each test case contains an integer $ n $ ( $ 1 \le n \le 200\, 000 $ ) — the number of elements in the binary array.

The second line of each test case contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ a_i \in \{0, 1\} $ ) — elements of the array.

It's guaranteed that sum of $ n $ over all test cases does not exceed $ 200\, 000 $ .

## 输出格式

For each test case print one integer — the value $ p \cdot q^{-1} \bmod 998\, 244\, 353 $ .

## 样例 #1

### 样例输入 #1

```
3
3
0 1 0
5
0 0 1 1 1
6
1 1 1 0 0 1
```

### 样例输出 #1

```
3
0
249561107
```

## 提示

Consider the first test case. If the pair of indices $ (2, 3) $ will be chosen, these elements will be swapped and array will become sorted. Otherwise, if one of pairs $ (1, 2) $ or $ (1, 3) $ will be selected, nothing will happen. So, the probability that the array will become sorted after one operation is $ \frac{1}{3} $ , the probability that the array will become sorted after two operations is $ \frac{2}{3} \cdot \frac{1}{3} $ , the probability that the array will become sorted after three operations is $ \frac{2}{3} \cdot \frac{2}{3} \cdot \frac{1}{3} $ and so on. The expected number of operations is $ \sum \limits_{i=1}^{\infty} \left (\frac{2}{3} \right)^{i - 1} \cdot \frac{1}{3} \cdot i = 3 $ .

In the second test case the array is already sorted so the expected number of operations is zero.

In the third test case the expected number of operations equals to $ \frac{75}{4} $ so the answer is $ 75 \cdot 4^{-1} \equiv 249\, 561\, 107 \pmod {998\, 244\, 353} $ .

## 题解：
对于我们的这一类操作类期望，首先，我们能够发现，我们本体是一个**排序问题**，我们对于排序问题最后有序，我们的一个有效的方法是，**通过我们的错位位置有哪些来进行处理**。

于是，我们就考虑通过计算**错位数量之间的贡献**，而显然，错位数量之间的转换是一个**有向无环的转换**。于是，我们就可以通过我们的对应的 dp 来进行处理

```
#include <bits/stdc++.h>
#define int long long
#define endl '\n'
int INF=0x3f3f3f3f3f3f3f3f;
using namespace std;
typedef pair<int,int> PII;
void init(){
    
}
int mod=998244353;
int qmi(int a,int b,int mod){
    int res=1;
    while(b){
        if(b&1){
            res=(res*a)%mod;
        }
        a=(a*a)%mod;
        b>>=1;
    }
    return res;
}
void solve(){
    int n;
    cin>>n;
    vector<int> a(n+1);
    int cnt0=0;
    int cnt1=1;
    for(int i=0;i<n;i++){
        cin>>a[i];
        cnt0+=(a[i]==0);
        cnt1+=(a[i]==1);
    }    
    vector<int> f(n+2,0);
    int m=0;
    for(int i=0;i<cnt0;i++){
        if(a[i]==0){
            continue;
        }else{
            m++;
        }
    }
    for(int i=1;i<=m;i++){
        f[i]=(f[i-1]+n*(n-1)%mod*qmi(2*i%mod*i%mod,mod-2,mod)%mod)%mod;
    }
    cout<<f[m]<<endl;
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