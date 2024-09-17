小 C 有一个长度为 n 的括号序列。今天，小 C 发现序列上的一些括号消失了。  
  
他十分的生气，于是让集训队的你计算有多少种填补序列的方式，使得得到的序列是个合法的括号序列。  
  
注意到小C的世界中有 m 种括号。  
  
接下来是合法括号序列的定义:  
・ 一个长度为 0 的括号序列是合法的。  
・ 如果 A 是合法的，x 是某种左括号,y 是同种类的右括号，那么 xAy 也是合法的。  
・ 如果 A,B 都是合法的，那么 AB 也是合法的.

输入格式

第一行是 T(1≤T≤20)，表示测试样例组数。  
  
每组样例的第一行是两个整数 n(1≤n≤500),m(1≤m<109+7), 分别表示序列的长度和括号的种数。  
  
第二行是 n 个整数 a1​,a2​,…,an​(∣ai​∣≤m)，代表小C的括号序列。  
  
・ 如果 ai​=0，代表括号消失。  
・ ai​>0, 代表第 ai​ 种括号的左括号。  
・ ai​<0, 代表第 i 种括号的右括号。  
  
数据保证最多只有 15 组测试样例的 n>100。

输出格式

对于每组样例，单独一行输出答案，对 109+7109+7 取模。  
  
出于某种原因，可能没有办法使它成为合法的括号序列，即答案可能为0

样例

|输入copy|输出copy|
|---|---|
|3<br>4 2<br>1 0 0 -1<br>4 2<br>0 0 0 -1<br>6 3<br>0 0 0 0 0 0|3<br>4<br>135|

## 题解
我们这一题考虑用我们的区间 dp 来计算，我们定义 $dp_{1}[l,r]$ 表示 $[l,r]$ 内的复合括号序列，$dp_{2}[l,r]$ 表示我们区间内的合法括号序列，且我们的 $l,r$ 相互匹配。我们的转移就有下面的公式
$$
dp_{2}[l,r]=dp_{2}[i+1][r-1],(两侧括号匹配||单侧有括号)
$$
$$
dp_{2}[l,r]=dp_{2}[l+1,r-1]*m(两侧都没有匹配)
$$
$$
dp_{2}[l,r]=0;
$$

接下来，我们考虑计算我们的 $dp_{1}[l,r]$ 如果我们直接计数的话，一定有重复计数，现在我们就考虑怎么计算我们的重复的计数。![[Pasted image 20231122172110.png]]

如果采用我们的感性认识，我们的 $dp_{2}$ 就是表示我们从 $l,r$ 只有 `嵌套` 类括号的方案数，我们的 $dp[1]$ 就是表示我们从 $L,r$ 各种方案都包含的方案数。然后我们的结果就很好算了。
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;
#define int ll
const int INF = 1e9 + 7, MAXN = 2e5 + 10, mod = 998244353;
void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i ++) {
         cin >> a[i];
    }
    vector<vector<int>> dp2(n + 2, vector<int> (n + 2)), dp1(n + 2, vector<int> (n + 2));
    for(int i = 0; i <= n; i ++) {
        dp1[i + 1][i] = 1;
    }
    for(int len = 2; len <= n; len += 2) {
        for(int l = 1; l <= n; l ++) {
            int r = l + len - 1;
            if(r > n) break;
            if(a[l] == a[r] && a[l] == 0) {
                (dp2[l][r] = dp1[l + 1][r - 1] * m) %= INF;
            } else if(a[l] > 0 && a[r] < 0 && a[l] + a[r] == 0) {
                dp2[l][r] = dp1[l + 1][r - 1];
            } else if((!a[l]  && a[r] < 0) || (!a[r] && a[l] > 0)) {
                dp2[l][r] = dp1[l + 1][r - 1];
            } else {
                dp2[l][r] = 0;
            }
            for(int x = l; x <= r; x ++) {
                (dp1[l][r] += dp1[l][x - 1] * dp2[x][r]) %= INF;
            }
        }
    }
    cout << dp1[1][n] % INF << '\n';
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int _ = 1;
    cin >> _;
    while(_ --) {
        solve();
    }
    return 0;
}
```