Petya and his friend, robot Petya++, like to solve exciting math problems.

One day Petya++ came up with the numbers $n$ and $x$ and wrote the following equality on the board:

$$
n\ \&\ (n+1)\ \&\ \dots\ \&\ m = x,
$$
 where $\&$ denotes the [bitwise AND operation](https://en.wikipedia.org/wiki/Bitwise_operation#AND). Then he suggested his friend Petya find such a minimal $m$ ($m \ge n$) that the equality on the board holds.

Unfortunately, Petya couldn't solve this problem in his head and decided to ask for computer help. He quickly wrote a program and found the answer.

Can you solve this difficult problem?

![](https://espresso.codeforces.com/031794267bde972f35f17902ed959e8302b26c14.png)

**Input**

Each test contains multiple test cases. The first line contains the number of test cases $t$ ($1 \le t \le 2000$). The description of the test cases follows.

The only line of each test case contains two integers $n$, $x$ ($0\le n, x \le 10^{18}$).

**Output**

For every test case, output the smallest possible value of $m$ such that equality holds.

If the equality does not hold for any $m$, print $-1$ instead.

We can show that if the required $m$ exists, it does not exceed $5 \cdot 10^{18}$.

## 题解
我们本题首先看到连续与运算，并且我们的值域很大，我们不妨打表找规律。我们发现，我们每一次下降的数，都是一个 2 的整数倍，于是我们就联想到，是不是我们每一次和运算最多都只能打掉我们的一个 lowbit 呢？
我们不妨接着找规律，我们发现，我们每一次的结果是有限的，我们每一次运算都会消除掉我们的一个连续的 1. 因此，我们考虑下面的做法：
我们用 lowbit 运算枚举我们的最后一位 1，然后让我们的 tmp 加上这个数，这样我们就能消掉一段连续的 1。之后，我们再去看这个数能去更新我们的哪些数，最后查询的时候，用一个 map 即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int lowbit(int x){
	return x&(-x);
}
void solve(){
	int n,q;
	cin>>n>>q;
	map<int,int> mp;
	int tmp=n;
	mp[tmp]=n;
	if(n==0){
		if(q>0){
			cout<<-1<<endl;
			return;
		}else{
			cout<<n<<endl;
			return;
		}
	}
	int addsum=0;
	while(tmp<=2*n){
		int deltnum=lowbit(tmp);
		tmp+=deltnum;
		if(mp.count(tmp&n)){
			mp[(tmp&n)]=min(mp[(tmp&n)],tmp);
		}else{
			mp[(tmp&n)]=tmp;
		}		
	}
	if(mp.count(q)){
		cout<<mp[q]<<endl;
	}else{
		cout<<-1<<endl;
	}
	

}
signed main(){
	int t;
	cin>>t;
	while(t--){
		solve();
	}
}
```