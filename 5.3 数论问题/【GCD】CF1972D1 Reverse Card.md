**The two versions are different problems. You may want to read both versions. You can make hacks only if both versions are solved.**

You are given two positive integers $n$, $m$.

Calculate the number of ordered pairs $(a, b)$ satisfying the following conditions:

-   $1\le a\le n$, $1\le b\le m$;
-   $a+b$ is a multiple of $b \cdot \gcd(a,b)$.

**Input**

Each test contains multiple test cases. The first line contains the number of test cases $t$ ($1\le t\le 10^4$). The description of the test cases follows.

The first line of each test case contains two integers $n$, $m$ ($1\le n,m\le 2 \cdot 10^6$).

It is guaranteed that neither the sum of $n$ nor the sum of $m$ over all test cases exceeds $2 \cdot 10^6$.


**Output**

For each test case, print a single integer: the number of valid pairs.

## 题解
对于本类题目，我们的首先需要枚举我们的 $a,b$ 这一点是几乎肯定的，但是，我们要怎么美剧能够更优秀，注意到，我们的两侧都存在 $gcd(a,b)$，我们考虑能否通过枚举 $gcd(a,b)$ 来帮助我们计算。

我们考虑下面的式子，我们令 $a=gcd(a,b)*p$, $b=gcd(a,b)*q$,那么我们就有 $a+b=k*b*(gcd(a,b))$ 就转换为了：$gcd(a,b)*p+gcd(a,b)*q=k*gcd(a,b)*q*gcd(a,b)$ 我们这个时候，再去两侧同时除上我们的 $gcd(a,b)$。就有：
$p+q=k*q*gcd(a,b)$,**并且，我们要求我们的 p, q 互质**.

于是，我们就有：$p=(k*gcd(a,b)-1)q$。这个时候，我们**因为我们的 p, q 互质**, 所以我们的**q 在成立的条件下一定为 1**.

所以，我们的 $(k*gcd(a,b)-1)$ 一定是我们的 $p$ 的一个因数，这个时候，我们也就是说，我们要求我们的 $gcd(a,b)$，满足 $p+1=k*gcd(a,b)$。这个时候，我们可以枚举我们的 $p$,然后再去考虑怎么去找到合理的 $k,gcd(a,b)$。

上面的做法是不好做的，并且也是不好判断的，我们不妨改成**枚举我们的 gcd (a, b)**, 然后去看，有哪些 p 是满足我们的条件的。这个时候，我们的答案就应该是：

```
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=2000005;
int tc,n,m; ll ans;
inline void solve(){
	cin>>n>>m; ans=0;
	for(int i=1;i<=m;i++)
		ans+=(n+i)/(1ll*i*i);
	cout<<ans-1<<'\n';
}
int main(){
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cin>>tc; while(tc--) solve();
	return 0;
}
```
