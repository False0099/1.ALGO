You are given integers $n$ and $m$. Fill an $n$ by $m$ grid with the integers $1$ through $n\cdot m$, in such a way that for any two adjacent cells in the grid, the absolute difference of the values in those cells is not a prime number. Two cells in the grid are considered adjacent if they share a side.

![](https://espresso.codeforces.com/a0834d13365d1753094fd957deb6b0ac5840c83a.png)

It can be shown that under the given constraints, there is always a solution.

**Input**

The first line of the input contains a single integer $t$ ($1 \le t \le 1000$) — the number of test cases. The description of the test cases follows.

The first and only line of each test case contains two integers $n$ and $m$ ($4 \le n, m \le 1000$) — the dimensions of the grid.

It is guaranteed that the sum of $n\cdot m$ over all test cases does not exceed $10^6$.

**Output**

For each test case, output $n$ lines of $m$ integers each, representing the final grid. Every number from $1$ to $n\cdot m$ should appear exactly once in the grid.

The extra spaces and blank lines in the sample output below are only present to make the output easier to read, and are **not** required.

If there are multiple solutions, print any of them.

## 题解
我们这一题考虑到 1 也是质数，所以我们的 1-n 直接放肯定在有些情况是一个合法的排列，但当我们的某一个位置不是是，我们就考虑如果我们纵向差为质数的情况，那么我们就想办法把我们的奇数和偶数分别输出即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a[1001][1001],t;
int main(){
	cin>>t;
	while(t--){
		cin>>n>>m;
		int tot=0;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				a[i][j]=++tot;
			}
		}
		for(int i=1;i<=n/2;i++){
			for(int j=1;j<=m;j++){
				cout<<a[2*i][j]<<' ';
			}
			cout<<endl;
		}
		if(n&1){
			for(int i=1;i<=n/2+1;i++){
				for(int j=1;j<=m;j++){
					cout<<a[2*i-1][j]<<' ';
				}
				cout<<endl;
			}
		}
		else{
			for(int i=1;i<=n/2;i++){
				for(int j=1;j<=m;j++){
					cout<<a[2*i-1][j]<<' ';
				}
				cout<<endl;
			}	
		}
		cout<<endl;
	}
	return 0;
}
```