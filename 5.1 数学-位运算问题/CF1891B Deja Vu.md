You are given an array $a$ of length $n$, consisting of positive integers, and an array $x$ of length $q$, also consisting of positive integers.

There are $q$ modification. On the $i$ \-th modification ($1 \leq i \leq q$), for each $j$ ($1 \leq j \leq n$), such that $a_j$ is divisible by $2^{x_i}$, you add $2^{x_i-1}$ to $a_j$. **Note that** $x_i$ ($1 \leq x_i \leq 30$) is **a positive integer not exceeding 30**.

After **all** modification queries, you need to output the final array.

**Input**

The first line contains a single integer $t$ ($1 \leq t \leq 10^4$) — the number of test cases. The description of the test cases follows.

The first line of each test case contains two integers $n$ and $q$ ($1 \leq n, q \leq 10^5$) —the length of the array $a$ and the number of queries respectively.

The second line of each test case contains $n$ integers $a_1, a_2, a_3, \ldots, a_n$ — the elements of the array $a$ ($1 \leq a_i \leq 10^9$).

The third line of each test case contains $q$ integers $x_1, x_2, x_3, \ldots, x_q$ — the elements of the array $x$ ($1 \leq x_i \leq 30$), which are the modification queries.

It is guaranteed that the sum of $n$ and the sum of $q$ across all test cases does not exceed $2 \cdot 10^5$.

**Output**

For each test case, output the array after all of the modification queries.

## 题解
我们这一题的思路就是先计算出我们每一个位置上我们的最低为 1 是在哪一位上，然后我们将我们的这个排序，我们每一次查询，我们就对我们排序好的上面的所有元素，全部位置变成我们的 $x_{i}-1$,

在这里，我们具体实现时，我们就可以考虑用一个优先队列来进行我们的计算。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,ll> pi;
ll A[500005];
void solve(){
	int n,q; cin>>n>>q;
	for(int i=1; i<=n; i++) cin>>A[i];
	priority_queue<pi,vector<pi>,less<pi>>pq;
	for(int i=1; i<=n; i++){
		int x = A[i];
		int trail = 0;
		while(x%2 == 0){
			trail++;
			x>>=1;
		}
		pq.push(pi(trail,i));
	}
	while(q--){
		int x; cin>>x;
		while(pq.top().first >= x){
			int i = pq.top().second;
			pq.pop();
			A[i]+=(1<<x)/2;
			pq.push(pi(x-1,i));
		}
	}
	for(int i=1; i<=n; i++) cout<<A[i]<<" "; cout<<'\n';
}

int main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	int t = 1;
	cin >> t;
	while(t--) solve();
}
```