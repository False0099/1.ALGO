Recall that string $a$ is lexicographically smaller than string $b$ if $a$ is a prefix of $b$ (and $a \ne b$), or there exists an index $i$ ($1 \le i \le \min(|a|, |b|)$) such that $a_i &lt; b_i$, and for any index $j$ ($1 \le j \land lt; i$) $a_j = b_j$.

Consider a sequence of strings $s_1, s_2, \dots, s_n$, each consisting of lowercase Latin letters. String $s_1$ is given explicitly, and all other strings are generated according to the following rule: to obtain the string $s_i$, a character is removed from string $s_{i-1}$ in such a way that string $s_i$ is lexicographically minimal.

For example, if $s_1 = \mathrm{dacb}$, then string $s_2 = \mathrm{acb}$, string $s_3 = \mathrm{ab}$, string $s_4 = \mathrm{a}$.

After that, we obtain the string $S = s_1 + s_2 + \dots + s_n$ ($S$ is the concatenation of all strings $s_1, s_2, \dots, s_n$).

You need to output the character in position $pos$ of the string $S$ (i. e. the character $S_{pos}$).

**Input**

The first line contains one integer $t$ — the number of test cases ($1 \le t \le 10^4$).

Each test case consists of two lines. The first line contains the string $s_1$ ($1 \le |s_1| \le 10^6$), consisting of lowercase Latin letters. The second line contains the integer $pos$ ($1 \le pos \le \frac{|s_1| \cdot (|s_1| +1)}{2}$). You may assume that $n$ is equal to the length of the given string ($n = |s_1|$).

Additional constraint on the input: the sum of $|s_1|$ over all test cases does not exceed $10^6$.

**Output**

For each test case, print the answer — the character that is at position $pos$ in string $S$. **Note that the answers between different test cases are not separated by spaces or line breaks**.

## 题解
思路：我们可以简单的求出我们每一次删除后，我们能够得到的字符串，所以我们就可以把我们的 pos 转换为第几个串的第几个字符，然后再去求答案即可。

如果我们求出来每一个位置的字符在什么时候被删除，那么就很容易解决了。
显然，一个字符串如果是有序的，那么我们从后往前逐个删除即可。
如果不是有序的，我们就考虑怎么删除某些元素来让我们变得有序。尝试在每时每刻都维护一个有序的字符串
我们的策略如下：
1. 如果我们一开始是无序的，我们的最后一位一定是所有元素中字典序最小的，我们把这个元素给删除。
2. 对于剩余部分，如果仍然是无序的，我们就重复进行上面的判断。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int t[N];
int id[N];
int n,m;
void solve(){
	string s;
	cin>>s;
	
	n=s.length();
	int x=0;
	m=0;
	for(int i=0;s[i];++i){
        //我们发现加入s[i]会使串变得无序
        //因此需要不断弹出栈顶的字符直至加入s[i]后是有序的
        while(m>0&&s[t[m]]>s[i])id[t[m]]=++x,--m;
        t[++m]=i;
    }
    while(m) id[t[m]]=++x,--m;
//    for(int i=0;i<n;i++){
//    	cout<<id[i]<<endl;
//	}
    int pos;
    cin>>pos;
    int now=n;
    x=0;
    while(pos-now>0) pos-=now,++x,--now;
    //判断进行到n时，我们要删除哪些字母 
	string ans=string("");
	for(int i=0;s[i];i++){
		if(id[i]>x) ans+=s[i];
	} 
	//cout<<ans<<endl;
	//cout<<pos<<endl;
	cout<<ans[pos-1]<<" "<<endl;
}
int main(){
	int t;
	cin>>t;
	while(t--){
		solve();
	}
}
```
```