### Problem Statement

There are N people numbered 1 to N on a coordinate plane.  
Person 11 is at the origin.

You are given M pieces of information in the following form:

- From person Ai​'s perspective, person Bi​ is Xi​ units away in the positive x-direction and Yi​ units away in the positive y-direction.

Determine the coordinates of each person. If the coordinates of a person cannot be uniquely determined, report that fact.

### Constraints

- 1≤N≤2×105
- 0≤M≤2×105
- 1≤Ai​,Bi​≤N
- Ai​ ≠Bi​
- −109≤Xi​,Yi​≤109
- All input values are integers.
- The given information is consistent.

---

### Input

The input is given from Standard Input in the following format:

N M
A1​ B1​ X1​ Y1​
⋮
AM​ BM​ XM​ YM​

### Output

Print N lines.  
If the coordinates of person i cannot be uniquely determined, the i-th line should contain `undecidable`.  
If they can be uniquely determined as (si​,ti​), the i-th line should contain si​ and ti​ in this order, separated by a space.

---

### Sample Input 1Copy

Copy

3 2
1 2 2 1
1 3 -1 -2

### Sample Output 1Copy

Copy

0 0
2 1
-1 -2

The figure below shows the positional relationship of the three people.

![Figure](https://img.atcoder.jp/abc320/787d69ac49af24e80723e88b4f954f44.png)

---

### Sample Input 2Copy

Copy

3 2
2 1 -2 -1
2 3 -3 -3

### Sample Output 2Copy

Copy

0 0
2 1
-1 -2

The figure below shows the positional relationship of the three people.

![Figure](https://img.atcoder.jp/abc320/5dde7e83dd268b5b5fc322ddcb44eb86.png)

---

### Sample Input 3Copy

Copy

5 7
1 2 0 0
1 2 0 0
2 3 0 0
3 1 0 0
2 1 0 0
3 2 0 0
4 5 0 0

### Sample Output 3Copy

Copy

0 0
0 0
0 0
undecidable
undecidable

The same piece of information may be given multiple times, and multiple people may be at the same coordinates.

## 题解
我们这一题只需要转化为求一个包含 1 的联通块内有多少个元素即可。注意要连接双向边，并且我们的权值要有方向

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

ll i,j,k,n,m,t,x[200500],y[200500],vis[200500];
vector<tuple<ll,ll,ll> >v[200500];

void dfs(int id){
	if(vis[id])return;
	vis[id]=1;
	for(auto [a,b,c]:v[id]){
		x[a]=x[id]+b; y[a]=y[id]+c;
		dfs(a);
	}
}

int main(){
	ios::sync_with_stdio(0);
	cin>>n>>m;
	for(i=1;i<=m;i++){
		ll a,b,c,d;
		cin>>a>>b>>c>>d;
		v[a].push_back({b,c,d});
		v[b].push_back({a,-c,-d});
	}
	dfs(1);
	for(i=1;i<=n;i++){
		if(!vis[i]){
			cout<<"undecidable\n";
		}
		else{
			cout<<x[i]<<' '<<y[i]<<'\n';
		}
	}
}
```