### Problem Statement

For strings $x$ and $y$, define $f(x, y)$ as follows:

-   $f(x, y)$ is the length of the longest common prefix of $x$ and $y$.

You are given $N$ strings $(S_1, \ldots, S_N)$ consisting of lowercase English letters. Find the value of the following expression:

$\displaystyle \sum_{i=1}^{N-1}\sum_{j=i+1}^N f(S_i,S_j)$.


### Constraints

-   $2 \leq N \leq 3\times 10^5$
-   $S_i$ is a string consisting of lowercase English letters.
-   $1 \leq |S_i|$
-   $|S_1|+|S_2|+\ldots+|S_N|\leq 3\times 10^5$
-   All input numbers are integers.

### Input

The input is given from Standard Input in the following format:


$N$ 
$S_1$ $\ldots$ $S_N$

### Output

Print the answer.

## 题解
我们本题是一个关于树上前缀和的典中典，我们的思路就是：通过我们的一个简单的 TRIE, 在统计答案的时候，我们可以**把贡献下放到每一个点上**的思路，来统计出我们的答案，我们每一个点对于我们的答案的贡献，显然就是这个点出现的总次数-1. 于是，我们只需要暴力插入，暴力统计即可。

```
#include <bits/stdc++.h>
using namespace std;
const int N=1e6+10;
#define int long long
int tr[N][26];
int tot=1;
int cnt[N];
void insert(string s){
	int idx=1;
	for(int i=0;s[i];i++){
		if(!tr[idx][s[i]-'a']){
			tr[idx][s[i]-'a']=++tot;
		}
		idx=tr[idx][s[i]-'a'];
		cnt[idx]++;
	}
}
int query(string s){
	int idx=1;
	int ans=0;
	for(int i=0;s[i];i++){
		idx=tr[idx][s[i]-'a'];
		ans+=cnt[idx]-1;
	}
	return ans;
}
signed main(){
	int n;
	cin>>n;
	int res=0;
	for(int i=0;i<n;i++){
		string s;
		cin>>s;
		insert(s);
		res+=query(s);
	}
	cout<<res<<endl;
}
```

