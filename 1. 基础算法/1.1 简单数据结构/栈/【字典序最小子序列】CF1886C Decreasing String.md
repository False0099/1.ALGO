# Decreasing String

## 题面翻译

有 $t$ 组测试点，每组测试点给出字符串 $s_1$ 和一个整数 $pos$。

以下列规则得到字符串 $ S $ ：

- 从 $s_{i - 1}$ 中删除一个字符，字典序最小的记为 $s_i$
- $S = s_1 + s_2 + \dots + s_n$

输出字符串 $S$ 第 $pos$ 个位置上的字符（即 $S_{pos}$）。

## 题目描述

Recall that string $ a $ is lexicographically smaller than string $ b $ if $ a $ is a prefix of $ b $ (and $ a \ne b $ ), or there exists an index $ i $ ( $ 1 \le i \le \min (|a|, |b|) $ ) such that $ a_i < b_i $ , and for any index $ j $ ( $ 1 \le j < i $ ) $ a_j = b_j $ .

Consider a sequence of strings $ s_1, s_2, \dots, s_n $ , each consisting of lowercase Latin letters. String $ s_1 $ is given explicitly, and all other strings are generated according to the following rule: to obtain the string $ s_i $ , a character is removed from string $ s_{i-1} $ in such a way that string $ s_i $ is lexicographically minimal.

For example, if $ s_1 = \mathrm{dacb} $ , then string $ s_2 = \mathrm{acb} $ , string $ s_3 = \mathrm{ab} $ , string $ s_4 = \mathrm{a} $ .

After that, we obtain the string $ S = s_1 + s_2 + \dots + s_n $ ( $ S $ is the concatenation of all strings $ s_1, s_2, \dots, s_n $ ).

You need to output the character in position $ pos $ of the string $ S $ (i. e. the character $ S_{pos} $ ).

## 输入格式

The first line contains one integer $ t $ — the number of test cases ( $ 1 \le t \le 10^4 $ ).

Each test case consists of two lines. The first line contains the string $ s_1 $ ( $ 1 \le |s_1| \le 10^6 $ ), consisting of lowercase Latin letters. The second line contains the integer $ pos $ ( $ 1 \le pos \le \frac{|s_1| \cdot (|s_1| +1)}{2} $ ). You may assume that $ n $ is equal to the length of the given string ( $ n = |s_1| $ ).

Additional constraint on the input: the sum of $ |s_1| $ over all test cases does not exceed $ 10^6 $ .

## 输出格式

For each test case, print the answer — the character that is at position $ pos $ in string $ S $ . Note that the answers between different test cases are not separated by spaces or line breaks.

## 样例 #1

### 样例输入 #1

```
3
cab
6
abcd
9
x
1
```

### 样例输出 #1

```
abx
```

## 题解
首先，我们考虑要让我们的字典序达到我们的最大，我们一定是让我们的从头到尾，依次看，我们删除哪一个元素可以让我们的答案变小，可以的话就优先删除这一个。

如果我们暴力处理我们的结果的话，我们的答案就是 $o(n^2)$ 级别的。
```cpp
#include <bits/stdc++.h>
using namespace std;
void solve(){
	string s;
	cin>>s;
	int query_n;
	cin>>query_n;
	if(query_n<=s.length()){
		cout<<s[query_n-1];
		return;
	}else{
		query_n-=s.length();
	}
	while(s.length()!=0){
		int delpos=s.length()-1;
		for(int i=0;s[i+1];i++){
			if(s[i]>s[i+1]){
				delpos=i;
				break;
			}
		}
		s.erase(delpos,1);
		//cout<<s<<endl;
		if(query_n<=s.length()){
			cout<<s[query_n-1];
			return;
		}else{
			query_n-=s.length();
		}
	}
}
int main(){
	int t;
	cin>>t;
	while(t--){
		solve();
	}
}
```

我们考虑每一次删除后，我们都有：我们删除元素的前面一定都会是固定的，因此，我们可以 $o(n)$ 的计算出，删除任意 $k$ 个字符后，我们的长度是多少。于是，我们就可以先预处理出我们的这一个 $query$ 是需要我们删除多少个 $k$。这一步的时间复杂度是 $o(\sqrt{ n })$ 的，而之后，我们只需要再去处理出我们删除 $k$ 个字母后的答案是什么样。

而我们删除掉 $k$ 个字母，可以通过我们的单调栈来计算，原因在于我们每一次比较都是比较我们的可行序列的第一个元素和我们的原序列的后一个元素，

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
void solve(){
	string s;
	int query_n;
	cin>>s>>query_n;
	vector<char> stk;
	stk.clear();
	int k=0;
	int len=s.length();
	while(query_n>len&&len!=0){
		query_n-=len;
		k++;
		len--;
	}
	int have_k=0;
	for(int i=0;s[i];i++){
		while(have_k<k&&stk.size()>0&&stk[stk.size()-1]>s[i]){
			stk.pop_back();
			have_k++;
		}
		stk.push_back(s[i]);
	}
	while(have_k<k){
		stk.pop_back();
		have_k++;
	}
//	for(auto u:stk){
//		cout<<u<<endl;
//	}
	//puts("ans");
	cout<<stk[query_n-1];
}
signed main(){
	//std::ios::sync_with_stdio(false);
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin>>t;
	while(t--){
		solve();
	}
}
```