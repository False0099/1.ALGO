### Problem Statement

In AtCoder Kingdom, $N$ kinds of takoyaki_s (ball-shaped Japanese food) are sold. A takoyaki of the $i$ \-th kind is sold for $A_i$ yen.

Takahashi will buy at least one takoyaki in total. He is allowed to buy multiple takoyakis of the same kind.

Find the $K$ \-th lowest price that Takahashi may pay. Here, if there are multiple sets of takoyakis that cost the same price, the price is counted only once.

### Constraints

-   $1 \le N \le 10$
-   $1 \le K \le 2 \times 10^5$
-   $1 \le A_i \le 10^9$
-   All values in the input are integers.

### Input

The input is given from Standard Input in the following format:


$N$ $K$
$A_1$ $A_2$ $\dots$ $A_N$

### Output

Print the answer as an integer.

### Sample Input 1

```
4 6
20 25 30 100
```

### Sample Output 1

```
50
```

The four kinds of takoyakis sold in AtCoder Kingdom cost $20$ yen, $25$ yen, $30$ yen, and $100$ yen.

The six lowest prices that Takahashi may pay are $20$ yen, $25$ yen, $30$ yen, $40$ yen, $45$ yen, and $50$ yen. Thus, the answer is $50$.

Note that at least one takoyaki must be bought.

## 题解
首先，因为我们的元素较少，并且我们的 K 要求不是很高，所以我们一定可以通过我们的搜索的方法来计算出来：也就是，每一次我们取出当前最小的一个数，并且拿这个数和我们的 N 中的数相加，最后得到的结果在放到我们的小根堆中，我们重复上述操作 $k$ 次，我们的堆顶元素就是我们的答案。（类似于我们的 BFS 搜索？）
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mxn = 10;
const ll N = mxn + 10;
set<ll> s, tmp;//定义set
ll n, k, fx, a[N];
signed main(){
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cin >> n >> k;
	for(ll i = 1; i <= n; ++ i) cin >> a[i];
	for(ll i = 1; i <= n; ++ i) tmp.insert(a[i]);//初始化
	while(s.size() <= k) {
		s.insert(* tmp.begin()); fx = * tmp.begin(); tmp.erase(tmp.begin());//将tmp中的最小值加入s中
		for(register int i = 1; i <= n; ++ i) tmp.insert(fx + a[i]);//枚举答案
	}
	for(ll i = 1; i < k; ++ i) s.erase(s.begin());//删除前k-1个
	cout << *s.begin() ;//输出第k个
	return 0;
}
```