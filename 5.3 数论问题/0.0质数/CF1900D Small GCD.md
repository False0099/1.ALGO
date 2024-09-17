Let $a$, $b$, and $c$ be integers. We define function $f(a, b, c)$ as follows:

Order the numbers $a$, $b$, $c$ in such a way that $a \le b \le c$. Then return $\gcd(a, b)$, where $\gcd(a, b)$ denotes the [greatest common divisor (GCD)](https://en.wikipedia.org/wiki/Greatest_common_divisor) of integers $a$ and $b$.

So basically, we take the $\gcd$ of the $2$ smaller values and ignore the biggest one.

You are given an array $a$ of $n$ elements. Compute the sum of $f(a_i, a_j, a_k)$ for each $i$, $j$, $k$, such that $1 \le i  \le j  \le k$.

More formally, compute

$$
\sum_{i = 1}^n \sum_{j = i+1}^n \sum_{k =j +1}^n f(a_i, a_j, a_k).
$$

## 题解
我们这一题，我们可以首先对我们的数组进行一个排序，然后因为我们后面的数对于我们的前面没有影响，所以我们在确定了我们的中间数 $g$ 的时候，我们的贡献系数就是已知的，是我们的 $n-i$。
然后，如果我们想求出我们的 $gcd$ 是多少，我们的思路是枚举我们的 $gcd$ 具体值是多少，然后我们再去检查前面有多少个（我们朴素方法的顺序是先枚举方案，再计算 gcd）。
这里，我们的 $gcd$ 值，一定是我们的当前数字 $x$ 的因子 $y$，

这个问题是经典的容斥 dp，我们可以维护一个数组 $cnt_{i}$, $cnt_{i}$ 表示我们当前 $I$ 的倍数是多少，对于当前的 $x$,我们从大到小枚举因子 $y$ ,设 $gcd(x,a_{i})$,

```cpp
#include<iostream>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
using LL = long long;
const int maxn = 1e5 + 5;
vector<int> factor[maxn];

int main(){

    cin.tie(0);
    cout.tie(0);
    ios::sync_with_stdio(0);

    for(int i = 1; i < maxn; i++){
        for(int j = i; j < maxn; j += i){
            factor[j].push_back(i);
        }
    }

    const int N = 1e5;
    int T;
    cin >> T;
    while(T--){
        int n;
        cin >> n;
        vector<int> a(n);
        for(int i = 0; i < n; i++) cin >> a[i];
        sort(a.begin(), a.end());

        vector<int> cnt(N + 1);
        LL pre = 0;
        LL ans = 0;
        vector<LL> f(N + 1);
        for(int i = 0; i < n; i++){
            int x = a[i];
            ans += pre;
            for(int k = factor[x].size() - 1; k >= 0; k--){
            //cnt表示以t为因数的数有多少个
                int t = factor[x][k];
                f[t] += cnt[t];
                pre += t * f[t];
                for(auto tt : factor[t]){
                    f[tt] -= f[t];
                }
            }
            for(auto t : factor[x]){
                cnt[t] += 1;
                f[t] = 0;
            }
        }
        cout << ans << '\n';
    }

}
```