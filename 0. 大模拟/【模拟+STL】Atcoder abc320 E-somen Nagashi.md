### Problem Statement

There are N people gathered for an event called Flowing Noodles. The people are lined up in a row, numbered 1 to N in order from front to back.

During the event, the following occurrence happens M times:

- At time Ti​, a quantity Wi​ of noodles is flown down. The person at the front of the row gets all of it (if no one is in the row, no one gets it). That person then steps out of the row and returns to their original position in the row at time Ti​+Si​.

A person who returns to the row at time X is considered to be in the row at time X.

After all the M occurrences, report the total amount of noodles each person has got.

### Constraints

- 1≤N≤2×105
- 1≤M≤2×105
- 0<T1​<…<TM​≤109
- 1≤Si​≤109
- 1≤Wi​≤109
- All input values are integers.

---

### Input

The input is given from Standard Input in the following format:

N M
T1​ W1​ S1​
⋮
TM​ WM​ SM​

### Output

Print N lines. The i-th line should contain the amount of noodles person i has got.

---

### Sample Input 1Copy

Copy

3 5
1 1 3
2 10 100
4 100 10000
10 1000 1000000000
100 1000000000 1

### Sample Output 1Copy

Copy

101
10
1000

The event proceeds as follows:

- At time 11, a quantity 11 of noodles is flown down. People 11, 22, and 33 are in the row, and the person at the front, person 11, gets the noodles and steps out of the row.
- At time 22, a quantity 1010 of noodles is flown down. People 22 and 33 are in the row, and the person at the front, person 22, gets the noodles and steps out of the row.
- At time 44, person 11 returns to the row.
- At time 44, a quantity 100100 of noodles is flown down. People 11 and 33 are in the row, and the person at the front, person 11, gets the noodles and steps out of the row.
- At time 1010, a quantity 10001000 of noodles is flown down. Only person 33 is in the row, and the person at the front, person 33, gets the noodles and steps out of the row.
- At time 100100, a quantity 10000000001000000000 of noodles is flown down. No one is in the row, so no one gets these noodles.
- At time 102102, person 22 returns to the row.
- At time 1000410004, person 11 returns to the row.
- At time 10000000101000000010, person 33 returns to the row.

The total amounts of noodles people 11, 22, and 33 have got are 101101, 1010, and 10001000, respectively.

---

### Sample Input 2Copy

Copy

3 1
1 1 1

### Sample Output 2Copy

Copy

1
0
0

---

### Sample Input 3Copy

Copy

1 8
1 1 1
2 2 2
3 3 3
4 4 4
5 5 5
6 6 6
7 7 7
8 8 8

### Sample Output 3Copy

Copy

15

## 题解
思路：采用两个优先队列，一个优先队列维护我们的事件，另一个优先队列维护我们第一个的队列（为什么堆叫做优先队列？）然后每一次，如果一个事件发生了，我们就把我们的对应队列中的头部弹出比较，如果满足条件，我们就弹出并放入一个新的值，新的值=旧的值+ $s_{i}$。


```cpp
#include<bits/stdc++.h>
using namespace std;
using ll=long long;
#define rep(i,l,r)for(int i=(l);i<(r);i++)

int main(){
	int n,m;
	cin >> n >> m;
    std::priority_queue<
      array<int,3>,
      std::vector<array<int,3>>,
      std::greater<array<int,3>>
    > q; // (time, -1, index), (time, w,s)定义我们的事件
	rep(_,0,m){
		int t,w,s;
		cin >> t >> w >> s;
		q.push({t,w,s});
	}
	
	vector<ll>ans(n);
	set<int>s;
	rep(i,0,n)s.insert(i);
	while(q.size()){
		auto[t,w,tt]=q.top();q.pop();//奇怪的语法增加了
		if(w==-1){
			s.insert(tt);
		}else{
			if(s.size()){
				ans[*s.begin()]+=w;//队列的第一个人 
				q.push({t+tt,-1,*s.begin()});//添加回归事件 
				s.erase(s.begin());
			}
		}
	}
	
	rep(i,0,n)cout << ans[i] << endl;
}

```