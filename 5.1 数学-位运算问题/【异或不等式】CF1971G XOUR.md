You are given an array $a$ consisting of $n$ nonnegative integers.

You can swap the elements at positions $i$ and $j$ if $a_i~\mathsf{XOR}~a_j \lt 4$, where $\mathsf{XOR}$ is the [bitwise XOR operation](https://en.wikipedia.org/wiki/Bitwise_operation#XOR).

Find the lexicographically smallest array that can be made with any number of swaps.

An array $x$ is lexicographically smaller than an array $y$ if in the first position where $x$ and $y$ differ, $x_i \lt y_i$.

**Input**

The first line contains a single integer $t$ ($1 \leq t \leq 10^4$) — the number of test cases.

The first line of each test case contains a single integer $n$ ($1 \leq n \leq 2\cdot10^5$) — the length of the array.

The second line of each test case contains $n$ integers $a_i$ ($0 \leq a_i \leq 10^9$) — the elements of the array.

It is guaranteed that the sum of $n$ over all test cases does not exceed $2 \cdot 10^5$.

**Output**

For each test case, output $n$ integers — the lexicographically smallest array that can be made with any number of swaps.

## 题解
我们本题利用的是我们的一个异或不等式的推论，如果我们满足，我们的异或小于某一个 $2^k-1$,那么我们只需要满足，我们**当且仅当**的 $k$ 位**往前都是一样**的即可。

因此，我们可以先预处理出，我们的哪些位置是可以预先无条件交换的，然后，我们再对这些位置进行排序即可。这里，我们的为题就是，怎么去进行我们的排序，这里我们可以考虑用一个 map 套优先队列，来进行我们的**分类**。

```
#include <bits/stdc++.h>
using namespace std;
void solve(){
	int n;
	cin>>n;
	vector<int> a(n);
	map<int,priority_queue<int,vector<int>,greater<int>>> mp;
	for(int i=0;i<n;i++){
		cin>>a[i];
		mp[a[i]/4].push(a[i]);
	}
	for(int i=0;i<n;i++){
		cout<<mp[a[i]/4].top()<<" ";
		mp[a[i]/4].pop();
	}
	puts("");
}
int main(){
	int t;
	cin>>t;
	while(t--){
		solve();
	}
}
```