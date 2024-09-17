### Problem Statement

We have a typewriter with $N$ rows. The keys in the $i$ \-th row from the top can type the characters in a string $S_i$.

Let us use this keyboard to enter a string, as follows.

-   First, choose an integer $1 \le k \le N$.
-   Then, start with an empty string and only use the keys in the $k$ \-th row from the top to enter a string of length exactly $L$.

How many strings of length $L$ can be entered in this way? Since the answer can be enormous, print it modulo $998244353$.

### Constraints

-   $N$ and $L$ are integers.
-   $1 \le N \le 18$
-   $1 \le L \le 10^9$
-   $S_i$ is a (not necessarily contiguous) non-empty subsequence of `abcdefghijklmnopqrstuvwxyz`.

### Input

Input is given from Standard Input in the following format:


$N$ $L$
$S_1$
$S_2$
$\dots$
$S_N$

### Output

Print the answer.

## 样例：
### Sample Input 1

```
2 2
ab
ac
```

### Sample Output 1

```
7
```

We can enter seven strings: `aa`, `ab`, `ac`, `ba`, `bb`, `ca`, `cc`.

### Sample Input 3

```
5 1000000000
abc
acde
cefg
abcfh
dghi
```

### Sample Output 3

```
346462871
```

Be sure to print the answer modulo $998244353$.


## 题解
本题是我们的一个容斥原理的标准模板，我们通过计算哪些字符选，哪些字符不选来进行我们的容斥，另外，我们需要对我们的字符集进行状态压缩，这样我们在容斥的时候才方便进行计算。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int mod=998244353;
int qpow(int x,int y)
{
	int ret=1;
	while(y){
		if(y&1)
			ret=ret*x%mod;
		x=x*x%mod;
		y/=2;
	}
	return ret;
}
inline int popcount(int s){		// 根据枚举出来的状态确定字符全集大小
	int cnt=0;
	for(int i=0;i<26;i++)
		if((s>>i)&1)cnt++;
	return cnt;
}
signed main(){
	int n,l;
	cin>>n>>l;
	vector<string> s(n+1);
	for(int i=1;i<=n;i++){
		cin>>s[i];
	}
	vector<int> a(n+1,0);
	//vector<bitset<26>> type(n);
	for(int i=1;i<=n;i++){
		for(int j=0;s[i][j];j++){
			a[i]|=(1ll<<(s[i][j]-'a'));
		}
	}
	int ans=0;
	for(long long s=1;s<(1ll<<n);s++){
		/*获得当前状态对应的二进制信息*/
		int sum=0;
		int now=(1ll<<27)-1;
		for(int j=1;j<=n;j++){
			if(s&(1<<(j-1))){
				now&=a[j];
			}
		}
		sum=qpow(popcount(now),l);
		if(popcount(s)&1){
			ans=(ans+sum)%mod;
		}else{
			ans=(ans-sum)%mod;
		}
	}
	cout<<(ans+mod)%mod<<endl;
}
```