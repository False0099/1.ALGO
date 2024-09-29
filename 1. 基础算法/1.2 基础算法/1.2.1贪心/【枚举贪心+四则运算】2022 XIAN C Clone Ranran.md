Ranran needs to prepare a contest! A contest is made of $c$ problems, and Ranran can do one of the following two things:

-   Clone himself in $a$ minutes. That is, after $a$ minutes, there will be one more Ranran.
-   Prepare a problem in $b$ minutes. That is, after $b$ minutes, there will be one more problem.

Note that a cloned Ranran can also do the two things above. A Ranran cannot do the two things at the same time.

Ranran wants to prepare the contest as fast as possible. But he is very lazy, so he asks you to find the minimum number of minutes to prepare the contest.

You need to answer $T$ queries independently.

**Input**

The first line contains an integer $T$ ($1\leq T\leq 10 ^ 5$).

Each of the next $T$ lines contains three integers $a$, $b$ and $c$ ($1\leq a, b, c\leq 10 ^ 9)$, representing a query.

**Output**

For each test case, output a line with a single integer representing the answer.

## 题解
我们的贡献贪心，就是我们每一次计算每一步操作对于我们的答案的贡献是多少。一般来说，我们的贡献贪心就是让我们的每一步都去选择我们贡献最大的一种操作，但是我们的贡献贪心可能的问题是，我们的这一步操作会受到我们前面操作的影响。所以对于这一类贪心，我们一般都是先确定我们的某一种或者某一类操作顺序，之后我们再去根据我们的操作顺序去计算每一个操作的贪心是多少。

具体到本题，我们就是先确定了，我们的最优解只可能是下面的几种情况：
1. 复制多次后直接做任务（多=1-n）

于是，我们就可以计算我们的每一次的贡献是多少，然后贪心的计算我们的答案了。
```cpp
#pragma GCC optimize("Ofast","unroll-loops","omit-frame-pointer","inline") //Optimization flags
#pragma GCC option("arch=native","tune=native","no-zero-upper") //Enable AVX
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2")
#include<bits/stdc++.h>
#define int long long
//#include<ext/pb_ds/assoc_container.hpp>
using namespace std;
//using namespace __gnu_pbds;
const int inf=0x3f3f3f3f;
const double eps=1e-6;
const int mod=1e9+7;
typedef long long ll;
#ifndef LOCAL
#define cerr if(0)cout
#define eprintf(...) 0
#else
#define eprintf(...) fprintf(stderr, __VA_ARGS__)
#endif
inline string getstr(string &s,int l,int r){string ret="";for(int i=l;i<=r;i++)ret.push_back(s[i]);return ret;}
int modpow(int x,int y,int md=mod){int ret=1;do{if(y&1)ret=(ll)ret*x%md;x=(ll)x*x%md;}while(y>>=1);return ret;}
inline int Rand(){return rand()*32768+rand();}
int T,a,b,c;
signed main(){
	cin>>T;
	while(T--){
		cin>>a>>b>>c;
		long long ans=9e18;
		long long add=0;
		for(int i=1;i<=c*2;i<<=1){
			ans=min(ans,1ll*((c+i-1)/i)*b+add);
			add+=a;
		}
		cout<<ans<<endl;
	}
	return 0;
}

```

