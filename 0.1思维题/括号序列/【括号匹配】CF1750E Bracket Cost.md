# Bracket Cost

## 题面翻译

给你一个长度为 $n$ 的括号序列。

我们能对一个括号序列做以下操作：

- 选择一个**子串**，将其循环右移一位。比如，`(())` 循环右移一位之后变为 `)(()`。
- 在括号序列的**任意位置**加一个左括号或右括号。

我们定义一个括号序列的代价为能将其变为**匹配序列**的最少操作次数。

求这个括号序列所有 $\frac{n(n+1)}{2}$ 个**子串的代价之和**。（子串互相独立）

多组数据。$n\le 2\times 10^5$。

## 题目描述

Daemon Targaryen decided to stop looking like a Metin 2 character. He turned himself into the most beautiful thing, a bracket sequence.

For a bracket sequence, we can do two kind of operations:

- Select one of its substrings $ ^\dagger $ and cyclic shift it to the right. For example, after a cyclic shift to the right, " (())" will become ")(()";
- Insert any bracket, opening ' (' or closing ')', wherever you want in the sequence.

We define the cost of a bracket sequence as the minimum number of such operations to make it balanced $ ^\ddagger $ .

Given a bracket sequence $ s $ of length $ n $ , find the sum of costs across all its $ \frac{n (n+1)}{2} $ non-empty substrings. Note that for each substring we calculate the cost independently.

 $ ^\dagger $ A string $ a $ is a substring of a string $ b $ if $ a $ can be obtained from $ b $ by deletion of several (possibly, zero or all) characters from the beginning and several (possibly, zero or all) characters from the end.

 $ ^\ddagger $ A sequence of brackets is called balanced if one can turn it into a valid math expression by adding characters $ + $ and $ 1 $ . For example, sequences " (())()", " ()", and " (()(()))" are balanced, while ")(", " (()", and " (()))(" are not.

## 输入格式

Each test consists of multiple test cases. The first line contains a single integer $ t $ ( $ 1 \leq t \leq 10^5 $ ) — the number of test cases. The description of test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 1 \le n \le 2 \cdot 10^5 $ ) — the length of the bracket sequence.

The second line of each test case contains a string $ s $ , consisting only of characters ' (' and ')', of length $ n $ — the bracket sequence.

It is guaranteed that sum of $ n $ across all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, print a single integer — the sum of costs of all substrings of $ s $ .

## 样例 #1

### 样例输入 #1

```
5
1
)
4
)()(
3
())
5
(((((
10
)(())))())
```

### 样例输出 #1

```
1
9
6
35
112
```

## 提示

In the first test case, there is the only substring ")". Its cost is $ 1 $ because we can insert ' (' to the beginning of this substring and get a string " ()", that is a balanced string.

In the second test case, the cost of each substring of length one is $ 1 $ . The cost of a substring ")(" is $ 1 $ because we can cyclically shift it to right and get a string " ()". The cost of strings ")()" and " ()(" is $ 1 $ because its enough to insert one bracket to each of them. The cost of substring ")()(" is $ 1 $ because we can cyclically shift it to right and get a string " ()()". So there are $ 4 + 2 + 2 + 1 = 9 $ substring of cost $ 1 $ and $ 1 $ substring of cost $ 0 $ . So the sum of the costs is $ 9 $ .

In the third test case,

- " (", the cost is $ 1 $ ;
- " ()", the cost is $ 0 $ ;
- " ())", the cost is $ 1 $ ;
- ")", the cost is $ 1 $ ;
- "))", the cost is $ 2 $ ;
- ")", the cost is $ 1 $ .

So the sum of the costs is $ 6 $ .

## 题解
我们假设我们已经拥有了一个子串，我们现在要求我们的操作次数是多少，这里我们假设我们已经有了 X 个左括号，Y 个右括号，T 个已经匹配了的括号对，那么我们的构造次数一定是我们的 $max(L,R)-X$,然后，我们现在的问题就变成了我们的二重求和。
这里，对于我们的 $\sum X$,我们考虑每一对已经配对的括号的贡献，这个我们可以简单的计算，一个匹配会在我们的 $l\times(n-r+1)$ 个子串中出现，

对于我们的 $\sum max(L,R)$,我们可以考虑用我们的公式：$((R+L)+|L-{R}|)/{2}$ 然后我们的前面一个小括号就也可以用我们的贡献法，计算我们的一个字母会在几个子串中出现，而我们的 $|L-R|$ 就需要一定的技巧，我们将左括号视为 1，右括号视为-1，我们将所有的前缀和从小到大排序为 s，那么我们的绝对值之和就是我们的 $\sum\sum s_{j}-s_{i}$,

```cpp
#include<bits/stdc++.h>
#define int long long
const int N=1000005;
using namespace std;

void solve(){
	int n;cin>>n;
	string s;cin>>s;
	vector<int> a(1);
	int sum=0;
	for(int i=0;i<n;i++){
		if(s[i]=='(')sum++;
		else sum--;
		a.push_back(sum);
	}
	sort(a.begin(),a.end());
	int res=0,ns=0;
	for(int i=0;i<=n;i++){
   		res+=i*a[i]-ns;//|L-R|
		res+=i*(n-i+1);// L+R
		ns+=a[i];
	}
	res/=2; 
	stack<int> sss;
	for(int i=0;i<n;i++){
		if(s[i]=='('){
			sss.push(i);
		}else{
			if(sss.empty())continue;
			res-=(sss.top()+1)*(n-i);// X
			sss.pop(); 
		}
	}
	cout<<res<<endl;
}

main(){
	ios::sync_with_stdio(0);
	int _T=1;cin>>_T;
	while(_T--)solve();
}
```