# Bracket Coloring

## 题面翻译

如果一个括号序列符合以下两个条件中的一个，那么它是优美的：

1、序列的任意一个前缀中，左括号的个数不少于右括号的个数，且整个序列中，左括号的个数等于右括号的个数。

2、序列的任意一个前缀中，右括号的个数不少于左括号的个数，且整个序列中，左括号的个数等于右括号的个数。

给定一个括号序列，你需要把它分成若干组，使得每一组的括号构成的序列都是优美的。求最少需要分成多少组，并输出分组方案。如果无解，输出 $-1$。

## 题目描述

A regular bracket sequence is a bracket sequence that can be transformed into a correct arithmetic expression by inserting characters "1" and "+" between the original characters of the sequence. For example:

- The bracket sequences " ()()" and " (())" are regular (the resulting expressions are: " (1)+(1)" and " ((1+1)+1)");
- The bracket sequences ")(", " (" and ")" are not.

A bracket sequence is called beautiful if one of the following conditions is satisfied:

- It is a regular bracket sequence;
- If the order of the characters in this sequence is reversed, it becomes a regular bracket sequence.

For example, the bracket sequences " ()()", " (())", ")))(((", "))()((" are beautiful.

You are given a bracket sequence $ s $ . You have to color it in such a way that:

- Every bracket is colored into one color;
- For every color, there is at least one bracket colored into that color;
- For every color, if you write down the sequence of brackets having that color in the order they appear, you will get a beautiful bracket sequence.

Color the given bracket sequence $ s $ into the minimum number of colors according to these constraints, or report that it is impossible.

## 输入格式

The first line contains one integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

Each test case consists of two lines. The first line contains one integer $ n $ ( $ 2 \le n \le 2 \cdot 10^5 $ ) — the number of characters in $ s $ . The second line contains $ s $ — a string of $ n $ characters, where each character is either " (" or ")".

Additional constraint on the input: the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, print the answer as follows:

- If it is impossible to color the brackets according to the problem statement, print $ -1 $ ;
- Otherwise, print two lines. In the first line, print one integer $ k $ ( $ 1 \le k \le n $ ) — the minimum number of colors. In the second line, print $ n $ integers $ c_1, c_2, \dots, c_n $ ( $ 1 \le c_i \le k $ ), where $ c_i $ is the color of the $ i $ -th bracket. If there are multiple answers, print any of them.

## 样例 #1

### 样例输入 #1

```
4
8
((())))(
4
(())
4
))((
3
(()
```

### 样例输出 #1

```
2
2 2 2 1 2 2 2 1
1
1 1 1 1
1
1 1 1 1
-1
```


## 题解
**注意，我们本体划分的最优方法，一定是最多分成两组**。，因为我们可以把我们的分散的组合并从而让我们的都在同一种类当中。

我们这一题是一个括号序列的套路：我们把左括号记作+1，右括号记作-1，然后我们求一个前缀和，有一个结论：原序列左右括号能否分为若干个合法序列的充要条件是左右括号个数是否相同，（即前缀和为 0），如果整个序列合法，那么我们直接全部输出 1 即可。否则我们记前缀和为 sum，若 $sum_{i}<0$ 或 $sum_{i-1}<0$ 则分为第一组，剩下的分到第二组。

```cpp
#include<bits/stdc++.h>
#define N 200005
using namespace std;
int read(){
	int x=0,f=1,ch=getchar();
	for(;!isdigit(ch);ch=getchar()) f=(ch=='-')?-1:1;
	for(;isdigit(ch);ch=getchar()) x=(x<<3)+(x<<1)+(ch^48);
	return x*f;
}
int T,n,a[N],sum[N];
string s;
void solve(){
	n=read();cin>>s;
	for(int i=1;i<=n;++i) a[i]=(s[i-1]=='(')?1:-1;
	for(int i=1;i<=n;++i) sum[i]=sum[i-1]+a[i];
	if(sum[n]){
		puts("-1");
		return;
	}
	bool flg1=false,flg2=false;
	for(int i=1;i<=n;++i){
		flg1|=(sum[i]<0);
		flg2|=(sum[i]>0);
	}
	if(!(flg1&flg2)){
		puts("1");
		for(int i=1;i<=n;++i) printf("1 ");
		puts("");
		return;
	}
	puts("2");
	for(int i=1;i<=n;++i) printf((sum[i]<0 || sum[i-1]<0)?"1 ":"2 ");
	puts("");
}
int main(){
	T=read();
	while(T--) solve();
	return 0;
}
```