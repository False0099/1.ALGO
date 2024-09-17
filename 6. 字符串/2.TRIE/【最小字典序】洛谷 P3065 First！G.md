# [USACO 12 DEC] First! G

## 题目描述

Bessie has been playing with strings again. She found that by

Changing the order of the alphabet she could make some strings come before all the others lexicographically (dictionary ordering).

For instance Bessie found that for the strings "omm", "moo", "mom", and "ommnom" she could make "mom" appear first using the standard alphabet and that she could make "omm" appear first using the alphabet

"abcdefghijklonmpqrstuvwxyz".  However, Bessie couldn't figure out any way to make "moo" or "ommnom" appear first.

Help Bessie by computing which strings in the input could be

lexicographically first by rearranging the order of the alphabet.  To compute if string X is lexicographically before string Y find the index of the first character in which they differ, j.  If no such index exists then X is lexicographically before Y if X is shorter than Y.  Otherwise X is lexicographically before Y if X[j] occurs earlier in the alphabet than Y[j].

Bessie 一直在研究字符串。她发现，通过改变字母表的顺序，她可以按改变后的字母表来排列字符串（字典序大小排列）。

例如，Bessie 发现，对于字符串串“omm”，“moo”，“mom”和“ommnom”，她可以使用标准字母表使“mom”排在第一个（即字典序最小），她也可以使用字母表“abcdefghijklonmpqrstuvwxyz”使得“omm”排在第一个。然而，Bessie 想不出任何方法（改变字母表顺序）使得“moo”或“ommnom”排在第一个。

接下来让我们通过重新排列字母表的顺序来计算输入中有哪些字符串可以排在第一个（即字典序最小），从而帮助 Bessie。

要计算字符串 X 和字符串 Y 按照重新排列过的字母表顺序来排列的顺序，先找到它们第一个不同的字母 X[i]与 Y[i]，按重排后的字母表顺序比较，若 X[i]比 Y[i]先，则 X 的字典序比 Y 小，即 X 排在 Y 前；若没有不同的字母，则比较 X 与 Y 长度，若 X 比 Y 短，则 X 的字典序比 Y 小，即 X 排在 Y 前。

## 输入格式

\* Line 1: A single line containing N (1 <= N <= 30,000), the number of strings Bessie is playing with.

\* Lines 2.. 1+N: Each line contains a non-empty string.  The total number of characters in all strings will be no more than 300,000.  All characters in input will be lowercase characters 'a' through 'z'.  Input will contain no duplicate strings.

第 1 行：一个数字 N（1 <= N <= 30,000），Bessie 正在研究的字符串的数量。

第 2~N+1 行：每行包含一个非空字符串。所有字符串包含的字符总数不会超过 300,000。输入中的所有字符都是小写字母，即 a~z。输入不包含重复的字符串。

## 输出格式

\* Line 1: A single line containing K, the number of strings that could be lexicographically first.

\* Lines 2.. 1+K: The (1+i) th line should contain the ith string that could be lexicographically first.  Strings should be output in the same order they were given in the input.

第 1 行：一个数字 K，表示按重排后的字母表顺序排列的字符串有多少可以排在第一个数量。

第 2~K+1 行：第 i+1 行包含第 i 个按重排后的字母表顺序排列后可以排在第一个的字符串。字符串应该按照它们在输入中的顺序来输出。

## 样例 #1

### 样例输入 #1

```
4
omm
moo
mom
ommnom
```

### 样例输出 #1

```
2
omm
mom
```

## 提示

The example from the problem statement.


Only "omm" and "mom" can be ordered first.


样例即是题目描述中的例子，只有“omm”和“mom”在各自特定的字典序下可以被排列在第一个。

## 题解
我们本题的题意是：给定 n 个小写英文字符串，问哪些串能在特定的字母顺序中字典序最小。

看到与字典序有关的问题，很容易想到建一棵 Trie (宇典树)。对于每一个字符串，我们可以**设它的字典序是所有字符串中最小**的。
 也就是说，这个字符串的第 $i$ 个字母在 Trie 的第 $i$ 层 (根节点算第 0 层) 的所有字母中字典序最小。
 设这个字符串的第 $i$ 个字母为 $u$,我们可以连单向边 $u\to v$,表示我们指定了 $u$ 的字典序比 $v$ 小，其中 $v$ 是第 $i$ 层的其它字母。若这个字符申是其它某个字符串的前缀，则这个字符串不可能成为字典序最小的串，比如说 $abba$ 的字典序一定比 $ab$ 大。当 26 个字母间的关系形成环时，也一定不能成为字典序最小的串。

 怎么判断是否形成环呢？可以用 tarjan 或者拓扑排序。
 这里我采用了拓扑排序。我们从入度为 0 的点开始，不断删去与它相连的边，并修改其它点的入度，将
 新的入度为 0 的点加入队列。若队列已空，但还存在入度不为 0 的点，则说明图存在环，反之则有解。
 时间复杂度为 $O(26m)$。


```cpp
#include <iostream>
#include <cstdio>
#include <queue>
#include <cstring>
#include <string.h>
using namespace std;

const int MAXN=300005;
struct trie{
	int next[27];
	int rank;
}t[MAXN];
int h[27][27],a[27],cnt=1,tot=0,n,ans=0;
string p[MAXN];
char s[MAXN];
bool c[MAXN];
queue <int> q;

void addtrie(int r){
	int id=1;
	for(int i=0;s[i];i++){
		if(!t[id].next[s[i]-96]){
			cnt++;
			t[id].next[s[i]-96]=cnt;
		}
		id=t[id].next[s[i]-96];
	}
	t[id].rank=r;
}


void dfs1(int d,int id){
	if(!s[d]){
		return;
	}
	for(int i=1;i<=26;i++){
		if(t[id].next[i]){
			if(i!=s[d]-96){
				h[s[d]-96][i]=1;
			}
			else{
				dfs1(d+1,t[id].next[i]);
			}
		}
	}
}

bool check(){
	int res=26;
	memset(h,0,sizeof(h));
	memset(a,0,sizeof(a));
	while(!q.empty()) q.pop();
	tot++;
	dfs1(0,1);
	for(int i=1;i<=26;i++){
		for(int j=1;j<=26;j++){
			if(h[i][j]){
				a[j]++;
			}
		}
	}
	for(int i=1;i<=26;i++){
		if(!a[i]){
			q.push(i);
		}
	}
	while(!q.empty()){
		int u=q.front();q.pop();
		res--;
		for(int i=1;i<=26;i++){
			if(h[u][i]){
				a[i]--;
				h[u][i]=0;
				if(a[i]==0){
					q.push(i);
				}
			}
		}
	}
	return res==0;
}

void dfs2(int d,int id){
	if(t[id].rank){
		if(check()){
			ans++;
			c[t[id].rank]=1;
		}
		return;
	}
	for(int i=1;i<=26;i++){
		if(t[id].next[i]){
			s[d]=i+96;
			dfs2(d+1,t[id].next[i]);
			s[d]=0;
		}
	}
}

int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		scanf("%s",s);
		p[i]=s;
		addtrie(i);
	}
	memset(s,0,sizeof(s));
	dfs2(0,1);
	cout<<ans<<endl;
	for(int i=1;i<=n;i++){
		if(c[i]){
			cout<<p[i]<<endl;
		}
	}
	return 0;
}
```