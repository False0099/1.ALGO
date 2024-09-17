# Game on Tree (Hard)

## 题面翻译

人话：在一个树，给定 $t$ 次询问，每一次询问给定一个根节点，上面有一个棋子，两个玩家轮流沿着有向边推动棋子，不能走的玩家判负。**要求实现换根**。

**这是问题的困难版本。这个版本的唯一区别是对 $t$ 的限制。

罗恩和赫敏正在一棵由 $n$ 个节点组成的树上玩游戏，这些节点最初都是不活动的。对局由 $t$ 个回合组成，每个回合开始时都有一颗棋子落在一个节点上，该节点被视为激活节点。棋子的移动包括选择一个节点上有棋子的非活动邻居，并将棋子移动到那里（从而激活这个邻居）。罗恩先下棋，然后与赫敏交替下棋，直到没有有效棋子为止。无法下棋的玩家输掉本轮游戏。如果双方都以最佳方式下棋，谁会在每一轮游戏中获胜？

请注意，所有回合都是用同一棵树进行的，只是起始节点发生了变化。此外，每轮游戏结束后，所有活动节点都会被重新视为非活动节点。

## 题目描述

This is the hard version of the problem. The only difference in this version is the constraint on $ t $ .

Ron and Hermione are playing a game on a tree of $ n $ nodes that are initially inactive. The game consists of $ t $ rounds, each of which starts with a stone on exactly one node, which is considered as activated. A move consists of picking an inactive neighbor of the node with a stone on it and moving the stone there (thus activating this neighbor). Ron makes the first move, after which he alternates with Hermione until no valid move is available. The player that cannot make a move loses the round. If both players play optimally, who wins each round of this game?

Note that all the rounds are played with the same tree; only the starting node changes. Moreover, after each round, all active nodes are considered inactive again.

## 输入格式

The first line contains integers $ n $ ( $ 2 \leq n \leq 2\times 10^5 $ ), $ t $ ( $ 1 \leq t \leq n $ ), the number of nodes in the tree and the number of rounds, respectively.

The next $ n-1 $ lines contain two integers $ 1 \leq u, v \leq n $ each, corresponding to an edge of the tree.

The next line contains $ t $ integers $ 1 \leq u_1 , \dots , u_t \leq n $ , corresponding to the node where the stone is initially put.

## 输出格式

The output consists of $ t $ lines, each line being either "Ron" or "Hermione".

## 样例 #1

### 样例输入 #1

```
5 2
1 2
1 3
3 4
3 5
1 2
```

### 样例输出 #1

```
Ron
Ron
```

## 样例 #2

### 样例输入 #2

```
6 3
1 2
2 3
1 4
4 5
4 6
1 4 6
```

### 样例输出 #2

```
Hermione
Ron
Hermione
```
## 题解
我们本体可以考虑通过我们的一个简单的树上 dp 来进行我们的游戏，我们可以设我们的 $dp[x]$ 表示我们以 $x$ 为根节点开始时，我们的最后的结果是获胜还是失败。

我们考虑怎么转移我们的状态，我们可以考虑使用我们的暴力 dp 来进行转移，但是这样我们的最后的复杂度为 $o(nq)$，但是，我们一定会超时。

这个时候，我们考虑能否通过我们的换根 dp 来进行转移，我们假设可以发生转移，那么我们就可以有：
$f[i]$ 表示我们以 $0$ 为我们的直接根的时候，在 $i$ 点时我们的答案，我们的 $g[i]$ 表示我们以 $i$ 为我们的答案是多少.

```
#include <iostream>
#include <vector>
using namespace std;
const int N=2e5+5;
int n,m,f[N],g[N];
vector<int> e[N];
void dfs1(int x,int fa){
	for(int y:e[x]) if(y!=fa) {
        dfs1(y,x);
        f[x]+=!f[y];
	}
}
void dfs2(int x,int fa,int o){
	g[x]=f[x]+!o;
	for(int y:e[x]) if(y!=fa) dfs2(y,x,g[x]-!f[y]);
}
int main(){
	cin.tie(0)->sync_with_stdio(0);
	cin>>n>>m;
	for(int i=1,u,v;i<n;i++) {
        cin>>u>>v;
        e[u].push_back(v);
        e[v].push_back(u);
	}
	dfs1(1,0);
	dfs2(1,0,1);
	for(int x;m--;) {
        cin>>x;
        cout<<(g[x]?"Ron\n":"Hermione\n");
	}
	return 0;
}

```