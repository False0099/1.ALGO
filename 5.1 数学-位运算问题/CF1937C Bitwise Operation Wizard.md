**This is an interactive problem.**

There is a secret sequence $p_0, p_1, \ldots, p_{n-1}$, which is a permutation of $\{0,1,\ldots,n-1\}$.

You need to find any two indices $i$ and $j$ such that $p_i \oplus p_j$ is maximized, where $\oplus$ denotes the [bitwise XOR operation](https://en.wikipedia.org/wiki/Bitwise_operation#XOR).

To do this, you can ask queries. Each query has the following form: you pick arbitrary indices $a$, $b$, $c$, and $d$ ($0 \le a,b,c,d \lt; n$). Next, the jury calculates $x = (p_a \mid p_b)$ and $y = (p_c \mid p_d)$, where $|$ denotes the [bitwise OR operation](https://en.wikipedia.org/wiki/Bitwise_operation#OR). Finally, you receive the result of comparison between $x$ and $y$. In other words, you are told if $x \lt; y$, $x \gt; y$, or $x = y$.

Please find any two indices $i$ and $j$ ($0 \le i,j \lt; n$) such that $p_i \oplus p_j$ is maximum among all such pairs, using at most $3n$ queries. If there are multiple pairs of indices satisfying the condition, you may output any one of them.

**Input**

Each test contains multiple test cases. The first line contains the number of test cases $t$ ($1 \le t \le 10^3$). The description of the test cases follows.

**Interaction**

The first line of each test case contains one integer $n$ ($2 \le n \le 10^4$). At this moment, the permutation $p_0, p_1, \ldots, p_{n-1}$ is chosen. The interactor in this task is **not adaptive**. In other words, the sequence $p$ is fixed in every test case and does not change during the interaction.

To ask a query, you need to pick four indices $a$, $b$, $c$, and $d$ ($0 \le a,b,c,d &lt; n$) and print the line of the following form:

-   "? A b c d"

After that, you receive:

-   "<" if $(p_a \mid p_b) &lt; (p_c \mid p_d)$;
-   "\=" if $(p_a \mid p_b) = (p_c \mid p_d)$;
-   "\>" if $(p_a \mid p_b) &gt; (p_c \mid p_d)$.

You can make at most $3n$ queries of this form.

Next, if your program has found a pair of indices $i$ and $j$ ($0 \le i, j &lt; n$) such that $p_i \oplus p_j$ is maximized, print the line of the following form:

-   "! I j"

Note that this line is **not** considered a query and is **not** taken into account when counting the number of queries asked.

After this, proceed to the next test case.

If you make more than $3n$ queries during an interaction, your program must terminate immediately, and you will receive the Wrong Answer verdict. Otherwise, you can get an arbitrary verdict because your solution will continue to read from a closed stream.

After printing a query or the answer for a test case, do not forget to output the end of line and flush the output. Otherwise, you will get the verdict Idleness Limit Exceeded. To do this, use:

-   fflush (stdout) or cout.Flush () in C++;
-   System.Out.Flush () in Java;
-   flush (output) in Pascal;
-   stdout.Flush () in Python;
-   see the documentation for other languages.

It is guaranteed that the sum of $n$ over all test cases does not exceed $10^4$.

**Hacks**

To hack, follow the test format below.

The first line contains the number of test cases $t$ ($1 \le t \le 10^3$). The description of the test cases follows.

The first line of each test case contains one integer $n$ ($2 \le n \le 10^4$).

The second line of each test case contains $n$ integers $p_0,p_1,\ldots,p_{n-1}$, which represent a permutation of integers from $0$ to $n - 1$.

The sum of $n$ over all test cases should not exceed $10^4$.

## 题解
首先，因为我们得到的是一个排列，所以我们就可以考虑下面的构造方法：
我们先找到我们的最大值，之后，我们再去找与这个最大值或结果最大的数字中的最小的哪一个，就能得到我们的答案。

我们这里，获得最大值的方法是：每个数字对自己或，这样，我们就可以得到我们的自己的最大值。

获得了最大值之后，我们再去吧所有或出来结果为最大值的加入到一个数组中，再在这个数组中取到我们的最小值即可。取最小值的方法和我们的取最大值的方法类似。

```cpp
#include <bits/stdc++.h>
using namespace std;
void solve(){
	int n;
	cin>>n;
	int maxposi=0;
	for(int i=1;i<n;i++){
		char ans;
		cout<<"? "<<i<<" "<<i<<" "<<maxposi<<" "<<maxposi<<endl;
		//cout.flush();
		cin>>ans;
		if(ans=='>'){
			maxposi=i;
		}
	}
	vector<int> possiblepos;
	possiblepos.push_back(0);
	for(int i=1;i<n;i++){
		char ans;
		cout<<"? "<<maxposi<<" "<<i<<" "<<maxposi<<" "<<possiblepos[0]<<endl;
		//cout.flush();
		cin>>ans;
		if(ans=='>'){
			possiblepos.clear();
			possiblepos.push_back(i);
		}else if(ans=='='){
			possiblepos.push_back(i);
		}
	}
	int smallestj=possiblepos[0];
	for(auto u:possiblepos){
		char ans;
		cout<<"? "<<smallestj<<" "<<smallestj<<" "<<u<<" "<<u<<endl;
		//cout.flush();
		cin>>ans;
		if(ans=='>'){
			smallestj=u;
		}
	}
	cout<<"! "<<maxposi<<" "<<smallestj<<endl;
	//cout.flush();
}
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	int t;
	cin>>t;
	while(t--){
		solve();
	}
} 
```