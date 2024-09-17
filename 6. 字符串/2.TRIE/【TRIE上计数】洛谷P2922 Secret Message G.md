# [USACO 08 DEC] Secret Message G

## 题目描述

Bessie is leading the cows in an attempt to escape! To do this, the cows are sending secret binary messages to each other.

Ever the clever counterspy, Farmer John has intercepted the first $b_i$ ($1 \le b_i \le 10,000$) bits of each of $M$ ($1 \le M \le 50,000$) of these secret binary messages.

He has compiled a list of $N$ ($1 \le N \le 50,000$) partial codewords that he thinks the cows are using. Sadly, he only knows the first $c_j$ ($1 \le c_j \le 10,000$) bits of codeword $j$.

For each codeword $j$, he wants to know how many of the intercepted messages match that codeword (i.e., for codeword $j$, how many times does a message and the codeword have the same initial bits). Your job is to compute this number.

The total number of bits in the input (i.e., the sum of the $b_i$ and the $c_j$) will not exceed  $500,000$.

贝茜正在领导奶牛们逃跑．为了联络，奶牛们互相发送秘密信息．

信息是二进制的，共有 $M$（$1 \le M \le 50000$）条，反间谍能力很强的约翰已经部分拦截了这些信息，知道了第  $i$ 条二进制信息的前 $b_i$（$1 \le b_i \le 10000$）位，他同时知道，奶牛使用 $N$（$1 \le N \le 50000$）条暗号．但是，他仅仅知道第 $j$ 条暗号的前 $c_j$（$1 \le c_j \le 10000$）位。

对于每条暗号 $j$，他想知道有多少截得的信息能够和它匹配。也就是说，有多少信息和这条暗号有着相同的前缀。当然，这个前缀长度必须等于暗号和那条信息长度的较小者。

在输入文件中，位的总数（即 $\sum b_i + \sum c_i$）不会超过 $500000$。

## 输入格式

Line $1$: Two integers: $M$ and $N$.

Lines $2 \ldots M+1$: Line $i+1$ describes intercepted code $i$ with an integer $b_i$ followed by $b_i$ space-separated `0` 's and `1` 's.

Lines $M+2 \ldots M+N+1$: Line $M+j+1$ describes codeword $j$ with an integer $c_j$ followed by $c_j$ space-separated `0` 's and `1` 's.

## 输出格式

Lines $1 \ldots N$: Line $j$: The number of messages that the $j$ -th codeword could match.

## 样例 #1

### 样例输入 #1

```
4 5 
3 0 1 0 
1 1 
3 1 0 0 
3 1 1 0 
1 0 
1 1 
2 0 1 
5 0 1 0 0 1 
2 1 1
```

### 样例输出 #1

```
1 
3 
1 
1 
2
```

## 提示

Four messages; five codewords. 

The intercepted messages start with 010, 1, 100, and 110.

The possible codewords start with 0, 1, 01, 01001, and 11.


0 matches only 010: 1 match

1 matches 1, 100, and 110: 3 matches

01 matches only 010: 1 match

01001 matches 010: 1 match

11 matches 1 and 110: 2 matches

## 题意：
问题可转换为：对于每一个串，计算这个串完全包含模式串的方案数，以及模式串完全包含这个串的总数

我们按照这个串有没有下一个匹配的字符分类，如果这一个串有下一个匹配的字符，那么我们就统计以下一个位置作为完结的字符串有多少个，添加到我们的 add 当中。`p=tr[p][v];sum+=ed[p]; `

如果我们的这个字符串已经没有未来了，那么我们就仅仅统计我们以当前位置为后缀的和，这个已经是我们的 add 了，所以我们直接添加 add 即可。`return sum;`

另外，如果我们的字符串已经完全匹配了，那么我们还需要统计以当前位置作为我们的前缀的字符串有多少个。注意，我们直接加的话，对于相等串会重复计算，所以我们要减去这一种情况，就是 `sum+cnt[p]-ed[p];`


而对于我们的模式串完全包含我们的这个串的方案书，我们则需要统计我们在结束位置的合法前缀个数有哪些。

**注意：写 trie 的时候，先加后赋值**
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=10000;
int tr[N<<5][2],cnt[N<<5],ed[N<<5],tot;
void insert(string s){
	int p=0;
	for(int i=0;s[i];i++){
		int v=s[i]-'0';
		if(!tr[p][v]){
			tr[p][v]=++tot;
		}
		p=tr[p][v];
		cnt[p]++;
	}
	ed[p]++;
}
int query(string s){
	int p=0;
	int sum=0;//统计被包含的前缀 
	bool match_suc=true;
	for(int i=0;s[i];i++){
		int v=s[i]-'0';
		if(!tr[p][v]){
			//失配，进入匹配所有前缀环节
			return sum; 
		}else{
			p=tr[p][v];
			sum+=ed[p];
			//成功匹配 
			
		}
	}
	return sum+cnt[p]-ed[p];

	
	//return cnt[p];	
}
int main(){
	int m,n;
	cin>>m>>n;
	for(int i=0;i<m;i++){
		int b;
		cin>>b;
		string s="";
		for(int i=0;i<b;i++){
			string tmp;
			cin>>tmp;
			s+=tmp;
		}
		//cout<<s<<endl;
		insert(s);
	}
	for(int i=0;i<n;i++){
		string s="";
		int c;
		cin>>c;
		for(int i=0;i<c;i++){
			string tmp;
			cin>>tmp;
			s+=tmp;
		}
		//cout<<s<<endl;
		cout<<query(s)<<'\n';
	}
}
```