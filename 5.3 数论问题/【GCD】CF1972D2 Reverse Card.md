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

我们考虑下面的式子，我们令 $a=gcd(a,b)*p$, $b=gcd(a,b)*q$,那么我们就有 $a+b=k*b*(gcd(a,b))$ 就转换为了：$k*(gcd(a,b)*p+gcd(a,b)*q)=gcd(a,b)*q*gcd(a,b)$ 我们这个时候，再去两侧同时除上我们的 $gcd(a,b)$。就有：
$k*(p+q)=q*gcd(a,b)$,**并且，我们要求我们的 p, q 互质**.

转换成**实际意义**，也就是说要求我们的**qd**是**p+q**的一个倍数，那么我们又因为，我们的 $p+q$ 满足我们的**p, q**互质，所以我们应该还有：$(p+q)|d$。

这个时候，我们有上中下三策。
上策：我们枚举我们的 $d$,然后找到两个互质的 $p,q$ 满足要求，这一步有点像背包，但是我们的返回可能略大
下册：枚举我们的 $p,q$，然后再去找 $p+q$ 对应的所有 $d$
中策：枚举我们的 $p+q$,检查能不能表示为多少个两个质数的和（显然可以），然后再去用这个和乘以我们的所有的因子。

然后这个时候我们发现，我们的**下策其实才是上策**，因为我们的 $p,q$ 满足我们的范围是不超过我们的 $\sqrt{ n }\sqrt{ \mathrm{m} }$ 的，于是，我们就可以有：

```
#include <bits/stdc++.h>
using namespace std;
 
#define nl "\n"
#define nf endl
#define ll long long
#define pb push_back
#define _ << ' ' <<
 
#define INF (ll)1e18
#define mod 998244353
#define maxn 110
 
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
 
    #if !ONLINE_JUDGE && !EVAL
        ifstream cin("input.txt");
        ofstream cout("output.txt");
    #endif
    int t;
    cin>>t;
    while(t--)
    {
        ll n,m; cin >> n>>m;
        ll sq = sqrt(n) + 2,sqm=sqrt(m)+2;
    
        vector bad(sq + 1, vector<bool>(sqm+1, 0));
        for (ll i = 2; i <= min(sq,sqm); i++) {
            for (ll a = i; a <= sq; a += i) {
                for (ll b = i; b <= sqm; b += i) {
                    bad[a][b] = true;
                }
            }
        }
    
        ll ans = 0;
        for (ll a = 1; a * a <= n; a++) {
            for (ll b = 1; b * b <= m; b++) {
                if (bad[a][b]) continue;
                ans += min(n/(a+b)/a,m/(a+b)/b);
            }
        }
        cout << ans << nl;
    }
 
    return 0;
}
```



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
