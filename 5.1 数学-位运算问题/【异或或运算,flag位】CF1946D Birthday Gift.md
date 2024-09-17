Yarik's birthday is coming soon, and Mark decided to give him an array $a$ of length $n$.

Mark knows that Yarik loves bitwise operations very much, and he also has a favorite number $x$, so Mark wants to find the maximum number $k$ such that it is possible to select pairs of numbers \[$l_1, r_1$ \], \[$l_2, r_2$ \], $\ldots$ \[$l_k, r_k$ \], such that:

-   $l_1 = 1$.
-   $r_k = n$.
-   $l_i \le r_i$ for all $i$ from $1$ to $k$.
-   $r_i + 1 = l_{i + 1}$ for all $i$ from $1$ to $k - 1$.
-   $(a_{l_1} \oplus a_{l_1 + 1} \oplus \ldots \oplus a_{r_1}) | (a_{l_2} \oplus a_{l_2 + 1} \oplus \ldots \oplus a_{r_2}) | \ldots | (a_{l_k} \oplus a_{l_k + 1} \oplus \ldots \oplus a_{r_k}) \le x$, where $\oplus$ denotes the operation of [bitwise XOR](https://en.wikipedia.org/wiki/Exclusive_or), and $|$ denotes the operation of [bitwise OR](https://en.wikipedia.org/wiki/Logical_disjunction).

If such $k$ does not exist, then output $-1$.


**Input**

Each test consists of multiple test cases. The first line contains a single integer $t$ ($1 \le t \le 10^4$) — the number of test cases. The following lines contain the descriptions of the test cases.

The first line of each test case contains two integers $n$ and $x$ ($1 \le n \le 10^5, 0 \le x \lt; 2^{30}$) — the length of the array $a$ and the number $x$ respectively.

The second line of each test case contains $n$ integers $a_1, a_2, \ldots, a_n$ ($0 \le a_i \lt; 2^{30}$) — the array $a$ itself.

It is guaranteed that the sum of the values of $n$ across all test cases does not exceed $10^5$.

**Output**

For each test case, output a single integer on a separate line — the maximum suitable number $k$, and $-1$ if such $k$ does not exist.

## 样例：
```
8
3 1
1 2 3
2 2
1 1
2 2
1 3
2 3
0 0
3 2
0 0 1
4 2
1 3 3 7
2 2
2 3
5 0
0 1 2 2 1
```

```
2
2
1
2
3
-1
1
2
```

## 题解
思路一：
本题的思路类似于我们的数位 dp，我们从高到低依次考虑每一位，
如果我们 $x$ 在这一位是 1，那么如果最后分割出来的结果在这一位答案为 $0$,那么我们只需要满足把尽可能多的 1... 1 配对出来，然后对于剩下的 0 部分我们就有多少切多少，这个就是我们能够得到的答案。
如果我们的 $x$ 在这一位为 1，并且我们最后分割出来的结果为 $1$,那么我们就相当于无事发生，因为你不管怎么切都不会影响我们的结果。我们就可以不去做任何限制。

如果我们的 $x$ 在这一位为 0，那么如果最后分割出来的结果在这一位的结果为 0，那么我们一定要满足把尽可能多的 $1,\dots1$ 配对，并且把对应的位置记录出来，让我们的后面的人不能再去分割。

如果我们的 $x$ 在这一位为 0，那么如果后面分割出来在这一位的结果为 $1$，我们直接跳过不更新，因为铁定不合法。

而对于我们的标记的处理，我们这里的思路是采用一个 flag 数组来存储我们能否在我们的某一个位置进行切割，如果可以，我们就把这个位置设置为 1，否则，我们就把这个位置设置为 0. 初始时，我们的 flag 数组默认全都为 1.

```cpp
#include <bits/stdc++.h>
using namespace std;
void solve(){
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		flag[i]=true;
		//flag[i]表示我们的i位能否分割 
	}
	for(int j=30;j>=0;j--){
		int cnt=0;
		if(m&(1<<j)){
			bool ok=true;//表示我们这一整个区间内1的个数 
			for(int i=0;i<=n;i++){
				if(a[i]&(1<<j)){
					ok=!ok;
				}
				if(ok&&flag[i]){
					cnt++;
				}
			}
			if(ok){
				ans=max(ans,cnt);
			}
		}else{
			bool ok=true;
			for(int i=1;i<=n;i++){
				if(a[i]&(1<<j)) ok=!ok;
				if(!ok) flag[i]=false;//这一位必须为0，不能再这个位置分段 
			}
			if(!ok){
				//不能分割，就是之前的最大答案，再向后看没有意义 
				cout<<ans<<endl;
				return;
			}
		}
	}
}
int main(){
	int t;
	cin>>t;
	while(t--){
		solve();
	}
}
```

方法二：二分我们答案，我们转换为计算：我们把我们的原来的答案分成 $m$ 段后，我们得到的最小值是多少，如果我们的最小值比我们的原来的还要大，我们就返回 false, 否则返回 true。
```cpp
#include <bits/stdc++.h>

using namespace std;

#ifndef ONLINE_JUDGE
    #include "debug.h"
#else
    #define debug(x) 
#endif

#define MOD 1000000007
#define INF 1e18
#define endl "\n"
#define pb push_back
#define ppb pop_back
#define ff first
#define ss second
#define sz(x) ((int)(x).size())
#define all(x) (x).begin(), (x).end()
#define int long long

int n, x;
std::vector<int> v;

bool check(int k) {
    set<int> bits;

    for(int i = 29; i >= 0; i--) {
        bits.insert(i);
        int segments = 0;
        map<int, int> cnt;

        debug(i);
        debug(bits);

        for(int j = 0; j < n; j++) {
            for(auto &b: bits) {
                if((1LL << b) & v[j]) {
                    cnt[b]++;
                }
            }

            bool flag = 1;
            for(auto &b: bits) {
                if(cnt[b] & 1) {
                    flag = 0;
                    break;
                }
            }

            if(flag) {
                cnt.clear();
                segments++;
            }
        }

        bool flag = 1;
        if(sz(cnt)) {
            for(auto &b: bits) {
                if(cnt[b] & 1) {
                    flag = 0;
                    break;
                }
            }

            if(flag)
                segments++;
        }

        if(flag)
            flag = (segments >= k);

        if((1LL << i) & x) {
            if(flag) 
                return true;
            else 
                bits.erase(i);
        }
        else {
            if(!flag)
                return false;
        }
    }

    return true;
}

void solve() {
    cin >> n >> x;

    v.clear(); v.resize(n);
    for(int i = 0; i < n; i++)
        cin >> v[i];

    int l = 1, r = n, ans = -1;

    while(l <= r) {
        int mid = l + (r - l) / 2;

        if(check(mid)) {
            l = mid + 1;
            ans = mid;
        }
        else {
            r = mid - 1;
        }
    }

    cout << ans << endl;
}

signed main() {
#ifndef ONLINE_JUDGE
    freopen("Error.txt", "w", stderr);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int tt = 1;
    cin >> tt;
    while(tt--) {
        solve();       
    }
    return 0;
}
```