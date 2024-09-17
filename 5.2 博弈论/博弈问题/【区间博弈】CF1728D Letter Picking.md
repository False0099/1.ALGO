# Letter Picking

## 题面翻译

### 题目描述

Alice 和 Bob 在玩游戏。

给出一个长度为偶数的，非空的且仅含小写字母的字符串 $s$。每个玩家还拥有一个初始为空的字符串。

Alice 先手，两名玩家交替行动。在一次行动中，玩家可以取 $s$ 首或尾字符，将其从 $s$ 中移除后加入到自己的字符串的 **最前面**。

当 $s$ 为空时游戏结束，拥有字典序更小的字符串的玩家获胜。若两名玩家的字符串相等则平局。

若 Alice 和 Bob 都足够聪明，判断谁会取胜，或者游戏为平局。

数据组数 $t\leq 10^3$，$\sum|s|\leq 2\times 10^3$。保证所有输入的 $|s|$ 长度都为偶数。

## 题目描述

Alice and Bob are playing a game. Initially, they are given a non-empty string $ s $ , consisting of lowercase Latin letters. The length of the string is even. Each player also has a string of their own, initially empty.

Alice starts, then they alternate moves. In one move, a player takes either the first or the last letter of the string $ s $ , removes it from $ s $ and prepends (adds to the beginning) it to their own string.

The game ends when the string $ s $ becomes empty. The winner is the player with a lexicographically smaller string. If the players' strings are equal, then it's a draw.

A string $ a $ is lexicographically smaller than a string $ b $ if there exists such position $ i $ that $ a_j = b_j $ for all $ j < i $ and $ a_i < b_i $ .

What is the result of the game if both players play optimally (e. g. both players try to win; if they can't, then try to draw)?

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 1000 $ ) — the number of testcases.

Each testcase consists of a single line — a non-empty string $ s $ , consisting of lowercase Latin letters. The length of the string $ s $ is even.

The total length of the strings over all testcases doesn't exceed $ 2000 $ .

## 输出格式

For each testcase, print the result of the game if both players play optimally. If Alice wins, print "Alice". If Bob wins, print "Bob". If it's a draw, print "Draw".

## 样例 #1

### 样例输入 #1

```
2
forces
abba
```

### 样例输出 #1

```
Alice
Draw
```

## 提示

One of the possible games Alice and Bob can play in the first testcase:

1. Alice picks the first letter in $ s $ : $ s= $ "orces", $ a= $ "f", $ b= $ "";
2. Bob picks the last letter in $ s $ : $ s= $ "orce", $ a= $ "f", $ b= $ "s";
3. Alice picks the last letter in $ s $ : $ s= $ "orc", $ a= $ "ef", $ b= $ "s";
4. Bob picks the first letter in $ s $ : $ s= $ "rc", $ a= $ "ef", $ b= $ "os";
5. Alice picks the last letter in $ s $ : $ s= $ "r", $ a= $ "cef", $ b= $ "os";
6. Bob picks the remaining letter in $ s $ : $ s= $ "", $ a= $ "cef", $ b= $ "ros".

Alice wins because "cef" &lt; "ros". Neither of the players follows any strategy in this particular example game, so it doesn't show that Alice wins if both play optimally.

## 题解
我们本题是一个典型的区间博弈，我们可以设 $f[l,r]$ 表示我们的 $[l,r]$ 区间我们的获胜情况，那么我们根据我们的极大极小原则，我们的 $f[l,r]$ 应该从我们的**第一次决策的最小可能**种选择一个**最大值**，也就是说，我们需要分类为第一次决策与第二次决策，我们最后这一段区间的答案就是我们的**第一次抉择的最大值**，但是我们的第一次抉择的结果有应该由我们的**第二次抉择的最小值**决定。

转换为代码就是：
```
f(a,b)=max(min(f(c),f(d)),min(f(e),f(f)));
```

现在考虑对于本题来说我们应该怎么样设计，我们考虑分类讨论，既然是考虑字典序，那么我们首先肯定是要从低到高的判断，又**根据我们的规则**，我们的低位就是我们的 $dp[i+1][r-1]$ 这些。

**在我们的低位相同的情况下，我们再去比较我们的高位**。这里，为了更好的比较我们的高低位，我们最好是写一个比较函数，然后在这个比较函数内比较即可。

```
#include <bits/stdc++.h>
using namespace std;
const int N=2020;
int dp[N][N];
string s;
int cmp(int a,int b){
	if(s[a]<s[b]){
		return -1;
	}
	if(s[a]>s[b]){
		return 1;
	}
	return 0;
}
void solve(){
	cin>>s;
	int n=s.length();
	for(int i=0;i<n;i++){
		dp[i][i+1]=(s[i]!=s[i+1]);
	}
	for(int len=4;len<=n;len+=2){
		for(int l=0;l+len-1<n;l++){
			int r=l+len-1;
			int f1=(dp[l+1][r-1]==0?cmp(l,r):dp[l+1][r-1]);
			int f2=(dp[l+2][r]==0?cmp(l,l+1):dp[l+2][r]);
			int g1=(dp[l+1][r-1]==0?cmp(r,l):dp[l+1][r-1]);
			int g2=(dp[l][r-2]==0?cmp(r,r-1):dp[l][r-2]);
			dp[l][r]=max(min(f1,f2),min(g1,g2));
		}
	}
	if(dp[0][n-1]==1){
		cout<<"Alice"<<endl;
	}else{
		cout<<"Draw"<<endl;
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
