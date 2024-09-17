### Problem Statement

You are given a sequence $A=(A_1,\ldots,A_N)$ of length $N$. The elements of $A$ are distinct.

Process $Q$ queries in the order they are given. Each query is of one of the following two types:

-   `1 x y` : Insert $y$ immediately after the element $x$ in $A$. It is guaranteed that $x$ exists in $A$ when this query is given.
-   `2 x` : Remove the element $x$ from $A$. It is guaranteed that $x$ exists in $A$ when this query is given.

It is guaranteed that after processing each query, $A$ will not be empty, and its elements will be distinct.

Print $A$ after processing all the queries.


### Constraints

-   $1 \leq N \leq 2\times 10^5$
-   $1 \leq Q \leq 2\times 10^5$
-   $1 \leq A_i \leq 10^9$
-   $A_i \neq A_j$
-   For queries of the first type, $1 \leq x,y \leq 10^9$.
-   When a query of the first type is given, $x$ exists in $A$.
-   For queries of the second type, $1 \leq x \leq 10^9$.
-   When a query of the second type is given, $x$ exists in $A$.
-   After processing each query, $A$ is not empty, and its elements are distinct.
-   All input values are integers.

### Input

The input is given from Standard Input in the following format:


$N$ 
$A_1$ $\ldots$ $A_N$
$Q$
$\mathrm{Query}_1$
$\vdots$ 
$\mathrm{Query}_Q$


Here, $\mathrm{Query}_i$ represents the $i$ \-th query and is given in one of the following formats:


$1$ $x$ $y$

$2$ $x$ 


## 题解：
本题是标准的用 map 模拟链表的问题，我们直接手写链表模拟我们的要求即可。
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
signed main(){
	int n;
	cin>>n;
	vector<int> a(n+2,0);
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	int head=0;
	map<int,int> next;
	map<int,int> prev;
	for(int i=1;i<=n;i++){
		if(i==1){
			next[0]=a[i];
		}
		next[a[i]]=a[i+1];
		prev[a[i]]=a[i-1];
	}
	int q;
	cin>>q;
	while(q--){
		int op;
		cin>>op;
		if(op==1){
			int l,r;
			cin>>l>>r;
			int right=next[l];
			next[r]=right;
			prev[r]=l;
			next[l]=r;
			prev[right]=r;
		}else if(op==2){
			int x;
			cin>>x;
			
				int left=prev[x];
				int right=next[x];
				prev[x]=0;
				next[x]=0;
				next[left]=right;
				prev[right]=left;
			
		}
	}
	while(next[head]!=0){
		cout<<next[head]<<" ";
		head=next[head];
	}
}
```