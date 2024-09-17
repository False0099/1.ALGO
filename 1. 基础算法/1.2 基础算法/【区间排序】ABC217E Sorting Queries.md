### Problem Statement

We have an empty sequence $A$. You will be given $Q$ queries, which should be processed in the order they are given. Each query is of one of the three kinds below:

-   `1 x` : Append $x$ to the end of $A$.
-   `2` : Print the element at the beginning of $A$. Then, delete that element. It is guaranteed that $A$ will not empty when this query is given.
-   `3` : Sort $A$ in ascending order.

### Constraints

-   $1 \leq Q \leq 2 \times 10^5$
-   $0 \leq x \leq 10^9$
-   $A$ will not be empty when a query `2` is given.
-   All values in input are integers.

### Input

Input is given from Standard Input in the following format:


$Q$
$\mathrm{query} 1$
$\mathrm{query} 2$
$\vdots$
$\mathrm{query} Q$


The $i$ \-th query, $\mathrm{query} i$, begins with the kind of query $c_i$ ($1$, $2$, or $3$). If $c_i = 1$, the line additionally has an integer $x$.

In other words, each query is in one of the three formats below.


$1$ $x$
$2$
$3$

## 题解
我们本题中由于我们每一次查询都是查询一个固定的位置，所以我们可以采用我们的线段树上二分答案的做法，也可以采用我们的 STL 。

对于 1 操作，只需要将 $x$ 放入普通队列中即可。

对于 3 操作，只需要将普通队列中的所有数都放入优先队列中即可，优先队列可以自动排序。
 
而对于 2 操作，若优先队列不为空，则输出优先队列开头的元素，反之则输出普通队列开头的元素。因为如果优先队列不为空，则必然执行过 3 操作，此时原题中的队列开头的元素必为优先队列开头的元素，而普通队列中的元素都被插入在优先队列元素的后面了。

```cpp
#include<bits/stdc++.h>
using namespace std;
int Q,x,opt;
priority_queue<int,vector<int>,greator<int> > qu;//越小越优先的优先队列
queue<int> q;//普通队列
int main(){
	cin>>Q;
	while(Q--){
		cin>>opt;
		if(opt==1){//1操作
			cin>>x;
			q.push(x);
		}
		else if(opt==2){//2操作
			if(qu.size()){
				cout<<qu.top()<<endl;
				qu.pop();
			}
			else{
				cout<<q.front()<<endl;
				q.pop();
			}
		}
		else{//3操作
			while(q.size()){
				qu.push(q.front());//将普通队列中的数转移到优先队列中
				q.pop();
			}
		}
	}
	return 0;
}
```