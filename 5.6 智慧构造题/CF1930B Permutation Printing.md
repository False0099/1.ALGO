You are given a positive integer $n$.

Find a permutation $^\dagger$ $p$ of length $n$ such that there do **not** exist two **distinct** indices $i$ and $j$ ($1 \leq i, j &lt; n$; $i \neq j$) such that $p_i$ divides $p_j$ and $p_{i+1}$ divides $p_{j+1}$.

Refer to the Notes section for some examples.

Under the constraints of this problem, it can be proven that at least one $p$ exists.

$^\dagger$ A permutation of length $n$ is an array consisting of $n$ distinct integers from $1$ to $n$ in arbitrary order. For example, $[2,3,1,5,4]$ is a permutation, but $[1,2,2]$ is not a permutation ($2$ appears twice in the array), and $[1,3,4]$ is also not a permutation ($n=3$ but there is $4$ in the array).

**Input**

Each test contains multiple test cases. The first line contains a single integer $t$ ($1 \leq t \leq 10^3$) — the number of test cases. The description of the test cases follows.

The first line of each test case contains a single integer $n$ ($3 \leq n \leq 10^5$) — the length of the permutation $p$.

It is guaranteed that the sum of $n$ over all test cases does not exceed $10^5$.

**Output**

For each test case, output $p_1, p_2, \ldots, p_n$.

If there are multiple solutions, you may output any one of them.

## 题解
我们本题可以通过我们的一种构造方法：我们让我们的奇数位置是我们的 1-u, 让我们的偶数位置从 n-u-1. 这么构造，我们一定可以做到我们需要的效果。

```cpp
#include <bits/stdc++.h>
using namespace std;
inline void solve(){
    int n;
    cin>>n;
    int x=1;
    vector<int> a(n);
    for(int i=0;i<n;i+=2){
        a[i]=x++;
    }
    int j=1;
    for(;j<n;j+=2);
    j-=2;
    for(;j>=0;j-=2){
        a[j]=x++;
    }
    for(int i=0;i<n;i++){
        cout<<a[i]<<" ";
    }
    cout<<"\n";
}
int main(){
	int t;
	cin>>t;
	while(t--){
		solve();
	}
}
```