# MADMAX

## 题面翻译

Alice和Bob有一个n个点m条边的DAG，每条边上有一个小写英文字母表示权值，Alice和Bob每人有一个棋子，每个人放在一个节点上（可以放在同一个节点上）。 第一轮Alice可以沿一条边把棋子移到一个相邻的节点上，之后Bob沿一条边移动棋子，以此类推，规则规定：每一次移动经过的边的ASCII码单调不降（即，若Alice沿'c'走了一步,Bob只能沿'c'或'c'之后的字母走，然后Alice又要沿Bob走过的字母之后的字母走...）。不能走的人输掉这盘游戏。 现在他们想知道，给定初始位置，两人都按最优策略，谁会赢？

Translated by @Ez3real

## 题目描述

As we all know, Max is the best video game player among her friends. Her friends were so jealous of hers, that they created an actual game just to prove that she's not the best at games. The game is played on a directed acyclic graph (a DAG) with $ n $ vertices and $ m $ edges. There's a character written on each edge, a lowercase English letter.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF917B/069e27c85e808ca91bd505121a515c236f5fa449.png)Max and Lucas are playing the game. Max goes first, then Lucas, then Max again and so on. Each player has a marble, initially located at some vertex. Each player in his/her turn should move his/her marble along some edge (a player can move the marble from vertex $ v $ to vertex $ u $ if there's an outgoing edge from $ v $ to $ u $ ). If the player moves his/her marble from vertex $ v $ to vertex $ u $ , the "character" of that round is the character written on the edge from $ v $ to $ u $ . There's one additional rule; the ASCII code of character of round $ i $ should be greater than or equal to the ASCII code of character of round $ i-1 $ (for $ i>1 $ ). The rounds are numbered for both players together, i. e. Max goes in odd numbers, Lucas goes in even numbers. The player that can't make a move loses the game. The marbles may be at the same vertex at the same time.

Since the game could take a while and Lucas and Max have to focus on finding Dart, they don't have time to play. So they asked you, if they both play optimally, who wins the game?

You have to determine the winner of the game for all initial positions of the marbles.

## 输入格式

The first line of input contains two integers $ n $ and $ m $ ( $ 2<=n<=100 $ , ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF917B/b396341093c8de8c036bb0806e1ea2995564046d.png)).

The next $ m $ lines contain the edges. Each line contains two integers $ v $ , $ u $ and a lowercase English letter $ c $ , meaning there's an edge from $ v $ to $ u $ written $ c $ on it ( $ 1<=v,u<=n $ , $ v≠u $ ). There's at most one edge between any pair of vertices. It is guaranteed that the graph is acyclic.

## 输出格式

Print $ n $ lines, a string of length $ n $ in each one. The $ j $ -th character in $ i $ -th line should be 'A' if Max will win the game in case her marble is initially at vertex $ i $ and Lucas's marble is initially at vertex $ j $ , and 'B' otherwise.

## 样例 #1

### 样例输入 #1

```
4 4
1 2 b
1 3 a
2 4 c
3 4 b
```

### 样例输出 #1

```
BAAA
ABAA
BBBA
BBBB
```

## 样例 #2

### 样例输入 #2

```
5 8
5 3 h
1 2 c
3 1 c
3 2 r
5 1 r
4 3 z
5 4 r
5 2 h
```

### 样例输出 #2

```
BABBB
BBBBB
AABBB
AAABA
AAAAB
```

## 提示

Here's the graph in the first sample test case:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF917B/f151740282c29ba680f87bf7d965be1031607fc5.png)Here's the graph in the second sample test case:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF917B/69855104972fed090a243866610202e10d83d508.png)
 ## 题解
 对于这一题，我们使用NIM函数的引理来解决这一题，即从必败态只能走到必胜态，由必胜态一定能走到必败态。使用引理计算时，我们通常需要用到我们的dp。
我们开一个三维数组$dp[i][j][w]$表示一个人在i另一个人在j，且另一个人上一步走棋走的边值为w的胜负情况，我们枚举i的所有权值不小于w的出边，然后利用引理进行转移。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=105;
int dp[N][N][30];
vector<pair<int,int>>e[N];
int dfs(int a,int b,int c)
{
	if(dp[a][b][c]!=-1)
		return dp[a][b][c];
	dp[a][b][c]=0;
	for(int i=0;i<e[a].size();i++)
	{
		int v=e[a][i].first;
		if(e[a][i].second<c)
			continue;
		if(!dfs(b,e[a][i].first,e[a][i].second))
		{
			dp[a][b][c]=1;
			return 1;
		}
	}
	return 0;
}
int main()
{
	ios::sync_with_stdio(false);
	memset(dp,-1,sizeof(dp));
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=m;i++)
	{
		int u,v;
		char c;
		cin>>u>>v>>c;
		e[u].push_back(make_pair(v,c-'a'));
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			if(dfs(i,j,0))
				cout<<'A';
			else
				cout<<'B';
		}
		cout<<endl;
	}
	return 0;
}
```