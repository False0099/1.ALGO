Given an extremely large non-negative integer n, you are asked to count the number of pairs (i,j) of integers satisfying the following conditions:

- 0≤j≤i≤n;
- =i; and
- �i & �=0j=0.

Here `&` represents the bitwise AND operator.

For simplicity, the binary representation of n will be given. Meanwhile, you only need to output the answer modulo (1 e9+7).


### Input

The first line contains an integer � (1≤�≤20)T (1≤T≤20) indicating the number of test cases.

Each of the following �T lines contains a string � (1≤∣�∣≤105)S (1≤∣S∣≤105) which is the binary representation of the non-negative integer �n. Note that leading zeros of �S could appear in the input.

### Output

For each test case, output a line containing the answer described above modulo (109+7)(109+7).

### Sample 1

|Inputcopy|Outputcopy|
|---|---|
|2<br>111<br>1010|14<br>15|
## 题解
我们本题的想法首先是打表一个，但是我们达标之后发现我们找不到什么规律，这个时候，我们有两种思路，一种思路是把我们的结果存储下来，然后考虑 $o(1)$ 输出结果。

但是，由于我们本题中的数字过于庞大，我们放弃这个想法。于是我们需要去寻找我们的对应条件，其中我们发现，关于第二个条件，**对于 n 的每个为 0 的二进制位，i 的对应二进制位也应为 0**。关于第三个条件，**对于 i 的每个位 1 的二进制位，j 的对应二进制位应该为 0**。得到这两个信息后我们不妨尝试找规律。最后结论为：
对于二进制数 n，从右向左数，第 i 个 1，其位于整个数的第 k 位，其贡献为 3 i-1+2 k-1, 答案就是所有的 1 的贡献加上 1 (没有算上 i 和 j 均为0这个数对)。


```
#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define IO ios::sync_with_stdio(false);cin.tie(0);cout.tie(0)

const int MAXN = 2e5 + 5;
const ll mod = 1e9 + 7;
int t, n, m, k, flag = 1;
string s;

ll qukpow_2(int b) {
	ll x = 2, ret = 1;
	while(b) {
		if(b&1) ret = ret * x % mod;
		x = x * x % mod;
		b >>= 1;
	}
	return ret;
}

int main(void) {
	IO;
	cin >> t;
	while(t--) {
		cin >> s;
		int len = s.size();
		ll ans = 1, now = 0;
		for(int i = len - 1; i >= 0; i--) {
			if(s[i] == '1') {
				if(now) {
					now = now * 3 % mod;
					ans += now;
					ans = ans % mod;
				}else {
					now = qukpow_2(len - 1 - i);
					ans += now;
					ans = ans % mod;
				}
			}else {
				now = now * 2 % mod;
			}
		}
		cout << ans << '\n';
	}
}

```