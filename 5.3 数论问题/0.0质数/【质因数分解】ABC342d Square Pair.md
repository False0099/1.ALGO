### Problem Statement

You are given a sequence of non-negative integers $A=(A_1,\ldots,A_N)$ of length $N$. Find the number of pairs of integers $(i,j)$ that satisfy both of the following conditions:

-   $1 \leq i \lt j\leq N$
-   $A_i A_j$ is a square number.

Here, a non-negative integer $a$ is called a square number when it can be expressed as $a=d^2$ using some non-negative integer $d$.

### Constraints

-   All inputs are integers.
-   $2\leq N\leq 2\times 10^5$
-   $0\leq A_i\leq 2\times 10^5$


### Input

The input is given from Standard Input in the following format:

```
$N$
$A_1$ $\ldots$ $A_N$
```

## 题解
本题我们考虑一个数如果是一个完全平方数，那么一定满足，在进行质因数分解后，我们的每一个质数的次方都是偶数次，否则我们就不能得到哦我们的答案。

于是，我们考虑化简，对于每一个数，把他是二次方的项移走，然后我们剩余的部分作为我们的特征值。

如果我们两个数相乘后是我们的平方数，那么我们的两个数之间的特征值一定是相等的。

记得开 long long

```cpp
#include <bits/stdc++.h>
using namespace std;
int main(){
	int n;
	cin>>n;
	map<int,int> mp;
	int ans=0;
	for(int i=0;i<n;i++){
		int u;
		cin>>u;
		if(u==0){
			ans+=i;
			mp[0]++;
			continue;
		}
		for(int j=2;j*j<=u;j++){
			int k=j*j;
			while(u%k==0){
				u/=k;	
			}
		}
		ans+=mp[0]+mp[u];
		mp[u]++; 
	}
	cout<<ans<<endl;
}
```