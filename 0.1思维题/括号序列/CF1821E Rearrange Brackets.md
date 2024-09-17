# Rearrange Brackets

## 题面翻译

- **本题一个测试点内有多组测试数据**。
- 对于一个匹配的括号串，定义它的权值为进行以下操作多次将它清空的最小总代价：
	- 选取两个相邻的左右括号删除，并将代价加上原右括号右边的括号数量。
- 你可以进行 **不超过 $k$ 次** 以下操作，将给定的匹配括号串 $S$ 变为另一个匹配括号串：
	- 选取 **一个** 括号，将它移动到串的任意位置。
- 求最终括号串的权值最小值。
- $1\leq |S|,\sum |S|\leq2\times10^5$，$0\leq k\leq5$。

## 题目描述

A regular bracket sequence is a bracket sequence that can be transformed into a correct arithmetic expression by inserting characters "1" and "+" between the original characters of the sequence. For example:

- Bracket sequences " ()()" and " (())" are regular (the resulting expressions are: " (1)+(1)" and " ((1+1)+1)");
- Bracket sequences ")(", " (" and ")" are not.

You are given a regular bracket sequence. In one move, you can remove a pair of adjacent brackets such that the left one is an opening bracket and the right one is a closing bracket. Then concatenate the resulting parts without changing the order. The cost of this move is the number of brackets to the right of the right bracket of this pair.

The cost of the regular bracket sequence is the smallest total cost of the moves required to make the sequence empty.

Actually, you are not removing any brackets. Instead, you are given a regular bracket sequence and an integer $ k $ . You can perform the following operation at most $ k $ times:

- Extract some bracket from the sequence and insert it back at any position (between any two brackets, at the start or at the end; possibly, at the same place it was before).

After all operations are performed, the bracket sequence has to be regular. What is the smallest possible cost of the resulting regular bracket sequence?

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of testcases.

The first line of each testcase contains a single integer $ k $ ( $ 0 \le k \le 5 $ ) — the maximum number of operations you can perform.

The second line contains a non-empty regular bracket sequence, it consists only of characters ' (' and ')'.

The total length of the regular bracket sequences over all testcases doesn't exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each testcase, print a single integer — the smallest possible cost of the regular bracket sequence after you perform at most $ k $ operations on it.

## 样例 #1

### 样例输入 #1

```
7
0
()
0
(())
1
(())
5
()
1
(()()(()))
2
((())()(()())((())))
3
((())()(()())((())))
```

### 样例输出 #1

```
0
1
0
0
1
4
2
```

## 题解
我们这一题能够发现，我们可以从右往左删除，如果一对括号的深度是 d，当我们删除这对括号时，右括号的右边恰好有 d 个括号，且都是右括号，所以删除这对括号的代价是 d。

我们发现，当我们的 $k=1$ 时，答案是多少？操作等价于把任意一对匹配的括号删除，例如我们的 `(()(()))` 我们可以删除最外层的括号，这样我们都会减少 1，所以我们的深度之和减少了 3.

一般的，我们删除一对匹配的括号，可以让我们的深度和减少 $floor\left( \dfrac{j-i}{2} \right)$

从我们的这个式子我们可以发现，删除外层括号，不会改变内层括号对深度之和的减少量。所以删除 $floor\left( \frac{j-i}{2} \right)$ 最大的 k 对括号即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define deb(x) cerr<<"Line: "<<__LINE__<<", val= "<<x<<"; \n"
#define pii pair<ll,ll>
#define mp make_pair
#define fi first
#define se second
const ll N=2e5+10;
ll T,n,k,L[N],dep[N];
char c[N];
void work(){
	scanf("%lld",&k);
	scanf("%s",c+1);
	n=strlen(c+1);
	ll de=0,ans=0;
	stack<ll> s;
	vector<pii> v;
	for(ll i=1;i<=n;i++){
		if(c[i]=='('){
			de++;
			s.push(i);
		}
		else{
			de--;
			dep[i]=de;
			ans+=de;
			L[i]=s.top();
			s.pop();
			v.push_back(mp(-i+L[i]-1,i));
		}
	}
	sort(v.begin(),v.end());
	for(int i=0;i<min(ll(v.size()),k);i++){
		ans-=-v[i].fi/2-1;	
	}
	printf("%lld\n",ans);
}
signed main(){
	scanf("%lld",&T);
	while(T--){
		work();
	}
	return 0;
}
```