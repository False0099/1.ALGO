Anton got bored during the hike and wanted to solve something. He asked Kirill if he had any new problems, and of course, Kirill had one.

You are given a permutation $p$ of size $n$, and a number $x$ that needs to be found. A permutation of length $n$ is an array consisting of $n$ distinct integers from $1$ to $n$ in arbitrary order. For example, $[2,3,1,5,4]$ is a permutation, but $[1,2,2]$ is not a permutation ($2$ appears twice in the array), and $[1,3,4]$ is also not a permutation ($n=3$ but there is $4$ in the array).

You decided that you are a cool programmer, so you will use an advanced algorithm for the search — binary search. However, you forgot that for binary search, the array must be sorted.

You did not give up and decided to apply this algorithm anyway, and in order to get the correct answer, you can perform the following operation **no more than** $2$ times before running the algorithm: choose the indices $i$, $j$ ($1\le i, j \le n$) and swap the elements at positions $i$ and $j$.

After that, the binary search is performed. At the beginning of the algorithm, two variables $l = 1$ and $r = n + 1$ are declared. Then the following loop is executed:

1.  If $r - l = 1$, end the loop
2.  $m = \lfloor \frac{r + l}{2} \rfloor$
3.  If $p_m \le x$, assign $l = m$, otherwise $r = m$.

The goal is to rearrange the numbers in the permutation before the algorithm so that after the algorithm is executed, $p_l$ is equal to $x$. It can be shown that $2$ operations are always sufficient.

**Input**

Each test consists of multiple test cases. The first line contains a single integer $t$ ($1 \le t \le 2\cdot 10^4$) — the number of test cases. Then follow the descriptions of the test cases.

The first line of each test case contains two integers $n$ and $x$ ($1 \le x \le n \le 2\cdot 10^5$) — the length of the permutation and the number to be found.

The second line contains the permutation $p$ separated by spaces ($1 \le p_i \le n$).

It is guaranteed that the sum of the values of $n$ for all test cases does not exceed $2\cdot 10^5$.

**Output**

For each test case, output an integer $k$ ($0 \le k \le 2$) on the first line — the number of operations performed by you. In the next $k$ lines, output $2$ integers $i$, $j$ ($1 \le i, j \le n$) separated by a space, indicating that you are swapping the elements at positions $i$ and $j$.

Note that you do not need to minimize the number of operations.

**Example**
5
6 3
1 2 3 4 5 6
6 5
3 1 6 5 2 4
5 1
3 5 4 2 1
6 3
4 3 1 5 2 6
3 2
3 2 1

0
1
3 4
2
2 4
1 5
2
4 5
2 4
1
1 3

## 题解
我们本题的思路是：因为我们在**二分查找中，我们位置为 1 的元素是一定不会移动的**，所以我们可以考虑采用我们的下面一种构造：我们让我们的目标元素先移动到我们的 1 位置，然后再去执行我们的二分，最后再把 1 和二分到的最终位置进行交换即可。
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,x,p[500005],c;
signed main()
{
	int t;
	cin>>t;
	while (t--){
		cin>>n>>x;
		for (int i=1;i<=n;i++){
			cin>>p[i];
			if (p[i]==x){
				c=i;
			}
		}
		int l=1,r=n+1;
		while (l<r-1){
			int m=(l+r)/2;
			if (p[m]<=x){
				l=m;
			}else{
				r=m;
			}
		}
		cout<<1<<endl<<c<<" "<<l<<endl;
	}
}
```