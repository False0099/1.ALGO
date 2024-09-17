# [AGC 038 C] LCMs

## 题面翻译

- 给定一个长度为 $N$ 的数列 $A_1, A_2, A_3, \ldots, A_N$。
- 请你求出 $\sum_{i=1}^{N}\sum_{j=i+1}^{N}\mathrm{lcm}(A_i,A_j)$ 的值模 $998244353$ 的结果。
- $1 \leq N \leq 2 \times 10^5$，$1 \leq A_i \leq 10^6$。

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc038/tasks/agc038_c

長さ $ N $ の整数列 $ A_0, A_1,\cdots, A_{N-1} $ があります。次式の値を求めてください。

- $ \sum_{i=0}^{N-2}\ \sum_{j=i+1}^{N-1}\ \mathrm{lcm}(A_i, A_j) $

ここで、$ \mathrm{lcm}(x, y) $ は、$ x $ と $ y $ の最小公倍数を意味します。 なお、答えは非常に大きくなることがあるので、$ 998244353 $ で割ったあまりを求めてください。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ N $ $ A_0\ A_1\ \cdots\ A_{N-1} $

## 输出格式

$ \sum_{i=0}^{N-2}\ \sum_{j=i+1}^{N-1}\ \mathrm{lcm}(A_i, A_j) $ の値を $ 998244353 $ で割ったあまりを出力せよ。

## 样例 #1

### 样例输入 #1

```
3
2 4 6
```

### 样例输出 #1

```
22
```

## 样例 #2

### 样例输入 #2

```
8
1 2 3 4 6 8 12 12
```

### 样例输出 #2

```
313
```

## 样例 #3

### 样例输入 #3

```
10
356822 296174 484500 710640 518322 888250 259161 609120 592348 713644
```

### 样例输出 #3

```
353891724
```

## 提示

### 制約

- $ 1\ \leq\ N\ \leq\ 200000 $
- $ 1\ \leq\ A_i\ \leq\ 1000000 $
- 入力される値はすべて整数である。

### Sample Explanation 1

$ \mathrm{lcm}(2,4)+\mathrm{lcm}(2,6)+\mathrm{lcm}(4,6)=4+6+12=22 $ です。

## 题解
本题是我们的 P 3911 的双倍经验，我们只需要修改一下我们的部分内容即可。
```cpp
// LUOGU_RID: 175701305
// LUOGU_RID: 175697484
#include <bits/stdc++.h>
#define int long long
#define endl '\n'
int INF = 0x3f3f3f3f3f3f3f3f;
using namespace std;
typedef pair<int, int> PII;
const int N = 1e6 + 10;
bool vis[N];
int miu[N];
int sum1[N];
int cnt = 0;
int pri[N];
int cnt_n[N];
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
void init() {
    miu[1] = 1;
    for (int i = 2; i < N; i++) {
        if (!vis[i]) {
            vis[i] = 1;
            miu[i] = -1;
            pri[++cnt] = i;
        }
        for (int j = 1; i * pri[j] < N && j <= cnt; j++) {
            vis[i * pri[j]] = 1;
            if (i % pri[j]) {
                miu[i * pri[j]] = miu[i] * -1;
            } else {
                miu[i * pri[j]] = 0;
                break;
            }
        }
    }
    for (int i = 1; i < N; i++)
        for (int j = i; j < N; j += i)
            sum1[j] = (sum1[j]+i * miu[i])%mod;
}

void solve() {
    long long n;
    cin >> n;
    vector<int> a(n);
//    map<int, int> cnt;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        cnt_n[a[i]]++;
    }
    int m=n;
    n = (int) *max_element(begin(a), end(a));
    int ans = 0;
    for (int t = 1; t <= n; t++) {
        int res = t * sum1[t]%mod;
        int sum2 = 0;
        for (int i = 1; i <= n / t; i++) {
            
                sum2 =(sum2+ (cnt_n[i * t] * i)%mod)%mod;
            
        }
        res=(res*sum2)%mod;
        res=(res*sum2)%mod;
//        res *= sum2 * sum2;
        ans=(ans+res)%mod;
//        ans += res;
    }
//    cout<<ans<<endl;
    for(int i=0;i<m;i++){
        ans=(ans-a[i]+mod)%mod;
    }
    cout << (ans*qmi(2,mod-2,mod))%mod<< endl;
}

signed main() {
    ios::sync_with_stdio(false), cin.tie(0);
    int t;
    t = 1;
    // cin >> t;
    init();
    while (t--) {
        solve();
    }
}
```