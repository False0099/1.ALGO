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
考虑特殊元素 1，如果我们相邻两个差位 1，我们一定可以构造。那么我们现在最原始的想法就是让我们的每一个元素按照我们的顺序依次为 $a[i][j]=i*n+j$,这种想法的问题在于，如果我们的 m 是一个质数，我们的这一种方法就会失效，那么我们有什么其他的方法吗？

我们这里的方法是：交换我们的奇数和偶数，使得我们的相邻两个差一定是 $2*m$，这样我们就能够得到我们的答案。

其实这种思路我们可以推广到数组中，例如：我们 $1,2,3,4$,我们交换后就可以变成：$1,3,2,4$

于是我们考虑优化，假设我们现在又 $n$ 行，我们如果 $n$ 是偶数，我们可以考虑直接让我们的偶数行为偶数 i，奇数行填入奇数 k。



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